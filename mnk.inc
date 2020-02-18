
Sub mnk_main
	
	/while (${Me.XTarget}) {
		/call move_to_camp
		/call get_target
		/call engage
		/call Defense
		/call CombatdpsDiscs
		/call Defense
		/call CombatdpsItems
		/call CombatdpsMash
		/call Defense
		/call DoNamed
	}

	/call mnk_self_buffs

/return

sub mnk_combat_buffs

/return

sub mnk_get_aggro
	/call CombatdpsMash
	/delay 1s
/return

sub mnk_self_buffs

	/if (!${Me.Buff[Levitation].ID}) {
		|/target id ${Me.ID}
		|/delay 5
		|/useitem "Pegasus Feather Cloak"
		/target id ${Me.ID}
		/delay 8
		/useitem "Pegasus Feather Cloak"
		/delay 8
		/delay 30s !${Me.Casting.ID}
	}

	/if (!${Me.Buff[Spinecoat].ID}) {
		/target id ${Me.ID}
		/delay 8
		/useitem "Violet Conch of the Tempest"
		/delay 8
		/delay 30s !${Me.Casting.ID}
	}

	/if (!${Me.Buff[Twitching Speed].ID}) {
		/target id ${Me.ID}
		/delay 8
		/useitem "Lizardscale Plated Girdle"
		/delay 8
		/delay 30s !${Me.Casting.ID}
	}

/return
|----------------------------------------------------------------------------
|- SUB: Defense
|----------------------------------------------------------------------------
Sub Defense
	/if (${check_for_named[FALSE]} || ${Me.XTarget} > 2) {
		
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${Spell[${EarthForce}].ID} && ${Me.ActiveDisc.ID} != ${Spell[${Heel}].ID} && ${Me.ActiveDisc.ID} != ${Spell[${Palm}].ID} && ${Me.ActiveDisc.ID} != ${Spell[${Speed}].ID}) {
				/stopdisc
			}
		}

		/if (${validate_cast[FALSE, disc, ${EarthForce}, ${Me.ID}]}) /call core_cast2 ${EarthForce} disc 0 FALSE
		
		/if (${Me.PctHPs} < 50) {
			/if (${validate_cast[FALSE, disc, ${RejectDeath}, ${Me.ID}]}) /call core_cast2 ${RejectDeath} disc 0 FALSE
		}
	
	}
	
	/if (${Me.AbilityReady[Mend]} && ${Me.PctHPs} < 50) {
		/doability Mend
		/delay 1
	}

	/if (${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) {
		/if (${validate_cast[FALSE, alt, "Purify Body", ${Me.ID}]}) /call core_cast2 "Purify Body" alt 0 FALSE
	}

	/if (${FindItem[Diplomatic Papers].Timer.TotalSeconds}==0 && ${Target.PctHPs}>10 && !${Me.Casting.ID} && !${Me.Moving} && ${Me.PctHPs} < 55) { 
		/useitem "Diplomatic Papers"
		/delay 5
	}
	/if (${FindItem[Overflowing Urn of Life].Timer.TotalSeconds}==0 && !${Me.Casting.ID} && !${Me.Moving} && ${Me.PctHPs} < 70) { 
		/useitem "Overflowing Urn of Life"
		/delay 5
	}

	/if (${check_for_named[FALSE]} || ${Me.XTarget} > 2) {
		/if (${FindItem[Blood Drinker's Coating].Timer.TotalSeconds}==0 && ${Target.PctHPs}>10 && !${Me.Casting.ID} && !${Me.Moving} && ${Me.PctHPs} < 60) { 
			/useitem "Blood Drinker's Coating"
			/delay 5
		}
	}


/return
|----------------------------------------------------------------------------
|- SUB: Combatdps Discs
|---------------------------------------------------------------------------- 
Sub CombatdpsDiscs
	/if (${Me.AltAbilityReady[Vehement Rage]} && ${Target.PctHPs}>10 && !${Me.Song[Infusion of Thunder].ID}) {
		/alt act 800
		/delay 2
	}
	/if (${Me.AltAbilityReady[Five Point Palm]} && !${Target.Buff[Sarnak Finesse].ID} && ${Target.PctHPs}>50 && ${Target.PctHPs}<95) {
		/if (!${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${Iron}]}) {
			
			/if (${validate_cast[FALSE, alt, "Swift Tails' Chant", ${Me.ID}]}) /call core_cast2 "Swift Tails' Chant" alt 0 FALSE
			
			/Disc ${Iron}
			/delay 5
			/doability "${DichoSpell}"
			/delay 8
			/Disc ${Crane}
			/delay 6
			/alt act 1012
		} else /if (!${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${Palm}]} && ${Me.AltAbilityReady[Five Point Palm]}) {
			
			/if (${validate_cast[FALSE, alt, "Focused Destructive Force", ${Me.ID}]}) /call core_cast2 "Focused Destructive Force" alt 0 FALSE
			
			/if (${Me.CombatAbilityReady[${Poise}]}) {
				/Disc ${Poise}
				/delay 3
			}
			
			/if (${validate_cast[FALSE, alt, "Swift Tails' Chant", ${Me.ID}]}) /call core_cast2 "Swift Tails' Chant" alt 0 FALSE
			
			/Disc ${Palm}
			/delay 5
			/doability "${DichoSpell}"
			/delay 8
			/Disc ${Crane}
			/delay 6
			/alt act 1012
		} else {
			/doability "${DichoSpell}"
			/delay 8
			/Disc ${Crane}
			/delay 6
			/alt act 1012
		}
	}
	/if (${Me.CombatAbilityReady[${Storm}]} && !${Me.ActiveDisc.ID} && ${Target.PctHPs}>5 && !${check_for_named[FALSE]}) {
		/Disc ${Storm}
		/delay 2
	}
/return
|----------------------------------------------------------------------------
|- SUB: Combatdps Items
|---------------------------------------------------------------------------- 
Sub CombatdpsItems
	/if (${FindItem[Transcendent's Phlogiston Tunic].Timer.TotalSeconds}==0 && ${Target.PctHPs}<98 && ${Target.PctHPs}>5 && !${Me.Casting.ID} && !${Me.Moving}) {
		/useitem "Transcendent's Phlogiston Tunic"
		/delay 5	
	}
	/if (${FindItem[Transcended Fistwraps of Immortality].Timer.TotalSeconds}==0 && ${Target.PctHPs}>10 && !${Me.Casting.ID} && !${Me.Moving} && !${Me.ActiveDisc.ID}) { 
		/useitem "Transcended Fistwraps of Immortality"
		/delay 5
	}
	/if (${FindItem[Miniature Horn of Unity].Timer.TotalSeconds}==0 && ${Target.PctHPs}>10 && !${Me.Casting.ID} && !${Me.Moving} && !${Me.ActiveDisc.ID}) { 
		/useitem "Miniature Horn of Unity"
		/delay 5
	}

/return
|----------------------------------------------------------------------------
|- SUB: Combatdps Mash
|---------------------------------------------------------------------------- 
Sub CombatdpsMash

	/if (${Me.AltAbilityReady[Zan Fi's Whistle]} && ${Target.PctHPs}>1) {
		/alt act 7001
		/delay 3
	}	
	/if (${Me.AltAbilityReady[Two-Finger Wasp Touch]} && (${Target.PctHPs}>50 || ${Target.Named} || ${Target.Level}>(${Me.Level}+3))) {
		/alt act 1235
		/delay 3
	}	
	|**
	/if (${Me.CombatAbilityReady[${Drunken}]} && ${Me.PctEndurance}>=20 && ${Target.PctHPs}>10) {
		/Disc ${Drunken}
		/delay 3
	}
	**|
	/if (${Me.CombatAbilityReady[${Curse}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>5) {
		/Disc ${Curse}
		/delay 3
	}
	/if (${Me.CombatAbilityReady[${Synergy}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${Synergy}
		/delay 3
	}	
	/if (${Me.CombatAbilityReady[${Fang}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${Fang}
		/delay 3
	}
	/if (${Me.CombatAbilityReady[${Fists}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${Fists}
		/delay 3
	}
	/if (${Me.CombatAbilityReady[${Precision}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${Precision}
		/delay 3
	}
	/if (${Me.CombatAbilityReady[${Shuriken}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${Shuriken}
		/delay 3
	}
	/if (${Me.AbilityReady[Intimidation]}) {
		/doability Intimidation
		/delay 3
	}
	/if (${Me.CombatAbilityReady[${Synergy}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${Synergy}
		/delay 3
	}	
 /return
|----------------------------------------------------------------------------
|- SUB: DoNamed
|---------------------------------------------------------------------------- 
Sub DoNamed

	|/if (${validate_cast[FALSE, alt, "Silent Strikes", ${Me.ID}]}) /call core_cast2 "Silent Strikes" alt 0 FALSE

	/if (${check_for_named[FALSE]}) {

		/if (${validate_cast[FALSE, alt, "Swift Tails' Chant", ${Me.ID}]}) /call core_cast2 "Swift Tails' Chant" alt 0 FALSE

		/if (${validate_cast[FALSE, disc, "${Drunken}", ${Me.ID}]}) /call core_cast2 "${Drunken}" disc 0 FALSE

		/if (${Me.ActiveDisc.ID} != ${Spell[${EarthForce}].ID} && ${Me.ActiveDisc.ID} != ${Spell[${Heel}].ID} && ${Me.ActiveDisc.ID} != ${Spell[${Palm}].ID} && ${Me.ActiveDisc.ID} != ${Spell[${Speed}].ID}) {
			/stopdisc
		}

		/if (${validate_cast[FALSE, alt, "Swift Tails' Chant", ${Me.ID}]}) /call core_cast2 "Swift Tails' Chant" alt 0 FALSE

		/if (${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID}) {
		
			/if (${validate_cast[FALSE, alt, "Infusion of Thunder", ${Target.ID}]}) /call core_cast2 "Infusion of Thunder" alt ${Target.ID} FALSE

			/if (${validate_cast[FALSE, alt, "Spire of the Sensei", ${Me.ID}]}) /call core_cast2 "Spire of the Sensei" alt 0 FALSE
		
			/if (${validate_cast[FALSE, alt, "${DichoSpell}", ${Me.ID}]}) /call core_cast2 "${DichoSpell}" alt 0 FALSE

			/if (${Me.CombatAbilityReady[${Crane}]}) {
				/Disc ${Crane}
				/delay 6
			}
			/if (${Me.AltAbilityReady[Five Point Palm]}) {
				/alt act 1012
				/delay 5
			}
			/delay 2
			/Disc ${Heel}
			/delay 5
		} else /if (!${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID}) {

			/if (${validate_cast[FALSE, alt, "Focused Destructive Force", ${Me.ID}]}) /call core_cast2 "Focused Destructive Force" alt 0 FALSE
			
			/if (${Me.CombatAbilityReady[${Poise}]}) {
				/Disc ${Poise}
				/delay 3
			}
			/if (${Me.CombatAbilityReady[${DichoSpell}]}) {
				/doability "${DichoSpell}"
				/delay 8
			}
			/if (${Me.CombatAbilityReady[${Crane}]}) {
				/Disc ${Crane}
				/delay 2
			}

			/if (${validate_cast[FALSE, alt, "Five Point Palm", ${Target.ID}]}) /call core_cast2 "Five Point Palm" alt ${Target.ID} FALSE

			/Disc ${Palm}
			/delay 5
		} else /if (!${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID}) {
			
			/if (${validate_cast[FALSE, alt, "Infusion of Thunder", ${Me.ID}]}) /call core_cast2 "Infusion of Thunder" alt ${Target.ID} FALSE

			/if (${validate_cast[FALSE, alt, "Spire of the Sensei", ${Me.ID}]}) /call core_cast2 "Spire of the Sensei" alt 0 FALSE

			
			/if (${validate_cast[FALSE, alt, "Ton Po's Stance", ${Me.ID}]}) /call core_cast2 "Ton Po's Stance" alt 0 FALSE

			/if (${Me.CombatAbilityReady[${DichoSpell}]}) {
				/doability "${DichoSpell}"
				/delay 8
			}
			/if (${Me.CombatAbilityReady[${Crane}]}) {
				/Disc ${Crane}
				/delay 2
			}

			/if (${validate_cast[FALSE, alt, "Five Point Palm", ${Target.ID}]}) /call core_cast2 "Five Point Palm" alt ${Target.ID} FALSE

			/Disc ${Speed}
			/delay 5
		} else /if (!${Me.ActiveDisc.ID}) {

			/if (${validate_cast[FALSE, alt, "Focused Destructive Force", ${Me.ID}]}) /call core_cast2 "Focused Destructive Force" alt 0 FALSE

			/if (${Me.CombatAbilityReady[${Poise}]}) {
				/Disc ${Poise}
				/delay 3
			}
			/if (${validate_cast[FALSE, alt, "Infusion of Thunder", ${Me.ID}]}) /call core_cast2 "Infusion of Thunder" alt 0 FALSE

			/if (${validate_cast[FALSE, alt, "Spire of the Sensei", ${Me.ID}]}) /call core_cast2 "Spire of the Sensei" alt 0 FALSE
			/Disc ${Storm}
			/delay 5
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: DowntimeDiscs
|---------------------------------------------------------------------------- 
Sub DowntimeDiscs

	/if (${Me.PctEndurance}<15 && ${Me.Endurance}>313 && ${Me.CombatAbilityReady[${endregen}]} && !${Me.CombatState.Equal[combat]} && !${Me.Invis}) {
		/disc ${endregen}
		/delay 5
	}
	/if (!${Spell[${Me.Aura[1]}].ID} && !${Me.Moving} && !${Me.Invis} && ${Me.State.NotEqual[FEIGN]} && ${Me.CombatAbility[${Spell[${mnkaura}].RankName}]} && ${Me.PctEndurance}>10) {
		/disc ${mnkaura}
		/delay 8s
	}
/return
