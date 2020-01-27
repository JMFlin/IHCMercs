|----------------------------------------------------------------------------
|- SUB: wiz_main
|----------------------------------------------------------------------------
Sub wiz_main

	
	/call wiz_self_buff_check FALSE

	/call get_target
|-	/call PetAttack
|-	/if (${Me.XTarget[1].ID} && ${Target.Distance}<=${AssistRange} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight} && ${Target.Type.Equal[NPC]} && ${Target.PctHPs}<=${AutoDebuffAt}) /call DebuffMobs
|-	/if (${Me.XTarget[1].ID} && ${Target.Distance}<${AssistRange}) /call AANDisc
	/call wiz_combat

|-	/if (${UseModRods}) /call ClickModRoD
	
|-	/if ((${Me.Poisoned.ID} || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} || ${Me.Snared.ID} || ${Me.Mezzed.ID} || ${Me.Charmed.ID}) && ${BegTimer}==0) /call BegForCure
	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: DebuffMobs
|---------------------------------------------------------------------------- 
Sub wiz_debuff
	/if (${Me.Casting.ID}) /return
	/if (${Target.Beneficial.ID} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
		/if (${Me.AltAbilityReady[${StripBuffSpell}]}) {
			/alt act ${Me.AltAbility[${StripBuffSpell}].ID}
			/delay 10 ${Window[CastingWindow].Open}
			/delay 10 !${Me.Casting.ID}
		} else /if (${Me.SpellReady[${StripBuffSpell}]}) {
			/call CastSpell "${StripBuffSpell}" ${autotargetid} dbf
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub wiz_aa_and_disc
	/if (${Target.PctHPs}>20 && ${Me.PctAggro}>50 && ${Me.AltAbilityReady[Concussive Intuition]}) {
		/alt act ${Me.AltAbility[Concussive Intuition].ID}
		/delay 5
	} else /if ((${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && ${Target.PctHPs}>10 && ${Me.AltAbilityReady[Arcane Whisper]}) {
		/alt act ${Me.AltAbility[Arcane Whisper].ID}
		/delay 5
	} else /if ((${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && ${Target.PctHPs}>10 && ${Me.AltAbilityReady[Mind Crash]}) {
		/alt act ${Me.AltAbility[Mind Crash].ID}
		/delay 5
	} else /if ((${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && ${Me.AltAbilityReady[Silent Casting]}) {
		/alt act ${Me.AltAbility[Silent Casting].ID}
		/delay 5
	} else /if (${Target.PctHPs}>20 && ${Me.PctAggro}>=80 && (${Me.SpellReady[${JoltSpell}]}) && ${Me.CurrentMana}>${Spell[${JoltSpell}].Mana}) {
		/call CastSpell "${JoltSpell}" ${autotargetid} AANDisc
	} else /if (${Target.PctHPs}>20 && ${Me.PctAggro}>=99 && ${Me.AltAbilityReady[A Hole In Space]}) {
		/alt act ${Me.AltAbility[A Hole In Space].ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Fury of the Gods]}) { 
		/alt act ${Me.AltAbility[Fury of the Gods].ID}
		/delay 5
	}
	/if (${Me.AltAbilityReady[Focus of Arcanum]}) {
		/alt act ${Me.AltAbility[Focus of Arcanum].ID}
		/delay 5
	}
	/if (${Me.PctMana}<45 && ((!${Me.SpellReady[${GambitSpell}]} && ${Me.Gem[${GambitSpell}]}) || (!${Me.SpellReady[${HarvestSpell}]} && ${Me.Gem[${HarvestSpell}]})) && ${Me.AltAbilityReady[Forceful Rejuvenation]}) {
		/alt act ${Me.AltAbility[Forceful Rejuvenation].ID}
		/delay 5
	}
	/if (${Cast.Ready[${ChestItemName}]} && ${Me.PctMana}<${HarvestManaPct} && ${ChestCombatCast} && ${FindItem[${ChestItemName}].ID} && !${Me.Song[${GambitSpell}].ID}) {
		/useitem "${ChestItemName}"
		/delay 10
	} else /if (${Me.PctMana}<${HarvestManaPct} && !${Me.Song[${GambitSpell}].ID} && !${Me.Song[Evoker's Synergy I].ID} && ${Me.AltAbilityReady[Harvest of Druzzil]}) {
		/alt act ${Me.AltAbility[Harvest of Druzzil].ID}
		/delay 5
	}
	/if (${Target.ID} && ${Target.PctHPs}>=50 && ${Target.PctHPs}<=99 && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && ${Me.AltAbilityReady[Call of Xuzl]}) {
		/alt act ${Me.AltAbility[Call of Xuzl].ID}
		/delay 5
	}
	/if (${Target.ID} && ${Target.PctHPs}>=80 && ${Target.PctHPs}<=99 && !${Target.Buff[Lower Element III].ID} && ${Me.AltAbilityReady[Lower Element]}) {
		/alt act ${Me.AltAbility[Lower Element].ID}
		/delay 5
	}
	/if (!${Me.Song[Arcane Destruction].ID} && ${Me.AltAbilityReady[Frenzied Devastation]}) {
		/alt act ${Me.AltAbility[Frenzied Devastation].ID}
		/delay 5
	} else /if (!${Me.Song[Frenzied Devastation].ID} && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && ${Me.AltAbilityReady[Arcane Destruction]}) {
		/alt act ${Me.AltAbility[Arcane Destruction].ID}
		/delay 5
	}
	/if (${Target.ID} && ${Target.PctHPs} > 1 && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && !${Me.Song[Chromatic Haze].ID} && !${Me.Song[Gift of Chromatic Haze].ID} && (${Me.Song[Arcane Destruction].ID} || ${Me.Song[Frenzied Devastation].ID}) && ${Me.AltAbilityReady[Arcane Fury]}) {
		/alt act ${Me.AltAbility[Arcane Fury].ID}
		/delay 5
	}
	/if (${Me.Song[Frenzied Devastation].ID} || ${Me.Song[Arcane Destruction].ID} && ${Me.AltAbilityReady[Fundament: Second Spire of Arcanum]}) {
		/alt act ${Me.AltAbility[Fundament: Second Spire of Arcanum].ID}
		/delay 5
	}
	/if (${Target.ID} && ${Target.PctHPs}>1 && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && !${Me.Buff[Twincast].ID} && ${Me.AltAbilityReady[Improved Twincast]}) {
		/alt act ${Me.AltAbility[Improved Twincast].ID}
		/delay 5
	} else /if (!${Me.Buff[Twincast].ID} && !${Me.Buff[Improved Twincast].ID} && (${Me.SpellReady[${TwincastSpell}]}) && ${Me.CurrentMana}>${Spell[${TwincastSpell}].Mana}) {
		/call CastSpell "${TwincastSpell}" ${autotargetid} dps
	}
	/if (${Target.ID} && (${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && ${Target.PctHPs}>=20 && ${Target.PctHPs}<=96 && ${Target.BuffsPopulated} && !${Target.Buff[Mana Burn].ID} && ${Me.AltAbilityReady[Mana Burn]} && ${UseManaBurn}) {
		/alt act ${Me.AltAbility[Mana Burn].ID}
		/delay 5
	}
/return
|----------------------------------------------------------------------------
|- SUB: combat
|---------------------------------------------------------------------------- 
Sub wiz_combat
	| if mana is below the puller check limit
	/if ((${Me.XTarget} && ${Me.PctMana} < 20) || (!${Me.XTarget} && ${Me.PctMana} < ${Limit})) {

		| If my corpse is near then don't waste harvest
		/if (!${Spawn[${Me.Name} pccorpse radius 50].ID}) {
			
			| Trigger first harvest
			/if (${validate_cast[FALSE, FIND, "${HarvestSpell1}", ${Me.ID}]}) /call core_cast2 "${HarvestSpell1}" FIND 0 FALSE
		}
	}

	/call get_target
	/if (!${validate_combat[${Target.ID}]} ) /return

	/if (${Me.Book[${SnareSpell}]} && !${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]}) {
		/if (${validate_cast[FALSE, spell, "${SnareSpell}", ${Target.ID}]}) {
			/call core_cast2 "${SnareSpell}" spell ${Target.ID} FALSE
			/call check_cast_events "${SnareSpell}" CAST_IMMUNE ${Target.ID}
		}
	} else /if (${Target.PctHPs} < 40 && !${Target.Rooted.ID} && !${Target.Snared.ID} && !${immuneSet.Contains[${Target.ID}]}) {
		/if (${validate_cast[FALSE, spell, "${RootSpell}", ${Target.ID}]}) {
			/call core_cast2 "${RootSpell}" spell ${Target.ID} FALSE
			/call check_cast_events "${RootSpell}" CAST_IMMUNE ${Target.ID}
		}
	}

	/if (${validate_cast[FALSE, spell, "${SelfRune1}", ${Me.ID}]}) {
		/call core_cast2 "${SelfRune1}" spell 0 FALSE
	}

	/if (${Target.PctHPs} >= 100) /return

	/if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) {
		/call core_cast2 "${TwincastSpell}" spell ${Target.ID} FALSE
	}

	/if (${Me.Buff[Improved Twincast].ID}) {

		/if (${validate_cast[FALSE, spell, "${FuseNuke}", ${Target.ID}]}) {
			/call core_cast2 "${FuseNuke}" spell ${Target.ID} FALSE
		}
		
		/if (${validate_cast[FALSE, spell, "${DichoSpell}", ${Target.ID}]}) {
			/call core_cast2 "${DichoSpell}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, spell, "${FireEtherealNuke}", ${Target.ID}]}) {
			/call core_cast2 "${FireEtherealNuke}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, spell, "${ColdEtherealNuke}", ${Target.ID}]}) {
			/call core_cast2 "${ColdEtherealNuke}" spell ${Target.ID} FALSE
		}

	} else /if (${Me.Buff[Twincast].ID} && ${Me.Buff[Fury of the Gods].ID}) {

		/if (${validate_cast[FALSE, spell, "${WildNuke}", ${Target.ID}]}) {
			/call core_cast2 "${WildNuke}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, spell, "${FuseNuke}", ${Target.ID}]}) {
			/call core_cast2 "${FuseNuke}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, spell, "${CloudburstNuke}", ${Target.ID}]}) {
			/call core_cast2 "${CloudburstNuke}" spell ${Target.ID} FALSE
		}

	} else {
	
		/if (${validate_cast[FALSE, spell, "${ClawNuke}", ${Target.ID}]}) {
			/call core_cast2 "${ClawNuke}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, spell, "${FuseNuke}", ${Target.ID}]}) {
			/call core_cast2 "${FuseNuke}" spell ${Target.ID} FALSE
		}

		/call wiz_manage_aggro

		/if (${validate_cast[FALSE, spell, "${CloudburstNuke}", ${Target.ID}]}) {
			/call core_cast2 "${CloudburstNuke}" spell ${Target.ID} FALSE
		}

		/if (${validate_cast[FALSE, spell, "${FireEtherealNuke}", ${Target.ID}]}) {
			/call core_cast2 "${FireEtherealNuke}" spell ${Target.ID} FALSE
		}

		/call wiz_manage_aggro
	}
/return


	|	/call AANDisc
	|/if (${Target.PctHPs}>=30 && ${Target.PctHPs}<=99 && ${Me.PctMana}<=${HarvestManaPct} && ${Me.SpellReady[${GambitSpell}]} && ${Me.CurrentMana}>${Spell[${GambitSpell}].Mana}) {
	|	/call CastSpell "${GambitSpell}" ${autotargetid} dps
	|} else /if (${Me.XTarget}<2 && ${SpawnCount[npc los radius 60 zradius 10]}<2 && ${Target.Distance}>=30 && ${Target.Distance}<=60 && ${Me.Song[${GambitSpell}].ID} && (${Me.SpellReady[${MagmaticAENuke}]}) && ${Me.CurrentMana}>${Spell[${MagmaticAENuke}].Mana}) {
	|	/call CastSpell "${MagmaticAENuke}" ${autotargetid} dps
	|} else /if ((${Me.Song[${GambitSpell}].ID} || ${Me.Song[Evoker's Synergy I].ID}) && (${Me.SpellReady[${CloudburstNuke}]}) && ${Me.CurrentMana}>${Spell[${CloudburstNuke}].Mana}) {
	|	/call CastSpell "${CloudburstNuke}" ${autotargetid} dps
	|} else /if (${Me.Song[${GambitSpell}].ID} && (${Me.SpellReady[${WildNuke}]}) && ${Me.CurrentMana}>${Spell[${WildNuke}].Mana}) {
	|	/call CastSpell "${WildNuke}" ${autotargetid} dps
	|} else /if (${Me.Song[${GambitSpell}].ID} && (${Me.SpellReady[${ChaosNuke}]}) && ${Me.CurrentMana}>${Spell[${ChaosNuke}].Mana}) {
	|	/call CastSpell "${ChaosNuke}" ${autotargetid} dps
	|} else /if (${Target.BuffsPopulated} && ((!${Me.Song[Evoker's Synergy I].ID}) || (!${Target.Buff[${VortexNuke}].ID})) && ${Me.SpellReady[${VortexNuke}]} && ${Me.CurrentMana}>${Spell[${VortexNuke}].Mana}) {
	|	/call CastSpell "${VortexNuke}" ${autotargetid} dps
	|} else /if ((${Me.Song[Gift of Mana].ID} || ${Me.Song[Gracious Gift of Mana (105)].ID}) && !${Me.Song[${GambitSpell}].ID} && !${Me.Buff[Twincast].ID} && !${Me.Buff[Improved Twincast].ID} && (${Me.SpellReady[${DichoSpell}]}) && ${Me.CurrentMana}>${Spell[${DichoSpell}].Mana}) {
	|	/call CastSpell "${DichoSpell}" ${autotargetid} dps
	|} else /if ((${Me.Song[Gift of Mana].ID} || ${Me.Song[Gracious Gift of Mana (105)].ID} || ${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && (${Me.SpellReady[${FuseNuke}]}) && ${Me.CurrentMana}>${Spell[${FuseNuke}].Mana}) {
	|	/call CastSpell "${FuseNuke}" ${autotargetid} dps
	|} else /if ((${Me.Song[Gift of Mana].ID} || ${Me.Song[Gracious Gift of Mana (105)].ID} || ${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && (${Me.SpellReady[${FireEtherealNuke}]}) && ${Me.CurrentMana}>${Spell[${FireEtherealNuke}].Mana}) {
	|	/call CastSpell "${FireEtherealNuke}" ${autotargetid} dps
	|} else /if ((${Me.Song[Gift of Mana].ID} || ${Me.Song[Gracious Gift of Mana (105)].ID} || ${Me.XTarget}>=${BurnMobCount} || (${Target.Named} && ${BurnNamed}) || ${BurnAlways} || ${burnnow}) && (${Me.SpellReady[${ColdEtherealNuke}]}) && ${Me.CurrentMana}>${Spell[${ColdEtherealNuke}].Mana}) {
	|	/call CastSpell "${ColdEtherealNuke}" ${autotargetid} dps
	|} else /if (${Me.Level}>=96 && (${Me.SpellReady[${ClawNuke}]}) && ${Me.CurrentMana}>${Spell[${ClawNuke}].Mana}) {
	|	/call CastSpell "${ClawNuke}" ${autotargetid} dps
	|} else /if (!${Me.Song[${GambitSpell}].ID} && (${Me.SpellReady[${FuseNuke}]}) && ${Me.CurrentMana}>${Spell[${FuseNuke}].Mana}) {
	|	/call CastSpell "${FuseNuke}" ${autotargetid} dps
	|} else /if (!${Me.Song[${GambitSpell}].ID} && (${Me.SpellReady[${FireEtherealNuke}]}) && ${Me.CurrentMana}>${Spell[${FireEtherealNuke}].Mana}) {
	|	/call CastSpell "${FireEtherealNuke}" ${autotargetid} dps
	|}
	|else /if (!${Me.Song[${GambitSpell}].ID} && ${validate_cast[FALSE, spell, "${FastNuke1}", ${Target.ID}]}) {
	|	/call core_cast2 "${FastNuke1}" spell ${Target.ID} FALSE
	|} else /if (${validate_cast[FALSE, spell, "${GeneralNuke1}", ${Target.ID}]}) {
	|	/call core_cast2 "${GeneralNuke1} spell ${Target.ID} FALSE
	|} else /if (${validate_cast[FALSE, spell, "${ClawNuke}", ${Target.ID}]}) {
	|	/call core_cast2 "${ClawNuke}" spell ${Target.ID} FALSE
	|} 
	
|	/if (${CastResult.Equal[CAST_SUCCESS]} || ${CastResult.Equal[CAST_RESIST]}) /varset DPSRecastTimer 0
|	/if (${WeaveAANukes} && !${AANukeRecasttimer}) /call AANukes
	

|***
 *	DES: Class self buffs
 *	USE: /call ${validate_cast[[TRUE|FALSE], [spell|alt|disc|item|pulse|FIND], name, targetID, ForceTarget]
 *	NOTE: This is designed tomake sure whatever we are attempting to cast, is castable. be it a disc, item, spell, booger flick.. whatever.. IS IT READY TO BE USED?
 ***|

Sub wiz_self_buff_check(bool _debug)
	/declare CastCheck			int local 0
	
	/if (${Me.XTarget}) /return

	/if (${validate_cast[FALSE, alt, "${ACPyromancy}", ${Me.ID}]}) /call core_cast2 "${ACPyromancy}" alt ${Me.ID} FALSE

	/if (${validate_cast[FALSE, FIND, "${FamiliarBuff}", ${Me.ID}]}) {
		/call core_cast2 "${FamiliarBuff}" FIND ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${validate_cast[FALSE, FIND, "${SelfHPBuff}", ${Me.ID}]}) {
		/call core_cast2 "${SelfHPBuff}" FIND ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${validate_cast[FALSE, spell, "${SelfRune1}", ${Me.ID}]}) {
		/call core_cast2 "${SelfRune1}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}

	/if (${CastCheck}) {
		/call ${Me.Class.ShortName.Lower}_load_spellbar
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Done Buffing
	}

/return
|----------------------------------------------------------------------------
|- SUB: BurnRoutine
|---------------------------------------------------------------------------- 
Sub BurnRoutine

/return
|----------------------------------------------------------------------------
|- SUB: ManageAggro
|---------------------------------------------------------------------------- 
Sub wiz_manage_aggro
	
	/if (${Target.PctHPs} < 35) /return
	/if (${Me.Buff[Twincast].ID}) /return

	/if (${Target.PctAggro} > 30) {
		/if (${validate_cast[FALSE, spell, "${JoltSpell}", ${Target.ID}]}) /call core_cast2 "${JoltSpell}" spell ${Target.ID} FALSE
	}
/return
|----------------------------------------------------------------------------
|- SUB: Handle Buff Requests
|----------------------------------------------------------------------------
Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
	/if (${Spawn[pc ${ChatSender}].ID} && ${ChatType.Equal[tell]}) /mqlog ${ChatSender} -- ${ChatText}
	/if (${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}) {
		|-/if (${Select[${ChatText},voice,crack,clarity,kei]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /call SpellQueue ${SingleMana} ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
		|-/if (${Select[${ChatText},haste,speed,zing]} && (${Spawn[${ChatSender.Right[-2].Left[-1]}].Distance}<100)) /call SpellQueue ${SingleHaste} ${Spawn[${ChatSender.Right[-2].Left[-1]}].ID}
	}
/return 