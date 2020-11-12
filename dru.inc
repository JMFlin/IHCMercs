|----------------------------------------------------------------------------
|- SUB: ManualPullCamping
|---------------------------------------------------------------------------- 

|**
Single-target heals
	Revitalization -> Adrenaline Barrage-> Curavida

Group Heals
	Lunasalve
	Survival of the Auspicious
	Wildtender's Survival

Debuffs
	There are several debuffs that need to be placed on every single “main” boss NPC the raid encounters.
	Frostreave Breath - The primary cold debuff. 
	Frostreave breath dramatically reduces armor class and increases cold damage taken by the target.

	It also heals the target’s target.
	Skin to Sumac - Increases fire damage taken by the target. Does not work on all NPCs.

	Glistening Frost - Dramatically decreases the target’s Attack and Armor Class stats. 
	Blessing of Ro (AA)/Vortex of Ro(AA) - Casts the highest rank of Cowl of Ro you have scribed.

	Massive fire debuff/damage increase/debuff. Vortex casts an AE version of the same spell.

	All Druids can cast Blessing of Ro on whatever the raid encounters (including add trash). 
	Save the larger debuffs for bosses and assign one to each Druid to spread the work out.

Nukes
	You can multibind this lineup (in this order):
	Dicho -> Remote Sunblaze -> Cyclonic Roar -> Anabatic Roar -> Winter’s Wildblaze
	Take note that the first two spells in this lineup provide a massive heal as well as top nuke damage for the class. 
	Making frequent use of them essentially fulfills two of your roles perfectly.

Offensive Casts (DoTs)

	Druids have four extremely powerful DoTs that can be utilized during burns. 
	You want to cast as many of these as possible during spell twincast (not ITC). 
	Once spell twincast has faded you can hit ITC and finish your rotation:

	Nature’s Blistering Wrath - Always cast this first
	Horde of Polybiads
	Sunflame
	Chill of the Wildtender - This is a large “doom dot” that triggers a larger DoT when it fades

	You can maintain these on large boss target(s) for as long as your mana/group survivability will allow. 
	Note that these DoTs are incredibly mana intensive and learning to balance your mana usage so you have something left over for healing is key.


Burning
	Twincast (Spell) -> Nature’s Blistering Wrath -> Horde -> Sunflame -> Chill of the Wildtender -> Improved Twincast -> Nuke Weave -> DoT refresh as needed

TODO:
	AAs:
		Rejuvenation of Spirit
		Vortex of Ro
		Wall of Wind
		Wildtender's Surival
		Wildtender's Unity

	Spells:
		Frostreave Breath
		Skin to Sumac
		Glistening Frost

	Add SpellSet for Dots vs Nukes
**|

Sub dru_main

|	/call check_for_corpse FALSE
	/if (!${doNotBuff}) /call dru_group_buffs
	/if (!${doNotBuff}) /call dru_combat_tank_buffs
	/call dru_self_buffs
	/call dru_heal_spam
	
	/if (${validate_cast[FALSE, alt, "Wrath of the Wild", ${Group.MainTank.ID}]}) {
		/call core_cast2 "Wrath of the Wild" alt ${Group.MainTank.ID} FALSE
	}

	/while (${Me.XTarget}) {

		/call dru_heal_spam

		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call dru_burn_routine

		/if (${validate_cast[FALSE, alt, "Group Spirit of the White Wolf", ${Me.ID}]}) {
			/call core_cast2 "Group Spirit of the White Wolf" alt ${Me.ID} FALSE
		}

		/call get_target
		/if (!${validate_combat[${Target.ID}]}) /continue
		
		| Does this work?
		/call get_target
		/if (!${Target.Buff[${Me.AltAbility[Season's Wrath].Rank}].ID}) {
			/if (${validate_cast[FALSE, alt, "Season's Wrath", ${Target.ID}]}) /call core_cast2 "Season's Wrath" alt ${Target.ID} FALSE
		}

		/if (${Target.Named}) { 
			/if (!${Target.Buff[${SingleFrostAtkDebuff}].ID}) {
				/if (${validate_cast[FALSE, spell, "${SingleFrostAtkDebuff}", ${Target.ID}]}) {
					/call core_cast2 "${SingleFrostAtkDebuff}" spell ${Target.ID} FALSE
				}
			}
		}

		/if (!${Target.Buff[${SingleFireAtkDebuff}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${validate_cast[FALSE, FIND, "${SingleFireAtkDebuffSpell}", ${Target.ID}]}) {
				/call core_cast2 "${SingleFireAtkDebuffSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SingleFireAtkDebuffSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		/call dru_heal_spam
		/call dru_group_heals
		/call dru_debuff_xtarget

		/call get_target
		/if (!${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]} && ${doSnare}) {
			/if (${validate_cast[FALSE, FIND, "${SnareSpell}", ${Target.ID}]}) {
				/call core_cast2 "${SnareSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SnareSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		/call dru_heal_spam
		/if (${Me.PctMana} > ${hybridManaLimit}) {
			|**
				ITC -> Dicho -> Remote Sunblaze -> Cyclonic Roar -> Anabatic Roar -> Winter's Wildblaze
			**|

			/if (!${Me.Buff[${TwincastSpell}].ID}) {
				/if (${validate_cast[FALSE, alt, "Improved Twincast", ${Me.ID}]}) {
					/call core_cast2 "Improved Twincast" alt 0 FALSE
				}
			}
			/call get_target
			/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) {
				/call core_cast2 "${Adrenaline}" spell ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, spell, "${RemoteSun}", ${Target.ID}]}) {
				/call core_cast2 "${RemoteSun}" spell ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, spell, "${Cyclonic}", ${Target.ID}]}) {
				/call core_cast2 "${Cyclonic}" spell ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, spell, "${LowerCyclonic}", ${Target.ID}]}) {
				/call core_cast2 "${LowerCyclonic}" spell ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, spell, "${Winter}", ${Target.ID}]}) {
				/call core_cast2 "${Winter}" spell ${Target.ID} FALSE
			}
		}

		/if (${Me.PctMana} > ${hybridManaLimit} && !${Me.Buff[Improved Twincast].ID}) {
			|**
				Spell Twincast -> Nature’s Blistering Wrath -> Horde of Polybiads -> Sunflame -> Chill of the Wildtender
			**|
			/if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) {
				/call core_cast2 "${TwincastSpell}" spell 0 FALSE
			}
			/call get_target
			/if (!${Target.Buff[${NBW}].ID}) {
				/if (${validate_cast[FALSE, spell, "${NBW}", ${Target.ID}]}) {
					/call core_cast2 "${NBW}" spell ${Target.ID} FALSE
				}
			}
			/call dru_heal_spam
			/call get_target
			/if (!${Target.Buff[${DoTSpell1}].ID}) {
				/if (${validate_cast[FALSE, spell, "${DoTSpell1}", ${Target.ID}]}) {
					/call core_cast2 "${DoTSpell1}" spell ${Target.ID} FALSE
				}
			}
			/call dru_heal_spam
			/call get_target
			/if (!${Target.Buff[${Sunflame}].ID}) {
				/if (${validate_cast[FALSE, spell, "${Sunflame}", ${Target.ID}]}) {
					/call core_cast2 "${Sunflame}" spell ${Target.ID} FALSE
				}
			}
			/call dru_heal_spam
			/call get_target
			/if (!${Target.Buff[${Chill}].ID}) {
				/if (${validate_cast[FALSE, spell, "${Chill}", ${Target.ID}]}) {
					/call core_cast2 "${Chill}" spell ${Target.ID} FALSE
				}
			}
		}

		/call dru_group_heals
		
		|**
		else /if (${Me.PctMana} > ${hybridManaLimit}) {
			/call get_target
			/if (${validate_cast[FALSE, alt, "Nature's Bolt", ${Target.ID}]}) {
				/call core_cast2 "Nature's Bolt" alt ${Target.ID} FALSE
			}
		}
		**|

		|**
		else /if (${Me.PctMana} > ${hybridManaLimit}) {
			/call get_target
			/if (${validate_cast[FALSE, alt, "Nature's Fire", ${Target.ID}]}) {
				/call core_cast2 "Nature's Fire" alt ${Target.ID} FALSE
			}
			/if (${validate_cast[FALSE, alt, "Nature's Frost", ${Target.ID}]}) {
				/call core_cast2 "Nature's Frost" alt ${Target.ID} FALSE
			}
		}
		**|
	}

	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: combat_tank_buffs
|---------------------------------------------------------------------------- 
Sub dru_heal_spam
	|**
		(Convergence of Spirits) -> Revitalization -> Adrenaline Barrage-> Curavida
	**|

	/call get_heal_target 60
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0 && ${worstHurtId} == ${Group.MainTank.ID}) {
		/if (${validate_cast[FALSE, alt, "Convergence of Spirits", ${worstHurtId}]}) {
			/call core_cast2 "Convergence of Spirits" alt ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 80
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Revitalization}", ${worstHurtId}]}) {
			/call core_cast2 "${Revitalization}" spell ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 80
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Adrenaline}", ${worstHurtId}]}) {
			/call core_cast2 "${Adrenaline}" spell ${worstHurtId} FALSE
		}
	}

	/call get_heal_target 80
	/varset worstHurtId ${Macro.Return}
	/if (${worstHurtId} > 0) {
		/if (${validate_cast[FALSE, spell, "${Curavida}", ${worstHurtId}]}) {
			/call core_cast2 "${Curavida}" spell ${worstHurtId} FALSE
		}
	}

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

	/delay 5
	/if (!${Target.Buff[${Reptile}].ID} && ${Target.PctHPs} > 70) {
		/if (${validate_cast[FALSE, spell, ${Reptile}, ${Group.MainTank.ID}]}) {
			/call core_cast2 "${Reptile}" spell ${Group.MainTank.ID} FALSE
			/varset CastCheck 1
		}
	}
	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
	}

/return
|----------------------------------------------------------------------------
|- SUB: combat 
|---------------------------------------------------------------------------- 
Sub dru_burn_routine

	/if (${validate_cast[FALSE, alt, "Destructive Vortex", ${Me.ID}]}) {
		/call core_cast2 "Destructive Vortex" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Distant Conflagration", ${Me.ID}]}) {
		/call core_cast2 "Distant Conflagration" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Swarm of Fireflies", ${Group.MainTank.ID}]}) {
		/call core_cast2 "Swarm of Fireflies" alt ${Group.MainTank.ID} FALSE
	}
	| ADD MGB HERE IF IN RAID
	/if (${validate_cast[FALSE, alt, "Spirit of the Wood", ${Group.MainTank.ID}]}) {
		/call core_cast2 "Spirit of the Wood" alt ${Group.MainTank.ID} FALSE
	}
	/if (${validate_cast[FALSE, alt, "Spirit of the Bear", ${Group.MainTank.ID}]}) {
		/call core_cast2 "Spirit of the Bear" alt ${Group.MainTank.ID} FALSE
	}
	/if (${validate_cast[FALSE, alt, "Spire of Nature", ${Group.MainTank.ID}]}) {
		/call core_cast2 "Spire of Nature" alt ${Group.MainTank.ID} FALSE
	}
	/if (${validate_cast[FALSE, alt, "Nature's Fury", ${Me.ID}]}) {
		/call core_cast2 "Nature's Fury" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Nature's Boon", ${Me.ID}]}) {
		/call core_cast2 "Nature's Boon" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Focus of Arcanum", ${Me.ID}]}) {
		/call core_cast2 "Focus of Arcanum" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Improved Twincast", ${Me.ID}]}) {
		/call core_cast2 "Improved Twincast" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Nature's Blessing", ${Me.ID}]}) {
		/call core_cast2 "Nature's Blessing" alt 0 FALSE
	}

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
		
		/if (!${Target.Buff[${SingleFireAtkDebuff}].ID}) {
			
			/if (${validate_cast[FALSE, FIND, "${SingleFireAtkDebuffSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Attack debuff \ar ${Target.Name} \ax with =>> \ag ${SingleFireAtkDebuffSpell} \ax <<=
				/call core_cast2 "${SingleFireAtkDebuffSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SingleFireAtkDebuffSpell}" CAST_IMMUNE ${Target.ID}
			}
		}

		/if (${Target.Named}) { 
			/if (!${Target.Buff[${SingleFrostAtkDebuff}].ID}) {
				/if (${validate_cast[FALSE, spell, "${SingleFrostAtkDebuff}", ${Target.ID}]}) {
					/call core_cast2 "${SingleFrostAtkDebuff}" spell ${Target.ID} FALSE
				}
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
		|/if (!${Me.Buff[${Mask}].ID}) {
		/if (${validate_cast[FALSE, spell, "${Mask}", ${Me.ID}]}) {
			/call core_cast2 "${Mask}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
		|}

		|/if (!${Me.Buff[${SelfDamageShield}].ID}) {
		/if (${validate_cast[FALSE, spell, "${SelfDamageShield}", ${Me.ID}]}) {
			/call core_cast2 "${SelfDamageShield}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
		|}
	} else {
		/if (!${Me.Buff[${SelfDamageShield}].ID} || !${Me.Buff[${Mask}].ID}) {
			/if (${validate_cast[FALSE, spell, "${SelfUnity}", ${Me.ID}]}) {
				/call core_cast2 "${SelfUnity}" spell ${Me.ID} FALSE
				/varset CastCheck 1
			}
		}
	}

	/if (${validate_cast[FALSE, alt, "Protection of the Direwood", ${Me.ID}]}) {
		/call core_cast2 "Protection of the Direwood" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Preincarnation", ${Me.ID}]}) {
		/call core_cast2 "Preincarnation" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Spirit of Eagles", ${Me.ID}]}) {
		/call core_cast2 "Spirit of Eagles" alt 0 FALSE
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
		/if (${Mercenary.State.Equal[DEAD]} || ${Mercenary.State.Equal[SUSPENDED]}) /return
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

		/if (!${druDoNotBuffShm}) {

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

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
					|- This is done becasue a shaman or another druid could have given the buff with a different rank
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${ShmAllianceBuff}].ID" "ShmAllianceRkI" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${ShmAllianceBuff} Rk. II].ID" "ShmAllianceRkII" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${ShmAllianceBuff} Rk. III].ID" "ShmAllianceRkIII" "int"

					/if (!${ShmAllianceRkI} && !${ShmAllianceRkII} && !${ShmAllianceRkIII}) {
						/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${AllianceBuff}].ID" "tmpbuffid" "int"
						/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${AllianceBuff}].Stacks" "tmpstackcheck" "bool"
					
						/if (!${tmpbuffid} && ${tmpstackcheck}) {
							/if (${validate_cast[FALSE, spell, ${AllianceBuff}, ${Group.Member[${_count}].ID}]}) {
								/call core_cast2 "${AllianceBuff}" spell ${Group.Member[${_count}].ID} FALSE
								/varset CastCheck 1
							}
						}
					}
				
			} else /if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
				/if (${Group.Member[${_count}].ID} != ${Target.ID}) /target ${Group.Member[${_count}]}
				/delay 1s
				/if (!${Target.Buff[${AllianceBuff}].ID} && !${Target.Buff[${ShmAllianceBuff}].ID} && !${Target.Buff[${ShmAllianceBuff} Rk. II].ID} && !${Target.Buff[${ShmAllianceBuff} Rk. III].ID}) {
					/if (${validate_cast[FALSE, spell, ${AllianceBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${AllianceBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}
				}
			}

			/if (${Group.Member[${_count}].Type.Equal[PC]}) {
				|- This is done becasue a shaman or another druid could have given the buff with a different rank
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GrowthBuff}].ID" "GrowthBuffRkI" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GrowthBuff} Rk. II].ID" "GrowthBuffRkII" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GrowthBuff} Rk. III].ID" "GrowthBuffRkIII" "int"

				/if (!${GrowthBuffRkI} && !${GrowthBuffRkII} && !${GrowthBuffRkIII}) {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GrowthBuff}].Stacks" "tmpstackcheck" "bool"
					/if (${tmpstackcheck}) {
						/if (${validate_cast[FALSE, spell, ${GrowthBuff}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${GrowthBuff}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
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
	|TODO: Wildtender's Surival
	/if (${check_hurt[FALSE, group, 85]} >= 3) {
		/if (${validate_cast[FALSE, alt, "Blessing of Tunare", ${Me.ID}]}) /call core_cast2 "Blessing of Tunare" alt ${Me.ID} FALSE
	}

	/if (${check_hurt[FALSE, group, 20]} >= 1) {
		/if (${validate_cast[FALSE, spell, "${Survival}", ${Me.ID}]}) /call core_cast2 "${Survival}" spell ${Me.ID} FALSE
	}

	/if (${check_hurt[FALSE, group, 85]} >= 3) {
		/if (${validate_cast[FALSE, spell, "${Lunasalve}", ${Me.ID}]}) /call core_cast2 "${Lunasalve}" spell ${Me.ID} FALSE
	}

/return