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
	/squelch /alias /camphere       /togglevariable ReturnToCamp 1
	/squelch /alias /campoff	    /togglevariable ReturnToCamp 0
	/squelch /alias /campradius     /changevarint General CampRadius
	/squelch /alias /chase          /togglevariable ChaseAssist
	/squelch /alias /chaseoff       /changevarint General ChaseAssist 0        
	/squelch /alias /chaseon        /changevarint General ChaseAssist 1 
	/noparse /alias /instantrelease /togglevariable InstantRelease
	/squelch /alias /meleeon        /togglevariable MeleeOn 1
	/squelch /alias /meleeoff       /togglevariable MeleeOn 0
	/squelch /alias /returntocamp   /togglevariable ReturnToCamp
	/squelch /alias /usefellowship 	/togglevariable UseFellowship
	|- IHC Mac common commands
	/alias /ihcstart /macro IHCMercs\IHC${Me.Class.ShortName}.mac
	/alias /ihcgroup /multiline ; /docommand /dgaex group_${EverQuest.Server}_${Group.Leader} /target ${Me.CleanName} ; /docommand /timed 10 /dgaex group_${EverQuest.Server}_${Group.Leader} /ihcstart
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

|- AFK camping
    /declare AggressiveRadius 	int outer 100
	/declare AssistRangeZ 		int outer 20
    /declare PullAbility		string outer NULL
	/declare PullAbilityAA 		int outer 0
    /declare PullAbility2 		int outer 0
	/declare PullAutoCampX		int outer 0
    /declare PullAutoCampY		int outer 0
	/declare PullAutoCampZ		int outer 0
	/declare PullDistance 		int outer 0
	/declare ResourceChecker 	int outer 1

|- Modes
	/declare Mode 				int outer 0
	/declare PreviousMode 		int outer 0
	/declare ModeName 			string outer NULL
	/declare PreviousModeName 	string outer NULL
	

	/echo -----${MacroName} LOADING------
	/if (${Me.XTarget[1].TargetType.NotEqual[Auto Hater]}) {
		/echo Extended Target 1 HAS TO BE SET TO Auto Hater
		/xtarget set 1 Autohater
		/echo Set Extended Target 1 to Auto
	  }
	|-Check for loaded plugins
	/call CheckPlugin MQ2Cast
    /call CheckPlugin MQ2Exchange
	/call CheckPlugin MQ2Rez
	/call CheckPlugin MQ2AdvPath
	/call CheckPlugin MQ2MoveUtils
	/call CheckPlugin MQ2DanNet
	/call CheckPlugin MQ2Nav
	/call UnCheckPlugin MQ2Twist
	/squelch /rez accept on
    /squelch /rez loot off
	/squelch /rez pct 90
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
Sub IllusionCheck
	/varset IllusionNum ${Math.Rand[10]}
	/if (!${Me.Buff[Illusion: Plaguebringer].ID} && !${Me.Buff[Illusion: Frost Bone].ID} && !${Me.Buff[Night's Terror].ID} && !${Me.Buff[Illusion: Bear].ID} && (${FindItem[=Polymorph Wand: Plaguebringer].ID} || ${FindItem[=Bone Mask of Horror].ID}) && !${Me.Casting.ID}) {
		/if (${Me.Sitting}) /stand
		/if (${IllusionNum}<1) {
			/cast item "Polymorph Wand: Plaguebringer"
			/delay 10
		} else {
			/cast item "Bone Mask of Horror"
		}
	}
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
|--------------------------------------------------------------------
|- SUB: Bind Change Var Int resets various interger settings from ini file
|- Removed mez and slow toggles. Class specific abilities will be handled in the class specific mac's
|----------------------------------------------------------------------------
Sub Bind_ChangeVarInt(string ISection, string IName, int IVar)
	/docommand /varset changetoini 1
	|-ChaseAssist Var Set
    /if (${IName.Equal[ChaseAssist]} && ${IVar}==1 && ${Target.Type.Equal[PC]}) {
		/docommand /varset FollowToonName ${Target.Name}
		/echo \aw Following ${If[${FollowToonName.Equal[NULL ]},\ar OFF,\ag ${FollowToonName}]}
	} else /if (${IName.Equal[ChaseAssist]} && ${IVar}==0) {
		/varset FollowToonName NULL
		/echo \aw Following \ar OFF
		/if (${AdvPath.Following}) /docommand /afollow off
	} else /if (${IName.Equal[CampRadius]} && ${IVar}>=20 && ${IVar}<=100) {
		/varset AutoCampRadius ${IVar}
		/echo \aw Camp Radius set to \ag ${IVar}
	} else /if (${IName.Equal[CampRadius]} && ${IVar}<20 && ${IVar}>100) {
		/echo \ar Invalid \aw Camp Radius - Set between 20-100 units
	} else /if (${IName.Equal[BurnMobCount]}) {
		/if (${IVar}>=2 && ${IVar}<=100) {
			/varset BurnMobCount ${IVar}
			/echo \aw ${IName} set to \ag ${IVar}
		} else {
			/beep
			/echo \ar Invalid \aw ${IName} - Set between 2-100 mobs
		}
	} else /if (${IName.Equal[AutoAssistAt]}) {
		/if (${IVar}>=10 && ${IVar}<=100) {
			/varset AutoAssistAt ${IVar}
			/echo \aw ${IName} set to \ag ${IVar}
		} else {
			/beep
			/echo \ar Invalid \ag ${IName} \aw HP%- Set between 10-100
		}
	} else /if (${IName.Equal[AssistRange]}) {
		/if (${IVar}>=20 && ${IVar}<=200) {
			/varset AssistRange ${IVar}
			/echo \aw ${IName} set to \ag ${IVar}
		} else {
			/beep
			/echo \ar Invalid \ag ${IName} \aw - Set between 20-200 units
		}
	} else /if (${Select[${IName},MedPct,EndMedPct]}) {
		/if (${IVar}>=0 && ${IVar}<100) {
			/varset ${IName} ${IVar}
			/echo \aw ${IName} set to \ag ${IVar}
		} else {
			/beep
			/echo \ar Invalid \ag ${IName}% \aw - Set between 0-100
		}
	}
/return
|----------------------------------------------------------------------------
|- SUB: PullAbilitySetup
|----------------------------------------------------------------------------
Sub PullAbilitySetup
	/if (${Me.Class.ShortName.Find[MNK]}) /varset PullAbility 376
	/if (${Me.Class.ShortName.Find[WAR]}) /varset PullAbility ${insult}
	/if (${FindItem[Staff of Viral Flux]}) /varset PullAbility2 ${FindItem[Staff of Viral Flux]}
	/if (${Me.Class.ShortName.Find[MNK]}) /varset PullDistance 190
	/if (${Me.Class.ShortName.Find[WAR]}) /varset PullDistance 90
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
	/delay 5
	/varset PullAutoCampY ${Me.Y}
	/varset PullAutoCampX ${Me.X}
	/varset PullAutoCampZ ${Me.Z}
	/delay 5
	/if (${Navigation.Active}) /nav stop
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
	/if (${AdvPath.Following}) /afollow off
	/if (${Target.ID}) /face fast
	/delay 2
	/stick ${StickHow} 11
	/delay 10 ${Stick.Active}
	/squelch /attack on
	/delay 2
/return
|----------------------------------------------------------------------------
|- SUB: CastersEngage
|---------------------------------------------------------------------------- 
Sub CastersEngage
	/if (${AdvPath.Following}) /afollow off
	/if (${Me.Class.ShortName.Find[CLR]}) /target id ${Group.MainTank.ID}
	/if (${Me.Class.ShortName.Find[SHM]} || ${Me.Class.ShortName.Find[ENC]}) /assist ${Group.MainAssist.Name}
	/if (${Target.ID}) /face fast
/return
|----------------------------------------------------------------------------
|- SUB: PostCombat
|---------------------------------------------------------------------------- 
Sub PostCombat
	/if (${Stick.Status.Equal[ON]}) /stick off
	/varset State 0
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
	/if (${Navigation.MeshLoaded} && ${Group.Leader.ID}!=${Me.ID}) {
		/target id ${Group.Leader.ID}
		/delay 5s ${Target.ID}==${Group.Leader.ID}
		/if (!${Navigation.Active} && ${Target.Distance}>10) /nav id ${Target.ID}
		/if (${Navigation.Active} && ${Target.Distance}<10) /nav stop
	}
	/if (${Me.Pet.ID} && ${Me.Combat}) /pet back off
	/if (!${Me.Invis} && !${Me.Buff[Communion of the Cheetah].ID} && ${Me.AltAbilityReady[Communion of the Cheetah]}) {
		/call AANow ${Me.AltAbility[Communion of the Cheetah].ID} ${Me.ID}
		/delay 1
	}
/return
|----------------------------------------------------------------------------
|- SUB: PullerCheckGroupManaEnd
|---------------------------------------------------------------------------- 
Sub PullerCheckGroupManaEnd
	/declare bmember	int local 0
	/varset ResourceChecker 1
	/for bmember 0 to ${Group}
		/if (${Group.Member[${bmember}].Distance}<100 && !${Group.Member[${bmember}].OtherZone} && !${Me.Moving}) {
			/if (${Select[${Group.Member[${bmember}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${bmember}].Name.Lower} "Me.PctMana" "ManaPct" "int"
				/if (${ManaPct}<20) {
					/varset ResourceChecker 0 
					/delay 5
				}
			}
			/if (${ResourceChecker}==0) /return
			/if (${Select[${Group.Member[${bmember}].Class.ShortName},WAR,ROG,BER,MNK]}) {
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${bmember}].Name.Lower} "Me.PctEndurance" "EndPct" "int"
				/if (${EndPct}<20) {
					/varset ResourceChecker 0
					/delay 5
				}
			}
			/if (${ResourceChecker}==0) /return
		}
	/next bmember
/return
|----------------------------------------------------------------------------
|- SUB: AFKPull
|---------------------------------------------------------------------------- 
Sub AFKPull
	/if (${ResourceChecker}==0) /return
	/if (${AdvPath.Following}) /afollow off
	/if (${NearestSpawn[npc radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}) /target id ${NearestSpawn[npc radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}
	/delay 5s ${NearestSpawn[npc radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}==${Target.ID}
	/if (${Mode}!=3) {
		/if (${Navigation.Active}) /nav stop
		/return
	}
	/if (${Target.ID}==${Me.ID} || !${Target.ID}) /return

|-	/if (!${Navigation.PathExists[id ${Target.ID}]}) {
|-		/if (${NearestSpawn[next npc radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}) /target id ${NearestSpawn[next npc radius ${AggressiveRadius} zradius ${AssistRangeZ}].ID}
|-	}

	
    /if (${Target.ID} && ${Navigation.MeshLoaded} && (${Target.Distance}>${PullDistance} || !${Spawn[id ${Target.ID} los].ID})) /nav id ${Target.ID}

	/while (${Navigation.Active}) {
		/delay 1s ${Target.Distance}<=${PullDistance}
		/if (${Navigation.Active} && ${Target.Distance}<=${PullDistance} && ${Spawn[id ${Target.ID} los].ID}) /nav stop
    }

	/delay 5
    /while (${Target.PctAggro}<=0 || ${Target.Distance}>=${PullDistance}) {
		/docommand /dgt \ag Pulling
		/if (${Me.CombatAbilityReady[${PullAbility}]}) /disc ${PullAbility}
		/if (${Me.AltAbilityReady[Distant Strike]}) /alt act 376
		/if (${Mode}!=3) {
			/if (${Navigation.Active}) /nav stop
			/return
		}
		/if (${Target.Distance}>${PullDistance} && ${Me.XTarget[1].ID}) /break
		/delay 5
	}
    /nav locxyz ${PullAutoCampX} ${PullAutoCampY} ${PullAutoCampZ}
	/delay 30s ${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${PullAutoCampY},${PullAutoCampX},${PullAutoCampZ}]}<15
    /if (${Target.ID}) /face fast
 /return
|----------------------------------------------------------------------------
|- SUB: MoveToCamp
|---------------------------------------------------------------------------- 
Sub MoveToCamp(int Xloc, int Yloc, int Zloc, int Distance)
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
|-------------------------------------------------------------------------------------
|- SUB: Bind_ToggleVariable  Check whenever the player is changing any variable via /echo
|-------------------------------------------------------------------------------------
Sub Bind_ToggleVariable(string Command, string Command2, string Command3)
    /declare i int local
	/declare OnOff local
    |- Toggle Variables & Set Variables
    /if (${Defined[${Command}]}) {
        /if (${Command2.Length} && ${Command2.NotEqual[null]}) {
            /if (${Select[${Command2},0,off]}) {
                /varset ${Command} 0
                /varset OnOff Off
				/echo \aw Resetting ${Command} to \ar OFF
            } else /if (${Select[${Command2},1,on]}) {
                /varset ${Command} 1
                /varset OnOff On
				/echo \aw Setting ${Command} to \ag ON
            } 
        } else /if (${${Command}}) {
			/varset ${Command} 0
            /varset OnOff Off
			/echo \aw Resetting ${Command} to \ar OFF
			/if (${Command.Equal[AutoCampHold]}) /moveto dist 10
		} else {
            /varset ${Command} 1
            /varset OnOff On
			/if (${Command.Equal[BurnNow]}) {
				/echo \ag BURNING NOW
			} else {
				/echo \aw Setting ${Command} to \ag ON
			}
			/if (${Command.Equal[AutoCampHold]}) /moveto dist 2
        }
		/docommand /varset changetoini 1
		/if (${Command.Equal[GroupPauseFlag]}) /docommand /mgx /mqp
		/if (${Command.Equal[GroupBackOffFlag]}) /docommand /mgx /backoff
		|-Camp Toggle
        /if (${Command.Equal[ReturnToCamp]} && ${OnOff.Equal[on]} ) {
			/echo \aw Camp turned \ag ON
			/docommand /varset ReturnToCamp 1
			/docommand /varset AutoCampX ${Me.X}
			/docommand /varset AutoCampY ${Me.Y}
			/if (${AutoCampHold}) {
				/moveto dist 2
			}
        } else /if (${Command.Equal[ReturnToCamp]} && ${OnOff.Equal[off]}) {
            /echo \aw Turning ALL Camp settings to \ar OFF
			/docommand /varset ReturnToCamp 0
			/moveto dist 10
        }
		|-Chase Toon Toggle
		/if (${Command.Equal[ChaseAssist]} && ${OnOff.Equal[on]} && ${Command3.NotEqual[null]} && ${Command3.Length}>0 && ${FollowToonName.NotEqual[${Command3}]}) {
			/docommand /varset FollowToonName ${Command3}
			/echo \aw Following ${If[${FollowToonName.Equal[NULL ]},\ar OFF,\ag ${FollowToonName}]}
		} else /if (${Command.Equal[ChaseAssist]} && ${OnOff.Equal[on]} && ${Target.Type.Equal[PC]}) {
			/docommand /varset FollowToonName ${Target.Name}
			/echo \aw Following ${If[${FollowToonName.Equal[NULL ]},\ar OFF,\ag ${FollowToonName}]}
		} else /if (${Command.Equal[ChaseAssist]} && ${OnOff.Equal[off]}) {
			/varset FollowToonName NULL
			/echo \aw Following \ar OFF
			/if (${AdvPath.Following}) /docommand /afollow off
		}
		|-Melee Toggle
		/if (${Command.Equal[MeleeOn]} && ${OnOff.Equal[on]} ) {
			/varset UseMelee 1
		} else /if (${Command.Equal[MeleeOn]} && ${OnOff.Equal[off]}) {
			/varset UseMelee 0
		}
		|-InstantRelease on Death
		/if (${Command.Equal[InstantRelease]} && ${OnOff.Equal[on]} ) {
			/varset InstantRelease 1
		} else /if (${Command.Equal[InstantRelease]} && ${OnOff.Equal[off]}) {
			/varset InstantRelease 0
		}
        |-Use Fellowship to port back on death
		/if (${Command.Equal[UseFellowship]} && ${OnOff.Equal[on]} ) {
			/varset UseFellowship 1
		} else /if (${Command.Equal[UseFellowship]} && ${OnOff.Equal[off]}) {
			/varset UseFellowship 0
		}
    }
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
	/if (${Bool[${FollowToonName}]}) /delay 1m ${Spawn[${FollowToonName}].ID}
	/delay 50
	/if (${ReturnToCamp}!=0) /varset ReturnToCamp 0
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
	/if ((${Cursor.ID}) && ${CursorTimer}==0 && ${ShitOnCursor.Equal[NULL]} && (${Me.FreeInventory}>1)) {
		/varset ShitOnCursor ${Cursor}
		/varset CursorTimer 1m
	} else /if (${Cursor.ID} && ${CursorTimer}==0 && ${ShitOnCursor.NotEqual[NULL]} && (${Me.FreeInventory}>1)) {
		/echo \aw Something has been left on cursor for over a minute Bagging it
		/autoinventory
		/varset ShitOnCursor NULL
	} else /if (${Cursor.ID} && ${ShitOnCursor.Find[Transvergence]} && (${Me.FreeInventory}>1)) {
		/echo \aw Bagging Mod Rod
		/autoinventory
		/varset ShitOnCursor NULL
	} else /if (${Cursor.ID} && ${ShitOnCursor.Find[Modulation]} && (${Me.FreeInventory}>1)) {
		/echo \aw Bagging Mod Rod
		/autoinventory
		/varset ShitOnCursor NULL
	}
/return
|----------------------------------------------------------------------------
|- SUB: Event Gain Something - DanNet message 
|----------------------------------------------------------------------------    
Sub Event_GainSomething(string Line,string text)
    /if (${Line.Find["ABILITY POINT!"]}) {
        /docommand /dgt \aw ${Me.Name} gained an AA, now has ${Me.AAPoints} unspent \ax
    } else /if (${Line.Find[LEVEL]}) {
        /docommand /dgt \aw ${Me.Name} gained a level, now is Level ${Me.Level} \ax
	}
/return 
|----------------------------------------------------------------------------
|- SUB: Event Task Update - DanNet message 
|----------------------------------------------------------------------------    
Sub Event_TaskUpdate(string Line,string name) 
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
	/if (${Me.Standing} && !${Me.Moving} && ${Stick.Status.Equal[OFF]} && !${Me.XTarget[1].ID} && !${MoveTo.Moving} && !${AdvPath.Following} && ${Me.CombatState.NotEqual[COMBAT]} && ${Me.CombatState.NotEqual[DEBUFFED]} && ${enablesit}==0 && ((${Me.PctMana}<=${MedPct} && ${Me.MaxMana}>1000) || (${Me.PctEndurance}<=${EndMedPct} && ${Me.MaxEndurance}>1000))) {
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
	/if (${acverbose}!=0) /echo \aw Casting \ag ${nextdisc}
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
	/if (${acverbose}!=0) /docommand /dgt Casting \ao =>> \ag ${Me.AltAbility[${nextaa}].Name} \ao <<= \ax
/return
|----------------------------------------------------------------------------
|- SUB: AbilityNow
|---------------------------------------------------------------------------- 
Sub AbilityNow(string nextability)
	/squelch /doability ${nextability}
	/delay 8 !${Me.AbilityReady[${nextability}]}
	/if (${acverbose}!=0) /echo \aw Casting \ag ${nextability}
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
	/if (${acverbose}!=0) /echo \aw Using Item \ag ${nextitem}
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
|----------------------------------------------------------------------------
|- SUB: Melee Engage Target - Need a StickHow variable in the mac. Ini option for melee just a declared variable set to null for classes that wont enageg in melee
|- Basic use will check the that the target is in assist range, stick and when in melee range start attacking ( reduces too far away and can not see messages )
|- Advanced use ( smart assist ) will check that the target is range of the MA before engaging....keeps melee from charging out after a mob on incoming
|- For classes that have a before combat move, it is recommended  to copy/paste this sub into new macro and rename. Add opening move ( ber, rog ) to just before turning on attack 
|---------------------------------------------------------------------------- 
Sub EngageTarget
	/declare OKRadCal int local 0
	/if (${Me.State.Equal[FEIGN]}) /stand
	|- If not the MA check that the mob is in range of the MA and not just  in assist range before engaging 
	/if (${UseSmartAssist}) {
		/varset OKRadCal ${Spawn[${SpawnSearchType} id ${autotargetid}].MaxRangeTo}
		/if (${Target.ID}==${autotargetid} && ${assistid}!=${Me.ID} && ${Spawn[${assistid}].ID} && ${Spawn[${SpawnSearchType} id ${autotargetid} loc ${Spawn[id ${assistid}].X} ${Spawn[id ${assistid}].Y} radius ${OKRadCal}].ID}) {
			/varset Ok2Assist 1
		} else /if (${assistid}==${Me.ID}) {
			/varset Ok2Assist 1
		} else {
			/varset Ok2Assist 0
		}
	}
	/if (!${Ok2Assist} && ${Stick.Status.Equal[ON]}) /stick off
	/if (${Ok2Assist} && ${UseMelee}==1 && ${Spawn[${SpawnSearchType} id ${autotargetid}].PctHPs}>0 && ${Target.ID}==${autotargetid} && ${Stick.Status.Equal[OFF]}) {
		/face fast
		/if (${StickHow.NotEqual[NULL]}) {
			/stick ${StickHow} 11
		} else /if (${Math.Calc[${Target.MaxRangeTo}*0.8]} > 29) {
			/stick snaproll rear 11
		} else {
			/stick ${Math.Calc[${Target.MaxRangeTo}*0.8]} behind uw 11
		}
		/delay 10 ${Stick.Active}
	}
	/call EngageAttack
/return
|-------------------------------------------------------------------------------------
|- SUB: EngageAttack	
|-------------------------------------------------------------------------------------
Sub EngageAttack
	/if (!${Me.Combat} && ${UseMelee}==1 && ${Target.PctHPs}<=${AutoAssistAt} && ${Target.PctHPs}>0 && ${Target.ID}==${autotargetid} && ${Spawn[id ${autotargetid} ${SpawnSearchType} radius ${AssistRange}].ID} && ${Ok2Assist}) {
		/if (${Target.MaxRangeTo}>=${Target.Distance}) {
			/if (${BeforeCombat.NotEqual[NULL]}) /call ${BeforeCombat}
			/squelch /attack on
			/delay 10 ${Me.Combat}
		}
	}
/return 
|-------------------------------------------------------------------------------------
|- SUB: CastSpell - Taken from kissassist and modified. Better spell casting control for longer casting spells plus return messages for monitoring resists, interruptions, immune
|-------------------------------------------------------------------------------------
Sub CastSpell(string WhatSpell,int WhatID,string sentFrom)
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
|-------------------------------------------------------------------------------------
|- SUB: NavgationDelay
|-------------------------------------------------------------------------------------
Sub NavgationDelay
	:naving
	/delay 1s
	|-/echo Navigating...
	/if (${Navigation.Active}) /goto :naving
	|-/echo Navigation Finished!
/return 
|-------------------------------------------------------------------------------------
|- SUB: KillTarget
|-------------------------------------------------------------------------------------
Sub KillTarget
	/varset KillTargetID ${Me.GroupAssistTarget.ID}
	/varset autotargetid ${Me.GroupAssistTarget.ID}
	/varset SpawnSearchType targetable
	/if (${StickToKillTarget}) {
		/stick id ${Me.GroupAssistTarget.ID}
	}
	/call EngageAttack
/return
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