|----------------------------------------------------------------------------
|- SUB: bst_main
|---------------------------------------------------------------------------- 
Sub bst_main

	/call engage
	/call bst_self_buff_check
	/call bst_combat

/return
|----------------------------------------------------------------------------
|- SUB: self_buff_check
|---------------------------------------------------------------------------- 
Sub bst_self_buff_check
	/declare CastCheck			int local 0
	
	/if (${Me.XTarget}) /return

	/if (!${Me.Pet.ID}) {
		/if (${validate_cast[FALSE, spell, "${PetSpell}", ${Me.ID}]}) {
			/call core_cast2 "${PetSpell}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${Me.Pet.ID}) {
		/if (!${Me.Pet.Buff[${PetDamageProc}]}) {
			/if (${validate_cast[FALSE, spell, "${PetDamageProc}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetDamageProc}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}
		|**
		/if (!${Me.Pet.Buff[${PetDefenseBuff}]}) {
			/if (${validate_cast[FALSE, spell, "${PetDefenseBuff}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetDefenseBuff}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}
		**|
		/if (!${Me.Pet.Buff[${PetHaste}]}) {
			/if (${validate_cast[FALSE, spell, "${PetHaste}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetHaste}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}
		/if (!${Me.Pet.Buff[${PetOffenseBuff}]}) {
			/if (${validate_cast[FALSE, spell, "${PetOffenseBuff}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetOffenseBuff}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}
	}

	/if (${validate_cast[FALSE, spell, "${FocusSpell}", ${Me.ID}]}) {
		/call core_cast2 "${FocusSpell}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${validate_cast[FALSE, spell, "${ManaRegenBuff}", ${Me.ID}]}) {
		/call core_cast2 "${ManaRegenBuff}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (!${Me.Buff[${PetHasteRecourse}].ID} && ${PetHasteRecourse.NotEqual[NULL]}) {
		/if (${validate_cast[FALSE, spell, "${PetHaste}", ${Me.Pet.ID}]}) {
			/call core_cast2 "${PetHaste}" spell ${Me.Pet.ID} FALSE
			/varset CastCheck 1
		}
	} else /if (${PetHasteRecourse.Equal[NULL]}) {
		/if (${validate_cast[FALSE, spell, "${Haste}", ${Me.ID}]}) {
			/call core_cast2 "${Haste}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${validate_cast[FALSE, spell, "${AtkBuff}", ${Me.ID}]}) {
		/call core_cast2 "${AtkBuff}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}

/return
Sub bst_combat_buffs

/return
|----------------------------------------------------------------------------
|- SUB: combat 
|---------------------------------------------------------------------------- 
Sub bst_combat

	/if (!${validate_combat[${Target.ID}]} ) /return

	/call get_target
	/call engage
	/call pet_attack
	/squelch /attack on

	/call use_skill_melee ${Target.ID} FALSE

	/if (!${Target.Buff[${BloodDoT}].ID}) {
		/if (${validate_cast[FALSE, spell, "${BloodDoT}", ${Target.ID}]}) /call core_cast2 "${BloodDoT}" spell ${Target.ID} FALSE
	}

	/if (${Target.PctHPs} > 30) {
		/if (${validate_cast[FALSE, spell, "${SwarmPet}", ${Target.ID}]}) /call core_cast2 "${SwarmPet}" spell ${Target.ID} FALSE
	}

	/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
		
		/if (${validate_cast[FALSE, FIND, "${SlowSpell}", ${Target.ID}]}) {
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing\ar ${Target.Name} \ax with =>> \ag ${SlowSpell} \ax <<=
			/call core_cast2 "${SlowSpell}" FIND ${Target.ID} FALSE
			/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
		}
	}

	/if (${Me.CombatAbilityReady[${Maul}]}) {
		/if (${validate_cast[FALSE, disc, ${Maul}, ${Target.ID}]}) /call core_cast2 ${Maul} disc ${Target.ID} FALSE
	}

	/if (${Me.AltAbilityReady[Warlord's Fury]} && ${Me.SecondaryPctAggro}>=60) {
		/call AANow ${Me.AltAbility[Warlord's Fury].ID}
	}



	|/if (!${Target.Crippled.ID} && !${Target.Buff[${CrippleSpell1}].ID} && !${Target.Buff[Mental Contortion].ID}) {
	|	/if (${validate_cast[FALSE, spell, "${CrippleSpell1}", ${Target.ID}]}) {
	|		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Crippling \ar ${Target.Name} \ax with =>> \ag ${CrippleSpell1} \ax <<=
	|		/call core_cast2 "${CrippleSpell1}" spell ${Target.ID} FALSE
	|	}
	|} 
	

	/if (!${Target.Buff[${FrozenNuke}].ID}) {
		/if (${validate_cast[FALSE, spell, "${FrozenNuke}", ${Target.ID}]}) /call core_cast2 "${FrozenNuke}" spell ${Target.ID} FALSE
	}
	
	/if (!${Target.Buff[${MaelstromNuke}].ID}) {
		/if (${validate_cast[FALSE, spell, "${MaelstromNuke}", ${Target.ID}]}) /call core_cast2 "${MaelstromNuke}" spell ${Target.ID} FALSE
	}

/return
|----------------------------------------------------------------------------
|- SUB: debuff_xtarget
|---------------------------------------------------------------------------- 
Sub bst_debuff_xtarget
	/declare x int local 1

	/if (!${Me.XTarget}) /return
	/if (${Me.XTarget} < 2) /return

	/for x 1 to ${Me.XTarget}
		
		/if (${If[${Select[${Me.XTarget[${x}].Animation},110,26,32,71,72,111]}, 0, 1]} == 0) /attack off
		/target id ${Me.XTarget[${x}].ID}
		/delay 2s ${Me.XTarget[${x}].ID} == ${Target.ID}
		/delay 2s !${Me.Moving}
		/delay 2s !${Me.Casting}

		/if (${Target.Distance} > 200) /return
		/if (!${Target.Type.Equal[NPC]}) /return
		
		| How will you handle the AA?
		/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${validate_cast[FALSE, FIND, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar${Target.Name} \ax with =>> \ag${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		|/if (!${Target.Crippled.ID} && !${Target.Buff[${CrippleSpell1}].ID} && !${Target.Buff[Mental Contortion].ID}) {
		|	/if (${validate_cast[FALSE, spell, "${CrippleSpell1}", ${Target.ID}]}) {
		|		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Crippling \ar ${Target.Name} \ax with =>> \ag ${CrippleSpell1} \ax <<=
		|		/call core_cast2 "${CrippleSpell1}" spell ${Target.ID} FALSE
		|	}
		|}
		/delay 2s
	/next x
/return
|----------------------------------------------------------------------------
|- SUB: get_aggro 
|---------------------------------------------------------------------------- 
Sub bst_get_aggro

/return

Sub bst_aoe_aggro

/return
|----------------------------------------------------------------------------
|- SUB: single_target_heals
|---------------------------------------------------------------------------- 
Sub bst_single_target_heals
	/declare worstHurtId 		int local 0

	/if (${Spawn[${WorstHurt[group,1,200,FALSE]}].Type.NotEqual[Corpse]} && ${Spawn[${WorstHurt[group,1,200,FALSE]}].PctHPs} < 50) {

		/varset worstHurtId ${Spawn[${WorstHurt[group,1,200,FALSE]}].ID}

		/if (${validate_cast[FALSE, spell, "${HealSpell1}", ${worstHurtId}]}) {
			/call core_cast2 "${HealSpell1}" spell ${worstHurtId} FALSE
			/return
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: BuffGroup
|---------------------------------------------------------------------------- 
Sub bst_buff_group
	/declare _count			int local 0
	/declare CastCheck			int local 0
	
	/if (${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${Yloc},${Xloc},${Zloc}]} > ${autoCampRadius}) /call move_to_camp ${pullAutoCampX} ${pullAutoCampY} ${pullAutoCampZ} ${autoCampRadius}

	/for _count 0 to ${Group}

		/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		/if (${Me.XTarget}) {
			/call ${Me.Class.ShortName.Lower}_load_spellbar
			/return
		}
		/if (${Mode} !=3 ) /return

		/if (${Group.Member[${_count}].Distance}<100 && !${Group.Member[${_count}].OtherZone} && (!${Me.Casting.ID}) && ${DanNet.Peers.Find[${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower}]}) {
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${FocusSpell}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Focus.ID" "tmpfocusid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${FocusSpell}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && ${Me.CurrentMana}>${Spell[${FocusSpell}].Mana} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
				/if (${validate_cast[FALSE, spell, ${FocusSpell}, ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${FocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			}
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${ManaRegenBuff}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${ManaRegenBuff}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && ${Me.Book[${ManaRegenBuff}]} && ${Me.CurrentMana}>${Spell[${ManaRegenBuff}].Mana} && !${Me.Casting.ID}) {
				/if (${validate_cast[FALSE, spell, ${ManaRegenBuff}, ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${ManaRegenBuff}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			}
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${RunSpeedBuff}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${RunSpeedBuff}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && ${Me.Book[${RunSpeedBuff}]} && ${Me.CurrentMana} > ${Spell[${RunSpeedBuff}].Mana}) {
				/if (${validate_cast[FALSE, spell, ${RunSpeedBuff}, ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${RunSpeedBuff}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}		
			}
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${AtkBuff}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${AtkBuff}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && ${Me.CurrentMana} > ${Spell[${AtkBuff}].Mana} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
			|	/if (${validate_cast[FALSE, spell, ${AtkBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${AtkBuff}" spell ${Group.Member[${_count}].ID} FALSE
			|		/varset CastCheck 1
			}
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${Haste}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${Haste}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && ${Me.CurrentMana} > ${Spell[${Haste}].Mana} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
				/if (${validate_cast[FALSE, spell, ${Haste}, ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${Haste}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			}
		}
	/next _count
	|- Delete variable's
	/if (${Defined[tmpbuffid]}) /deletevar tmpbuffid
	/if (${Defined[tmpfocusid]}) /deletevar tmpfocusid
	/if (${Defined[tmpstackcheck]}) /deletevar tmpstackcheck

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}
	
/return
|----------------------------------------------------------------------------
|- SUB: CombatDiscs
|---------------------------------------------------------------------------- 
Sub bst_disc
	/doevents
|---- Combat Buffs
	/if (${DoFerocity} && ${Cast.Status.Equal[I]} && (${Me.SpellReady[${AtkBuff}]}) && (!${Me.Buff[${AtkBuff}].ID})) {
			/call SpellQueue "${AtkBuff}" ${Me.ID}
	}
	
	/if ( ${Target.CurrentHPs}<=${autoAssistAt} && ${Target.ID}==${autotargetid} && ${Target.Distance}<=${assistRange} && ${Ok2Assist}) {
		|- Pet Attack
		/if ((!${Me.Pet.Combat} || ${Pet.Target.ID}!=${autotargetid}) && ${Me.Pet.ID} && ${Target.Type.Equal[NPC]} && ${Target.ID} && ${Target.CurrentHPs}<=${autoAssistAt} && ${UsePet}) {
			/pet attack 
			/pet swarm
		}
		|- Slow
		/if (${DoSlow} && ${Target.CurrentHPs}<=${autoAssistAt} && !${Me.Casting.ID} && ${Target.LineOfSight} && !${Me.Moving} && !${Target.Slowed.ID} && !${Target.Type.Equal[Corpse]}) {
			/if (${Me.AltAbilityReady[Sha's Reprisal]}) {
				/call AANow ${Me.AltAbility[Sha's Reprisal].ID} ${autotargetid}
			} else /if (${Me.SpellReady[${SlowSpell}]}) {
				/call CastSpell "${SlowSpell}" ${autotargetid} dbf
			}
		}	
		|- DPS
		/if (${Me.PctMana}>=${Manatonuke}) {
			/if (${Cast.Status.Equal[I]} && ${DoDot} && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && (${Me.SpellReady[${DoTSpell1}]}) && (!${Target.Buff[${DoTSpell1}].ID})) {
				/call SpellQueue "${DoTSpell1}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${DoDot} && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && (${Me.SpellReady[${DoTSpell2}]}) && (!${Target.Buff[${DoTSpell2}].ID})) {
				/call SpellQueue "${DoTSpell2}" ${autotargetid}
			} else /if (${UseSwarmpet} && ${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${SwarmPet}].RankName}]} && ${Me.CurrentMana}>${Spell[${SwarmPet}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
				/call SpellQueue "${Spell[${SwarmPet}].RankName}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${DichoSpell}].RankName}]} && ${Me.CurrentMana}>${Spell[${DichoSpell}].Mana} && !${Me.Song[Dichotomic Fury].ID} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight} && !${Me.Song[Ruaabri's Fury].ID}) {
				/call SpellQueue "${Spell[${DichoSpell}].RankName}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${NukeSpell1}].RankName}]} && ${Me.PctAggro}<${StopNukeAggro} && ${Target.CurrentHPs}<90 && ${Me.CurrentMana}>${Spell[${NukeSpell1}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
				/call SpellQueue "${Spell[${NukeSpell1}].RankName}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${NukeSpell2}].RankName}]} && ${Me.PctAggro}<${StopNukeAggro} && ${Target.CurrentHPs}<88 && ${Me.CurrentMana}>${Spell[${NukeSpell2}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight} && !${NoDisease}) {
				/call SpellQueue "${Spell[${NukeSpell2}].RankName}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${NukeSpell3}].RankName}]} && ${Me.PctAggro}<${StopNukeAggro} && ${Target.CurrentHPs}<86 && ${Me.CurrentMana}>${Spell[${NukeSpell3}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
				/call SpellQueue "${Spell[${NukeSpell3}].RankName}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${NukeSpell4}].RankName}]} && ${Me.PctAggro}<${StopNukeAggro} && ${Target.CurrentHPs}<85 && ${Me.CurrentMana}>${Spell[${NukeSpell4}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
				/call SpellQueue "${Spell[${NukeSpell4}].RankName}" ${autotargetid}
			} else /if (${Cast.Status.Equal[I]} && ${Me.SpellReady[${Spell[${NukeSpell5}].RankName}]} && ${Me.PctAggro}<${StopNukeAggro} && ${Target.CurrentHPs}<85 && ${Me.CurrentMana}>${Spell[${NukeSpell5}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
				/call SpellQueue "${Spell[${NukeSpell5}].RankName}" ${autotargetid}
			} else /if (${Me.SpellReady[${PetGrowl}]} && ${Me.Level}<85 && !${Me.Buff[${PetGrowl}].ID} && !${Me.Song[${PetGrowl}].ID}) {
				/call CastSpell "${PetGrowl}" ${autotargetid} cbt
			}
		}
		 /if (${Me.AbilityReady[Round Kick]} && ${Target.LineOfSight}) {
				/doability "Round Kick"
				/delay 5
			} else /if (${UseAoE} && ${Me.CombatAbilityReady[${AEClaws}]}) {
				/call DiscNow "${AEClaws}" ${autotargetid}
			} else /if (${Me.CombatAbilityReady[${Maul}]}) {
				/call DiscNow "${Maul}" ${autotargetid}
			} else /if (${Me.CombatAbilityReady[${SingleClaws}]}) {
				/call DiscNow "${SingleClaws}" ${autotargetid}
			} else /if (${Me.AltAbilityReady[Chameleon Strike]}) {
				/call AANow ${Me.AltAbility[Chameleon Strike].ID} ${autotargetid}
			} else /if (${Me.AbilityReady[Eagle Strike]} && ${Target.LineOfSight}) {
				/doability "Eagle Strike"
				/delay 5
			} else /if (${Me.AltAbilityReady[Enduring Frenzy]} && (${Target.PctHPs}>90)) {
				/call AANow ${Me.AltAbility[Enduring Frenzy].ID} ${autotargetid}
			} else /if (${Me.PctEndurance}<80 && ${Me.CombatAbilityReady[${EndRegenProcDisc}]}) {
				/call DiscNow "${EndRegenProcDisc}" ${autotargetid}
			} else /if (${Me.CombatAbilityReady[${BeastialBuffDisc}]}) {
				/call DiscNow "${BeastialBuffDisc}" ${autotargetid}
			}
		/if (!${Me.Song[Bestial Alignment X].ID} && !${Me.Song[${HHEFuryDisc}].ID} && !${Me.Buff[Ferociousness II].ID} && !${Me.PetBuff[Bestial Bloodrage VI]} && !${Me.Song[Group Bestial Alignment IV].ID} && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow})) {
			/if (${Me.AltAbilityReady[Bestial Alignment]}) {
				/call AANow ${Me.AltAbility[Bestial Alignment].ID}
				/if (${Me.AltAbilityReady[Frenzy of Spirit]}) /call AANow ${Me.AltAbility[Frenzy of Spirit].ID}
				/if (${Me.AltAbilityReady[Bloodlust]}) /call AANow ${Me.AltAbility[Bloodlust].ID}
				/if (${Me.AltAbilityReady[Fundament: First Spire of the Savage Lord]}) /call AANow ${Me.AltAbility[Fundament: First Spire of the Savage Lord].ID}
				/if (${Me.AltAbilityReady[Frenzied Swipes]}) /call AANow ${Me.AltAbility[Frenzied Swipes].ID}
			} else /if (${Me.CombatAbilityReady[${HHEFuryDisc}]}) {
				/call DiscNow "${HHEFuryDisc}"
				/if (${Me.CombatAbilityReady[${DmgModDisc}]}) /call DiscNow "${DmgModDisc}"
			} else /if (${Me.AltAbilityReady[Ferociousness]}) {
				/call AANow ${Me.AltAbility[Ferociousness].ID}
			} else /if (${Me.AltAbilityReady[Companion's Fury]}) {
				/call AANow ${Me.AltAbility[Companion's Fury].ID}
				/if (${FindItem[${ChestItemName}].ID} && ${ChestCombatCast} && ${Cast.Ready[${ChestItemName}]}) {
					/useitem "${ChestItemName}"
					/delay 10	
				}
			} else /if (${Me.AltAbilityReady[Group Bestial Alignment]}) {
				/call AANow ${Me.AltAbility[Group Bestial Alignment].ID}
			} 
		}
		/varset groupbufftimer 1m
	}		
/return
|----------------------------------------------------------------------------
|- SUB: BuffCheck
|----------------------------------------------------------------------------
Sub BuffCheck
	/if (${DoFerocity} && ${Cast.Status.Equal[I]} && (${Me.SpellReady[${AtkBuff}]}) && (!${Me.Buff[${AtkBuff}].ID})) {
		/call SpellQueue "${AtkBuff}" ${Me.ID}
		/varset spellrememtimer 5s 
	}
	/if (!${Me.Song[Paragon of Spirit].ID} && ${Me.AltAbilityReady[Paragon of Spirit]} && ${Me.PctMana}<=${ParagonManaPct} && !${Me.Moving} && !${Me.Sitting} && !${Me.Invis}) {
		/call AANow ${Me.AltAbility[Paragon of Spirit].ID}
	} else /if (${UsePet} && !${Me.Pet.ID} && ${Cast.Status.Equal[I]} && ${Me.Book[${PetSpell}]} && ${Me.CurrentMana}>${Spell[${PetSpell}].Mana}) {
		/call SpellQueue "${PetSpell}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (!${Me.Buff[${Spell[${ManaRegenBuff}].RankName}].ID} && (!${Me.Casting.ID}) && (${Spell[${ManaRegenBuff}].Stacks}) && ${Me.Book[${ManaRegenBuff}]} && ${Me.CurrentMana}>${Spell[${ManaRegenBuff}].Mana}) {
		/if (${Me.Book[${UnityBuff}]} && ${Me.CurrentMana}>${Spell[${UnityBuff}].Mana} && ${Select[${Me.Level},100,105,110]}) {
			/call SpellQueue "${UnityBuff}" ${Me.ID}
		} else {
			/call SpellQueue "${ManaRegenBuff}" ${Me.ID}
		}
		/varset spellrememtimer 5s 
	} else /if (!${Me.Buff[${Spell[${AtkHPBuff}].RankName}].ID} && (!${Me.Casting.ID}) && (${Spell[${AtkHPBuff}].Stacks}) && ${Me.Book[${AtkHPBuff}]} && ${Me.CurrentMana}>${Spell[${AtkHPBuff}].Mana}) {
		/if (${Me.Book[${UnityBuff}]} && ${Me.CurrentMana}>${Spell[${UnityBuff}].Mana} && ${Select[${Me.Level},100,105,110]}) {
			/call SpellQueue "${UnityBuff}" ${Me.ID}
		} else {
			/call SpellQueue "${AtkHPBuff}" ${Me.ID}
		}
		/varset spellrememtimer 5s 
	} else /if (!${Me.Buff[${FocusSpell}].ID} && ${Spell[${FocusSpell}].Stacks} && (!${Me.Casting.ID}) && ${Me.Book[${FocusSpell}]} && ${Me.CurrentMana}>${Spell[${FocusSpell}].Mana} && ${UseFocus}) {
		/call SpellQueue "${FocusSpell}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (!${Me.Buff[${KillShotBuff}].ID} && (!${Me.Casting.ID}) && (${Spell[${KillShotBuff}].Stacks}) && ${Me.Book[${KillShotBuff}]} && ${Me.CurrentMana}>${Spell[${KillShotBuff}].Mana}) {
		/call SpellQueue "${KillShotBuff}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (!${Me.Buff[${RunSpeedBuff}].ID} && (!${Me.Casting.ID}) && (${Spell[${RunSpeedBuff}].Stacks}) && ${Me.Book[${RunSpeedBuff}]} && ${Me.CurrentMana}>${Spell[${RunSpeedBuff}].Mana} && ${UseRunSpeed}) {
		/call SpellQueue "${RunSpeedBuff}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (${UsePet} && !${DoPetTank} && !${Me.Pet.Buff[${PetOffenseBuff}]} &&  ${Spell[${PetOffenseBuff}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetOffenseBuff}]} && ${Me.CurrentMana}>${Spell[${PetOffenseBuff}].Mana}) {
		/call SpellQueue "${PetOffenseBuff}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (${UsePet} && ${DoPetTank} && !${Me.Pet.Buff[${PetDefenseBuff}]} &&  ${Spell[${PetDefenseBuff}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetDefenseBuff}]} && ${Me.CurrentMana}>${Spell[${PetDefenseBuff}].Mana}) {
		/call SpellQueue "${PetDefenseBuff}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (${UsePet} && ${DoPetSlow} && !${Me.Pet.Buff[${PetSlowProc}]} &&  ${Spell[${PetSlowProc}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetSlowProc}]} && ${Me.CurrentMana}>${Spell[${PetSlowProc}].Mana}) {
		/call SpellQueue "${PetSlowProc}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (${UsePet} && !${Me.Pet.Buff[${PetHaste}]} &&  ${Spell[${PetHaste}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetHaste}]} && ${Me.CurrentMana}>${Spell[${PetHaste}].Mana}) {
		/call SpellQueue "${PetHaste}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (${UsePet} && !${Me.Pet.Buff[${PetDamageProc}]} &&  ${Spell[${PetDamageProc}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetDamageProc}]} && ${Me.CurrentMana}>${Spell[${PetDamageProc}].Mana}) {
		/call SpellQueue "${PetDamageProc}" ${Me.ID}
		/varset spellrememtimer 5s
	} else /if (${UsePet} && !${Me.Pet.Buff[${PetHealProc}]} &&  ${Spell[${PetHealProc}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetHealProc}]} && ${Me.CurrentMana}>${Spell[${PetHealProc}].Mana} && ${spellrememtimer}==0) {
		/call SpellQueue "${PetHealProc}" ${Me.ID}
		/if (${CastResult.NotEqual[CAST_SUCCESS]}) {
			/varset spellrememtimer ${Spell[${PetHealProc}].RecastTime.Seconds}s
			/if (${groupbufftimer}<=39) /varset groupbufftimer 40s
		} else {
			/varset spellrememtimer 5s
		}
	} else /if (${UsePet} && !${Me.Pet.Buff[${PetSpellGuard}]} &&  ${Spell[${PetSpellGuard}].StacksPet} && (!${Me.Casting.ID}) && ${Me.Book[${PetSpellGuard}]} && ${Me.CurrentMana}>${Spell[${PetSpellGuard}].Mana} && ${spellrememtimer}==0) {
		/call SpellQueue "${PetSpellGuard}" ${Me.ID}
		/if (${CastResult.NotEqual[CAST_SUCCESS]}) {
			/varset spellrememtimer ${Spell[${PetSpellGuard}].RecastTime.Seconds}s
			/if (${groupbufftimer}<=39) /varset groupbufftimer 41s
		} else {
			/varset spellrememtimer 5s
		}
	} else /if (${Me.PctEndurance}<21 && ${Me.Endurance}>313 && ${Me.AltAbilityReady[Pact of the Wurine]} && !${Me.Invis}) {
		/call AANow ${Me.AltAbility[Pact of the Wurine].ID}
	} else /if (${Me.PctEndurance}<21 && ${Me.Endurance}>313 && ${Me.CombatAbilityReady[${EndRegenDisc}]} && !${Me.CombatState.Equal[combat]} && !${Me.Invis}) {
		/call DiscQueue "${EndRegenDisc}"
	} else /if (${Me.PctHPs}>70 && ${Me.PctMana}<80 && ${Me.AltAbilityReady[Consumption of Spirit]} && !${Me.Invis}) {
		/call AANow ${Me.AltAbility[Consumption of Spirit].ID}
	} else /if (!${Me.Gem[${spellmisc}].Name.Equal[${miscspellremem}]} && ${spellrememtimer}==0 && ${miscspellremem.NotEqual[NULL]} && !${BringYourOwnSpells}) {
		/call LoadSpellGem "${miscspellremem}" ${spellmisc}
	}
	|-Apply poison to weapon if enabled
	/if (${UsePoisons} && ${FindItem[${PoisonName}].ID} && ${Cast.Ready[${PoisonName}]} && !${Me.Buff[${PoisonBuffName}].ID}) {
		/useitem "${PoisonName}"
		/delay 50
	} else /if (${UsePoisons} && !${FindItem[${PoisonName}].ID}) {
		/echo No Poison Found in Inventory - Disabling
		/varset UsePoisons 0
		/varset changetoini 1
	}
	/if (${Group.MainAssist.ID} && ${ReTargetDelay}==0 && ${Target.ID}!=${Group.MainAssist.ID}) {
		/target id ${Group.MainAssist.ID}
		/varset ReTargetDelay 1m
		/varset autotargetid 0
	}
/return	
|-------------------------------------------------------------------------------------
|- SUB: DoParagon
|-------------------------------------------------------------------------------------
Sub DoParagon
	/declare i int local 
	/if (${Me.PctHPs}>70 && ${Me.PctMana}<70 && ${Me.AltAbilityReady[Consumption of Spirit]} && !${Me.Invis}) {
		/call AANow ${Me.AltAbility[Consumption of Spirit].ID}
	}
	/doevents
	/if (!${fparatimer2} && ${Me.AltAbilityReady[Paragon of Spirit]} && ${Me.PctMana}<=${ParagonManaPct}  && !${Me.Song[Paragon of Spirit].ID}) {
    	/echo \aw Casting Paragon of Spirit
		/call AANow ${Me.AltAbility[Paragon of Spirit].ID}
        /delay 2s
	    /varset fparatimer2 60s
		/return
	} else /if (!${fparatimer2} && ${Me.AltAbilityReady[Focused Paragon of Spirits]} && (${Me.PctMana}<=${FocParagonManaPct} || (${Me.PctEndurance}<=${FocParagonEndPct} && ${Me.AltAbility[Focused Paragon of Spirits].Rank}>12))  && !${Me.Song[Paragon of Spirit].ID}) {
		/squelch /tar id ${Me.ID}
        /delay 1s ${Target.ID}==${Me.ID}
    	/echo \aw Casting Focused Paragon of Spirits on \ag ${Me.Name}
		/call AANow ${Me.AltAbility[Focused Paragon of Spirits].ID} ${Me.ID}
        /delay 2s
	    /varset fparatimer2 60s
		/return
	}
    /for i 0 to ${Group}
		/doevents
		/if (!${fparatimer2} && !${Select[${Group.Member[${i}].Class.ShortName},BER,MNK,WAR,ROG]} && ${Me.AltAbilityReady[Paragon of Spirit]} && ${Group.Member[${i}].CurrentMana}<=${ParagonManaPct} && ${Group.Member[${i}].ID} && !${SpawnCount[${Group.Member[${i}]} corpse]} && ${Spawn[ID ${Group.Member[${i}].ID} radius 200].ID}) {
			/echo \aw Casting Paragon of Spirit
			/call AANow ${Me.AltAbility[Paragon of Spirit].ID}
			/delay 2s
			/varset fparatimer2 60s
			/break
		}
        /if (!${fparatimer2} && !${Select[${Group.Member[${i}].Class.ShortName},BER,MNK,WAR,ROG,SHM,CLR]} && ${Me.AltAbilityReady[Focused Paragon of Spirits]} && ${Group.Member[${i}].CurrentMana}<=${FocParagonManaPct} && ${Group.Member[${i}].ID} && !${SpawnCount[${Group.Member[${i}]} corpse]} && ${Spawn[ID ${Group.Member[${i}].ID} radius 200].ID}) {
			/squelch /tar id ${Group.Member[${i}].ID}
            /delay 1s ${Target.ID}==${Group.Member[${i}].ID}
			/echo \aw Casting Focused Paragon of Spirits on \ag ${Target.Name}
			/call AANow ${Me.AltAbility[Focused Paragon of Spirits].ID} ${Group.Member[${i}].ID}
			/delay 2s
			/varset fparatimer2 60s
			/squelch /tar clear
			/break
		} else /if (!${fparatimer2} && !${Select[${Group.Member[${i}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]} && ${Me.AltAbilityReady[Focused Paragon of Spirits]} && ${Me.AltAbility[Focused Paragon of Spirits].Rank}>12 && ${Group.Member[${i}].PctEndurance}<=${FocParagonEndPct} && ${Group.Member[${i}].ID} && !${SpawnCount[${Group.Member[${i}]} corpse]} && ${Spawn[ID ${Group.Member[${i}].ID} radius 200].ID}) {
			/squelch /tar id ${Group.Member[${i}].ID}
            /delay 1s ${Target.ID}==${Group.Member[${i}].ID}
			/echo \aw Casting Focused Paragon of Spirits on \ag ${Target.Name}
			/call AANow ${Me.AltAbility[Focused Paragon of Spirits].ID} ${Group.Member[${i}].ID}
			/delay 2s
			/varset fparatimer2 60s
			/squelch /tar clear
			/break
        } 
	/next i
/return
|----------------------------------------------------------------------------
|- SUB: ConfigHeal
|---------------------------------------------------------------------------- 
Sub ConfigHeal
	/if (${Select[${Zone.ID},795,796]}==0 && !${Raid.Members}) {
		/if (${Me.XTarget}>2||${Me.XTarget[1].Named}) {
			/if (${Healpoint}!=90) {
				/varset Healpoint 80
			}
		} else /if (${Me.XTarget[1].Level}>=${Me.Level}) {
			/if (${Healpoint}!=85) {
				/varset Healpoint 80
			}
		} else /if (${Me.XTarget[1].Level}>=${Math.Calc[${Me.Level}-5]}) {
			/if (${Healpoint}!=80) {
				/varset Healpoint 75
			}
		} else {
			/if (${Healpoint}!=70) {
				/varset Healpoint 70

			}
		}
	} else /if (${Healpoint}!=${TBMHealpoint} && !${Raid.Members}) {
		/varset Healpoint ${TBMHealpoint}
	} else /if (${Healpoint}!=${RaidHealpoint} && ${Raid.Members}) {
		/varset Healpoint ${RaidHealpoint}
	}
/return 
|----------------------------------------------------------------------------
|- SUB: Symbol - HP Buff Single use
|----------------------------------------------------------------------------
Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
	|/if (${Spawn[pc ${ChatSender}].ID} && ${ChatType.Equal[tell]}) /mqlog ${ChatSender} -- ${ChatText}
	|/if (${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}) {
	|	/if (${Select[${ChatText},SoW,RunSpeedBuff,Tala]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<200)) /call SpellQueue "${RunSpeedBuff}" ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
	|}
/return
|----------------------------------------------------------------------------
|- SUB: Event_WornOff
|----------------------------------------------------------------------------
Sub Event_WornOff
	
/return 
|----------------------------------------------------------------------------
|- SUB: Event GroupChange
|----------------------------------------------------------------------------
Sub Event_GroupChange
	
/return 