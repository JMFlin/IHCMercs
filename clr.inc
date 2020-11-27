|----------------------------------------------------------------------------
|- SUB: Cleric
|----------------------------------------------------------------------------
|**
https://forums.daybreakgames.com/eq/index.php?threads/basic-healing-setup-for-raid-clerics-for-ros-multi-bind-method.247597/

Sequence 1
	Merciful Remedy -> Spiritual Remedy -> Merciful Intervention -> Mystical Intervention -> Virtuous Intervention

Sequence 2 
	Merciful Remedy -> Spiritual Remedy -> Graceful Remedy

Sequence 3
	Syllable of Mending -> Word of Greater Restoration
**|

Sub clr_main
	
	/if (!${Me.XTarget}) /call check_for_corpse FALSE
	/if (!${doNotBuff} && !${timeForBuffs}) /call clr_group_buffs
	/if (!${Me.XTarget}) /call clr_self_buffs
	/if (!${doNotBuff}) /call clr_combat_tank_buffs
	/call clr_mana_check
	/call clr_heal_spam

	|!${Me.Song[${GroupElixirSpell}].ID}
	/if (${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID}) {
		/if (${validate_cast[FALSE, spell, "${GroupElixirSpell}", ${Me.ID}]}) {
			/call core_cast2 "${GroupElixirSpell}" spell ${Me.ID} FALSE
		}
	}

	/while (${Me.XTarget} && ${Mode} == 3) {

		/if (!${doNotBuff}) {
			/if (${validate_tank_heal[70]}) {
				/if (${validate_cast[FALSE, spell, "${WardSpell}", ${Group.MainTank.ID}]}) {
					/call core_cast2 "${WardSpell}" spell ${Group.MainTank.ID} FALSE
				}
			}
		}

		/call clr_heal_spam

		/if (${check_hurt[FALSE, group, 80]} >= 3) {
			/if (${validate_cast[FALSE, spell, "${MendingSplash}", ${Group.MainAssist.ID}]}) {
				/call core_cast2 "${MendingSplash}" spell ${Group.MainAssist.ID} FALSE
			}
		}

		/call get_heal_target 40
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${worstHurtId}]}) {
				/call core_cast2 "${DichoSpell}" spell ${worstHurtId} FALSE
			}
		}

		/call clr_heal_spam_2

		/if (!${doNotBuff}) {
			/if (${validate_tank_heal[90]}) {
				/if (!${Target.Buff[${PromisedHeal}].ID}) {
					/if (${validate_cast[FALSE, spell, "${PromisedHeal}", ${Group.MainTank.ID}]}) {
						/call core_cast2 "${PromisedHeal}" spell ${Group.MainTank.ID} FALSE
					}
				}
			}
		}

		/if (${check_for_named[FALSE]}) {
			/if (${validate_cast[FALSE, item, "${ChestItemName}", ${Me.ID}]}) {
				/call core_cast2 "${ChestItemName}" item 0 FALSE
			}
		}
		/call clr_heal_spam_3
		/call clr_mana_check
		/call move_to_camp
		|**
		/call Gquery ${EverQuest.Server.Lower}_${Group.MainTank.Name.Lower} "Me.Song[${SingleElixirSpell}].ID" "elixirHeal" "int"
		
		/if (!${elixirHeal}) {
			/if (${validate_tank_heal[95]}) {
				/if (${validate_cast[FALSE, spell, "${SingleElixirSpell}", ${Group.MainTank.ID}]}) {
					/call core_cast2 "${SingleElixirSpell}" spell ${Group.MainTank.ID} FALSE
				}
			}
		}
		**|
	}

|	/call clr_cures
	/doevents
	
/return

|----------------------------------------------------------------------------
|- SUB: buffs
|---------------------------------------------------------------------------- 
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

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
	}

/return

|----------------------------------------------------------------------------
|- SUB: Merciful Remedy -> Spiritual Remedy -> Merciful Intervention -> Mystical Intervention -> Virtuous Intervention
|---------------------------------------------------------------------------- 
Sub clr_heal_spam

	/call get_heal_target 85
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Remedy1}", ${worstHurtId}]}) {
			/call core_cast2 "${Remedy1}" spell ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 85
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

/return

|----------------------------------------------------------------------------
|- SUB: Merciful Remedy -> Spiritual Remedy -> Graceful Remedy
|---------------------------------------------------------------------------- 
Sub clr_heal_spam_2

	/call get_heal_target 85
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Remedy1}", ${worstHurtId}]}) {
			/call core_cast2 "${Remedy1}" spell ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 85
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Remedy2}", ${worstHurtId}]}) {
			/call core_cast2 "${Remedy2}" spell ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 85
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Remedy3}", ${worstHurtId}]}) {
			/call core_cast2 "${Remedy2}" spell ${worstHurtId} FALSE
		}
	}

/return

|----------------------------------------------------------------------------
|- SUB: Syllable of Mending -> Word of Greater Restoration
|---------------------------------------------------------------------------- 
Sub clr_heal_spam_3

	/if (${check_hurt[FALSE, group, 80]} >= 3) {
		/if (${validate_cast[FALSE, spell, "${SyllableSpell}", ${Me.ID}]}) /call core_cast2 "${SyllableSpell}" spell ${Me.ID} FALSE
	}

	/if (${check_hurt[FALSE, group, 85]} >= 3) {
		/if (${validate_cast[FALSE, spell, "${GroupWordSpell}", ${Me.ID}]}) /call core_cast2 "${GroupWordSpell}" spell ${Me.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: group_buffs
|---------------------------------------------------------------------------- 
Sub clr_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (!${Group}) /return
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
	}
	/call set_timers
	
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
	}

/return

Sub clr_mana_check
	/call bag_mod_rod
	/call use_mod_rod
/return
|----------------------------------------------------------------------------
|- SUB: cures
|---------------------------------------------------------------------------- 
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