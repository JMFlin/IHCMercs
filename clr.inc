|----------------------------------------------------------------------------
|- SUB: ManualPullCamping
|---------------------------------------------------------------------------- 
Sub clr_main
	
	/if (${powerLevel}) {
		/call check_for_corpse FALSE
		/return
	} 

	/call get_heal_target 90
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Remedy1}", ${worstHurtId}]}) {
			/call core_cast2 "${Remedy1}" spell ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 90
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Remedy2}", ${worstHurtId}]}) {
			/call core_cast2 "${Remedy2}" spell ${worstHurtId} FALSE
		}
	}

	/call check_for_corpse FALSE
	/call clr_group_buffs
	/call clr_self_buffs
	/call clr_combat_tank_buffs
	|!${Me.Song[${GroupElixirSpell}].ID}
	/if (${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID}) {
		/if (${validate_cast[FALSE, spell, "${GroupElixirSpell}", ${Me.ID}]}) {
			/call core_cast2 "${GroupElixirSpell}" spell ${Me.ID} FALSE
		}
	}

	/while (${Me.XTarget}) {

		/if (${validate_tank_heal[70]}) {
			/if (${validate_cast[FALSE, spell, "${WardSpell}", ${Group.MainTank.ID}]}) {
				/call core_cast2 "${WardSpell}" spell ${Group.MainTank.ID} FALSE
			}
		}
		
		/call get_heal_target 90
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Remedy1}", ${worstHurtId}]}) {
				/call core_cast2 "${Remedy1}" spell ${worstHurtId} FALSE
			}
		}

		/call get_heal_target 90
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Remedy2}", ${worstHurtId}]}) {
				/call core_cast2 "${Remedy2}" spell ${worstHurtId} FALSE
			}
		}

		/call get_heal_target 75
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Intervention1}", ${worstHurtId}]}) {
				/call core_cast2 "${Intervention1}" spell ${worstHurtId} FALSE
			}
		}

		/if (!${Target.Buff[${PromisedHeal}].ID}) {
			/if (${validate_tank_heal[70]}) {
				/if (${validate_cast[FALSE, spell, "${PromisedHeal}", ${Group.MainTank.ID}]}) {
					/call core_cast2 "${PromisedHeal}" spell ${Group.MainTank.ID} FALSE
				}
			}
		}

		/if (!${Target.Buff[${WardSpell}].ID}) {
			/if (${validate_tank_heal[70]}) {
				/if (${validate_cast[FALSE, spell, "${WardSpell}", ${Group.MainTank.ID}]}) {
					/call core_cast2 "${WardSpell}" spell ${Group.MainTank.ID} FALSE
				}
			}
		}

		/call get_heal_target 75
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Intervention2}", ${worstHurtId}]}) {
				/call core_cast2 "${Intervention2}" spell ${worstHurtId} FALSE
			}
		}

		/call get_heal_target 75
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Intervention3}", ${worstHurtId}]}) {
				/call core_cast2 "${Intervention3}" spell ${worstHurtId} FALSE
			}
		}

		/if (${check_hurt[FALSE, group, 85]} >= 3) {
			/if (${validate_cast[FALSE, spell, "${GroupHealSpell1}", ${Me.ID}]}) /call core_cast2 "${GroupHealSpell1}" spell ${Me.ID} FALSE
		}

		/call Gquery ${EverQuest.Server.Lower}_${Group.MainTank.Name.Lower} "Me.Song[${SingleElixirSpell}].ID" "elixirHeal" "int"
		
		/if (!${elixirHeal}) {
			/if (${validate_tank_heal[95]}) {
				/if (${validate_cast[FALSE, spell, "${SingleElixirSpell}", ${Group.MainTank.ID}]}) {
					/call core_cast2 "${SingleElixirSpell}" spell ${Group.MainTank.ID} FALSE
				}
			}
		}
	}
	
	/if (${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID}) {
		/if (${validate_cast[FALSE, spell, "${GroupElixirSpell}", ${Me.ID}]}) {
			/call core_cast2 "${GroupElixirSpell}" spell ${Me.ID} FALSE
		}
	}

|	/call cures
	/doevents
	
/return

Sub clr_self_buffs
	/declare CastCheck			int local 0

	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) /return

	/if (${Me.XTarget}) /return

	/if (!${Me.Buff[${SelfBuff}].ID}) {
		/if (${validate_cast[FALSE, spell, ${SelfBuff}, ${Me.ID}]}) {
			/call core_cast2 "${SelfBuff}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (!${Me.Buff[${Retaliation}].ID}) {
		/if (${validate_cast[FALSE, spell, ${Retaliation}, ${Me.ID}]}) {
			/call core_cast2 "${Retaliation}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (!${Me.Buff[${TankBuff}].ID}) {
		/if (${validate_cast[FALSE, spell, ${TankBuff}, ${Me.ID}]}) {
			/call core_cast2 "${TankBuff}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/docommand /dgt \aw Done Buffing
	}

/return
|-------------------------------------------------------------------------
|- SUB: ConfigHeal
|---------------------------------------------------------------------------- 
Sub clr_config_heal
	/if (${Select[${Zone.ID},795,796]}==0 && !${Raid.Members}) {
		/if (${Me.XTarget}>4 || ${Me.XTarget[1].Named}) {
			/if (${tankhealpoint}!=95) {
				/varset tankhealpoint 95
				/varset grouphealpoint 95
				/varset bighealpoint 95
			}
		} else /if (${Me.XTarget[1].Level}>=${Me.Level}) {
			/if (${tankhealpoint}!=85) {
				/varset tankhealpoint 95
				/varset grouphealpoint 95
				/varset bighealpoint 95
			}
		} else /if (${Me.XTarget[1].Level}>=${Math.Calc[${Me.Level}-5]}) {
			/if (${tankhealpoint}!=80) {
				/varset tankhealpoint 95
				/varset grouphealpoint 95
				/varset bighealpoint 95
			}
		} else {
			/if (${tankhealpoint}!=70) {
				/varset tankhealpoint 95
				/varset grouphealpoint 95
				/varset bighealpoint 95
			}
		}
	} else /if (${tankhealpoint}!=${tbmhealpoint} && !${Raid.Members}) {
		/varset healpoint ${tbmhealpoint}
		/varset tankhealpoint ${tbmhealpoint}
		/varcalc grouphealpoint ${tbmhealpoint}-5
		/varcalc bighealpoint ${tbmhealpoint}-10
	} else /if (${tankhealpoint}!=${raidhealpoint} && ${Raid.Members}) {
		/varset healpoint ${raidhealpoint}
		/varset tankhealpoint ${raidhealpoint}
		/varcalc grouphealpoint ${raidhealpoint}-5
		/varcalc bighealpoint ${raidhealpoint}-10
	}
/return

Sub clr_cures
	/declare _count			int local 0
	/for _count 1 to ${Group}
		/if (!${${Group.Member[1].Name.Lower}_TotalCounters}) /continue

		/if (${${Group.Member[1].Name.Lower}_CountersDisease}) /echo Use Disease cure
		/if (${${Group.Member[1].Name.Lower}_CountersCurse})	/echo Use Curse cure
		/if (${${Group.Member[1].Name.Lower}_CountersPoison}) 	/echo Use Poison cure
		/if (${${Group.Member[1].Name.Lower}_CountersCorruption}) /echo Use Corruption cure

	/next _count
		
/return	
|----------------------------------------------------------------------------
|- SUB: group_buffs
|---------------------------------------------------------------------------- 
Sub clr_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) /return

	/if (${Me.XTarget}) /return
	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return

	/for _count 0 to ${Group}

		/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		/if (${Me.XTarget}) {
			/call ${Me.Class.ShortName.Lower}_load_spellbar
			/return
		}
		/if (${Mode} !=3 ) /return

		/if (${Group.Member[${_count}].Distance}<${Spell[${HPBuff}].MyRange} && !${Group.Member[${_count}].OtherZone} && !${Me.Casting.ID}) {

			/if (!${Me.Book[${GroupHPBuff}]}) {

				/if (${Group.Member[${_count}].Type.Equal[PC]}) {

					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${HPBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Skin.ID" "tmpskinid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Symbol.ID" "tmpsymbolid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Aego.ID" "tmpaegoid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${HPBuff}].Stacks" "tmpstackcheck" "bool"
					/if (${tmpstackcheck} && !${tmpaegoid} && !${tmpbuffid} && ${Me.Book[${HPBuff}]} && ${Me.CurrentMana}>${Spell[${HPBuff}].Mana} && !${Me.Casting.ID}) {
						/if (${validate_cast[FALSE, spell, ${HPBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${HPBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
					/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
					/delay 1s
					/if (!${Target.Buff[${HPBuff}].ID}) {
						/if (${validate_cast[FALSE, spell, ${HPBuff}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${HPBuff}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
				}
			} else {
				
				/if (${Group.Member[${_count}].Type.Equal[PC]}) {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GroupHPBuff}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Skin.ID" "tmpskinid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Symbol.ID" "tmpsymbolid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Aego.ID" "tmpaegoid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GroupHPBuff}].Stacks" "tmpstackcheck" "bool"
					/if (${tmpstackcheck} && !${tmpaegoid} && !${tmpbuffid}) {
						/if (${validate_cast[FALSE, spell, ${GroupHPBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${GroupHPBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
					/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
					/delay 1s
					/if (!${Target.Buff[${GroupHPBuff}].ID}) {
						/if (${validate_cast[FALSE, spell, ${GroupHPBuff}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${GroupHPBuff}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GroupVieBuff}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GroupVieBuff}].Stacks" "tmpstackcheck" "bool"
				/if (${tmpstackcheck} && !${tmpbuffid}) {
					/if (${validate_cast[FALSE, spell, ${GroupVieBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${GroupVieBuff}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${GroupVieBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${GroupVieBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${GroupVieBuff}" spell ${Group.Member[${_count}].ID} FALSE
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
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${TankBuffMatch}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${TankBuff}].Stacks" "tmpstackcheck" "bool"
					/if (!${tmpbuffid} && !${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${TankBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${TankBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]} && ${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${TankBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${TankBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${TankBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}
			
			/if (${Group.Member[${_count}].ID} == ${Group.MainTank.ID}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${DivineBuff}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${DivineBuff}].Stacks" "tmpstackcheck" "bool"
				/if (!${tmpbuffid} && !${tmpstackcheck}) {
					/if (!${Target.Buff[${DivineBuff}].ID}) {
					/if (${validate_cast[FALSE, spell, ${DivineBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${DivineBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
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
|- SUB: combat_tank_buffs
|---------------------------------------------------------------------------- 
Sub clr_combat_tank_buffs

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
	/if (!${Target.Buff[${TankBuff}].ID} && ${Target.PctHPs} > 90) {
		/if (${validate_cast[FALSE, spell, ${TankBuff}, ${Group.MainTank.ID}]}) {
			/call core_cast2 "${TankBuff}" spell ${Group.MainTank.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: single_target_heals
|---------------------------------------------------------------------------- 
Sub clr_single_target_heals
	


/return
|----------------------------------------------------------------------------
|- SUB: group_heals
|---------------------------------------------------------------------------- 
Sub clr_group_heals


/return
	

|-Group Healing
 |   /if (${HurtMember}>=${grouphealcount} && ${Me.AltAbilityReady[Beacon of Life]} && ${Group}) {
|		/call AANow ${Me.AltAbility[Beacon of Life].ID} ${Me.ID}
|	} else /if (${HurtMember}>=${grouphealcount} && ${Me.SpellReady[${groupfastheal}]}) {
|		/call SpellQueue "${groupfastheal}" ${Me.ID}
|	} else /if (${HurtMember}>=${grouphealcount} && ${Me.SpellReady[${groupheal}]} && ${NoCures}!=1) {
|		/call SpellQueue "${groupheal}" ${Me.ID}
|	} else /if (${HurtMember}>=${grouphealcount} && ${Me.SpellReady[${grouphealnocure}]} && ${NoCures}==1) {
|		/call SpellQueue "${grouphealnocure}" ${Me.ID}
|	} else /if (${Me.PctHPs}<=${grouphealpoint}) {
|		/varset healpoint ${grouphealpoint}
|		/call HealQueue ${Me.ID}
|	} else /if ((${usepromheals}==1) && (${PromisedTimer}==0) && (${Group.Member[${assistname}]${TnKCond}Distance}<=${promhealrange}) && ${Me.XTarget[1].ID} && ${Group.Member[${assistname}]${TnKCond}PctHPs}>=1 && ${Me.GemTimer[${promheal}]}==0 && (${Group.Member[${assistname}]${TnKCond}PctHPs}>${bighealpoint})) {
|		/call SpellQueue "${promheal}" ${assistid}
|		/if ((${Macro.Return.Equal[CAST_SUCCESS]}) || (${Macro.Return.Equal[CAST_TAKEHOLD]})) /varset PromisedTimer 21s
|	} else /if ((${Group.Member[${assistname}]${TnKCond}Distance}<=${healspellrange}) && (${Group.Member[${assistname}]${TnKCond}PctHPs}<=${tankhealpoint}) && ${Group.Member[${assistname}]${TnKCond}PctHPs}>=1) {
|		/varset healpoint ${tankhealpoint}
|		/call HealQueue ${assistid}
|	} else /if ((${Group.Member[${worsthurtname}]${GrPCond}Distance}<=${healspellrange}) && (${worsthp}<=${grouphealpoint} || ${petworsthp}<=${grouphealpoint}) && ${Group.Member[${worsthurtname}]${GrPCond}PctHPs}>=1) {
|		/varset healpoint ${grouphealpoint}
|		/call HealQueue ${worstHurtId}
|	} else /if ((${Me.Corrupted.ID} || ${Me.Snared.ID}) && ${NoCures}!=1 && (${Me.AltAbilityReady[Purify Soul]} || ${Me.AltAbilityReady[Group Purify Soul ]} || ${Me.AltAbilityReady[Purified Spirits]}) && ${CureTimer}==0 && !${Me.Casting.ID} && ${CureOther}) {
|		/call OtherCure ${Me.ID}
|	} else /if (${Target.Type.Equal[PC]} && ${Target.BuffsPopulated}==TRUE && ${NoCures}!=1 && (${Target.Corrupted.ID} || ${Target.Snared.ID} || ${Target.Mezzed.ID} || ${Target.Charmed.ID}) && (${Me.AltAbilityReady[Purify Soul]} || ${Me.AltAbilityReady[Group Purify Soul ]}) && ${CureTimer}==0 && !${Me.Casting.ID} && ${CureOther}) {
|		/call OtherCure ${Target.ID}
|	} else /if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID}) && ${NoCures}!=1 && (${Me.AltAbilityReady[Radiant Cure]} || ${Me.AltAbilityReady[Purify Soul]} || ${Me.AltAbilityReady[Group Purify Soul ]} || ${Me.AltAbilityReady[Purified Spirits]}) && ${CureTimer}==0 && !${Me.Casting.ID}) {
|		/call GroupCure ${Me.ID}
|	} else /if (${Target.Type.Equal[PC]} && ${Target.BuffsPopulated}==TRUE && ${NoCures}!=1 && (${Target.Poisoned.ID} || ${Target.Diseased.ID} || ${Target.Cursed.ID}) && (${Me.AltAbilityReady[Radiant Cure]} || ${Me.AltAbilityReady[Purify Soul]} || ${Me.AltAbilityReady[Group Purify Soul ]}) && ${CureTimer}==0 && !${Me.Casting.ID}) {
|		/call GroupCure ${Target.ID}
|	} else /if (${Target.Buff[Gift of Living Death].ID} && ${CureTimer}==0 && !${Me.Casting.ID}) {
|||		/call SingleCure ${Target.ID}
	|} else /if ((${DivineBuffOn}==1 )&& (${DivineBuffRecast}==1) && (!${Me.Casting.ID}) && (${Spell[${DivineBuff}].Range}>${Group.Member[${assistname}]${TnKCond}Distance}) && (${Group.Member[${assistname}]${TnKCond}PctHPs}>=1) && (!${Group.Member[${assistname}]${TnKCond}Hovering}) && (${Group.Member[${assistname}]${TnKCond}PctHPs}>${tankhealpoint}) && ${bufftimer}==0) {
	|		/call DivineUsage
|	} else /if ((${Me.PctMana}>=${Manatonuke}) && (${Me.XTarget[1].ID}) && (!${Raid.Members}) && (${UseMelee}==1 || ${UseReverseDS}==1)) {
|		/call Offense
|	} else /if (${CureCount} && ${CureID}) {
|		/call GroupCure ${CureID}
|	}
|	/varset GrPCond .

|----------------------------------------------------------------------------
|- SUB: BuffCheck
|----------------------------------------------------------------------------
Sub BuffCheck
	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (${SpawnCount[pccorpse group raid ${setMaxRezRange}]}) /return

	/if (${Me.Buff[Spiritual Vi].ID}) /blockspell add me ${Spell[${Me.Buff[Spiritual Vi]}].ID}
	/if (${Me.Buff[Focus].ID}) /blockspell add me ${Spell[${Me.Buff[Focus]}].ID}
	/if (!${Me.Buff[${SelfBuff}].ID} && !${Me.Casting.ID} && ${Spell[${SelfBuff}].Stacks} && ${usedruid}==0 && ${Me.Book[${SelfBuff}]} && ${Me.CurrentMana}>${Spell[${SelfBuff}].Mana}) {
		/call SpellQueue "${SelfBuff}" ${Me.ID}
	} else /if (!${Me.Buff[${GroupHealProcBuff}].ID} && !${Me.Casting.ID} && ${Spell[${GroupHealProcBuff}].Stacks} && ${Me.Book[${GroupHealProcBuff}]} && ${Me.CurrentMana}>${Spell[${GroupHealProcBuff}].Mana}) {
		/call SpellQueue "${GroupHealProcBuff}" ${Me.ID}
	} else /if (!${Me.Aego.ID} && !${Me.Skin.ID} && !${Me.Symbol.ID} && ${Me.Book[${GroupBuff}]} && !${Spell[${Me.Buff[${GroupBuff}]}].ID} && ${Me.CurrentMana}>${Spell[${GroupBuff}].Mana}) {
		/call SpellQueue "${GroupBuff}" ${Me.ID}
	} else /if (!${Me.Casting.ID} && ${Spell[${SymbolBuff}].Range}>${Spawn[${SymbolBuffRecast}].Distance} && ${Spawn[${SymbolBuffRecast}].ID} && !${Spawn[${SymbolBuffRecast}].Hovering} && ${Me.Book[${SymbolBuff}]} && ${Me.CurrentMana}>${Spell[${SymbolBuff}].Mana} && ${bufftimer}==0) {
		/call SpellQueue "${SymbolBuff}" ${Spawn[${SymbolBuffRecast}].ID}
		/varset SymbolBuffRecast 0
	} else /if (!${Me.Casting.ID} && ${Spell[${HPBuff}].Range}>${Spawn[${HPBuffRecast}].Distance} && ${Spawn[${HPBuffRecast}].ID} && !${Spawn[${HPBuffRecast}].Hovering} && ${Me.Book[${HPBuff}]} && ${Me.CurrentMana}>${Spell[${HPBuff}].Mana} && ${bufftimer}==0) {
		/call SpellQueue "${HPBuff}" ${Spawn[${HPBuffRecast}].ID}
		/varset HPBuffRecast 0
	} else /if (!${Me.Casting.ID} && ${Spell[${TankBuff}].Range}>${Spawn[${ShiningBuffRecast}].Distance} && ${Spawn[${ShiningBuffRecast}].ID} && !${Spawn[${ShiningBuffRecast}].Hovering} && ${Me.Book[${TankBuff}]} && ${Me.CurrentMana}>${Spell[${TankBuff}].Mana} && ${bufftimer}==0) {
		/call SpellQueue "${TankBuff}" ${Spawn[${ShiningBuffRecast}].ID}
		/varset ShiningBuffRecast 0
	}
/return	
|----------------------------------------------------------------------------
|- SUB: DA Logic 
|----------------------------------------------------------------------------
Sub DALogic
	/if (${Me.Song["Touch of the Divine"].ID}) {
		/echo Touch of the Divine detected!
		/removebuff Touch of the Divine
		/delay 5 !${Me.Song["Touch of the Divine"].ID}
    }
	/call AggroCheck
/return
|----------------------------------------------------------------------------
|- SUB: Aggro Check
|----------------------------------------------------------------------------
Sub AggroCheck
	/if (${Me.AltAbilityReady[Divine Peace]}) {
		/call AANow ${Me.AltAbility[Divine Peace].ID}
	} else /if (${Me.AltAbilityReady[Sanctuary]}) {
		/call AANow ${Me.AltAbility[Sanctuary].ID}
	} else /if (${Me.AltAbilityReady[Silent Casting]}) {
		/call AANow ${Me.AltAbility[Silent Casting].ID}
	}
/return
|----------------------------------------------------------------------------
|- SUB: Misc Events
|----------------------------------------------------------------------------
Sub Event_GoMana
	/varset GoMana 1
	/timed 180 /varset GoMana 0
	/call Healgroup
/return

Sub Event_GoMoff
/varset GoMana 0
/return
|----------------------------------------------------------------------------
|- SUB: Symbol - HP Buff Single use
|----------------------------------------------------------------------------
Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
	/if (${Spawn[pc ${ChatSender}].ID} && ${ChatType.Equal[tell]}) /mqlog ${ChatSender} -- ${ChatText}
	/if (${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}) {
		/if (${Select[${ChatText},symbol,Symbol,SYMBOL]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /varset SymbolBuffRecast ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
		/if (${Select[${ChatText},hpbuff,HPBuff,HPBUFF,HpBuff,Hpbuff,HPbuff]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /varset HPBuffRecast ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
		/if (${Select[${ChatText},Shining,shining]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /varset ShiningBuffRecast ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
		/if (${Select[${ChatText},Cure,cure,CURE]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<200)) /call SingleCure ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
		/if (${Select[${ChatText},RC,Radiant,GC]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<200)) /call GroupCure ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
	}
/return
|----------------------------------------------------------------------------
|- SUB: SingleCure
|----------------------------------------------------------------------------
Sub SingleCure(int cureid)
	/varset CureTimer 10s
	/if ((${Me.SpellReady[${bigheal1}]}) && ${Me.CurrentMana}>${Spell[${bigheal1}].Mana}) {
		/call SpellQueue "${bigheal1}" ${cureid}
	} else /if ((${Me.SpellReady[${bigheal2}]}) && ${Me.CurrentMana}>${Spell[${bigheal2}].Mana}) {
		/call SpellQueue "${bigheal2}" ${cureid}
	} else /if (${Me.AltAbilityReady[Purify Soul]} && !${Me.Casting.ID}) {
		/call AANow ${Me.AltAbility[Purify Soul].ID} ${cureid}
	}
/return
|----------------------------------------------------------------------------
|- SUB: GroupCure
|----------------------------------------------------------------------------
Sub GroupCure(int cureid)
	/varset CureTimer 10s
	/if (${Me.AltAbilityReady[Radiant Cure]}) {
		/call AANow ${Me.AltAbility[Radiant Cure].ID} ${cureid}
	} else /if (${Me.AltAbilityReady[Group Purify Soul]}) {
		/call AANow ${Me.AltAbility[Group Purify Soul].ID} ${cureid}
	} else /if (${Me.AltAbilityReady[Purify Soul]} && !${Me.Casting.ID}) {
		/call AANow ${Me.AltAbility[Purify Soul].ID} ${cureid}
	}
	/varset CureCount 0
	/varset CureID 0
/return
|----------------------------------------------------------------------------
|- SUB: OtherCure - Used for curing Corruption, Snare and Mez
|----------------------------------------------------------------------------
Sub OtherCure(int cureid)
	/varset CureTimer 10s
	/if (${Me.ID}==${cureid} && ${Me.AltAbilityReady[Purified Spirits]}) {
		/call AANow ${Me.AltAbility[Purified Spirits].ID} ${cureid}
	} else /if (${Me.AltAbilityReady[Group Purify Soul]}) {
		/call AANow ${Me.AltAbility[Group Purify Soul].ID} ${cureid}
	} else /if (${Me.AltAbilityReady[Purify Soul]} && !${Me.Casting.ID}) {
		/call AANow ${Me.AltAbility[Purify Soul].ID} ${cureid}
	}
/return
|----------------------------------------------------------------------------
|- SUB: Buff Event
|----------------------------------------------------------------------------
Sub Event_Buff(string line, string Mybuff)
    /if (${Mybuff.Equal[${TankBuffMatch}]})	/varset TankBuffRecast 1
	/if (${Mybuff.Equal[${DivineBuff}]}) 	/varset DivineBuffRecast 1
/return
|----------------------------------------------------------------------------
|- SUB: ReactCure - 
|----------------------------------------------------------------------------
Sub Event_ReactCure
	/call GroupCure
/return