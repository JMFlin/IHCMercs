|----------------------------------------------------------------------------
|- SUB: shm_main
|----------------------------------------------------------------------------
Sub shm_main

|**
	/if (${powerLevel}) {
		/call check_for_corpse FALSE
		/return
	} 
	**|
	/call shm_self_buffs
	/call shm_group_buffs
	/call check_for_corpse FALSE

	/call get_heal_target 90
	/varset worstHurtId ${Macro.Return}
	
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${RecklessHeal1}", ${worstHurtId}]}) {
			/call core_cast2 "${RecklessHeal1}" spell ${worstHurtId} FALSE
		}
	}

	/if (${Me.PctHPs} >= 40 && ${Me.PctMana} < 70) {
		/if (${validate_cast[FALSE, alt, "Cannibalization", ${Me.ID}]}) {
			/call core_cast2 "Cannibalization" alt 0 FALSE
		}
	}

	/if (!${Me.Song[${GroupRenewalHoT}].ID}) {
		/if (${validate_cast[FALSE, spell, "${GroupRenewalHoT}", ${Me.ID}]}) {
			/call core_cast2 "${GroupRenewalHoT}" spell ${Me.ID} FALSE
		}
	}
	
	/while (${Me.XTarget}) {
		/call move_to_camp

		/call get_heal_target 85
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${RecklessHeal1}", ${worstHurtId}]}) {
				/call core_cast2 "${RecklessHeal1}" spell ${worstHurtId} FALSE
			}
		}

		/call get_target
		
		/if (!${validate_combat[${Target.ID}]}) /continue

		/if (${check_for_named[FALSE]}) /call shm_do_named

		/if (${Target.Named}) {
			/if (!${Target.Maloed.ID} && !${Target.Buff[${MaloName}].ID}) {
				/if (${validate_cast[FALSE, FIND, "${Malo}", ${Target.ID}]}) /call core_cast2 "${Malo}" FIND ${Target.ID} FALSE
			}
		}
		
		/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {		
			/if (${validate_cast[FALSE, FIND, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}

		/call pet_attack ${Target.ID}

	
		|**
		/call get_target
		/if (!${Target.Crippled.ID} && !${Target.Buff[${CrippleSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {		
			/if (${validate_cast[FALSE, spell, "${CrippleSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Crippling \ar ${Target.Name} \ax with =>> \ag ${CrippleSpell} \ax <<=
				/call core_cast2 "${CrippleSpell}" spell ${Target.ID} FALSE
				/call check_cast_events "${CrippleSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		**|
		
		/call get_heal_target 85
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${RecklessHeal2}", ${worstHurtId}]}) {
				/call core_cast2 "${RecklessHeal2}" spell ${worstHurtId} FALSE
			}
		}

		/if (${Me.XTarget} > 1) /call shm_debuff_xtarget
		
		/call get_heal_target 85
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${RecklessHeal1}", ${worstHurtId}]}) {
				/call core_cast2 "${RecklessHeal1}" spell ${worstHurtId} FALSE
			}
		}

		/call get_heal_target 50
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, alt, "Union of Spirits", ${worstHurtId}]}) {
				/call core_cast2 "Union of Spirits" alt ${worstHurtId} FALSE
			}
		}

		
		/call shm_aa_and_disc

		/call get_heal_target 85
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${RecklessHeal3}", ${worstHurtId}]}) {
				/call core_cast2 "${RecklessHeal3}" spell ${worstHurtId} FALSE
			}
		} else {
			/if (!${Me.Song[${GroupRenewalHoT}].ID}) {
				/if (${validate_cast[FALSE, spell, "${GroupRenewalHoT}", ${Me.ID}]}) {
					/call core_cast2 "${GroupRenewalHoT}" spell ${Me.ID} FALSE
				}
			}
		}

		/call get_target
		/if (${Target.Named}) {
			/if (!${Target.Buff[${ChaoticPoisonDoT}].ID}) {		
				/if (${validate_cast[FALSE, spell, "${ChaoticPoisonDoT}", ${Target.ID}]}) {
					/call core_cast2 "${ChaoticPoisonDoT}" spell ${Target.ID} FALSE
				}
			}
		}

		/if (${Me.PctHPs} >= 50 && ${Me.PctMana} < 30) {
			/if (${validate_cast[FALSE, alt, "Cannibalization", ${Me.ID}]}) {
				/call core_cast2 "Cannibalization" alt 0 FALSE
			}
		}

		/if (${check_hurt[FALSE, group, 50]} >= 1) {
			/if (${validate_cast[FALSE, spell, "${InterventionHeal}", ${Me.ID}]}) /call core_cast2 "${InterventionHeal}" spell ${Me.ID} FALSE
		}

		/call get_target
		/if (${check_hurt[FALSE, group, 90]} >= 3) {
			/if (${validate_cast[FALSE, spell, "${TwinHealNuke}", ${Target.ID}]}) /call core_cast2 "${TwinHealNuke}" spell ${Group.MainTank.ID} FALSE
			/if (${validate_cast[FALSE, spell, "${AESpiritualHeal}", ${Group.MainTank.ID}]}) /call core_cast2 "${AESpiritualHeal}" spell ${Group.MainTank.ID} FALSE
		}

		/if (${check_hurt[FALSE, group, 70]} >= 2) {
			/if (${validate_cast[FALSE, spell, "${RecourseHeal}", ${Me.ID}]}) /call core_cast2 "${RecourseHeal}" spell ${Me.ID} FALSE
		}
		DEBUG Spirit Guard ${validate_cast[FALSE, alt, "Spirit Guardian", ${Group.MainTank.ID}]}
		DEBUG Ancestral Aid ${validate_cast[FALSE, alt, "Ancestral Aid", ${Me.ID}]}
		DEBUG Call of the Ancients ${validate_cast[FALSE, alt, "Call of the Ancients", ${Me.ID}]}

	}

/return
|----------------------------------------------------------------------------
|- SUB: Single Heal
|---------------------------------------------------------------------------- 
Sub shm_single_target_heals

	
/return
|----------------------------------------------------------------------------
|- SUB: HealthToMana
|---------------------------------------------------------------------------- 
Sub shm_health_to_mana
	/if (${Me.PctHPs} >= 40) {
		/if (${validate_cast[FALSE, alt, "Cannibalization", ${Me.ID}]}) {
			/call core_cast2 "Cannibalization" alt 0 FALSE
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: debuff_xtarget
|---------------------------------------------------------------------------- 
Sub shm_debuff_xtarget
	/declare _count int local 1

	/for _count 1 to ${Me.XTarget}

		/if (${immuneSet.Contains[${Me.XTarget[${_count}].ID}]}) /continue

		/if (${Me.XTarget[${_count}].ID} != ${Target.ID}) {
			/target id ${Me.XTarget[${_count}].ID}
			/delay 1s ${Me.XTarget[${_count}].ID} == ${Target.ID}
			/delay 5
		}

		/if (${Target.Distance} > 200) /return
		/if (!${Target.Type.Equal[NPC]}) /return
		
		/if (${Target.Named}) {
			/if (!${Target.Maloed.ID} && !${Target.Buff[${Malo}].ID}) {
				/if (${validate_cast[FALSE, spell, "${Malo}", ${Target.ID}]}) /call core_cast2 "${Malo}" spell ${Target.ID} FALSE
			}
		}

		| How will you handle the AA?
		/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			
			/if (${validate_cast[FALSE, FIND, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Attack debuff \ar ${Target.Name} \ax with =>> \ag ${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}

	/next _count
/return
|----------------------------------------------------------------------------
|- SUB: DoNamed
|---------------------------------------------------------------------------- 
Sub shm_do_named
	
	|-Shaman AAs for nameds on tank

	| Main Tank
	/if (${validate_cast[FALSE, alt, "Spirit Guardian", ${Group.MainTank.ID}]}) /call core_cast2 "Spirit Guardian" alt ${Group.MainTank.ID} FALSE
	/if (${validate_cast[FALSE, alt, "Ancestral Aid", ${Me.ID}]}) /call core_cast2 "Ancestral Aid" alt 0 FALSE

|**
		${Me.AltAbilityReady["Call of the Ancients"]}
		${Spell["Call of the Ancients"].MyRange}
		${Spell["Call of the Ancients"].Mana}
		${Spell["Call of the Ancients"].SpellType.Equal[Beneficial]}
**|

	| Group and Wards
	/if (${validate_cast[FALSE, alt, "Call of the Ancients", ${Me.ID}]}) /call core_cast2 "Call of the Ancients" alt ${Me.ID} FALSE
	/if (${validate_cast[FALSE, alt, "Spire of Ancestors", ${Me.ID}]}) /call core_cast2 "Spire of Ancestors" alt 0 FALSE

	
	| Self Buffs
	/if (${validate_cast[FALSE, alt, "Ancestral Guard", ${Me.ID}]}) /call core_cast2 "Ancestral Guard" alt 0 FALSE
	/if (${validate_cast[FALSE, alt, "Spiritual Blessing", ${Me.ID}]}) /call core_cast2 "Spiritual Blessing" alt 0 FALSE
	/if (${validate_cast[FALSE, alt, "Dampen Resistance", ${Me.ID}]}) /call core_cast2 "Dampen Resistance" alt 0 FALSE
	/if (${validate_cast[FALSE, alt, "Fleeting Spirit", ${Me.ID}]}) /call core_cast2 "Fleeting Spirit" alt 0 FALSE
	/if (${validate_cast[FALSE, alt, "Rabid Bear", ${Me.ID}]}) /call core_cast2 "Rabid Bear" alt 0 FALSE
	/if (${validate_cast[FALSE, alt, "Focus of Arcanum", ${Me.ID}]}) /call core_cast2 "Focus of Arcanum" alt 0 FALSE

/return
|----------------------------------------------------------------------------
|- SUB: SingleCure
|----------------------------------------------------------------------------
Sub shm_single_cure(int cureid)
	/varset CureTimer 10s
	/if (${Me.AltAbilityReady[Radiant Cure]}) {
		/call AANow ${Me.AltAbility[Radiant Cure].ID} ${cureid}
	} else /if (${Me.SpellReady[${CureSpell}]}) {
		/call SpellQueue "${CureSpell}" ${cureid}
	}
	/varset CureMemberCount 0
	/varset CureMemberID 0
/return
|----------------------------------------------------------------------------
|- SUB: GroupCure
|----------------------------------------------------------------------------
Sub shm_group_cure(int cureid)
	/varset CureTimer 10s
	/if (${Me.AltAbilityReady[Purified Spirits]} && ${Me.ID}==${cureid}) {
		/call AANow ${Me.AltAbility[Purified Spirits].ID} ${cureid}
	} else /if (${Me.AltAbilityReady[Radiant Cure]}) {
		/call AANow ${Me.AltAbility[Radiant Cure].ID} ${cureid}
	}
	/varset CureMemberCount 0
	/varset CureMemberID 0
/return
|----------------------------------------------------------------------------
|- SUB: shm_cc
|---------------------------------------------------------------------------- 
Sub shm_cc
	/declare _count int local 0
	
	/for _count 1 to ${Me.XTarget}

		/target id ${Me.XTarget[${_count}].ID}

		/if (${Target.Distance} <= 55 && !${Target.Mezzed.ID} && ${Target.CurrentHPs} > 95) {
			/face fast
			/if (${validate_cast[FALSE, alt, "Virulent Paralysis", ${Target.ID}]}) {
				/call core_cast2 "Virulent Paralysis" alt ${Target.ID} FALSE
			}
		}
	/next _count
/return
|----------------------------------------------------------------------------
|- SUB: DebuffMobs
|---------------------------------------------------------------------------- 
Sub shm_debuff
	/declare _count int local 0
|**
	/if (${SpawnCount[npc radius ${assistRange} zradius ${assistRangeZ}]}>2 && ${NearestSpawn[los npc radius ${assistRange} zradius ${assistRangeZ}].ID}) {

		/target id ${NearestSpawn[los npc radius ${assistRange} zradius ${assistRangeZ}].ID}
		/delay 1s ${Target.ID}==${NearestSpawn[los npc radius ${assistRange} zradius ${assistRangeZ}].ID}

		/if (${Me.AltAbilityReady[Wind of Malaise]} && !${Target.Buff[${Malo}].ID} && !${Target.Maloed.ID}) {
			/alt act ${Me.AltAbility[Wind of Malaise].ID}
			/delay 5s !${Me.Casting.ID}
			/delay 5s !${Me.AltAbilityReady[Wind of Malaise]}
		} 

		/if (${Me.AltAbilityReady[Turgur's Virulent Swarm]} && !${Target.Buff[Turgur's Insects].ID}) {
			/alt act ${Me.AltAbility[Turgur's Virulent Swarm].ID}
			/delay 5s !${Me.Casting.ID}
			/delay 5s !${Me.AltAbilityReady[Turgur's Virulent Swarm]}
		}
	}
**|
	/for _count 1 to ${Me.XTarget}

		/target id ${Me.XTarget[${_count}].ID}
		/delay 5 ${Target.ID}==${Me.XTarget[${_count}].ID}
		/delay 1
		/if (${Me.AltAbilityReady[Malaise]} && !${Target.Buff[Malosinata].ID} && !${Target.Buff[${Malo}].ID} && !${Target.Maloed.ID}) {
			/alt act ${Me.AltAbility[Malaise].ID}
			/delay 5s !${Me.Casting.ID}
			/delay 5s !${Me.AltAbilityReady[Malaise]}
		}
		
		/call get_heal_target 85
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${RecklessHeal1}", ${worstHurtId}]}) {
				/call core_cast2 "${RecklessHeal1}" spell ${worstHurtId} FALSE
			}
		}
		
		/call get_heal_target 85
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${RecklessHeal2}", ${worstHurtId}]}) {
				/call core_cast2 "${RecklessHeal2}" spell ${worstHurtId} FALSE
			}
		}

		/target id ${Me.XTarget[${_count}].ID}
		/delay 5 ${Target.ID}==${Me.XTarget[${_count}].ID}
		/delay 1
		/if (${Me.AltAbilityReady[Turgur's Swarm]} && !${Target.Buff[Turgur's Insects].ID} && ${Target.Distance}<120) {
			/alt act ${Me.AltAbility[Turgur's Swarm].ID}
			/delay 5s !${Me.Casting.ID}
			/delay 5s !${Me.AltAbilityReady[Turgur's Swarm]}
		}
		/delay 1
	/next _count
/return

|----------------------------------------------------------------------------
|- SUB: AANDisc 
|---------------------------------------------------------------------------- 
Sub shm_aa_and_disc

	/if (!${FindItem["Blessed Spiritstaff of the Heyokah"].TimerReady} && ${Me.XTarget[1].Distance} <= 75) {
		/if (${validate_cast[FALSE, item, "Blessed Spiritstaff of the Heyokah", ${Me.ID}]}) {
			/call core_cast2 "Blessed Spiritstaff of the Heyokah" item 0 FALSE
		}
	}

	/call get_target

	/if (${Target.Type.Equal[NPC]} && ${Target.Distance} <= 75) {
		/target id ${Group.MainTank.ID}
		/delay 1s ${Target.ID} == ${Group.MainTank.ID}
		/delay 5
		/if (!${Target.Buff[${DichoSpell}].ID}) {
			/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Group.MainTank.ID}]}) {
				/call core_cast2 "${DichoSpell}" spell ${Group.MainTank.ID} FALSE
			}
		}
	}

	/if (${validate_cast[FALSE, spell, "Spirit Guardian", ${Group.MainTank.ID}]}) {
		/call core_cast2 "Spirit Guardian" spell ${Group.MainTank.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: Combatdps
|---------------------------------------------------------------------------- 
Sub shm_combat

	

	
/return
|----------------------------------------------------------------------------
|- SUB: BuffGroup 
|---------------------------------------------------------------------------- 
Sub shm_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) /return
	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return
	/if (${Me.XTarget}) /return
	/if (${useMerc}) {
		/if (${Mercenary.State.Equal[DEAD]} || ${Mercenary.State.Equal[SUSPENDED]}) /continue
	}
	

	/for _count 0 to ${Group}

		/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		/if (${Me.XTarget}) {
			/call ${Me.Class.ShortName.Lower}_load_spellbar
			/return
		}
		/if (${Mode} !=3 ) /return

		/if (${Group.Member[${_count}].OtherZone}) /continue

		/if (!${Me.Book[${FocusSpell}]}) {
			
			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Focus.ID" "tmpfocusid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${SingleFocusSpell}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${SingleFocusSpell}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid} && !${tmpfocusid}) {
					/if (${validate_cast[FALSE, spell, ${SingleFocusSpell}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${SingleFocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${SingleFocusSpell}].ID}) {
					/if (${validate_cast[FALSE, spell, ${SingleFocusSpell}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${SingleFocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}
		} else {

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {

				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Focus.ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${FocusSpell}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid} && ${Me.Book[${FocusSpell}]} && ${Me.CurrentMana}>${Spell[${FocusSpell}].Mana} && !${Me.Casting.ID}) {
					/if (${validate_cast[FALSE, spell, ${FocusSpell}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${FocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${FocusSpell}].ID}) {
					/if (${validate_cast[FALSE, spell, ${FocusSpell}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${FocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${RunSpeedBuffName}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${RunSpeedBuffName}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid}) {
					/if (${validate_cast[FALSE, FIND, ${RunSpeedBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${RunSpeedBuff}" FIND ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${RunSpeedBuffName}].ID}) {
					/if (${validate_cast[FALSE, FIND, ${RunSpeedBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${RunSpeedBuff}" FIND ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]} && ${Select[${Group.Member[${_count}].Class.ShortName},WAR,ROG,BER,MNK,SHD,PAL,BRD]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${HasteSpell}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${HasteSpell}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid}) {
					/if (${validate_cast[FALSE, FIND, ${HasteSpell}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${HasteSpell}" FIND ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${HasteSpell}].ID}) {
					/if (${validate_cast[FALSE, FIND, ${HasteSpell}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${HasteSpell}" FIND ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].ID} != ${Group.MainTank.ID}) /continue

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GrowthBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GrowthBuff}].Stacks" "tmpstackcheck" "bool"
					
					
					
					/if (!${tmpbuffid} && ${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${GrowthBuff}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${GrowthBuff}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
				
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${GrowthBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${GrowthBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${GrowthBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {

					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${SlowProcBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${SlowProcBuff}].Stacks" "tmpstackcheck" "bool"
					
					

					/if (!${tmpbuffid} && ${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${SlowProcBuff}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${SlowProcBuff}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
				
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${SlowProcBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${SlowProcBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${SlowProcBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${AllianceBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${AllianceBuff}].Stacks" "tmpstackcheck" "bool"
					
					

					/if (!${tmpbuffid} && ${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${AllianceBuff}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${AllianceBuff}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
				
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${AllianceBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${AllianceBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${AllianceBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

		}
	/next _count
	|- Delete variable's
	/if (${Defined[tmpbuffid]}) /deletevar tmpbuffid
	/if (${Defined[tmpskinid]}) /deletevar tmpskinid
	/if (${Defined[tmpsymbolid]}) /deletevar tmpsymbolid
	/if (${Defined[tmpaegoid]}) /deletevar tmpaegoid
	/if (${Defined[tmpstackcheck]}) /deletevar tmpstackcheck

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/docommand /dgt \aw Done Buffing
	}
	
/return

|----------------------------------------------------------------------------
|- SUB: BuffSelf
|---------------------------------------------------------------------------- 
Sub shm_self_buffs
	/declare CastCheck int local 0

	/if (!${Me.Pet.ID}) {
		/if (${validate_cast[FALSE, spell, "${PetSpell}", ${Me.ID}]}) {
			/call core_cast2 "${PetSpell}" spell 0 FALSE
			/varset CastCheck 1
		}
	}
	/if (${validate_cast[FALSE, alt, "Preincarnation", ${Me.ID}]}) {
		/call core_cast2 "Preincarnation" alt 0 FALSE
		/varset CastCheck 1
	}
	|/if (${validate_cast[FALSE, alt, "Visionary's Unity", ${Me.ID}]}) {
	|	/call core_cast2 "Visionary's Unity" alt 0 FALSE
	|	/varset CastCheck 1
	|}
	/if (${validate_cast[FALSE, spell, "${GroupHealProcBuff}", ${Me.ID}]}) {
		/call core_cast2 "${GroupHealProcBuff}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	|**
	/if (!${Spell[${Me.Aura[1]}].ID} && ${Me.AltAbilityReady[${ShamanAura}]}) {
		/alt act ${Me.AltAbility[${ShamanAura}].ID}
		/delay 5
		/varset CastCheck 1
	} else /if (${UsePet} && !${Me.Pet.ID} && ${Cast.Status.Equal[I]} && ${Me.Book[${PetSpell}]} && ${Me.CurrentMana}>${Spell[${PetSpell}].Mana}) {
		/call SpellQueue "${PetSpell}" 0
		/varset CastCheck 1
	} else /if (!${Me.Buff[${GroupHealProcBuff}].ID} && !${Me.Casting.ID} && ${Spell[${GroupHealProcBuff}].Stacks} && ${Me.Book[${GroupHealProcBuff}]} && ${Me.CurrentMana}>${Spell[${GroupHealProcBuff}].Mana}) {
		/call SpellQueue "${GroupHealProcBuff}" 0
		/varset CastCheck 1
	} else /if (${Me.AltAbilityReady[Preincarnation]} && ${Me.AltAbility[Preincarnation].Rank}>=2 && !${Me.Buff[Preincarnation].ID}) {
		/alt act ${Me.AltAbility[Preincarnation].ID}
		/delay 15
		/varset CastCheck 1
	}
	/if (!${Me.Buff[${Me.Focus.ID}].ID}) /call BuffGroupMember "${FocusSpell}" ${Group.Member[0].ID}
	|-else /if (${Me.AltAbilityReady[Visionary's Unity]} && !${Me.Buff[Pack of Aina].ID}) {
|-		/alt act ${Me.AltAbility[Visionary's Unity].ID}
|-		/delay 15
|-	}
**|
	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}
/return
|----------------------------------------------------------------------------
|- SUB: ConfigHeal
|---------------------------------------------------------------------------- 
Sub shm_config_heal
	/if (${Me.XTarget}>2 || ${check_for_named[FALSE]}) {
		/if (${TankHealPoint}!=95) {
			/varset TankHealPoint 95
			/varset GroupHealPoint 85
			/varset BigHealPoint 80
		}
	} else /if (${Me.XTarget[1].Level}>=${Me.Level}) {
		/if (${TankHealPoint}!=85) {
			/varset TankHealPoint 85
			/varset GroupHealPoint 80
			/varset BigHealPoint 70
		}
	} else /if (${Me.XTarget[1].Level}>=${Math.Calc[${Me.Level}-5]}) {
		/if (${TankHealPoint}!=80) {
			/varset TankHealPoint 80
			/varset GroupHealPoint 75
			/varset BigHealPoint 60
		}
	} else {
		/if (${TankHealPoint}!=70) {
			/varset TankHealPoint 70
			/varset GroupHealPoint 75
			/varset BigHealPoint 60
		}
	}
	
/return
|-------------------------------------------------------------------------------------
|- SUB: Rez Check
|-------------------------------------------------------------------------------------
Sub RezCheck
    /declare RezID int local
	/declare RezName string local
	
    /if (${Spawn[pccorpse noalert 3 group radius 100 zradius 50].ID} && !${Me.Combat} && !${Me.XTarget[1].ID}) {
		/hidecorpse npc
		/varset RezID ${Spawn[pccorpse noalert 3 group radius 100 zradius 50].ID}
		/varset RezName ${Spawn[pccorpse noalert 3 group radius 100 zradius 50].Name}
		/target id ${RezID}
		/delay 5 ${Target.ID}==${RezID}
		/if (${Target.Distance}>25) /corpse
		/delay 5 ${Target.Distance}<25
		/if (${Me.AltAbilityReady[Rejuvenation of Spirit]}) {
			/docommand /dgt \ag Rezzing ${RezName}
			/alt act 2051
			/delay 6s !${Me.Casting.ID}
		} 
	}

	/if (${Spawn[pccorpse noalert 3 group radius 100 zradius 50].ID} && ${Me.XTarget[1].ID}) {
		/hidecorpse npc
		/varset RezID ${Spawn[pccorpse noalert 3 group radius 100 zradius 50].ID}
		/varset RezName ${Spawn[pccorpse noalert 3 group radius 100 zradius 50].Name}
		/target id ${RezID}
		/delay 5 ${Target.ID}==${RezID}
		/if (${Target.Distance}>25) /corpse
		/delay 5 ${Target.Distance}<25
		/if (${Me.AltAbilityReady[Call of the Wild]}) {
			/docommand /dgt \ag Battle rezzing ${RezName}
			/alt act 404
			/delay 6s !${Me.Casting.ID}
		} 
	}
/return
|----------------------------------------------------------------------------
|- SUB: Symbol - HP Buff Single use
|----------------------------------------------------------------------------
Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
	/if (${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}) {
		/if (${Select[${ChatText},Cure,cure,CURE,RC,Radiant,GC]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<200)) /call SingleCure ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
	}
/return
|----------------------------------------------------------------------------
|- SUB: Event_WornOff
|----------------------------------------------------------------------------
Sub Event_WornOff
	/doevents flush WornOff
/return 
|----------------------------------------------------------------------------
|- SUB: Event GroupChange
|----------------------------------------------------------------------------
Sub Event_GroupChange

/return
