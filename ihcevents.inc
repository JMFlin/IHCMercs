|- ihcevents.inc
|- Version 2.0
|- Updated: 4/25/2019
|-#Event	EventName	"Event Text"
|-Sub Event_EventName	
|- /popcustom 
|- /doevents flush EventName
|-/return 
|-------------------------------------------------------------------------------------
|- SUB: ZoneEventChk
|-------------------------------------------------------------------------------------
Sub ZoneEventChk
 |- Expansion: The Broken Mirror
	|-Damsel of Decay
	/if (${Zone.ID}==797 && ${Spawn[Anashti Sul, Damsel of Decay].ID}) {
		/echo \ar***Damsel of Decay Event Detected***
		/echo \awPlease Have Distillate of Immunization XVII & Distillate of Immunization XII
		/echo \awTo Preform Auto Curing of the Cyclic DoT
		/if (${Select[${Me.Class.ShortName},CLR,DRU]}) /docommand /nocures
		/call CheckPlugin MQ2Nav
		/varset NoDisease 1
		/varset NoCorruption 1
		/varset EventSetupFlag 797
	}
	|-Lady of Life
	|-Enslaver of Souls
	/if (${Zone.ID}==795 && ${Spawn[Anashti Sul, Lady of Life].ID}) {
		/echo \ar***Enslaver of Souls Event Detected***
		/varset NoDisease 1
		/varset NoCorruption 1
		/varset EventSetupFlag 795
	|-	/varset DoAutoEngage 0
	}
 |- Expansion: Ring of Scale
	|-Zone: Gorowyn - RoS
	|- /if (${Zone.ID}==792) {
	|-	/varset EventSetupFlag 792
	|- }
	|-Zone: Charasis - RoS
	|- /if (${Zone.ID}==813) {
	|-	/varset EventSetupFlag 813
	|- }
	|-Zone: Skyfire - RoS
	|- /if (${Zone.ID}==814) {
	|-	/varset EventSetupFlag 814
	|- }
	|-Zone: The Overthere - RoS
	/if (${Zone.ID}==815) {
		/varset EventSetupFlag 815
	}
	|-Zone: Veeshans Peak - RoS
	|- /if (${Zone.ID}==816) {
	|-	/varset EventSetupFlag 816
	|- }
 |- Expansion: The Burning Lands
	|-Zone: Plane of Smoke
	|- /if (${Zone.ID}==817) {
	|-	/varset EventSetupFlag 817
	|- }
	|-Zone: Stratos: Zephyr's Flight
	|- /if (${Zone.ID}==818) {
	|-	/varset EventSetupFlag 818
	|- }
	|-AAlishai: Palace of Embers
	/if (${Zone.ID}==819) {
		/varset EventSetupFlag 819
	}
	|-Zone: Empyr: Realms of Ash - Handles some of the named mob mechanics
	|-/if (${Zone.ID}==820) {
	|-	/varset EventSetupFlag 820
	|-}
	|-Zone: Esianti: Palace of the Winds
	|- /if (${Zone.ID}==821) {
	|-	/varset EventSetupFlag 821
	|- }
	|-Zone: Mearatas: The Stone Demesne
	|- /if (${Zone.ID}==822) {
	|-	/varset EventSetupFlag 822
	|- }
	|-Zone: The Chamber of Tears
	|- /if (${Zone.ID}==823) {
	|-	/varset EventSetupFlag 823
	|- }
/return
|-------------------------------------------------------------------------------------
|- SUB: EventLogic819 -Brass Palace Mission
|-------------------------------------------------------------------------------------
Sub EventLogic819
	/if (${Spawn[Silent Sun].ID}==${Target.ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER,WAR]} && ${Target.Buff[Cape of Lava].ID} && !${BackOffFlag}) {
		/call DoBackOff
	} else /if (${Spawn[Silent Sun].ID}==${Target.ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER,WAR]} && ${BackOffFlag}) {
		/varset BackOffFlag 0
	}
/return
|-------------------------------------------------------------------------------------
|- SUB: EventLogic820 -Empyr: Realm of Ash - Handles some of the named mob mechanics
|-------------------------------------------------------------------------------------
Sub EventLogic820
	/if (${Spawn[Stalwart Flicker].ID}==${Target.ID}) {
		/call FireTrapDebuff
	}
/return
|-------------------------------------------------------------------------------------
|- TBL Debuff Handling Subs
|-------------------------------------------------------------------------------------
Sub FireTrapDebuff
	/if (${Me.Buff[Fire Trap].ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,BRD,BER,WAR,PAL,SHD]} && !${BackOffFlag}) {
		/call DoBackOff
	} else /if (${assistid}!=${Me.ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,BRD,BER]} && ${Me.PctHPs}<=50 && !${BackOffFlag}) {
		/call DoBackOff
	} else /if (${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,BRD,BER,WAR,PAL,SHD]} && ${BackOffFlag}) {
		/varset BackOffFlag 0
	}
/return
|--------------------------------------------------------------------------------------
|-Event: DebuffFireTrap
|--------------------------------------------------------------------------------------
#Event DebuffFireTrap "#*#threatening to burn you if you attack#*#"
Sub Event_DebuffFireTrap
|	/if (${Group}) /gsay !!!FIRE TRAP!!!Backing Off!!!
	/delay 5
|	/if (${Group} && ${DoGroupBeg}) /gsay RC
	:firetraploop
		/if ((${Me.Buff[Fire Trap].ID} || ${Me.Song[Fire Trap].ID}) && !${BackOffFlag}) /call DoBackOff
		/delay 1s
		/if (${Me.Buff[Fire Trap].ID} || ${Me.Song[Fire Trap].ID}) /goto :firetraploop
	/if (${BackOffFlag}) /varset BackOffFlag 0
	/doevents flush DebuffFireTrap
/return
|--------------------------------------------------------------------------------------
|-Event: RainbowMez
|--------------------------------------------------------------------------------------
#Event RainbowMez "#*#You are enthralled by rainbows#*#"
Sub Event_RainbowMez
|	/if (${Group} && ${DoGroupBeg}) /gsay RC
|	/doevents flush RainbowMez
/return
|--------------------------------------------------------------------------------------
|-Event: HotFootDebuff
|--------------------------------------------------------------------------------------
#Event HotFootDebuff "#*#You foot is on fire. Run to put it out#*#"
Sub Event_HotFootDebuff
|	/if (${Group}) /gsay !!!HOT FOOT Running to put it out!!!
	/call DoBackOff
	:hotfootloop
	/if (${Circle.Status.Equal[OFF]}) /circle on 20
	/delay 1s 
	/if (${Me.Buff[Hot Foot].ID} || ${Me.Song[Hot Foot].ID}) /goto :hotfootloop
	/if (${Circle.Status.Equal[ON]}) /circle off
	/varset BackOffFlag 0
	/doevents flush HotFootDebuff
/return
|-------------------------------------------------------------------------------------
|- SUB: EventLogic795 -Enslaver of Souls
|-------------------------------------------------------------------------------------
Sub EventLogic795
	|- /if (${assistid}!=${Me.ID} &&  && ) {
	|-	/stick id ${assistid} 10
	|- }
	|- /if (${Me.XTarget[1].ID} && ${assistid}!=${Me.ID}) {
	|-	/call EngageAttack
	|- }
/return
|-------------------------------------------------------------------------------------
|- SUB: EventLogic815 -Fell Foliage
|-------------------------------------------------------------------------------------
Sub EventLogic815
	/if (${assistid}!=${Me.ID} && ${Spawn[Cactiikii].ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER]} && ${Me.PctHPs}<=50 && !${BackOffFlag}) {
		/call DoBackOff
	} else /if (${Spawn[Cactiikii].ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER]} && ${BackOffFlag}) {
		/varset BackOffFlag 0
	}
/return
|-------------------------------------------------------------------------------------
|- SUB: EventLogic797 -Damsel of Decay
|-------------------------------------------------------------------------------------
Sub EventLogic797
	/if (${Zone.ID}==797) {
		/if (${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,ENC,WIZ,MAG,NEC,SHD,PAL,BRD,BER]} && (${Me.Buff[Withering Physicality XIII].ID} || ${Me.Buff[Withering Limbs XIII].ID})) {
			/if (${Me.Buff[Withering Physicality XIII].ID} && ${Me.ItemReady[135331]}) /casting 135331|item
			/if (${Me.Buff[Withering Limbs XIII].ID} && ${Me.ItemReady[35919]}) /casting 35919|item	
		}	
		/if (${Select[${Me.Class.ShortName},CLR,SHM,DRU]} && (${Me.Buff[Withering Physicality XIII].ID} || ${Me.Buff[Withering Faith XIII].ID})) {
			/if (${Me.Buff[Withering Physicality XIII].ID} && ${Me.ItemReady[35919]}) /casting 35919|item
			/if (${Me.Buff[Withering Faith XIII].ID} && ${Me.ItemReady[135331]}) /casting 135331|item
		}
		/if (${Select[${Me.Class.ShortName},WAR,SHD,PAL]} && ${Me.Buff[Withering Physicality XIII].ID}) {
			/if (${Me.Buff[Withering Physicality XIII].ID} && ${Me.ItemReady[35919]}) /casting 35919|item
		}
		/if (${Spawn[Anashti Sul, Damsel of Decay].DistanceZ.Int}>30 && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,ENC,WIZ,MAG,NEC,SHD,PAL,BRD,BER]} && !${Navigation.Active} && !${BackOffFlag}) {
			|-Downstairs
			/if (${Target.Z} < -400) {
				/call DoBackOff
				/delay 5
				/nav locxyz -5.51 -103.89 -421.41
				/delay 1s
				/call NavgationDelay
			} else {
				/call DoBackOff
				/delay 5
				/nav locxyz 29.59 -113.82 -370.70
				/delay 1s
				/call NavgationDelay
			}
		}
		/if (${Spawn[Anashti Sul, Damsel of Decay].DistanceZ.Int}<30 && ${BackOffFlag} && !${Navigation.Active}) /call DoBackOff
	}
/return
|--------------------------------------------------------------------------------------
|-Event: 16th Anniversary Shared Task: Pirates of Timorous Deep
|--------------------------------------------------------------------------------------
#Event A16Pirates1 "#*#Captain Turek shouts, 'Prepare to fire the cannon!'"
Sub Event_A16Pirates1	
	/popcustom 14 !!!MOVE TUREK === CANNONBALL INC === MOVE TUREK!!!
/return 
|--------------------------------------------------------------------------------------
|-Event: Anniversary Shared Task: Pub Crawl
|--------------------------------------------------------------------------------------
#Event A16PubCrawl1 "#*#Galdorin Visigothe says, 'My stinky stein has rough dirty lips,'"
Sub Event_A16PubCrawl1	
	/say My stinky stein has rough dirty lips,
/return 
#Event A16PubCrawl2 "#*#Galdorin Visigothe says, 'but she loves a deep carouse.'"
Sub Event_A16PubCrawl2	
	/say but she loves a deep carouse. 
/return 
#Event A16PubCrawl3 "#*#Galdorin Visigothe says, 'Beer or ale are her great trips.'"
Sub Event_A16PubCrawl3	
	/say Beer or ale are her great trips. 
/return 
#Event A16PubCrawl4 "#*#Galdorin Visigothe says, 'No matter how many vows'"
Sub Event_A16PubCrawl4	
	/say No matter how many vows
/return 
#Event A16PubCrawl5 "#*#Galdorin Visigothe says, 'I make or break, my drinking glass'"
Sub Event_A16PubCrawl5	
	/say I make or break, my drinking glass
/return 
#Event A16PubCrawl6 "#*#Galdorin Visigothe says, 'reminds me of my lovely Brasse.'"
Sub Event_A16PubCrawl6	
	/say reminds me of my lovely Brasse.
/return 
|--------------------------------------------------------------------------------------
|-Event: 15th Anniversary Group Mission: War Games
|--------------------------------------------------------------------------------------
#Event A15WarGames1 "#*#A catapult is about to fire in your direction!"
Sub Event_A15WarGames1	
	/mgax //popcustom 14 !!!MOVE === INC AE ON ${Me.CleanName}=== MOVE!!!
/return
|--------------------------------------------------------------------------------------
|-Event: The Return of King Xorbb
|--------------------------------------------------------------------------------------
#Event Xorbb3 "#*#King Xorbb shouts '|${Me.CleanName}|'"
Sub Event_Xorbb3
	/dgt I need to face away from him for a bit
	/beep
	/if (${Me.Combat}) /squelch /attack off 
	/if (${Stick.Active}) /stick off
	/target id ${Spawn[npc King Xorbb].ID}
	/delay 5
	/squelch /face away
	/delay 16s
/return
