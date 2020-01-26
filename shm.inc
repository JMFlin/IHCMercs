|----------------------------------------------------------------------------
|- SUB: shm_main
|----------------------------------------------------------------------------
Sub shm_main
	/call shm_single_target_heals
/return
|----------------------------------------------------------------------------
|- SUB: Single Heal
|---------------------------------------------------------------------------- 
Sub shm_single_target_heals
	/declare _worstHurtId int local 0

	/call get_heal_target 85
	/varset _worstHurtId ${Macro.Return}
	
	/if (${_worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${RecklessHeal1}", ${_worstHurtId}]}) {
			/call core_cast2 "${RecklessHeal1}" spell ${_worstHurtId} FALSE
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: HealthToMana
|---------------------------------------------------------------------------- 
Sub shm_health_to_mana
	/if (${Me.PctHPs}>=${AACanniMinHP} && ${Me.AltAbilityReady[Cannibalization]}) {
		/call AANow ${Me.AltAbility[Cannibalization].ID} ${Me.ID}
		/delay 20 !${Me.Casting.ID}
	} else /if (${Me.PctHPs}>=${CanniMinHP} && ${Me.SpellReady[${CanniSpell}]}) {
		/call SpellQueue "${CanniSpell}" ${Me.ID}
		/delay ${Math.Calc[(${Spell[${CanniSpell}].MyCastTime}/100)+5].Int} !${Me.Casting.ID}
	}
/return
|----------------------------------------------------------------------------
|- SUB: DoNamed
|---------------------------------------------------------------------------- 
Sub shm_do_named
|-Shaman AAs for nameds on tank
	/if (${Me.AltAbilityReady[Ancestral Aid]}) {
		/call AANow ${Me.AltAbility[Ancestral Aid].ID} ${assistid}
		/delay 4
	}
	/if (${Me.AltAbilityReady[Union of Spirits]}) {
		/call AANow ${Me.AltAbility[Union of Spirits].ID} ${assistid}
		/delay 2
	}
	/if (${Me.AltAbilityReady[Spirit Guard]}) {
		/call AANow ${Me.AltAbility[Spirit Guard].ID} ${assistid}
		/delay 3
	}
	/if (${Me.AltAbilityReady[Call of the Ancients]}) {
		/call AANow ${Me.AltAbility[Call of the Ancients].ID} ${assistid}
		/delay 3
	}
	/if (${Me.AltAbilityReady[Spiritual Blessing]}) {
		/call AANow ${Me.AltAbility[Spiritual Blessing].ID} ${Me.ID}
		/delay 3
	}
	/if (${Me.AltAbilityReady[Fundament: Third Spire of Ancestors]}) {
		/call AANow ${Me.AltAbility[Fundament: Third Spire of Ancestors].ID} ${Me.ID}
		/delay 4
	}
	/if (${Me.AltAbilityReady[Dampen Resistance]}) {
		/call AANow ${Me.AltAbility[Dampen Resistance].ID} ${Me.ID}
		/delay 4
	}
	/if (${Me.AltAbilityReady[Fleeting Spirit]}) {
		/call AANow ${Me.AltAbility[Fleeting Spirit].ID} ${Me.ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Rabid Bear]}) {
		/call AANow ${Me.AltAbility[Rabid Bear].ID} ${Me.ID}
		/delay 3
	}
	/if (${Me.AltAbilityReady[Ancestral Guard]}) {
		/call AANow ${Me.AltAbility[Ancestral Guard].ID} ${Me.ID}
		/delay 5
	}
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
|- SUB: CC
|---------------------------------------------------------------------------- 
Sub CC
	/declare x int local 0
	
	/for x 1 to ${Me.XTarget}

		/target id ${Me.XTarget[${x}].ID}

		/if (${Target.Distance}<=55 && !${Target.Mezzed.ID} && !${Me.Casting.ID} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.Type.Equal[NPC]} && ${Target.LineOfSight} && ${Me.AltAbilityReady[Virulent Paralysis]} && !${Target.Buff[Virulent Paralysis].ID} && !${Target.Rooted.ID} && ${Me.GroupAssistTarget.ID}!=${Target.ID} && ${Target.CurrentHPs}>95) {
			/face fast
			/alt act ${Me.AltAbility[Virulent Paralysis].ID}
			/delay 20 !${Me.AltAbilityReady[Virulent Paralysis]}
		}
	/next x
/return
|----------------------------------------------------------------------------
|- SUB: DebuffMobs
|---------------------------------------------------------------------------- 
Sub shm_debuff
	/declare x int local 0

	/if (!${Me.Casting.ID} && !${Me.Moving} && ${SpawnCount[npc radius ${AssistRange} zradius ${AssistRangeZ}]}>2 && ${NearestSpawn[los npc radius ${AssistRange} zradius ${AssistRangeZ}].ID}) {

		/target id ${NearestSpawn[los npc radius ${AssistRange} zradius ${AssistRangeZ}].ID}
		/delay 40 ${Target.ID}==${NearestSpawn[los npc radius ${AssistRange} zradius ${AssistRangeZ}].ID}

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

	/for x 1 to ${Me.XTarget}

		/target id ${Me.XTarget[${x}].ID}
		/delay 5 ${Target.ID}==${Me.XTarget[${x}].ID}
		/if (!${Me.Casting.ID} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.Distance}<200 && ${Target.LineOfSight}) {
			/if (${Me.AltAbilityReady[Malaise]} && !${Target.Buff[Malosinata].ID} && !${Target.Buff[${Malo}].ID} && !${Target.Maloed.ID}) {
				/alt act ${Me.AltAbility[Malaise].ID}
				/delay 5s !${Me.Casting.ID}
				/delay 5s !${Me.AltAbilityReady[Malaise]}
			}
			/delay 1
			/if (${Me.AltAbilityReady[Turgur's Swarm]} && !${Target.Buff[Turgur's Insects].ID} && ${Target.Distance}<120) {
				/alt act ${Me.AltAbility[Turgur's Swarm].ID}
				/delay 5s !${Me.Casting.ID}
				/delay 5s !${Me.AltAbilityReady[Turgur's Swarm]}
			}
			/delay 1
		}
	/next x
/return
|----------------------------------------------------------------------------
|- SUB: AANDisc 
|---------------------------------------------------------------------------- 
Sub shm_aa_and_disc
	|/if (!${FindItem[=${EpicSpiritStaff}].TimerReady} && !${Me.Casting.ID} && ${Me.XTarget[1].Distance}<=75) {
	|	/useitem "${EpicSpiritStaff}"
	|	/delay 5
	|}
	/if (!${Me.Buff[Roar of the Lion].ID} && !${Me.Buff[Dissident Roar].ID} && ${Me.CurrentMana}>${Spell[${DichoSpell}].Mana} && !${Me.Casting.ID} && ${Me.SpellReady[${DichoSpell}]} && ${Me.XTarget[1].Distance}<=75) {
		/call SpellQueue "${DichoSpell}" ${Me.ID}
		/delay 5
	}

	/if (${Me.AltAbilityReady[Spirit Guardian]}) {
		/call AANow ${Me.AltAbility[Spirit Guardian].ID} ${assistid}
		/delay 3
	}
/return
|----------------------------------------------------------------------------
|- SUB: Combatdps
|---------------------------------------------------------------------------- 
Sub shm_combat

	/if (${Target.PctHPs}<=${AutoAssistAt} && ${Target.Distance}<=${AssistRange} && ${Target.Type.Equal[NPC]}) {
		/if (${Me.AltAbilityReady[Focus of Arcanum]}) {
			/call AANow ${Me.AltAbility[Focus of Arcanum].ID} ${Me.ID}
		}
		|- DPS
		/if (${Me.PctMana}>=${Manatonuke}) {
			/if (${DoDot} && ${Me.SpellReady[${CurseDoT1}]} && !${Target.Buff[${CurseDoT1}].ID} && (${Target.PctHPs}>=10 || ${Target.Named})) {
				/call SpellQueue "${CurseDoT1}" ${Target.ID}
				/delay 5
			}
|-			/if (${DoDot} && ${Me.SpellReady[${CurseDoT1}]} && !${Target.Buff[${CurseDoT2}].ID} && (${Target.PctHPs}>=10 || ${Target.Named})) {
|-				/call SpellQueue "${CurseDoT2}" ${Target.ID}
|-				/delay 5
|-			}
			/if (${DoDot} && ${Me.SpellReady[${ChaoticPoisonDoT}]} && !${Target.Buff[${ChaoticPoisonDoT}].ID} && ${Target.PctHPs}>=5 && ${Target.Named}) {
				/call SpellQueue "${ChaoticPoisonDoT}" ${Target.ID}
				/delay 5
			}
			/if (${DoDot} && ${Me.SpellReady[${FastDiseaseDoT}]} && !${Target.Buff[${FastDiseaseDoT}].ID} && (${Target.PctHPs}>=10) || ${Target.Named}) {
				/call SpellQueue "${FastDiseaseDoT}" ${Target.ID}
				/delay 5
			}
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: BuffGroup 
|---------------------------------------------------------------------------- 
Sub shm_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) /return
	/if (${Me.Casting.ID}) /return

	/if (${Me.XTarget}) /return
	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return

	/for _count 1 to ${Group}

		/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		/if (${Me.XTarget}) {
			/call ${Me.Class.ShortName.Lower}_load_spellbar
			/return
		}
		/if (${Mode} !=3 ) /return
		/if (${Group.Member[${_count}].Distance}<100 && !${Group.Member[${_count}].OtherZone}) {



			/if (!${Me.Book[${FocusSpell}]}) {
			
			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Focus.ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${SingleFocusSpell}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid}) {
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
					/if (${validate_cast[FALSE, spell, ${FocusSpell}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${FocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
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
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${RunSpeedBuff}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${RunSpeedBuff}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid}) {
					/if (${validate_cast[FALSE, spell, ${RunSpeedBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${RunSpeedBuff}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${RunSpeedBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${RunSpeedBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${RunSpeedBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${CasterSpeedBuff}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${CasterSpeedBuff}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid} && !${Select[${Group.Member[${_count}].Class.ShortName},WAR,ROG,BER,MNK]}) {
					/if (${validate_cast[FALSE, spell, ${CasterSpeedBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${CasterSpeedBuff}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/if (${Group.Member[${_count}].ID}==${Group.MainTank.ID}) {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GrowthBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GrowthBuff}].Stacks" "tmpstackcheck" "bool"
					/if (!${tmpbuffid} && !${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${GrowthBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${GrowthBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
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
				/if (${Group.Member[${_count}].ID}==${Group.MainTank.ID}) {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${SlowProcBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${SlowProcBuff}].Stacks" "tmpstackcheck" "bool"
					/if (!${tmpbuffid} && !${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${SlowProcBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${SlowProcBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
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
				/if (${Group.Member[${_count}].ID}==${Group.MainTank.ID}) {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${AllianceBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${AllianceBuff}].Stacks" "tmpstackcheck" "bool"
					/if (!${tmpbuffid} && !${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${AllianceBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${AllianceBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
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
	/if (${CastCheck}) /call ${Me.Class.ShortName.Lower}_load_spellbar
/return
|----------------------------------------------------------------------------
|- SUB: ConfigHeal
|---------------------------------------------------------------------------- 
Sub shm_config_heal
	/if (${Me.XTarget}>2 || ${Me.XTarget[1].Named}) {
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
