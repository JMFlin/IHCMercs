|----------------------------------------------------------------------------
|- SUB: ManualPullCamping
|---------------------------------------------------------------------------- 
Sub dru_main

|	/call check_for_corpse FALSE
	/call dru_group_buffs
	/call dru_self_buffs
	
	/call get_heal_target 70
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Curavida}", ${worstHurtId}]}) {
			/call core_cast2 "${Curavida}" spell ${worstHurtId} FALSE
		}
	}
	
	/while (${Me.XTarget}) {
		
		/call get_heal_target 70
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Curavida}", ${worstHurtId}]}) {
				/call core_cast2 "${Curavida}" spell ${worstHurtId} FALSE
			}
		}

		/call get_heal_target 55
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Adrenaline}", ${worstHurtId}]}) {
				/call core_cast2 "${Adrenaline}" spell ${worstHurtId} FALSE
			}
		}

		/call get_target
		/if (!${validate_combat[${Target.ID}]}) /continue

		/if (!${Target.Buff[${SingleFrostAtkDebuff}].ID}) {
			/if (${validate_cast[FALSE, spell, "${SingleFrostAtkDebuff}", ${Target.ID}]}) /call core_cast2 "${SingleFrostAtkDebuff}" spell ${Target.ID} FALSE
		}
		
		/call get_heal_target 70
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Curavida}", ${worstHurtId}]}) {
				/call core_cast2 "${Curavida}" spell ${worstHurtId} FALSE
			}
		} else /if (${Me.PctMana} < ${hybridManaLimit}) {
			/call get_target
			/if (!${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]}) {
				/if (${validate_cast[FALSE, spell, "${SnareSpell}", ${Target.ID}]}) {
					/call core_cast2 "${SnareSpell}" spell ${Target.ID} FALSE
					/call check_cast_events "${SnareSpell}" CAST_IMMUNE ${Target.ID}
				}
			}
		}

		/call dru_group_heals

		/call get_heal_target 55
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Adrenaline}", ${worstHurtId}]}) {
				/call core_cast2 "${Adrenaline}" spell ${worstHurtId} FALSE
			}
		}

		/call dru_debuff_xtarget

		/call get_heal_target 70
		/varset worstHurtId ${Macro.Return}
		DEBUG At NBW: ${worstHurtId}, ${Me.PctMana} < ${hybridManaLimit}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Curavida}", ${worstHurtId}]}) {
				/call core_cast2 "${Curavida}" spell ${worstHurtId} FALSE
			}
		} else /if (${Me.PctMana} < ${hybridManaLimit}) {
			/call get_target
			/delay 1s
			/if (!${Target.Buff[${NBW}].ID}) {
				/if (${validate_cast[FALSE, spell, "${NBW}", ${Target.ID}]}) /call core_cast2 "${NBW}" spell ${Target.ID} FALSE
			}
		}
		
		/call get_heal_target 70
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Curavida}", ${worstHurtId}]}) {
				/call core_cast2 "${Curavida}" spell ${worstHurtId} FALSE
			}
		}

		
		/call get_heal_target 55
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Adrenaline}", ${worstHurtId}]}) {
				/call core_cast2 "${Adrenaline}" spell ${worstHurtId} FALSE
			}
		} else /if (${Me.PctMana} < ${hybridManaLimit}) {
			/call get_target
			/delay 5
			/if (!${Target.Buff[${Cyclonic}].ID}) {
				/if (${validate_cast[FALSE, spell, "${Cyclonic}", ${Target.ID}]}) /call core_cast2 "${Cyclonic}" spell ${Target.ID} FALSE
			}
		}
		/call dru_group_heals
		/call dru_combat_tank_buffs
	}

	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: combat_tank_buffs
|---------------------------------------------------------------------------- 
Sub dru_combat_tank_buffs
	
	/declare CastCheck			int local 0

	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return
	/if (!${Me.XTarget} && ${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (!${Me.XTarget} && ${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) /return

	/if (${Group.Member[${Group.MainTank}].Type.Equal[Mercenary]}) {
		/if (${Mercenary.State.Equal[DEAD]} || ${Mercenary.State.Equal[SUSPENDED]}) /return
	}

	/if (${Target.ID} != ${Group.MainTank.ID}) {
		/target id ${Group.MainTank.ID}
		/delay 1s ${Target.ID} == ${Group.MainTank.ID}
	}

	/delay 8
	/if (!${Target.Buff[${Reptile}].ID} && ${Target.PctHPs} > 70) {
		/if (${validate_cast[FALSE, spell, ${Reptile}, ${Group.MainTank.ID}]}) {
			/call core_cast2 "${Reptile}" spell ${Group.MainTank.ID} FALSE
			/varset CastCheck 1
		}
	}
	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: combat 
|---------------------------------------------------------------------------- 
Sub dru_combat
	

/return
|----------------------------------------------------------------------------
|- SUB: debuff_xtarget
|---------------------------------------------------------------------------- 
Sub dru_debuff_xtarget
	/declare _count int local 1

	/if (!${Me.XTarget}) /return
	/if (${Me.XTarget} < 2) /return

	/for _count 1 to ${Me.XTarget}

		/if (${immuneSet.Contains[${Me.XTarget[${_count}].ID}]}) /continue

		/if (${Me.XTarget[${_count}].ID} != ${Target.ID}) {
			/target id ${Me.XTarget[${_count}].ID}
			/delay 1s ${Me.XTarget[${_count}].ID} == ${Target.ID}
			/delay 5
		}

		/if (${Target.Distance} > 200) /return
		/if (!${Target.Type.Equal[NPC]}) /return
		
		| How will you handle the AA?
		/if (!${Target.Buff[${SingleFrostAtkDebuff}].ID}) {
			
			/if (${validate_cast[FALSE, spell, "${SingleFrostAtkDebuff}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Attack debuff \ar ${Target.Name} \ax with =>> \ag ${SingleFrostAtkDebuff} \ax <<=
				/call core_cast2 "${SingleFrostAtkDebuff}" spell ${Target.ID} FALSE
				/call check_cast_events "${SingleFrostAtkDebuff}" CAST_IMMUNE ${Target.ID}
			}
		}

		/delay 1s
	/next _count
/return
|----------------------------------------------------------------------------
|- SUB: group_buffs
|---------------------------------------------------------------------------- 
Sub dru_self_buffs
	/declare CastCheck			int local 0


	/if (!${Me.Book[${SelfUnity}]}) {
		/if (!${Me.Buff[${Mask}].ID}) {
			/if (${validate_cast[FALSE, spell, "${Mask}", ${Me.ID}]}) {
				/call core_cast2 "${Mask}" spell ${Me.ID} FALSE
				/varset CastCheck 1
			}
		}

		/if (!${Me.Buff[${SelfDamageShield}].ID}) {
			/if (${validate_cast[FALSE, spell, "${SelfDamageShield}", ${Me.ID}]}) {
				/call core_cast2 "${SelfDamageShield}" spell ${Me.ID} FALSE
				/varset CastCheck 1
			}
		}
	} else {
		/if (!${Me.Buff[${SelfDamageShield}].ID} || !${Me.Buff[${Mask}].ID}) {
			/if (${validate_cast[FALSE, spell, "${SelfUnity}", ${Me.ID}]}) {
				/call core_cast2 "${SelfUnity}" spell ${Me.ID} FALSE
				/varset CastCheck 1
			}
		}
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}
/return
|----------------------------------------------------------------------------
|- SUB: group_buffs
|---------------------------------------------------------------------------- 

Sub dru_group_buffs
	/declare _count				int local 0
	/declare CastCheck			int local 0

	/if (${Me.XTarget}) /return
	/if (${Me.Casting.ID}) /return

	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) /return
	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return

	/if (${useMerc}) {
		/if (${Mercenary.State.Equal[DEAD]} || ${Mercenary.State.Equal[SUSPENDED]}) /continue
	}
	
	/for _count 0 to ${Group}

		/if (${Group.Member[${_count}].OtherZone}) /continue

		/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		/if (${Me.XTarget}) {
			/call ${Me.Class.ShortName.Lower}_load_spellbar
			/return
		}

		/if (${Mode} != 3) /return

		/if (!${Me.Book[${GroupSkin}]}) {
			
			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Buff[${Skin}].ID" "tmpbuffid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Skin.ID" "tmpskinid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Aego.ID" "tmpaegoid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Spell[${Skin}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpaegoid} && !${tmpbuffid} && !${tmpskinid}) {
					/if (${validate_cast[FALSE, spell, ${Skin}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${Skin}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID} && !${Group.HealerMercCount} && !${Group.Cleric}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${Skin}].ID}) {
					/if (${validate_cast[FALSE, spell, ${Skin}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${Skin}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}
		} else {
			
			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Buff[${GroupSkin}].ID" "tmpbuffid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Skin.ID" "tmpskinid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Aego.ID" "tmpaegoid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Spell[${GroupSkin}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpaegoid} && !${tmpbuffid} && !${tmpskinid}) {
					/if (${validate_cast[FALSE, spell, ${GroupSkin}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${GroupSkin}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID} && !${Group.HealerMercCount} && !${Group.Cleric}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${GroupSkin}].ID}) {
					/if (${validate_cast[FALSE, spell, ${GroupSkin}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${GroupSkin}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}
		}

		/if (${Group.Member[${_count}].Type.Equal[PC]}) {
			/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Buff[${SoW}].ID" "tmpbuffid" "int"
			/call Gquery ${Group.Member[${_count}].Name.Lower} "Spell[${SoW}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck}) {
				/if (${validate_cast[FALSE, spell, ${SoW}, ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${SoW}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			}
		} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${SoW}].ID}) {
					/if (${validate_cast[FALSE, spell, ${SoW}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${SoW}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}
		
		/if (${Mode} != 3) /return

		/if (${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
			
			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Buff[${DamageShield}].ID" "tmpbuffid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Spell[${DamageShield}].Stacks" "tmpstackcheck" "bool"
				/if (!${tmpbuffid} && ${tmpstackcheck}) {
					/if (${validate_cast[FALSE, spell, ${DamageShield}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${DamageShield}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${DamageShield}].ID}) {
					/if (${validate_cast[FALSE, spell, ${DamageShield}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${DamageShield}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Me.Buff[${Reptile}].ID" "tmpbuffid" "int"
				/call Gquery ${Group.Member[${_count}].Name.Lower} "Spell[${Reptile}].Stacks" "tmpstackcheck" "bool"
				/if (!${tmpbuffid} && ${tmpstackcheck}) {
					/if (${validate_cast[FALSE, spell, ${Reptile}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${Reptile}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${Reptile}].ID}) {
					/if (${validate_cast[FALSE, spell, ${Reptile}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${Reptile}" spell ${Group.Member[${_count}].ID} FALSE
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
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: Single Heal
|---------------------------------------------------------------------------- 
Sub dru_single_target_heals

	
/return
|----------------------------------------------------------------------------
|- SUB: HealGroup
|---------------------------------------------------------------------------- 
Sub dru_group_heals

	/if (${check_hurt[FALSE, group, 20]} >= 1) {
		/if (${validate_cast[FALSE, spell, "${Survival}", ${Me.ID}]}) /call core_cast2 "${Survival}" spell ${Me.ID} FALSE
	}

	/if (${check_hurt[FALSE, group, 85]} >= 3) {
		/if (${validate_cast[FALSE, spell, "${Lunasalve}", ${Me.ID}]}) /call core_cast2 "${Lunasalve}" spell ${Me.ID} FALSE
	}

/return