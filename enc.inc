|----------------------------------------------------------------------------
|- SUB: ManualPullCamping
|----------------------------------------------------------------------------
Sub enc_main
	|/call check_resources FALSE "Gather Mana" spell ${Me.ID} 60
	|/call check_resources FALSE "Azure Mind Crystal" alt ${Me.ID} 40
	|/call check_resources FALSE "${ChestItemName}" item ${Me.ID} 80
	/call enc_self_buffs
	/call enc_group_buffs
	
	/while (${Me.XTarget}) {

		| Have we assisted MA?
		/call get_target

		| Do we have a valid target?
		/if (!${validate_combat[${Target.ID}]}) /continue

		| Before debuffing and nuking check if we have to mezz
		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"

		| Before nuking check if we have to debuff
		/call enc_debuff_xtarget

		| Start dpsing
		/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) /call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE

		/if (!${Target.Tashed.ID} && !${Target.Buff[${TashSpell}].ID}) {
			/if (${validate_cast[FALSE, spell, "${TashSpell}", ${Target.ID}]}) /call core_cast2 "${TashSpell}" spell ${Target.ID} FALSE
		}

		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"

		/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {		
			/if (${validate_cast[FALSE, spell, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" spell ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"

		/if (!${Target.Mezzed.ID} && !${Target.Buff[${MezSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
				
			/if (${validate_cast[FALSE, spell, "${SingleStunSpell1}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Stunning \ar ${Target.Name} \ax with =>> \ag ${SingleStunSpell1} \ax <<=
				/call core_cast2 "${SingleStunSpell1}" spell ${Target.ID} FALSE
				/call check_cast_events "${SingleStunSpell1}" CAST_IMMUNE ${Target.ID}
			}
		}

		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"
		/call enc_debuff_xtarget

		/if (!${Me.Buff[Improved Twincast].ID} && !${Target.Buff[${Drown}].ID}) {
			/if (${validate_cast[FALSE, spell, "${Drown}", ${Target.ID}]}) /call core_cast2 "${Drown}" spell ${Target.ID} FALSE
		}

		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"
		/call enc_debuff_xtarget

		/if (${validate_cast[FALSE, spell, "Chromatic Haze", ${Target.ID}]}) /call core_cast2 "Chromatic Haze" alt ${Target.ID} FALSE

		/if (${validate_cast[FALSE, spell, "${MindNukeMain}", ${Target.ID}]}) /call core_cast2 "${MindNukeMain}" spell ${Target.ID} FALSE
		
		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"
		/call enc_debuff_xtarget

		/if (!${Target.Mezzed.ID} && !${Target.Buff[${MezSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${validate_cast[FALSE, spell, "${SingleStunSpell1}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Stunning \ar ${Target.Name} \ax with =>> \ag ${SingleStunSpell1} \ax <<=
				/call core_cast2 "${SingleStunSpell1}" spell ${Target.ID} FALSE
				/call check_cast_events "${SingleStunSpell1}" CAST_IMMUNE ${Target.ID}
			}
		}
		/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) /call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
		/call mezz_xtarget "${AEMezSpell}" "${MezSpell}"
		/call enc_debuff_xtarget
		/if (${validate_cast[FALSE, spell, "${MindNukeSub}", ${Target.ID}]}) /call core_cast2 "${MindNukeSub}" spell ${Target.ID} FALSE
	}
|	/call CheckMana
|	/if (${UseModRods}) /call ClickModRoD
	
|	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) && ${BegTimer}==0 && ${DoGroupBeg}) /call BegForCure
	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: enc_debuff_xtarget
|---------------------------------------------------------------------------- 
Sub enc_debuff_xtarget
	/declare _count int local 1

	| Is there something to mez?
	/if (!${Me.XTarget}) /return
	/if (${Me.XTarget} < 2) /return

	/for _count 1 to ${Me.XTarget}

		/if (${debuffSet.Contains[${Me.XTarget[${_count}].ID}]}) /continue

		/if (${Me.XTarget[${_count}].ID} != ${Target.ID}) {
			/target id ${Me.XTarget[${_count}].ID}
			/delay 1s ${Me.XTarget[${_count}].ID} == ${Target.ID}
			/delay 5
		}

		/if (${Target.Distance} > 200) /return
		/if (!${Target.Type.Equal[NPC]}) /return
		
		/if (!${Target.Tashed.ID} && !${Target.Buff[${TashSpell}].ID}) {
			/if (${validate_cast[FALSE, spell, "${TashSpell}", ${Target.ID}]}) /call core_cast2 "${TashSpell}" spell ${Target.ID} FALSE
		}

		/if (!${Target.Buff[${Constriction}].ID} && ${Target.Named}) {
			/if (${validate_cast[FALSE, spell, "${Constriction}", ${Target.ID}]}) /call core_cast2 "${Constriction}" spell ${Target.ID} FALSE
		}
	
		/if (!${Target.Buff[Mental Contortion].ID} && ${Target.Named}) {
			/if (${validate_cast[FALSE, alt, "Mental Contortion", ${Target.ID}]}) /call core_cast2 "Mental Contortion" alt ${Target.ID} FALSE
		}

		| How will you handle the AA?
		/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			
			/if (${validate_cast[FALSE, spell, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" spell ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}
		
		/if (!${Target.Crippled.ID} && !${Target.Buff[${CrippleSpell1}].ID} && !${Target.Buff[Mental Contortion].ID}) {
			
			/if (${validate_cast[FALSE, spell, "${CrippleSpell1}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${CrippleSpell1} \ax <<=
				/call core_cast2 "${CrippleSpell1}" spell ${Target.ID} FALSE
			}
		}
		
		/if (!${debuffSet.Add[${Target.ID}]}) {
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Set Add of${Target.ID} failed.
		}

|			/if (${StripBuffs} && (!${Me.Casting.ID}) && ${Target.Beneficial.ID} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
|				/if (${Me.AltAbilityReady[${StripBuffSpell}]}) {
|					/alt act ${Me.AltAbility[${StripBuffSpell}].ID}
|					/delay 10 ${Window[CastingWindow].Open}
|					/delay 10 !${Me.Casting.ID}
|				} else /if (${Me.SpellReady[${StripBuffSpell}]}) {
|					/call CastSpell "${StripBuffSpell}" ${autotargetid} dbf
|				}
|			}
|			/if (${DoBlurr} && ${Me.PctAggro}>=${BlurrAggroPct}) /call ManageAggro "BlrFlg"

|			/if (${DoTash} && ${Me.SpellReady[${TashSpell}]} && !${Target.Tashed.ID} && ${Cast.Status.Equal[I]} && ${Me.CurrentMana}>${Spell[${TashSpell}].Mana}) {
|				/call CastSpell "${TashSpell}" ${Target.ID} dbf
|				/delay 16
|			}
|			/if (${DoSlow} && ${Me.AltAbilityReady[Slowing Helix]} && !${Target.Slowed.ID} && !${Me.Casting.ID} && !${Target.Buff[Turgur's Insects].ID}) {
|				/alt act ${Me.AltAbility[Slowing Helix].ID}
|				/delay 10 ${Window[CastingWindow].Open}
|				/delay 10 !${Me.Casting.ID}
|			} else /if (${DoSlow} && ${Me.SpellReady[${SlowSpell}]} && !${Target.Slowed.ID} && !${Me.Casting.ID} && !${Target.Buff[Turgur's Insects].ID}) {
|				/call CastSpell "${SlowSpell}" ${Target.ID} dbf
|			}
|			/if (${DoBlurr} && ${Me.PctAggro}>=${BlurrAggroPct}) /call ManageAggro "BlrFlg"
|		/delay 5s !${Me.Casting.ID}
		/delay 7
	/next _count

	/call get_target

/return

|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub enc_aa_and_disc
	
|-Defensive AA's for Name Mobs or Low HP on MA
	/if (${Me.AltAbilityReady[Glyphy Spray]} && ((${Target.Named} && ${Target.Level}>${Me.Level}) || ${Target.Level}>(${Me.Level}+3) || (${Group.Member[${assistname}]${TnKCond}PctHPs}<45 && ${Group.Member[${assistname}]${TnKCond}PctHPs}>5))) {
		/alt act ${Me.AltAbility[Glyphy Spray].ID}
		/delay 10
	}
	/if (${Me.AltAbilityReady[Reactive Rune]} && ((${Target.Named} && ${Target.Level}>${Me.Level}) || ${Target.Level}>(${Me.Level}+3) || (${Group.Member[${assistname}]${TnKCond}PctHPs}<45 && ${Group.Member[${assistname}]${TnKCond}PctHPs}>5))) {
		/alt act ${Me.AltAbility[Reactive Rune].ID}
		/delay 10
	}
|-Constant Use AA's
	/if (${Me.AltAbilityReady[Focus of Arcanum]}) {
		/alt act ${Me.AltAbility[Focus of Arcanum].ID}
		/delay 10
	}
/return
|----------------------------------------------------------------------------
|- SUB: combat
|---------------------------------------------------------------------------- 
Sub enc_combat

	

/return
|----------------------------------------------------------------------------
|- SUB: BurnRoutine
|---------------------------------------------------------------------------- 
Sub enc_burn
	/if (${Me.AltAbilityReady[Illusions of Grandeur]}) {
		/alt act ${Me.AltAbility[Illusions of Grandeur].ID}
		/delay 10
	}
	/if (${Me.AltAbilityReady[Fundament: Third Spire of Enchantment]}) {
		/alt act ${Me.AltAbility[Fundament: Third Spire of Enchantment].ID}
		/delay 10
	} 
	/if (${Me.AltAbilityReady[Improved Twincast]}) {
		/alt act ${Me.AltAbility[Improved Twincast].ID}
		/delay 10
	}
	/if (${Me.AltAbilityReady[Forceful Rejuvenation]} && ${Me.Buff[Improved Twincast].ID}) {
		/if (${Me.SpellReady[${MindNukeMain}]} && ${Cast.Status.Equal[I]} && ${Me.CurrentMana}>${Spell[${MindNukeMain}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
			/call CastSpell "${MindNukeMain}" ${Target.ID} brn
			/delay 16
		}
		/if (${Me.AltAbilityReady[Calculated Insanity]} && (!${Me.Casting.ID}) && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
			/alt act ${Me.AltAbility[Calculated Insanity].ID}
			/delay 10 ${Window[CastingWindow].Open}
			/delay 20 !${Window[CastingWindow].Open}
		}
		/if (${Me.SpellReady[${MindNukeSub}]} && ${Cast.Status.Equal[I]} && ${Me.CurrentMana}>${Spell[${MindNukeSub}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
			/call CastSpell "${MindNukeSub}" ${Target.ID} brn
			/delay 16
		}
		/alt act ${Me.AltAbility[Forceful Rejuvenation].ID}
		/delay 10 !${Me.Casting.ID}
		/if (${Me.SpellReady[${MindNukeMain}]} && ${Cast.Status.Equal[I]} && ${Me.CurrentMana}>${Spell[${MindNukeMain}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
			/call CastSpell "${MindNukeMain}" ${Target.ID} brn
			/delay 16
		}
		/if (${Me.SpellReady[${MindNukeSub}]} && ${Cast.Status.Equal[I]} && ${Me.CurrentMana}>${Spell[${MindNukeSub}].Mana} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
			/call CastSpell "${MindNukeSub}" ${Target.ID} brn
			/delay 16
		}	
	} else /if (${Me.AltAbilityReady[Calculated Insanity]}) {
		/alt act ${Me.AltAbility[Calculated Insanity].ID}
		/delay 10
	}
/return
|----------------------------------------------------------------------------
|- SUB: self_buffs
|---------------------------------------------------------------------------- 
Sub enc_self_buffs

	/declare CastCheck			int local 0

	/if (${Me.XTarget}) /return

	
	/if (!${Me.Buff[${SelfHPBuff}].ID} && (${Spell[${SelfHPBuff}].Stacks}) && ${Me.Book[${SelfHPBuff}]} && ${Me.CurrentMana}>${Spell[${SelfHPBuff}].Mana} && ${Me.AltAbilityReady[Orator's Unity]}) {
		/alt act ${Me.AltAbility[Orator's Unity].ID}
	} else /if (!${Me.Buff[${SelfHPBuff}].ID} && !${Me.AltAbilityReady[Orator's Unity]}) {
		/if (${validate_cast[FALSE, spell, "${SelfHPBuff}", ${Me.ID}]}) {
			/call core_cast2 "${SelfHPBuff}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	} 

	/if (!${Me.Pet.ID} && ${FindItem[=Tiny Dagger].ID}) {
		/if (${validate_cast[FALSE, spell, "${PetSpell}", ${Me.ID}]}) {
			/call core_cast2 "${PetSpell}" spell 0 FALSE
			/varset CastCheck 1
		}
	}
|**
	/if (${Me.Pet.ID} && !${Me.Pet.Buff[${PetBuffSpell}]}) {
		/if (${validate_cast[FALSE, spell, "${PetBuffSpell}", ${Me.Pet.ID}]}) {
			/call core_cast2 "${PetBuffSpell}" spell ${Me.Pet.ID} FALSE
			/varset CastCheck 1
		}
	}
**|
	/if (!${Me.Buff[${MezBuff}].ID}) {
		/if (${validate_cast[FALSE, spell, "${MezBuff}", ${Me.ID}]}) {
			/call core_cast2 "${MezBuff}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	} 
|**
	/if (${validate_cast[FALSE, spell, "${UnityRune}", ${Me.ID}]}) {
		/if (!${Me.Buff[${UnityRune}].ID}) {
			/call core_cast2 "${UnityRune}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	} else {
**|
	/if (!${Me.Buff[${SelfRune1}].ID}) {
		/if (${validate_cast[FALSE, spell, "${SelfRune1}", ${Me.ID}]}) {
			/call core_cast2 "${SelfRune1}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	} 

	/if (!${Me.Buff[${SelfRune2}].ID}) {
		/if (${validate_cast[FALSE, spell, "${SelfRune2}", ${Me.ID}]}) {
			/call core_cast2 "${SelfRune2}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	} 
	|}
	
|				/call SpellQueue "${PetSpell}" ${Me.ID}
|				/varset CastCheck 1
|				/delay 5
|	} else /if (${UsePet} && !${UseCharmPet} && ${Me.Pet.ID} && ${Cast.Status.Equal[I]} && ${Me.Book[${PetBuffSpell}]} && ${Me.CurrentMana}>${Spell[${PetBuffSpell}].Mana} && !${Me.Pet.Buff[${PetBuffSpell}]}) {
|				/call SpellQueue "${PetBuffSpell}" ${Me.Pet.ID}
|				/varset CastCheck 1
|	else /if (!${Me.Buff[${GroupMana}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${GroupMana}].Stacks}) && ${Me.Book[${GroupMana}]} && ${Me.CurrentMana}>${Spell[${GroupMana}].Mana}) {
||				/call SpellQueue "${GroupMana}" ${Me.ID}
|				/varset CastCheck 1
|	} else /if (!${Me.Buff[${GroupHaste}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${GroupHaste}].Stacks}) && ${Me.Book[${GroupHaste}]} && ${Me.CurrentMana}>${Spell[${GroupHaste}].Mana}) {
|				/call SpellQueue "${GroupHaste}" ${Me.ID}
|				/varset CastCheck 1
|	} else /if (!${Me.Buff[${MezBuff}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${MezBuff}].Stacks}) && ${Me.Book[${MezBuff}]} && ${Me.CurrentMana}>${Spell[${MezBuff}].Mana}) {
|				/call SpellQueue "${MezBuff}" ${Me.ID}
|				/varset CastCheck 1 
|	} else /if (!${Me.Buff[Eldritch Rune].ID} && !${Me.Buff[${SelfRune1}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${SelfRune1}].Stacks}) && ${Me.Book[${SelfRune1}]} && ${Me.CurrentMana}>${Spell[${SelfRune1}].Mana}) {
|				/call SpellQueue "${SelfRune1}" ${Me.ID}
|				/varset CastCheck 1
|	} else /if (!${Me.Buff[${SelfRune2}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${SelfRune2}].Stacks}) && ${Me.Book[${SelfRune2}]} && ${Me.CurrentMana}>${Spell[${SelfRune2}].Mana}) {
|				/call SpellQueue "${SelfRune2}" ${Me.ID}
|				/varset CastCheck 1
|	} else /if (!${Me.Buff[${GroupSpellShield}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${GroupSpellShield}].Stacks}) && ${Me.Book[${GroupSpellShield}]} && ${Me.CurrentMana}>${Spell[${GroupSpellShield}].Mana} && ${UseSpellRune}) {
|				/call SpellQueue "${GroupSpellShield}" ${Me.ID}
|				/varset CastCheck 1 
|	} else /if (!${Me.Buff[${GroupDoTShield}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${GroupDoTShield}].Stacks}) && ${Me.Book[${GroupDoTShield}]} && ${Me.CurrentMana}>${Spell[${GroupDoTShield}].Mana} && ${UseDoTRune}) {
|				/call SpellQueue "${GroupDoTShield}" ${Me.ID}
|				/varset CastCheck 1
|	} else /if (!${Me.Buff[${GroupAuspiceBuff}].ID} && ${Cast.Status.Equal[I]} && (${Spell[${GroupAuspiceBuff}].Stacks}) && ${Me.Book[${GroupAuspiceBuff}]} && ${Me.CurrentMana}>${Spell[${GroupAuspiceBuff}].Mana} && ${UseAuspice}) {
|				/call SpellQueue "${GroupAuspiceBuff}" ${Me.ID}
||				/varset CastCheck 1
|	} else /if (!${Me.Buff[Veil of Mindshadow].ID} && ${Cast.Status.Equal[I]} && (${Spell[Veil of Mindshadow].Stacks}) && ${Me.AltAbilityReady[Veil of Mindshadow]}) {
|				/alt act 791
|				/delay 5
|				/varset CastCheck 1
|	} else /if (${UsePet} && !${UseCharmPet} && !${Me.Pet.ID} && ${Cast.Status.Equal[I]} && ${Me.Book[${PetSpell}]} && ${Me.CurrentMana}>${Spell[${PetSpell}].Mana}) {
|				/call SpellQueue "${PetSpell}" ${Me.ID}
|				/varset CastCheck 1
|				/delay 5
|	} else /if (${UsePet} && !${UseCharmPet} && ${Me.Pet.ID} && ${Cast.Status.Equal[I]} && ${Me.Book[${PetBuffSpell}]} && ${Me.CurrentMana}>${Spell[${PetBuffSpell}].Mana} && !${Me.Pet.Buff[${PetBuffSpell}]}) {
|				/call SpellQueue "${PetBuffSpell}" ${Me.Pet.ID}
|				/varset CastCheck 1
|	} else /if (!${Me.Gem[${spellmisc}].Name.Equal[${miscspellremem}]} && ${spellrememtimer}==0 && ${miscspellremem.NotEqual[NULL]}) {
|				/call LoadSpellGem "${miscspellremem}" ${spellmisc}
|	}
	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: group_buffs
|---------------------------------------------------------------------------- 
Sub enc_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (${Me.XTarget}) /return
	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return
	
	/for _count 0 to ${Group}
		/if (${Group.Member[${_count}].Distance} < 100 && !${Group.Member[${_count}].OtherZone} && (!${Me.Casting.ID})) {
			
			/if (${Me.XTarget}) {
				/call ${Me.Class.ShortName.Lower}_load_spellbar
				/return
			}
			/if (${Mode} !=3 ) /return

			/if (!${Me.Book[${GroupMana}]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${SingleMana}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${SingleMana}].Stacks" "tmpstackcheck" "bool"
				/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},WAR,ROG,BER,MNK]}) {
					/if (${validate_cast[FALSE, spell, "${SingleMana}", ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${SingleMana}" spell ${Group.Member[${_count}].ID} FALSE
						/delay 10
						/varset CastCheck 1 
					}
				}
			}

			/if (!${Me.Book[${GroupHaste}]} && ${Select[${Group.Member[${_count}].Class.ShortName},WAR,ROG,BER,MNK,SHD,PAL]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${SingleHaste}].ID" "tmpbuffid" "bool"
				/if (!${tmpbuffid}) {
					/if (${validate_cast[FALSE, spell, "${SingleHaste}", ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${SingleHaste}" spell ${Group.Member[${_count}].ID} FALSE
						/delay 10
						/varset CastCheck 1
					}
				}
			}
			
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GroupHaste}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GroupHaste}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
				/if (${validate_cast[FALSE, spell, "${GroupHaste}", ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${GroupHaste}" spell ${Group.Member[${_count}].ID} FALSE
					/delay 10
					/varset CastCheck 1
				}
			}
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${GroupMana}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${GroupMana}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},WAR,ROG,BER,MNK]}) {
				/if (${validate_cast[FALSE, spell, "${GroupMana}", ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${GroupMana}" spell ${Group.Member[${_count}].ID} FALSE
					/delay 10
					/varset CastCheck 1
				}
			}
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${ProcBuff}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${ProcBuff}].Stacks" "tmpstackcheck" "bool"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[Illusion Benefit Greater Jann].ID" "jaanbuffid" "int"
			/if (!${tmpbuffid} && !${jaanbuffid} && ${tmpstackcheck} && ${Select[${Group.Member[${_count}].Class.ShortName},BRD,BST,BER,MNK,PAL,RNG,ROG,SHD,WAR]}) {
				/if (${validate_cast[FALSE, spell, "${ProcBuff}", ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${ProcBuff}" spell ${Group.Member[${_count}].ID} FALSE
					/delay 10
					/varset CastCheck 1
				}
			}
		}
	/next _count

	|- Delete variable's
	/if (${Defined[tmpbuffid]}) /deletevar tmpbuffid
	/if (${Defined[tmpstackcheck]}) /deletevar tmpstackcheck
	/if (${Defined[jaanbuffid]}) /deletevar jaanbuffid
	/if (${Window[SpellBookWnd]}) /book
	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}
/return
|----------------------------------------------------------------------------
|- SUB: ManageAggro
|---------------------------------------------------------------------------- 
Sub enc_manage_aggro(string OptFlag)
	/if (!${Me.Buff[Eldritch Rune].ID} && !${Me.Buff[${SelfRune1}].ID} && ${Cast.Status.Equal[I]} && (${Spell[Eldritch Rune].Stacks}) && ${Me.AltAbilityReady[Eldritch Rune]}) {
		/alt act 173
		/delay 5 
	}
	/if (${OptFlag.Equal[BlrFlg]} && ${Me.PctAggro}>=${BlurrAggroPct}) {
		/if (${DoBlurr} && ${Me.SpellReady[${BlurSpell}]} && (!${Me.Casting.ID}) && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
			/call CastSpell "${BlurSpell}" ${autotargetid} dbf
		}
	}
	/if (${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID} && ${Target.ID}!=${Me.ID} && ${Target.ID}==${Me.GroupAssistTarget.ID}) {
		/if (${Me.PctHPs}<=30 && ${Me.AltAbilityReady[Self Stasis]}) {
			/call AANow ${Me.AltAbility[Self Stasis].ID} ${Target.ID}
		} else /if (${Me.PctHPs}<=30 && ${Me.AltAbilityReady[Dimensional Instability]}) {
			/call AANow ${Me.AltAbility[Dimensional Instability].ID} ${Target.ID}
		} else /if (${Me.PctHPs}<=40 && ${Me.AltAbilityReady[Beguiler's Directed Banishment]}) {
			/call AANow ${Me.AltAbility[Beguiler's Directed Banishment].ID} ${Target.ID}
		} else /if (${Me.PctHPs}<=50 && ${Me.AltAbilityReady[Beguiler's Banishment]} && ${SpawnCount[npc radius 20]} > 2) {
			/call AANow ${Me.AltAbility[Beguiler's Banishment].ID} ${Target.ID}
		} else /if (${Me.PctHPs}<=60 && ${Me.AltAbilityReady[Doppelganger]}) {
			/call AANow ${Me.AltAbility[Doppelganger].ID} ${Target.ID}
		} else /if (${Me.PctHPs}<=60 && ${Me.AltAbilityReady[Phantasmal Opponent]}) {
			/call AANow ${Me.AltAbility[Phantasmal Opponent].ID} ${Target.ID}
		} else /if (${Me.PctHPs}<=80 && ${Me.AltAbilityReady[Dimensional Shield]}) {
			/call AANow ${Me.AltAbility[Dimensional Shield].ID} ${Target.ID}
		}
	}
	/if (${Target.ID}==${Me.GroupAssistTarget.ID} && (${Me.PctAggro}>=90 || ${Me.TargetOfTarget.ID}==${Me.ID})) {
		/if (${Me.AltAbilityReady[Arcane Whisper]}) {
			/call AANow ${Me.AltAbility[Arcane Whisper].ID} ${Target.ID}
		} else /if (${Me.AltAbilityReady[Silent Casting]}) {
			/call AANow ${Me.AltAbility[Silent Casting].ID} ${Target.ID}
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: Handle Buff Requests
|----------------------------------------------------------------------------
|-Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
|-	/if (${Spawn[pc ${ChatSender}].ID} && ${ChatType.Equal[tell]}) /mqlog ${ChatSender} -- ${ChatText}
|-	/if (${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}) {
|-		/if (${Select[${ChatText},voice,crack,clarity,kei]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /call SpellQueue "${SingleMana}" ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
|-		/if (${Select[${ChatText},haste,speed,zing]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /call SpellQueue "${SingleHaste}" ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
|-	}
|-/return
|----------------------------------------------------------------------------
|- SUB: CharmCheck
|----------------------------------------------------------------------------
Sub CharmCheck
	/declare nArray int local
	/declare nArray2 int local
	/if (${CharmDelay}) /return
	/if (${CharmedID} && !${Spawn[ID ${CharmedID}].ID}) /varset CharmedID 0
	/if (${OldCharmedID} && !${Spawn[ID ${OldCharmedID}].ID}) /varset OldCharmedID 0
	
	/if (${UseCharmPet} && !${Me.Pet.ID} && ${CharmSpell1.NotEqual[NULL]} && ${Me.SpellReady[${CharmSpell1}]}) {
		/if (${CharmedID} && ${Spawn[${CharmedID}].ID} && ${Spawn[${CharmedID}].Type.Equal[NPC]} && ${Spawn[${CharmedID}].Distance}<${Math.Calc[${Spell[${CharmSpell1}].Range}-25]}) {
			/squelch /target ID ${CharmedID}
			/delay 1s ${Target.ID}==${CharmedID}
		} else /if (${OldCharmedID} && ${Spawn[${OldCharmedID}].ID} && ${Spawn[${OldCharmedID}].Type.Equal[NPC]} && ${Spawn[${OldCharmedID}].Distance}<${Math.Calc[${Spell[${CharmSpell1}].Range}-25]}) {
			/squelch /target ID ${OldCharmedID}
			/delay 1s ${Target.ID}==${OldCharmedID}
		} else {
			/call MezRadar
			/if (${MezCheckElements}==0) /return
			/if (${MezCheckElements}>=${CharmMinMobs}) {
				/for nArray 1 to ${MezCheckElements}
					/if (${Defined[CCTarget${nArray}Info]}) {
						/if (${Spawn[${CCTarget${nArray}Info.Arg[1,|]}].ID} && ${Spawn[${CCTarget${nArray}Info.Arg[1,|]}].ID}!=${Me.GroupAssistTarget.ID} && ${Spawn[${CCTarget${nArray}Info.Arg[1,|]}].Distance}<=${assistRange} && ${CCTarget${nArray}Info.Arg[2,|]}>=${CharmMinLvl} && ${CCTarget${nArray}Info.Arg[2,|]}<=${CharmMaxLvl}) {
							/squelch /target ID ${CCTarget${nArray}Info.Arg[1,|]}
							/varset CharmedID ${CCTarget${nArray}Info.Arg[1,|]}
						}
					}
				/next nArray
				/delay 1s ${Target.ID}==${CharmedID}
			}
		}
		/if (${Target.ID}==${CharmedID} && ${Target.Type.Equal[NPC]}) {
			/if (${CharmPreStun} && ${SingleStunSpell1.NotEqual[NULL]} && ${Me.SpellReady[${SingleStunSpell1}]}) {
				/call CastSpell "${SingleStunSpell1}" ${Target.ID} Charm
			}
			/if (${CharmPreTash} && ${TashSpell.NotEqual[NULL]} && ${Me.SpellReady[${TashSpell}]}) {
				/call CastSpell "${TashSpell}" ${Target.ID} Charm
			}
			/call CastSpell "${CharmSpell1}" ${Target.ID} Charm
			/if (${CastResult.Equal[CAST_SUCCESS]}) {
				/echo Successfully Charmed ${Me.Pet.CleanName} | ${Me.Pet.ID}
			} else {
				/echo Failed to Charm ${Spawn[${CharmedID}].CleanName} | ${CharmedID}
				/varset OldCharmedID ${CharmedID}
				/varset CharmedID 0
			}
		}
	} else /if (${MezCheckElements}>0) {
		/for nArray2 1 to ${MezCheckElements}
			/if (${Defined[CCTarget${nArray2}Info]}) {
				/if (${CCTarget${nArray2}Info.Arg[3,|].Find[corpse]} || !${Spawn[${CCTarget${nArray2}Info.Arg[1,|]}].ID} || ${Spawn[${CCTarget${nArray2}Info.Arg[1,|]}].Type.Equal[Corpse]}) /call RemoveCCTarget ${nArray2}
				/if (${Spawn[${CCTarget${nArray2}Info.Arg[1,|]}].ID}==${Me.Pet.ID}) /call RemoveCCTarget ${nArray2}
			}
		/next nArray2
	}
/return 