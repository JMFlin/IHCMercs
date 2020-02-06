|----------------------------------------------------------------------------
|- SUB: shadowknight 
|---------------------------------------------------------------------------- 
Sub shd_main

	/call shd_self_buffs

	/while (${Me.XTarget}) {

		/call get_target
		
		/call shd_get_aggro
	
		/call shd_combat_buffs
		
		/if (!${validate_combat[${Target.ID}]}) /return
		
		/call engage
		
		/call shd_disc

		/if (!${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${Me.AltAbilityReady[Encroaching Darkness]}) {
				/if (${validate_cast[FALSE, alt, "Encroaching Darkness", ${Target.ID}]}) {
					/call core_cast2 "Encroaching Darkness" alt ${Target.ID} FALSE
					/call check_cast_events CAST_IMMUNE "Encroaching Darkness"
				}
			} else {
				/if (${validate_cast[FALSE, spell, "${SnareSpell}", ${Target.ID}]}) {
					/call core_cast2 "${SnareSpell}" spell ${Target.ID} FALSE
					/call check_cast_events CAST_IMMUNE "${SnareSpell}"
				}
			}
		}

		/call check_add_aggro
	
		/if (${validate_cast[FALSE, alt, "Chattering Bones", ${Target.ID}]}) {
			/call core_cast2 "Chattering Bones" alt ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Vicious Bite of Chaos", ${Target.ID}]}) {
			/call core_cast2 "Vicious Bite of Chaos" alt ${Target.ID} FALSE
		}
		
		/call shd_aoe_aggro
		/call check_add_aggro

		/if (${validate_cast[FALSE, alt, "Visage of Death", ${Me.ID}]}) {
			/call core_cast2 "Visage of Death" alt 0 FALSE
		}

		/if (${Me.PctHPs} < 99) {
			/if (${validate_cast[FALSE, spell, "${Touch1}", ${Target.ID}]}) /call core_cast2 "${Touch1}" spell ${Target.ID} FALSE
		}
		
		/call shd_get_aggro
		/call check_add_aggro
		/if (${Me.PctHPs} < 90) {
			/if (${validate_cast[FALSE, spell, "${Touch2}", ${Target.ID}]}) /call core_cast2 "${Touch2}" spell ${Target.ID} FALSE
		}

		/call check_add_aggro

		/if (!${Me.Buff[${Recourse}].ID}) {
			/if (${validate_cast[FALSE, spell, "${Touch3}", ${Target.ID}]}) /call core_cast2 "${Touch3}" spell ${Target.ID} FALSE
		}

		/call shd_aoe_aggro
		/call check_add_aggro

		/if (${Me.ActiveDisc.ID} != ${DeflectionID}) {
			/if (${validate_cast[FALSE, disc, "${Withstand}", ${Me.ID}]}) {
				/call core_cast2 "${Withstand}" disc 0 FALSE
			}
		}
		
		/call shd_get_aggro

		/if (${Me.PctHPs} < 65) {
			/if (${validate_cast[FALSE, spell, "${DireTestemony}", ${Target.ID}]}) /call core_cast2 "${DireTestemony}" spell ${Target.ID} FALSE
		}

	}
/return
|----------------------------------------------------------------------------
|- SUB: self_buffs 
|---------------------------------------------------------------------------- 
Sub shd_self_buffs
	/declare CastCheck			int local 0

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${Skin}", ${Me.ID}]}) {
		/call core_cast2 "${Skin}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${Stance}", ${Me.ID}]}) {
		/call core_cast2 "${Stance}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}
	

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${Cloak}", ${Me.ID}]}) {
		/call core_cast2 "${Cloak}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}
	

	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, spell, "${HPShroud}", ${Me.ID}]}) {
		/call core_cast2 "${HPShroud}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${Me.XTarget}) /return

	/if (${validate_cast[FALSE, spell, "${MPShroud}", ${Me.ID}]}) {
		/call core_cast2 "${MPShroud}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}
	

	/if (${Me.XTarget}) /return
	
	/if (${validate_cast[FALSE, alt, "Voice of Thule", ${Me.ID}]}) {
		/call core_cast2 "Voice of Thule" alt ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (!${Me.Buff["Bobbing Corpse"].ID}) {
		/if (${validate_cast[FALSE, alt, "Bobbing Corpse", ${Me.ID}]}) {
			/call core_cast2 "Bobbing Corpse" alt ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${validate_cast[FALSE, spell, "${Disruption}", ${Me.ID}]}) {
		/call core_cast2 "${Disruption}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/docommand /dgt \aw Done Buffing
	}
/return

Sub shd_combat_buffs

	/if (${validate_cast[FALSE, spell, "${Skin}", ${Me.ID}]}) /call core_cast2 "${Skin}" spell ${Target.ID} FALSE

	/if (!${Target.Buff[${Bond}].ID}) {
		/if (${validate_cast[FALSE, spell, "${Bond}", ${Target.ID}]}) /call core_cast2 "${Bond}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "${Stance}", ${Me.ID}]}) /call core_cast2 "${Stance}" spell ${Target.ID} FALSE

	/if (${validate_cast[FALSE, spell, "${Disruption}", ${Me.ID}]}) /call core_cast2 "${Disruption}" spell ${Me.ID} FALSE

	/if (${validate_cast[FALSE, alt, "Scourge Skin", ${Me.ID}]}) /call core_cast2 "Scourge Skin" alt 0 FALSE
	
	/if (${validate_cast[FALSE, alt, "Spire of the Reavers", ${Me.ID}]}) /call core_cast2 "Spire of the Reavers" alt 0 FALSE

	/if (${Me.ActiveDisc.ID} != ${DeflectionID}) {
		/if (${validate_cast[FALSE, disc, "${Withstand}", ${Me.ID}]}) {
			/call core_cast2 "${Withstand}" disc 0 FALSE
		}
	}



/return
|----------------------------------------------------------------------------
|- SUB: DoDisc 
|---------------------------------------------------------------------------- 
Sub shd_disc

	/if (${Me.XTarget} > 2 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/if (${validate_cast[FALSE, disc, "${DeflectionDisc}", ${Me.ID}]}) /call core_cast2 "${DeflectionDisc}" disc 0 FALSE
				
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${DeflectionDisc}", ${Me.ID}]}) /call core_cast2 "${DeflectionDisc}" disc 0 FALSE
		}
	

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/if (${validate_cast[FALSE, disc, "${IchorGuardDisc}", ${Me.ID}]}) /call core_cast2 "${IchorGuardDisc}" disc 0 FALSE
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${IchorGuardDisc}", ${Me.ID}]}) /call core_cast2 "${IchorGuardDisc}" disc 0 FALSE
		}
	

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/if (${validate_cast[FALSE, disc, "${LeechcurseID}", ${Me.ID}]}) {
					/call core_cast2 "${LeechcurseID}" disc 0 FALSE
				}
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${LeechcurseID}", ${Me.ID}]}) {
				/call core_cast2 "${LeechcurseID}" disc 0 FALSE
			}
		}
	

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/delay 1s !${Me.ActiveDisc.ID}
				/if (${validate_cast[FALSE, disc, "${UnholyAuraDisc}", ${Me.ID}]}) {
					/call core_cast2 "${UnholyAuraDisc}" disc 0 FALSE
				}
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${UnholyAuraDisc}", ${Me.ID}]}) {
				/call core_cast2 "${UnholyAuraDisc}" disc 0 FALSE
			}
		}
	}
	
/return
|----------------------------------------------------------------------------
|- SUB: get_aggro
|---------------------------------------------------------------------------- 
Sub shd_get_aggro

	/call use_skill_melee ${Target.ID} FALSE

	/if (${validate_cast[FALSE, spell, "${Terror1}", ${Target.ID}]}) {
		/call core_cast2 "${Terror1}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "${Terror2}", ${Target.ID}]}) {
		/call core_cast2 "${Terror2}" spell ${Target.ID} FALSE
	}
	

	/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
		/if (${validate_cast[FALSE, alt, "Ageless Enmity", ${Target.ID}]}) /call core_cast2 "Ageless Enmity" alt ${Target.ID} FALSE
	}
	
	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Projection of Doom", ${Target.ID}]} && ${Me.SecondaryPctAggro} >= 30) {
			/call core_cast2 "Projection of Doom" alt ${Target.ID} FALSE
		}
	}

	/if (${validate_cast[FALSE, alt, "Hate's Attraction", ${Target.ID}]}) {
		/call core_cast2 "Hate's Attraction" alt ${Target.ID} FALSE
	}
	
	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${Target.ID}]}) /call core_cast2 "Explosion of Hatred" alt ${Target.ID} FALSE
	}
	/if (${Me.SecondaryPctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Explosion of Spite", ${Target.ID}]}) /call core_cast2 "Explosion of Spite" alt ${Target.ID} FALSE
	}
/return
|----------------------------------------------------------------------------
|- SUB: aoe_aggro   
|---------------------------------------------------------------------------- 
Sub shd_aoe_aggro

	/if (${Me.XTarget} > 1) {
		/if (${SpawnCount[NPC radius 50 zradius 30]} > 1) {
			/if (${validate_cast[FALSE, spell, "${Denial}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Using AoE aggro with =>> \ag ${Denial} \ax <<=
				/call core_cast2 "${Denial}" spell ${Target.ID} FALSE
			}
		}
		
		/if (${SpawnCount[NPC radius 50 zradius 50]} > 1) {
			/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${Target.ID}]}) /call core_cast2 "Explosion of Hatred" alt ${Target.ID} FALSE
		}
		
		/if (${SpawnCount[NPC radius 50 zradius 50]} > 1) {
			/if (${validate_cast[FALSE, alt, "Explosion of Spite", ${Target.ID}]}) /call core_cast2 "Explosion of Spite" alt ${Target.ID} FALSE
		}

		/if (${SpawnCount[NPC radius 40 zradius 40]} > 2) {
			/if (${validate_cast[FALSE, spell, "${Bargain}", ${Target.ID}]}) /call core_cast2 "${Bargain}" spell ${Target.ID} FALSE
		} 
	}

/return