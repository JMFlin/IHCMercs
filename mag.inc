|----------------------------------------------------------------------------
|- SUB: wiz_main
|----------------------------------------------------------------------------
Sub mag_main

	
	/call mag_self_buff_check FALSE
	/call get_target
	/call mag_combat
	
	/doevents
	
/return
|----------------------------------------------------------------------------
|- SUB: DebuffMobs
|---------------------------------------------------------------------------- 
Sub mag_debuff
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
Sub mag_aa_and_disc

/return
|----------------------------------------------------------------------------
|- SUB: combat
|---------------------------------------------------------------------------- 
Sub mag_combat

	/call get_target
	/if (!${validate_combat[${Target.ID}]} ) /return
    /call pet_attack

	/if (${Target.PctHPs} >= 100) /return

    /if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) {
		/call core_cast2 "${TwincastSpell}" spell ${Target.ID} FALSE
	}

    /if (${Me.Buff[Improved Twincast].ID}) {

		/if (${validate_cast[FALSE, spell, "${ServantSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ServantSpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ManySpell}", ${Target.ID}]}) {
            /call core_cast2 "${ManySpell}" spell ${Target.ID} FALSE
        }
        
        /if (${validate_cast[FALSE, spell, "${SpearSpell1}", ${Target.ID}]}) {
            /call core_cast2 "${SpearSpell1}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${SpearSpell2}", ${Target.ID}]}) {
            /call core_cast2 "${SpearSpell2}" spell ${Target.ID} FALSE
        }

	} else /if (${Me.Buff[Twincast].ID}) {

		/if (${validate_cast[FALSE, spell, "${ChaoticSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ChaoticSpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ServantSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ServantSpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ManySpell}", ${Target.ID}]}) {
            /call core_cast2 "${ManySpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ChaoticSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ChaoticSpell}" spell ${Target.ID} FALSE
        }
        
        /if (${validate_cast[FALSE, spell, "${SpearSpell1}", ${Target.ID}]}) {
            /call core_cast2 "${SpearSpell1}" spell ${Target.ID} FALSE
        }

	} else {

        /if (${validate_cast[FALSE, spell, "${ServantSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ServantSpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ManySpell}", ${Target.ID}]}) {
            /call core_cast2 "${ManySpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ChaoticSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ChaoticSpell}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${SpearSpell1}", ${Target.ID}]}) {
            /call core_cast2 "${SpearSpell1}" spell ${Target.ID} FALSE
        }

        /if (${validate_cast[FALSE, spell, "${ChaoticSpell}", ${Target.ID}]}) {
            /call core_cast2 "${ChaoticSpell}" spell ${Target.ID} FALSE
        }

    }
    |***
	/if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) {
		/call core_cast2 "${TwincastSpell}" spell ${Target.ID} FALSE
	}
	
	/if (${validate_cast[FALSE, spell, "${ClawNuke}", ${Target.ID}]}) {
		/call core_cast2 "${ClawNuke}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "${FuseNuke}", ${Target.ID}]}) {
		/call core_cast2 "${FuseNuke}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "${CloudburstNuke}", ${Target.ID}]}) {
		/call core_cast2 "${CloudburstNuke}" spell ${Target.ID} FALSE
	}

	/if (${validate_cast[FALSE, spell, "${FireEtherealNuke}", ${Target.ID}]}) {
		/call core_cast2 "${FireEtherealNuke}" spell ${Target.ID} FALSE
	}
    **|
	
/return


|***
 *	DES: Class self buffs
 *	USE: /call ${validate_cast[[TRUE|FALSE], [spell|alt|disc|item|pulse|FIND], name, targetID, ForceTarget]
 *	NOTE: This is designed tomake sure whatever we are attempting to cast, is castable. be it a disc, item, spell, booger flick.. whatever.. IS IT READY TO BE USED?
 ***|

Sub mag_self_buff_check(bool _debug)
	/declare CastCheck			int local 0
	
	/if (${Me.XTarget}) /return

	/if (${validate_cast[FALSE, FIND, "${SelfHPBuff}", ${Me.ID}]}) {
		/call core_cast2 "${SelfHPBuff}" FIND ${Me.ID} FALSE
		/varset CastCheck 1
	}

    /if (!${Me.Pet.ID}) {
		/if (${validate_cast[FALSE, spell, "${PetSpell}", ${Me.ID}]}) {
			/call core_cast2 "${PetSpell}" spell ${Me.ID} FALSE
			/varset CastCheck 1
		}
	}

	/if (${Me.Pet.ID}) {

		/if (!${Me.Pet.Buff[${PetBuff}]}) {
			/if (${validate_cast[FALSE, spell, "${PetBuff}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetBuff}" spell ${Me.Pet.ID} FALSE
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
|- SUB: BurnRoutine
|---------------------------------------------------------------------------- 
Sub mag_burn_routine

/return
|----------------------------------------------------------------------------
|- SUB: ManageAggro
|---------------------------------------------------------------------------- 
Sub mag_manage_aggro
	
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