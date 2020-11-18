|-----------------------------------------------------------------------------
|- Sub: Bind_IHCSettings - Bind that handles settings changes across the
|- Macro suite
|-----------------------------------------------------------------------------
#bind   Settings   /addict
Sub Bind_Settings(string _setMode, int _pullRadiusXY, int _pullRadiusZ, int _npcRadiusCheck)

    /if (${_setMode.Equal[travel]}) /varset Mode 0
	/if (${_setMode.Equal[afkfight]}) {
		/varset Mode 3
		/varset pullRadiusXY ${_pullRadiusXY} 
		/varset pullRadiusZ ${_pullRadiusZ}
		/varset npcRadiusCheck ${_npcRadiusCheck}
		/mapfilter CastRadius ${_pullRadiusXY}
	}
	/if (${_setMode.Equal[event]}) /varset Mode 5
	/if (${_setMode.Equal[raid]}) /varset Mode 6
    /if (${_setMode.Equal[scribe]}) /varset Mode 9
/return

#bind   Powerlevel   /powerlevel
Sub Bind_Powerlevel(string _powerLevel)
	
	/if (${powerLevel}) {
		/if (${_powerLevel.Equal[off]}) /varset powerLevel TRUE
	} else {
		/if (${_powerLevel.Equal[on]}) /varset powerLevel FALSE
	}
	/echo ${Me.Name} has PowerLevel set to ${powerLevel}

/return

#bind   Scribezone   /scribezone
Sub Bind_Scribezone(string _zoneName)
	/varset getSpellsFromZone ${_zoneName}
	/echo ${Me.Name} set scribe zone to ${_zoneName}
	/if (${Navigation.Active}) /nav stop
/return

#bind   Scribelevels   /scribelevels
Sub Bind_Scribelevels(int _minLevel, int _maxLevel)
	/varset minScribeLevel ${_minLevel}
	/varset maxScribeLevel ${_maxLevel}
	/echo ${Me.Name} set scribe levels to ${_minLevel} - ${_maxLevel}
/return

#bind   Campfire   /campfire
sub Bind_Campfire(string _forceCreate)
	

    /declare _fellowCount int local 0
	/declare _count int local 0
    /declare i int local
    /declare j int local

	/if (${Me.Fellowship.Members} == 0) {
        /echo \arFellowship members is 0
        /return
    }

	/for _count 1 to ${SpawnCount[pc radius 50]}

		/for i 1 to ${SpawnCount[pc radius 50]}
			/for j 1 to ${Me.Fellowship.Members}
				/if (${NearestSpawn[${i},PC radius 50].CleanName.Equal[${Me.Fellowship.Member[${j}]}]}) {
					/varcalc _fellowCount ${_fellowCount}+1
					/if (${_fellowCount} >= 3) /break
				}
			/next j
            /if (${_fellowCount} >= 3) /break
		/next i
        /if (${_fellowCount} >= 3) /break
	/next _count

    /if (${_fellowCount} < 3) {
        /echo \arFellowship members less than 3 in radius 50
        /return
    }

	/if (!${_forceCreate}) {
		/if (${Zone.Name.Equal[${Me.Fellowship.CampfireZone}]}) {
			/if (${Math.Distance[${pullAutoCampY}, ${pullAutoCampX}, ${pullAutoCampZ}:${Me.Fellowship.CampfireY}, ${Me.Fellowship.CampfireX}, ${Me.Fellowship.CampfireZ}]} < 200) {
				/if (${Me.Fellowship.CampfireDuration} > 600) {
					/return
				}
			}
		}
	}

	| Destroy old campfire
	/while (${Me.Fellowship.Campfire}) {
		/if (!${Window[FellowshipWnd].Open}) /windowstate FellowshipWnd open
		/delay 3s ${Window[FellowshipWnd].Open}
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_Subwindows tabselect 2
		/delay 5
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_RefreshList leftmouseup
		/delay 5
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_CampsiteKitList listselect 1
		/delay 5
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_DestroyCampsite leftmouseup
		/delay 3s ${Window[ConfirmationDialogBox].Open}
		/if (${Window[ConfirmationDialogBox].Open}) /nomodkey /notify ConfirmationDialogBox CD_Yes_Button leftmouseup
		/delay 5
		/if (${Window[ConfirmationDialogBox].Open}) /notify ConfirmationDialogBox Yes_Button leftmouseup
		/delay 5
		/if (${Window[ConfirmationDialogBox].Open}) /notify ConfirmationDialogBox Confirm_Button leftmouseup
		/delay 5
	}
	
	/delay 1s

	| Create new campfire
	/while (!${Me.Fellowship.Campfire}) {
		/if (!${Window[FellowshipWnd].Open}) /windowstate FellowshipWnd open
		/delay 3s ${Window[FellowshipWnd].Open}
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_Subwindows tabselect 2
		/delay 5
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_RefreshList leftmouseup
		/delay 5
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_CampsiteKitList listselect 1
		/delay 5
		/if (${Window[FellowshipWnd].Open}) /nomodkey /notify FellowshipWnd FP_CreateCampsite leftmouseup
		/delay 3s ${Me.Fellowship.Campfire}
		/if (${Window[FellowshipWnd].Open} && !${Me.Fellowship.Campfire}) /nomodkey /notify FellowshipWnd FP_CreateCampsite leftmouseup
		/delay 3s ${Me.Fellowship.Campfire}
		/if (${Window[FellowshipWnd].Open}) /windowstate FellowshipWnd close
	}

/return

#bind   ForceScribe   /forcescribe
Sub Bind_ForceScribe
	/if (!${Select[${Me.Class.ShortName},CLR,DRU,SHM,ENC,WIZ,MAG,NEC]}) /call ScribeTomes
	/if (!${Select[${Me.Class.ShortName},WAR,BER,MNK,ROG]}) /call ScribeSpells
	/call ${Me.Class.ShortName.Lower}_abilities
/return

#bind   TravelToZone   /traveltozone
Sub Bind_TravelToZone(string _zoneName)
	/if (!${_zoneName.Length}) {
		DEBUG You've failed to provide a destination. Please type /traveltozone desination, IE: /traveltozone "plane of knowledge"
	} else {
		/if (${_zoneName.Equal["guild hall"]}) {
			/if (${Navigation.Active}) /nav stop
			/call go_to_guildhall
			/return
		} else {
			/declare Destination string local "${_zoneName}"
		}
	}
	/if (${Navigation.Active}) /nav stop

	/call OpenWnd ZoneGuideWnd
	DEBUG Destination is ${Destination}
	DEBUG Clicking Text box to search for destination.
	/if (${Window[ZoneGuideWnd].Open}) /notify ZoneGuideWnd ZGW_ZoneSelect_EditBox leftmouseup
	/if (${Window[ZoneGuideWnd].Child[ZGW_ClearZonesSearch_Btn].Enabled}) {
		DEBUG Clicking Clear button
		/if (${Window[ZoneGuideWnd].Open}) /notify ZoneGuideWnd ZGW_ClearZonesSearch_Btn leftmouseup
	}
	/call TypeIn "${Destination}"
	/delay 1s ${Window[ZoneGuideWnd].Child[ZGW_SearchZones_Btn].Enabled}
	DEBUG Clicking search button
	/if (${Window[ZoneGuideWnd].Open}) /notify ZoneGuideWnd ZGW_SearchZones_Btn leftmouseup
	/delay 1s ${Window[ZoneGuideWnd].Child[ZGW_Zones_ListBox].List[1,1].Length}
	/declare i int local 0
	/for i 1 to 10
		/if (${Window[ZoneGuideWnd].Child[ZGW_Zones_ListBox].List[${i},1].Equal[${Destination}]}) {
			/varset i ${i}
			/break
		}
	/next i
	DEBUG selecting zone from the list. 
	/if (${Window[ZoneGuideWnd].Open}) /notify ZoneGuideWnd ZGW_Zones_ListBox listselect ${i}
	/delay 5
	DEBUG setting end location. 
	/if (${Window[ZoneGuideWnd].Open}) /notify ZoneGuideWnd ZGW_SetEnd_Btn leftmouseup
	/delay 1s ${Window[ZoneGuideWnd].Child[ZGW_PathEndZone_EditBox].Text.Equal[${Window[ZoneGuideWnd].Child[ZGW_Zones_ListBox].List[${i},1]}]}
	/delay 5
	/if (${Window[ZoneGuideWnd].Child[ZGW_PathEndZone_EditBox].Text.Equal[${Window[ZoneGuideWnd].Child[ZGW_Zones_ListBox].List[${i},1]}]}) {
		DEBUG Clicking Activate Path. 
		/if (${Window[ZoneGuideWnd].Open}) /notify ZoneGuideWnd ZGW_ActivatePath_Btn leftmouseup
	} else {
		DEBUG Something went wrong getting the destination setup, please try again!
	}
	/call CloseWnd ZoneGuideWnd
	/while (${Navigation.Active}) {
        /delay 1s
    }

/return 

Sub OpenWnd(string what)
	/windowstate ${what} open
	/delay 1s ${Window[${what}].Open}
/return

Sub CloseWnd(string what)
	/windowstate ${what} close
	/delay 5
/return

Sub TypeIn(string InStr)
	DEBUG Typing ${InStr}
	/declare char string local
	/declare i int local
	/for i 1 to ${InStr.Length}
		/varset char ${InStr.Mid[${i},1]}
		/if (!${char.Length}) {
			/nomodkey /keypress Space chat
		} else {
			/if (${char.Left[1].Equal[(]}) /return
			/if (${char.Left[1].Equal[)]}) /return
			/nomodkey /keypress ${char} chat
		}
	/next i
/return

Sub ClearChat(parent,child)
	/while (${Window[${parent}].Child[${child}].Text.Length}>0) {
		/ctrlkey /shiftkey /keypress home chat
		/delay 5
		/ctrlkey /shiftkey /keypress delete chat
		/delay 5
	}
/return


|-------------------------------------------------------------------------------------
|- SUB: BIND Bind_lazylobbyrez
|- credit: TreeHuginDruid RIP
|-------------------------------------------------------------------------------------
#bind LazyLobbyRez /lazylobbyrez
Sub Bind_LazyLobbyRez
    /declare SoulStoneMerchant     	string local   "A Disciple of Luclin"
	/declare CorpseSummoner 	    string local   "A Priestess of Luclin"
	/declare RangeDist              int    local   8
	/declare SoulStoneName		    string local
	/declare bag               	    string local
	/declare slot              	    string local
	/declare ItemToGet              string local
	/declare MercClass              string local
	/declare i			            int    local

	/squelch /target clear
	/delay 10

    /if (!${Plugin[MQ2Nav].Name.Equal[MQ2Nav]}) {
		/echo Loading MQ2Nav
		/squelch /plugin MQ2Nav load
		/delay 1s
		/if (!${Plugin[MQ2Nav].Name.Equal[MQ2Nav]}) {
			/beep
			/echo Unable to load MQ2MoveUtils plugin, stopping.
			/return
		}
	} else {
		/echo MQ2Nav plugin is loaded.
	}
	/if (${Navigation.Active}) /nav stop
	/if (!${Select[${Zone.ShortName},GuildLobby]}) /call go_to_guildlobby

    /if (!${Zone.Name.Equal[Guild Lobby]}) {
        /echo Get your lazy self to the Guild Lobby!
        /return
    }

    /if (${Me.Level}<=115) /varset SoulStoneName Velium Soulstone
	/if (${Me.Level}<=110) /varset SoulStoneName Draconic Soulstone
	/if (${Me.Level}<=105) /varset SoulStoneName Torrential Soulstone
	/if (${Me.Level}<=100) /varset SoulStoneName Coalescent Soulstone
	/if (${Me.Level}<=95) /varset SoulStoneName Luminous Soulstone
	/if (${Me.Level}<=90) /varset SoulStoneName Phantasmal Soulstone
	/if (${Me.Level}<=85) /varset SoulStoneName Iridescent Soulstone
	/if (${Me.Level}<=80) /varset SoulStoneName Prismatic Soulstone
	/if (${Me.Level}<=75) /varset SoulStoneName Glowing Soulstone
	/if (${Me.Level}<=70) /varset SoulStoneName Pristine Soulstone
	/if (${Me.Level}<=55) /varset SoulStoneName Faceted Soulstone
	/if (${Me.Level}<=50) /varset SoulStoneName Greater Soulstone
	/if (${Me.Level}<=40) /varset SoulStoneName Soulstone
	/if (${Me.Level}<=30) /varset SoulStoneName Lesser Soulstone
	/if (${Me.Level}<=20) /varset SoulStoneName Minor Soulstone
	/delay 10
	/echo Soulstone for my level (${Me.Level}) is (${SoulStoneName}).

    /if (${FindItem[${SoulStoneName}].ID}) {
		/echo I already have a (${SoulStoneName}).
	} 
    /if (!${FindItem[${SoulStoneName}].ID}) {
		/echo I do not have a (${SoulStoneName}).

        /nav spawn npc ${SoulStoneMerchant}
        /while (${Navigation.Active}) {
        /if (${Spawn[npc ${SoulStoneMerchant}].Distance3D} < 20) /break
        /delay 5
        }
        /squelch /target npc ${SoulStoneMerchant}
        /delay 2s ${Target.ID}==${Spawn[npc ${SoulStoneMerchant}].ID}
        /face
    } 

    /echo We have arrived at ${SoulStoneMerchant}
	/nomodkey /click right target
	/delay 10s ${Merchant.ItemsReceived}

	/if (${Merchant.ItemsReceived}) {
		/delay 3s
		/varset ItemToGet ${Window[MerchantWnd].Child[ItemList].List[=${SoulStoneName},2]}
	}

	/if (!${ItemToGet}) {
		/echo I couldn't find (${SoulStoneName})  to purchase!
		/return
	} else {
		/echo Found (${SoulStoneName}) to purchase!
		/notify MerchantWnd ItemList listselect ${ItemToGet}
		/delay 10
		/notify MerchantWnd ItemList LeftMouseUp ${ItemToGet}
		/delay 10
		/nomodkey /notify MerchantWnd MW_Buy_Button LeftMouseUp
		/delay 10
	}
    :CloseMerchantWnd1
	/if (${Window[MerchantWnd].Open}) {
		/nomodkey /notify MerchantWnd MW_Done_Button LeftMouseUp
		/delay 10
		/if (${Window[MerchantWnd].Open}) /goto :CloseMerchantWnd1
	}

    /nav spawn npc ${CorpseSummoner}
    /while (${Navigation.Active}) {
        /if (${Spawn[npc ${CorpseSummoner}].Distance3D} < 20) /break
        /delay 5
    }
    /squelch /target npc ${CorpseSummoner}
    /delay 2s ${Target.ID}==${Spawn[npc ${CorpseSummoner}].ID}
    /face

	/echo Attempting to grab (${SoulStoneName}).
	/if (!${Window[InventoryWindow].Open}) /keypress Inventory
	/delay 5
	/itemnotify "${SoulStoneName}" leftmouseup
	/delay 5

	/if (${Cursor.ID} && ${Cursor.Name.Equal[${SoulStoneName}]}) {
		/echo I have (${SoulStoneName}) on my cursor.
		/echo Giving (${Cursor.Name}) to (${Target.CleanName}).
    }
	:OpenGiveWindowB
		/nomodkey /click left target
		/delay 5s ${Window[GiveWnd].Open}
		/if (!${Window[GiveWnd].Open}) /goto :OpenGiveWindowB
	:GiveSoulStone
		/if (${Window[GiveWnd].Open}) {
			/notify GiveWnd GVW_Give_Button leftmouseup
			/delay 3s
			/if (${Window[GiveWnd].Open}) /goto :GiveSoulStone
		}
	:CloseInvWnd
    	/if (${Window[InventoryWindow].Open}) {
			/nomodkey /notify InventoryWindow IW_DoneButton LeftMouseUp
			/delay 5
			/if (${Window[InventoryWindow].Open}) /goto :CloseInvWnd
		} else {
		/echo I couldn't find (${SoulStoneName}) on my cursor!
		/return
	}
	/if (${Window[InventoryWindow].Open}) /nomodkey /notify InventoryWindow IW_DoneButton LeftMouseUp
	/delay 5
	/squelch /target clear
	/delay 10

/return



#bind AutoSell /selltomerchant
Sub Bind_AutoSell
    |- /if (!${Select[${Zone.ShortName},GuildLobby,GuildHall,PoKnowledge,moors,crescent]})
	
	/if (${Select[${Zone.ShortName},GuildLobby]}) {
		/declare MerchantA	     	string local   "A Disciple of Luclin"
	} else /if (${Select[${Zone.ShortName},PoKnowledge]}) {
		/declare _randNum int local ${Math.Rand[50]}
		/if (${_randNum} >= 0 && ${_randNum} <= 10) /declare MerchantA 		    string local   "Savet Ironstove"
		/if (${_randNum} > 10 && ${_randNum} <= 20) /declare MerchantA 		    string local   "Mercia"
		/if (${_randNum} > 20 && ${_randNum} <= 30) /declare MerchantA 		    string local   "Boiron Ston"
		/if (${_randNum} > 30 && ${_randNum} <= 40) /declare MerchantA 		    string local   "Glena Quok"
		/if (${_randNum} > 40 && ${_randNum} <= 50) /declare MerchantA 		    string local   "Sirekoth Eshe"
	} else {
		/echo ${Zone.ShortName} is not a supported zone for selling
		/return
	}
	/if (${Navigation.Active}) /nav stop
	/squelch /target clear
	/delay 10

    /if (!${Plugin[MQ2Nav].Name.Equal[MQ2Nav]}) {
		/echo Loading MQ2Nav
		/squelch /plugin MQ2Nav load
		/delay 1s
		/if (!${Plugin[MQ2Nav].Name.Equal[MQ2Nav]}) {
			/beep
			/echo Unable to load MQ2MoveUtils plugin, stopping.
			/return
		}
	}

    /if (${Spawn[npc ${MerchantA}].Distance3D} > 20) {

        /nav spawn npc ${MerchantA}
        /while (${Navigation.Active}) {
			/if (${Spawn[npc ${MerchantA}].Distance3D} < 20) /break
			/delay 5
        }
	}

	/squelch /target npc ${MerchantA}
	/delay 2s ${Target.ID}==${Spawn[npc ${MerchantA}].ID}
	/face
	/delay 2s
	/autoloot sell
	/delay 2s
	/while (${Window[MerchantWnd].Open} || ${Window[InventoryWindow].Open}) {
		/delay 1s
	}

	:CloseMerchantWnd1
	/if (${Window[MerchantWnd].Open}) {
		/nomodkey /notify MerchantWnd MW_Done_Button LeftMouseUp
		/delay 10
		/if (${Window[MerchantWnd].Open}) /goto :CloseMerchantWnd1
	}

	:CloseInvWnd
	/if (${Window[InventoryWindow].Open}) {
		/nomodkey /notify InventoryWindow IW_DoneButton LeftMouseUp
		/delay 5
		/if (${Window[InventoryWindow].Open}) /goto :CloseInvWnd
	}
	
	/delay 5
	/squelch /target clear
	/delay 10

/return
|----------------------------------------------------------------------------
|- BIND: navtome
|----------------------------------------------------------------------------
#bind NavTo /navto
Sub Bind_NavTo(string _to)

	/if (${Navigation.Active}) /nav stop
	/if (${Stick.Status.Equal[ON]}) /stick off

    /if (${_to.Equal[me]}) {
        /dga /nav id ${Me.ID}
    } else /if (${_to.Equal[target]}) {
		/dgga /assist ${Me.ID}
		/dgga /attack off
        /dgga /nav id ${Target.ID}
    }
	/while (${Navigation.Active}) {
		/delay 1s
	}

/return

|----------------------------------------------------------------------------
|- BIND: DragAll
|----------------------------------------------------------------------------
#bind DragAll /dragall
Sub Bind_DragAll
	/declare _count int local 0
	/declare _corpseTarget int local 0
	/declare _numCorpses int local ${SpawnCount[pccorpse radius 100]}

	/while (${DragAllVar}) {
		/if (${_numCorpses}) {
			/varset _numCorpses ${SpawnCount[pccorpse radius 100]}
			/for _count 1 to ${_numCorpses}
				/varset _corpseTarget ${NearestSpawn[${_count}, pccorpse radius 100].ID}
				/tar id ${_corpseTarget}
				/delay 5 ${Target.ID}==${_corpseTarget}
				/cor
			/next _count
		} else {
			/echo No corpses found
			/delay 1s
		}
	}

/return