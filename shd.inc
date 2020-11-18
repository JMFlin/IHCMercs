|----------------------------------------------------------------------------
|- SUB: shadowknight 
|---------------------------------------------------------------------------- 
Sub shd_main

	/if (!${Me.XTarget}) /call shd_self_buffs
	/if (!${Me.XTarget}) /call shd_mana_check

	/while (${Me.XTarget} && ${Mode} == 3) {

		/call get_target
		
		/if (${Target.Distance3D} > 50) {
			/if (${validate_cast[FALSE, spell, "${Terror1}", ${Target.ID}]}) {
				/call core_cast2 "${Terror1}" spell ${Target.ID} FALSE
			}
			/if (${Target.Distance3D} > 50) {
				/if (${validate_cast[FALSE, spell, "${Terror2}", ${Target.ID}]}) {
					/call core_cast2 "${Terror2}" spell ${Target.ID} FALSE
				}
			}
		}

		/call shd_combat_buffs ${Target.ID}
		/call shd_rotation ${Target.ID}
		/call shd_disc

		/if (!${validate_combat[${Target.ID}]}) /continue
		
		/call use_skill_melee ${Target.ID} FALSE

		/if (${Target.Named} || ${Target.PctHPs} > 90) {
			/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceSpell}" ${Target.ID}
		}

		/if (!${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]} && ${shdDoSnare}) {
			/if (${validate_cast[FALSE, FIND, "${SnareSpell}", ${Target.ID}]}) {
				/call core_cast2 "${SnareSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events CAST_IMMUNE "${SnareSpell}"
			}
		}

		/if (${validate_cast[FALSE, spell, "${Spear}", ${Target.ID}]}) {
			/call core_cast2 "${Spear}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Chattering Bones", ${Target.ID}]}) {
			/call core_cast2 "Chattering Bones" alt ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Vicious Bite of Chaos", ${Target.ID}]}) {
			/call core_cast2 "Vicious Bite of Chaos" alt ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Visage of Death", ${Me.ID}]}) {
			/call core_cast2 "Visage of Death" alt 0 FALSE
		}

		/call shd_mana_check
	}
/return

Sub shd_rotation(int _tmpID)
	/declare _notAggroCounter int local 0
	/declare _aoeCasted bool local FALSE

	/if (!${_tmpID}) /return
	/if (${Group.MainTank.ID} != ${Me.ID}) /return

	/call get_xtar_haters_not_aggro ${verboseSHD}
	/varset _notAggroCounter ${Macro.Return}
		
	/if (${_notAggroCounter} > 1) {
		
		/if (${SpawnCount[loc ${Spawn[id ${_tmpID}].X} ${Spawn[id ${_tmpID}].Y} radius 50 zradius 50 npc targetable noalert 1]} > 1) {
			/if (${validate_cast[FALSE, alt, "Explosion of Spite", ${_tmpID}]}) {
				/call core_cast2 "Explosion of Spite" alt ${_tmpID} FALSE
				/varset _aoeCasted TRUE
			}
		}
		/if (!${_aoeCasted}) {
			/if (${SpawnCount[NPC radius 50 zradius 50]} > 1) {
				/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${_tmpID}]}) {
					/call core_cast2 "Explosion of Hatred" alt ${_tmpID} FALSE
					/varset _aoeCasted TRUE
				}
			}
		}

		/if (!${_aoeCasted}) {
			/if (${SpawnCount[NPC radius 40 zradius 40]} > 2) {
				/if (${validate_cast[FALSE, spell, "${Bargain}", ${_tmpID}]}) {
					/call core_cast2 "${Bargain}" spell ${_tmpID} FALSE
					/varset _aoeCasted TRUE
				}
			}
		}

		/if (!${_aoeCasted}) {
			/if (${SpawnCount[NPC radius 50 zradius 30]} > 1) {
				/if (${validate_cast[FALSE, spell, "${Denial}", ${_tmpID}]}) {
					/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Using AoE aggro with =>> \ag ${Denial} \ax <<=
					/call core_cast2 "${Denial}" spell ${_tmpID} FALSE
					/varset _aoeCasted TRUE
				}
			}
		}
	}

	/call use_skill_melee ${_tmpID} FALSE
	/if (${get_xtar_min_haters[30]}) {

		/if (${validate_cast[FALSE, spell, "${Power}", ${_tmpID}]}) {
			/call core_cast2 "${Power}" spell ${_tmpID} FALSE
			/return
		}

		/if (${validate_cast[FALSE, spell, "${Terror1}", ${_tmpID}]}) {
			/call core_cast2 "${Terror1}" spell ${_tmpID} FALSE
			/return
		}

		/if (${validate_cast[FALSE, spell, "${Terror2}", ${_tmpID}]}) {
			/call core_cast2 "${Terror2}" spell ${_tmpID} FALSE
			/return
		}
		
		/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
			/if (${validate_cast[FALSE, alt, "Ageless Enmity", ${_tmpID}]}) {
				/call core_cast2 "Ageless Enmity" alt ${_tmpID} FALSE
				/return
			}
		}
		
		/if (${Me.SecondaryPctAggro} > 30) {
			/if (${validate_cast[FALSE, alt, "Projection of Doom", ${_tmpID}]} && ${Me.SecondaryPctAggro} >= 30) {
				/call core_cast2 "Projection of Doom" alt ${_tmpID} FALSE
				/return
			}
		}

		/if (${validate_cast[FALSE, alt, "Hate's Attraction", ${_tmpID}]}) {
			/call core_cast2 "Hate's Attraction" alt ${_tmpID} FALSE
			/return
		}
		
		/if (${Me.SecondaryPctAggro} > 30) {
			/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${_tmpID}]}) {
				/call core_cast2 "Explosion of Hatred" alt ${_tmpID} FALSE
				/return
			}
		}
		/if (${Me.SecondaryPctAggro} > 30) {
			/if (${validate_cast[FALSE, alt, "Explosion of Spite", ${_tmpID}]}) {
				/call core_cast2 "Explosion of Spite" alt ${_tmpID} FALSE
				/return
			}
		}
	} else {

		/if (${Me.PctHPs} < 30) {
			/if (${validate_cast[FALSE, alt, "Leech Touch", ${_tmpID}]}) {
				/call core_cast2 "Leech Touch" alt ${_tmpID} FALSE
			}
		}

		/if (${Me.PctHPs} < 50) {
			/if (${validate_cast[FALSE, spell, "${DireTestemony}", ${_tmpID}]}) {
				/call core_cast2 "${DireTestemony}" spell ${_tmpID} FALSE
			}
		}

		/if (${Me.PctHPs} < 55) {
			/if (${validate_cast[FALSE, spell, "${DichotomicFang}", ${_tmpID}]}) {
				/call core_cast2 "${DichotomicFang}" spell ${_tmpID} FALSE
			}
		}

		|**
		/if (!${Me.Buff[${Recourse}].ID}) {
			/if (${validate_cast[FALSE, spell, "${Touch3}", ${_tmpID}]}) {
				/call core_cast2 "${Touch3}" spell ${_tmpID} FALSE
			}
		}
		**|

		/if (${Me.ActiveDisc.ID} == ${UnholyAuraID} || ${Target.Buff[${AllianceSpell}]}) {
			/if (${validate_cast[FALSE, spell, "${Touch1}", ${_tmpID}]}) {
				/call core_cast2 "${Touch1}" spell ${_tmpID} FALSE
			}
			/if (${validate_cast[FALSE, spell, "${Touch2}", ${_tmpID}]}) {
				/call core_cast2 "${Touch2}" spell ${_tmpID} FALSE
			}

			/if (${validate_cast[FALSE, alt, "Forceful Rejuvenation", ${Me.ID}]} && ${Me.ActiveDisc.ID} == ${UnholyAuraID}) {
				/call core_cast2 "Forceful Rejuvenation" alt 0 FALSE
				/if (${validate_cast[FALSE, spell, "${Touch1}", ${_tmpID}]}) {
					/call core_cast2 "${Touch1}" spell ${_tmpID} FALSE
				}

				/if (${validate_cast[FALSE, spell, "${Touch2}", ${_tmpID}]}) {
					/call core_cast2 "${Touch2}" spell ${_tmpID} FALSE
				}
			}
		}

		/if (${Me.PctHPs} < 90) {
			/if (${validate_cast[FALSE, spell, "${Touch1}", ${_tmpID}]}) {
				/call core_cast2 "${Touch1}" spell ${_tmpID} FALSE
				/return
			}
		}
		/if (${Me.PctHPs} < 90) {
			/if (${validate_cast[FALSE, spell, "${Touch2}", ${_tmpID}]}) {
				/call core_cast2 "${Touch2}" spell ${_tmpID} FALSE
				/return
			}
		}

	}

/return

|----------------------------------------------------------------------------
|- SUB: shd_lifetap_spam
|---------------------------------------------------------------------------- 
Sub shd_lifetap_spam(int _tmpID, bool _debug)

	/if (${Me.PctHPs} < 45) {
		/if (${validate_cast[FALSE, alt, "Leech Touch", ${_tmpID}]}) {
			/call core_cast2 "Leech Touch" alt ${_tmpID} FALSE
		}
	}

	/if (${Me.PctHPs} < 55) {
		/if (${validate_cast[FALSE, spell, "${DireTestemony}", ${_tmpID}]}) {
			/call core_cast2 "${DireTestemony}" spell ${_tmpID} FALSE
		}
	}

	/if (!${Me.Buff[${Recourse}].ID}) {
		/if (${validate_cast[FALSE, spell, "${Touch3}", ${_tmpID}]}) {
			/call core_cast2 "${Touch3}" spell ${_tmpID} FALSE
		}
	}

	/if (${Me.ActiveDisc.ID} == ${UnholyAuraID} || ${Target.Buff[${AllianceSpell}]}) {
		/if (${validate_cast[FALSE, spell, "${Touch1}", ${_tmpID}]}) {
			/call core_cast2 "${Touch1}" spell ${_tmpID} FALSE
		}
		/if (${validate_cast[FALSE, spell, "${Touch2}", ${_tmpID}]}) {
			/call core_cast2 "${Touch2}" spell ${_tmpID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Forceful Rejuvenation", ${Me.ID}]} && ${Me.ActiveDisc.ID} == ${UnholyAuraID}) {
			/call core_cast2 "Forceful Rejuvenation" alt 0 FALSE
			/if (${validate_cast[FALSE, spell, "${Touch1}", ${_tmpID}]}) {
				/call core_cast2 "${Touch1}" spell ${_tmpID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${Touch2}", ${_tmpID}]}) {
				/call core_cast2 "${Touch2}" spell ${_tmpID} FALSE
			}
		}
	}

	/if (${validate_cast[FALSE, spell, "${Touch1}", ${_tmpID}]}) {
		/call core_cast2 "${Touch1}" spell ${_tmpID} FALSE
		/return
	}
	/if (${validate_cast[FALSE, spell, "${Touch2}", ${_tmpID}]}) {
		/call core_cast2 "${Touch2}" spell ${_tmpID} FALSE
		/return
	}

/return

|----------------------------------------------------------------------------
|- SUB: get_aggro
|---------------------------------------------------------------------------- 
Sub shd_get_aggro(int _tmpID, bool _debug)

	/if (${validate_cast[FALSE, spell, "${Terror1}", ${_tmpID}]}) {
		/call core_cast2 "${Terror1}" spell ${_tmpID} FALSE
		/return
	}

	/if (${validate_cast[FALSE, spell, "${Terror2}", ${_tmpID}]}) {
		/call core_cast2 "${Terror2}" spell ${_tmpID} FALSE
		/return
	}
	
	/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
		/if (${validate_cast[FALSE, alt, "Ageless Enmity", ${_tmpID}]}) {
			/call core_cast2 "Ageless Enmity" alt ${_tmpID} FALSE
			/return
		}
	}
	
	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Projection of Doom", ${_tmpID}]} && ${Me.SecondaryPctAggro} >= 30) {
			/call core_cast2 "Projection of Doom" alt ${_tmpID} FALSE
			/return
		}
	}

	/if (${validate_cast[FALSE, alt, "Hate's Attraction", ${_tmpID}]}) {
		/call core_cast2 "Hate's Attraction" alt ${_tmpID} FALSE
		/return
	}
	
	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${_tmpID}]}) {
			/call core_cast2 "Explosion of Hatred" alt ${_tmpID} FALSE
			/return
		}
	}
	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Explosion of Spite", ${_tmpID}]}) {
			/call core_cast2 "Explosion of Spite" alt ${_tmpID} FALSE
			/return
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: aoe_aggro   
|---------------------------------------------------------------------------- 
Sub shd_aoe_aggro(int _tmpID, bool _debug)

	/if (${SpawnCount[NPC radius 50 zradius 30]} > 1) {
		/if (${validate_cast[FALSE, spell, "${Denial}", ${_tmpID}]}) {
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Using AoE aggro with =>> \ag ${Denial} \ax <<=
			/call core_cast2 "${Denial}" spell ${_tmpID} FALSE
		}
	}
	
	/if (${SpawnCount[NPC radius 50 zradius 50]} > 1) {
		/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${_tmpID}]}) /call core_cast2 "Explosion of Hatred" alt ${_tmpID} FALSE
	}
	
	/if (${SpawnCount[NPC radius 50 zradius 50]} > 1) {
		/if (${validate_cast[FALSE, alt, "Explosion of Spite", ${_tmpID}]}) /call core_cast2 "Explosion of Spite" alt ${_tmpID} FALSE
	}

	/if (${SpawnCount[NPC radius 40 zradius 40]} > 2) {
		/if (${validate_cast[FALSE, spell, "${Bargain}", ${_tmpID}]}) /call core_cast2 "${Bargain}" spell ${_tmpID} FALSE
	} 

/return

|----------------------------------------------------------------------------
|- SUB: self_buffs 
|---------------------------------------------------------------------------- 
Sub shd_self_buffs
	/declare _castCheck			int local 0

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${Skin}", ${Me.ID}]}) {
		/call core_cast2 "${Skin}" spell 0 FALSE
		/varset _castCheck 1
	}

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${Stance}", ${Me.ID}]}) {
		/call core_cast2 "${Stance}" spell 0 FALSE
		/varset _castCheck 1
	}
	
	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${Cloak}", ${Me.ID}]}) {
		/call core_cast2 "${Cloak}" spell 0 FALSE
		/varset _castCheck 1
	}

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${HPShroud}", ${Me.ID}]}) {
		/call core_cast2 "${HPShroud}" spell 0 FALSE
		/varset _castCheck 1
	}

	/if (${Me.XTarget}) /return
	/if (!${Me.Buff[${HPShroud}].ID}) {
		/if (${validate_cast[FALSE, spell, "${MPShroud}", ${Me.ID}]}) {
			/call core_cast2 "${MPShroud}" spell 0 FALSE
			/varset _castCheck 1
		}
	}

	/if (${Me.XTarget}) /return
	/if (${Group.MainTank.ID} == ${Me.ID}) {
		/if (${validate_cast[FALSE, alt, "Voice of Thule", ${Me.ID}]}) {
			/call core_cast2 "Voice of Thule" alt ${Me.ID} FALSE
		}
	}

	/if (!${Me.Buff["Bobbing Corpse"].ID}) {
		/if (${validate_cast[FALSE, alt, "Bobbing Corpse", ${Me.ID}]}) {
			/call core_cast2 "Bobbing Corpse" alt ${Me.ID} FALSE
		}
	}

	/if (${validate_cast[FALSE, spell, "${Disruption}", ${Me.ID}]}) {
		/call core_cast2 "${Disruption}" spell ${Me.ID} FALSE
		/varset _castCheck 1
	}

	/if (${_castCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
	}
/return

Sub shd_combat_buffs(int _tmpID)

	/if (${Target.Distance3D} < 60) {
		/if (${Me.ActiveDisc.ID} != ${DeflectionID}) {
			/if (${validate_cast[FALSE, disc, "${Withstand}", ${Me.ID}]}) {
				/call core_cast2 "${Withstand}" disc 0 FALSE
				/return
			}
		}
	}

	/if (${validate_cast[FALSE, spell, "${Skin}", ${Me.ID}]}) {
		/call core_cast2 "${Skin}" spell 0 FALSE
		/return
	}

	|**
	/if ((${Target.Named} || ${Me.XTarget}>=${BurnMobCount}) && !${Target.Buff[${Bond}].ID}) {
		/if (${validate_cast[FALSE, spell, "${Bond}", ${_tmpID}]}) {
			/call core_cast2 "${Bond}" spell ${_tmpID} FALSE
			/return
		}
	}
	**|

	/if (${validate_cast[FALSE, spell, "${Stance}", ${Me.ID}]}) {
		/call core_cast2 "${Stance}" spell 0 FALSE
		/return
	}

	/if (${validate_cast[FALSE, spell, "${Disruption}", ${Me.ID}]}) {
		/call core_cast2 "${Disruption}" spell ${Me.ID} FALSE
		/return
	}

	/if (${validate_cast[FALSE, alt, "Scourge Skin", ${Me.ID}]}) {
		/call core_cast2 "Scourge Skin" alt 0 FALSE
	}
	
	/if (${validate_cast[FALSE, alt, "Spire of the Reavers", ${Me.ID}]}) {
		/call core_cast2 "Spire of the Reavers" alt 0 FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: DoDisc 
|---------------------------------------------------------------------------- 
Sub shd_disc

	/if (${Me.XTarget} > 2 || ${check_for_named[FALSE]} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) {

		/if (${validate_cast[FALSE, disc, "${DeflectionDisc}", ${Me.ID}]}) {
			/if (${Me.ActiveDisc.ID}) {
				/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
					/stopdisc
					/delay 1s !${Me.ActiveDisc.ID}
					/call core_cast2 "${DeflectionDisc}" disc 0 FALSE
				}
			} else {
				/call core_cast2 "${DeflectionDisc}" disc 0 FALSE
			}
		}
	
		/if (${validate_cast[FALSE, disc, "${IchorGuardDisc}", ${Me.ID}]}) {
			/if (${Me.ActiveDisc.ID}) {
				/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
					/stopdisc
					/delay 1s !${Me.ActiveDisc.ID}
					/call core_cast2 "${IchorGuardDisc}" disc 0 FALSE
				}
			} else {
				/call core_cast2 "${IchorGuardDisc}" disc 0 FALSE
			}
		}

		/call get_target
		/if (${validate_cast[FALSE, alt, "Harm Touch", ${Target.ID}]}) {
			/call core_cast2 "Harm Touch" alt ${Target.ID} FALSE
		}
	}

	/if (${validate_cast[FALSE, disc, "${LeechcurseID}", ${Me.ID}]}) {
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/call core_cast2 "${LeechcurseID}" disc 0 FALSE
			}
		} else {
			/call core_cast2 "${LeechcurseID}" disc 0 FALSE
		}
	}

	/if (${validate_cast[FALSE, disc, "${UnholyAuraDisc}", ${Me.ID}]}) {
		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/call core_cast2 "${UnholyAuraDisc}" disc 0 FALSE
			}
		} else {
			/call core_cast2 "${UnholyAuraDisc}" disc 0 FALSE
		}
	}
	
/return

Sub shd_mana_check
	/call bag_mod_rod
	/call use_mod_rod
/return