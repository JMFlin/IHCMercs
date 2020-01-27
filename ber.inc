
|----------------------------------------------------------------------------
|- SUB: ber_main
|---------------------------------------------------------------------------- 
Sub ber_main

	/call engage
	/call ber_aa_and_disc
	/call ber_combat
	
	/call make_axes "${JoltAxeName}" "${JoltAxeComponent}"
	/call make_axes "${SnareAxeName}" "${SnareAxeComponent}"
	/call make_axes "${StunAxeName}" "${StunAxeComponent}"

|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure
	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub ber_aa_and_disc

	/call get_target

	/if (!${validate_combat[${Target.ID}]} ) /return
	/if (${Target.Distance3D} > 50) /return
	/doevents
	
	/if (!${Me.Combat}) {
		/if (${validate_cast[FALSE, disc, ${PreCombatDisc}, ${Target.ID}]}) /call core_cast2 ${PreCombatDisc} disc ${Target.ID} FALSE
	}

	

	/if (!${Me.Casting.ID} && ${Me.PctEndurance}<=75 && ${Me.PctHPs}>=50 && ${Me.AltAbilityReady[Communion of Blood]} && !${Me.Song[${endregen}].ID} && !${Me.Moving} && !${Me.Invis}) {
		/alt act ${Me.AltAbility[Communion of Blood].ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Battle Leap]} && !${Me.Song[Battle Leap Warcry].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${Me.Combat}) {
		/alt act ${Me.AltAbility[Battle Leap].ID}
	}
	/if (${Me.AltAbilityReady[Desperation]} && !${Me.Buff[Desperation].ID} && ${Me.Haste}<224) {
		/alt act ${Me.AltAbility[Desperation].ID}
		/delay 5
	}
	/if (${Me.CombatAbilityReady[${Spell[${CryHavoc}].RankName}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1 && !${Me.Song[${CryHavoc}].ID} && ${Me.ActiveDisc.ID}!=${CleavingDiscID}) {
		/Disc ${Spell[${CryHavoc}].RankName}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Blood Pact]} && !${Me.Buff[Blood Pact].ID} && ${Target.PctHPs}>1) {
		/alt act ${Me.AltAbility[Blood Pact].ID}
		/delay 5
	}
	/if (${Me.CombatAbilityReady[${SappingStrike}]} && ${Target.PctHPs}>1 && ${Me.PctEndurance}<90) {
		/disc ${SappingStrike}
		/delay 5
	}	
	/if (${Me.CombatAbilityReady[${RageStrike}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1) {
		/Disc ${RageStrike}
		/delay 5
	}
	/if (${Me.CombatAbilityReady[${SharedBuff}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1 && !${Me.Song[${SharedBuffName}].ID} && ${Target.Aggressive}) {
		/Disc ${SharedBuff}
		/delay 5
	}	
	/if (${Me.CombatAbilityReady[${FrenzyBoost}]} && !${Me.Buff[${FrenzyBoostBuff}].ID}) {
		/if (${Me.PctHPs}>80) {
			/alt act 752
			/delay 5
		}
		/Disc ${FrenzyBoost}
		/delay 5
	}
	
	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	/if (${Target.AggroHolder.ID}==${Me.ID} && ${Me.PctAggro}>90 && (${Target.PctHPs}>20 || ${Target.Named}) && ${Target.Level}>=105 && ${Me.AltAbilityReady[Uncanny Resilience]}) {
			/echo Looks like I'm Tanking, GL!
			/alt act ${Me.AltAbility[Uncanny Resilience].ID}
			/delay 5
	}
	/if (${Me.AltAbilityReady[Savage Spirit]} && ${Me.Combat} && ${Target.PctHPs}<99 && ${Me.CombatAbilityReady[${PrimaryBurnDisc}]} && (${Me.XTarget}>=${BurnMobCount} || ${Target.Named})) {
		/alt act ${Me.AltAbility[Savage Spirit].ID}
		/delay 5
	}
	| ${Me.Buff[Savage Spirit].ID}
	/if (${Me.PctEndurance}>=5 && ${Me.CombatAbilityReady[${PrimaryBurnDisc}]} && (${Me.XTarget}>=${BurnMobCount} || ${Target.Named})) {
		/if (${Me.ActiveDisc.ID}) /stopdisc
		/delay 5
		/disc ${PrimaryBurnDisc}
		/delay 5
	}
	/if ((${Me.XTarget}>1 || ${Me.Buff[Savage Spirit].ID}) && ${Me.AltAbilityReady[Fundament: Second Spire of Savagery]} && ${Target.PctHPs}>40 && ${Me.Combat} && ${Target.PctHPs}<99) {
		/alt act ${Me.AltAbility[Fundament: Second Spire of Savagery].ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Blinding Fury]} && ${Me.Buff[Savage Spirit].ID}) {
		/alt act ${Me.AltAbility[Blinding Fury].ID}
		/delay 5
	}
	/if (${Me.Buff[Savage Spirit].ID} && ${Me.AltAbilityReady[Untamed Rage]} && !${Me.Song[Quick Time V].ID}) {
		/alt act ${Me.AltAbility[Untamed Rage].ID}
		/delay 5
	}	
	/if (${Me.Buff[Savage Spirit].ID} && ${Me.AltAbilityReady[Silent Strikes]}) {
		/alt act ${Me.AltAbility[Silent Strikes].ID}
		/delay 5
	}	
	/if (${Me.Buff[Savage Spirit].ID} && ${Me.AltAbilityReady[Focused Furious Rampage]}) {
		/alt act ${Me.AltAbility[Focused Furious Rampage].ID}
		/delay 5
	}

	|/if (${Me.AltAbilityReady[Furious Rampage]} && ${Me.XTarget}>1) {
	|	/alt act ${Me.AltAbility[Furious Rampage].ID}
	|	/delay 5
	|}	

	/if (${Me.PctEndurance}>=5 && ${Me.CombatAbilityReady[${CleavingDisc}]} && ${Me.Combat} && ${Target.PctHPs}<99 && !${Me.CombatAbilityReady[${PrimaryBurnDisc}]} && (${Me.XTarget}>=${BurnMobCount} || ${Target.Named})) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${PrimaryBurnDiscID} && ${Me.ActiveDisc.ID} != ${FlurryDiscID}) {
				/stopdisc
				/delay 5 !${Me.ActiveDisc.ID}
			}
		} else {
			/disc ${CleavingDisc}
		}
	}

	/if (${Me.AltAbilityReady[Reckless Abandon]} && ${Me.ActiveDisc.ID}==${CleavingDiscID}) {
		/alt act ${Me.AltAbility[Reckless Abandon].ID}
		/delay 5
	}

	/if (${Me.PctEndurance}>=5 && ${Me.CombatAbilityReady[${Spell[${FlurryDisc}].RankName}]} && ${Me.Combat} && ${Target.PctHPs}<99 && !${Me.CombatAbilityReady[${PrimaryBurnDisc}]} && !${Me.CombatAbilityReady[${CleavingDisc}]} && (${Me.XTarget}>=${BurnMobCount} || ${Target.Named})) {
		
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${PrimaryBurnDiscID} && ${Me.ActiveDisc.ID} != ${CleavingDiscID}) {
				/stopdisc
				/delay 5 !${Me.ActiveDisc.ID}
			}
		} else {
			/disc ${FlurryDisc}
		}
	}

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	/if ((${Me.XTarget}>1 || ${Me.ActiveDisc.ID}==${FlurryDiscID}) && ${Me.AltAbilityReady[Vehement Rage]} && ${Me.Combat} && ${Target.PctHPs}>20 && ${Target.PctHPs}<99) {
		/alt act ${Me.AltAbility[Vehement Rage].ID}
		/delay 5
	}	
	/if (${Me.CombatAbilityReady[${HHEBuff}]} && ${Me.Combat} && !${Me.Song[${HHEBuff}].ID} && !${Me.Song[Dichotomic Fury].ID} && !${Me.Song[Ruaabri's Fury].ID} && !${Me.Song[Quick Time].ID} && (${Me.ActiveDisc.ID}==${PrimaryBurnDiscID} || ${Me.ActiveDisc.ID}==${CleavingDiscID} || ${Me.ActiveDisc.ID}==${FlurryDiscID})) {
		/disc ${HHEBuff}
		/delay 5
	}	
	/if (${Target.PctHPs}>1 && ${Me.ActiveDisc.ID}!=${DisconDiscID} && ${UseEpic}) { 
		/useitem "${epicaxe}"
		/delay 10
	}
	/if (${Me.PctEndurance}>=5 && ${Me.CombatAbilityReady[${DisconDisc}]} && ${Target.PctHPs}>1 && !${Me.ActiveDisc.ID} && !${Me.Song[Strike of Savagery].ID}) {
		/disc ${DisconDisc}
		/delay 10
	}
	/if (${Me.PctEndurance}>=5 && ${Me.CombatAbilityReady[${ResolveDisc}]} && ${Me.Combat} && ${Target.PctHPs}<99 && !${Me.ActiveDisc.ID}) {
		/if (${Me.PctHPs}>80) {
			/alt act ${Me.AltAbility[Bloodfury].ID}
			/delay 5
		}
		/disc ${ResolveDisc}
		/delay 5
	}
	/if ((${Me.XTarget}>1 || ${Me.ActiveDisc.ID}==${ResolveDiscID}) && ${Me.AltAbilityReady[Juggernaut Surge]} && ${Me.Combat} && ${Target.PctHPs}>20 && ${Target.PctHPs}<99) {
		/alt act ${Me.AltAbility[Juggernaut Surge].ID}
		/delay 5
	}
 /return
|----------------------------------------------------------------------------
|- SUB: Combatdps
|---------------------------------------------------------------------------- 
Sub ber_combat

	/call get_target
	/if (!${validate_combat[${Target.ID}]} ) /return

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
	
	/if (${Me.CombatAbilityReady[${Alliance}]} && !${Target.Buff[Demolisher's Alliance Trigger].ID} && ${UseAlliance}) {
		/Disc ${Alliance}
		/delay 5
	}
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
		/delay 5
	}
	/doevents
	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	|/if (${SpawnCount[npc radius 25 zradius 15 targetable playerstate 4]} < 2) {
	|	/if (${validate_cast[FALSE, disc, "${AEVicious}", ${Target.ID}]}) /call core_cast2 "${AEVicious}" disc ${Target.ID} FALSE
	|	/delay 5
	|}
	/if (!${Target.Buff[Sarnak Finesse].ID} && ${Target.Type.Equal[npc]} && ${Me.Combat} && ${Me.AltAbilityReady[War Cry of the Braxi]} && ${Me.CombatAbilityReady[${DichoSpell}]}) {
		/alt act 1013
		/delay 5
		/doability "${DichoSpell}"
	}	
	/if (${Me.AltAbilityReady[Binding Axe]} && ${Target.PctHPs}>1 && ${Me.Combat}) {
		/alt act 642
		/delay 5
	}	

	/if (${validate_cast[FALSE, disc, "${Dfrenzy}", ${Target.ID}]}) /call core_cast2 "${Dfrenzy}" disc ${Target.ID} FALSE

	/if (${Target.Type.Equal[Corpse]} || !${Target.ID} || !${Me.XTarget[1].ID} || !${Target.Type.Equal[NPC]}) /return

	/if (${Me.CombatAbilityReady[${Dvolley}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1 && ${Me.Combat}) {
		/Disc ${Dvolley}
		/delay 5
	}
	| ${berStunRotationStunner.Equal[${Me.DisplayName}]} && 
	/if (${stunTurn}) {
		/if (${validate_cast[FALSE, disc, "${Stun}", ${Target.ID}]}) {
			/call core_cast2 "${Stun}" disc ${Target.ID} FALSE
			/delay 5
			/call get_next_in_rotation
			/varset berStunRotationStunner ${Macro.Return}
			/docommand /dgt ******** NEXT SHOULD BE ${berStunRotationStunner} *********
			/squelch /dex ${berStunRotationStunner} /varset stunTurn 1
			/squelch /dex ${berStunRotationStunner} /varset berStunRotationCounter ${berStunRotationCounter} 
			/varset stunTurn 0
		}
	} else /if (!${berStunRotationStunner.Equal[${Me.DisplayName}]}) {
		/if (${Me.CombatAbilityReady[${Daxethrow}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1 && ${Me.Combat}) {
			/Disc ${Daxethrow}
			/delay 5
		}
	}
	/if (${Me.CombatAbilityReady[${Daxeof}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>1 && ${Me.Combat}) {
		/Disc ${Daxeof}
		/delay 5
	}
	/if (${Me.CombatAbilityReady[${Phantom}]} && ${Me.PctEndurance}>=5 && ${Target.PctHPs}>50 && ${Me.Combat}) {
		/Disc ${Phantom}
		/delay 5
	}

 /return
|----------------------------------------------------------------------------
|- SUB: DowntimeDiscs
|---------------------------------------------------------------------------- 
Sub make_axes(string AxeName, string AxeComponents)

	/if (${Me.Combat}) /return
	/if (${Me.XTarget}) /return
	/if (${Me.Moving}) /return
	/if (${Navigation.Active}) /return
	/if (${FindItemCount[${AxeComponents}]} <= 1) /return
	/if (${Me.CombatAbilityReady[${AxeName}]}) /return 

	/while (${FindItemCount[${AxeName}]} < 200 && ${FindItemCount[${AxeComponents}]} > 1) {
		DEBUG Making ${AxeName} with ${AxeComponents}
		/if (${Cursor.ID}) /autoinventory
		/if (${Me.XTarget}) /return
		/if (${Mode} == 0) /return
		/if (!${Me.Casting.ID} && !${Cursor.ID}) {
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
  	/vardata si berStunRotationSet.First

	/varcalc berStunRotationCounter ${berStunRotationCounter} + 1
  	/if (${berStunRotationCounter} > ${berTotal}) /varset berStunRotationCounter 1
  
  	/while (!${si.IsEnd}) {

		/if (${_counter} == ${berStunRotationCounter}) {
			/varset berStunRotationStunner ${si.Value}
			/break
		}
		
		/varcalc _counter ${_counter} + 1
		
		/if (${si.Advance}) {
		} else {
			/echo 'Iterator not advanced. IsEnd: ${si.IsEnd}.'
			/endmacro
		}
	}

/return ${berStunRotationStunner}