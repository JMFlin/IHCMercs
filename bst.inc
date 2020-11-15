|----------------------------------------------------------------------------
|- SUB: bst_main
|---------------------------------------------------------------------------- 

|**
The other key that I’m always mashing contains several combat/melee abilities:

	Bestial Evulsing
	Maul
	Kick (the standard combat ability from the Abilities Page [ALT+A])
	Feral Swipe
	Gorilla Smash
	Roaring Strike
	Focused Clamor of Claws or Tempest of Claws (event pending)

Method 3

	Slot 1: Dichotomic Fury
	Slot 2: Maelstrom
	Slot 3: Glistenwing
	(Unlinked) Slot 4: Miasma
	(Unlinked) Slot 5: Kirchen’s Chill

	Result: This is the option that I like to go with, where only the first three slots are linked to the keybind. 
	This will make sure that Maelstrom is always cast before Glistenwing, and then I will manually cast Miasma each time that Maelstrom is on lockout. 
	As discussed, I’ll hit Chill only when it’s warranted.


**|
Sub bst_main
	
	/if (!${Me.XTarget}) /call bst_self_buffs
	/if (!${doNotBuff}) /call bst_group_buffs

	/while (${Me.XTarget} && ${Mode} == 3) {
		
		/call get_target

		/if (!${Target.Slowed.ID} && !${Target.Buff[${SlowSpell}].ID} && !${immuneSet.Contains[${Target.ID}]}) {
			/if (${validate_cast[FALSE, spell, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing\ar ${Target.Name} \ax with =>> \ag ${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" spell ${Target.ID} FALSE
				/call check_cast_events "${SlowSpell}" CAST_IMMUNE ${Target.ID}
			}
		}

		/if (!${validate_combat[${Target.ID}]}) /continue

		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call bst_burn_routine

		/call engage
		/call pet_attack ${Target.ID}

		/if (${validate_cast[FALSE, alt, "Taste of Blood", ${Me.ID}]}) {
			/call core_cast2 "Taste of Blood" alt ${Me.ID} FALSE
		}

		/if (${Target.PctHPs} > 30) {
			/if (${validate_cast[FALSE, alt, "Attack of the Warders", ${Target.ID}]}) {
				/call core_cast2 "Attack of the Warders" alt ${Target.ID} FALSE
			}
		}

		/if (${Target.PctHPs} > 30) {
			/if (${validate_cast[FALSE, spell, "${SwarmPet}", ${Target.ID}]}) {
				/call core_cast2 "${SwarmPet}" spell ${Target.ID} FALSE
			}
		}

		/if (${Target.PctAggro} > 30) {
			/if (${validate_cast[FALSE, alt, "Roar of Thunder", ${Target.ID}]}) {
				/call core_cast2 "Roar of Thunder" alt ${Target.ID} FALSE
			}
		}

		/if (${validate_cast[FALSE, alt, "Enduring Frenzy", ${Target.ID}]}) {
			/call core_cast2 "Enduring Frenzy" alt 0 FALSE
		}

		/if (${Target.Named} || ${Target.PctHPs} > 80) {
			/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceSpell}" ${Target.ID}
		}

		/call use_skill_melee ${Target.ID} FALSE

		|**
			Dichotomic Fury -> Maelstrom -> Glistenwing -> Miasma -> Kirchen’s Chill
		**|
		/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) {
			/call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
		} else /if (!${Me.Buff[Quick Time].ID}) { |- How to find a string from buffs?
			/if (${validate_cast[FALSE, alt, "Ruaabri's Fury", ${Me.ID}]}) {
				/call core_cast2 "Ruaabri's Fury" alt ${Me.ID} FALSE
			}
		}

		/if (${validate_cast[FALSE, spell, "${MaelstromNuke}", ${Target.ID}]}) {
			/call core_cast2 "${MaelstromNuke}" spell ${Target.ID} FALSE
		}

		/if (!${Target.Buff[${BloodDoT}].ID} && !${Me.Buff[Frenzy of Spirit].ID} && !${Me.Buff[Bestial Alignment].ID}) {
			/if (${validate_cast[FALSE, spell, "${BloodDoT}", ${Target.ID}]}) {
				/call core_cast2 "${BloodDoT}" spell ${Target.ID} FALSE
			}
		}

		/if (${validate_cast[FALSE, spell, "${FrozenNuke}", ${Target.ID}]}) {
			/call core_cast2 "${FrozenNuke}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Forceful Rejuvenation", ${Me.ID}]}) {
				
			/call core_cast2 "Forceful Rejuvenation" alt 0 FALSE

			/if (${validate_cast[FALSE, spell, "${MaelstromNuke}", ${Target.ID}]}) {
				/call core_cast2 "${MaelstromNuke}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${FrozenNuke}", ${Target.ID}]}) {
				/call core_cast2 "${FrozenNuke}" spell ${Target.ID} FALSE
			}
		}

		/if (!${Target.Buff[${ChillDoT}].ID} && ${Target.Named} && !${Me.Buff[Frenzy of Spirit].ID} && !${Me.Buff[Bestial Alignment].ID}) {
			/if (${validate_cast[FALSE, spell, "${ChillDoT}", ${Target.ID}]}) {
				/call core_cast2 "${ChillDoT}" spell ${Target.ID} FALSE
			}
		}

		|**
			Bestial Evulsing -> Maul -> Feral Swipe -> Gorilla Smash ->	Roaring Strike -> Focused Clamor of Claws or Tempest of Claws (event pending)
		**|
		/if (${validate_cast[FALSE, disc, ${Maul}, ${Target.ID}]}) {
			/call core_cast2 ${Maul} disc ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, disc, "Bestial Evulsing", ${Target.ID}]}) {
			/call core_cast2 "Bestial Evulsing" disc ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, disc, "${Smash}", ${Target.ID}]}) {
			/call core_cast2 "${Smash}" disc ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, alt, "Roaring Strike", ${Target.ID}]}) {
			/call core_cast2 "Roaring Strike" alt ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, disc, "${SingleClaws}", ${Target.ID}]}) {
			/call core_cast2 "${SingleClaws}" disc ${Target.ID} FALSE
		}

		/call get_heal_target 40
		/varset worstHurtId ${Macro.Return}
		/if (${worstHurtId} > 0) {
			/if (${validate_cast[FALSE, spell, "${Mending}", ${worstHurtId}]}) {
				/call core_cast2 "${Mending}" spell ${worstHurtId} FALSE
			}
		}
		/call bst_mana_check
		/call bst_pet_hp_check
		/call move_to_camp
	}

/return
|----------------------------------------------------------------------------
|- SUB: self_buff_check
|---------------------------------------------------------------------------- 
Sub bst_self_buffs
	/declare CastCheck			int local 0

	/if (!${Me.Buff[${KillShotBuff}]}) {
		/if (${validate_cast[FALSE, FIND, "Feralist's Unity", ${Me.ID}]}) {
			/call core_cast2 "Feralist's Unity" FIND ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${validate_cast[FALSE, alt, "Pact of the Wurine", ${Me.ID}]}) {
		/call core_cast2 "Pact of the Wurine" alt ${Me.ID} FALSE
	}
	
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

		/if (!${Me.Pet.Buff[${Me.AltAbility[Companion's Aegis].Rank}]}) {
			/if (${validate_cast[FALSE, alt, "Companion's Aegis", ${Me.Pet.ID}]}) {
				/call core_cast2 "Companion's Aegis" alt ${Me.Pet.ID} FALSE
			}
		}
	}

	/if (${validate_cast[FALSE, spell, "${FocusSpell}", ${Me.ID}]}) {
		/call core_cast2 "${FocusSpell}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub bst_mana_check
	/if (${Me.PctMana} < 85) {
		/if (${validate_cast[FALSE, alt, "Consumption of Spirit", ${Me.ID}]}) {
			/call core_cast2 "Consumption of Spirit" alt 0 FALSE
		}
	}

	/call bag_mod_rod
	/call use_mod_rod

/return
|----------------------------------------------------------------------------
|- SUB: combat 
|---------------------------------------------------------------------------- 
Sub bst_pet_hp_check
	/if (${Me.Pet.ID} < 50) {
		/if (${validate_cast[FALSE, alt, "Companion's Shielding", ${Me.Pet.ID}]}) {
			/call core_cast2 "Companion's Shielding" alt 0 FALSE
		}
	}
	/if (${Me.Pet.ID} < 20) {
		/if (${validate_cast[FALSE, alt, "Second Wind Ward", ${Me.Pet.ID}]}) {
			/call core_cast2 "Second Wind Ward" alt 0 FALSE
		}
	}

	/if (${Me.Pet.ID} < 70) {
		/if (${validate_cast[FALSE, alt, "Mend Companion", ${Me.Pet.ID}]}) {
			/call core_cast2 "Mend Companion" alt 0 FALSE
		}
	}

/return
|----------------------------------------------------------------------------
|- SUB: combat 
|---------------------------------------------------------------------------- 
Sub bst_burn_routine(int _tmpID)
	|**
		Frenzy of Spirit -> Bestial Alignment -> Bloodlust -> Frenzied Swipes -> Al`ele's Vindication
	**|
	/if (${validate_cast[FALSE, alt, "${ChestItemName}", ${Me.ID}]}) {
		/call core_cast2 "${ChestItemName}" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Spire of the Savage Lord", ${Me.ID}]}) {
		/call core_cast2 "Spire of the Savage Lord" alt 0 FALSE
	}
	/if (${burnRotation} == 1) {

		/if (${validate_cast[FALSE, alt, "Frenzy of Spirit", ${Me.ID}]}) {
			/call core_cast2 "Frenzy of Spirit" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, alt, "Bestial Alignment", ${Me.ID}]}) {
			/call core_cast2 "Bestial Alignment" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, alt, "Bloodlust", ${Me.ID}]}) {
			/call core_cast2 "Bloodlust" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, alt, "Frenzied Swipes", ${Me.ID}]}) {
			/call core_cast2 "Frenzied Swipes" alt 0 FALSE
		}

		/if (${validate_cast[FALSE, disc, "Al`ele's Vindication", ${Me.ID}]}) {
			/call core_cast2 "Al`ele's Vindication" disc 0 FALSE
		}

		/if (!${Me.Buff[Bestial Alignment].ID}) {
			/varcalc burnRotation ${burnRotation} + 1
		}
	} else /if (${burnRotation} == 2) {
		
		/if (${validate_cast[FALSE, alt, "Savage Rancor", ${Me.ID}]}) {
			/call core_cast2 "Savage Rancor" alt 0 FALSE
		}
		
		/if (!${Me.Buff[Savage Rancor].ID}) {
			/varcalc burnRotation ${burnRotation} + 1
		}
	} else /if (${burnRotation} == 3) {
		
		/if (${validate_cast[FALSE, alt, "Ferociousness", ${Me.ID}]}) {
			/call core_cast2 "Ferociousness" alt 0 FALSE
		}
		
		/if (!${Me.Buff[Ferociousness].ID}) {
			/varcalc burnRotation ${burnRotation} + 1
		}
	} else /if (${burnRotation} == 4) {
		
		/if (${validate_cast[FALSE, alt, "Group Bestial Alignment", ${Me.ID}]}) {
			/call core_cast2 "Group Bestial Alignment" alt 0 FALSE
		}
		
		/if (!${Me.Buff[Group Bestial Alignment].ID}) {
			/varset burnRotation 1
		}
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
			/if (${validate_cast[FALSE, spell, "${SlowSpell}", ${Target.ID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Slowing \ar${Target.Name} \ax with =>> \ag${SlowSpell} \ax <<=
				/call core_cast2 "${SlowSpell}" spell ${Target.ID} FALSE
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
|- SUB: BuffGroup
|---------------------------------------------------------------------------- 
Sub bst_group_buffs
	/declare _count			int local 0
	/declare CastCheck			int local 0

	/if (!${Group}) /return
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

		/if (${Group.Member[${_count}].Distance} > 200) /continue

		
		/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${ManaRegenBuff}].ID" "tmpbuffid" "int"
		/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${ManaRegenBuff}].Stacks" "tmpstackcheck" "bool"
		/if (!${tmpbuffid} && ${tmpstackcheck}) {
			/if (${validate_cast[FALSE, spell, ${ManaRegenBuff}, ${Group.Member[${_count}].ID}]}) {
				/call core_cast2 "${ManaRegenBuff}" spell ${Group.Member[${_count}].ID} FALSE
				/varset CastCheck 1
			}
		}
		/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${AtkBuff}].ID" "tmpbuffid" "int"
		/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${AtkBuff}].Stacks" "tmpstackcheck" "bool"
		/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
		|	/if (${validate_cast[FALSE, spell, ${AtkBuff}, ${Group.Member[${_count}].ID}]}) /call core_cast2 "${AtkBuff}" spell ${Group.Member[${_count}].ID} FALSE
		|		/varset CastCheck 1
		}

		/if (!${bstDoNotBuffShm}) {
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${FocusSpell}].ID" "tmpbuffid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Focus.ID" "tmpfocusid" "int"
			/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${FocusSpell}].Stacks" "tmpstackcheck" "bool"
			/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
				/if (${validate_cast[FALSE, spell, ${FocusSpell}, ${Group.Member[${_count}].ID}]}) {
					/call core_cast2 "${FocusSpell}" spell ${Group.Member[${_count}].ID} FALSE
					/varset CastCheck 1
				}
			}
			
			/if (!${bstDoNotBuffDru}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${RunSpeedBuff}].ID" "tmpbuffid" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${RunSpeedBuff}].Stacks" "tmpstackcheck" "bool"
				/if (!${tmpbuffid} && ${tmpstackcheck}) {
					/if (${validate_cast[FALSE, spell, ${RunSpeedBuff}, ${Group.Member[${_count}].ID}]}) {
						/call core_cast2 "${RunSpeedBuff}" spell ${Group.Member[${_count}].ID} FALSE
						/varset CastCheck 1
					}		
				}
			}
			
			/if (!${bstDoNotBuffEnc}) {
				/if (${PetHasteRecourse.Equal[NULL]}) {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${Haste}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${Haste}].Stacks" "tmpstackcheck" "bool"
					/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
						/if (${validate_cast[FALSE, spell, ${Haste}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${Haste}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
				} else {
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Buff[${PetHaste}].ID" "tmpbuffid" "int"
					/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${PetHaste}].Stacks" "tmpstackcheck" "bool"
					/if (!${tmpbuffid} && ${tmpstackcheck} && !${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
						/if (${validate_cast[FALSE, spell, ${PetHaste}, ${Group.Member[${_count}].ID}]}) {
							/call core_cast2 "${PetHaste}" spell ${Group.Member[${_count}].ID} FALSE
							/varset CastCheck 1
						}
					}
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