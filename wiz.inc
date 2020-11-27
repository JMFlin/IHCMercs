|----------------------------------------------------------------------------
|- SUB: wiz_main
|----------------------------------------------------------------------------
|**
First burn:
	Focus of Arcanum
	Fury of the Gods
	Arcane Fury
	second spire
	glyph of the cataclysm
	Twincast spell

	Unitl the spell version of your twincast runs out:
	claw > braid > wildether barrage > wildspark barrage

Second burn:
	Arcane Destruction
	Frenzied Devastation
	Improved Twincast

	braid > dichotomic > ethereal skyfire > ethereal Icefloe
	After braid, Alliance, Dissident, use Forceful Rejuvenation.

Non-burn:
	claw > braid > cloudburst thunderbolt / Dissident > fire ethereal

	Alliance & Vortex need to fit in as well, i manually cast these.  Try to cast them as much as possible.
**|

Sub wiz_main

	/if (!${Me.XTarget}) /call wiz_self_buff_check FALSE
	/if (!${Me.XTarget}) /call wiz_mana_check

	/while (${Me.XTarget} && ${Mode} == 3) {

		/call move_to_camp

		/call get_target

		/if (${Int[${Target.Beneficial.ID}]}) {
			/if (${validate_cast[FALSE, alt, "Eradicate Magic", ${Target.ID}]}) /call core_cast2 "Eradicate Magic" alt ${Target.ID} FALSE
		}

		/if (!${validate_combat[${Target.ID}]}) /continue

		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call wiz_burn_routine

		/if (${Target.Named} || ${Target.PctHPs} > 90) {
			/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceSpell}" ${Target.ID}
		}

		/if (!${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]} && ${wizDoSnare}) {
			/if (${validate_cast[FALSE, FIND, "${SnareSpell}", ${Target.ID}]}) {
				/call core_cast2 "${SnareSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SnareSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		/if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) /call core_cast2 "${TwincastSpell}" spell 0 FALSE
		
		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call wiz_burn_routine

		/if (${Me.Buff[${TwincastSpell}].ID}) {
			|** 
				claw > braid > wildether barrage > wildspark barrage
			**|
			/if (${validate_cast[FALSE, spell, "${ClawNuke}", ${Target.ID}]}) {
				/call core_cast2 "${ClawNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${BraidNuke}", ${Target.ID}]}) {
				/call core_cast2 "${BraidNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${WildNuke}", ${Target.ID}]}) {
				/call core_cast2 "${WildNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${LowerWildNuke}", ${Target.ID}]}) {
				/call core_cast2 "${LowerWildNuke}" spell ${Target.ID} FALSE
			}

		} else /if (${Me.Buff[Improved Twincast ${ImprovedTwincastRank}].ID}) {
			|** 
				braid > dichotomic > foreful rejuvenation > braid > dichotomic > ethereal skyfire > ethereal Icefloe
			**|
			/if (${validate_cast[FALSE, spell, "${BraidNuke}", ${Target.ID}]}) {
				/call core_cast2 "${BraidNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) {
				/call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, alt, "Forceful Rejuvenation", ${Me.ID}]}) {
				
				/call core_cast2 "Forceful Rejuvenation" alt 0 FALSE

				/if (${validate_cast[FALSE, spell, "${BraidNuke}", ${Target.ID}]}) {
					/call core_cast2 "${BraidNuke}" spell ${Target.ID} FALSE
				}

				/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) {
					/call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
				}
			}

			/if (${validate_cast[FALSE, spell, "${FireEtherealNuke}", ${Target.ID}]}) {
				/call core_cast2 "${FireEtherealNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${ColdEtherealNuke}", ${Target.ID}]}) {
				/call core_cast2 "${ColdEtherealNuke}" spell ${Target.ID} FALSE
			}

		} else {
			|** 
				claw > braid > cloudburst thunderbolt / Dissident > fire ethereal
			**|
			
			| ROTATION COMMUNICATION FOR VORTEX
			/if (${validate_cast[FALSE, spell, "${VortexNuke}", ${Target.ID}]}) {
				/call core_cast2 "${VortexNuke}" spell ${Target.ID} FALSE
			}
			
			/if (${validate_cast[FALSE, spell, "${ClawNuke}", ${Target.ID}]}) {
				/call core_cast2 "${ClawNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${BraidNuke}", ${Target.ID}]}) {
				/call core_cast2 "${BraidNuke}" spell ${Target.ID} FALSE
			}

			/if (${Me.PctMana} > 30 && ${Target.PctHPs} > 20) {
				/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) {
					/call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
				}
			} else {
				/if (${validate_cast[FALSE, spell, "${CloudburstNuke}", ${Target.ID}]}) {
					/call core_cast2 "${CloudburstNuke}" spell ${Target.ID} FALSE
				}
			}

			/if (${validate_cast[FALSE, spell, "${FireEtherealNuke}", ${Target.ID}]}) {
				/call core_cast2 "${FireEtherealNuke}" spell ${Target.ID} FALSE
			}
		}
		
		/call wiz_manage_aggro
		/call wiz_mana_check
	}
	
|-	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) && ${BegTimer}==0) /call BegForCure
	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: wiz_mana_check
|---------------------------------------------------------------------------- 
sub wiz_mana_check

	| if mana is below the puller check limit
	/if (${Spawn[${Me.Name} pccorpse radius 50].ID}) /return

	/call bag_mod_rod
	/call use_mod_rod
	
	/if (${Me.PctMana} < 80) {
		/if (${validate_cast[FALSE, item, "${ChestItemName}", ${Me.ID}]}) /call core_cast2 "${ChestItemName}" item 0 FALSE
	}
	/if (${Me.PctMana} < 70 && ${Me.XTarget}) {
		/if (${validate_cast[FALSE, spell, "${GambitSpell}", ${Me.ID}]}) /call core_cast2 "${GambitSpell}" spell 0 FALSE
		/return
	}
	/if (${Me.PctMana} < 70) {
		/if (${validate_cast[FALSE, alt, "Harvest of Druzzil", ${Me.ID}]}) /call core_cast2 "Harvest of Druzzil" alt 0 FALSE
		/return
	}
	/if (${Me.PctMana} < 45 || ${Me.PctMana} < ${Limit}) {

		/if (!${validate_cast[FALSE, FIND, "${HarvestSpell1}", ${Me.ID}]}) {
			/if (${validate_cast[FALSE, alt, "Forceful Rejuvenation", ${Me.ID}]}) {
				/call core_cast2 "Forceful Rejuvenation" alt 0 FALSE
			}
			/if (${validate_cast[FALSE, FIND, "${HarvestSpell1}", ${Me.ID}]}) {
				/call core_cast2 "${HarvestSpell1}" FIND 0 FALSE
			}
		} else {
			/call core_cast2 "${HarvestSpell1}" FIND 0 FALSE
		}
	}

/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub wiz_burn_routine

	/if (${burnRotation} == 1) {
		/if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) {
			/call core_cast2 "${TwincastSpell}" spell 0 FALSE
		}
		/if (${validate_cast[FALSE, alt, "Focus of Arcanum", ${Me.ID}]}) {
			/call core_cast2 "Focus of Arcanum" alt 0 FALSE
		}
		/if (${validate_cast[FALSE, alt, "Fury of the Gods", ${Me.ID}]}) {
			/call core_cast2 "Fury of the Gods" alt 0 FALSE
		}
		/if (${validate_cast[FALSE, alt, "Arcane Fury", ${Me.ID}]}) {
			/call core_cast2 "Arcane Fury" alt 0 FALSE
		}
		/if (${validate_cast[FALSE, spell, "Spire of Arcanum", ${Me.ID}]}) {
			/call core_cast2 "Spire of Arcanum" spell 0 FALSE
		}
		/if (!${Me.Buff[${TwincastSpell}].ID}) {
			/varcalc burnRotation ${burnRotation} + 1
		}
	} else /if (${burnRotation} == 2) {
		/if (${validate_cast[FALSE, alt, "Arcane Destruction", ${Me.ID}]}) {
			/call core_cast2 "Arcane Destruction" alt 0 FALSE
		}
		/if (${validate_cast[FALSE, alt, "Frenzied Devastation", ${Me.ID}]}) {
			/call core_cast2 "Frenzied Devastation" alt 0 FALSE
		}
		/if (!${Me.Song[Twincast Effect].ID} && !${Me.Buff[${TwincastSpell}].ID} && !${Me.Buff[Improved Twincast].ID} && !${Me.Buff[Improved Twincast ${ImprovedTwincastRank}].ID}) {
			/if (${validate_cast[FALSE, alt, "Improved Twincast", ${Me.ID}]}) {
				/call core_cast2 "Improved Twincast" alt 0 FALSE
			}
		}
		/if (!${Me.Buff[Improved Twincast].ID} && !${Me.Buff[Improved Twincast ${ImprovedTwincastRank}].ID}) {
			/varcalc burnRotation ${burnRotation} - 1
		}
	}

/return

Sub wiz_self_buff_check(bool _debug)
	/declare CastCheck			int local 0
	
	/if (${Me.XTarget}) /return
	
	/if (${validate_cast[FALSE, FIND, "${FamiliarBuff}", ${Me.ID}]}) {
		/call core_cast2 "${FamiliarBuff}" FIND 0 FALSE
		/varset CastCheck 1
	}

	/if (!${Me.Buff[${SelfHPBuffName}].ID} && !${Me.Buff[${SelfHPBuff}].ID}) {
		/if (${validate_cast[FALSE, FIND, "${SelfHPBuff}", ${Me.ID}]}) {
			/call core_cast2 "${SelfHPBuff}" FIND 0 FALSE
			/varset CastCheck 1
		}
	}

	/if (${validate_cast[FALSE, spell, "${SelfRune1}", ${Me.ID}]}) {
		/call core_cast2 "${SelfRune1}" spell 0 FALSE
		/varset CastCheck 1
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: ManageAggro
|---------------------------------------------------------------------------- 
Sub wiz_manage_aggro
	
	/if (${Target.PctHPs} < 35) /return
	/if (${Me.Buff[Twincast].ID}) /return

	/if (${Target.PctAggro} > 30) {
		/if (${validate_cast[FALSE, FIND, "${JoltSpell}", ${Target.ID}]}) {
			/call core_cast2 "${JoltSpell}" FIND ${Target.ID} FALSE
		}
	}
	/if (${Target.PctAggro} > 30) {
		/if (${validate_cast[FALSE, alt, "Mind Crash", ${Target.ID}]}) {
			/call core_cast2 "Mind Crash" alt ${Target.ID} FALSE
		}
	}
/return

|----------------------------------------------------------------------------
|- SUB: Handle Buff Requests
|----------------------------------------------------------------------------
Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
	/if (${Spawn[pc ${ChatSender}].ID} && ${ChatType.Equal[tell]}) /mqlog ${ChatSender} -- ${ChatText}
	/if (${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}) {
		|-/if (${Select[${ChatText},voice,crack,clarity,kei]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /call SpellQueue ${SingleMana} ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
		|-/if (${Select[${ChatText},haste,speed,zing]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /call SpellQueue ${SingleHaste} ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
	}
/return 
