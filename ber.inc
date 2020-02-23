
|**
Main burn- 
Disconcerting - 
Secondary Burn -
Disconcerting + Glyph - 
Third Burn - 
Disconcerting (Vehement Rage will be back up at some point while Disconcerting is running can pop it again now) - 
Fourth Burn- Disconcerting- 
Back to main burn minus Furious/Focused and repeat (when you get back to secondary burn cleaving acrimony will not be up either just use reckless abandon anyway at the point)
**|


|**
Main burn:

Brutal Discipline
Savage Spirit
Juggernaut Surge
Blood Pact
Blinding Fury
Silent Strikes
Second Spire
Desperation (Added this this expansion due to the extra 1% chance of a second hit with 2hder also it lasts 10 minutes)
Furious or Focused Rampage
Untamed Rage (If your not grouped with a bard)
Epic 2.0 
EoK Chest click

Secondary Burn:

Reckless Abandon
Cleaving Acrimony
Vehement Rage (Use this here just for the added Min hit % bonus)

Third Burn:

Frenzied Resolve

Fourth Burn:

Avenging Flurry Discipline

**|

|----------------------------------------------------------------------------
|- SUB: ber_main
|---------------------------------------------------------------------------- 
Sub ber_main
	
	
	/if (!${Me.XTarget}) /call make_axes "${JoltAxeName}" "${JoltAxeComponent}"
	/if (!${Me.XTarget}) /call make_axes "${SnareAxeName}" "${SnareAxeComponent}"
	/if (!${Me.XTarget}) /call make_axes "${StunAxeName}" "${StunAxeComponent}"
	/if (!${Me.XTarget}) /call make_axes "${DichoAxeName}" "${DichoAxeComponent}"

	/while (${Me.XTarget}) {
		/call get_target

		/if (${Me.PctHPs} > 89) {
			/if (${validate_cast[FALSE, disc, "${RitualScarification}", ${Me.ID}]}) /call core_cast2 "${RitualScarification}" disc 0 FALSE
		}

		/if (!${Me.Buff[${FrenzyBoostBuff}].ID}) {
			/if (${validate_cast[FALSE, disc, "${FrenzyBoost}", ${Me.ID}]}) /call core_cast2 "${FrenzyBoost}" disc 0 FALSE
		}

		/if (${validate_cast[FALSE, disc, ${PreCombatDisc}, ${Target.ID}]}) /call core_cast2 ${PreCombatDisc} disc ${Target.ID} FALSE

		/if (!${validate_combat[${Target.ID}]}) /continue
		/call engage

		/if (!${Me.Combat}) {
			/if (${validate_cast[FALSE, disc, ${PreCombatDisc}, ${Target.ID}]}) /call core_cast2 ${PreCombatDisc} disc ${Target.ID} FALSE
		}
		
		/call use_skill_melee FALSE ${Target.ID}

		/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceDisc}" ${Target.ID}

		/call use_skill_melee FALSE ${Target.ID}

		|**
		/if (!${Me.ActiveDisc.ID}) {
				/if (${burnRotation} == 1) {
					
					/if (${validate_cast[FALSE, disc, "${BrutalDisc}", ${Me.ID}]}) {
						/if (${validate_cast[FALSE, item, "Vengeful Taelosian Blood Axe", ${Me.ID}]}) /call core_cast2 "Vengeful Taelosian Blood Axe" item 0 FALSE
						/if (${validate_cast[FALSE, alt, "Savage Spirit", ${Me.ID}]}) /call core_cast2 "Savage Spirit" alt 0 FALSE
						/if (${validate_cast[FALSE, alt, "Juggernaut Surge", ${Me.ID}]}) /call core_cast2 "Juggernaut Surge" alt 0 FALSE
						
						/if (!${Me.Buff[Blood Pact].ID}) {
							/if (${validate_cast[FALSE, alt, "Blood Pact", ${Me.ID}]}) /call core_cast2 "Blood Pact" alt 0 FALSE
						}

						/if (${validate_cast[FALSE, alt, "Blinding Fury", ${Me.ID}]}) /call core_cast2 "Blinding Fury" alt 0 FALSE
						/if (${validate_cast[FALSE, alt, "Silent Strikes", ${Me.ID}]}) /call core_cast2 "Silent Strikes" alt 0 FALSE
						/if (${validate_cast[FALSE, alt, "Spire of the Juggernaut", ${Me.ID}]}) /call core_cast2 "Spire of the Juggernaut" alt 0 FALSE
						/if (${validate_cast[FALSE, alt, "Desperation", ${Me.ID}]}) /call core_cast2 "Desperation" alt 0 FALSE
						/if (${validate_cast[FALSE, alt, "Focused Furious Rampage", ${Me.ID}]}) /call core_cast2 "Focused Furious Rampage" alt 0 FALSE
						/call core_cast2 "${BrutalDisc}" disc 0 FALSE
						| Or if Quicktime drops I know to cast Untamed Rage on my zerker: https://forums.daybreakgames.com/eq/index.php?threads/tucos-setup-critique-welcome.240258/page-6#post-3627587
						/if (!${Me.Song[Quick Time V].ID}) {
							/if (${validate_cast[FALSE, alt, "Untamed Rage", ${Me.ID}]}) /call core_cast2 "Untamed Rage" alt 0 FALSE 
						}
					}
					/varset inBetween 1
				}
			}
		**|

		|/echo ${validate_cast[FALSE, alt, "Savage Spirit", ${Me.ID}]}
		|/echo ${validate_cast[FALSE, alt, "Desperation", ${Me.ID}]}

		/if (${check_for_named[FALSE]}) {
			
			/if (${validate_cast[FALSE, item, "Vengeful Taelosian Blood Axe", ${Me.ID}]}) /call core_cast2 "Vengeful Taelosian Blood Axe" item 0 FALSE
			/if (${validate_cast[FALSE, alt, "Savage Spirit", ${Me.ID}]}) /call core_cast2 "Savage Spirit" alt 0 FALSE
			/if (${validate_cast[FALSE, alt, "Juggernaut Surge", ${Me.ID}]}) /call core_cast2 "Juggernaut Surge" alt 0 FALSE
			
			/if (!${Me.Buff[Blood Pact].ID}) {
				/if (${validate_cast[FALSE, alt, "Blood Pact", ${Me.ID}]}) /call core_cast2 "Blood Pact" alt 0 FALSE
			}

			/if (${validate_cast[FALSE, alt, "Blinding Fury", ${Me.ID}]}) /call core_cast2 "Blinding Fury" alt 0 FALSE
			/if (${validate_cast[FALSE, alt, "Silent Strikes", ${Me.ID}]}) /call core_cast2 "Silent Strikes" alt 0 FALSE
			/if (${validate_cast[FALSE, alt, "Spire of the Juggernaut", ${Me.ID}]}) /call core_cast2 "Spire of the Juggernaut" alt 0 FALSE
			/if (${validate_cast[FALSE, alt, "Desperation", ${Me.ID}]}) /call core_cast2 "Desperation" alt 0 FALSE
			/if (${validate_cast[FALSE, alt, "Focused Furious Rampage", ${Me.ID}]}) /call core_cast2 "Focused Furious Rampage" alt 0 FALSE
			| Or if Quicktime drops I know to cast Untamed Rage on my zerker: https://forums.daybreakgames.com/eq/index.php?threads/tucos-setup-critique-welcome.240258/page-6#post-3627587
			/if (!${Me.Song[Quick Time V].ID}) {
				/if (${validate_cast[FALSE, alt, "Untamed Rage", ${Me.ID}]}) /call core_cast2 "Untamed Rage" alt 0 FALSE 
			}

			/if (${validate_cast[FALSE, disc, "${BrutalDisc}", ${Me.ID}]}) {
				/if (${Me.ActiveDisc.ID} == ${DisconDiscID}) {
					/stopdisc
				}
				/call core_cast2 "${BrutalDisc}" disc 0 FALSE	
			}
			/varset inBetween 1
		}

		/if (!${Me.ActiveDisc.ID}) {
			/if (${burnRotation} == 2) {
				/if (${validate_cast[FALSE, alt, "Reckless Abandon", ${Me.ID}]}) /call core_cast2 "Reckless Abandon" alt 0 FALSE
				/if (${validate_cast[FALSE, alt, "Vehement Rage", ${Me.ID}]}) /call core_cast2 "Vehement Rage" alt 0 FALSE
				/if (${validate_cast[FALSE, disc, "${CleavingDisc}", ${Me.ID}]}) {
					/call core_cast2 "${CleavingDisc}" disc 0 FALSE
				}
				/varset inBetween 1
			}
		}

		/if (!${Me.ActiveDisc.ID}) {
			/if (${burnRotation} == 3) {
				/if (${validate_cast[FALSE, alt, "Vehement Rage", ${Me.ID}]}) /call core_cast2 "Vehement Rage" alt 0 FALSE
				/if (${validate_cast[FALSE, disc, "${ResolveDisc}", ${Me.ID}]}) {
					/call core_cast2 "${ResolveDisc}" disc 0 FALSE
				}
				/varset inBetween 1
			}
		}

		/if (!${Me.ActiveDisc.ID}) {
			/if (${burnRotation} == 4) {
				/if (${validate_cast[FALSE, disc, "${FlurryDisc}", ${Me.ID}]}) {
					/call core_cast2 "${FlurryDisc}" disc 0 FALSE
				}
				/varset burnRotation 0
				/varset inBetween 1
			}
		}

		/if (!${Me.ActiveDisc.ID}) {
			
			/if (${inBetween} == 1) {
				/if (${Me.CombatAbility[${Spell[Disconcerting Discipline].RankName}]}) {
					/if (${validate_cast[FALSE, disc, "${DisconDisc}", ${Me.ID}]}) {
						/call core_cast2 "${DisconDisc}" disc 0 FALSE
						/varcalc burnRotation ${burnRotation} + 1
						/varset inBetween 0
					}
				} else {
					/varcalc burnRotation ${burnRotation} + 1
					/varset inBetween 0
				}
			}
		}
			
		/call use_skill_melee FALSE ${Target.ID}

		/if (!${Me.Casting.ID} && ${Me.PctEndurance}<=75 && ${Me.PctHPs}>=50 && ${Me.AltAbilityReady[Communion of Blood]} && !${Me.Song[${endregen}].ID} && !${Me.Moving} && !${Me.Invis}) {
			/alt act ${Me.AltAbility[Communion of Blood].ID}
			/delay 5
		}

		/if (!${Me.Song[Battle Leap].ID} && !${Me.Song[Battle Leap Warcry].ID} && !${Me.Song[Group Bestial Alignment].ID}) {
			/if (${validate_cast[FALSE, alt, "Battle Leap", ${Target.ID}]}) /call core_cast2 "Battle Leap" alt 0 FALSE
		}


		/if (!${Me.Song[${CryHavoc}].ID} && ${Me.ActiveDisc.ID}!=${CleavingDiscID}) {
			/if (${validate_cast[FALSE, disc, "${CryHavoc}", ${Me.ID}]}) /call core_cast2 "${CryHavoc}" disc 0 FALSE
		}

		/if (${validate_cast[FALSE, disc, "${SappingStrike}", ${Target.ID}]}) /call core_cast2 "${SappingStrike}" disc ${Target.ID} FALSE

		/if (${validate_cast[FALSE, disc, "${RageStrike}", ${Target.ID}]}) /call core_cast2 "${RageStrike}" disc ${Target.ID} FALSE

		
		/if (!${Me.Song[${SharedBuffName}].ID}) {
			/if (${validate_cast[FALSE, disc, "${SharedBuff}", ${Target.ID}]}) /call core_cast2 "${SharedBuff}" disc ${Target.ID} FALSE
		}
		
		/if (!${Me.Song[${HHEBuff}].ID} && !${Me.Song[Dichotomic Fury].ID} && !${Me.Song[Ruaabri's Fury].ID} && !${Me.Song[Quick Time].ID} && (${Me.ActiveDisc.ID}==${BrutalDiscID} || ${Me.ActiveDisc.ID}==${CleavingDiscID} || ${Me.ActiveDisc.ID}==${FlurryDiscID})) {
			/if (${validate_cast[FALSE, disc, "${HHEBuff}", ${Me.ID}]}) /call core_cast2 "${HHEBuff}" disc 0 FALSE
		}
	
		/call ber_combat
		/call move_to_camp
	|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure
		/doevents
	}
	
/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub ber_aa_and_disc

	
	
	
 /return
|----------------------------------------------------------------------------
|- SUB: Combatdps
|---------------------------------------------------------------------------- 
Sub ber_combat

	/call get_target
	/call engage

|	/doevents BerStunRotation

	/if (${Target.PctAggro} > 85) {
		/if (${validate_cast[FALSE, disc, "${JoltDisc}", ${Target.ID}]}) {
			/call core_cast2 "${JoltDisc}" disc ${Target.ID} FALSE
		}
	}

	/call use_skill_melee FALSE ${Target.ID}
	|/if (!${Target.Snared.ID} && ${Target.Fleeing} && ${FindItemCount[${SnareAxeName}]} > 0 && !${immuneSet.Contains[${Target.ID}]}) {
	|	/if (${validate_cast[FALSE, disc, "${Snare}", ${Target.ID}]}) /call core_cast2 "${Snare}" disc ${Target.ID} FALSE
	|	/call check_cast_events "${Snare}" CAST_IMMUNE ${Target.ID}
	|}

	|/if (${Me.CombatAbilityReady[${BloodDisc}]} && !${Target.Buff[${BloodDisc}].ID}) {
	|	/Disc ${BloodDisc}
	|	/delay 5
	|}
	
	/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceDisc}" ${Target.ID}

	|/if (${FindItem[${ChestItemName}].ID} && !${FindItem[${ChestCombatCast}].TimerReady}) {
	|	/useitem "${ChestItemName}"
	|	/delay 10	
	|}

	|/if (${Me.AltAbilityReady[Furious Rampage]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1 && ${Me.Combat}) {
	|	/alt act ${Me.AltAbility[Furious Rampage].ID}
	|	/delay 5
	|}
	
	/if (${SpawnCount[npc radius 40 zradius 15 targetable playerstate 4]} < 2) {
		/if (${validate_cast[FALSE, disc, "${AESlice}", ${Target.ID}]}) /call core_cast2 "${AESlice}" disc ${Target.ID} FALSE
	}
	/doevents
	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	|/if (${SpawnCount[npc radius 25 zradius 15 targetable playerstate 4]} < 2) {
	|	/if (${validate_cast[FALSE, disc, "${AEVicious}", ${Target.ID}]}) /call core_cast2 "${AEVicious}" disc ${Target.ID} FALSE
	|	/delay 5
	|}

	/if (!${Target.Buff[Sarnak Finesse].ID}) {
		/if (${validate_cast[FALSE, alt, "Braxi's Howl", ${Target.ID}]}) /call core_cast2 "Braxi's Howl" alt ${Target.ID} FALSE
		/if (${validate_cast[FALSE, disc, "${DichoDisc}", ${Target.ID}]}) /call core_cast2 "${DichoDisc}" disc ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, alt, "Binding Axe", ${Target.ID}]}) /call core_cast2 "Binding Axe" alt ${Target.ID} FALSE

	/if (${validate_cast[FALSE, disc, "${Dfrenzy}", ${Target.ID}]}) /call core_cast2 "${Dfrenzy}" disc ${Target.ID} FALSE

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	/if (${validate_cast[FALSE, disc, "${Dvolley}", ${Target.ID}]}) /call core_cast2 "${Dvolley}" disc ${Target.ID} FALSE

	|**
	/if (${stunTurn} && ${classTotal} > 1) {
		/if (${validate_cast[FALSE, disc, "${Stun}", ${Target.ID}]}) {
			
			| Cast stun
			/call core_cast2 "${Stun}" disc ${Target.ID} FALSE
			/delay 5

			| Get next in rotation
			/call get_next_in_rotation
			/varset berStunCaster ${Macro.Return}
			
			| Announce the next one
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt ******** NEXT SHOULD BE ${berStunCaster} *********

			| Tell the next one in line that it is their turn
			/squelch /dex ${berStunCaster} /varset stunTurn 1
			/squelch /dex ${berStunCaster} /varset berStunCounter ${berStunCounter}

			| Done casting for this round
			/varset stunTurn 0
		}
	} else {
		**|
	/if (${validate_cast[FALSE, disc, "${Daxethrow}", ${Target.ID}]}) /call core_cast2 "${Daxethrow}" disc ${Target.ID} FALSE
	|}

	/if (${validate_cast[FALSE, disc, "${Daxeof}", ${Target.ID}]}) /call core_cast2 "${Daxeof}" disc ${Target.ID} FALSE

	/if (${validate_cast[FALSE, disc, "${Phantom}", ${Target.ID}]}) /call core_cast2 "${Phantom}" disc ${Target.ID} FALSE

 /return
|----------------------------------------------------------------------------
|- SUB: DowntimeDiscs
|---------------------------------------------------------------------------- 
Sub make_axes(string AxeName, string AxeComponents)
	/delay 1s
	/if (${Me.Combat}) /return
	/if (${Me.XTarget}) /return
	/if (${Me.Moving}) /return
	/if (${Navigation.Active}) /return
	/if (${FindItemCount[${AxeComponents}]} <= 1) /return
	/if (!${Me.CombatAbilityReady[${AxeName}]}) /return 
	/if (!${validate_cast[FALSE, disc, "${AxeName}", ${Me.ID}]}) /return

	/while (${FindItemCount[${AxeName}]} < 200 && ${FindItemCount[${AxeComponents}]} > 1) {
		/if (${Cursor.ID}) /autoinventory
		/if (${Me.XTarget}) /return
		/if (${Mode} == 0) /return
		/if (!${Me.Casting.ID} && !${Cursor.ID}) {
			DEBUG Making ${AxeName} with ${AxeComponents}
			/if (${validate_cast[FALSE, disc, "${AxeName}", ${Me.ID}]}) /call core_cast2 "${AxeName}" disc 0 FALSE
			/if (${Cursor.ID}) /autoinventory
		}
		/if (${Cursor.ID}) /autoinventory
		/if (${FindItemCount[${AxeName}]} > 200) /break
		/if (${Cursor.ID}) /autoinventory
	}
	
/return


Sub get_next_in_rotation

  	/declare _counter   int local 1
  	/declare si setiterator local
  	/vardata si berStunSet.First

	/varcalc berStunCounter ${berStunCounter} + 1
  	/if (${berStunCounter} > ${classTotal}) /varset berStunCounter 1
  
  	/while (!${si.IsEnd}) {

		/if (${_counter} == ${berStunCounter}) {
			/varset berStunCaster ${si.Value}
			/break
		}
		
		/varcalc _counter ${_counter} + 1
		
		/if (${si.Advance}) {
		} else {
			/echo 'Iterator not advanced. IsEnd: ${si.IsEnd}.'
			/endmacro
		}
	}

/return ${berStunCaster}