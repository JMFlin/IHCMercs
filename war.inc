|----------------------------------------------------------------------------
|- SUB: warrior 
|---------------------------------------------------------------------------- 
Sub war_main
	
	/while (${Me.XTarget}) {
		/call engage

		/call get_target
		/call check_add_aggro
		/call war_get_aggro

		/if (!${validate_combat[${Target.ID}]} ) /return

		/call war_get_aggro
		/if (!${Me.Song[Battle Leap].ID}) {
			/if (${validate_cast[FALSE, alt, "Battle Leap", ${Target.ID}]}) /call core_cast2 "Battle Leap" alt 0 FALSE
		}

		/call use_skill_melee FALSE ${Target.ID}
		
		/call war_get_aggro
		/call check_add_aggro

		/if (${Target.Named} || ${Me.PctHPs} < 61) {
			/if (${validate_cast[FALSE, disc, "${knuckle}", ${Target.ID}]}) /call core_cast2 "${knuckle}" disc ${Target.ID} FALSE
		}
		
		/call check_add_aggro
		/call war_aoe_aggro

		/if (${SpawnCount[NPC radius 45 zradius 20 noalert 1]} < 2) {
			/if (${validate_cast[FALSE, alt, "Rampage", ${Target.ID}]}) /call core_cast2 "Rampage" alt ${Target.ID} FALSE
		}

		/if (${Me.SecondaryPctAggro} > 10) {
			/if (${validate_cast[FALSE, disc, "${singlehealhate}", ${Target.ID}]}) /call core_cast2 "${singlehealhate}" disc ${Target.ID} FALSE
		}
		
		/call war_get_aggro

		/if (${Me.SecondaryPctAggro} > 10) {
			/if (${validate_cast[FALSE, disc, "${phantom}", ${Target.ID}]}) /call core_cast2 "${phantom}" disc ${Target.ID} FALSE
		}

		/call war_combat_buffs
		/call check_add_aggro
		/call war_disc

		/if (${Me.SecondaryPctAggro} > 30) {
			/if (${validate_cast[FALSE, alt, "Projection of Fury", ${Target.ID}]}) /call core_cast2 "Projection of Fury" alt ${Target.ID} FALSE
		}
		/if (${Me.SecondaryPctAggro} > 50) {
			/if (${validate_cast[FALSE, alt, "Warlord's Grasp", ${Target.ID}]}) /call core_cast2 "Warlord's Grasp" alt ${Target.ID} FALSE
		}
		
		/call war_get_aggro

		/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
			/if (${validate_cast[FALSE, alt, "Ageless Enmity", ${Target.ID}]}) /call core_cast2 "Ageless Enmity" alt ${Target.ID} FALSE
		}

		/call check_add_aggro

		/if (${validate_cast[FALSE, disc, "${tongue}", ${Target.ID}]}) /call core_cast2 "${tongue}" disc ${Target.ID} FALSE

		/if (${validate_cast[FALSE, disc, "${reprisal}", ${Target.ID}]}) /call core_cast2 "${reprisal}" disc ${Target.ID} FALSE

		/call war_combat_buffs
		/call war_disc
		/call war_aoe_aggro
	}
|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID} || ${Me.Buff[Drachnid Entangle].ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure

/return
|----------------------------------------------------------------------------
|- SUB: combat_buffs 
|---------------------------------------------------------------------------- 
Sub war_combat_buffs
	
	/if (!${validate_combat_buffs[FALSE]}) /return

	/call engage
	
	/if (!${Me.Song[Field].ID}) {
		/if (${validate_cast[FALSE, disc, "${groupac}", ${Me.ID}]}) /call core_cast2 "${groupac}" disc 0 FALSE
	}

	/if (!${Me.Song[Commanding Voice].ID}) {
		/if (${validate_cast[FALSE, disc, "${groupdodge}", ${Me.ID}]}) /call core_cast2 "${groupdodge}" disc 0 FALSE
	}

	/if (!${Me.ActiveDisc.ID}) {
		/if (${validate_cast[FALSE, disc, "${defenseac}", ${Me.ID}]}) /call core_cast2 "${defenseac}" disc 0 FALSE
	}

	/if (${validate_cast[FALSE, alt, "Brace for Impact", ${Me.ID}]}) /call core_cast2 "Brace for Impact" alt 0 FALSE

	|--DoAutoPDH: https://forums.daybreakgames.com/eq/index.php?threads/tucos-setup-critique-welcome.240258/
	|-- https://forums.daybreakgames.com/eq/index.php?threads/returning-warrior.253870/
	|-- https://pb.gamerlaunch.com/forums/viewtopic.php?t=11328956&gid=518180
	|-- https://forums.daybreakgames.com/eq/index.php?threads/warrior-ability-stacking.230888/
	|-- Front Mitigation: Pain Doesn't Hurt > Brace for Impact > Diplo Papers
	|-- Rear Mitigation: Dichotomic > RoS BP > Warrior's Bastion
	|-- Front Mitigation: Anguish BP > Warlord's Bravery

	/if (!${Me.Buff[Diplomatic Immunity].ID} && !${Me.Song[Pain Doesn't Hurt].ID} && ${Me.CombatAbilityReady[${Spell[Pain Doesn't Hurt].RankName}]}) {
		/if (${validate_cast[FALSE, disc, "${absorball}", ${Me.ID}]}) /call core_cast2 "${absorball}" disc 0 FALSE
	} else /if (!${Me.Song[Pain Doesn't Hurt].ID} && !${FindItem[${ItemDipPapers}].TimerReady}) {
		/if (${validate_cast[FALSE, item, "${ItemDipPapers}", ${Me.ID}]}) /call core_cast2 "${ItemDipPapers}" item 0 FALSE
	}

	/if (!${Me.Buff[${warbulwark}].ID} && !${Me.Buff[Roaring Shield].ID} && ${Me.CombatAbilityReady[${bmdisc}]}) {
		|/docommand /disc 57800
		/if (${validate_cast[FALSE, disc, "${bmdisc}", ${Me.ID}]}) /call core_cast2 "${bmdisc}" disc 0 FALSE
	} else /if (!${FindItem[${ChestItemName}].TimerReady} && !${Me.Buff[Dichotomic Shield].ID} && !${Me.Buff[${warbulwark}].ID}) {
		/if (${validate_cast[FALSE, item, "${ChestItemName}", ${Me.ID}]}) /call core_cast2 "${ChestItemName}" item 0 FALSE
	} else /if (!${Me.Buff[Dichotomic Shield].ID} && !${Me.Buff[${warbulwark}].ID} && !${Me.Buff[Roaring Shield].ID}) {
		/if (${validate_cast[FALSE, disc, "${warbulwark}", ${Me.ID}]}) /call core_cast2 "${warbulwark}" disc 0 FALSE
	} 
	
	/if (!${FindItem[${ItemOoWBP}].TimerReady} && !${Me.Buff[Warlord's Bravery].ID} && !${Me.Buff[Spire of the Warlord].ID}) {
		/if (${validate_cast[FALSE, item, "${ItemOoWBP}", ${Me.ID}]}) /call core_cast2 "${ItemOoWBP}" item 0 FALSE
	} else /if (!${Me.Buff[Warlord's Bravery].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Spire of the Warlord].ID} && ${Me.AltAbilityReady[Warlord's Bravery]}) {
		/if (${validate_cast[FALSE, alt, "Warlord's Bravery", ${Me.ID}]}) /call core_cast2 "Warlord's Bravery" alt 0 FALSE
	}

	/if (!${Me.Buff[Warlord's Bravery].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Spire of the Warlord].ID} && ${Me.AltAbilityReady[Spire of the Warlord]}) {
		/if (${validate_cast[FALSE, alt, "Spire of the Warlord", ${Me.ID}]}) /call core_cast2 "Spire of the Warlord" alt 0 FALSE
	}

	|-- Defensive buffs based on health
	/if (${Me.PctHPs} < 45) {
		/if (${validate_cast[FALSE, alt, "Blade Guardian", ${Me.ID}]}) /call core_cast2 "Blade Guardian" alt 0 FALSE
	}
	
	/if (${Me.PctHPs} < 25) {
		/if (${validate_cast[FALSE, alt, "Warlord's Resurgence", ${Me.ID}]}) /call core_cast2 "Warlord's Resurgence" alt 0 FALSE
	} 
	
	/if (${Me.PctHPs} < 45 || ${Target.Named}) {
		/if (${validate_cast[FALSE, alt, "Imperator's Charge", ${Me.ID}]}) /call core_cast2 "Imperator's Charge" alt 0 FALSE
		/if (${validate_cast[FALSE, alt, "Resplendent Glory", ${Me.ID}]}) /call core_cast2 "Resplendent Glory" alt 0 FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: DoDisc 
|---------------------------------------------------------------------------- 
Sub war_disc

	/if (!${validate_combat[${Target.ID}]} ) /return

	/if (${Me.PctHPs} < 55 && ${Me.ActiveDisc.ID} != ${FortitudeDiscID}) {
		/disc ${parryall}
	}

	/if (${Me.XTarget} > 2 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/disc ${missall}
				/if (${validate_cast[FALSE, disc, "${missall}", ${Me.ID}]}) /call core_cast2 "${missall}" disc 0 FALSE
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${missall}", ${Me.ID}]}) /call core_cast2 "${missall}" disc 0 FALSE
		}
	
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/if (${validate_cast[FALSE, disc, "${meleemit}", ${Me.ID}]}) /call core_cast2 "${meleemit}" disc 0 FALSE
			}
		} else {
			/disc ${meleemit}
			/if (${validate_cast[FALSE, disc, "${meleemit}", ${Me.ID}]}) /call core_cast2 "${meleemit}" disc 0 FALSE
		}
	}

	/if (${Target.Named} || ${Target.Level} > (${Me.Level}+3)) {

		/if (${validate_cast[FALSE, alt, "Mark of the Mage Hunter", ${Me.ID}]}) /call core_cast2 "Mark of the Mage Hunter" alt 0 FALSE
		/if (${validate_cast[FALSE, disc, "${attention}", ${Me.ID}]}) /call core_cast2 "${attention}" disc ${Target.ID} FALSE
	}

	/if (${Me.XTarget} > 3 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) {

		/if (${validate_cast[FALSE, alt, "Warlord's Tenacity", ${Me.ID}]}) /call core_cast2 "Warlord's Tenacity" alt 0 FALSE
		/if (${validate_cast[FALSE, alt, "Wars Sheol's Heroic Blade", ${Me.ID}]}) /call core_cast2 "Wars Sheol's Heroic Blade" alt ${Target.ID} FALSE
		/if (${validate_cast[FALSE, alt, "Rage of Rallos Zek", ${Me.ID}]}) /call core_cast2 "Rage of Rallos Zek" alt 0 FALSE
	}

	/if (${Target.Named}) {
		/if (${validate_cast[FALSE, disc, "${throat}", ${Me.ID}]}) /call core_cast2 "${throat}" disc ${Target.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: get_aggro
|---------------------------------------------------------------------------- 
Sub war_get_aggro

	/if (${Group.MainTank.ID} != ${Me.ID}) /return
	/if (!${validate_combat[${Target.ID}]} ) /return
	
	/call engage

	/call use_skill_melee FALSE ${Target.ID}

	/if (${validate_cast[FALSE, alt, "Call of Challenge", ${Target.ID}]}) /call core_cast2 "Call of Challenge" alt ${Target.ID} FALSE	

	/if (${validate_cast[FALSE, disc, "${shout}", ${Target.ID}]}) /call core_cast2 "${shout}" disc ${Target.ID} FALSE
	
	/if (${validate_cast[FALSE, disc, "${insult}", ${Target.ID}]}) /call core_cast2 "${insult}" disc ${Target.ID} FALSE
	
	/if (${validate_cast[FALSE, disc, "${roar}", ${Target.ID}]}) /call core_cast2 "${roar}" disc ${Target.ID} FALSE
	
	
	/if (${validate_cast[FALSE, disc, "${shieldhit}", ${Target.ID}]}) /call core_cast2 "${shieldhit}" disc ${Target.ID} FALSE

	/if (${validate_cast[FALSE, alt, "Knee Strike", ${Target.ID}]}) /call core_cast2 "Knee Strike" alt ${Target.ID} FALSE

	/if (${validate_cast[FALSE, alt, "Gut Punch", ${Target.ID}]}) /call core_cast2 "Gut Punch" alt ${Target.ID} FALSE

|**
	/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {

	}

	${validate_cast[FALSE, alt, "Warlord's Fury", ${Target.ID}]} is always false
**|
	/if (${validate_cast[FALSE, alt, "Blast of Anger", ${Target.ID}]}) {
			/call core_cast2 "Warlord's Fury" alt 0 FALSE
			/call core_cast2 "Blast of Anger" alt ${Target.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: AoEAggro   
|---------------------------------------------------------------------------- 
Sub war_aoe_aggro
	/declare _count				 int local 1
	/declare _numberOfSpawn 	 int local 0

	/if (${Group.MainTank.ID} != ${Me.ID}) /return
	/if (!${validate_combat[${Target.ID}]} ) /return
	
	/call engage

	/if (${SpawnCount[NPC radius 30 zradius 30]} > 1 && ${Me.XTarget} > 1) {
		/if (${validate_cast[FALSE, disc, "${aeroar}", ${Target.ID}]}) /call core_cast2 "${aeroar}" disc ${Target.ID} FALSE
	}
	
	/if (${SpawnCount[NPC radius 40 zradius 40]} > 2 && ${Me.XTarget} > 2) {
		/if (${validate_cast[FALSE, alt, "Area Taunt", ${Target.ID}]}) /call core_cast2 "Area Taunt" alt ${Target.ID} FALSE
	}
|**
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
		|	/if (${validate_cast[FALSE, disc, "${aehitall}", ${Target.ID}]}) /call core_cast2 "${aehitall}" disc ${Target.ID} FALSE
		}
	}
**|
/return