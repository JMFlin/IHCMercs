
Sub mnk_main
	
	/while (${Me.XTarget}) {

		/call get_target
		/call engage
		/call Defense
		/call CombatdpsDiscs
		/call CombatdpsItems
		/call CombatdpsMash
		/call DoNamed
		
	}

	/call mnk_self_buffs

/return

sub mnk_combat_buffs

/return

sub mnk_get_aggro

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
	/if (!${Me.AbilityReady[Mend]} && ${Me.CombatAbilityReady[${EarthForce}]} && ${Me.PctHPs}<45) {
		/Disc ${EarthForce}
		/delay 1
	} else /if (!${Me.AbilityReady[Mend]} && !${Me.CombatAbilityReady[${EarthForce}]} && ${Me.CombatAbilityReady[${RejectDeath}]} && ${Me.PctHPs}<45) {
		/Disc ${RejectDeath}
		/delay 1
	} else /if (${Me.AbilityReady[Mend]} && ${Me.PctHPs}<50) {
		/doability Mend
		/delay 1
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
		/if (!${Me.ActiveDisc.ID} && !${Target.Named} && ${Me.CombatAbilityReady[${Iron}]}) {
			/if (${Me.AltAbilityReady[Swift Tails' Chant]} && ${Me.PctEndurance}<80) {
				/call AANow ${Me.AltAbility[Swift Tails' Chant].ID}
				/delay 2
			}
			/Disc ${Iron}
			/delay 5
			/doability "${DichoSpell}"
			/delay 8
			/Disc ${Crane}
			/delay 6
			/alt act 1012
		} else /if (!${Me.ActiveDisc.ID} && !${Target.Named} && ${Me.CombatAbilityReady[${Palm}]} && ${Me.AltAbilityReady[Five Point Palm]}) {
			/if (${Me.AltAbilityReady[Focused Destructive Force]}) {
				/call AANow ${Me.AltAbility[Focused Destructive Force].ID}
				/delay 2
			}
			/if (${Me.CombatAbilityReady[${Poise}]}) {
				/Disc ${Poise}
				/delay 3
			}
			/if (${Me.AltAbilityReady[Swift Tails' Chant]} && ${Me.PctEndurance}<80) {
				/call AANow ${Me.AltAbility[Swift Tails' Chant].ID}
				/delay 2
			}
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
	/if (${Me.CombatAbilityReady[${Storm}]} && !${Me.ActiveDisc.ID} && ${Target.PctHPs}>5 && !${Target.Named}) {
		/Disc ${Storm}
		/delay 2
	}
	/if (${Me.CombatAbilityReady[${EarthForce}]} && !${Me.ActiveDisc.ID} && ${Target.PctHPs}>5 && !${Target.Named}) {
		/Disc ${EarthForce}
		/delay 1
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

	/if (${Me.AltAbilityReady[Silent Strikes]}) {
		/call AANow ${Me.AltAbility[Silent Strikes].ID}
		/delay 1
	}
	/if (${Me.AltAbilityReady[Swift Tails' Chant]}) {
		/call AANow ${Me.AltAbility[Swift Tails' Chant].ID}
		/delay 1
	}



	/if (${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID}) {
		/if (${Me.AltAbilityReady[Infusion of Thunder]}) {
			/call AANow ${Me.AltAbility[Infusion of Thunder].ID}
			/delay 2
		}
		/if (${Me.AltAbilityReady[Spire of the Sensei]}) {
			/call AANow ${Me.AltAbility[Spire of the Sensei].ID}
			/delay 3
		}
		/if (${Me.CombatAbilityReady[${DichoSpell}]}) {
			/doability "${DichoSpell}"
			/delay 8
		}
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
		/if (${Me.AltAbilityReady[Focused Destructive Force]}) {
			/call AANow ${Me.AltAbility[Focused Destructive Force].ID}
			/delay 2
		}
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
		/if (${Me.AltAbilityReady[Five Point Palm]}) {
			/alt act 1012
			/delay 2
		}
		/Disc ${Palm}
		/delay 5
	} else /if (!${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID}) {
		/if (${Me.AltAbilityReady[Infusion of Thunder]}) {
			/call AANow ${Me.AltAbility[Infusion of Thunder].ID}
			/delay 2
		}
		/if (${Me.AltAbilityReady[Spire of the Sensei]}) {
			/call AANow ${Me.AltAbility[Spire of the Sensei].ID}
			/delay 3
		}
		/if (${Me.AltAbilityReady[Ton Po's Stance]}) {
			/call AANow ${Me.AltAbility[Ton Po's Stance].ID}
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
		/if (${Me.AltAbilityReady[Five Point Palm]}) {
			/alt act 1012
			/delay 2
		}
		/Disc ${Speed}
		/delay 5
	} else /if (!${Me.ActiveDisc.ID}) {
		/if (${Me.AltAbilityReady[Focused Destructive Force]}) {
			/call AANow ${Me.AltAbility[Focused Destructive Force].ID}
			/delay 2
		}
		/if (${Me.CombatAbilityReady[${Poise}]}) {
			/Disc ${Poise}
			/delay 3
		}
		/if (${Me.AltAbilityReady[Infusion of Thunder]}) {
			/call AANow ${Me.AltAbility[Infusion of Thunder].ID}
			/delay 2
		}
		/if (${Me.AltAbilityReady[Spire of the Sensei]}) {
			/call AANow ${Me.AltAbility[Spire of the Sensei].ID}
			/delay 3
		}
		/Disc ${Storm}
		/delay 5
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
