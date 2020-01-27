|----------------------------------------------------------------------------
|- SUB: shadowknight 
|---------------------------------------------------------------------------- 
Sub shd_main

	/call engage
	/call check_add_aggro
	/call shd_aoe_aggro
	/call shd_disc
	/call shd_get_aggro
	/call shd_self_buffs
	/call shd_combat
	/call shd_combat_buffs
	
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
		/call core_cast2 "${Stance}" spell ${Me.ID} FALSE¨
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

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/docommand /dgt \aw Done Buffing
	}
/return
|----------------------------------------------------------------------------
|- SUB: combat 
|---------------------------------------------------------------------------- 
Sub shd_combat
	
	/call get_target
	/if (!${validate_combat[${Target.ID}]} ) /return
	
	/squelch /attack on

	/if (!${Target.Snared.ID} && ${snareImmuneID} != ${Target.ID}) {
		/if (${validate_cast[FALSE, FIND, "${SnareSpell}", ${Target.ID}]}) {
			/call core_cast2 "${SnareSpell}" FIND ${Target.ID} FALSE
			/call check_cast_events CAST_IMMUNE "${SnareSpell}"
		}
	}

	/if (${validate_cast[FALSE, alt, "Chattering Bones", ${Target.ID}]}) {
		/call core_cast2 "Chattering Bones" alt ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, alt, "Vicious Bite of Chaos", ${Target.ID}]}) {
		/call core_cast2 "Vicious Bite of Chaos" alt ${Target.ID} FALSE
	}

	/if (${Me.PctHPs} < 99) {
		/if (${validate_cast[FALSE, spell, "${Touch1}", ${Target.ID}]}) /call core_cast2 "${Touch1}" spell ${Target.ID} FALSE
	}
	
	/call get_target

	/if (${Me.PctHPs} < 90) {
		/if (${validate_cast[FALSE, spell, "${Touch2}", ${Target.ID}]}) /call core_cast2 "${Touch2}" spell ${Target.ID} FALSE
	}

	/if (${Me.ActiveDisc.ID} != ${DeflectionID}) {
		/if (${validate_cast[FALSE, disc, "${Withstand}", ${Target.ID}]}) {
			/call core_cast2 "${Withstand}" disc ${Target.ID} FALSE
		}
	}
	
	/call get_target

	/if (${Me.PctHPs} < 65) {
		/if (${validate_cast[FALSE, spell, "${DireTestemony}", ${Target.ID}]}) /call core_cast2 "${DireTestemony}" spell ${Target.ID} FALSE
	}


/return

Sub shd_combat_buffs
	
	/call get_target
	/if (!${validate_combat_buffs[FALSE]}) /return

	/if (${Me.ActiveDisc.ID} != ${DeflectionID}) {
		/if (${validate_cast[FALSE, disc, "${Withstand}", ${Me.ID}]}) {
			/call core_cast2 "${Withstand}" disc ${Me.ID} FALSE
		}
	}

	/if (${validate_cast[FALSE, spell, "${Skin}", ${Me.ID}]}) /call core_cast2 "${Skin}" spell ${Me.ID} FALSE
	

	/if (!${Target.Buff[${Bond}].ID}) {
		/if (${validate_cast[FALSE, spell, "${Bond}", ${Target.ID}]}) /call core_cast2 "${Bond}" spell ${Target.ID} FALSE
	}

	/if (!${Me.Buff["${Recourse}"]}) {
		/if (${validate_cast[FALSE, spell, "${Touch3}", ${Target.ID}]}) /call core_cast2 "${Touch3}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "${Stance}", ${Me.ID}]}) /call core_cast2 "${Stance}" spell ${Me.ID} FALSE

	/if (${Me.PctHPs} < 65) {
		/if (${validate_cast[FALSE, alt, "Scourage Skin", ${Target.ID}]}) /call core_cast2 "Scourage Skin" alt ${Target.ID} FALSE
	}

	
	/if (${validate_cast[FALSE, alt, "Spire of the Reavers", ${Me.ID}]}) /call core_cast2 "Spire of the Reavers" alt ${Target.ID} FALSE
	

/return
|----------------------------------------------------------------------------
|- SUB: DoDisc 
|---------------------------------------------------------------------------- 
Sub shd_disc

	/call get_target
	/if (!${validate_combat[${Target.ID}]} ) /return


	/if ((${Me.XTarget} > 2 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3) || ${Me.PctHPs} < 30) && ${Me.PctHPs} < 30) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/if (${validate_cast[FALSE, disc, "${DeflectionDisc}", ${Target.ID}]}) {
					/call core_cast2 "${DeflectionDisc}" disc ${Target.ID} FALSE
				}
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${DeflectionDisc}", ${Target.ID}]}) {
				/call core_cast2 "${DeflectionDisc}" disc ${Target.ID} FALSE
			}
		}
	}

	/if ((${SpawnCount[npc radius 60 zradius 50]} > 3 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3))) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/if (${validate_cast[FALSE, disc, "${IchorGuardDisc}", ${Target.ID}]}) {
					/call core_cast2 "${IchorGuardDisc}" disc ${Target.ID} FALSE
				}
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${IchorGuardDisc}", ${Target.ID}]}) {
				/call core_cast2 "${IchorGuardDisc}" disc ${Target.ID} FALSE
			}
		}
	}

	/if ((${SpawnCount[npc radius 60 zradius 50]} > 3 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3))) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/if (${validate_cast[FALSE, disc, "${LeechcurseID}", ${Target.ID}]}) {
					/call core_cast2 "${LeechcurseID}" disc ${Target.ID} FALSE
				}
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${LeechcurseID}", ${Target.ID}]}) {
				/call core_cast2 "${LeechcurseID}" disc ${Target.ID} FALSE
			}
		}
	}

	/if ((${SpawnCount[npc radius 60 zradius 50]} > 3 || ${Target.Named} || ${Target.Level} > (${Me.Level}+3))) {

		/if (${Me.ActiveDisc.ID}) {
			/if (${Me.ActiveDisc.ID} != ${DeflectionID} && ${Me.ActiveDisc.ID} != ${LeechcurseID} && ${Me.ActiveDisc.ID} != ${UnholyAuraID} && ${Me.ActiveDisc.ID} != ${IchorGuardID}) {
				/stopdisc
				/if (${validate_cast[FALSE, disc, "${UnholyAuraDisc}", ${Target.ID}]}) {
					/call core_cast2 "${UnholyAuraDisc}" disc ${Target.ID} FALSE
				}
			}
		} else {
			/if (${validate_cast[FALSE, disc, "${UnholyAuraDisc}", ${Target.ID}]}) {
				/call core_cast2 "${UnholyAuraDisc}" disc ${Target.ID} FALSE
			}
		}
	}
	
/return
|----------------------------------------------------------------------------
|- SUB: get_aggro
|---------------------------------------------------------------------------- 
Sub shd_get_aggro
	
	/if (!${validate_combat[${Target.ID}]} ) /return

	/squelch /attack on

	/call use_skill_melee ${Target.ID} FALSE

	/if (${validate_cast[FALSE, spell, "${Terror1}", ${Target.ID}]}) {
		/call core_cast2 "${Terror1}" spell ${Target.ID} FALSE
	}	
	/doevents
	
	/if (${validate_cast[FALSE, spell, "${Terror2}", ${Target.ID}]}) {
		/call core_cast2 "${Terror2}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "Ageless Enmity", ${Target.ID}]} && ${Me.SecondaryPctAggro}>=100) {
		/call core_cast2 "Ageless Enmity" alt ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "Projection of Doom", ${Target.ID}]} && ${Me.SecondaryPctAggro}>=30) {
		/call core_cast2 "Projection of Doom" alt ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "Hates Attraction", ${Target.ID}]} && ${Me.SecondaryPctAggro}>=50) {
		/call core_cast2 "Hates Attraction" alt ${Target.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: aoe_aggro   
|---------------------------------------------------------------------------- 
Sub shd_aoe_aggro

	/if (!${validate_combat[${Target.ID}]} ) /return

	/if (${Me.XTarget} > 1) {
		/if (${SpawnCount[NPC radius 50 zradius 30]} > 1) {
			/if (${validate_cast[FALSE, spell, "${Denial}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Using AoE aggro with =>> \ag ${Denial} \ax <<=
				/call core_cast2 "${Denial}" spell ${Target.ID} FALSE
			}
		}
		

		/if (${SpawnCount[NPC radius 50 zradius 50]} > 2) {
			/if (${validate_cast[FALSE, alt, "Explosion of Hatred", ${Target.ID}]}) /call core_cast2 "Explosion of Hatred" alt ${Target.ID} FALSE
		} 

		/if (${SpawnCount[NPC radius 40 zradius 40]} > 2) {
	|		/if (${validate_cast[FALSE, spell, "${Bargain}", ${Target.ID}]}) /call core_cast2 "${Bargain}" spell ${Target.ID} FALSE
		} 

		/if (${SpawnCount[npc radius 50 zradius 50]} > 1) {
	| 		/if (${validate_cast[FALSE, alt, "Area Taunt", ${Target.ID}]}) /call core_cast2 "Area Taunt" alt ${Target.ID} FALSE
		}
	}

/return