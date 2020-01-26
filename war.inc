|----------------------------------------------------------------------------
|- SUB: warrior 
|---------------------------------------------------------------------------- 
Sub war_main

	/call engage
	/call war_get_aggro
	/call check_add_aggro
	/call war_combat_buffs
	/call war_disc
	/call war_aoe_aggro

|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID} || ${Me.Buff[Drachnid Entangle].ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure
	/doevents
/return
|----------------------------------------------------------------------------
|- SUB: combat_buffs 
|---------------------------------------------------------------------------- 
Sub war_combat_buffs
	
	/if (!${validate_combat_buffs[FALSE]}) /return

	/if (${Me.PctEndurance}>20 && ${Me.CombatAbilityReady[${groupac}]} && !${Me.Song[Field].ID}) {
		/call DiscNow "${groupac}"
	}
	/if (${Me.PctEndurance}>20 && ${Me.CombatAbilityReady[${groupdodge}]} && !${Me.Song[Commanding Voice].ID}) {
		/call DiscNow "${groupdodge}"
	}
	/if (${Me.CombatAbilityReady[${defenseac}]} && !${Me.ActiveDisc.ID} && ${Me.XTarget[1].ID}) {
		/disc ${defenseac}
		/delay 5
	}

	|--DoAutoPDH: https://forums.daybreakgames.com/eq/index.php?threads/tucos-setup-critique-welcome.240258/
	|-- https://forums.daybreakgames.com/eq/index.php?threads/returning-warrior.253870/
	|-- https://pb.gamerlaunch.com/forums/viewtopic.php?t=11328956&gid=518180
	|-- https://forums.daybreakgames.com/eq/index.php?threads/warrior-ability-stacking.230888/
	|-- Front Mitigation: Pain Doesn't Hurt > Brace for Impact > Diplo Papers
	|-- Rear Mitigation: Dichotomic > RoS BP > Warrior's Bastion
	|-- Front Mitigation: Anguish BP > Warlord's Bravery

	/if (!${Me.Buff[Diplomatic Immunity].ID} && !${Me.Song[Pain Doesn't Hurt].ID} && ${Me.CombatAbilityReady[${Spell[Pain Doesn't Hurt].RankName}]}) {
		/call DiscNow "${absorball}"
	} else /if (!${Me.Song[Pain Doesn't Hurt].ID} && !${FindItem[${ItemDipPapers}].TimerReady}) {
		/call ItemNow "${ItemDipPapers}"
	}
	/if (${Me.AltAbilityReady[Brace for Impact]}) {
		/call AANow ${Me.AltAbility[Brace for Impact].ID}
	}
	/if (${Target.Type.Equal[Corpse]} || !${Target.ID}) /return
	
	
	/if (!${Me.Buff[${warbulwark}].ID} && !${Me.Buff[Roaring Shield].ID} && ${Me.CombatAbilityReady[${bmdisc}]}) {
		/docommand /disc 57800
	} else /if (!${FindItem[${ChestItemName}].TimerReady} && !${Me.Buff[Dichotomic Shield].ID} && !${Me.Buff[${warbulwark}].ID}) {
		/call ItemNow "${ChestItemName}"
	} else /if (!${Me.Buff[Dichotomic Shield].ID} && !${Me.Buff[${warbulwark}].ID} && !${Me.Buff[Roaring Shield].ID}) {
		/call DiscNow "${warbulwark}"
	} 
	
	/if (!${FindItem[${ItemOoWBP}].TimerReady} && !${Me.Buff[Warlord's Bravery].ID} && !${Me.Buff[Fundament: Third Spire of the Warlord].ID}) {
		/call ItemNow "${ItemOoWBP}"
	} else /if (!${Me.Buff[Warlord's Bravery].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Fundament: Third Spire of the Warlord].ID} && ${Me.AltAbilityReady[Warlord's Bravery]}) {
		/call AANow ${Me.AltAbility[Warlord's Bravery].ID}
	}

	/if (!${Me.Buff[Warlord's Bravery].ID} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Spire of the Warlord].ID} && ${Me.AltAbilityReady[Spire of the Warlord]}) {
		/call AANow ${Me.AltAbility[Spire of the Warlord].ID}
	}

	|-- Defensive buffs based on health
	/if (${Me.AltAbilityReady[Blade Guardian]} && ${Me.PctHPs}<45 && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Blade Guardian].ID}
	}
	/if (${Me.PctHPs}<25  && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Warlord's Resurgence].ID}
	} 
	/if (${Me.AltAbilityReady[Imperator's Charge]} && (${Me.PctHPs} < 45 || ${Target.Named}) && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Imperator's Charge].ID}
		/if (${Me.AltAbilityReady[Resplendent Glory]}) {
			/call AANow ${Me.AltAbility[Resplendent Glory].ID}
		}
	} else /if (${Me.PctHPs} < 45 || ${Target.Named}) {
		/if (${Me.AltAbilityReady[Resplendent Glory]}) {
			/call AANow ${Me.AltAbility[Resplendent Glory].ID}
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: DoDisc 
|---------------------------------------------------------------------------- 
Sub war_disc

	/if (!${validate_combat[${Target.ID}]} ) /return

	/if ((${Me.XTarget} > 2 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) &&  ${Me.CombatAbilityReady[${missall}]}) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
				/stopdisc
				/delay 5 !${Me.ActiveDisc.ID}
				/disc ${missall}
			}
		} else {
			/disc ${missall}
		}
	}

	/if (${Me.PctHPs} < 55 && ${Me.ActiveDisc.ID} != ${FortitudeDiscID}) {
		/disc ${parryall}
	}

	/if ((${Me.XTarget} > 2 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) && ${Me.CombatAbilityReady[${meleemit}]}) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${FortitudeDiscID} && ${Me.ActiveDisc.ID} != ${CulminatingStandID}) {
				/stopdisc
				/delay 5 !${Me.ActiveDisc.ID}
				/disc ${meleemit}
			}
		} else {
			/disc ${meleemit}
		}
	} 

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID}) /return
	
	/if (${Target.Named} || ${Target.Level} > (${Me.Level}+3)) {

		/if (${Me.AltAbilityReady[Mark of the Mage Hunter]} && ${Target.PctHPs}>1) {
			/call AANow ${Me.AltAbility[Mark of the Mage Hunter].ID}
		}
		/if (${Me.CombatAbilityReady[${attention}]} && ${Target.PctHPs} > 1) {
			/call DiscNow "${attention}"
		}
	}

	/if ((${Me.XTarget} > 3 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30)) {
		/if (${Me.AltAbilityReady[Warlord's Tenacity]} && ${Target.PctHPs} > 1) {
			/call AANow ${Me.AltAbility[Warlord's Tenacity].ID}
		} 
		/if (${Me.AltAbilityReady[Wars Sheol's Heroic Blade]} && ${Target.PctHPs} > 1) {
			/call AANow ${Me.AltAbility[Wars Sheol's Heroic Blade].ID}
		}
		/if (${Me.AltAbilityReady[Rage of Rallos Zek]} && ${Target.PctHPs} > 1) {
			/call AANow ${Me.AltAbility[Rage of Rallos Zek].ID}
		}
	}

	/if (${Target.Named} && ${Me.CombatAbilityReady[${throat}]} && ${Target.PctHPs} > 1) {
		/call DiscNow "${throat}"
	}
/return
|----------------------------------------------------------------------------
|- SUB: get_aggro
|---------------------------------------------------------------------------- 
Sub war_get_aggro

	/if (!${validate_combat[${Target.ID}]} ) /return

	/if (${Me.AltAbilityReady[Battle Leap]} && !${Me.Song[Battle Leap].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${Target.MaxRangeTo}>=${Target.Distance}) {
		/call AANow ${Me.AltAbility[Battle Leap].ID}
		/squelch /attack on
	}

	/call use_skill_melee FALSE ${Target.ID}

	/if (${Me.AltAbilityReady[Warlord's Fury]} && ${Me.SecondaryPctAggro}>=60) {
		/call AANow ${Me.AltAbility[Warlord's Fury].ID}
	}

	/if (${Me.PctEndurance}>10 && ${Me.CombatAbilityReady[${shout}]} && ${Target.PctHPs}>1) {
		/call DiscNow "${shout}"
	}
	/if (${Me.PctEndurance}>5 && ${Me.CombatAbilityReady[${insult}]} && ${Target.PctHPs}>1) {
		/call DiscNow "${insult}"
	}
	/if (${Me.PctEndurance}>10 && ${Me.CombatAbilityReady[${roar}]} && ${Target.PctHPs}>1 && ${Me.SecondaryPctAggro}>=80) {
		/call DiscNow "${roar}"
	}

	/if (${Me.AltAbilityReady[Rage of the Forsaken]} && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Rage of the Forsaken].ID}
	}
	/if (${Me.CombatAbilityReady[${shieldhit}]} && !${Target.Buff[Sarnak Finesse].ID} && ${Me.Endurance}>500  && ${Target.PctHPs}>1) {
		/call DiscNow "${shieldhit}"
	}

	|-- Mash key base
	/if (${Me.AltAbilityReady[Knee Strike]} && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Knee Strike].ID}
	}

	/if ((${Target.Named} || ${Me.PctHPs} < 61) && ${Me.CombatAbilityReady[${knuckle}]} && ${Target.PctHPs}>1) {
		/call DiscNow ${knuckle}
	}
	/if (${Me.CombatAbilityReady[${StrikeDisc}]} && ${Target.PctHPs}>1) {
		/call DiscNow ${StrikeDisc}
	}

	/if (${Me.AltAbilityReady[Gut Punch]} && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Gut Punch].ID}
	}
	/if (${Me.AltAbilityReady[Call of Challenge]} && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Call of Challenge].ID}
	}

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	/if (${SpawnCount[NPC radius 45 zradius 20 noalert 1]}<2 && ${Me.AltAbilityReady[Rampage]} && ${Target.PctHPs}>1) {
		/call AANow ${Me.AltAbility[Rampage].ID}
	}

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID}) /return

	|-- Mash key aggro
	/if (${Me.CombatAbilityReady[${singlehealhate}]} && ${Me.SecondaryPctAggro}>10) {
		/call DiscNow "${singlehealhate}"
	}
	/if (${Me.CombatAbilityReady[${phantom}]} && ${Me.PctEndurance}>10 && ${Me.SecondaryPctAggro}>20) {
		/call DiscNow "${phantom}"
	}
	/if (${Me.AltAbilityReady[Blast of Anger]} && ${Me.SecondaryPctAggro}>60) {
		/call AANow ${Me.AltAbility[Blast of Anger].ID}
	}
	/if (${Me.AltAbilityReady[Projection of Fury]} && ${Me.SecondaryPctAggro}>30) {
		/call AANow ${Me.AltAbility[Projection of Fury].ID}
	}
	/if (${Me.AltAbilityReady[Warlord's Grasp]} && ${Me.SecondaryPctAggro}>50) {
		/call AANow ${Me.AltAbility[Warlord's Grasp].ID}
	}
	/if (${Me.AltAbilityReady[Ageless Enmity]} && ${Me.SecondaryPctAggro}>=100 && ${Target.PctHPs}<=98) {
		/call AANow ${Me.AltAbility[Ageless Enmity].ID}
	}

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	/if (${Me.CombatAbilityReady[${tongue}]} && ${Me.SecondaryPctAggro}>10) {
		/call DiscNow "${tongue}"
	}
	/if (${Me.CombatAbilityReady[${reprisal}]} && ${Me.SecondaryPctAggro}>5) {
		/call DiscNow "${reprisal}"
	}
/return
|----------------------------------------------------------------------------
|- SUB: AoEAggro   
|---------------------------------------------------------------------------- 
Sub war_aoe_aggro
	/declare x				 int local 1
	/declare numberOfSpawn 	 int local 0

	/if (!${validate_combat[${Target.ID}]} ) /return

	/if (${SpawnCount[NPC radius 30 zradius 30]} > 1 && ${Me.XTarget} > 1) {
		/if (${validate_cast[FALSE, disc, "${aeroar}", ${Target.ID}]}) /call core_cast2 "${aeroar}" disc ${Target.ID} FALSE
	}
	
	/if (${SpawnCount[NPC radius 40 zradius 40]} > 2 && ${Me.XTarget} > 2) {
		/if (${validate_cast[FALSE, alt, "Area Taunt", ${Target.ID}]}) /call core_cast2 "Area Taunt" alt ${Target.ID} FALSE
	}

	| How many mobs are there?
	/if (${SpawnCount[npc radius 50 zradius 50]} > 1 && ${Me.XTarget} > 1) {
		
		/for x 1 to ${Me.XTarget}

			| If xtarget is not mezzed, add it to count
			/if (${If[${Select[${Me.XTarget[${x}].Animation},110,26,32,71,72,111]}, 0, 1]} == 1) {
				/varcalc numberOfSpawn ${numberOfSpawn}+1
			}

		/next x

		| If no mob is yet mezzed hit them all
		/if (${numberOfSpawn} > 1) {
			/if (${validate_cast[FALSE, disc, "${aehitall}", ${Target.ID}]}) /call core_cast2 "${aehitall}" disc ${Target.ID} FALSE
		}
	}

/return