|- File: ihcsubs.inc
|- Version 2.1
|- Original File: auto_subs.inc
|- Auto-Subs Shared routines across Auto series macros by Noobhaxor
|- Version 6.2
|- Updated: 4/25/2019
|- Modified version of the above file to maintain compatability with the automac's / kissassist
|- Modified to fit the IHC mac's and mod's better
#Event Camping           "#*#seconds to prepare your camp."
#Event GainSomething	 "#*#You have gained|#1#|"
#Event TaskUpdate		 "#*#Your task |#1#| has been updated#*#" 
#Event Zoned             "LOADING, PLEASE WAIT#*#"
#Event Zoned             "You have entered#*#"
#Event CAST_IMMUNE                 "#*# is immune to #*#"
#Event CAST_IMMUNE                 "Your target cannot be mesmerized#*#"
#Event CAST_RESIST                 "#*# resisted your #1#!"
#bind QuestSay			/qsay
#bind BackOff        /backoff
#bind Campfire       /campfire
#bind ChangeVarInt   /changevarint
#bind ToggleVariable /togglevariable
#bind GroupBehindMe  /rallybehind
#bind GroupFrontFace /rallyfront
#bind KillMATarget   /killtarget
#bind SetAutoTargetID /settarget
#bind ChaseMe		   /chaseme
#Bind SheepMove	     /sheepmove
|----------------------------------------------------------------------------
|- SUB: Compatibility with KissAssist Aliases Old and New
|----------------------------------------------------------------------------
Sub AliasSetup
	|- KissAssist and AutoMac Common Commands
	/squelch /alias /campradius     /changevarint General CampRadius
	|- IHC Mac common commands
	/alias /addicted /macro IHCMercs\IHC${Me.Class.ShortName}.mac
	/squelch /alias /assistrange	/changevarint Set AssistRange
	/squelch /alias /autoassistat	/changevarint Set AutoAssistAt
	/squelch /alias /burnit			/togglevariable BurnNow
	/squelch /alias /burncount		/changevarint Set BurnMobCount
	/squelch /alias /campexact		/togglevariable AutoCampHold
	/squelch /alias /endmedpct		/changevarint Set EndMedPct
	/squelch /alias /gpause			/togglevariable GroupPause
	/squelch /alias /gbackoff		/togglevariable GroupBackOff
	/squelch /alias /medpct			/changevarint Set MedPct
	/squelch /alias /smartassist	/togglevariable UseSmartAssist
	/squelch /alias /tglburn		/togglevariable BurnAlways
	/squelch /alias /tglbeg			/togglevariable DoGroupBeg
	/squelch /alias /tglzlogic		/togglevariable EventLogic
	/squelch /alias /tglmed			/togglevariable DoMed
	/squelch /alias /tglmelee		/togglevariable UseMelee
	|- DanNet Command Aliases
	/squelch /alias /mgx 			/dggexecute
	/squelch /alias /mgax 			/dggaexecute
	/alias /mgt 	/dgtell group_${EverQuest.Server}_${Group.Leader}
/return
Sub VarSetup
	/declare autotargetid		int outer 0
	/declare sittimer			timer outer 0
	/declare enablesit			int outer 0
	/declare ReturnToCamp		int outer 0
	/declare AutoCampX			int outer ${Me.X}
	/declare AutoCampY			int outer ${Me.Y}
	/declare changetoini		int outer 0
	/declare targetcleartimer	timer outer 0
	/declare numoftargets		int outer 0
	/declare ChaseAssist		int outer 0		
	|- IHC macro's common variables
	/declare GrPCond 			string outer .
	/declare TnKCond 			string outer .
	/declare PetTank 			int outer 0	
	/declare assistname 		string outer
	/declare assistid 			string outer
	/declare assisttargetid		string outer Me.GroupAssistTarget.ID
	/declare MainTankName 		string outer
	/declare MainAssistType 	string outer
	/declare Ok2Assist			int outer 1
	/declare UseSpellInterrupt	int outer 0
	/declare burnnow			int outer 0
	/declare BackOffFlag		int outer 0
	/declare BeforeCombat		string outer NULL
	/declare GroupPauseFlag		int outer 0
	/declare GroupBackOffFlag	int outer 0
	/declare ReTargetDelay		timer outer	0
	/declare ShitOnCursor		string outer NULL
	/declare CursorTimer		timer outer 0
	/declare NoDisease			int outer 0
	/declare NoCorruption		int outer 0
	/declare NoPoison			int outer 0
	/declare NoFire				int outer 0
	/declare NoCold				int outer 0
	/declare NoChromatic		int outer 0
	/declare NoMagic			int outer 0
	/declare EventSetupFlag		int outer 0
	/declare KillTargetID		int outer 0
	/declare SpawnSearchType	string outer npc
	/declare BegTimer			timer outer	0

	/declare State				int outer 0
	/declare IllusionNum		int outer 0
	/declare RunAndGunMedTimer	timer outer	0

	/declare UseItems 			int outer 0

	/declare illusionItem 		string outer "Bone Mask of Horror"
|- Rezzing
	/declare setCombatRadius	int outer 50
	/declare setMaxRezRange 	int outer 90
	/declare rezToken 			bool outer FALSE
	/declare rezCombat			bool outer FALSE
|- AFK camping
    /declare AggressiveRadius 	int outer 100
	/declare AssistRangeZ 		int outer 20
    /declare PullAbility		string outer NULL
	/declare PullAbility3		string outer NULL
	/declare PullAbilityAA 		int outer 0
    /declare PullAbility2 		int outer 0
	/declare PullAutoCampX		int outer 0
    /declare PullAutoCampY		int outer 0
	/declare PullAutoCampZ		int outer 0
	/declare PullDistance 		int outer 0
	/declare PullDistance3 		int outer 0
	/declare ResourceChecker 	int outer 1
	/declare Limit 				int outer 30
	/declare DummyTime        	int outer 10
	/declare DummyMsg         	string outer  "BRB, the roof is on fire."
|	/declare PCRadiusCheck 		int outer 10
|- Balance events
	/declare HighHPID 					int outer 0
    /declare highhppct 					int outer 99
    /declare Balance 					int outer 0
|- Assisting

|- Modes
	/declare Mode 				int outer 0
	/declare PreviousMode 		int outer 0
	/declare ModeName 			string outer NULL
	/declare PreviousModeName 	string outer NULL
	
|- core_cast2
	/declare castReturn 		string outer NULL
	/declare castBreak 			bool outer TRUE

	
|- Raiding
	/declare RangeToTarget 		int outer 15

	/echo -----${MacroName} LOADING------
	/if (${Me.XTarget[1].TargetType.NotEqual[Auto Hater]}) {
		/echo Extended Target 1 HAS TO BE SET TO Auto Hater
		/xtarget set 1 Autohater
		/echo Set Extended Target 1 to Auto
	  }
	|-Check for loaded plugins
|	/call CheckPlugin MQ2Cast
|    /call CheckPlugin MQ2Exchange
	/call CheckPlugin MQ2Rez
	/call CheckPlugin MQ2AdvPath
	/call CheckPlugin MQ2MoveUtils
	/call CheckPlugin MQ2DanNet
	/call CheckPlugin MQ2Nav
	/call CheckPlugin MQ2Autoloot
	/call CheckPlugin AAspend
	/call CheckPlugin AutoGroup
	/call CheckPlugin MQ2Hud
	/call CheckPlugin MQ2EasyFind
	/call CheckPlugin MQ2SpawnSort
	/call UnCheckPlugin MQ2Twist
	/squelch /rez accept on
    /squelch /rez loot off
	/squelch /rez pct 20
	/aaspend order 3521
	/aaspend brute on
	/aaspend bonus on
	|- Set the order of the tabs to be spent when brute force is on. 1=general,2=archetype,3=class,4=special,5=focus
	|- /aaspend order 32541 - Brute force mode would buy all AAs in this order Class, Archetype, Focus, Special, General
	|-Disable mq2melee if its running
	/if (${Plugin[MQ2Melee].Name.Length}) {
		/if (${Melee.Enable}) {
			/melee off
		}
	}
	|- Load DanNet to communicate with other box chars in the same group. 
	/if (${Plugin[MQ2DanNet].Name.Length}) {
		/if (${DanNet.CommandEcho}) /squelch /dnet commandecho off
	}
/return
|----------------------------------------------------------------------------
|- SUB: IllusionCheck - Check for Plaguebringer illusion
|----------------------------------------------------------------------------
Sub check_illusion(bool _debug, string _illusionItem)
	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, item, ${_illusionItem}, ${Me.ID}]}) /cast item ${_illusionItem}
/return
|----------------------------------------------------------------------------
|- SUB IHC Common Config Options - Config options that will be the same across all mac's
|----------------------------------------------------------------------------
Sub LoadCommonConfig
	/call LoadIni Combat DoAutoTarget			int 1
	/call LoadIni Combat DoAutoEngage			int 1
	/call LoadIni Combat FollowMarkTarget		int 0
	/call LoadIni General IHCMacVersion			string 0.0
	/call LoadIni General FollowToonName 		string NULL
	/if (${Select[${Me.Class.ShortName},CLR,SHM]}) {
		/call LoadIni General acverbose				int 1
	} else {
		/call LoadIni General acverbose				int 0
	}
	/call LoadIni General AssistRange			int 100
	/call LoadIni General AutoAssistAt			int 98
	/call LoadIni General AutoCampHold			int 1
	/call LoadIni General AutoCampRadius		int 30
	/call LoadIni General BurnAlways 			int 0
	/call LoadIni General BurnMobCount 			int 3
	/call LoadIni General BurnNamed 			int 1
	/call LoadIni General DoMed				 	int 1
	/call LoadIni General EndMedPct				int 95
	/call LoadIni General MedPct			 	int 90
	/call LoadIni General ModRodManaPct			int 0
	/call LoadIni General InstantRelease 		int 0
	/call LoadIni General StickToKillTarget		int 1
	/call LoadIni General UseFellowship 		int 0
	/call LoadIni General UseModRods	 		int 0
	/call LoadIni General UseSmartAssist		int 1
	/call LoadIni General UseZoneLogic			int 0
	/call LoadIni Options DoBuffs				int 1
	/call LoadIni Options DoGroupBeg			int 0
	/if (${AutoCampHold}) /moveto dist 2
	/stick set breakontarget on
	/if (${Select[${Me.Class.ShortName},CLR,DRU,SHM,PAL,RNG,BST]}) {
		/declare callID													int 			outer 0
		/declare NULLPoint												int 			outer 0
		/declare PetPoint 												int				outer 80
		/declare CLRPoint		 										int 			outer 80
		/declare DRUPoint 												int 			outer 70
		/declare SHMPoint 												int 			outer 60
		/declare WIZPoint 												int 			outer 75
		/declare MAGPoint 												int 			outer 75
		/declare ENCPoint 												int 			outer 80
		/declare NECPoint 												int 			outer 75
		/declare WARPoint 												int 			outer 70
		/declare MNKPoint 												int 			outer 60
		/declare ROGPoint 												int 			outer 60
		/declare RNGPoint 												int 			outer 90
		/declare BSTPoint 												int 			outer 70
		/declare SHDPoint 												int 			outer 90
		/declare BRDPoint 												int 			outer 65
		/declare BERPoint 												int 			outer 70
		/declare PALPoint 												int 			outer 90
		/declare GoMpoint 												int 			outer 80	
		/declare PanicPoint 											int 			outer 40	
		|/call timer_set FALSE tXHeal																			string		outer 3m 		timer_set_xtarget
	}
/return
|----------------------------------------------------------------------------
|- SUB IHC Common Config Options - Config options that will be the same across all mac's
|----------------------------------------------------------------------------
Sub SaveCommonConfig
	/call SetIni Combat DoAutoTarget			int ${DoAutoTarget}
	/call SetIni Combat DoAutoEngage			int ${DoAutoEngage}
	/call SetIni Combat FollowMarkTarget		int ${FollowMarkTarget}
	/call SetIni General FollowToonName 		string ${FollowToonName}
	/call SetIni General AssistRange			int ${AssistRange}
	/call SetIni General AutoAssistAt			int ${AutoAssistAt}
	/call SetIni General AutoCampHold			int ${AutoCampHold}
	/call SetIni General AutoCampRadius			int ${AutoCampRadius}
	/call SetIni General BurnAlways 			int ${BurnAlways}
	/call SetIni General BurnMobCount 			int ${BurnMobCount}
	/call SetIni General BurnNamed	 			int ${BurnNamed}
	/call SetIni General DoMed				 	int ${DoMed}
	/call SetIni General EndMedPct				int ${EndMedPct}
	/call SetIni General MedPct				 	int ${MedPct}
	/call SetIni General ModRodManaPct			int ${ModRodManaPct}
	/call SetIni General InstantRelease 		int ${InstantRelease}
	/call SetIni General StickToKillTarget 		int ${StickToKillTarget}
	/call SetIni General UseFellowship 			int ${UseFellowship}
	/call SetIni General UseModRods 			int ${UseModRods}
	/call SetIni General UseSmartAssist			int ${UseSmartAssist}
	/call SetIni General UseZoneLogic			int ${UseZoneLogic}
	/call SetIni Options DoBuffs				int ${DoBuffs}
	/call SetIni Options DoGroupBeg				int ${DoGroupBeg}
/return
|----------------------------------------------------------------------------
|- SUB: check_state
|---------------------------------------------------------------------------- 
Sub check_state(bool _debug)

	| am I moving?
	/if (${Me.Moving}) /return
	
	| am I casting?
	/if (${Me.Casting.ID} && !${Me.Class.ShortName.Find[BRD]}) /return

	| is my spell in cooldown?
	/if (${Me.SpellInCooldown} && !${Me.Class.ShortName.Find[BRD]}) /return
	
	| am I navigating?
	/if (${Navigation.Active}) /return

	| am I dead?
	/if (${Me.Hovering}) /call DeathSub
	
	| mod rod on cursor?
	|/if (${Cursor.ID}) /call BagModRods
	
	| have I been knocked down?
	/if (${Me.State.Equal[FEIGN]}) /stand

	/if (${Me.XTarget}) /return

	| if I don't have a target: relax
	/if (!${Me.XTarget}) {
		
		| if stick is on we can turn it off
		/if (${Stick.Status.Equal[ON]}) /stick off

		| attack off
		/attack off

		| clear target
		/if (${Target.ID}) /target clear

		| check pet
		/if (${Me.Pet.ID}) /pet back off
		
		/if (${Me.Book[${Aura1}]} || ${Me.CombatAbilityReady[${Aura1}]}) {
			| check aura one
			/if (!${Spell[${Me.Aura[1]}].ID} && !${Me.Song[${Aura1}].ID}) {

				/if (${Select[${Me.Class.ShortName},BRD]}) /stopsong
				
				/echo attempting to cast ${Aura1}
				/if (${validate_cast[FALSE, FIND, ${Aura1}, ${Me.ID}]}) /call core_cast2 "${Aura1}" FIND ${Me.ID} FALSE

				/if (!${Select[${Me.Class.ShortName},WAR,ROG,MNK,BER]}) {
					
					| reload the spell if i just memmed aura
					/call LoadSpellBar
				}
			}
		}

		/if (${Me.Book[${Aura2}]}) {
			| check aura one
			/if (!${Spell[${Me.Aura[2]}].ID} && !${Me.Song[${Aura2}].ID}) {

				/if (${validate_cast[FALSE, FIND, ${Aura2}, ${Me.ID}]}) /call core_cast2 "${Aura2}" FIND ${Me.ID} FALSE

				/if (!${Select[${Me.Class.ShortName},WAR,ROG,MNK,BER]}) {

					| reload the spell if i just memmed aura
					/call LoadSpellBar
				}
			}
		}

		/if (${Select[${Me.Class.ShortName},WIZ,ENC,MAG]}) {
			
			| Check book for first harvest
			/if (${Me.Book[${HarvestSpell1}]}) {
				
				| Condition for first harvest
				/if (${Me.PctMana} < 50) {

					| Trigger first harvest
					/if (${validate_cast[FALSE, FIND, "${HarvestSpell1}", ${Me.ID}]}) /call core_cast2 "${HarvestSpell1}" FIND ${Me.ID} FALSE
				}
			}
		}

|		/call check_illusion FALSE ${illusionItem}
		/if (${Me.Standing} && (${Me.PctMana} < 90 || ${Me.PctEndurance} < 90)) /sit
	}
/return
|----------------------------------------------------------------------------
|- SUB: set_timers
|---------------------------------------------------------------------------- 
Sub set_timers
	/if (${TimeForMezVariable}==1 && !${Me.XTarget[1].ID}) /varset TimeForMezVariable 0
		

	/if (${Me.XTarget[1].ID} && ${TimeForMezVariable}==0) {
		/varset TimeForMez 6s
		/varset TimeForMezVariable 1
	}

/return
|----------------------------------------------------------------------------
|- SUB: ModeSet
|----------------------------------------------------------------------------
Sub ModeSet
	/if (${PreviousMode}!=${Mode}) {

		/if (${PreviousMode}==0) /varset PreviousModeName Travel
		/if (${PreviousMode}==1) /varset PreviousModeName ManualPullCamping
		/if (${PreviousMode}==2) /varset PreviousModeName ManualRunAndGun
		/if (${PreviousMode}==3) /varset PreviousModeName AFKPullCamping
		/if (${PreviousMode}==4) /varset PreviousModeName AFKRunAndGun
		/if (${PreviousMode}==5) /varset PreviousModeName DoEvent
		/if (${PreviousMode}==6) /varset PreviousModeName Raid

		/if (${Mode}==0) /varset ModeName Travel
		/if (${Mode}==1) /varset ModeName ManualPullCamping
		/if (${Mode}==2) /varset ModeName ManualRunAndGun
		/if (${Mode}==3) /varset ModeName AFKPullCamping
		/if (${Mode}==4) /varset ModeName AFKRunAndGun
		/if (${Mode}==5) /varset ModeName DoEvent
		/if (${Mode}==6) /varset ModeName Raid

 		/docommand /dgt \ar Previous mode ${PreviousModeName} \ag Current mode ${ModeName}
		/varset PreviousMode ${Mode}
	}
/return
|----------------------------------------------------------------------------
|- SUB: MakeCamp
|----------------------------------------------------------------------------
Sub MakeCamp
	/if (${MakeCamp.Status.Equal[ON]}) /makecamp off
	/if (${Navigation.Active}) /nav stop
	/delay 5
	/varset PullAutoCampY ${Me.Y}
	/varset PullAutoCampX ${Me.X}
	/varset PullAutoCampZ ${Me.Z}
	/delay 5
/return
|----------------------------------------------------------------------------
|- SUB: RemoveTravelBuffs
|---------------------------------------------------------------------------- 
Sub RemoveTravelBuffs
	/makemevisible
	/delay 2
	/removebuff Group Perfected Levitation
	/delay 2
	/removebuff Group Perfected Invisibility to Undead
	/delay 2
/return
|----------------------------------------------------------------------------
|- SUB: Engage
|---------------------------------------------------------------------------- 
Sub Engage
	
	| if not target then nothing to engage
	/if (!${Target.ID}) /return

	| if target is not an NPC then don't engage
	/if (!${Target.Type.Equal[NPC]}) /return

	| tank engage if target is close enough
	/if (${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && (${Target.PctHPs} < 100 ||${Navigation.PathLength[id ${Target.ID}]} < 30)) {
		/if (${Target.ID}) /face fast
		/if (!${Stick.Active}) /stick 12 moveback loose
		/delay 10 ${Stick.Active}
		/if (${Target.ID}) /squelch /attack on
	}

	| melee dps engage if target is close enough
	/if (!${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && (${Target.PctHPs} < 97 || ${Navigation.PathLength[id ${Target.ID}]} < 30)) {
		/if (${Target.ID}) /face fast
		/if (!${Stick.Active}) /stick 12 hold moveback !front loose
		/delay 10 ${Stick.Active}
		/if (${Target.ID}) /squelch /attack on
	}

|	/if (${Target.PctHPs}<98 || ${Navigation.PathLength[id ${Target.ID}]} < 25) {
|		/if (${AssistRange}>80) {
|			/varcalc SmartAssistRange ${AssistRange}*1.1
|		} else /if (${AssistRange}>50) {
|			/varcalc SmartAssistRange ${AssistRange}*1.7
|		} else /if (${AssistRange}>25) {
|			/varcalc SmartAssistRange ${AssistRange}*2.1
|		} else /if (${AssistRange}>10) {
|			/varcalc SmartAssistRange ${AssistRange}*2.4
|		} else /if (${AssistRange}>0) {
|			/varcalc SmartAssistRange ${AssistRange}*4.2
|		}
|		/if (${Navigation.PathLength[id ${Target.ID}]} > ${SmartAssistRange}) /return
|	} else {
|		/if (${Navigation.PathLength[id ${Target.ID}]} > ${AssistRange}) /return
|	}
	
|	/if (${Math.Distance[${Target.Y},${Target.X},${Target.Z}:${PullAutoCampY},${PullAutoCampX},${PullAutoCampZ}]} > ${AssistRange}) /return

|	/if (${Select[${Me.Class.ShortName},WAR,ROG,BER,MNK,BRD]}) {
|		/if (${Target.ID}) /face fast
|		/stick ${StickHow} 10
|		/delay 10 ${Stick.Active}
|		/squelch /attack on
|	}
/return
|----------------------------------------------------------------------------
|- SUB: CastersEngage
|---------------------------------------------------------------------------- 
Sub CastersEngage
	/if (${Me.Class.ShortName.Find[CLR]}) /target id ${Group.MainTank.ID}
	/if (!${Me.Class.ShortName.Find[CLR]}) /assist ${Group.MainAssist.Name}
	/if (${Target.ID}) /face fast
/return
|----------------------------------------------------------------------------
|- SUB: PostCombat
|---------------------------------------------------------------------------- 
Sub PostCombat(bool _debug)
	/if (${Me.XTarget}) /return
	/if (${Stick.Status.Equal[ON]}) /stick off
	/attack off
	/if (${Target.ID}) /target clear
	/if (${Me.Pet.ID}) /pet back off
/return
|----------------------------------------------------------------------------
|- SUB: Travel
|----------------------------------------------------------------------------
Sub Travel
	/if (${Stick.Status.Equal[ON]}) /stick off
	/if (${MakeCamp.Status.Equal[ON]}) /makecamp off
	/attack off
	/if (${Me.Pet.ID} && ${Me.Combat}) /pet back off

	/if (${Navigation.MeshLoaded} && ${Group.Leader.ID} != ${Me.ID}) {
		/if (!${Navigation.Active} && ${Navigation.PathLength[id ${Group.Leader.ID}]} > 50) /nav id ${Group.Leader.ID}
		/if (${Navigation.Active} && ${Navigation.PathLength[id ${Group.Leader.ID}]} < 20) /nav stop
	}

	/if (${Select[${Me.Class.ShortName},SHM]}) {
		/call core_cast2 "${TravelSpell}" FIND ${Me.ID} FALSE
	}

	/if (${Select[${Me.Class.ShortName},BRD]} && !${Me.Buff[Selo's Accelerating Chorus].ID} && !${Me.Casting.ID}) {
		/stopsong
		/melody 3 1
	}
/return
|----------------------------------------------------------------------------
|- SUB: puller_check_group_resources
|---------------------------------------------------------------------------- 
Sub puller_check_group_resources
	
	/if (${Me.XTarget[1].ID}) /return
	/if (${Group.Puller.ID} != ${Me.ID}) /return

	/declare bmember	int local 0
	/if (${Limit} == 30 && ${ResourceChecker} == 0) /varset Limit 85
	/if (${Limit} == 85 && ${ResourceChecker} == 1) /varset Limit 30
	/varset ResourceChecker 1

	/for bmember 0 to ${Group}
		/if (${Group.Member[${bmember}].Distance} < 100 && !${Group.Member[${bmember}].OtherZone} && !${Me.Moving}) {
			/if (${Select[${Group.Member[${bmember}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG,DRU,SHD,PAL]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${bmember}].Name.Lower} "Me.PctMana" "ResPct" "int"
			} else /if (${Select[${Group.Member[${bmember}].Class.ShortName},WAR,ROG,BER,MNK]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${bmember}].Name.Lower} "Me.PctEndurance" "ResPct" "int"
			}
			/if (${ResPct} < ${Limit}) {
				/varset ResourceChecker 0 
				/delay 5
			}
			/if (${ResourceChecker} == 0) /return
		}
	/next bmember
/return
|----------------------------------------------------------------------------
|- SUB: check_add_aggro
|---------------------------------------------------------------------------- 
Sub check_add_aggro

	/if (${Balance}) /return
	/if (!${Me.XTarget[2].ID}) /return
|	/if (${TimeForMez}!=0) /return

	/declare x int local 0
	/if (${Target.Type.Equal[Corpse]}) /target clear

	| if any npcs on xtarget have less than 100% aggro
	/if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100) {
		/if (${If[${Select[${SpawnSort[1,asc,PctAggro,xtarhater].Animation},110,26,32,71,72,111]}, 0, 1]}==1) {
			/target id ${SpawnSort[1,asc,PctAggro,xtarhater].ID}
			/delay 5 ${Target.ID}==${SpawnSort[1,asc,PctAggro,xtarhater].ID}
			/call Engage
			/call get_aggro
		}
	}

|	/for x 1 to ${Me.XTarget}
|		:getaggro
|		/if (${If[${Select[${Me.XTarget[${x}].Animation},110,26,32,71,72,111]}, 0, 1]}==1 && ${Me.XTarget[${x}].PctAggro}<100 && ${Me.XTarget[${x}].Distance}<=${AssistRange}) {
|			/target id ${Me.XTarget[${x}].ID}
|			/delay 5 ${Target.ID}==${Me.XTarget[${x}].ID}
|			/if (!${AdvPath.Following}) /call Engage
|			/if (${Me.XTarget[${x}].PctAggro}<100) /call DoCombat
|		}
|		/if (${Target.Type.Equal[Corpse]}) /target clear
|		/if (!${Me.XTarget[1].ID} || ${Target.ID}==${Me.ID} || !${Target.ID}) /return
|		/if (${Me.XTarget[${x}].PctAggro}<100 && ${If[${Select[${Me.XTarget[${x}].Animation},110,26,32,71,72,111]}, 0, 1]}==1 && ${Me.XTarget[${x}].Distance}<=${AssistRange}) {
|			/goto :getaggro
|		}
|	/next x
/return
|----------------------------------------------------------------------------
|- SUB: AddToAlert
|---------------------------------------------------------------------------- 
Sub AddToAlert
	/declare i int local 0
	/squelch /alert clear 1

	/docommand /dgt \aw Creating alert list for \ag ${Zone.Name} \aw from eq.db
	/sqlite C:\Users\janne\OneDrive\Desktop\Release\Macros\IHCMercs\DB\eq.db ignore_list SELECT DISTINCT NAME, ID FROM ignore_pulling WHERE ZONE_ID = ${Zone.ID};
	/if (!${sqlite.rows[ignore_list]}) /return
	/for i 1 to ${sqlite.rows[ignore_list]}
		/squelch /alert add 1 id ${sqlite.result[ignore_list ${i} ID]}
		/docommand /dgt \aw Added \ag ${sqlite.result[ignore_list ${i} NAME]} \aw to ignore
		/delay 1
	/next i
/return
|----------------------------------------------------------------------------
|- SUB: AFKPull
|---------------------------------------------------------------------------- 
Sub afk_pull
	/declare PullTargetID 	int local 0
	/declare Dummy 			int local 0
	/declare i 				int local 1
	/declare MobsInRadius 	int local 0
	/declare PathLength 	int local 9999

	/if (${Me.XTarget[1].ID}) /return
	/if (!${Group.Puller.ID}==${Me.ID}) /return
	/if (${Me.Casting.ID}) /return

	/if (${Select[${Me.Class.ShortName},SHD,WIZ,PAL,DRU,ENC]}) {
		/if (${Me.PctMana}<20) /return
	}
	/if (${Select[${Me.Class.ShortName},WAR,MNK,BER,ROG]}) {
		/if (${Me.PctEndurance}<20) /return
	}

	/if (${ResourceChecker}==0) /return
	/if (${Me.Snared.ID}) /return

	/if (!${PullAbility.Equal[Melee]}) {
		/if (!(${Me.CombatAbilityReady[${PullAbility}]} || ${Me.AbilityReady[${PullAbility}]} || ${Me.AltAbilityReady[${PullAbility}]} || ${Me.SpellReady[${PullAbility}]} || (!${FindItem[${PullAbility2}].TimerReady} && ${PullAbility2}))) /return
	}
	/if (${AdvPath.Following}) /afollow off

	/varset MobsInRadius ${SpawnCount[npc targetable noalert 1 radius ${AggressiveRadius} zradius ${AssistRangeZ}]}

	/while (${i} <= ${MobsInRadius}) {
		/if (${Navigation.PathExists[id ${NearestSpawn[${i}, npc targetable noalert 1 radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}]}) {
			/if (${NearestSpawn[${i}, npc targetable noalert 1 radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}) /varset Dummy ${NearestSpawn[${i}, npc targetable noalert 1 radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID} 
			/if (${PathLength} > ${Navigation.PathLength[id ${Dummy}]}) {
				/varset PathLength ${Navigation.PathLength[id ${Dummy}]}
				/varset PullTargetID ${Dummy}
			}
		}
		/varcalc i ${i}+1
		/delay 1
		
	}
	
	/if (!${PullTargetID}) /return
	
	/if (${Mode}!=3) {
		/if (${Navigation.Active}) /nav stop
		/return
	}
	
	/if (${Navigation.MeshLoaded} && (${Spawn[id ${PullTargetID}].Distance}>${PullDistance} || !${Spawn[id ${PullTargetID}].LineOfSight})) /nav id ${PullTargetID}
	/while (${Navigation.Active}) {
		/delay 1s ${Spawn[id ${PullTargetID}].Distance}<=${PullDistance}
		/if (${Spawn[id ${PullTargetID}].LineOfSight}) /target id ${PullTargetID}
		/if (${Me.XTarget}) /varset PullTargetID ${Me.XTarget[1].ID}
		/if (${Navigation.Active} && ${Spawn[id ${PullTargetID}].Distance}<=${PullDistance} && ${Spawn[id ${PullTargetID}].LineOfSight}) /nav stop
	}
	
	/if ((!${Target.ID}!=${PullTargetID} || !${Target.ID}) && ${Spawn[id ${PullTargetID}].LineOfSight}) /target id ${PullTargetID}
	/delay 1s ${Target.ID}==${PullTargetID}

    /while (${PullTargetID}==${Target.ID} && ${Spawn[id ${PullTargetID}].LineOfSight}) {
		/if (${Me.Sitting}) /stand
		/if (${PullTargetID}!=${Target.ID}) /target id ${PullTargetID}
		/if (${PullAbility.Equal[Melee]}) /attack on
		/if (!${PullAbility.Equal[Melee]} && ${validate_cast[FALSE, FIND, ${PullAbility}, ${PullTargetID}]}) /call core_cast2 "${PullAbility}" FIND ${PullTargetID} FALSE
		|/if (${Spawn[id ${PullTargetID}].LineOfSight} && ${Me.AltAbilityReady[Distant Strike]}) /alt act 376
		/if (${Me.Class.ShortName.Find[MNK]}) /call Defense
		/if (${Mode}!=3) {
			/if (${Navigation.Active}) /nav stop
			/return
		}
		/if (!${Navigation.Active} && ${Spawn[id ${PullTargetID}].Distance}>${PullDistance}) /nav id ${PullTargetID}
		/if (${Navigation.Active} && ${Spawn[id ${PullTargetID}].Distance}<=${PullDistance} && ${Spawn[id ${PullTargetID}].LineOfSight}) /nav stop
		/if (${Me.XTarget}) /break
	}
    /nav locxyz ${PullAutoCampX} ${PullAutoCampY} ${PullAutoCampZ}
	/if (${Me.Class.ShortName.Find[MNK]}) /call Defense
	/delay 30s ${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${PullAutoCampY},${PullAutoCampX},${PullAutoCampZ}]}<7
	/if (${Navigation.Active}) /nav stop
    /if (${Target.ID}) /face fast
	/if (${Defined[PullTargetID]}) /deletevar PullTargetID
	/if (${Defined[PathLength]}) /deletevar PathLength
 /return
|----------------------------------------------------------------------------
|- SUB: MoveToCamp
|---------------------------------------------------------------------------- 
Sub MoveToCamp(int Xloc, int Yloc, int Zloc, int Distance)

	| if casting return
	/if (${Me.Casting.ID} && !${Select[${Me.Class.ShortName},BRD]}) /return

	| if target is running let melee follow it
	/if (${Target.ID}) {
		/if (${Target.Fleeing} || !${Target.Snared.ID}) /return
	}

	/if (${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && ${Target.Type.Equal[NPC]}) {
		/if (!${Target.PctAggro}>=100) /return
	}

	/if (${Target.Rooted.ID}) /return

	/if (${Navigation.Active}) /return

	| if I have a target then the distance to move to camp is larger to allow for a larger assist range
	/if (${Me.XTarget}) {
		/if (${Distance}>80) {
			/varcalc Distance ${Distance}*1.1
		} else /if (${Distance}>50) {
			/varcalc Distance ${Distance}*1.7
		} else /if (${Distance}>25) {
			/varcalc Distance ${Distance}*2
		} else /if (${Distance}>10) {
			/varcalc Distance ${Distance}*2.5
		} else /if (${Distance}>0) {
			/varcalc Distance ${Distance}*4
		}
	}
	
	/if (${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${Yloc},${Xloc},${Zloc}]}>${Distance}) {
		/if (${Stick.Active}) /stick off
		/nav locxyz ${Xloc} ${Yloc} ${Zloc}
		:movinghome
			/if (${Mode}==0) {
				/nav stop
				/return
			}
			/delay 5
			/if (${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${Yloc},${Xloc},${Zloc}]}>${Distance} && ${Navigation.Active}) /goto :movinghome
		/if (${Navigation.Active}) /nav stop
		/if (${Target.ID}) /face fast
		/delay 10
	}
/return
|----------------------------------------------------------------------------
|- SUB: pre_combat_buffs
|---------------------------------------------------------------------------- 
Sub pre_combat_buffs(bool _debug, string _spell, string _type, string _tmpID)
	/if (${Me.XTarget} && !${Me.Combat}) {
		/if (${validate_cast[FALSE, ${_type}, ${_spell}, ${_tmpID}]}) /call core_cast2 ${_spell} ${_type} ${_tmpID} FALSE
	}
/return
|----------------------------------------------------------------------------
|- SUB: check_resources
|---------------------------------------------------------------------------- 
Sub check_resources(bool _debug, string _spell, string _type, int _tmpID, int _condition)

	| FALSE "Gather Mana" spell ${Me.ID} 50

	/if (${Select[${Me.Class.ShortName},CLR,DRU,SHM,NEC,WIZ,ENC]}) {
		/if (${Me.PctMana} < ${_condition}) {
			/if (${validate_cast[FALSE, ${_type}, ${_spell}, ${_tmpID}]}) /call core_cast2 ${_spell} ${_type} ${_tmpID} FALSE
				|sub core_cast2(string _spell, string _type, int _tmpID, string _sub, bool _debug)
		}
	} else /if (${Select[${Me.Class.ShortName},WAR,BER,MNK]}) {
		/if (${Me.Combat}) /return
		/if (${Me.XTarget[1].ID}) /return
		/if (${Me.PctEndurance} < ${_condition}) {
			/if (${validate_cast[FALSE, ${_type}, ${_spell}, ${_tmpID}]}) /call core_cast2 ${_spell} ${_type} ${_tmpID} FALSE
		}
	}
	/delay 5s !${Me.Casting.ID}
	/if (${Select[${Me.Class.ShortName},ENC]} && ${Cursor.Name.Equal[Azure Mind Crystal]}) {
		/if (${Cursor.Name.Equal[Azure Mind Crystal]} && ${Me.FreeInventory}>1) /autoinventory
		/delay 1s
		/if (!${FindItem[${_spell}].TimerReady}) /call ItemNow "${_spell}"
	}
/return
|----------------------------------------------------------------------------
|- SUB: PetAttack
|---------------------------------------------------------------------------- 
Sub PetAttack
	/if (!${Me.Pet.ID}) /return
	/assist ${Group.MainAssist.Name}
	/if (!${Target.Type.Equal[NPC]}) /return
	/if (${Target.PctHPs}>${AutoAssistAt}) /return
	/if (${Target.Distance}>${AssistRange}) /return

	|- Pet Attack
	/if (${Target.PctHPs}>=30 && ${Me.AltAbilityReady[Spirit Call]}) {
		/alt act 177
		/delay 2
	}
	/if (!${Me.Pet.Combat}) {
		/pet attack 
		/pet swarm
	}
	
	/if (!${Spawn[${Group.MainTank} pccorpse radius 40].ID} && ${Me.Pet.Taunt}) /pet taunt off
	/if (${Spawn[${Group.MainTank} pccorpse radius 40].ID} && !${Me.Pet.Taunt}) /pet taunt on
/return
|----------------------------------------------------------------------------  
|- SUB: SetControlToon
|----------------------------------------------------------------------------
Sub SetControlToon
	|-Set Main Assist/Tank
	/if (${Target.ID}) {
		/if (${Target.Type.Equal[Pet]}) {
			/varset TnKCond .Pet.
			/varset PetTank 1
			/varset assistname 	${Target.Master.Name}
		} else {
			/varset PetTank 0
			/varset assistname 	${Target.Name}
		}
		/varset assistid 	${Target.ID}
		/varset MainAssistType ${Target.Type}
	} else /if (${Group}) {
		/if (${Group.MainAssist.ID}) {
			/echo \aw No Target Selected - Switching Group Main Assist
			/target id ${Group.MainAssist.ID}
			/delay 1s ${Target.ID}
			/if (${Target.Type.Equal[Pet]}) {
				/varset TnKCond .Pet.
				/varset PetTank 1
				/varset assistname ${Target.Master.Name}
			} else {
				/varset PetTank 0
				/varset assistname ${Target.Name}
			}
		} else {
			/echo \aw No Target Selected - Switching to First Group Member
			/squelch /keypress f2
			/delay 1s ${Target.ID}
			/if (${Target.Type.Equal[Pet]}) {
				/varset TnKCond .Pet.
				/varset PetTank 1
				/varset assistname ${Target.Master.Name}
			} else {
				/varset PetTank 0
				/varset assistname ${Target.Name}
			}
		}
		/varset assistid  ${Target.ID}
		/varset MainAssistType ${Target.Type}
	} else /if (${Me.Class.ShortName.Equal[ENC]}) {
		/beep
		/echo \aw This Macro Requires a Group or Player Target at Start up
		/echo \aw Ending Macro
		/endmac
	} else {
		/echo \aw No Group or Target - Switching to Self Assist mode
		/varset assistname		${Me.Name}
		/varset MainAssistType 	${Me.Type}
		/varset assistid 		${Me.ID}
	}
	|- /if (${Group.Member[${assistname}].ID} && ${Group.Leader.ID}==${Me.ID} && ${Group.MainAssist.ID}!=${assistid}) /grouproles set ${Group.Member[${assistname}].ID} 2 
/return 
|----------------------------------------------------------------------------  
|- SUB: Back Off and stop melee  New Version
|----------------------------------------------------------------------------      
Sub Bind_BackOff  
	/call DoBackOff
/return 
Sub DoBackOff
	/if (${BackOffFlag}) {
		/echo \aw Resetting. No Longer Backing off. \ar OFF
		/varset BackOffFlag 0
	} else {
		/echo \aw Resetting. Backing off. \ag ON
		/if (${Target.ID}) /target clear
		/if (${Me.Combat}) /squelch /attack off 
		/if (${Stick.Active}) /stick off
		/if (${Me.Pet.ID}) /pet back off
		/varset BackOffFlag 1
		/call AutoCampCheck
	}
	/doevents flush Event_BackOff  
/return
|----------------------------------------------------------------------------
|- SUB: Event Camping - end macro
|----------------------------------------------------------------------------
Sub Event_Camping	
	/if (${Me.Casting.ID}) /stopcast
	/end
/return
|----------------------------------------------------------------------------
|- SUB: Event CAST_RESIST
|----------------------------------------------------------------------------
Sub Event_CAST_RESIST
	/varset CastResult CAST_RESIST
	/doevents flush Event_CAST_RESIST
/return
|----------------------------------------------------------------------------
|- SUB: Event CAST_IMMUNE
|----------------------------------------------------------------------------
Sub Event_CAST_IMMUNE
	/varset CastResult CAST_IMMUNE
	/doevents flush Event_CAST_IMMUNE
/return
|----------------------------------------------------------------------------
|- SUB: Campfire ${Window[FellowshipWnd].Child[FP_CampPage].Child[FP_CampsiteViewer].Text}
|----------------------------------------------------------------------------
Sub Bind_Campfire
	/if ((${Me.Fellowship.Campfire} && (${Select[${Me.Fellowship.CampfireZone},${Zone.Name}]} || ${Me.Fellowship.CampfireZone.Name.Find[guild hall]})) || (${Me.InInstance}==FALSE)) /return
    /declare FellowCount int local 0
    /declare i int local
    /declare j int local
    /for i 1 to ${SpawnCount[pc radius 50]}
        /for j 1 to ${Me.Fellowship.Members}
            /if (${NearestSpawn[${i},PC radius 50].CleanName.Equal[${Me.Fellowship.Member[${j}]}]}) /varcalc FellowCount ${FellowCount}+1
        /next j
    /next i
    /if (${FellowCount}>=3) {
        /windowstate FellowshipWnd open
		/delay 10
		/nomodkey /notify FellowshipWnd FP_Subwindows tabselect 2
		/nomodkey /notify FellowshipWnd FP_DestroyCampsite leftmouseup
		/delay 5s ${Window[ConfirmationDialogBox].Open}
		/if (${Window[ConfirmationDialogBox].Open}) /nomodkey /notify ConfirmationDialogBox Yes_Button leftmouseup
		/delay 5s !${Me.Fellowship.Campfire}
		/delay 1s
		/nomodkey /notify FellowshipWnd FP_RefreshList leftmouseup
		/delay 1s        
		/nomodkey /notify FellowshipWnd FP_CampsiteKitList listselect 1
		/delay 1s
		/nomodkey /notify FellowshipWnd FP_CreateCampsite leftmouseup
		/delay 5s ${Me.Fellowship.Campfire}
		/windowstate FellowshipWnd close
		/if (${Me.Fellowship.Campfire}) /echo Campfire Dropped
    }
/return
|----------------------------------------------------------------------------
|- SUB: Event Zoned
|----------------------------------------------------------------------------
Sub Event_Zoned(Message)
	/call Zoning
/return
	
Sub Zoning
	/delay 1m !${Me.Zoning}
	
	/delay 50
/return
|----------------------------------------------------------------------------
|- SUB: Load Ini
|----------------------------------------------------------------------------
Sub LoadIni(string sectionName, string varName, string varType, string varValue)     
	/if (!${Defined[${varName}]} && ${Defined[varType]}) /declare ${varName} ${varType} outer 0
	/if (!${Ini[${IniFileName},${sectionName},${varName}].Length}) {
		/if (${varValue.Length}) {
			/ini "${IniFileName}" "${sectionName}" "${varName}" "${varValue}"
			/varset ${varName} ${varValue}
			/echo \aw set \ag ${varName} \ay ${varValue}
		}
	} else {
		/varset ${varName} ${Ini[${IniFileName},${sectionName},${varName}]} 
		/echo \aw set \ag ${varName} \ay ${varValue}
	}
/return
|----------------------------------------------------------------------------
|- SUB: Set Ini
|----------------------------------------------------------------------------
Sub SetIni(string sectionName, string varName, string varType, string varValue)
    /if (${varValue.Length}) {
        /ini "${IniFileName}" "${sectionName}" "${varName}" "${varValue}"
    }
/return
|----------------------------------------------------------------------------
|- SUB: CLCheck - Check Command Line options.
|----------------------------------------------------------------------------
Sub CLCheck
    /if (!${Macro.Params}) /return
	/declare plc int local 0
	/declare NumParams int local ${Math.Calc[${Macro.Params}-1]}
    /for plc 0 to ${NumParams}
        /if (${Defined[Param${plc}]}) {
			/if (${Param${plc}.Arg[1,|].Equal[MA]} && ${Spawn[=${Param${plc}.Arg[2,|]}].ID}) {
					/varset assistname ${Spawn[=${Param${plc}.Arg[2,|]}].Name}
					/varset assistid ${Spawn[=${Param${plc}.Arg[2,|]}].ID}
			} else /if (${Param${plc}.Arg[1,|].Equal[MT]} && ${Spawn[=${Param${plc}.Arg[2,|]}].ID}) {
					/varset MainTankName ${Spawn[=${Param${plc}.Arg[2,|]}].Name}
			} else /if (${Param${plc}.Arg[1,|].Equal[INI]} && ${Param${plc}.Arg[2,|].Length}) {
				/varset IniFileName ${Param${plc}.Arg[2,|]}.ini
			}
        }
    /next plc
/return
|----------------------------------------------------------------------------
|- SUB: Gquery. Used for DanNet Queries on other connected members. Creates new variables for use in subs  
|- Before calling this sub check for a connected member, ex:/if (${DanNet.Peers.Find[${EverQuest.Server.Lower}_${Group.Member[#].Name.Lower}]})
|- Calling this sub quotes around tmpquery, varName and varType are recommended to avoid any potential concatenation of strings
|- EX:/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${bmember}].Name.Lower} "Spell[${FocusSpell}].Stacks" "tmpstackcheck" "bool"
|---------------------------------------------------------------------------- 
Sub Gquery(string DnetName, string tmpquery, string varName, string varType)
	/if (!${Defined[${varName}]} && ${Defined[varType]}) {
		/if (${varType.Equal[int]}) {
			/declare ${varName} ${varType} outer 0
		} else /if (${varType.Equal[bool]}) {
			/declare ${varName} ${varType} outer FALSE
		} else /if (${varType.Equal[string]}) {
			/declare ${varName} ${varType} outer NULL
		}
	}
	/dquery ${DnetName} -q "${tmpquery}" -o ${varName}
	/delay 20 ${DanNet[${DnetName}].Query["${tmpquery}"].Received}
/return
|----------------------------------------------------------------------------
|- SUB: FollowToon
|---------------------------------------------------------------------------- 
Sub FollowToon
/if (${Spawn[pc =${FollowToonName}].ID}) {
	/if (${Me.Dead}) /return
	/if (${Spawn[pc =${FollowToonName}].Distance}>20 && !${Spawn[pc =${FollowToonName}].Dead} && ${Spawn[pc =${FollowToonName}].Distance}<400) {
		 /squelch /afollow spawn ${Spawn[pc =${FollowToonName}].ID}
		 /delay 2s ${Spawn[pc =${FollowToonName}].Distance}<20
		 /if (${Spawn[pc =${FollowToonName}].Distance}<20) /squelch /afollow off
	}
}
/return
|----------------------------------------------------------------------------
|- SUB: AutoCampCheck - Modified - AutoCampHold set to 1 will cause a return to camp /loc everytime and not just when we move out of AutoCampRadius
|----------------------------------------------------------------------------
Sub AutoCampCheck
|----Camp Return Logic
	/if (${Spawn[=${FollowToonName}].ID} && (!${Me.Casting.ID}) && !${MoveTo.Moving} && ${ReturnToCamp}==1) {
		/varset ReturnToCamp 0
		/echo \aw FollowToon Detected - \ar Disabling Camp
	} else /if (${Stick.Status.Equal[ON]} && ${ReturnToCamp}==1) {
|-		/varset ReturnToCamp 0
|-		/echo \aw Stick Detected - \ar Disabling Camp
	} else /if (${AdvPath.Following} && ${ReturnToCamp}==1) {
		/varset ReturnToCamp 0
		/echo \aw AdvPath Follow Detected - \ar Disabling Camp
	} else /if (!${Spawn[=${FollowToonName}].ID} && ${Stick.Status.Equal[OFF]} && !${Me.Casting.ID} && ${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}>${AutoCampRadius} && (${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}<400) && !${MoveTo.Moving} && ${ReturnToCamp}==1) {
		/moveto loc ${AutoCampY} ${AutoCampX}|on
		:movinghome
		/delay 5
		/if ((${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}>20) && (${MoveTo.Moving})) /goto :movinghome
		/moveto off
	} else /if (${AutoCampHold} && !${Spawn[=${FollowToonName}].ID} && ${Stick.Status.Equal[OFF]} && !${Me.Casting.ID} && (${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}<400) && (${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}>=5) && !${MoveTo.Moving} && ${ReturnToCamp}==1) {
		/moveto loc ${AutoCampY} ${AutoCampX}|on
		:movinghome2
		/delay 5
		/if ((${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}>5) && (${MoveTo.Moving})) /goto :movinghome2
		/moveto off
	}
/return
|----------------------------------------------------------------------------
|- SUB: BagModRods
|----------------------------------------------------------------------------
Sub BagModRods
	/if (!${Cursor.ID} ) /return
	/if ((${Cursor.ID}) && ${CursorTimer}==0 && ${ShitOnCursor.Equal[NULL]} && (${Me.FreeInventory}>1)) {
		/varset ShitOnCursor ${Cursor}
		/varset CursorTimer 1m
	} else /if (${CursorTimer}==0 && ${ShitOnCursor.NotEqual[NULL]} && (${Me.FreeInventory}>1)) {
		/echo \aw Something has been left on cursor for over a minute Bagging it
		/autoinventory
		/varset ShitOnCursor NULL
	} else /if (${ShitOnCursor.Find[Transvergence]} && (${Me.FreeInventory}>1)) {
		/echo \aw Bagging Mod Rod
		/autoinventory
		/varset ShitOnCursor NULL
	} else /if (${ShitOnCursor.Find[Modulation]} && (${Me.FreeInventory}>1)) {
		/echo \aw Bagging Mod Rod
		/autoinventory
		/varset ShitOnCursor NULL
	}
	/if (${Cursor.Name.Equal[Azure Mind Crystal]} && ${Me.FreeInventory}>1) /autoinventory
/return
|----------------------------------------------------------------------------
|- SUB: Event Gain Something - DanNet message 
|----------------------------------------------------------------------------    
Sub Event_GainSomething(string Line, string text)
    /if (${Line.Find["ABILITY POINT!"]}) {
        /docommand /dgt \aw ${Me.Name} gained an AA, now has ${Me.AAPoints} unspent \ax
    } else /if (${Line.Find[LEVEL]}) {
        /docommand /dgt \aw ${Me.Name} gained a level, now is Level ${Me.Level} \ax
	}
/return 
|----------------------------------------------------------------------------
|- SUB: Event Unpullable - DanNet message 
|----------------------------------------------------------------------------    
Sub Event_Unpullable(string Line, string text)
    /if (${Line.Find["You cannot cast Distant Strike"]}) {
        /docommand /dgt \aw Adding ${Target.Name} to unpullable list \ax
    }
/return 
|----------------------------------------------------------------------------
|- SUB: Event Task Update - DanNet message 
|----------------------------------------------------------------------------    
Sub Event_TaskUpdate(string Line, string name) 
    /if (${acverbose}!=0) /docommand /dgt \at Task updated...(${name})\ax    
/return
|----------------------------------------------------------------------------
|- SUB: Check Plugin
|----------------------------------------------------------------------------
Sub CheckPlugin(string pluginname)
    /if (!${Bool[${Plugin[${pluginname}]}]}) {
        /squelch /plugin ${pluginname} noauto
        /echo \aw ${pluginname} \ar not detected! \aw This macro requires it! Loading ...
    }
/return	
|----------------------------------------------------------------------------
|- SUB: Death Sub
|----------------------------------------------------------------------------
Sub DeathSub
	/echo You are sleeping with the fishes
	/if (${ReturnToCamp}!=0) /varset ReturnToCamp 0
    :DeathSubwait
	/if (${Window[RespawnWnd].Open} && ${UseFellowship}==1 && ${InstantRelease}==1) {
		/nomodkey /notify RespawnWnd RW_OptionsList listselect 1 
		/delay 1s
		/nomodkey /notify RespawnWnd RW_SelectButton leftmouseup
		/delay 5s ${Me.Zoning}
	}
    /if (${Me.Hovering}) /goto :DeathSubwait
	/delay 1m !${Me.Zoning}
	/if (${UseFellowship}==1 && ${FindItem["Fellowship Registration Insignia"].Timer}==0) {
		/delay 30s ${Me.CombatState.Equal[ACTIVE]}
		/useitem "Fellowship Registration Insignia"
		/delay 2s ${FindItem["Fellowship Registration Insignia"].Timer}!=0
	} else /if (${UseFellowship}==1 && ${FindItem["Fellowship Registration Insignia"].Timer}!=0) {
		/echo \aw Bummer, Insignia on cooldown, you must really suck at this game...
	} else {
		/echo \aw Waiting on someone that knows how to heal to \ar rez me
	}
/return
|----------------------------------------------------------------------------
|- SUB: AutoMed - Modified SitCheck from auto subs, user configureable end/mana % to start medding at 
|- Need: EndMedPct and MedPct variables to use.
|---------------------------------------------------------------------------- 
Sub AutoMed
|---SIT Check
   /if ((${Me.Moving} || ${Me.XTarget[1].ID} || ${MoveTo.Moving} || ${Me.CombatState.Equal[COMBAT]} || ${Stick.Status.Equal[ON]} || ${AdvPath.Following}) && (${enablesit}==1)) /varset enablesit 0
|--Out of Combat MedTime - Sitting
	|-/if (${Me.Standing} && !${Me.Moving} && ${Stick.Status.Equal[OFF]} && !${Me.XTarget[1].ID} && !${MoveTo.Moving} && !${AdvPath.Following} && ${Me.CombatState.NotEqual[COMBAT]} && ${Me.CombatState.NotEqual[DEBUFFED]} && ${enablesit}==0 && ((${Me.PctMana}<=${MedPct} && ${Me.MaxMana}>1000) || (${Me.PctEndurance}<=${EndMedPct} && ${Me.MaxEndurance}>1000))) {
	/if (${Me.Standing} && !${Me.Moving} && ${Stick.Status.Equal[OFF]} && !${Me.XTarget[1].ID} && !${MoveTo.Moving} && !${AdvPath.Following} && ${Me.CombatState.NotEqual[COMBAT]} && ${Me.CombatState.NotEqual[DEBUFFED]} && ${enablesit}==0 && ((${Me.PctMana}<=${MedPct}) || (${Me.PctEndurance}<=${EndMedPct}))) {
		/varset enablesit 1
	} else /if (${sittimer}==0 && ${enablesit}==0 && ${Me.Sitting} && (${Me.Moving} || ${Me.XTarget[1].ID} || ${MoveTo.Moving} || ${Me.CombatState.Equal[COMBAT]} || ${Stick.Status.Equal[ON]} || ${AdvPath.Following})) {
		/stand
		/varset sittimer 10s
	} else /if (${sittimer}==0 && ${enablesit}==1 && !${Me.Sitting}) {
		/sit
		/varset sittimer 10s
	}
/return
|----------------------------------------------------------------------------
|- SUB: UnCheck Plugin
|----------------------------------------------------------------------------
Sub UnCheckPlugin(string pluginname)
    /if (${Bool[${Plugin[${pluginname}]}]}) {
        /squelch /plugin ${pluginname} unload
        /echo \ar ${pluginname} detected! \aw Unloading it before it fucks shit up! UnLoading ...
    }
/return	
|----------------------------------------------------------------------------
|- SUB: DiscQueue
|---------------------------------------------------------------------------- 
Sub DiscQueue(string nextdisc)
	/if (!${Me.Standing}) /stand
	/delay 10 ${Me.Standing}
	/if (${Window[SpellBookWnd]}) /book
	/if (${Me.ActiveDisc.ID}) /stopdisc
	/delay 20 !${Me.ActiveDisc.ID}
	/squelch /disc ${nextdisc}
	/delay 20 ${Me.ActiveDisc.ID}
	/delay 8 !${Me.CombatAbilityReady[${nextdisc}]}
|	/if (${acverbose}!=0) /echo \aw Casting \ag ${nextdisc}
/return
|----------------------------------------------------------------------------
|- SUB: DiscNow
|---------------------------------------------------------------------------- 
Sub DiscNow(string nextdisc)
	/if (${Window[CastingWindow].Open}) /return
	/if (!${Me.Standing}) /stand
	/delay 10 ${Me.Standing}
	/if (${Window[SpellBookWnd]}) /book
	/squelch /disc ${nextdisc}
	/delay 8 !${Me.CombatAbilityReady[${nextdisc}]}
	/if (${acverbose}!=0) /echo \aw Casting \ag ${nextdisc}
/return
|----------------------------------------------------------------------------
|- SUB: AANow
|---------------------------------------------------------------------------- 
Sub AANow(int nextaa,int aatargetid)
	/if (${Spawn[ID ${aatargetid}].FeetWet}!=${Me.FeetWet} && ${Spawn[id ${aatargetid} npc].ID} && ${Window[CastingWindow].Open}) /return
	/if (!${Me.Standing}) /stand
	/delay 10 ${Me.Standing}
	/if (${Window[SpellBookWnd]}) /book
	/if (${Window[CastingWindow].Open}) /interrupt
	/delay 5 !${Window[CastingWindow].Open}
	/if (${Target.ID}!=${aatargetid} && ${Spawn[id ${aatargetid} npc].ID}) {
		/target id ${aatargetid}
		/delay 10 ${Target.ID}==${aatargetid}
	}
	/squelch /alt act ${nextaa}
	/delay 8 !${Me.AltAbilityReady[${nextaa}]}
|	/if (${acverbose}!=0) /docommand /dgt Casting \ao =>> \ag ${Me.AltAbility[${nextaa}].Name} \ao <<= \ax
/return
|----------------------------------------------------------------------------
|- SUB: AbilityNow
|---------------------------------------------------------------------------- 
Sub AbilityNow(string nextability)
	/squelch /doability ${nextability}
	/delay 8 !${Me.AbilityReady[${nextability}]}
|	/if (${acverbose}!=0) /echo \aw Casting \ag ${nextability}
/return
|----------------------------------------------------------------------------
|- SUB: ItemNow
|---------------------------------------------------------------------------- 
Sub ItemNow(string nextitem)
	/if (${Window[CastingWindow].Open}) /return
	/if (!${Me.Standing}) /stand
	/delay 10 ${Me.Standing}
	/if (${Window[SpellBookWnd]}) /book
	/if (${Window[CastingWindow].Open}) /interrupt
	/delay 5 !${Window[CastingWindow].Open}
	/useitem ${nextitem}
	/delay 15 !${Me.ItemReady[${nextitem}]}
|--Checks if item is used and does it again if not
	/if (${Me.ItemReady[${nextitem}]}&&${FindItem[${nextitem}].ID}) {
		/useitem ${nextitem}
		/delay 15 !${Me.ItemReady[${nextitem}]}
	}
|	/if (${acverbose}!=0) /echo \aw Using Item \ag ${nextitem}
/return
|----------------------------------------------------------------------------
|- SUB: BuffGroupMember
|---------------------------------------------------------------------------- 
Sub BuffGroupMember(string buffspell, int member)	
	/if (!${Me.Book[${buffspell}]}) /return
	/if (!${Me.Gem[${buffspell}]}) {
		:waitForMem
		/mem "${buffspell}" 10
		/delay 5
		/if (!${Me.Gem[${buffspell}]}) /goto :waitForMem
		/delay 20s !${Me.GemTimer[${buffspell}]}
	}
	:waitForReady
	/if (${Me.SpellReady[${buffspell}]}) {
		/docommand /dgt \ag ${buffspell} \ar =>> \ay ${Spawn[ID ${member}].Name} \ar <<=
		/target id ${Spawn[ID ${member}].ID}
		/delay 2s ${Spawn[ID ${member}].ID}==${Target.ID}
		/cast "${buffspell}" -targetid|${Spawn[ID ${member}].ID} -maxtries|2
		/delay 1m !${Me.Casting.ID}
	} else {
		/if (${Me.XTarget[1].ID}) /return
		/goto :waitForReady
	}
/return
|----------------------------------------------------------------------------
|- SUB: SpellQueue - Modified to use memspell replacement sub and return a cast result
|---------------------------------------------------------------------------- 
Sub SpellQueue(string nextspell,int nextid)
	/if (${Me.CurrentMana}<${Spell[${nextspell}].Mana}) /return
	/if (!${Me.Book[${nextspell}]}) /return
	/varset CastResult CAST_NO_RESULT
	/if (${Me.Sitting}) /stand
	/if (${Window[SpellBookWnd]}) /book
	/if (!${Me.Gem[${nextspell}]}) { 
		/delay 1s !${Me.Casting.ID}
		/call LoadSpellGem "${nextspell}" ${spellmisc}
		/if (!${Me.XTarget[1].ID}) {
			/delay 5s ${Me.GemTimer[${nextspell}]}==0
			/delay 5s ${Me.SpellReady[${nextspell}]}
		}
    }
	/if (${Me.SpellReady[${nextspell}]}) {
		/if (${Target.ID}!=${nextid}) {
			/if (${Me.Combat}) /squelch /attack off
			/target id ${nextid}
			/delay 10 ${Target.ID}==${nextid}
			/if (${Target.FeetWet}!=${Me.FeetWet}) /return
		}
		|- /if (${Target.Buff[${nextspell}].ID}) /return
		/if (${acverbose}!=0) /docommand /dgt \ag ${nextspell} \ar =>> \ay ${Spawn[ID ${nextid}].Name} \ar <<=
		/cast "${nextspell}"
		/delay 10 ${Window[CastingWindow].Open}
		/delay ${Math.Calc[(${Spell[${nextspell}].MyCastTime}*10)+15]} !${Me.Casting.ID}
	}
	/if (${CastResult.NotEqual[CAST_CANCELLED]}) {
		/varset CastResult ${Cast.Result}
	} else {
		/varset CastResult CAST_CANCELLED
	}
/return ${CastResult}
|----------------------------------------------------------------------------
|- SUB: FindTarget - melee attack portion removed. Melee attack moved into engage sub to reduce too far away and can not see messages
|---------------------------------------------------------------------------- 
Sub FindTarget
/declare xt int local 1
/declare xtlow int local ${AutoAssistAt}
/declare xtid int local 0
	/if (${Target.Type.Equal[Corpse]}) /target clear
	/if (!${Spawn[${SpawnSearchType} id ${autotargetid}].ID} && ${autotargetid}!=0) {
		/varset autotargetid 0
		/if (${Stick.Status.Equal[ON]}) /stick off
		/if (${burnnow}) /varset burnnow 0
	}
|--Query XTarget to find hp percents
	/for xt 1 to ${Me.XTarget}
		/if (${Me.XTarget[${xt}].PctHPs}<=${xtlow} && ${Spawn[id ${Me.XTarget[${xt}].ID} ${SpawnSearchType}].ID}) {
			/varset xtlow ${Me.XTarget[${xt}].PctHPs}
			/varset xtid ${Me.XTarget[${xt}].ID}
		}
	/next xt
|- Spawn search code to replace above Xtarget search
|- /declare MobIDList string local
|-	:targetsearch
|-	/if (${NearestSpawn[${xt},npc radius ${AssistRange} zradius 15 targetable playerstate 4].ID}) {
|-		/if (!${MobIDList.Find[|${NearestSpawn[${xt},npc radius ${AssistRange} zradius 15 targetable playerstate 4].ID}]} && ${NearestSpawn[${xt},npc radius ${AssistRange} zradius 15 targetable playerstate 4].PctHPs}<=${xtlow}) {
|-			/varset xtid ${NearestSpawn[${xt},npc radius ${AssistRange} zradius 15 targetable playerstate 4].ID}
|-			/varset xtlow ${Spawn[npc id ${xtid}].PctHPs}
|-			/varset MobIDList ${MobIDList}|${xtid}
|-		}		
|-		/varcalc xt ${xt}+1
|-		/goto :targetsearch
|-	}
|--Check target matches MA if not based off lowest hp in XTarget
	/if (${FollowMarkTarget}) {
		/if (${Me.GroupMarkNPC[${FollowMarkTarget}].ID} && ${autotargetid}!=${Me.GroupMarkNPC[${FollowMarkTarget}].ID}) {
			/varset autotargetid ${Me.GroupMarkNPC[${FollowMarkTarget}].ID}
		}
	} else /if (${Group.MainAssist.ID}!=${Me.ID} && ${autotargetid}!=${Me.GroupAssistTarget.ID} && ${Spawn[id ${Me.GroupAssistTarget.ID} ${SpawnSearchType}].ID}) {
		/varset autotargetid ${Me.GroupAssistTarget.ID}
	} else /if ((!${Group.MainAssist.ID} || ${Group.MainAssist.ID}==${Me.ID}) && ${Spawn[${SpawnSearchType} id ${xtid}].ID}) {
		/varset autotargetid ${xtid}
	}
|--Target the new target
	/if (${Target.ID}!=${autotargetid} && ${Spawn[${SpawnSearchType} id ${autotargetid}].ID}) {
		/squelch /target id ${autotargetid}
		/delay 10 ${Target.ID}==${autotargetid}
	}
/return 
|-------------------------------------------------------------------------------------
|- SUB: CastSpell - Taken from kissassist and modified. Better spell casting control for longer casting spells plus return messages for monitoring resists, interruptions, immune
|-------------------------------------------------------------------------------------
Sub CastSpell(string WhatSpell, int WhatID, string sentFrom)
    /declare MaxTryNum int local 2
	/varset CastResult CAST_NO_RESULT
    /if (!${Target.CanSplashLand} && ${Spell[${WhatSpell}].TargetType.Equal[Free Target]}) {
        /echo \ar Splash Spell will not cast at targets location. Skipping ${WhatSpell}
        /return
    }
    /if (${Target.ID}!=${WhatID} && ${Spell[${WhatSpell}].TargetType.NotEqual[Self]} && ${Spawn[id ${WhatID}].ID}) /call CastTarget ${WhatID}
    /if (${Me.Gem[${WhatSpell}]}) {
		/if (${Me.GemTimer[${WhatSpell}]}==0) {
            /casting "${WhatSpell}" -maxtries|${MaxTryNum}
            /while (${Cast.Status.Equal[C]} && ${CastResult.NotEqual[CAST_CANCELLED]}) {
                /delay 5
				/if (${Target.Type.Equal[Corpse]} && ${UseSpellInterrupt}) /stopcast
            }
            /call CastWait "${WhatSpell}"
            /if (${CastResult.NotEqual[CAST_CANCELLED]}) /varset CastResult ${Cast.Result}
			/doevents
        }
    } else {
        /echo \aw Skip Casting \ag ${WhatSpell}. \ar Sell Not Memed.
        /varset CastResult CAST_CANCELLED
    }
	/delay 4s
/return ${CastResult}  
|-------------------------------------------------------------------------------------
|- SUB: CastWait - Cast Spell sub routine from kissassist
|-------------------------------------------------------------------------------------
Sub CastWait(string WaitSpell)
    /if (${Spell[${WaitSpell}].CastTime}) {
        /while (${Me.Casting.ID} || ${Cast.Status.Equal[c]}) {
            /delay 5
			/if (${Target.Type.Equal[Corpse]} && ${UseSpellInterrupt}) /stopcast
        }
    }
/return
|-------------------------------------------------------------------------------------
|- SUB: CastTarget - Cast Spell sub routine from kissassist
|-------------------------------------------------------------------------------------
Sub CastTarget(int WhatID)
    /squelch /target clear
    /delay 10 !${Target.ID}
    /target id ${WhatID}
    /delay 10 ${Target.ID}==${WhatID}
/return
|------------------------------------------------------------------------------------------
|- SUB: LoadSpellGem - Replaces memspell sub
|------------------------------------------------------------------------------------------
Sub LoadSpellGem(string SpellToMem,int memgem)
	/declare ii int local
    /if (${SpellToMem.Length} && ${SpellToMem.NotEqual[null]}) {
        /if (${Me.Book[${SpellToMem}]}) {
            /if (${Int[${Me.Gem[${SpellToMem}]}]}>0 && ${Int[${Me.Gem[${SpellToMem}]}]}!=${memgem}) {
                /varcalc ii ${Int[${Me.Gem[${SpellToMem}]}]}-1
                /notify CastSpellWnd CSPW_Spell${ii} rightmouseup
                /delay 20 ${Int[${Me.Gem[${SpellToMem}]}]}==0
            }
            /if (!${Int[${Me.Gem[${memgem}].Name.Length}]} || ${Me.Gem[${memgem}].Name.NotEqual[${SpellToMem}]}) {
                /echo \ag Meming \aw ${SpellToMem} in \ag slot ${memgem}
                /memspell ${memgem} "${SpellToMem}"
                /delay 90 ${Me.Gem[${memgem}].Name.Equal[${SpellToMem}]}
            }
        } else {
                /echo \aw Could Not find the spell ${SpellToMem} in your spell book.
        }
    } else {
		/echo \ar Invalid \aw SpellToMem ${SpellToMem} 
	}
/return
|----------------------------------------------------------------------------
|- SUB: FindNumTargets
|---------------------------------------------------------------------------- 
Sub FindNumTargets
	/declare xt int local 1
	/if (!${Defined[numoftargets]}) /declare numoftargets int outer 0
	/varset numoftargets 0
	|--Query XTarget to find npcs
	/for xt 1 to ${Me.XTarget}
		/if (${Me.XTarget[${xt}].Type.Equal[NPC]}) /varcalc numoftargets ${numoftargets}+1
	/next xt
/return 
|----------------------------------------------------------------------------
|- SUB: IDUpdateCheck - keeps MA ID updated if it changes ( Death, Zoning )
|---------------------------------------------------------------------------- 
Sub IDUpdateCheck
	/if (${Spawn[pc =${assistname}].ID} && ${Spawn[pc =${assistname}].ID}!=${assistid}) {
		/echo \aw MA ID Mismatch - \ag Updating
		/varset assistid ${Spawn[pc =${assistname}].ID}
	}
/return
|-------------------------------------------------------------------------------------
|- SUB: ClickModRoD - 
|-------------------------------------------------------------------------------------
Sub ClickModRoD
	/if (${FindItem[Transvergence].ID} && ${FindItem[Transvergence].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Transvergence]}"
	/if (${FindItem[Modulation].ID} && ${FindItem[Modulation].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Modulation]}"
/return 
|-------------------------------------------------------------------------------------
|- SUB: PlayersInGroup - Checking for PC vs Merc
|-------------------------------------------------------------------------------------
Sub PlayersInGroup
	/declare i int local 0
	/declare gcnt int local 0
	/for i 1 to ${Group.Members}
		/if (${Group.Member[${i}].Type.Equal[PC]}) {
			/varcalc gcnt ${gcnt}+1
		}
	/next i
/return ${gcnt}
|----------------------------------------------------------------------------
|- BIND: GroupFrontFace - Credit EQMules mod of kissassist
|----------------------------------------------------------------------------
Sub Bind_GroupFrontFace(string radius)
	/declare GrpCount int local 0
	/call PlayersInGroup
	/varset GrpCount ${Macro.Return}
	/if (!${GrpCount}) {
		/echo no members in the group to order around, returning
		/return
	}
	/declare i int local 0
	/declare XOff float local 0
	/declare YOff float local 0
	/declare XMove float local 0
	/declare YMove float local 0
	/declare BaseRadians local
	/declare Multiplier local 90
	/if (${GrpCount}==2) {
		/varset Multiplier 45
	} else /if (${GrpCount}==3) {
		/varset Multiplier 30
	} else /if (${GrpCount}==4) {
		/varset Multiplier 23
	} else /if (${GrpCount}==5) {
		/varset Multiplier 18
	}
	/declare MyHeading float local ${Math.Calc[${Me.Heading.Degrees} - ${Multiplier}]}
	/declare BaseRadian float local ${Math.Calc[180 / ${GrpCount}]}
	/for i 1 to ${Group.Members}
		/if (${Group.Member[${i}].Type.Equal[PC]}) {
			/varcalc XMove ${Math.Cos[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
			/varcalc YMove ${Math.Sin[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
			/varcalc XOff ${Me.X} + ( ${Int[${radius}]} * ${XMove} )
			/varcalc YOff ${Me.Y} + ( ${Int[${radius}]} * ${YMove} )
			/dexecute ${Group.Member[${i}]} /sheepmove ${Me.ID} ${YOff} ${XOff}
		}
	/next i
/return
|----------------------------------------------------------------------------
|- BIND: GroupBehindMe - Credit EQMules mod of kissassist
|----------------------------------------------------------------------------
Sub Bind_GroupBehindMe(string radius)
	/declare GrpCount int local 0
	/call PlayersInGroup
	/varset GrpCount ${Macro.Return}
	/if (!${GrpCount}) {
		/echo no members in the group to order around, returning
		/return
	}
	/declare i int local 0
	/declare XOff float local 0
	/declare YOff float local 0
	/declare XMove float local 0
	/declare YMove float local 0
	/declare BaseRadians local
	/declare Multiplier local 270
	/if (${GrpCount}==2) {
		/varset Multiplier 224
	} else /if (${GrpCount}==3) {
		/varset Multiplier 208
	} else /if (${GrpCount}==4) {
		/varset Multiplier 200
	} else /if (${GrpCount}==5) {
		/varset Multiplier 196
	}
	/declare MyHeading float local ${Math.Calc[${Me.Heading.Degrees} - ${Multiplier}]}
	/declare BaseRadian float local ${Math.Calc[180 / ${GrpCount}]}
	/for i 1 to ${Group.Members}
		/if (${Group.Member[${i}].Type.Equal[PC]}) {
			/varcalc XMove ${Math.Cos[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
			/varcalc YMove ${Math.Sin[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
			/varcalc XOff ${Me.X} + ( ${Int[${radius}]} * ${XMove} )
			/varcalc YOff ${Me.Y} + ( ${Int[${radius}]} * ${YMove} )
			/dexecute ${Group.Member[${i}]} /sheepmove ${Me.ID} ${YOff} ${XOff}
		}
	/next i
/return
|----------------------------------------------------------------------------
|- BIND: SheepMove - Credit EQMules mod of kissassist
|----------------------------------------------------------------------------
Sub Bind_SheepMove(int shepherdID, int l_YLoc, int l_XLoc)
	/echo shepherdID=${shepherdID} l_YLoc=${l_YLoc} l_XLoc=${l_XLoc}
	/if (!${shepherdID}) {
		/echo cant invoke sheepmove, not enough arguments supplied
		/return
	}
	/declare oldRTC int local 0
	/declare oldChase int local 0
	/if (${Bool[${Plugin[mq2moveutils]}]}==TRUE) {
		/varset oldRTC ${ReturnToCamp}
		/varset oldChase ${ChaseAssist}
		/if (${Bool[${Plugin[mq2advpath]}]}==TRUE) {
        	       	/play off
 		}
		/if (${Bool[${Plugin[mq2navigation]}]}==TRUE || ${Bool[${Plugin[mq2nav]}]}==TRUE) {
        		/if (${Navigation.Active}) {
				/nav stop
			}
        }
		/call Bind_ToggleVariable ReturnToCamp off
		/call Bind_ToggleVariable ChaseAssist off
        /if (${MoveTo.Moving}) /moveto off
		/if (${Stick.Active}) /squelch /stick off
		/moveto mdist 3
		/moveto loc ${l_YLoc} ${l_XLoc}
		/delay 3s ${MoveTo.Moving}
		/delay 30s !${MoveTo.Moving}
		/delay 1s
		/moveto mdist 5
		/face id ${shepherdID}
		/if (${oldChase}) /call Bind_ToggleVariable ChaseAssist on
		/if (${oldRTC}) /call Bind_ToggleVariable ReturnToCamp on
	} else {
		/echo \aw SheepMove failed because you don't have \ag mq2moveutils \aw loaded.
	}
/return
|-------------------------------------------------------------------------------------
|- SUB: Welcome Message
|-------------------------------------------------------------------------------------
Sub WelcomeMsg
	/echo \aw****************************
	/echo \awWelcome to \ag${MacroName}
	/echo \awVersion \ag${IHCVersion}
	/echo \aw****************************
	/echo \aw use \ag /ihchelp \aw for a list of commands
/return
|---------------------------------------------------------------------------- 
|- SUB: BalanceHP & HighHP
|---------------------------------------------------------------------------- 
Sub balance_hp
	/if (!${Balance}) /return
	/if (!${Me.XTarget}) /return
	/if (!${Me.XTarget[2].ID}) /return
	/if (${Me.ID} != ${Group.MainAssist.ID}) /return
	:balance
	/if (!${Target.ID}) /target id ${Me.XTarget[1].ID}
	/call high_hp
	/if (!${Me.Combat} || ${Target.ID} == ${HighHPID}) {
	    /attack on
	    /if (${Me.XTarget[2].ID} && ${Balance}) /call Engage
		/if (${Me.XTarget[2].ID} && ${Balance}) /call AoEAggro
		/if (${Me.XTarget[2].ID} && ${Balance}) /call DoDisc
		/if (${Me.XTarget[2].ID} && ${Balance}) /call DoCombat
		/if (${Me.XTarget[2].ID} && ${Balance}) /call CombatBuffs	
	}
	/delay 1
	/if (${Me.XTarget[2].ID} && ${Balance}) /goto :balance
	/if (!${Me.XTarget[2].ID} || !${Balance}) /return

Sub high_hp
    /declare x int local 0
    /declare LowHP int local ${Target.PctHPs}
    /declare LowHPID int local ${Target.ID}
    /declare HighHP int local 0
    
    /for x 1 to ${Me.XTarget}
        /if (${Me.XTarget[${x}].PctHPs}<${LowHP}) {
            /varset LowHP ${Me.XTarget[${x}].PctHPs}
            /varset LowHPID ${Target.ID}
        }
        /if (!${Balance}) /return
        /if (${Me.XTarget[${x}].PctHPs}>${HighHP}) {
            /varset HighHP ${Me.XTarget[${x}].PctHPs}
            /varset HighHPID ${Me.XTarget[${x}].ID}
        }
    /next x
    
    /declare HPDiff int local 0
    /varcalc HPDiff ${HighHP}-${LowHP}
    /if (${HPDiff}>=2 && ${Target.ID}!=${HighHPID}) {
        /target id ${HighHPID}
        /delay 2s ${Target.ID}==${HighHPID}
    }
/return
|----------------------------------------------------------------------------
|- SUB: get_target  
|---------------------------------------------------------------------------- 
Sub get_target
	/declare x int local 0
	/declare npcIDontHaveAggroOnID int local 0

	| is there a target to be had?
	|/echo Checking xtarget
	/if (!${Me.XTarget}) /return

	| should we be balancing?
	|/echo Checking balance
	/if (${Balance}) /return

	| if I have a target: assist and get ready
	/if (${Me.XTarget}) {
		/if (${Me.Sitting}) /stand
		/if (${Target.Type.Equal[Corpse]}) /target clear
	}

	| if there is only one target on xtarget then target that
	/if (!${Me.XTarget[2].ID}) {
		/target id ${Me.XTarget[1].ID}
		/return
	}

	/if (${Me.ID} == ${Group.MainAssist.ID}) {

		/echo Distance of closest xtarget: ${SpawnSort[1,asc,PathLength,xtarhater].Distance}

		| if there is an xtarget close then target the one with lowest hp
		/if (${SpawnSort[1,asc,PathLength,xtarhater].Distance} < 200) {
			/target id ${SpawnSort[1,asc,PctHPs,xtarhater].ID}
		}
	}

	/if (${Me.ID}==${Group.MainTank.ID}) {

		| if current target is not 100% aggro then get aggro
		/if (${Target.ID}) {
			/if (${Target.PctAggro} < 100) /call get_aggro
			/if (${Target.PctAggro} < 100) /return
		}

		| if any npcs on xtarget have less than 100% aggro
		/if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100) {

			/varset npcIDontHaveAggroOnID ${SpawnSort[1,asc,PctAggro,xtarhater].ID}

			| is the mob mezzed?
			/if (${If[${Select[${SpawnSort[1,asc,PctAggro,xtarhater].Animation},110,26,32,71,72,111]}, 0, 1]}==1) {

				| if mob is not mezzed then target it and get aggro
				/target id ${npcIDontHaveAggroOnID}
				/delay 5 ${Target.ID} == ${npcIDontHaveAggroOnID}
				/call get_aggro
			}
		} else {
			/assist ${Group.MainAssist.Name}
		}
	}

	/if (${Me.ID} != ${Group.MainAssist.ID} && ${Me.ID} != ${Group.MainTank.ID}) /assist ${Group.MainAssist.Name}

/return
|-------------------------------------------------------------------------------- 
| Sub DummyMode
|--------------------------------------------------------------------------------
Sub DummyMode

	/if (${Me.XTarget}) /return
	/if (!${Spawn[gm].ID}) /return 
	/if (!(${SpawnCount[pc radius ${AggressiveRadius}]}>6)) /return 

	/declare i int local

	/echo Entering Dummy Mode... 
	/delay 3s 
	/afk ${DummyMsg}

	:waitabit 
	/for i 1 to ${DummyTime}
		/echo ${i}/${DummyTime}
		/if (${Me.XTarget}) /return
		/delay 1s 
	/next i
	/if (${Spawn[gm].ID} || (${SpawnCount[pc radius ${AggressiveRadius}]}>6)) /goto :waitabit 
	
	/afk off
	/delay 1s 
/return

|***
 *	DES: validates casting of "things on a target
 *	USE: /call ${validate_cast[[TRUE|FALSE], [spell|alt|disc|item|pulse|FIND], name, targetID, ForceTarget]
 *	NOTE: This is designed tomake sure whatever we are attempting to cast, is castable. be it a disc, item, spell, booger flick.. whatever.. IS IT READY TO BE USED?
 ***|
Sub validate_cast(bool _debug, string _type, string _spell, int _tmpID)
	|DEBUG \a-tvalidate_cast\ax(\a-w${_type}, ${_spell}, ${_tmpID}\ax)
	
	| _spell set to false
	/if (!${Bool[${_spell}]}) /return FALSE

	| obey invis
	/if (${Me.Invis}) /return FALSE
	
	| is the issued target dead?
	/if (${_tmpID}) {
		/if (!${Spawn[${_tmpID}].ID}) /return FALSE
	}

	| is the target an NPC?
	/if (!${Spell[${_spell}].SpellType.Equal[Beneficial]}) {
		/if (!${Spawn[npc los id ${_tmpID}].ID}) /return FALSE
	}

	|CHECKINPUTS
	
	| what type is it?
	/if (${_type.Equal[FIND]}) {
|		DEBUG ${dep}FIND${dep}${_type}
		/if (${Me.AltAbilityReady[${_spell}]}) {	
			/varset _type alt
		} else /if (${Me.Book[${Spell[${_spell}].RankName}]}) {
			/varset _type spell
		} else /if (${Me.CombatAbilityReady[${Me.CombatAbility[${Spell[${_spell}].RankName}]}]}) {
			/varset _type disc
		} else /if (${Me.ItemReady[${_spell}]}) {
			/varset _type item
		} else {
			/return FALSE
		}
|		DEBUG FOUND${dep}${_type}
	}
		
	| check spell
	/if (${_type.Equal[spell]}) {
|		DEBUG ${dep}spell\ax${dep}name:${_spell}
		
		| buff on me i shouldnt cast with?
|		/if (${check_no_cast_buff[FALSE]}) /return FALSE
		
		| am i casting a spell?
		/if (${Me.Casting.ID}) /return FALSE
		
		| global cooldown? is this shit broke?
		/if (${Me.SpellInCooldown}) /return FALSE
		
		| are we moving?
		/if (${Me.Moving}) /return FALSE
		/if (${Stick.Active}) /return FALSE
		/if (${Navigation.Active}) /return FALSE
		/if (${AdvPath.Following}) /return FALSE
		
		| correct rank name
|		/varset _spell ${Spell[${_spell}].RankName}
		
		| gem in cooldown?
		/if (${Me.GemTimer[${_spell}]}) /return FALSE
		
		| enough manna to cast?
		/if (${Me.CurrentMana} < ${Spell[${_spell}].Mana}) /return FALSE
		
		| dont fail buffs so they can be memed when needed
		/if (!${Me.SpellReady[${_spell}]} && !${Spell[${_spell}].Category.Equal[Heals]}) {
			/declare _pass bool local FALSE
			/if (${Spell[${_spell}].SpellType.Equal[Beneficial]}) /varset _pass TRUE
			/if (${Spell[${_spell}].SpellType.Equal[Pet]}) /varset _pass TRUE
			/if (${Spell[${_spell}].SpellType.Equal[aura]}) /varset _pass TRUE
			
			/if (!${_pass}) /return FALSE
		}
		
		| check cast range
		/if (${Spell[${_spell}].Range}) {
			/if (${Spawn[${_tmpID}].Distance} > ${Spell[${_spell}].MyRange}) /return FALSE
		}
		| check AE range
|		/if (${Spell[${_spell}].TargetType.Equal[Group V2]}) {
|			/if (${Spawn[${_tmpID}].Distance} > ${Spell[${_spell}].AERange}) /return FALSE
|		}
	
		| restist types vs zone control
|		/if (!${Spell[${_spell}].SpellType.Equal[Beneficial]}) {
|			/if (${NoDiseaseList.Find[${Target.DisplayName}]} && ${Spell[${_spell}].ResistType.Equal[Disease]}) /return FALSE
|			/if (${NoMagicList.Find[${Target.DisplayName}]} && ${Spell[${_spell}].ResistType.Equal[Magic]}) /return FALSE
|			/if (${NoPoisonList.Find[${Target.DisplayName}]} && ${Spell[${_spell}].ResistType.Equal[Poison]}) /return FALSE
|			/if (${NoFireList.Find[${Target.DisplayName}]} && ${Spell[${_spell}].ResistType.Equal[Fire]}) /return FALSE
|			/if (${NoColdList.Find[${Target.DisplayName}]} && ${Spell[${_spell}].ResistType.Equal[Cold]}) /return FALSE
|			/if (${NoCorruptionList.Find[${Target.DisplayName}]} && ${Spell[${_spell}].ResistType.Equal[Corruption]}) /return FALSE
|		}
		
		| check for stacking issues
		/if (${_tmpID} == ${Me.ID}) {
			/if (${Spell[${_spell}].SpellType.Equal[Beneficial]} && !${Spell[${_spell}].Category.Equal[Heals]}) {
				/if (!${Spell[${_spell}].NewStacks}) /return FALSE
				/if (${Me.Buff[${_spell}].ID}) /return FALSE
				/if (${Me.Song[${_spell}].ID}) /return FALSE		
			}
		}
		
		/if (!${Bool[${Me.Book[${_spell}]}]}) /return FALSE
|		DEBUG ${dep}validate spell END: ${Spell[${_spell}].RankName}


	| check alt ability
	} else /if (${_type.Equal[alt]}) {
|		DEBUG ${dep}alt\ax${dep}name:${_spell}
		/if (!${Me.AltAbilityReady[${_spell}]}) /return FALSE
		/if (${Me.CurrentMana} < ${Spell[${_spell}].Mana}) /return FALSE
		/if (${Spell[${_spell}].Range}) {
			/if (${Spawn[${_tmpID}].Distance} > ${Spell[${_spell}].MyRange}) /return FALSE
		}		
		| stacking
		/if (${Spell[${_spell}].SpellType.Equal[Beneficial]} && (${_tmpID} == ${Me.ID})) {
			/if (!${Spell[${_spell}].NewStacks}) /return FALSE
			/if (${Me.Buff[${_spell}].ID}) /return FALSE
			/if (${Me.Song[${_spell}].ID}) /return FALSE		
		}
	
	| check disc
	} else /if (${_type.Equal[disc]}) {
|		DEBUG ${dep}disc\ax${dep}name:${_spell}
		/varset _spell ${Spell[${_spell}].RankName}
		/if (!${Bool[${_spell}]}) /return FALSE
		/if (!${Me.CombatAbilityReady[${Me.CombatAbility[${Spell[${_spell}].RankName}]}]}) /return FALSE
		/if (${Me.CurrentEndurance} < ${Spell[${_spell}].EnduranceCost}) /return FALSE
		/if (${Spell[${_spell}].Range}) {
			/if (${Spawn[${_tmpID}].Distance} > ${Spell[${_spell}].MyRange}) /return FALSE
		}
		/if (${Bool[${Me.Song[${_spell}].Duration}]}) /return FALSE
		/if (${Bool[${Me.Buff[${_spell}].Duration}]}) /return FALSE		
					
		| stacking
		| /if (${Spell[${_spell}].SpellType.Equal[Beneficial]} && (${_tmpID} == ${Me.ID})) {
		| 	/if (!${Spell[${_spell}].NewStacks}) /return FALSE
		| }

	| check disc that requires running disc slot
	} else /if (${_type.Equal[activedisc]}) {
		/varset _spell ${Spell[${_spell}].RankName}
|		DEBUG ${dep}activedisc\ax${dep}name:${_spell}
		/if (!${Bool[${_spell}]}) /return FALSE
		/if (${Bool[${Me.ActiveDisc}]}) /return FALSE
		/if (!${Me.CombatAbilityReady[${Me.CombatAbility[${Spell[${_spell}].RankName}]}]}) /return FALSE
		/if (${Me.CurrentEndurance} < ${Spell[${_spell}].EnduranceCost}) /return FALSE

	| check item
	} else /if (${_type.Equal[item]}) {
|		DEBUG ${dep}item\ax${dep}name:${_spell}
		/if (!${FindItem[${_spell}].Timer.TotalSeconds}==0 && !${Me.ItemReady[=${_spell}]}) /return FALSE

		| check the distance
		/if (${_tmpID} != ${Me.ID}) {
			/if (${Spawn[${_tmpID}].Distance} > ${Spell[${FindItem[=${_spell}].Spell}].MyRange} && ${Spell[${FindItem[=${_spell}].Spell}].Range} != 0) /return FALSE
		}
		
		| do we already have the effect?
		/if (${_tmpID} == ${Me.ID}) {
			/if (${Me.Buff[${FindItem[=${_spell}].Spell}].ID}) /return FALSE
			/if (${Me.Song[${FindItem[=${_spell}].Spell}].ID}) /return FALSE
		}
					
		| stacking
		| /if (${Spell[${FindItem[=${_spell}].Spell}].SpellType.Equal[Beneficial]} && (${_tmpID} == ${Me.ID})) {
		| 	/if (!${Spell[${FindItem[=${_spell}].Spell}].NewStacks}) /return FALSE
		| }

	
	| check bard shit.. gotta be difficult..
	} else /if (${_type.Equal[pulse]}) {
		/varset _spell ${Spell[${_spell}].RankName}
		/if (${Me.CurrentMana} < ${Spell[${_spell}].Mana}) /return FALSE
		/if (${Me.Buff[${_spell}].Duration.Seconds} > 6) /return FALSE
		/if (${Me.Song[${_spell}].Duration.Seconds} > 6) /return FALSE
		/if (!${Spell[${_spell}].NewStacks}) /return FALSE
	}
/return TRUE
	| epic clicks
|	else /if (${_type.Equal[epicitem]}) {
|		DEBUG ${dep}epicitem\ax${dep}name:${_spell}
|		/if (!${Me.ItemReady[=${${Me.Class.ShortName}Epic${_spell}}]}) /return FALSE
|		/if (${_tmpID} != ${Me.ID}) {
|			/if (${Spawn[${_tmpID}].Distance} > ${Spell[${FindItem[=${${Me.Class.ShortName}Epic${_spell}}].Spell}].MyRange} && ${Spell[${FindItem[=${${Me.Class.ShortName}Epic${_spell}}].Spell}].Range} != 0) /return FALSE
|		}
|		/if (${Me.Buff[${FindItem[=${${Me.Class.ShortName}Epic${_spell}}].Spell}].ID}) /return FALSE
|		/if (${Me.Song[${FindItem[=${${Me.Class.ShortName}Epic${_spell}}].Spell}].ID}) /return FALSE
|		
|		/if (${Spell[${FindItem[=${${Me.Class.ShortName}Epic${_spell}}].Spell}].SpellType.Equal[Beneficial]} && (${Target.ID} == ${Me.ID})) {
|			/if (!${Spell[${FindItem[=${${Me.Class.ShortName}Epic${_spell}}].Spell}].NewStacks}) /return FALSE
|		}

	
|	} 
	


|***
 *	DES: checks your toon for buffs that should stop casting for some reason
 *	USE: /call check_no_cast_buff
 *	NOTE: this is by toon.
 ***|
|sub check_no_cast_buff(bool _debug)
|	DEBUG \a-tcheck_no_cast_buff\ax()
	
	| disabled?
|	/if (${lstNoCastWith.Arg[1,|].Equal[FALSE]} || !${Bool[${lstNoCastWith}]}) /return FALSE

|	/declare _count int local 0
|	/for _count 1 to ${lstNoCastWith.Count[|]}
|		AMIDEAD
|		CHECKINPUTS
|		/if (${Bool[${Me.Buff[${lstNoCastWith.Arg[${_count},|]}]}]}) /return TRUE
|		/if (${Bool[${Target.Buff[${lstNoCastWith.Arg[${_count},|]}]}]}) /return TRUE
|		/if (${Bool[${Me.Song[${lstNoCastWith.Arg[${_count},|]}]}]}) /return TRUE
|	/next _count
	
|/return FALSE


|***
 *	DES: spell/disc/aa/item cast wrapper
 *	USE: /call core_cast2 "SPELLNAME" [alt|activedisc|disc|gem#|item|epicitem|pulse] [TargetID|0 (for castless skills)] [subname|FALSE]
 *	NOTE: MQ2Cast ["spell name"|"item name"|"AA name"|"AA#"] [[item|slotname]|alt|gem#] [give up time][s|m] [custom subroutine name] [-targetid|###] [-maxtries|#] [-recast|#] [-setin|setname] [-bandolier|setname]
 *  NOTE2: the note above is full of crap... i wouldn't trust a thing it says..!
 *	Note3: lets be honest. i dont think i would trust any note anywhere in this script.
 ***|
sub core_cast2(string _spell, string _type, int _tmpID, string _sub, bool _debug)
	|DEBUG \a-tcore_cast2\ax(\a-w${_spell}, ${_type}, ${_tmpID}, ${_sub}\ax)
	| /if ((${Me.Casting.ID} || ${Window[CastingWindow].Open}) && !${Select[${Me.Class.ShortName},BRD]}) /return
	|AMIDEAD

	| obey invis
	/if (${Me.Invis}) /return FALSE

	|CLOSEBOOK
		
	| make sure we have our target 
	/if (${Bool[${_tmpID}]}) {
		/if (${Target.ID} != ${_tmpID}) {
			/squelch /target ID ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}
		}
	}
	
	| what type is it?
	| /if (${_type.Equal[FIND]}) {
	/if (${Select[${_type},FIND,FORCE]}) {
		|DEBUG ${dep}_type${dep}\a-w${_type}\ax
		/if (${Me.AltAbilityReady[${_spell}]}) {	
			/varset _type alt
		} else /if (${Me.Book[${Spell[${_spell}].RankName}]}) {
			/if (${_type.Equal[FIND]}) {
				/varset _type 8
			} else /if (${_type.Equal[FORCE]}) {
				/varset _type ${buffGem}
			}
		} else /if (${Me.CombatAbilityReady[${Me.CombatAbility[${Spell[${_spell}].RankName}]}]}) {
			/varset _type disc
		} else /if (${Me.ItemReady[${_spell}]}) {
			/varset _type item
		} else {
		|	DEBUG FIND${dep}\arFAIL\ax${dep}${_spell}${dep}\a-wnot found or not ready\az
			/return FALSE
		}
	} 	


	| spell
	/if (!${Select[${_type},alt,item,disc,pulse,epicitem,activedisc]}) {
		|DEBUG ${dep}spell${dep}${_spell}
		/declare _castLoop int local 1
		/varset castReturn CAST_NOTREADY
		/varset castBreak FALSE

		| check any subs? yes.. no.. maybe??
		/if (${SubDefined[${_sub}]}) {
		|	DEBUG ${dep}/call ${_sub}
			/call ${_sub}
			/if (${castBreak}) {
				/varset castReturn CAST_BREAK
				/return CAST_BREAK
			}
		}


		| cast GOM if song proc?
		/if (${_tmpID} != 0 && ${Target.ID} && ${Me.Song[Gift of Mana].ID} && !${Select[${Me.Class.ShortName},CLR]} && ${Spawn[${Target.ID}].Type.NotEqual[pc]}) {
		
			| nuke 1
			/if (${Me.SpellReady[${Spell[${GoMNuke}].RankName}]}) {
				/varset _spell ${GoMNuke}

			| nuke 2
			} else /if (${Me.SpellReady[${Spell[${GoMNuke2}].RankName}]}) {
				/varset _spell ${GoMNuke2}
			}	
		}
				
		| correct the rank
		/varset _spell ${Spell[${_spell}].RankName}

		| mem spell if needed
		/if (!${Me.Gem[${_spell}]}) /call mem_spell FALSE TRUE "${_spell}" ${_type} TRUE
		| ${_type.Equal[${buffGem}]} && 
		| is the spell memed
		/if (${Me.Gem[${_spell}]}) {

			| echos
			|/if (${_tmpID} == 0) {
			|	VSPELL Spell ${sep} ${csp}${_spell}\ax
			|} else /if (${_tmpID} != 0 && ${Target.ID}) {
			|	VSPELL Spell ${sep} ${csp}${_spell}\ax ${sep} [${ctar}${Spawn[ID ${_tmpID}].DisplayName}\ax]
			|}
			|VBC Spell "${_spell}" ${_tmpID} 0 		

			| give this a try
			/while (${_castLoop}) {
			
				/if (${Me.Invis} || ${Select[${Me.Class.ShortName},ROG]}) /return FALSE
			
				| can we say no MQ2Cast ???
				/cast ${Me.Gem[${_spell}]}
	
				| set delays for casting. GTFO out of this as fast as possible
				/delay ${Math.Calc[${Spell[${_spell}].MyCastTime.Float}+5]}s !${Me.Casting.ID}

				| delay for longer casts if there is any, cooldowns or open spell cast windows
				/while (${Me.Casting.ID} || ${Window[CastingWindow].Open} || ${Me.SpellInCooldown}) {
					/delay 3
				}
 				
 				|CHECKINPUTS
 			| /call check_cast_events 1
						
				| good cast
				/if (${Select[${castReturn},CAST_SUCCESS]}) /break
				
				| spell is not ready
				/if (${Select[${castReturn},CAST_NOTREADY]}) {
					/varcalc _castLoop ${_castLoop}-1
					/delay 2
				}

			}

		}
		/return


	| AA
	} else /if (${Select[${_type},alt]}) {
		|DEBUG ${dep}alt${dep}${_spell}
		
		/declare _castLoop int local 1
		/varset castReturn CAST_NOTREADY
		/varset castBreak FALSE
		
		|/if (${Select[${Me.Class.ShortName},BRD]}) {
		|	| /if (${Me.BardSongPlaying}) /call pulse_stop 9
		|	/if (${coreAuto} && (${swCombatMelee} || ${swCombatRange})) {
		|		CHECKFACE ${Target2Kill} FALSE
		|		/call stick_to_target ${Target2Kill}
		|	}
		|}
		
		| delay for aa casting
		/delay ${Math.Calc[${Spell[${_spell}].MyCastTime.Float}+5]}s !${Me.Casting.ID}
		
		| .AltAbility .AltAbilityReady .AltAbilityTimer .AltCurrency .AltTimer .AltTimerReady
		
		| is the spell memed
		/if (${Me.AltAbilityReady[${_spell}]}) {

			| echos
			|/if (${_tmpID} == 0) {
			|	VALT AA ${sep} ${csp}${_spell}\ax
			|} else /if (${_tmpID} != 0 && ${Target.ID}) {
			|	VALT AA ${sep} ${csp}${_spell}\ax ${sep} [${ctar}${Spawn[ID ${_tmpID}].DisplayName}\ax]
			|}
			|VBC Alt "${_spell}" ${_tmpID} 0

			| gonna try this 3 times.
			/while (${_castLoop}) {
			
				/alt act ${Me.AltAbility[${_spell}].ID}
				
				/delay 8
				/delay ${Math.Calc[${Spell[${_spell}].MyCastTime.Float}+5]}s !${Me.Casting.ID}

				| delay for longer casts if there is any, cooldowns or open spell cast windows
				/while (${Me.Casting.ID} || ${Window[CastingWindow].Open}) {
					/delay 3
				}
 				
 				|CHECKINPUTS
				| /call check_cast_events 2
						
				| good cast
				/if (${Select[${castReturn},CAST_SUCCESS]}) /break
				
				| spell is not ready
				/if (${Select[${castReturn},CAST_NOTREADY]}) {
					/varcalc _castLoop ${_castLoop}-1
					/delay 2
				}

			}

		}
		/return		
		
		
	| item
	} else /if (${Select[${_type},item,epicitem]}) {
	|	DEBUG ${dep}item,epicitem${dep}${_spell}
		/declare _castLoop int local 1
		/varset castReturn CAST_NOTREADY

		|/if (${Select[${Me.Class.ShortName},BRD]}) {
		|	| /if (${Me.BardSongPlaying}) /call pulse_stop 9
	||		/if (${coreAuto} && (${swCombatMelee} || ${swCombatRange}) && ${Target2Kill}) {
	||			CHECKFACE ${Target2Kill} FALSE
	|			/call stick_to_target ${Target2Kill}
	|		}
	|	}

		| is the item ready?
		/if (${Me.ItemReady[${_spell}]}) {

			| echos
			|/if (${_tmpID} == 0) {
			|	VITEM Item ${sep} ${citem}${_spell}\ax
			|} else /if (${_tmpID} != 0 && ${Target.ID}) {
			|	VITEM Item ${sep} ${citem}${_spell}\ax ${sep} [${ctar}${Spawn[ID ${_tmpID}].DisplayName}\ax]	
			|}
			|VBC Item "${_spell}" ${_tmpID} 0 		


			| try this 2 times
			/while (${_castLoop}) {
			
				/useitem "${_spell}" 
				/delay 2s ${Me.Casting.ID}
				| /delay 2s !${Me.Casting.ID}
 	
				/while (${Me.Casting.ID} || ${Window[CastingWindow].Open}) {
					/delay 3
				} 	

				/if (${Target2Kill}) {
					/if (${is_target_dead[${Target2Kill}]}) /break
				}
 				
 				|CHECKINPUTS
				| /call check_cast_events 2
						
				/if (${Select[${castReturn},CAST_SUCCESS]}) /break
				
				| spell is not ready
				/if (${Select[${castReturn},CAST_NOTREADY]}) {
					/varcalc _castLoop ${_castLoop}-1
					/delay 2
				}

			}

		}
		/return		
		

		
	| disc
	} else /if (${Select[${_type},disc,activedisc]}) {
		|DEBUG ${dep}disc,activedisc${dep}${_spell}
		/varset _spell ${Spell[${_spell}].RankName}

		|/if (${Select[${Me.Class.ShortName},BRD]}) {
			| /if (${Me.BardSongPlaying}) /call pulse_stop 9
		|	/if (${coreAuto} && (${swCombatMelee} || ${swCombatRange}) && ${Target2Kill}) {
		|		CHECKFACE ${Target2Kill} FALSE
		|		/call stick_to_target ${Target2Kill}
		|	}
		|}

		|/if (${_tmpID} == 0) VDISC Disc ${sep} ${csp}${_spell}\ax
		|/if (${_tmpID} != 0 && ${Target.ID}) VDISC Disc ${sep} ${csp}${_spell}\ax ${sep} [${ctar}${Spawn[ID ${_tmpID}].DisplayName}\ax]
		|VBC Disc "${_spell}" ${_tmpID} 0 
		/disc ${Me.CombatAbility[${Me.CombatAbility[${_spell}]}].ID}
		| /disc ${_spell}
		/delay 5
		/while (${Me.Casting.ID} && ${Window[CastingWindow].Open}) {
			/delay 5
		}	
			


	| bard song	
	} else /if (${Select[${_type},pulse]}) {
	|	DEBUG ${dep}pulse${dep}${_spell}

		/declare _castLoop int local 1
		/varset castReturn CAST_NOTREADY
		/varset _spell ${Spell[${_spell}].RankName}
		
		/if (${Me.BardSongPlaying}) /call pulse_stop core_cast_pulsestop
		|/if (${coreAuto} && (${swCombatMelee} || ${swCombatRange}) && ${Target2Kill}) {
		|	CHECKFACE ${Target2Kill} FALSE
		|	/call stick_to_target ${Target2Kill}
		|}

		| is the gem ready?
		/if (${Me.Gem[${_spell}]}) {

			| echos
			|/if (${_tmpID} == 0) {
			|	VPULSE Pulse ${sep} ${csp}${_spell}\ax
			|} else /if (${_tmpID} != 0 && ${Target.ID}) {
			|	VPULSE Pulse ${sep} ${csp}${_spell}\ax ${sep} [${ctar}${Spawn[ID ${_tmpID}].DisplayName}\ax]
			|}
			|VBC Pulse "${_spell}" ${_tmpID} 0 		

			| gonna try this 2 times.
			/while (${_castLoop}) {
			
				/cast ${Me.Gem[${_spell}]}
				/delay 5 

				| adjust delay for Metronome AA (fuck bards)
				/if (${Me.AltAbility[Metronome]}) {
					/delay ${Spell[${_spell}].CastTime.Seconds}s
				} else {
					/delay ${Math.Calc[${Spell[${_spell}].CastTime.Seconds}+${Math.Calc[${Spell[${_spell}].CastTime.Seconds}*.05]}]}s
				}

				/while (${Window[CastingWindow].Open}) {
					/delay 3
				}
 				
 				|CHECKINPUTS
				| /call check_cast_events 2
						
				/if (${Select[${castReturn},CAST_SUCCESS]}) /break
				
				/if (${Select[${castReturn},CAST_NOTREADY]}) {
				 	/varcalc _castLoop ${_castLoop}-1
				 	/delay 2
				}

			}
			
		}
		/return
	
	}

/return FALSE

|***
 *	DES: Memorize a spell/song
 *	USE: /call mem_spell [DEBUG T/F] [echo memming T/F] ["spell name"] [gem to mem it in] [wait for recycle to cast T/F]
 *	NOTE: 
 ***|
sub mem_spell(bool _debug, bool _echo, string _spellname, string _spellgem, bool _wait)

	/echo attempting to cast ${_spellname}
	
 	/if (${Me.Gem[${Spell[${_spellname}].RankName}]}) /return TRUE
	
	| cant open a book with shit in hands
	/if (${Cursor.ID}) {
		/autoinventory
	}

	| set timer for.. whatever
	/if (${_wait}) {
		/declare _breakTimer timer local 30s
	} else {
		/declare _breakTimer timer local 5s
	}

	| do we even have the spell?
	/echo Do I have the spell ${Me.Book[${Spell[${_spellname}].RankName}]}
	/if (!${Me.Book[${Spell[${_spellname}].RankName}]}) {
		/return FALSE
	}
	
	| just the facts ma'am
	/call fix_gem_id "${_spellgem}"
	/declare _gem int local ${Macro.Return}
	
	/echo Spell gem ${_gem}

	/if (${Me.State.NotEqual[SIT]} && !${Me.Mount.ID}) {
		/sit
		/delay 1s ${Me.State.Equal[SIT]}
	}
	
	| mem the spell
	/memspell ${_gem} "${Spell[${_spellname}].RankName}"
	/delay 5
	/delay 2s ${Me.Gem[${_gem}].Name.Equal[${Spell[${_spellname}].RankName}]}

	/echo what is this ${Me.Gem[${_gem}].Name.Equal[${Spell[${_spellname}].RankName}]}
	

	| wait for spell to be ready
	/while (${_wait}) {
		/if (!${_breakTimer}) /return FALSE
		/if (${Me.SpellReady[${Spell[${_spellname}].RankName}]}) /break
		/delay 2
	}

	/echo Is spell ready ${Me.SpellReady[${Spell[${_spellname}].RankName}]}

	/delay 5
		
/return TRUE

|***
 *	DES: corrects the Gem## to simply a #
 *	USE: /call fix_gem_id [gem##] | ${fix_gem[gem##]}
 *	NOTE:
 ***|
sub fix_gem_id(string _spellGem, bool _debug)
	/declare _gem int local 8

	/if (${_spellGem.Length} == 1 || ${_spellGem.Length} == 4) {
		/varset _gem ${_spellGem.Right[1]}
	} else /if (${_spellGem.Length} == 2 || ${_spellGem.Length} == 5) {
		/varset _gem ${_spellGem.Right[2]} 
	}
| ${_gem}
/return 8

|-------------------------------------------------------------------------------------
|***
 *	DES: Res routines for the healer slobs.
 *	USE: /call check_for_corpse
 *	NOTE: looks for corpses.. rez them
 ***|
 |-------------------------------------------------------------------------------------
sub check_for_corpse(bool _debug)
	/declare _count 						int 		local 0
	/declare _tmpID 						int 		local 0

	/if (${Me.State.Equal[HOVER]} || ${Me.Hovering} || ${Me.Dead}) /return FALSE
	
	| no one dead
	/if (!${SpawnCount[pccorpse radius ${setMaxRezRange}]}) /return FALSE
	
	| no combat rez
	/if (!${rezCombat} && ${SpawnCount[npc radius ${setCombatRadius} playerstate 4]}) /return FALSE

	| not enough manna for AA rez
	/if (${Me.PctMana} < 2 && !${rezToken}) /return FALSE

	| no emergency tokens AND dont use them when a cleric is around
	/if (${rezToken}) {
		/if (!${Me.ItemReady[Token of Resurrection]}) /return FALSE
		/if (${Spawn[pc CLR radius ${setMaxRezRange}].ID}) /return FALSE
	}
		
	| set rez name/type	
	| necro stuff
	/if (${Select[${Me.Class.ShortName},NEC]}) {
		/if (!${FindItem[Essence Emerald].ID}) /return FALSE
		/declare _rezNEC						string	local "Convergence"
	}

	| clerics first group or raid
	/if (${SpawnCount[pccorpse cleric group radius ${setMaxRezRange}]} || ${SpawnCount[pccorpse cleric raid radius ${setMaxRezRange}]}) {

		/for _count 1 to ${SpawnCount[pccorpse group cleric radius ${setMaxRezRange}]}
			/varset _tmpID ${NearestSpawn[${_count},pccorpse group cleric radius ${setMaxRezRange}].ID}
			|/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.AltAbilityReady[${_divinerezCLR}]} && ${DivineRezCleric}) {
			|	/call cast_rez ${_tmpID} ${_divinerezCLR}		
			|} else 
			/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Reviviscence]}) {
				/call cast_rez ${_tmpID} "Reviviscence"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
				/call cast_rez ${_tmpID} "Resurrection"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resuscitate]}) {
				/call cast_rez ${_tmpID} "Resuscitate"		
			} 
			|else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
			|	/call cast_rez ${_tmpID} "Resurrection"		
			|}| else /if (${Select[${Me.Class.ShortName},CLR,DRU,PAL,SHM,NEC]} && ${Me.AltAbilityReady[${_rez${Me.Class.ShortName}}]}) {
			|	/call cast_rez ${_tmpID} ${_rez${Me.Class.ShortName}}
			|} 
		/next _count
	} 
	
	| group members
	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) {
		/for _count 1 to ${SpawnCount[pccorpse group radius ${setMaxRezRange}]}
				/varset _tmpID ${NearestSpawn[${_count},pccorpse group radius ${setMaxRezRange}].ID}
				|/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.AltAbilityReady[${_divinerezCLR}]} && ${DivineRezCleric}) {
				|	/call cast_rez ${_tmpID} ${_divinerezCLR}		
				|} else 
				/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Reviviscence]}) {
					/call cast_rez ${_tmpID} "Reviviscence"		
				} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
					/call cast_rez ${_tmpID} "Resurrection"		
				} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resuscitate]}) {
					/call cast_rez ${_tmpID} "Resuscitate"		
				} 
				|else /if (${Select[${Me.Class.ShortName},CLR,DRU,PAL,SHM,NEC]} && ${Me.AltAbilityReady[${_rez${Me.Class.ShortName}}]}) {
				|	/call cast_rez ${_tmpID} ${_rez${Me.Class.ShortName}}
				|} 
		/next _count
	}		
	
	| tanks

	/if (${Raid.Members}) {
|	/if (${SpawnCount[pccorpse raid tank radius ${setMaxRezRange}]}) {
		/for _count 1 to ${SpawnCount[pccorpse raid radius ${setMaxRezRange} tank]}
			/varset _tmpID ${NearestSpawn[${_count},pccorpse raid radius ${setMaxRezRange} tank].ID}
			|/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.AltAbilityReady[${_divinerezCLR}]} && ${DivineRezCleric}) {
			|	/call cast_rez ${_tmpID} ${_divinerezCLR}		
			|} else 
			/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Reviviscence]}) {
				/call cast_rez ${_tmpID} "Reviviscence"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
				/call cast_rez ${_tmpID} "Resurrection"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resuscitate]}) {
				/call cast_rez ${_tmpID} "Resuscitate"		
			} 
			| else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
			|	/call cast_rez ${_tmpID} "Resurrection"		
			|} |else /if (${Select[${Me.Class.ShortName},CLR,DRU,PAL,SHM,NEC]} && ${Me.AltAbilityReady[${_rez${Me.Class.ShortName}}]}) {
			|	/call cast_rez ${_tmpID} ${_rez${Me.Class.ShortName}}
			|} 
		/next _count
|	}

	| remaining raid members
|	/if (${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}) {
		/for _count 1 to ${SpawnCount[pccorpse raid radius ${setMaxRezRange}]}
		
			/varset _tmpID ${NearestSpawn[${_count},pccorpse raid radius ${setMaxRezRange}].ID}
			|/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.AltAbilityReady[${_divinerezCLR}]} && ${DivineRezCleric}) {
			|	/call cast_rez ${_tmpID} ${_divinerezCLR}		
			|} else 
			/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Reviviscence]}) {
				/call cast_rez ${_tmpID} "Reviviscence"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
				/call cast_rez ${_tmpID} "Resurrection"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resuscitate]}) {
				/call cast_rez ${_tmpID} "Resuscitate"		
			} 
			|else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
			|	/call cast_rez ${_tmpID} "Resurrection"		
			|} |else /if (${Select[${Me.Class.ShortName},CLR,DRU,PAL,SHM,NEC]} && ${Me.AltAbilityReady[${_rez${Me.Class.ShortName}}]}) {
			|	/call cast_rez ${_tmpID} ${_rez${Me.Class.ShortName}}
			|} 
		/next _count
|	} 
	}
	/for _count 1 to ${SpawnCount[pccorpse radius 20]}
			/varset _tmpID ${NearestSpawn[${_count},pccorpse radius 20].ID}
			|/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.AltAbilityReady[${_divinerezCLR}]} && ${DivineRezCleric}) {
			|	/call cast_rez ${_tmpID} ${_divinerezCLR}		
			|} else 
			/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Reviviscence]}) {
				/call cast_rez ${_tmpID} "Reviviscence"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
				/call cast_rez ${_tmpID} "Resurrection"		
			} else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resuscitate]}) {
				/call cast_rez ${_tmpID} "Resuscitate"		
			} 
			| else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
			|	/call cast_rez ${_tmpID} "Resurrection"		
			|} |else /if (${Select[${Me.Class.ShortName},CLR,DRU,PAL,SHM,NEC]} && ${Me.AltAbilityReady[${_rez${Me.Class.ShortName}}]}) {
			|	/call cast_rez ${_tmpID} ${_rez${Me.Class.ShortName}}
			|} 
		/next _count
/return

|-------------------------------------------------------------------------------------
|***
 *	DES: rez/call casting code.
 *	USE: /call cast_rez [ID] [rez aa|token]
 *	NOTE: 
 ***|
 |-------------------------------------------------------------------------------------
sub cast_rez(int _tmpID, string _rez, bool _debug)
	/if (${Me.Dead}) /return FALSE

	| ignore the people we dont like
	|/if (${lstNoRez.Find[${Spawn[pccorpse ${_tmpID}].DisplayName}]}) {
	|	/call timer_update timer_corpse_${_tmpID}} 30m
	|	/return FALSE
	|}
		
	| get the corpse close to us
	/if (${Spawn[pccorpse ${_tmpID}].Distance} > ${AssistRange} && ${Spawn[pccorpse ${_tmpID}].Distance} <= ${setMaxRezRange}) {
		/squelch /corpse
	}

	| can we AA res or token, maybe spell?
	/if (${Me.AltAbilityReady[${_rez}]} || (${Me.ItemReady[Token of Resurrection]} && ${rezToken}) || ${Me.SpellReady[${_rez}]}) {	

		| res the damn person
		
		| AA rez
		/if (!${rezToken}) {
			| /if (!${Spawn[pccorpse ${_tmpID}].ID}) /return
			/delay 5s !${Me.Casting.ID}
			/squelch /target ID ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}
			/if (${validate_cast[FALSE, FIND, "${_rez}", ${Me.ID}]}) /call core_cast2 "${_rez}" FIND ${_tmpID} FALSE

		| token rez
		} else /if (${rezToken}) {
			/delay 5s !${Me.Casting.ID}
			/squelch /target ID ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}
			/if (${validate_cast[FALSE, item, "Token of Resurrection", ${Me.ID}]}) /call core_cast2 "Token of Resurrection" item ${_tmpID} FALSE
		}
	
		| if cast was good, set the timers.
		|/if (${Select[${castReturn},CAST_SUCCESS]}) { 
		|	/call timer_update timer_corpse_${_tmpID} ${tRez_Retry}
		|	ECHOCHANNEL ${Me.Class.ShortName} Rez: ${Spawn[${_tmpID}].DisplayName}
		|} else {
		|	/if (${Select[${Me.Class.ShortName},CLR]}) {
		|		/call timer_update timer_corpse_${_tmpID} 30s
		|	} else /if (${Select[${Me.Class.ShortName},DRU,SHM,PAL]}) {
		|		/call timer_update timer_corpse_${_tmpID} 45s
		|	} else {
		|		/call timer_update timer_corpse_${_tmpID} 1m
		|	}
		|}
		
	}

/return
|***
 *	DES: check  health
 *	USE: /call check_hurt [DEBUG T/F] [group|pet|xtarget|self|mypet]} || ${check_hurt[DEBUG, group|pet|xtarget|self|mypet]}
 *	NOTE: shared by PAL,DRU,CLR,SHM this returns the # of "hurt" for the group check you request as the pass/fail marker
 ***|
sub check_hurt(bool _debug, string _type)

	/declare _count int local 0
	/varset hurtID ${Me.ID}
	/varset hurtPctHP 100
	| /varset hurtPctHP ${If[${setHealOverride},${Float[${setHealOverride}].Centi},99.99]}
	/varset hurtCLS ${Me.Class.ShortName}
	/varset hurtCount 0
	/declare _hurtWeight float local 0
	/declare _tmpWeight float local 0

	| check group hurt
	/if (${_type.Equal[group]}) {
		/for _count 0 to ${Group}
			|/if (${Group.Member[${_count}].PctHPs} > ${${Group.Member[${_count}].Class.ShortName}Point}*.${tmpHealOverride}) /continue
			| /if (${Group.Member[${_count}].PctHPs} > ${hurtPctHP}) /continue
			|/if (${Group.Member[${_count}].Distance} > ${setMobAgro}) /continue
			/if (!${Group.Member[${_count}].Present} || ${Group.Member[${_count}].Dead}) /continue
			|/if (${Group.Member[${_count}].DisplayName.Equal[${RampageTank}]}) /continue
			|/if (${lstNoHeal.Find[${Group.Member[${_count}].DisplayName}]}) /continue
			/varcalc _tmpWeight (${Group.Member[${_count}].PctHPs} / ${${Group.Member[${_count}].Class.ShortName}Point}) + .${${Group.Member[${_count}].Class.ShortName}Point}

			/if (${_tmpWeight} > ${_hurtWeight}) { 
				/varcalc _hurtWeight ${_tmpWeight}
				/varset hurtPctHP ${Group.Member[${_count}].PctHPs}
				/varset hurtID ${Group.Member[${_count}].ID}
				/varset hurtCLS ${Group.Member[${_count}].Class.ShortName}
				/varcalc hurtCount ${hurtCount}+1
				/if (${useGroupHeal} && ${hurtCount} >= ${useGroupHeal}) {
					/break
				}
			}
		
		/next _count
		/return ${hurtCount}

	| check xtarget hurt
	} else /if (${_type.Equal[xtarget]}) {
		/for _count 1 to ${Me.XTargetSlots}
	  	/if (!${Me.XTarget[${_count}].ID}) /continue
	  	/if (${Me.XTarget[${_count}].Dead}) /continue
	  	/if (${Me.XTarget[${_count}].PctHPs} > ${hurtPctHP}) /continue
	  	/if (${Me.XTarget[${_count}].Distance} > ${setMobAgro}) /continue
			/if (${Me.XTarget[${_count}].DisplayName.Equal[${RampageTank}]}) /continue
			/if (${lstNoHeal.Find[${Me.XTarget[${_count}].DisplayName}]}) /continue
	  	/if (!${Me.XTarget[${_count}].Type.Equal[PC]} && !${ProtectNPCList.Find[${Me.XTarget[${_count}].DisplayName}]}) /continue
			/if (${Me.XTarget[${_count}].PctHPs} > ${${Me.XTarget[${_count}].Class.ShortName}Point}*.${tmpHealOverride}) /continue

			/varset hurtID ${Me.XTarget[${_count}].ID}
			/varset hurtPctHP ${Me.XTarget[${_count}].PctHPs}
			/varset hurtCLS ${Me.XTarget[${_count}].Class.ShortName}
			/varcalc hurtCount ${hurtCount}+1

	  /next _count
	  /return ${hurtCount}
	  
	  
	| check pet hurt
	} else /if (${_type.Equal[pet]}) {
		/for _count 0 to ${Group}
			/if (!${Group.Member[${_count}].Pet.ID}) /continue
	    /if (${Group.Member[${_count}].Pet.PctHPs} >= ${PetPoint}) /continue
	    /if (${Group.Member[${_count}].Pet.Distance} > ${setMobAgro}) /continue
	    /if (${Group.Member[${_count}].Pet.PctHPs} >= ${hurtPctHP}) /continue

			/varset hurtCount 1
			/varset hurtID ${Group.Member[${_count}].Pet.ID}
			/varset hurtPctHP ${Group.Member[${_count}].Pet.PctHPs}
			/varset hurtCLS Pet
	  /next _count
	  /return ${hurtCount}
	  

	| self only pet hurt
	} else /if (${_type.Equal[mypet]}) {
		/if (!${Me.Pet.ID}) /return FALSE
    /if (${Me.Pet.PctHPs} >= ${PetPoint}) /return FALSE
    /if (${Me.Pet.Distance} > ${setMobAgro}) /return FALSE

		/varset hurtID ${Me.Pet.ID}
		/varset hurtPctHP ${Me.Pet.PctHPs}
		/varset hurtCLS Pet
	  /if (${hurtPctHP} >= ${${hurtCLS}Point}*.${tmpHealOverride}) /return FALSE
		/varset hurtCount 1
		/return ${hurtCount}


	| set self hurt
	} else /if (${_type.Equal[self]}) {
		/varset hurtID ${Me.ID}
		/varset hurtPctHP ${Me.PctHPs}
		/varset hurtCLS ${Me.Class.ShortName}

		/if (${hurtPctHP} >= ${${hurtCLS}Point}*.${tmpHealOverride}) /return FALSE
		/varset hurtCount 1
		/return ${hurtCount}
	  
	}

/return FALSE
|-------------------------------------------------------------------------------------
|- SUB: BegForCure
|-------------------------------------------------------------------------------------
Sub BegForCure
	/varset BegTimer 10s
	/if (${DanNet.Peers.Find[${EverQuest.Server.Lower}_${Group.Cleric.Name.Lower}]}) {
		/call Gquery ${EverQuest.Server.Lower}_${Group.Cleric.Name.Lower} "Me.AltAbilityReady[Radiant Cure]" "tmpRCready" "bool"
		/call Gquery ${EverQuest.Server.Lower}_${Group.Cleric.Name.Lower} "Me.AltAbilityReady[Group Purify Soul]" "tmpGPSready" "bool"
		/call Gquery ${EverQuest.Server.Lower}_${Group.Cleric.Name.Lower} "Me.AltAbilityReady[Purify Soul]" "tmpPSready" "bool"
		/call Gquery ${EverQuest.Server.Lower}_${Group.Cleric.Name.Lower} "Macro.Name" "tmpMacName" "string"
		/if (${tmpMacName.Find[IHC]} && (${tmpPSready} || ${tmpRCready} || ${tmpGPSready})) { 
			/squelch /dex ${Group.Cleric.Name.Lower} /curegroup ${Me.ID}
			/delay 5
			/return
		}
	}
	/if (${DanNet.Peers.Find[${EverQuest.Server.Lower}_${Spawn[group shaman].Name.Lower}]}) {
		/call Gquery ${EverQuest.Server.Lower}_${Spawn[group shaman].Name.Lower} "Me.AltAbilityReady[Radiant Cure]" "tmpRCready" "bool"
		/call Gquery ${EverQuest.Server.Lower}_${Spawn[group shaman].Name.Lower} "Macro.Name" "tmpMacName" "string"
		/if (${tmpMacName.Find[IHC]}) {
			/call Gquery ${EverQuest.Server.Lower}_${Spawn[group shaman].Name.Lower} "CureSpell" "tmpCureSpellName" "string"
			/call Gquery ${EverQuest.Server.Lower}_${Spawn[group shaman].Name.Lower} "Me.SpellReady[${tmpCureSpellName}]" "tmpCureSpellReady" "bool"
			/if (${tmpRCready} || ${tmpCureSpellReady}) {
				/squelch /dex ${Spawn[group shaman].Name.Lower} /curesingle ${Me.ID}
				/delay 5
				/return
			}
		}
	}
	/if (${Defined[tmpRCready]}) /deletevar tmpRCready
	/if (${Defined[tmpGPSready]}) /deletevar tmpGPSready
	/if (${Defined[tmpPSready]}) /deletevar tmpPSready
	/if (${Defined[tmpMacName]}) /deletevar tmpMacName
	/if (${Defined[tmpCureSpellName]}) /deletevar tmpCureSpellName
	/if (${Defined[tmpCureSpellReady]}) /deletevar tmpCureSpellReady
	/delay 5
/return
|-------------------------------------------------------------------------------------
|- SUB: BIND KillMATarget
|-------------------------------------------------------------------------------------
Sub Bind_KillMATarget
	/call KillTarget
/return
|-------------------------------------------------------------------------------------
|- SUB: BIND SetAutoTargetID
|-------------------------------------------------------------------------------------
Sub Bind_SetAutoTargetID
	/varset autotargetid ${Target.ID}
/return
|-------------------------------------------------------------------------------------
|- SUB: BIND QuestSay
|-------------------------------------------------------------------------------------
Sub Bind_QuestSay(string QSayText)
	/squelch /mgax /target id ${Target.ID}
	/delay 5
	/squelch /mgax /say ${QSayText}
	/delay 5
/return
|-------------------------------------------------------------------------------------
|- SUB: BIND ChaseMe
|-------------------------------------------------------------------------------------
Sub Bind_ChaseMe
    /squelch /mgx /chase on ${Me.CleanName}
/return
|-------------------------------------------------------------------------------------
|- SUB: Help Common - 
|-------------------------------------------------------------------------------------
Sub CommonHelp
/echo \ag===General Commands=== 
/echo \ag/assistrange\aw - How far away the target can be to Attack
/echo \ag/autoassistat\aw - Sets Mob HP% to start attacking at - ex: /autoassistat 98
/echo \ag/backoff\aw - Backoff and stop combat
/echo \ag/burn\aw - Triggered On Demand Buring
/echo \ag/burncount\aw - Sets the number of targets to Start auto burn - ex: /burncount 3 
/echo \ag/campexact\aw - toggles always returning to /camphere /loc x y after combat otherwise you must be outside /campradius before a return happens
/echo \ag/campfire\aw - Sets/Unsets a fellowship campfire
/echo \ag/camphere\aw - Sets a camp at the current /loc x y
/echo \ag/campoff\aw - Unsets the saved x y /loc
/echo \ag/campradius\aw - Radius around /camphere loc considered "in camp"
/echo \ag/chase\aw - toggle follow the main assist on/off
/echo \ag/chaseoff\aw - stop following the main assist
/echo \ag/chaseon\aw - start following the main assist
/echo \ag/endmedpct\aw - % Endurance to start medding at /tglmed must be On to start medding
/echo \ag/ralleybehind\aw - All chars running IHC mac's will rally around the rear of the char that uses this command 
/echo \ag/ralleyfront\aw - All chars running IHC mac's will rally around the front of the char that uses this command
/echo \ag/ihchelp\aw - List of available commands
/echo \ag/instantrelease\aw - toggle instant respawn on death
/echo \ag/medpct\aw - % Mana to start medding at /tglmed must be On to start medding
/echo \ag/meleeoff\aw - Turn melee combat off
/echo \ag/meleeon\aw - Turn melee combat on
/echo \ag/returntocamp\aw - toggle returning to /loc x y  set with /camphere if outside of camp radius OR always if /campexact is on
/echo \ag/smartassist\aw - toggles waiting till a mob is in melee range of the MA before engaging even if below assist % on incoming
/echo \ag/tglburn\aw - Burn all the time as spells/abilities become available
/echo \ag/tglmed\aw - Toggle automatic medding, med % can be set in your ini file or with /medpct #
/echo \ag/usefellowship\aw - use fellowship insignia if a campfire is set
/return 