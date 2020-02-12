|----------------------------------------------------------------------------
|- SUB: wiz_main
|----------------------------------------------------------------------------
Sub mag_main
	/if (${powerLevel}) {
		/return
	} 
	
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
		
		/call cast_summon_weapons

		/if (!${Me.Pet.Buff[${BurnoutSpell}]}) {
			/if (${validate_cast[FALSE, spell, "${BurnoutSpell}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${BurnoutSpell}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}

		/if (!${Me.Pet.Buff[${PetProc}]}) {
			/if (${validate_cast[FALSE, spell, "${PetProc}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetProc}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}

		/if (!${Me.Pet.Buff[${PetMalo}]}) {
			/if (${validate_cast[FALSE, spell, "${PetMalo}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${PetMalo}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}

		/if (${validate_cast[FALSE, spell, "${ChaoticHeal}", ${Me.ID}]}) {
			/call core_cast2 "${ChaoticHeal}" spell ${Me.ID} FALSE
			/varset CastCheck 1
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



|***
 *	DES: returns a non container inventory slot ##
 *	USE: ${get_openPackSlot[]}
 *	NOTE: 0 on full bag inventory, you can pass an optional name to find an item in a top slot
 ***|
sub get_open_pack_slot(string _orFind, bool _debug)
	DEBUG get_open_pack_slot()

	/declare _count int local 0

	/for _count 23 to 32
		/if (${InvSlot[${_count}].Item.Container} == 0 || ${InvSlot[${_count}].Item.Name.Equal[${_orFind}]}) {
			/return ${_count}
		}
	/next _count

/return 0



|***
 *	DES: give weapons to pet
 *	USE: /call give_to_pet "ITEMNAME"
 *	NOTE: 1 item at a fucking time.. seriously people...
 ***|
sub give_to_pet(string _item)
	DEBUG give_to_pet(${_item})
	
	| get pet as target
	/if (${Target.ID} != ${Me.Pet.ID}) {
		/squelch /target ID ${Me.Pet.ID}
		/delay 1s ${Target.ID} == ${Me.Pet.ID}
	}
	
	|AMIDEAD
	|CHECKINPUTS
	/if (${Cursor.ID} && ${Me.Pet.ID}) {
		/if (${Cursor.Name.Equal[${_item}]}) {
			/click left target
			/delay 5s !${Bool[${Cursor.ID}]}
		} else {
			|CLEARCURSOR TRUE
		}
	}
	
/return



|***
 *	DES: Summon and equip pet weapons
 *	USE: /call cast_summon_weapons [DEBUG T/F]
 *	NOTE: 
 ***|
sub cast_summon_weapons
	DEBUG cast_summon_weapons

	| Check if spell level less than 76 because mage pets auto equipped after that.

	/if (!${Me.Pet.ID}) /return

	|CHECKTIE
	|AMIDEAD
	|CHECKINPUTS

	/declare _count int local 0
	/declare _openPackSlot int local 0
	
	| get everything out of your hands
	/if (${Cursor.ID}) /autoinventory

	| need a non bag inventory slot or ur fuckled!
	/varset _openPackSlot ${get_open_pack_slot[None]}
	DEBUG _openPackSlot ${_openPackSlot}
	/if (!${_openPackSlot} && !${FindItemCount[=${setMAGPetWepName}]}) {
		| OUT ${onotice} ${sep} You have no TOP inventory slots that are not bags.
		| OUT Clean up your damn inventory then you can give your pet some weapons.
		/return FALSE
	} else /if (!${Me.FreeInventory}) {
		| OUT ${onotice} ${sep} You have free inventory. Damn hoarders....
		/return FALSE
	}
	
	| we have the weapons we can rebuild her better then before
	/if (${FindItemCount[=${setMAGPetWepName}]} > 1) /goto :havepetweapons
	:havepouchandnoweapons
	| still have an old bag. it needs to be gone
	| /if (${FindItemCount[=Pouch of Quellious]} && ${FindItemCount[=${setMAGPetWepName}]} < 2) {
	| 	/call item_delete FALSE "Pouch of Quellious"
	| }
	
	| how much for a dime?
	/if (${FindItemCount[=${setMAGClosedBag}]}) {
		/goto :havemageclosedbag
	} else /if (!${FindItemCount[=${setMAGClosedBag}]} && !${FindItemCount[=${setMAGPetWepName}]}) {
		/if (${Select[${Me.Class.ShortName},MAG]}) {
			/if (${validate_cast[FALSE, spell, "${setMAGWepSpell}", ${Me.ID}]}) {
				/call core_cast2 "${setMAGWepSpell}" ${buffGem} ${Me.ID} FALSE
			}
		} else {
			/return FALSE
		}
	}
		
	| have bag/not opened
	:havemageclosedbag
	DEBUG :havemageclosedbag
	/if (${Cursor.ID}) /autoinventory
		
	/if (${Select[${FindItem[=${setMAGClosedBag}].InvSlot},23,24,25,26,27,28,29,30,31,32]} != 0) {
		| DEBUG \agSWAP\ax ${setMAGClosedBag} to slot \aw${_openPackSlot}\ax
		/call Bind_swap "${setMAGClosedBag}" ${_openPackSlot} TRUE
	}

	/if (${Cursor.ID}) /autoinventory

	/if (${validate_cast[FALSE, item, "${setMAGClosedBag}", ${Me.ID}]}) {
		/call core_cast2 "${setMAGClosedBag}" item 0 FALSE
	}
	
	/if (${Cursor.ID}) /autoinventory
	
	| have 2 blades
	:havepetweapons
	DEBUG :havepetweapons
	/for _count 1 to 2
		/if (${Cursor.ID}) /autoinventory
		/delay 2
		DEBUG WEAPON ${_count} Pack${Int[${Math.Calc[${FindItem[Pouch of Quellious].ItemSlot}-22]}]} ${Int[${Math.Calc[${FindItem[=${setMAGPetWepName}].ItemSlot2}+1]}]}
		/nomodkey /itemnotify in Pack${Int[${Math.Calc[${FindItem[Pouch of Quellious].ItemSlot}-22]}]} ${Int[${Math.Calc[${FindItem[=${setMAGPetWepName}].ItemSlot2}+1]}]} leftmouseup

		/delay 3s ${Cursor.ID}
		/delay 5
		/call give_to_pet "${Cursor.Name}"
		/delay 3s !${Cursor.ID}
	/next _count

	| close the give to window
	/if (${Window[GiveWnd].Open}) {
		DEBUG close GiveWnd window
		/nomodkey /notify GiveWnd GVW_Give_Button leftmouseup
		/delay 5
		/invoke ${Window[GiveWnd].DoClose}
	}

	/if (${Cursor.ID}) /autoinventory

	:havepouchandnoweapons
	DEBUG :havepouchandnoweapons
	/if (${FindItemCount[=Pouch of Quellious]} && ${FindItemCount[=${setMAGPetWepName}]} < 2) {
		/nomodkey /itemnotify ${FindItem[Pouch of Quellious].InvSlot} leftmouseup
		/delay 1
		/call item_delete FALSE "Pouch of Quellious"

	}

	/if (${Cursor.ID}) /autoinventory

	/if (${Window[InventoryWindow].Open}) /invoke ${Window[InventoryWindow].DoClose}
	
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