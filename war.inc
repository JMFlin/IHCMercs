|----------------------------------------------------------------------------
|- SUB: warrior 
|---------------------------------------------------------------------------- 
|**
	For raid have same communication as alliance rotations.
	If MT then grab aggro, if not then look for adds that do not have tanks as  ${Me.TargetOfTarget.Name.NotEqual[${_tankNameLooper}]}
**|

Sub war_main

	/while (${Me.XTarget} && ${Mode} == 3) {

		/call get_target

		/if (!${validate_combat[${Target.ID}]}) /continue

		/call engage
		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call war_burn_routine
		/call war_rotation ${Target.ID}
		/call war_combat_buffs

		/call use_skill_melee FALSE ${Target.ID}
		/if (!${Me.Song[Battle Leap].ID}) {
			/if (${validate_cast[FALSE, alt, "Battle Leap", ${Target.ID}]}) {
				/call core_cast2 "Battle Leap" alt 0 FALSE
			}
		}

		/if (${Me.PctHPs} < 50 && ${Me.ActiveDisc.ID} != ${FortitudeDiscID}) {
			/disc ${parryall}
		}

		/if (${Me.PctHPs} < 30) {

			/if (${validate_cast[FALSE, disc, "${missall}", ${Me.ID}]}) {
				/if (${Me.ActiveDisc.ID}) {
					/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
						/stopdisc
						/delay 1s !${Me.ActiveDisc.ID}
						/call core_cast2 "${missall}" disc 0 FALSE
					}
				} else {
					/call core_cast2 "${missall}" disc 0 FALSE
				}
			}
		}

		/if (!${Me.ActiveDisc.ID}) {
			/if (${validate_cast[FALSE, disc, "${defenseac}", ${Me.ID}]}) {
				/call core_cast2 "${defenseac}" disc 0 FALSE
			}
		}

		/if (${validate_cast[FALSE, disc, "${shieldhit}", ${Target.ID}]}) {
			/call core_cast2 "${shieldhit}" disc ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Knee Strike", ${Target.ID}]}) {
			/call core_cast2 "Knee Strike" alt ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Gut Punch", ${Target.ID}]}) {
			/call core_cast2 "Gut Punch" alt ${Target.ID} FALSE
		}
		
		/call move_to_camp
		/call check_state

	}
|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID} || ${Me.Buff[Drachnid Entangle].ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure

/return


Sub war_rotation(int _tmpID)
	/declare _notAggroCounter int local 0
	/declare _aoeCasted bool local FALSE
	/declare _notAggroTarget int local 0

	/if (!${_tmpID}) /return
	/if (${Group.MainTank.ID} != ${Me.ID}) /return

	/call get_xtar_no_aggro_aoe ${verboseWAR}
	/varset _notAggroCounter ${Macro.Return}
	/if (${_notAggroCounter} > 1) {
		|***
			AoE Aggro
		**|
		/if (${SpawnCount[NPC radius 30 zradius 30]} > 1 && ${Me.XTarget} > 1) {
			/if (${validate_cast[FALSE, disc, "${aeroar}", ${_tmpID}]}) {
				/call core_cast2 "${aeroar}" disc ${_tmpID} FALSE
				/varset _aoeCasted TRUE
			}
		}
		
		/if (!${_aoeCasted}) {
			/if (${SpawnCount[NPC radius 40 zradius 40]} > 1 && ${Me.XTarget} > 1) {
				/if (${validate_cast[FALSE, alt, "Area Taunt", ${_tmpID}]}) {
					/call core_cast2 "Area Taunt" alt ${_tmpID} FALSE
					/varset _aoeCasted TRUE
				}
			}
		}

		/if (!${_aoeCasted}) {
			| How many mobs are there?
			/if (${SpawnCount[npc radius 50 zradius 50]} > 1 && ${Me.XTarget} > 1) {
				
				/for _count 1 to ${Me.XTarget}

					| If xtarget is not mezzed, add it to count
					/if (${If[${Select[${Me.XTarget[${_count}].Animation},110,26,32,71,72,111]}, 0, 1]} == 1) {
						/varcalc _numberOfSpawn ${_numberOfSpawn}+1
					}

				/next _count

				| If no mob is yet mezzed hit them all
				/if (${_numberOfSpawn} > 1) {
					/if (${validate_cast[FALSE, disc, "${aehitall}", ${_tmpID}]}) {
						/call core_cast2 "${aehitall}" disc ${_tmpID} FALSE
						/varset _aoeCasted TRUE
					}
				}
			}
		}
		
	}

	/call get_xtar_no_aggro FALSE
	/varset _notAggroTarget ${Macro.Return}
	/if (${_notAggroTarget} || ${Me.SecondaryPctAggro} >= 40) {
		|***
			Single Aggro
		**|
		/if (!${_notAggroTarget}) /varset _notAggroTarget ${_tmpID}

		/if (${Me.AbilityReady[Taunt]} && ${Spawn[id ${_notAggroTarget}].Distance} <= 18 && ${Me.TargetOfTarget.Name.NotEqual[${Me.DisplayName}]}) {
			/doability Taunt
		}

		/if (${validate_cast[FALSE, alt, "Call of Challenge", ${_notAggroTarget}]}) {
			/call core_cast2 "Call of Challenge" alt ${_notAggroTarget} FALSE	
			/return
		}

		/if (${validate_cast[FALSE, disc, "${shout}", ${_notAggroTarget}]}) {
			/call core_cast2 "${shout}" disc ${_notAggroTarget} FALSE
			/return
		}
		
		/if (${validate_cast[FALSE, disc, "${insult}", ${_notAggroTarget}]}) {
			/call core_cast2 "${insult}" disc ${_notAggroTarget} FALSE
			/return
		}
		
		/if (${validate_cast[FALSE, disc, "${roar}", ${_notAggroTarget}]}) {
			/call core_cast2 "${roar}" disc ${_notAggroTarget} FALSE
			/return
		}

		/if (${Me.SecondaryPctAggro} > 30) {
			/if (${validate_cast[FALSE, disc, "${PhantomDisc}", ${_notAggroTarget}]}) {
				/call core_cast2 "${PhantomDisc}" disc ${_notAggroTarget} FALSE
				/return
			}
		}
		/if (${Me.SecondaryPctAggro} > 10) {
			/if (${validate_cast[FALSE, disc, "${singlehealhate}", ${_notAggroTarget}]}) {
				/call core_cast2 "${singlehealhate}" disc ${_notAggroTarget} FALSE
				/return
			}
		}

		/if (${Me.SecondaryPctAggro} > 30) {
			/if (${validate_cast[FALSE, alt, "Projection of Fury", ${_notAggroTarget}]}) {
				/call core_cast2 "Projection of Fury" alt ${_notAggroTarget} FALSE
				/return
			}
		}
		
		/if (${validate_cast[FALSE, alt, "Warlord's Grasp", ${_notAggroTarget}]}) {
			/call core_cast2 "Warlord's Grasp" alt ${_notAggroTarget} FALSE
			/return
		}

		/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
			/if (${validate_cast[FALSE, alt, "Ageless Enmity", ${_notAggroTarget}]}) {
				/call core_cast2 "Ageless Enmity" alt ${_notAggroTarget} FALSE
				/return
			}
		}

		/if (${validate_cast[FALSE, disc, "${tongue}", ${_notAggroTarget}]}) {
			/call core_cast2 "${tongue}" disc ${_notAggroTarget} FALSE
			/return
		}

		/if (${validate_cast[FALSE, disc, "${reprisal}", ${_notAggroTarget}]}) {
			/call core_cast2 "${reprisal}" disc ${_notAggroTarget} FALSE
			/return
		}

		/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
			/if (${validate_cast[FALSE, alt, "Blast of Anger", ${_notAggroTarget}]}) {
				/call core_cast2 "Warlord's Fury" alt 0 FALSE
				/call core_cast2 "Blast of Anger" alt ${_notAggroTarget} FALSE
				/return
			}
		}

	} else {

		/if (${Target.Named} || ${Me.PctHPs} < 61) {
			/if (${validate_cast[FALSE, disc, "${knuckle}", ${_tmpID}]}) {
				/call core_cast2 "${knuckle}" disc ${_tmpID} FALSE
			}
		}
	
		/if (${SpawnCount[NPC radius 45 zradius 20 noalert 1]} < 2) {
			/if (${validate_cast[FALSE, alt, "Rampage", ${_tmpID}]}) {
				/call core_cast2 "Rampage" alt ${_tmpID} FALSE
			}
		}
	}

/return

|----------------------------------------------------------------------------
|- SUB: combat_buffs 
|---------------------------------------------------------------------------- 
Sub war_combat_buffs
	
	/if (!${validate_combat_buffs[FALSE]}) /return
	
	/if (!${Me.Song[Field].ID}) {
		/if (${validate_cast[FALSE, disc, "${groupac}", ${Me.ID}]}) {
			/call core_cast2 "${groupac}" disc 0 FALSE
		}
	}

	/if (!${Me.Song[Commanding Voice].ID}) {
		/if (${validate_cast[FALSE, disc, "${groupdodge}", ${Me.ID}]}) {
			/call core_cast2 "${groupdodge}" disc 0 FALSE
		}
	}

	/if (!${Me.ActiveDisc.ID}) {
		/if (${validate_cast[FALSE, disc, "${defenseac}", ${Me.ID}]}) {
			/call core_cast2 "${defenseac}" disc 0 FALSE
		}
	}

	/if (${validate_cast[FALSE, alt, "Spire of the Warlord", ${Me.ID}]}) {
		/call core_cast2 "Spire of the Warlord" alt 0 FALSE
	}

	|--DoAutoPDH: https://forums.daybreakgames.com/eq/index.php?threads/tucos-setup-critique-welcome.240258/
	|-- https://forums.daybreakgames.com/eq/index.php?threads/returning-warrior.253870/
	|-- https://pb.gamerlaunch.com/forums/viewtopic.php?t=11328956&gid=518180
	|-- https://forums.daybreakgames.com/eq/index.php?threads/warrior-ability-stacking.230888/
	|-- Front Mitigation: Pain Doesn't Hurt > Brace for Impact > Diplo Papers
	|-- Rear Mitigation: Dichotomic > RoS BP > Warrior's Bastion
	|-- Front Mitigation: Anguish BP > Warlord's Bravery

	| Main rotation: Dicho -> PDH -> Guardian's Bravery -> Diplomatic Immunity
	
	/if (!${Me.Buff[${DichoDisc}].ID} && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID}) {
		
		| Main rotation stacking check for Dicho
		| SPA stacking check
		/if (!${Me.Buff[${BastionDisc}].ID} && !${Me.Buff[${ChestItemSpellName}].ID}) {
			/if (${validate_cast[FALSE, disc, "${DichoDisc}", ${Me.ID}]}) /call core_cast2 "${DichoDisc}" disc 0 FALSE
		}
	}
	| Main rotation stacking check for PDH
	/if (!${Me.Buff[${DichoDisc}].ID} && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID}) {	
		/if (${validate_cast[FALSE, disc, "${PDHDisc}", ${Me.ID}]})  /call core_cast2 "${PDHDisc}" disc 0 FALSE
	}
	| Main rotation stacking check for Guardian's Bravery
	/if (!${Me.Buff[${DichoDisc}].ID} && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID}) {
		/if (!${Me.Buff[Warlord's Bravery].ID}) {
			/if (${validate_cast[FALSE, item, "Gladiator's Plate Chestguard of War", ${Me.ID}]}) /call core_cast2 "Gladiator's Plate Chestguard of War" item 0 FALSE	
		}
	}
	| Main rotation stacking check for Diplomatic Immunity
	/if (!${Me.Buff[${DichoDisc}].ID} && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID}) {
		/if (!${Me.Buff[Brace for Impact].ID}) {
			/if (${validate_cast[FALSE, item, "Diplomatic Papers", ${Me.ID}]})  /call core_cast2 "Diplomatic Papers" item 0 FALSE	
		}
	}

	| Pain Doesn't Hurt > Brace for Impact > Diplo Papers
	/if (!${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Brace for Impact].ID}) {
		/if (${validate_cast[FALSE, alt, "Brace for Impact", ${Me.ID}]}) /call core_cast2 "Brace for Impact" alt 0 FALSE
	}

	| Dichotomic > RoS BP > Warrior's Bastion
	/if (!${Me.Buff[${DichoDisc}].ID} && !${Me.Buff[${ChestItemSpellName}].ID} && !${Me.Buff[Warrior's Bastion].ID}) {
		/if (${validate_cast[FALSE, item, "${ChestItemName}", ${Me.ID}]}) /call core_cast2 "${ChestItemName}" item 0 FALSE
	}
	| Dichotomic > RoS BP > Warrior's Bastion
	/if (!${Me.Buff[${DichoDisc}].ID} && !${Me.Buff[${ChestItemSpellName}].ID} && !${Me.Buff[Warrior's Bastion].ID}) {
		/if (${validate_cast[FALSE, disc, "${BastionDisc}", ${Me.ID}]}) /call core_cast2 "${BastionDisc}" disc 0 FALSE	
	}

	| Anguish BP > Warlord's Bravery
	/if (!${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Warlord's Bravery].ID}) {
		/if (${validate_cast[FALSE, alt, "Warlord's Bravery", ${Me.ID}]}) /call core_cast2 "Warlord's Bravery" alt 0 FALSE
	}
	
	| Defensive buffs based on health
	/if (${Me.PctHPs} < 45) {
		/if (${validate_cast[FALSE, alt, "Blade Guardian", ${Me.ID}]}) /call core_cast2 "Blade Guardian" alt 0 FALSE
	}
	
	/if (${Me.PctHPs} < 25) {
		/if (${validate_cast[FALSE, alt, "Warlord's Resurgence", ${Me.ID}]}) /call core_cast2 "Warlord's Resurgence" alt 0 FALSE
	} 
	
	/if (${Me.PctHPs} < 60 || ${check_for_named[FALSE]}) {
		/if (${validate_cast[FALSE, alt, "Imperator's Command", ${Me.ID}]}) /call core_cast2 "Imperator's Command" alt 0 FALSE
		/if (${validate_cast[FALSE, alt, "Resplendent Glory", ${Me.ID}]}) /call core_cast2 "Resplendent Glory" alt 0 FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: DoDisc 
|---------------------------------------------------------------------------- 
Sub war_burn_routine

	/if (!${validate_combat_buffs[${Target.ID}]}) /return

	/if (${validate_cast[FALSE, disc, "${missall}", ${Me.ID}]}) {
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/call core_cast2 "${missall}" disc 0 FALSE
			}
		} else {
			/call core_cast2 "${missall}" disc 0 FALSE
		}
	}

	/if (${validate_cast[FALSE, disc, "${meleemit}", ${Me.ID}]}) {
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/call core_cast2 "${meleemit}" disc 0 FALSE
			}
		} else {
			/call core_cast2 "${meleemit}" disc 0 FALSE
		}
	}

	/if (${validate_cast[FALSE, alt, "Mark of the Mage Hunter", ${Me.ID}]}) {
		/call core_cast2 "Mark of the Mage Hunter" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, disc, "${attention}", ${Me.ID}]}) {
		/call core_cast2 "${attention}" disc ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, alt, "Warlord's Tenacity", ${Me.ID}]}) {
		/call core_cast2 "Warlord's Tenacity" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Wars Sheol's Heroic Blade", ${Me.ID}]}) {
		/call core_cast2 "Wars Sheol's Heroic Blade" alt ${Target.ID} FALSE
	}
	/if (${validate_cast[FALSE, alt, "Rage of Rallos Zek", ${Me.ID}]}) {
		/call core_cast2 "Rage of Rallos Zek" alt 0 FALSE
	}

	/if (${validate_cast[FALSE, disc, "${throat}", ${Me.ID}]}) {
		/call core_cast2 "${throat}" disc ${Target.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: get_aggro
|---------------------------------------------------------------------------- 
Sub war_get_aggro

	/if (${Group.MainTank.ID} != ${Me.ID}) /return
	/if (!${validate_combat[${Target.ID}]}) /return

	/if (${validate_cast[FALSE, alt, "Call of Challenge", ${Target.ID}]}) /call core_cast2 "Call of Challenge" alt ${Target.ID} FALSE	

	/if (${validate_cast[FALSE, disc, "${shout}", ${Target.ID}]}) /call core_cast2 "${shout}" disc ${Target.ID} FALSE
	
	/if (${validate_cast[FALSE, disc, "${insult}", ${Target.ID}]}) /call core_cast2 "${insult}" disc ${Target.ID} FALSE
	
	/if (${validate_cast[FALSE, disc, "${roar}", ${Target.ID}]}) /call core_cast2 "${roar}" disc ${Target.ID} FALSE

	/if (${Me.SecondaryPctAggro} > 10) {
		/if (${validate_cast[FALSE, disc, "${PhantomDisc}", ${Target.ID}]}) /call core_cast2 "${PhantomDisc}" disc ${Target.ID} FALSE
	}
	/if (${Me.SecondaryPctAggro} > 10) {
		/if (${validate_cast[FALSE, disc, "${singlehealhate}", ${Target.ID}]}) /call core_cast2 "${singlehealhate}" disc ${Target.ID} FALSE
	}

	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Projection of Fury", ${Target.ID}]}) /call core_cast2 "Projection of Fury" alt ${Target.ID} FALSE
	}
	
	/if (${validate_cast[FALSE, alt, "Warlord's Grasp", ${Target.ID}]}) /call core_cast2 "Warlord's Grasp" alt ${Target.ID} FALSE

	/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
		/if (${validate_cast[FALSE, alt, "Ageless Enmity", ${Target.ID}]}) /call core_cast2 "Ageless Enmity" alt ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, disc, "${tongue}", ${Target.ID}]}) /call core_cast2 "${tongue}" disc ${Target.ID} FALSE

	/if (${validate_cast[FALSE, disc, "${reprisal}", ${Target.ID}]}) /call core_cast2 "${reprisal}" disc ${Target.ID} FALSE


	/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
		/if (${validate_cast[FALSE, alt, "Blast of Anger", ${Target.ID}]}) {
			/call core_cast2 "Warlord's Fury" alt 0 FALSE
			/call core_cast2 "Blast of Anger" alt ${Target.ID} FALSE
		}
	}

/return
|----------------------------------------------------------------------------
|- SUB: AoEAggro   
|---------------------------------------------------------------------------- 
Sub war_aoe_aggro
	/declare _count				 int local 1
	/declare _numberOfSpawn 	 int local 0

	/if (${Group.MainTank.ID} != ${Me.ID}) /return

	/if (${SpawnCount[NPC radius 30 zradius 30]} > 1 && ${Me.XTarget} > 1) {
		/if (${validate_cast[FALSE, disc, "${aeroar}", ${Target.ID}]}) {
			/call core_cast2 "${aeroar}" disc ${Target.ID} FALSE
			/return
		}
	}
	
	/if (${SpawnCount[NPC radius 40 zradius 40]} > 1 && ${Me.XTarget} > 1) {
		/if (${validate_cast[FALSE, alt, "Area Taunt", ${Target.ID}]}) {
			/call core_cast2 "Area Taunt" alt ${Target.ID} FALSE
			/return
		}
	}

	| How many mobs are there?
	/if (${SpawnCount[npc radius 50 zradius 50]} > 1 && ${Me.XTarget} > 1) {
		
		/for _count 1 to ${Me.XTarget}

			| If xtarget is not mezzed, add it to count
			/if (${If[${Select[${Me.XTarget[${_count}].Animation},110,26,32,71,72,111]}, 0, 1]} == 1) {
				/varcalc _numberOfSpawn ${_numberOfSpawn}+1
			}

		/next _count

		| If no mob is yet mezzed hit them all
		/if (${_numberOfSpawn} > 1) {
			/if (${validate_cast[FALSE, disc, "${aehitall}", ${Target.ID}]}) {
				/call core_cast2 "${aehitall}" disc ${Target.ID} FALSE
			}
		}
	}
/return