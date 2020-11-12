|----------------------------------------------------------------------------
|- SUB: Bard
|----------------------------------------------------------------------------
|**

https://docs.google.com/document/d/1m2hDtDxAdt7qxSLByIi3JEuZ97kOW_JQQ91u9Rplb4E/edit?pli=1

**|

Sub brd_main

	/if (${powerLevel}) {
		/return
	} 

	
	/if (${Me.Song[${ChorusRegenSong}].Duration.TotalSeconds} < 6) {
		/if (${validate_cast[FALSE, pulse, "${ChorusRegenSong}", ${Me.ID}]}) {
			/call core_cast2 "${ChorusRegenSong}" pulse 0 FALSE
		}
	}

	/if (${Me.Buff[${AccelerandoSong}].Duration.TotalSeconds} < 30) {
		/if (${validate_cast[FALSE, pulse, "${AccelerandoSong}", ${Me.ID}]}) {
			/call core_cast2 "${AccelerandoSong}" pulse 0 FALSE
		}
	}

	/while (${Me.XTarget}) {
		
		/call get_target
		
		/if (!${validate_combat[${Target.ID}]} ) /continue
		/call engage

		/if (${Target.Named} || ${Target.PctHPs} > 90) {
			/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceSpell}" ${Target.ID}
		}

		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"
		
		/call brd_combat
		
		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"

		/if (${Target.Type.Equal[NPC]} && !${Target.Slowed.ID} && !${Target.Buff[${SlowSong}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${validate_cast[FALSE, pulse, "${SlowSong}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSong} \ax <<=
				/call core_cast2 "${SlowSong}" pulse ${Target.ID} FALSE
				/call check_cast_events "${SlowSong}" CAST_IMMUNE ${Target.ID}
			}
		}

		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"
		
		/if (${Me.XTarget}) {

			/if (${Me.Gem[${InsultSong1}]}) {
				/if (${validate_cast[FALSE, pulse, "${InsultSong1}", ${Target.ID}]}) {
					/call core_cast2 "${InsultSong1}" pulse ${Target.ID} FALSE
				}
			}
			/if (${validate_cast[FALSE, pulse, "${MainAriaSong}", ${Me.ID}]}) {
				/call core_cast2 "${MainAriaSong}" pulse 0 FALSE
			}
			/if (${validate_cast[FALSE, pulse, "${WarMarchSong}", ${Me.ID}]}) {
				/call core_cast2 "${WarMarchSong}" pulse 0 FALSE
			}
		}

		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"

		/if (${Me.XTarget}) {
			/if (${Me.Gem[${InsultSong2}]}) {
				/if (${validate_cast[FALSE, pulse, "${InsultSong2}", ${Target.ID}]}) {
					/call core_cast2 "${InsultSong2}" pulse ${Target.ID} FALSE
				}
			}
			/if (${Me.Gem[${SufferingSong}]}) {
				/if (${validate_cast[FALSE, pulse, "${SufferingSong}", ${Me.ID}]}) {
					/call core_cast2 "${SufferingSong}" pulse 0 FALSE
				}
			}
			/if (${validate_cast[FALSE, pulse, "${ArcaneSong}", ${Me.ID}]}) {
				/call core_cast2 "${ArcaneSong}" pulse 0 FALSE
			}
		}

		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"

		/if (${Me.XTarget}) {
			/if (${Me.Gem[${InsultSong1}]}) {
				/if (${validate_cast[FALSE, pulse, "${InsultSong1}", ${Target.ID}]}) {
					/call core_cast2 "${InsultSong1}" pulse ${Target.ID} FALSE
				}
			}
			/if (${validate_cast[FALSE, pulse, "${StormBladeSong}", ${Me.ID}]}) {
				/call core_cast2 "${StormBladeSong}" pulse 0 FALSE
			}
			/if (${validate_cast[FALSE, pulse, "${MainAriaSong}", ${Me.ID}]}) {
				/call core_cast2 "${MainAriaSong}" pulse 0 FALSE
			}
		}

		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"

		/if (${Me.XTarget}) {
			/if (${Me.Gem[${InsultSong2}]}) {
				/if (${validate_cast[FALSE, pulse, "${InsultSong2}", ${Target.ID}]}) {
					/call core_cast2 "${InsultSong2}" pulse ${Target.ID} FALSE
				}
			}
			/if (${validate_cast[FALSE, pulse, "${WarMarchSong}", ${Me.ID}]}) {
				/call core_cast2 "${WarMarchSong}" pulse 0 FALSE
			}
			/if (${Me.Gem[${SufferingSong}]}) {
				/if (${validate_cast[FALSE, pulse, "${SufferingSong}", ${Me.ID}]}) {
					/call core_cast2 "${SufferingSong}" pulse 0 FALSE
				}
			}
		}

		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSong}" "${MezSong}"

		/if (${Me.XTarget}) {
			/if (${Me.Gem[${InsultSong1}]}) {
				/if (${validate_cast[FALSE, pulse, "${InsultSong1}", ${Target.ID}]}) {
					/call core_cast2 "${InsultSong1}" pulse ${Target.ID} FALSE
				}
			}
			/if (${validate_cast[FALSE, pulse, "${ArcaneSong}", ${Me.ID}]}) {
				/call core_cast2 "${ArcaneSong}" pulse 0 FALSE
			}
			/if (${validate_cast[FALSE, pulse, "${StormBladeSong}", ${Me.ID}]}) {
				/call core_cast2 "${StormBladeSong}" pulse 0 FALSE
			}
		}
		/call move_to_camp
	}

|	/if ((${Me.XTarget[1].ID} || ${KillTargetID}) && ${Target.Distance}<${assistRange} && (!${Target.Mezzed.ID} || ${AllowMezBreak})) /call AANDisc
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
	
	/if (${validate_cast[FALSE, alt, "Fierce Eye", ${Me.ID}]}) {
		/call core_cast2 "Fierce Eye" alt 0 FALSE
	}

	/if (${Me.XTarget}>=${BurnMobCount} || ${Target.Named}) {

		/if (${Target.Named}) {
			
			/if (${validate_cast[FALSE, alt, "Boastful Bellow", ${Target.ID}]}) {
				/call core_cast2 "Boastful Bellow" alt ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, alt, "Funeral Dirge", ${Target.ID}]}) {
				/call core_cast2 "Funeral Dirge" alt ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, alt, "Lyrical Prankster", ${Target.ID}]}) {
				/call core_cast2 "Lyrical Prankster" alt ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, alt, "Cacophony", ${Target.ID}]}) {
				/call core_cast2 "Cacophony" alt ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, alt, "Bladed Song", ${Target.ID}]}) {
				/call core_cast2 "Bladed Song" alt ${Target.ID} FALSE
			}
		}

		/if (!${Me.Buff[Dichotomic Fury]} || !${Me.Buff[Ruaabri's Fury]}) {
			/if (${validate_cast[FALSE, alt, "Quick Time", ${Me.ID}]}) {
				/call core_cast2 "Quick Time" alt 0 FALSE
			}
		}

		/if (${validate_cast[FALSE, alt, "Spire of the Minstrels", ${Me.ID}]}) {
			/call core_cast2 "Spire of the Minstrels" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, disc, "Thousand Blades", ${Me.ID}]}) {
			/call core_cast2 "Thousand Blades" disc 0 FALSE
		}

		/if (${validate_cast[FALSE, alt, "Dance of Blades", ${Me.ID}]}) {
			/call core_cast2 "Dance of Blades" alt 0 FALSE
		}
		
		/if (${validate_cast[FALSE, alt, "Frenzied Kicks", ${Me.ID}]}) {
			/call core_cast2 "Frenzied Kicks" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, alt, "Flurry of Notes", ${Me.ID}]}) {
			/call core_cast2 "Flurry of Notes" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, alt, "Song of Stone", ${Target.ID}]}) {
			/call core_cast2 "Song of Stone" alt ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, item, "${ChestItemName}", ${Me.ID}]}) {
			/call pulse_stop itemcaster FALSE
			/call core_cast2 "${ChestItemName}" item 0 FALSE
		}

		/if (${validate_cast[FALSE, item, "Blade of Vesagran", ${Me.ID}]}) {
			/call pulse_stop itemcaster FALSE
			/call core_cast2 "Blade of Vesagran" item 0 FALSE
		}

		
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