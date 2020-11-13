|----------------------------------------------------------------------------
|- SUB: wiz_main
|----------------------------------------------------------------------------
Sub mag_main
	/if (${powerLevel}) {
		/return
	}

	/call mag_self_buff_check FALSE

	/while (${Me.XTarget}) {
		
		/call mag_mana_check
		/call mag_pet_hp_check
		
		/if (${check_for_named[FALSE]} || ${Me.XTarget}>=${BurnMobCount}) /call mag_burn_routine
		/call get_target
		/if (${Int[${Target.Beneficial.ID}]}) {
			/if (${validate_cast[FALSE, alt, "Eradicate Magic", ${Target.ID}]}) /call core_cast2 "Eradicate Magic" alt ${Target.ID} FALSE
		}
		
		/if (!${validate_combat[${Target.ID}]}) /continue
		
		/call pet_attack ${Target.ID}

		/if (${validate_cast[FALSE, FIND, "${Malo}", ${Target.ID}]}) {
			/call core_cast2 "${Malo}" FIND ${Target.ID} FALSE
		}

		/if (${Target.Named} || ${Target.PctHPs} > 80) {
			/if (${useAlliance} && ${allianceTurn}) /call cast_alliance "${AllianceSpell}" ${Target.ID}
		}

		/if (${validate_cast[FALSE, spell, "${TwincastSpell}", ${Me.ID}]}) {
			/call core_cast2 "${TwincastSpell}" spell 0 FALSE
		}
		/if (${Me.Buff[Improved Twincast].ID} && ${Me.Buff[Twincast].ID}) {
			/if (${validate_cast[FALSE, spell, "Companion's Fury", ${Me.Pet.ID}]}) {
				/call core_cast2 "Companion's Fury" spell 0 FALSE
			}
		}

		/if (${Me.Buff[Improved Twincast].ID}) {

			/if (${validate_cast[FALSE, spell, "${ServantSpell}", ${Target.ID}]}) {
				/call core_cast2 "${ServantSpell}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, spell, "${ManySpell}", ${Target.ID}]}) {
				/call core_cast2 "${ManySpell}" spell ${Target.ID} FALSE
			}

			/if (${validate_cast[FALSE, alt, "Forceful Rejuvenation", ${Me.ID}]}) {
				
				/call core_cast2 "Forceful Rejuvenation" alt 0 FALSE

				/if (${validate_cast[FALSE, spell, "${ServantSpell}", ${Target.ID}]}) {
					/call core_cast2 "${ServantSpell}" spell ${Target.ID} FALSE
				}

				/if (${validate_cast[FALSE, spell, "${ManySpell}", ${Target.ID}]}) {
					/call core_cast2 "${ManySpell}" spell ${Target.ID} FALSE
				}
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
		/if (${Target.PctAggro} > 70) {
			/if (${validate_cast[FALSE, alt, "Arcane Whisper", ${Target.ID}]}) {
				/call core_cast2 "Arcane Whisper" alt ${Target.ID} FALSE
			}
		}
	}
	
/return
|----------------------------------------------------------------------------
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub mag_pet_hp_check
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
|- SUB: AANDisc
|---------------------------------------------------------------------------- 
Sub mag_mana_check
	/if (${Me.PctMana} < 25) {
		/if (${validate_cast[FALSE, alt, "Elemental Conversion", ${Me.ID}]}) {
			/call core_cast2 "Elemental Conversion" alt 0 FALSE
		}
	}

	| Do (self) modrod here

	|**
	/if (${Me.PctMana} < 90) {
		/if (${validate_cast[FALSE, alt, "Azure Mind Crystal", ${Me.ID}]}) {
			/call core_cast2 "Azure Mind Crystal" alt 0 FALSE

			/if (${Me.FreeInventory} >= 1) /autoinventory

			/if (${validate_cast[FALSE, item, "Azure Mind Crystal ${AzureMindCrystalRank}", ${Me.ID}]}) {
				/call core_cast2 "Azure Mind Crystal ${AzureMindCrystalRank}" item 0 FALSE
			}
		}
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

	/if (${validate_cast[FALSE, alt, "Thaumaturge's Unity", ${Me.ID}]}) {
		/call core_cast2 "Thaumaturge's Unity" alt 0 FALSE
	}

	|/if (!${Me.Buff[${Me.AltAbility[Elemental Form].Rank}].ID}) {
		/if (${validate_cast[FALSE, alt, "Elemental Form", ${Me.ID}]}) {
			/call core_cast2 "Elemental Form" alt 0 FALSE
		}
	|}

	|/if (!${Me.Buff[${SelfHPBuff}].ID}) {
	/if (${validate_cast[FALSE, FIND, "${SelfHPBuff}", ${Me.ID}]}) {
		/call core_cast2 "${SelfHPBuff}" FIND 0 FALSE
		/varset CastCheck 1
	}
	|}

	|/if (!${Me.Buff[${Me.AltAbility[${ChaoticHeal}].Rank}]}) {
	/if (${validate_cast[FALSE, spell, "${BodyguardSpell}", ${Me.ID}]}) {
		/call core_cast2 "${BodyguardSpell}" spell 0 FALSE
		/varset CastCheck 1
	}
	|}

	|/if (!${Me.Buff[${ShieldSpell}].ID}) {
	/if (${validate_cast[FALSE, spell, "${ShieldSpell}", ${Me.ID}]}) {
		/call core_cast2 "${ShieldSpell}" spell 0 FALSE
		/varset CastCheck 1
	}
	|}

	|/if (!${Me.Buff[${ChaoticHeal}].ID}) {
	/if (${validate_cast[FALSE, spell, "${ChaoticHeal}", ${Me.ID}]}) {
		/call core_cast2 "${ChaoticHeal}" spell ${Me.ID} FALSE
		/varset CastCheck 1
	}
	|}

    /if (!${Me.Pet.ID}) {
		/if (${validate_cast[FALSE, spell, "${PetSpell}", ${Me.ID}]}) {
			/call core_cast2 "${PetSpell}" spell 0 FALSE
			/varset CastCheck 1
		}
	}

	/if (${Me.Pet.ID}) {
		
		|/call cast_summon_weapons

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

		/if (!${Me.Pet.Buff[${Iceflame}]}) {
			/if (${validate_cast[FALSE, spell, "${Iceflame}", ${Me.Pet.ID}]}) {
				/call core_cast2 "${Iceflame}" spell ${Me.Pet.ID} FALSE
				/varset CastCheck 1
			}
		}

		/if (!${Me.Pet.Buff[${Me.AltAbility[Velocity].Rank}]}) {
			/if (${validate_cast[FALSE, alt, "Velocity", ${Me.Pet.ID}]}) {
				/call core_cast2 "Velocity" alt 0 FALSE
			}
		}

		/if (!${Me.Pet.Buff[${Me.AltAbility[Host in the Shell].Rank}]}) {
			/if (${validate_cast[FALSE, alt, "Host in the Shell", ${Me.Pet.ID}]}) {
				/call core_cast2 "Host in the Shell" alt 0 FALSE
			}
		}

		/if (!${Me.Pet.Buff[${Me.AltAbility[Companion's Aegis].Rank}]}) {
			/if (${validate_cast[FALSE, alt, "Companion's Aegis", ${Me.Pet.ID}]}) {
				/call core_cast2 "Companion's Aegis" alt 0 FALSE
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

	/if (${validate_cast[FALSE, alt, "Silent Casting", ${Me.ID}]}) {
		/call core_cast2 "Silent Casting" alt 0 FALSE
	}

	/if (${validate_cast[FALSE, alt, "Dimensional Shield", ${Me.ID}]}) {
		/call core_cast2 "Dimensional Shield" alt 0 FALSE
	}

	/if (${validate_cast[FALSE, alt, "Heart of Skyfire", ${Me.ID}]}) {
		/call core_cast2 "Heart of Skyfire" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Heart of Froststone", ${Me.ID}]}) {
		/call core_cast2 "Heart of Froststone" alt 0 FALSE
	}

	/if (${validate_cast[FALSE, alt, "Spire of Elements", ${Me.ID}]}) {
		/call core_cast2 "Spire of Elements" alt 0 FALSE
	}
	/if (${validate_cast[FALSE, alt, "Shield of the Elements", ${Me.ID}]}) {
		/call core_cast2 "Shield of the Elements" alt 0 FALSE
	}

	/if (${validate_cast[FALSE, alt, "Focus of Arcanum", ${Me.ID}]}) {
		/call core_cast2 "Focus of Arcanum" alt 0 FALSE
	}

	/if (${validate_cast[FALSE, alt, "Thaumaturge's Focus", ${Me.ID}]}) {
		/call core_cast2 "Thaumaturge's Focus" alt 0 FALSE
	}

	/if (!${Me.Buff[Twincast].ID} && ${validate_cast[FALSE, alt, "Improved Twincast", ${Me.ID}]}) {
		/call core_cast2 "Improved Twincast" alt 0 FALSE
	}
	

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