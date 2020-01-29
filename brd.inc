|----------------------------------------------------------------------------
|- SUB: brd_main
|---------------------------------------------------------------------------- 
Sub brd_main

	/if (${Me.XTarget}) {
		/call brd_pulse FALSE ${BattleMelody}
	}
	/if (!${Me.XTarget}) {
		/call brd_pulse FALSE ${RegenMelody}
	}

|	/if ((${Me.XTarget[1].ID} || ${KillTargetID}) && ${Target.Distance}<${AssistRange} && (!${Target.Mezzed.ID} || ${AllowMezBreak})) /call AANDisc
|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure
	
	/doevents
/return

|***
 *	DES: Sing "Pulse" a single song
 *	USE: /call pulse [gem##] [type] 
 *  NOTE:
 ***|
Sub brd_pulse(bool _debug, string _melody)

	/declare _song 							int local 0
	/declare _lnString               		int local ${_melody.Length}
    /declare _melodyArray[${_lnString}]  	string local

    /for _song 1 to ${_lnString}
        /varset _melodyArray[${_song}] ${_melody.Mid[${_song},1]}
    /next _song
	
	/call get_target
	/call engage
	/call mezz_xtarget "${AEMezSong}" "${MezSong}"

	/for _song 1 to ${_lnString}
		/call get_target
		/call engage
		/call mezz_xtarget "${AEMezSong}" "${MezSong}"
		/call brd_combat

		/if (${Target.Type.Equal[NPC]} && !${Target.Slowed.ID} && !${Target.Buff[${SlowSong}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${validate_cast[FALSE, pulse, "${SlowSong}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSong} \ax <<=
				/call core_cast2 "${SlowSong}" pulse ${Target.ID} FALSE
				/call check_cast_events "${SlowSong}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		/if (!${Me.XTarget} && ${_melody} == ${BattleMelody}) {
			/call pulse_stop pulse_line_start
			/return
		} else /if (${Me.XTarget} && ${_melody} == ${RegenMelody}) {
			/call pulse_stop pulse_line_start
			/return
		}
		
		|DEBUG ${Me.Gem[${_melodyArray[${_song}]}]}: ${validate_cast[FALSE, pulse, "${Me.Gem[${_melodyArray[${_song}]}]}", ${Me.ID}]}
		/if (${validate_cast[FALSE, pulse, "${Me.Gem[${_melodyArray[${_song}]}]}", ${Me.ID}]}) {
			/call core_cast2 "${Me.Gem[${_melodyArray[${_song}]}]}" pulse 0 FALSE
		}

		/if (${_melodyArray.Size} < 3) /delay 2s
		/if (${_melody} == ${RegenMelody}) /stopsong

	/next _song
	
/return TRUE
|----------------------------------------------------------------------------
|- SUB: Combatdps
|---------------------------------------------------------------------------- 
Sub brd_combat
	/if (!${validate_combat[${Target.ID}]} ) /return

	/if (${Me.XTarget}>=${BurnMobCount} || ${Target.Named}) {
		/if (${Me.CombatAbilityReady[Thousand Blades]}) {
			/disc Thousand Blades
			/delay 5
		}
		/if (${Me.AltAbilityReady[Dance of Blades]}) {
			/alt act ${Me.AltAbility[Dance of Blades].ID}
			/delay 5
		}
		/if (${Me.AltAbilityReady[Flurry of Notes]}) {
			/alt act ${Me.AltAbility[Flurry of Notes].ID}
			/delay 5
		}
		/if (${Me.AltAbilityReady[Song of Stone]}) {
			/alt act ${Me.AltAbility[Song of Stone].ID}
			/delay 5
		}
		/if (${Me.AltAbilityReady[Frenzied Kicks]}) {
			/alt act ${Me.AltAbility[Frenzied Kicks].ID}
			/delay 5
		}
		/if (${Me.AltAbilityReady[Funeral Dirge]}) {
			/alt act ${Me.AltAbility[Funeral Dirge].ID}
			/delay 5
		}
	}


	/if (${MelodyType.Equal[Caster]} && ${Me.AltAbilityReady[Fundament: Second Spire of the Minstrels]}) {
		/alt act ${Me.AltAbility[Fundament: Second Spire of the Minstrels].ID}
		/delay 5
	} else /if (${Me.AltAbilityReady[Fundament: Third Spire of the Minstrels]}) {
		/alt act ${Me.AltAbility[Fundament: Third Spire of the Minstrels].ID}
		/delay 5
	} else /if (${FindItem[${ChestItemName}].ID} && ${Me.ItemReady[${ChestItemName}]} && !${Me.Buff[Third Spire of the Minstrels].ID} && !${Me.Buff[Second Spire of the Minstrels].ID}) {
		/useitem "${ChestItemName}"
		/delay 10	
	}
	/if (${Me.AltAbilityReady[Boastful Bellow]} && !${Target.Buff[Boastful Bellow].ID} && ${Me.PctEndurance}>20 && ${Target.PctHPs}>20) {
		/alt act ${Me.AltAbility[Boastful Bellow].ID}
		/delay 5
	} else /if (${Me.AltAbilityReady[Lyrical Prankster]} && ${Me.PctEndurance}>20 && ${Target.PctHPs}>20) {
		/alt act ${Me.AltAbility[Lyrical Prankster].ID}
		/delay 5
	} else /if (${Me.AltAbilityReady[Cacophony]} && ${Me.PctEndurance}>20 && ${Target.PctHPs}>20) {
		/alt act ${Me.AltAbility[Cacophony].ID}
		/delay 5
	} else /if (${Me.AltAbilityReady[Bladed Song]} && ${Me.PctEndurance}>20 && ${Target.PctHPs}>20) {
		/alt act ${Me.AltAbility[Bladed Song].ID}
		/delay 5
	}
/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub brd_aa_and_disc
	/doevents

	/if (!${validate_combat[${Target.ID}]} ) /return

	/call use_skill_melee FALSE ${Target.ID}

	/if (${FindItem[=${Epicsword}].ID} && ${Me.ItemReady[=${Epicsword}]}) {
		/call StopTune
		/useitem "${Epicsword}"
		/delay 10
	}
	/if (${Me.AltAbilityReady[Fierce Eye]}) {
		/alt act ${Me.AltAbility[Fierce Eye].ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Tune Stuck in Your Head]}) {
		/alt act ${Me.AltAbility[Tune Stuck in Your Head].ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Quick Time]} && !${Me.Song[Ruaabri's Fury].ID}) {
		/alt act ${Me.AltAbility[Quick Time].ID}
		/delay 5
	}
/return
|***
 *	DES: quit singing.
 *	USE: 
 *  NOTE: 
 ***|
sub pulse_stop(string _marker, bool _debug)
	/if ((${Me.Casting.ID} || ${Me.BardSongPlaying})) {
		/varset castReturn CAST_NOTREADY
		/stopsong
		/stopcast
		/delay 10 !${Me.Casting.ID}
	}	
/return TRUE