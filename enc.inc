|----------------------------------------------------------------------------
|- SUB: ManualPullCamping
|----------------------------------------------------------------------------
|**
http://forums.eqfreelance.net/index.php?topic=16075.0

Droba:
have dmg amp aura + mana recip up,cast dicho right before engage, mob gets tashed, 
pop ITC -> mind tempest -> robe -> iog -> CH -> mindslash -> strangulate -> mind slash -> 
strangulate -> strangulate -> mindslash -> repeat until itc fades, drop spell amp aura for twincast aura.
Always recast dichotomic the moment it repops.
Always recast Mindslash when it repops to proc synergy.

Gotcharms:
Your actual activated burn order should look like this: Dicho -> ITC +IoG -> Robe Click (rotate casts if other Enchanters are using theirs) -> Chromatic Haze -> Mindslash

Caster order 1:
(Dicho on Cooldown) -> Mindslash -> Mindsunder -> Strangulate
Caster order 2:
(Dicho on Cooldown) -> Mindslash -> Strangulate -> Strangulate

CO1 is for fulminating Alliance, low mana pools, or during Calculated Insanity (strangulate does not gain CI benefit).
CO2 is for everything else. It is mana intensive, does not fulminate alliance, and will not use all 27 CI charges.
This is largely preference. I swap between the two on the fly.

Auras 
Twincast, Mana Reciprocation, and Bolstering Aura. 
In events where the group is burning "off the top," both Mana Reciprocation and Bolstering Aura should be up and running at least 3 ticks before the event starts. 
Activating them later than that will result in no benefit because they take time to actually pulse.

Once the Enchanter's own ITC (Improved Twincast) has faded, immediately drop Bolstering Aura and activate Twincast. 
I generally keep all three of these auras on my spell bar at the start of the event so I don't have to bother with hotswapping.

TODO:
	Glyph Spray
	Eldrich Rune
	Arcane Whisper
	Dimensional Shield

**|

Sub enc_main

	/if (!${Me.XTarget}) /call enc_self_buffs
	/if (!${doNotBuff} && !${timeForBuffs} && !${Me.XTarget}) /call enc_group_buffs
	/if (!${Me.XTarget}) /call enc_check_mana
	/if (!${Me.XTarget}) /call set_timers

	/while (${Me.XTarget} && ${Mode} == 3) {

		| Have we assisted MA?
		/call get_target

		| If target has beneficial spells we should dispell
		/if (${Int[${Target.Beneficial.ID}]}) {
			/if (${validate_cast[FALSE, alt, "Eradicate Magic", ${Target.ID}]}) /call core_cast2 "Eradicate Magic" alt ${Target.ID} FALSE
		}

		| If target is close enough then dicho
		/if (${Navigation.PathLength[id ${Target.ID}]} <= 150) {
			/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) /call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
		}

		| Do we have a valid target?
		/if (!${validate_combat[${Target.ID}]}) /continue

		| Before debuffing and nuking check if we have to mezz
		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSpell}" "${MezSpell}"

		| Before nuking check if we have to debuff
		/if (${Me.XTarget} > 1) /call enc_debuff_xtarget

		| Tash target if not tashed
		/if (!${Target.Tashed.ID} && !${Target.Buff[${TashSpell}].ID} && ${Target.Type.Equal[NPC]}) {
			/if (${validate_cast[FALSE, spell, "${TashSpell}", ${Target.ID}]}) /call core_cast2 "${TashSpell}" spell ${Target.ID} FALSE
		}

		| If adds verify that they are mezzed
		/if (${Me.XTarget} > 1) /call mezz_xtarget "${AEMezSpell}" "${MezSpell}"

		| Slow the target
		/if (!${Target.Buff[${SlowSpellName}].ID} && !${immuneSet.Contains[${Target.ID}]}) {		
			/if (${validate_cast[FALSE, FIND, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSpellName} \ax <<=
				/call core_cast2 "${SlowSpell}" FIND ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}

		| If there is a named or there are too many mobs then start burning
		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call enc_burn_routine

		| If target is named then hard debuff else stun
		/if (${Target.Named}) {
			/if (!${Target.Buff[${Constriction}].ID}) {
				/if (${validate_cast[FALSE, spell, "${Constriction}", ${Target.ID}]}) /call core_cast2 "${Constriction}" spell ${Target.ID} FALSE
			}
	
			/if (!${Target.Buff[Mental Contortion ${MentalContortionRank}].ID}) {
				/if (${validate_cast[FALSE, alt, "Mental Contortion", ${Target.ID}]}) /call core_cast2 "Mental Contortion" alt ${Target.ID} FALSE
			}
		} else {
			/if (!${Target.Mezzed.ID} && !${Target.Buff[${MezSpell}].ID} && !${immuneSet.Contains[${Target.ID}]} && ${encDoStun}) {
				
				/if (${validate_cast[FALSE, spell, "${SingleStunSpell1}", ${Target.ID}]}) {
					/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Stunning \ar ${Target.Name} \ax with =>> \ag ${SingleStunSpell1} \ax <<=
					/call core_cast2 "${SingleStunSpell1}" spell ${Target.ID} FALSE
					/call check_cast_events "${SingleStunSpell1}" CAST_IMMUNE ${Target.ID}
				}
			}
		}

		/call get_target
		/call enc_rotation
		
		| If we have been knocked back then run back to camp
		/call move_to_camp

		| Check mana even though we are in combat
		/call enc_check_mana
		/call check_state
	}
	/doevents
	/if (${Target.ID}) {
		/target clear
		/delay 1s
	}
/return

Sub enc_rotation(int _tmpID)
	|**
		Dicho -> ITC +IoG -> Robe Click -> Chromatic Haze -> Mindslash
		(Dicho on Cooldown) -> Mindslash -> Mindsunder -> Strangulate
	**|
	/call pet_attack ${_tmpID}

	/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${_tmpID}]}) {
		/call core_cast2 "${DichoSpell}" spell ${_tmpID} FALSE
		/return
	}
	/if (${validate_cast[FALSE, spell, "${MindNukeMain}", ${_tmpID}]}) {
		/call core_cast2 "${MindNukeMain}" spell ${_tmpID} FALSE
		/return
	}
	/if (${validate_cast[FALSE, spell, "${MindNukeSub}", ${_tmpID}]}) {
		/call core_cast2 "${MindNukeSub}" spell ${_tmpID} FALSE
		/return
	}

	/if (${validate_cast[FALSE, spell, "${Drown}", ${_tmpID}]}) {
		/call core_cast2 "${Drown}" spell ${_tmpID} FALSE
		/return
	}

/return

Sub enc_burn_routine
	|**
		IoG -> Chromatic Haze. Third spire as soon as IoG fades.
		Calculated Insanity gives you 100% crit rate regardless of additional modifiers, so try to use it when nothing else is running.
		Some groups may want Third Spire along with IoG if there is no Auspice running.
	**|
	| /notify QuantityWnd QTYW_slider newvalue #                                         Adjust the value of the slider in Quantity Window.
	| /notify BuffWindow Buff${Math.Calc[${Me.Buff[BuffName].ID}-1].Int} leftmouseup     Cancels the buff called "BuffName"
	| /notify AuraWindow AW_AuraList listselect 1
	| /notify AuraWindow AW_AuraList leftmouse 1
	| /notify AuraWindow Remove_Aura leftmouseup

	
	/if (!${Me.Buff[Improved Twincast ${ImprovedTwincastRank}].ID}) {
		/if (${validate_cast[FALSE, alt, "Improved Twincast", ${Me.ID}]}) {
			/call core_cast2 "Improved Twincast" alt 0 FALSE
		}
	}
	/if (${validate_cast[FALSE, spell, "Focus of Arcanum", ${Me.ID}]}) {
		/call core_cast2 "Focus of Arcanum" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, spell, "Chromatic Haze", ${Me.ID}]}) {
		/call core_cast2 "Chromatic Haze" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, spell, "Illusions of Grandeur", ${Me.ID}]}) {
		/call core_cast2 "Illusions of Grandeur" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, spell, "Spire of Enchantment", ${Me.ID}]}) {
		/call core_cast2 "Spire of Enchantment" alt 0 FALSE
	}
	
	/if (!${Me.Song[Chromatic Haze ${ChromaticHazeRank}].ID} && !${Me.Song[Illusions of Grandeur ${IllusionsOfGrandeurRank}].ID}) {
		/if (${validate_cast[FALSE, spell, "Calculated Insanity", ${Me.ID}]}) {
			/call core_cast2 "Calculated Insanity" alt 0 FALSE
		}
	}

/return
|----------------------------------------------------------------------------
|- SUB: enc_debuff_xtarget
|---------------------------------------------------------------------------- 
Sub enc_debuff_xtarget
	/declare _count int local 1
	/attack off
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

		/if (${Target.Named}) {
			/if (!${Target.Buff[${Constriction}].ID}) {
				/if (${validate_cast[FALSE, spell, "${Constriction}", ${Target.ID}]}) /call core_cast2 "${Constriction}" spell ${Target.ID} FALSE
			}
	
			/if (!${Target.Buff[Mental Contortion].ID}) {
				/if (${validate_cast[FALSE, alt, "Mental Contortion", ${Target.ID}]}) /call core_cast2 "Mental Contortion" alt ${Target.ID} FALSE
			}
		}

		| How will you handle the AA?
		/if (!${Target.Buff[${SlowSpellName}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			
			/if (${validate_cast[FALSE, FIND, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar ${Target.Name} \ax with =>> \ag ${SlowSpellName} \ax <<=
				/call core_cast2 "${SlowSpell}" FIND ${Target.ID} FALSE
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
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Set Add of ${Target.ID} failed.
		}

		/delay 3
	/next _count

	/call get_target

/return

|----------------------------------------------------------------------------
|- SUB: enc_check_mana
|---------------------------------------------------------------------------- 
sub enc_check_mana

	| if mana is below the puller check limit
	/if (${Spawn[${Me.Name} pccorpse radius 50].ID}) /return

	/call bag_mod_rod
	/call use_mod_rod

	/if (${Me.PctMana} < 80) {
		/if (${validate_cast[FALSE, item, "${ChestItemName}", ${Me.ID}]}) /call core_cast2 "${ChestItemName}" item 0 FALSE
	}

	/if (${Me.PctMana} < 50) {
		/if (${validate_cast[FALSE, alt, "Gather Mana", ${Me.ID}]}) /call core_cast2 "Gather Mana" alt 0 FALSE
	}

	/if (${Me.PctMana} < 90) {
		/if (${validate_cast[FALSE, alt, "Azure Mind Crystal", ${Me.ID}]}) {
			/call core_cast2 "Azure Mind Crystal" alt 0 FALSE

			/if (${Me.FreeInventory} >= 1) /autoinventory

			/if (${validate_cast[FALSE, item, "Azure Mind Crystal ${AzureMindCrystalRank}", ${Me.ID}]}) /call core_cast2 "Azure Mind Crystal ${AzureMindCrystalRank}" item 0 FALSE
		}
	}

/return
|----------------------------------------------------------------------------
|- SUB: self_buffs
|---------------------------------------------------------------------------- 
Sub enc_self_buffs

	/declare CastCheck			int local 0

	/if (${Me.XTarget}) /return
	
	/if (!${Me.Buff[${SelfHPBuff}].ID} && !${Me.Buff[${SelfHPBuffName}].ID}) {
		/if (${validate_cast[FALSE, FIND, "${SelfHPBuff}", ${Me.ID}]}) {
			/call core_cast2 "${SelfHPBuff}" FIND ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (!${Me.Pet.ID} && ${FindItem[=Tiny Dagger].ID}) {
		/if (${validate_cast[FALSE, spell, "${PetSpell}", ${Me.ID}]}) {
			/call core_cast2 "${PetSpell}" spell 0 FALSE
			/varset CastCheck 1
		}
		/if (${Me.Pet.ID}) /pet guard
	}

	/if (${Me.Pet.ID} && !${Me.Pet.Buff[${PetBuffSpell}]} && !${Me.Pet.Buff[${PetBuffName}]}) {
		/if (${validate_cast[FALSE, spell, "${PetBuffSpell}", ${Me.Pet.ID}]}) {
			/call core_cast2 "${PetBuffSpell}" spell ${Me.Pet.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (!${Me.Buff[${MezBuff}].ID} && !${Me.Buff[${MezBuffName}].ID}) {
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
	/if (!${Me.Buff[${SelfRune1}].ID} && !${Me.Buff[${SelfRune1Name}].ID}) {
		/if (${validate_cast[FALSE, spell, "${SelfRune1}", ${Me.ID}]}) {
			/call core_cast2 "${SelfRune1}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	} 

	/if (!${Me.Buff[${SelfRune2}].ID} && !${Me.Buff[${SelfRune2Name}].ID}) {
		/if (${validate_cast[FALSE, spell, "${SelfRune2}", ${Me.ID}]}) {
			/call core_cast2 "${SelfRune2}" spell ${Me.ID} FALSE
			/varset CastCheck 1
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
Sub enc_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (${Me.XTarget}) /return
	/if (!${Group}) /return
	/if (${Group.Member[${Group.MainTank}].OtherZone}) /return
	
	/for _count 0 to ${Group}
	
		/if (${Group.Member[${_count}].Distance} < 100 && !${Group.Member[${_count}].OtherZone}) {
			
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
			/if (!${tmpbuffid} && !${jaanbuffid} && ${tmpstackcheck} && ${Select[${Group.Member[${_count}].Class.ShortName},BRD,BST,BER,MNK,PAL,RNG,ROG,SHD]}) {
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