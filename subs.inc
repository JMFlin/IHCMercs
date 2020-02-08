|- File: subs.inc
|- Version 2.1
|- Original File: auto_subs.inc
|- Auto-Subs Shared routines across Auto series macros by Noobhaxor
|- Version 6.2
|- Updated: 4/25/2019
|- Modified version of the above file to maintain compatability with the automac's / kissassist
|- Modified to fit the IHC mac's and mod's better


|**
IDEAS:

Replace SpawnSort with NearestSpawn like in HUD?

DO THIS:
Bring back your own old PathLength code?



**|
#bind Campfire       /campfire
#bind GroupBehindMe  /rallybehind
#bind GroupFrontFace /rallyfront
#bind KillMATarget   /killtarget
#bind ad /ad

|----------------------------------------------------------------------------
|- SUB: Compatibility with KissAssist Aliases Old and New
|----------------------------------------------------------------------------
Sub var_setup
|	/declare autotargetid		int outer 0
|	/declare sittimer			timer outer 0
|	/declare enablesit			int outer 0
|	/declare ReturnToCamp		int outer 0
|	/declare AutoCampX			int outer ${Me.X}
|	/declare AutoCampY			int outer ${Me.Y}
|	/declare changetoini		int outer 0
|	/declare targetcleartimer	timer outer 0
|	/declare numoftargets		int outer 0
|	/declare ChaseAssist		int outer 0		
	|- IHC macro's common variables
	/declare BurnMobCount		int outer 3
	/declare BackOffFlag		int outer 0
	/declare BeforeCombat		string outer NULL
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

	/declare IllusionNum		int outer 0
	/declare RunAndGunMedTimer	timer outer	0

	/declare petFollow 			int outer 0
	/declare illusionItem 		string outer "Bone Mask of Horror"

	/declare autoCampRadius 	int outer 10
|- Rezzing
	/declare setCombatRadius	int outer 50
	/declare setMaxRezRange 	int outer 150
	/declare rezToken 			bool outer FALSE
	/declare rezCombat			bool outer FALSE

|- AFK camping
    /declare pullRadiusXY 		int outer 100
	/declare pullRadiusZ 		int outer 100
	/declare npcRadiusCheck		int outer 65
    /declare pullAbility		string outer NULL
	/declare pullAutoCampX		int outer 0
    /declare pullAutoCampY		int outer 0
	/declare pullAutoCampZ		int outer 0
	/declare pullDistance 		int outer 0
	/declare chainPullLimit 	int outer 20
	/declare resourceChecker 	int outer 1
	/declare Limit 				int outer 50
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
	/declare allowedFizzleCount int outer 3

|- timers
	/declare TimeForMez					timer outer	0
	/declare TimeForMezVariable			int outer 0
	/declare checkResourcesTimer  		timer outer 0 
	

|- melee skills
	/declare intimidation 	bool outer FALSE
	/declare eaglestrike 	bool outer FALSE
	/declare tigerclaw 		bool outer FALSE
	/declare dragonpunch 	bool outer FALSE
	/declare kick 			bool outer FALSE
	/declare backstab 		bool outer FALSE
	/declare frenzy 		bool outer FALSE
	/declare flyingkick 	bool outer FALSE
	/declare roundkick  	bool outer FALSE
	/declare bash 			bool outer FALSE

|- alliance
	/declare UseAlliance 	bool outer FALSE

|- events
	/declare snareImmuneID 		int outer 0
	/declare slowImmuneID 		int outer 0
	/declare mezzImmuneID 		int outer 0
	/declare stunImmuneID 		int outer 0
	/declare hybridManaLimit 	int outer 80
	/declare cannotCast 		bool outer FALSE

|- observers
	/declare lstObserverCure 	string outer "|Me|TotalCounters|CountersDisease|CountersCurse|CountersPoison|CountersCorruption|Snared|Mezzed|Maloed|Tashed"

|- assisting
	/declare autoAssistAt 		int outer 0
	/declare assistRange 		int outer 0

|- sets 
	/declare immuneSet			 set outer
	/declare immuneSetIterator	 setiterator outer
	/declare debuffSet 			 set outer
|- verbose
	/declare verboseSHD 		bool outer FALSE
	/declare verboseWAR 		bool outer FALSE
	/declare verboseBST 		bool outer FALSE
	/declare verboseDRU 		bool outer FALSE
	/declare verboseSHM 		bool outer TRUE
	/declare verboseBER 		bool outer TRUE
	/declare verboseWIZ 		bool outer FALSE
	/declare verboseENC 		bool outer TRUE
	/declare verboseBRD 		bool outer TRUE
	/declare verboseCLR 		bool outer FALSE
	/declare verboseMAG 		bool outer FALSE
	/declare verboseMNK 		bool outer TRUE

|- classes
	/declare casterCasting 		int outer 0

|- travel
	/declare Invis				bool outer FALSE

|- travel
	/declare mezzDone 			bool outer FALSE

|- mercs
	/declare useMerc 			int outer 0

|- burns
	/declare burnRotation 		int outer 1
	/declare inBetween			int outer 0

|- 
	/declare worstHurtId 		int outer 0

	/declare PowerLevel 		bool outer FALSE
	/declare goSell 			int outer 0
/return 
|----------------------------------------------------------------------------
|- SUB: IllusionCheck - Check for Plaguebringer illusion
|----------------------------------------------------------------------------
Sub check_illusion(bool _debug, string _illusionItem)
	/if (${Me.XTarget}) /return
	/if (${validate_cast[FALSE, item, ${_illusionItem}, ${Me.ID}]}) /cast item ${_illusionItem}
/return
|----------------------------------------------------------------------------
|- SUB: set_timers
|---------------------------------------------------------------------------- 
Sub set_timers
	/if (${Group.MainTank.ID} == ${Me.ID}) {

		/if (${TimeForMezVariable} == 1 && !${Me.XTarget}) /varset TimeForMezVariable 0
			
		/if (${Me.XTarget} && ${TimeForMezVariable} == 0) {
			/varset TimeForMez 7s
			/varset TimeForMezVariable 1
		}
	}

	/if (${Group.Puller.ID} == ${Me.ID}) {

		/if (${checkResourcesTimer} == 0) {
			/varset checkResourcesTimer 20s
		}
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

 		/docommand /dgt  Previous mode \ar ${PreviousModeName} \ax Current mode \ag ${ModeName}
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
	/varset pullAutoCampY ${Me.Y}
	/varset pullAutoCampX ${Me.X}
	/varset pullAutoCampZ ${Me.Z}
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
|- SUB: engage
|---------------------------------------------------------------------------- 
Sub engage

	/if (!${validate_combat[${Target.ID}]} ) /return
	/if (!${validate_target_distance[FALSE]}) /return
	| if target is not an NPC then don't engage
	| /if (!${Target.Type.Equal[NPC]}) /return
	
	/if (${Target.ID}) /face fast

	/if (${Navigation.Active}) /nav stop
	
	/if (${Me.ID} == ${Group.MainTank.ID}) {
		/if (!${Stick.Active}) /stick 12 moveback loose
		/delay 10 ${Stick.Active}
	}

	/if (${Me.ID} != ${Group.MainTank.ID}) {
		/if (!${Stick.Active}) /stick 12 hold moveback !front loose
		/delay 10 ${Stick.Active}
	}
	/if (!${Me.Combat} && ${Select[${Me.Class.ShortName},BER,ROG]}) {
		/if (${validate_cast[FALSE, disc, ${PreCombatDisc}, ${Target.ID}]}) /call core_cast2 ${PreCombatDisc} disc ${Target.ID} FALSE
	}
	/if (${Target.ID} && ${Target.Distance3D} < 50) /squelch /attack on
	/call pet_attack

/return

sub validate_target_distance(bool _debug)
	/if (${Target.Distance} > 200) {
		/if (${Stick.Active}) /stick off
		/if (${Navigation.Active}) /nav stop
		/target clear
		/return FALSE
	}
/return TRUE
|----------------------------------------------------------------------------
|- SUB: Travel
|----------------------------------------------------------------------------
Sub Travel
	/if (${Stick.Status.Equal[ON]}) /stick off
	/if (${MakeCamp.Status.Equal[ON]}) /makecamp off
	/attack off
	/if (${Me.Pet.ID} && ${Me.Combat}) /pet back off
	/if (${Me.Pet.ID} && !${petFollow}) {
		/pet follow
		/varset petFollow 1
	}

	/if (${pullAutoCampY} != 0) /varset pullAutoCampY 0
	/if (${pullAutoCampX} != 0) /varset pullAutoCampX 0
	/if (${pullAutoCampZ} != 0) /varset pullAutoCampZ 0

	/if (${Navigation.MeshLoaded} && ${Group.Leader.ID} != ${Me.ID} && !${Group.Member[${Group.Leader.ID}].OtherZone}) {
		/if (!${Navigation.Active} && ${Navigation.PathLength[id ${Group.Leader.ID}]} > 50) /nav id ${Group.Leader.ID}
		/if (${Navigation.Active} && ${Navigation.PathLength[id ${Group.Leader.ID}]} < 20) /nav stop
	}

	/if (${Select[${Me.Class.ShortName},SHM]}) {
		/call core_cast2 "${TravelSpell}" FIND ${Me.ID} FALSE
	}

	/if (${Select[${Me.Class.ShortName},BRD]} && !${Me.Buff[Selo's Accelerating Chorus].ID} && !${Me.Casting.ID} && !${Me.Invis}) {
		/stopsong
		/melody 3 1
	}
	/if (${Select[${Me.Class.ShortName},BRD]} && !${Me.Buff[Selo's Accelerating Chorus].ID} && !${Me.Casting.ID} && !${Me.Invis}) {
		/stopsong
		/melody 1
	}
	/call misc
/return
|----------------------------------------------------------------------------
|- SUB: check_add_aggro
|---------------------------------------------------------------------------- 
Sub check_add_aggro

	/if (${Balance}) /return
	/if (!${Me.XTarget[2].ID}) /return
	/if (${TimeForMez} != 0) /return

	/if (${Target.Type.Equal[Corpse]}) /target clear

	| if any npcs on xtarget have less than 100% aggro
	/if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100) {
		/if (${If[${Select[${SpawnSort[1,asc,PctAggro,xtarhater].Animation},110,26,32,71,72,111]}, 0, 1]}==1) {
			/target id ${SpawnSort[1,asc,PctAggro,xtarhater].ID}
			/delay 5 ${Target.ID} == ${SpawnSort[1,asc,PctAggro,xtarhater].ID}
			/call engage
			/call ${Me.Class.ShortName.Lower}_get_aggro
			/call ${Me.Class.ShortName.Lower}_aoe_aggro
			/delay 1s
		}
	}

/return
|----------------------------------------------------------------------------
|- SUB: puller_check_group_resources
|---------------------------------------------------------------------------- 
Sub puller_check_group_resources
	
	/declare _count	int local 0

	/if (${Me.XTarget[1].ID}) /return
	/if (${Group.Puller.ID} != ${Me.ID}) /return

	/if (${Limit} == 50 && ${resourceChecker} == 0) /varset Limit 85
	/if (${Limit} == 85 && ${resourceChecker} == 1) /varset Limit 50
	/varset resourceChecker 1
	/varset casterCasting 0

	/for _count 0 to ${Group}
		/if (!${Group.Member[${_count}].Type.Equal[PC]}) /continue
		/if (${Group.Member[${_count}].Distance} < 100 && !${Group.Member[${_count}].OtherZone}) {

			

			/if (${Select[${Group.Member[${_count}].Class.ShortName},CLR,SHM,NEC,ENC,WIZ,MAG,DRU,SHD,PAL,BST]}) {


				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.PctMana" "ResPct" "int"
				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.Casting.ID" "casterCasting" "int"

				DEBUG Asking ${Group.Member[${_count}].DisplayName} about mana ${ResPct} < ${Limit}

			} else /if (${Select[${Group.Member[${_count}].Class.ShortName},WAR,ROG,BER,MNK]}) {

				/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Me.PctEndurance" "ResPct" "int"

				DEBUG Asking ${Group.Member[${_count}].DisplayName} about endurance ${ResPct} < ${Limit}

			}
			/if (${ResPct} < ${Limit} || ${casterCasting}) {
				/varset resourceChecker 0 
				/delay 5
			}
			/if (${resourceChecker} == 0) /return
		}
	/next _count
/return
|----------------------------------------------------------------------------
|- SUB: AFKPull /varset PullTargetID ${SpawnSort[1,asc,PathLength,npc targetable noalert 1 radius ${pullRadiusXY} zradius ${pullRadiusZ}].ID}
|---------------------------------------------------------------------------- 
Sub pre_pull_group_healer_spells
	/declare promisedSpell string outer NULL
	/declare elixirSpell string outer NULL
	/declare elixirCastTime string outer NULL

	| /if (${DanNet.Peers.Find[${EverQuest.Server.Lower}_${Spawn[group shaman].Name.Lower}]})
	| /if (${DanNet.Peers.Find[${EverQuest.Server.Lower}_${Spawn[group druid].Name.Lower}]})

	/if (${Group.Cleric.ID}) {
		/call Gquery ${Group.Cleric.Name.Lower} "PromisedHeal" "promisedSpellName" "string"
		/call Gquery ${Group.Cleric.Name.Lower} "SingleElixirSpell" "elixirSpellName" "string"
		/call Gquery ${Group.Cleric.Name.Lower} "Math.Calc[${Spell[${elixirSpellName}].MyCastTime.Float}]" "elixirCast" "int"

		/varset promisedSpell ${promisedSpellName}
		/varset elixirSpell ${elixirSpellName}
		/varset elixirCastTime ${elixirCast}
	}
/return

Sub afk_pull
	/declare _pullTargetID 	int local 0
	/if (${Posse.Strangers} > 0) /return
	/if (${Select[${Me.Class.ShortName},BST]}) {
		/if (!${Me.Pet.ID}) /return
	}
	/if (${Me.XTarget}) /return
	/if (${Me.Casting.ID}) /return
	/if (!(${Group.Puller.ID} == ${Me.ID})) /return
	/if (!${Navigation.MeshLoaded}) /return
	/if (${Me.Snared.ID}) /return
	/if (${Me.PctHPs} < 90) /return
	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]}) /return
	/if (!${SpawnCount[npc targetable noalert 1 radius ${pullRadiusXY} zradius ${pullRadiusZ}]}) /return
	/if (${checkResourcesTimer} != 0) /return
	/if (!${pullAbility.Equal[Melee]}) {
		/if (!(${Me.CombatAbilityReady[${pullAbility}]} || ${Me.AbilityReady[${pullAbility}]} || ${Me.AltAbilityReady[${pullAbility}]} || ${Me.SpellReady[${pullAbility}]})) /return
	}
	/call puller_check_group_resources
	
	/if (${resourceChecker} == 0) {
		/call set_timers
		/return
	}

	
	/if (${Group.MainTank.ID} == ${Me.ID} && ${Group.Cleric.ID}) {

		/if (!${Me.Song[${elixirSpell}].ID}) {
			
			DEBUG
			DEBUG Begging for ${elixirSpell}
			
			/squelch /dex ${Group.Cleric.Name.Lower} /target ${Me.Name}
			/delay 1s
			/squelch /dex ${Group.Cleric.Name.Lower} /cast "${elixirSpell}"
			/delay ${elixirCastTime}s
			/delay 1s
		}
	|**
		/if (!${Me.Buff[${promisedSpell}].ID}) {
			
			DEBUG Begging for ${promisedSpell}
			
			/squelch /dex ${Group.Cleric.Name.Lower} /target ${Me.Name}
			/delay 1s
			/squelch /dex ${Group.Cleric.Name.Lower} /cast "${promisedSpell}"
			/delay 2s
		}
		**|
	}
	
	
	/while (!${Me.XTarget}) {
		/call set_pull_target
		/varset _pullTargetID ${Macro.Return}
		/if (!${_pullTargetID}) {
			/if (${Navigation.Active}) /nav stop
			/return
		}

		/if (!${pullAbility.Equal[Melee]}) /call get_pull_target ${_pullTargetID}
		/if (${pullAbility.Equal[Melee]}) /call get_pull_target_melee_range ${_pullTargetID}
	
		/delay 1
	}

    /nav locxyz ${pullAutoCampX} ${pullAutoCampY} ${pullAutoCampZ}
	
	/while (${Navigation.Active}) {
		/if (${Me.Pet.ID} && ${Me.Pet.Combat}) /pet back
		/if (${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${pullAutoCampY},${pullAutoCampX},${pullAutoCampZ}]} < 10 && ${Navigation.Active}) /nav stop
		/delay 1
	}
	
	/if (!${Me.XTarget}) {
		/target clear
    } else /if (${Target.ID} && ${Me.XTarget}) {
		/face fast
		/call ${Me.Class.ShortName.Lower}_combat_buffs
		/if (${Target.Distance3D} > 70) {
			/if (${validate_cast[FALSE, alt, "${PullTowards}", ${Target.ID}]}) /call core_cast2 "${PullTowards}" alt ${Target.ID} FALSE
		}
	}
	
	/if (${Defined[_pullTargetID]}) /deletevar _pullTargetID
	/delay 5
 /return


 Sub chain_pull
	/declare _pullTargetID 	int local 0

	/if (${Posse.Strangers} > 0) /return
	/if (${Me.XTarget}) /return
	/if (${Me.Casting.ID}) /return
	/if (!(${Group.Puller.ID} == ${Me.ID})) /return
	/if (!${Navigation.MeshLoaded}) /return
	/if (${Me.PctEndurance} < ${chainPullLimit}) {
		/varset chainPullLimit 80
		/return
	} else {
		/varset chainPullLimit 20
	}
	
	/while (!${Me.XTarget}) {
		/call set_pull_target
		/varset _pullTargetID ${Macro.Return}
		/if (!${_pullTargetID}) {
			/if (${Navigation.Active}) /nav stop
			/return
		}

		/if (!${pullAbility.Equal[Melee]}) /call get_pull_target ${_pullTargetID}
		/if (${pullAbility.Equal[Melee]}) /call get_pull_target_melee_range ${_pullTargetID}
	
		/delay 1
	}

    /nav locxyz ${pullAutoCampX} ${pullAutoCampY} ${pullAutoCampZ}
	
	/while (${Navigation.Active}) {
		/if (${Me.Pet.ID} && ${Me.Pet.Combat}) /pet back
		/if (${Math.Distance[${Me.Y},${Me.X},${Me.Z}:${pullAutoCampY},${pullAutoCampX},${pullAutoCampZ}]} < 10 && ${Navigation.Active}) /nav stop
		/delay 1
	}
	
	/if (!${Me.XTarget}) /target clear
    /if (${Target.ID} && ${Me.XTarget}) /face fast
	/if (${Defined[_pullTargetID]}) /deletevar _pullTargetID
	/if (${Me.XTarget}) /call ${Me.Class.ShortName.Lower}_combat_buffs
	/delay 5
 /return


Sub get_pull_target_melee_range
	/if (${Spawn[id ${_tmpID}].Distance} > ${pullDistance} || !${Spawn[id ${_tmpID}].LineOfSight}) {
		
		/nav id ${_tmpID}
		/while (${Navigation.Active}) {
			/if (!${Spawn[id ${_tmpID}].LineOfSight} || ${Spawn[id ${_tmpID}].Distance} > (${pullDistance} + 100)) /continue

			/target id ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}

			/if (!${Me.XTarget} && ${Target.ID} && ${Spawn[id ${_tmpID}].Distance} < ${pullDistance}) {
				/if (${Spawn[id ${_tmpID}].Distance} < 20) /call get_close_target
			} 

			/if (${Navigation.Active} && ${Me.XTarget}) {
				/if (${_tmpID} != ${Me.XTarget[1].ID}) {
					/target id ${Me.XTarget[1].ID}
					/nav stop
					/return
				}
			}

			/delay 1
		}
	}

/return

Sub get_pull_target(int _tmpID)

	/if (${Spawn[id ${_tmpID}].Distance} < ${pullDistance} && ${Spawn[id ${_tmpID}].LineOfSight}) {
		
		/if (${Spell[${pullAbility}].MyCastTime.Float} > 1) /delay 3s !${Me.Moving}

		/if (${validate_cast[FALSE, FIND, ${pullAbility}, ${_tmpID}]}) {
			/call core_cast2 "${pullAbility}" FIND ${_tmpID} FALSE
			/call check_cast_events "${pullAbility}" CAST_CANNOTCAST ${_tmpID}
			/if (!${Me.XTarget}) /call check_cast_events "${pullAbility}" CANNOT_HIT ${_tmpID}
			/if (${cannotCast}) {
				/varset cannotCast FALSE
				/return
			}
		}
		/delay 1s ${Me.XTarget}
		/return
	}
	
	/nav id ${_tmpID}

	/while (${Navigation.Active}) {

		/if (${Navigation.Active} && ${Me.XTarget}) {
			/if (${_tmpID} != ${Me.XTarget[1].ID}) {
				/target id ${Me.XTarget[1].ID}
			}
			/return
		}

		/if (!${Spawn[id ${_tmpID}].LineOfSight} || ${Spawn[id ${_tmpID}].Distance} > (${pullDistance} + 100)) /continue
		/if (${Spell[${pullAbility}].MyCastTime.Float} < 1) {
			:tag_target
			/if (${validate_cast[FALSE, FIND, ${pullAbility}, ${_tmpID}]}) {
				/call core_cast2 "${pullAbility}" FIND ${_tmpID} FALSE
				/call check_cast_events "${pullAbility}" CAST_CANNOTCAST ${_tmpID}
				/if (!${Me.XTarget}) /call check_cast_events "${pullAbility}" CANNOT_HIT ${_tmpID}
				/if (${cannotCast}) {
					/varset cannotCast FALSE
					/return
				}
			}
			/if (!${Me.XTarget}) {
				/if (${Spawn[id ${_tmpID}].Distance} < 20) /call get_close_target
				/if (!${Me.XTarget}) /goto :tag_target
			}
		} else {
			/if (${Navigation.Active}) /nav stop
			/if (${Me.XTarget}) /return
			/delay 3s !${Me.Moving}
			/delay 5
			/if (${validate_cast[FALSE, FIND, ${pullAbility}, ${_tmpID}]}) {
				/call core_cast2 "${pullAbility}" FIND ${_tmpID} FALSE
				/call check_cast_events "${pullAbility}" CAST_CANNOTCAST ${_tmpID}
				/if (!${Me.XTarget}) /call check_cast_events "${pullAbility}" CANNOT_HIT ${_tmpID}
				/if (${cannotCast}) {
					/varset cannotCast FALSE
					/return
				}
			}
			/return
		}

		/if (!${Navigation.Active}) {
			/if (${Spawn[id ${_tmpID}].Distance} > ${pullDistance} || !${Spawn[id ${_tmpID}].LineOfSight}) {
				/if (!${Me.XTarget}) /nav id ${_tmpID}
			}
		}
		/delay 1
	}

/return

Sub get_close_target(int _tmpID)

	/if (${Navigation.Active}) /nav stop
	/call check_cast_events "${pullAbility}" CAST_CANNOTCAST ${_tmpID}
	/stick 12 moveback loose
	/attack on
	/if (!${Me.XTarget}) /call check_cast_events "${pullAbility}" CANNOT_HIT ${_tmpID}
	/delay 3s ${Me.XTarget}
	/stick off

/return

Sub validate_no_pc(int _tmpID)
	/declare locX			int	local	${Spawn[id ${_tmpID}].X}
	/declare locY			int	local	${Spawn[id ${_tmpID}].Y}
	/declare locZ			int	local	${Spawn[id ${_tmpID}].Z}
	/declare _groupCount	int local	${SpawnCount[loc ${locX} ${locY} radius 15 zradius 10 pc group notid ${Me.ID} noalert 1]}
	/declare _pcCount		int local 	${SpawnCount[loc ${locX} ${locY} radius 15 zradius 10 pc notid ${Me.ID} noalert 1]}
	
	/varcalc _pcCount ${_pcCount} - ${_groupCount}

	/if (${_pcCount} > 0) /return FALSE
	/if (${Me.TargetOfTarget.Name.NotEqual[${Me.DisplayName}]}) /return FALSE

/return TRUE

Sub validate_single_pull(int _tmpID)
	/declare locX			int	local	${Spawn[id ${_tmpID}].X}
	/declare locY			int	local	${Spawn[id ${_tmpID}].Y}
	/declare _addCount		int local	${SpawnCount[loc ${locX} ${locY} radius ${npcRadiusCheck} zradius 20 npc targetable noalert 1]}
	
	/if (${_addCount} > 1) /return FALSE

/return TRUE

Sub set_pull_target
	/declare _count 		int local 1
	/declare _pullMob 		int local 0
	/declare _mobsInRadius 	int local 0
	/declare _pullTargetID 	int local 0
	/declare _pathLength 	int local 999

	/if (${Me.XTarget[1].ID}) {
		/varset _pullTargetID ${Me.XTarget[1].ID}
		/return ${_pullTargetID}
	}

	/varset _mobsInRadius ${SpawnCount[npc targetable noalert 1 loc ${pullAutoCampX} ${pullAutoCampY} radius ${pullRadiusXY} zradius ${pullRadiusZ}]}
	
	|DEBUG 
	|DEBUG Mobs in radius: ${Int[${_mobsInRadius}]}
	|DEBUG 

	/if (${_mobsInRadius} == 0) {
		DEBUG Mobs in radius: ${Int[${_mobsInRadius}]}
		/return 0
	}

	/while (${_count} <= ${_mobsInRadius}) {

		/if (${Me.XTarget}) /return ${Me.XTarget[1].ID}

		/varset _pullMob ${NearestSpawn[${_count}, npc targetable noalert 1 radius ${pullRadiusXY} zradius ${pullRadiusZ}].ID}

		|DEBUG Does Navigation.Path exist to ${Spawn[id ${_pullMob}].DisplayName}: ${Navigation.PathExists[id ${_pullMob}]}
		/if (!${Navigation.PathExists[id ${_pullMob}]}) {
			/varcalc _count ${_count}+1
			/continue
		}
		
		|DEBUG Are there no PCs close to ${Spawn[id ${_pullMob}].DisplayName}: ${validate_no_pc[${_pullMob}]}
		|/if (!${validate_no_pc[${_pullMob}]}) {
		|	/varcalc _count ${_count}+1
		|	/continue
		|}
		
		|DEBUG Are there no adds close to ${Spawn[id ${_pullMob}].DisplayName}: ${validate_single_pull[${_pullMob}]}
		/if (!${validate_single_pull[${_pullMob}]}) {
			/varcalc _count ${_count}+1
			/continue
		}
		
		|DEBUG How does the Path Length compare for ${Spawn[id ${_pullMob}].DisplayName}: ${Int[${Navigation.PathLength[id ${_pullMob}]}]} vs ${_pathLength}
		/if (${_pathLength} > ${Int[${Navigation.PathLength[id ${_pullMob}]}]}) {
			/varset _pullTargetID ${_pullMob}
			/varset _pathLength ${Int[${Navigation.PathLength[id ${_pullMob}]}]}
		}

		/varcalc _count ${_count} + 1
	}
	|DEBUG 
	DEBUG Set ${Spawn[id ${_pullTargetID}].DisplayName} as pull target
	|DEBUG 

/return ${_pullTargetID}
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
Sub pet_attack
	/if (!${Me.Pet.ID}) /return
	/if (${petFollow}) /varset petFollow 0
	/if (!${validate_combat[${Target.ID}]} ) /return
	
	|- Spirit call
	/if (${Target.PctHPs} >= 30 && ${Me.AltAbilityReady[Spirit Call]}) {
		/if (!${Target.Type.Equal[NPC]} && !${Target.Type.Equal[Corpse]}) /alt act 177
		/delay 2
	}
	/if (!${Me.Pet.Combat}) {
		/if (${Target.Type.Equal[NPC]} && !${Target.Type.Equal[Corpse]}) /pet attack 
		/if (${Target.Type.Equal[NPC]} && !${Target.Type.Equal[Corpse]}) /pet swarm
	}

	/if (!${Spawn[${Group.MainTank} pccorpse radius 40].ID} && ${Me.Pet.Taunt}) /pet taunt off
	/if (${Spawn[${Group.MainTank} pccorpse radius 40].ID} && !${Me.Pet.Taunt}) /pet taunt on
/return

|***
 *	DES: the the mass group buff
 *	USE: CHECKINPUTS
 *	NOTE: 
 ***|
sub check_buffs_mgb(bool _debug)
	
	| do not use outside raid
	/if (!${Raid.Members}) /return FALSE
	
	| caster?
	/if (!${validate_class[FALSE, ${lstClassCast}]}) /return FALSE
	
	| need more mana
	/if (${Me.PctMana} < ${BuffMGBMana}) /return FALSE
	
	| more people!
	/if (${Raid.Members} < ${BuffMGBCount}) /return FALSE

	| is my stuff ready?
	/if (!${Me.AltAbilityReady[Tranquil Blessings]} && !${Me.AltAbilityReady[Mass Group Buff]}) /return FALSE
	
	| do I have
	/if (${Bool[${Me.Buff[${BuffMGBchk}].Duration}]}) /return FALSE
	
	| TB or MGB ??
	/if (${Me.AltAbilityReady[Tranquil Blessings]}) {
		/if (${validate_cast[FALSE, alt, "Tranquil Blessings", ${Me.ID}]}) /call core_cast2 "Tranquil Blessings" alt 0 FALSE	
	} else /if (${Me.AltAbilityReady[Mass Group Buff]}) {
		/if (${validate_cast[FALSE, alt, "Mass Group Buff", ${Me.ID}]}) /call core_cast2 "Mass Group Buff" alt 0 FALSE	
	}
	/if (${validate_cast[FALSE, spell, "${BuffMGBname}", ${Me.ID}]}) /call core_cast2 "${BuffMGBname}" ${buffgem} ${Me.ID} FALSE

/return
|----------------------------------------------------------------------------
|- SUB: Campfire ${Window[FellowshipWnd].Child[FP_CampPage].Child[FP_CampsiteViewer].Text}
|----------------------------------------------------------------------------
Sub Bind_Campfire
    /declare FellowCount int local 0
    /declare i int local
    /declare j int local

	/if (${Me.Fellowship.Campfire}) /return

    /for i 1 to ${SpawnCount[pc radius 50]}
        /for j 1 to ${Me.Fellowship.Members}
            /if (${NearestSpawn[${i},PC radius 50].CleanName.Equal[${Me.Fellowship.Member[${j}]}]}) /varcalc FellowCount ${FellowCount}+1
        /next j
    /next i

	/return
	|**
    /if (${FellowCount}>=3) {
        /windowstate FellowshipWnd open
		/delay 1s
		/nomodkey /notify FellowshipWnd FP_Subwindows tabselect 2
		/nomodkey /notify FellowshipWnd FP_RefreshList leftmouseup
		|/delay 5s ${Window[ConfirmationDialogBox].Open}
		|/if (${Window[ConfirmationDialogBox].Open}) /nomodkey /notify ConfirmationDialogBox Yes_Button leftmouseup
		|/delay 5s !${Me.Fellowship.Campfire}
		/delay 1s
		/nomodkey /notify FellowshipWnd FP_RefreshList leftmouseup
		/delay 1s        
		/nomodkey /notify FellowshipWnd FP_CampsiteKitList listselect 1
		/delay 1s
		/nomodkey /notify FellowshipWnd FP_DestroyCampsite leftmouseup
		/delay 1s
		/nomodkey /notify FellowshipWnd FP_CreateCampsite leftmouseup
		/delay 5s ${Me.Fellowship.Campfire}
		/windowstate FellowshipWnd close
    }

**|
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
|- EX:/call Gquery ${EverQuest.Server.Lower}_${Group.Member[${_count}].Name.Lower} "Spell[${FocusSpell}].Stacks" "tmpstackcheck" "bool"
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
|- SUB: Check Plugin
|----------------------------------------------------------------------------
Sub CheckPlugin(string pluginname)
    /if (!${Bool[${Plugin[${pluginname}]}]}) {
        /squelch /plugin ${pluginname} noauto
        /echo \aw ${pluginname} not detected! Loading ...
    }
/return	
|----------------------------------------------------------------------------
|- SUB: Death Sub
|----------------------------------------------------------------------------
Sub DeathSub
    /while (${Me.Hovering}) {
	|**
	/if (${Window[RespawnWnd].Open} && ${UseFellowship}==1 && ${InstantRelease}==1) {
		/nomodkey /notify RespawnWnd RW_OptionsList listselect 1 
		/delay 1s
		/nomodkey /notify RespawnWnd RW_SelectButton leftmouseup
		/delay 5s ${Me.Zoning}
	}
	**|
		/delay 2s
	}
	/delay 1m !${Me.Zoning}
	|**
	/if (${UseFellowship}==1 && ${FindItem["Fellowship Registration Insignia"].Timer}==0) {
		/delay 30s ${Me.CombatState.Equal[ACTIVE]}
		/useitem "Fellowship Registration Insignia"
		/delay 2s ${FindItem["Fellowship Registration Insignia"].Timer}!=0
	} else /if (${UseFellowship}==1 && ${FindItem["Fellowship Registration Insignia"].Timer}!=0) {
		/echo \aw Bummer, Insignia on cooldown, you must really suck at this game...
	} else {
		/echo \aw Waiting on someone that knows how to heal to \ar rez me
	}
	**|
/return
|----------------------------------------------------------------------------
|- SUB: UnCheck Plugin
|----------------------------------------------------------------------------
Sub UnCheckPlugin(string pluginname)
    /if (${Bool[${Plugin[${pluginname}]}]}) {
        /squelch /plugin ${pluginname} unload
        /echo \aw ${pluginname} detected! Unloading ...
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
|-------------------------------------------------------------------------------------
|- SUB: ClickModRoD - 
|-------------------------------------------------------------------------------------
Sub ClickModRoD
	/if (${FindItem[Transvergence].ID} && ${FindItem[Transvergence].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Transvergence]}"
	/if (${FindItem[Modulation].ID} && ${FindItem[Modulation].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Modulation]}"
/return 
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
|-------------------------------------------------------------------------------------
|- SUB: Welcome Message
|-------------------------------------------------------------------------------------
Sub WelcomeMsg
	/echo \aw****************************
	/echo \awWelcome\ag
	/echo \aw****************************
/return
|----------------------------------------------------------------------------
|- SUB: get_target  
|---------------------------------------------------------------------------- 
Sub get_target
	/declare _npcIDontHaveAggroOnID 	int local 0
	/declare _currentTarget 			int local 0
	/declare _tmpID 				int local 0

	| is there a target to be had?
	|/echo Checking xtarget
	/if (!${Me.XTarget}) /return

	| should we be balancing?
	|/echo Checking balance
	/if (${Me.ID} == ${Group.MainAssist.ID} && ${Balance}) /return

	| if I have a target: assist and get ready
	/if (${Me.XTarget}) {
		/if (${Me.Sitting}) /stand
		/if (${Target.Type.Equal[Corpse]}) /target clear
	}

	/varset _currentTarget ${Target.ID}

	/if (${Me.ID} == ${Group.MainAssist.ID}) {

		| if there is an xtarget close then target the one with lowest hp
		/if (${SpawnSort[1,asc,PctHPs,xtarhater].Distance} < 200) {
			/target id ${SpawnSort[1,asc,PctHPs,xtarhater].ID}

			/if (${_currentTarget} != ${Target.ID}) {
				/if (${Navigation.Active}) /nav stop
				/if (${Stick.Active}) /stick off
			}

			/delay 5
		}
	}

	/if (${Me.ID} == ${Group.MainTank.ID}) {

		| if current target is not 100% aggro then get aggro
		/if (${Target.ID}) {
			/if (${Target.PctAggro} < 100) /call engage
			/if (${Target.PctAggro} < 100) /call ${Me.Class.ShortName.Lower}_get_aggro
		}

		| if any npcs on xtarget have less than 100% aggro
		/if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100) {

			/varset _npcIDontHaveAggroOnID ${SpawnSort[1,asc,PctAggro,xtarhater].ID}

			| is the mob mezzed?
			/if (${If[${Select[${SpawnSort[1,asc,PctAggro,xtarhater].Animation},110,26,32,71,72,111]}, 0, 1]}==1) {

				| if mob is not mezzed then target it and get aggro
				/target id ${_npcIDontHaveAggroOnID}
				/delay 5 ${Target.ID} == ${_npcIDontHaveAggroOnID}
				/delay 5
				/call engage
				/call ${Me.Class.ShortName.Lower}_get_aggro
			}
		}
	}

	| if I am not the main tank or ma assist then assist the MA
	/if (${Me.ID} != ${Group.MainAssist.ID} && ${Me.ID} != ${Group.MainTank.ID}) {
		| /if (${GroupAssistTarget}) 
		/assist ${Group.MainAssist.Name}
		/delay 1s ${Me.AssistComplete} == TRUE
		/delay 5

		/if (${_currentTarget} != ${Target.ID}) {
			/if (${Navigation.Active}) /nav stop
			/if (${Stick.Active}) /stick off
		}

		/return
	}

/return

|-------------------------------------------------------------------------------- 
| Sub validate_combat_buffs
|--------------------------------------------------------------------------------
sub validate_combat_buffs(bool _debug)

	/if (!${Me.XTarget}) /return FALSE
	/if (!${Target.ID}) /return FALSE
	/if (${Target.Type.Equal[Corpse]}) /return FALSE
	/if (!${Target.Type.Equal[NPC]}) /return FALSE
	
	/if (!${Select[${Me.Class.ShortName},WAR,PAL]}) {
		/if (${Navigation.PathLength[id ${Target.ID}]} > ${assistRange}+60) /return FALSE
	}

	/if (!${Select[${Me.Class.ShortName},SHD]}) {
		/if (${Navigation.PathLength[id ${Target.ID}]} > ${assistRange}+100) /return FALSE
	}

/return TRUE

|-------------------------------------------------------------------------------- 
| Sub validate_combat
|--------------------------------------------------------------------------------
sub validate_combat(int _tmpID)

	/if (!${Me.XTarget}) /return FALSE
	/if (!${_tmpID}) /return FALSE
	|/if (!${Target.Type.Equal[NPC]}) /return FALSE
	/if (${Target.Type.Equal[Corpse]}) /return FALSE


	/if (${Select[${Me.Class.ShortName},BER,ROG,BRD]}) {
		/if (!${Spawn[id ${_tmpID}].LineOfSight} && ${Navigation.PathLength[id ${_tmpID}]} < ${assistRange}) {
			/if (${Stick.Active}) /stick off
			/nav id ${_tmpID}
		}
	}

	/if (${Group.MainTank.ID} != ${Me.ID}) {
		/if (${Target.PctHPs} > ${autoAssistAt}) /return FALSE
		/if (${Target.Mezzed.ID}) /return FALSE
		/if (${Group.MainTank.ID} && ${Group.MainTank.ID} != ${Me.ID}) {
			/if (${Spawn[id ${Group.MainTank.ID} pc radius 60].ID} && ${Me.PctAggro} >= 90) {
				/if (${Stick.Active}) /stick off
				/if (${Me.CombatState.Equal[COMBAT]}) /attack off
				/return FALSE
			}
		}
	}

	/if (${Target.PctHPs} < 95 || (${Target.PctHPs} < 98 && ${Navigation.PathLength[id ${_tmpID}]} < 65 && ${Spawn[id ${_tmpID}].LineOfSight}) || ${Navigation.PathLength[id ${_tmpID}]} < ${assistRange}) {

		/if (${Select[${Me.Class.ShortName},BER,BRD,ROG,MNK,WAR,PAL,SHD]}) {
			/if (${Group.MainTank.ID} != ${Me.ID}) {
				/if (!${SpawnCount[loc ${Spawn[id ${Group.MainTank.ID}].X} ${Spawn[id ${Group.MainTank.ID}].Y} radius 15 zradius 15 npc targetable]}) /return FALSE
			}
		}
		
		/return TRUE
	} else {
		/return FALSE
	}

/return TRUE

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

	| line of sight?
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
		
		| if not instant cast spell
		/if (${Spell[${_spell}].MyCastTime.Float} > 0) {
			| are we moving?
			/if (${Me.Moving}) /return FALSE
		}
		
		
		| /if (${Stick.Status.Equal[ON]}) /stick off

		/if (${Spell[${_spell}].MyCastTime.Float} > 0) {
			| are we moving?
			/if (${Navigation.Active}) /return FALSE
		}
		
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

		| if not instant cast spell
		/if (${Spell[${_spell}].MyCastTime.Float} > 0) {
			| are we moving?
			/if (${Me.Moving}) /return FALSE
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

		| if not instant cast spell
		/if (${Spell[${_spell}].MyCastTime.Float} > 0) {
			| are we moving?
			/if (${Me.Moving}) /return FALSE
		}
					
		| stacking
		| /if (${Spell[${FindItem[=${_spell}].Spell}].SpellType.Equal[Beneficial]} && (${_tmpID} == ${Me.ID})) {
		| 	/if (!${Spell[${FindItem[=${_spell}].Spell}].NewStacks}) /return FALSE
		| }

	
	| check bard shit.. gotta be difficult..
	} else /if (${_type.Equal[pulse]}) {
		/varset _spell ${Spell[${_spell}].RankName}
		/if (${Me.CurrentMana} < ${Spell[${_spell}].Mana}) /return FALSE
		|/if (${Me.Buff[${_spell}].Duration.TotalSeconds} > 20) /return FALSE
		|/if (${Me.Song[${_spell}].Duration.TotalSeconds} > 20) /return FALSE
		|/if (!${Spell[${_spell}].NewStacks}) /return FALSE
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
	/if (${Select[${_type},FIND,FORCE]} && ${Select[${Me.Class.ShortName},BRD]}) {
		/varset _type pulse
	} else /if (${Select[${_type},FIND,FORCE]}) {
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
		/declare _fizzle bool local FALSE
		/declare _fizzleCount int local 0
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
		/if (${_tmpID} != 0 && ${Me.Song[Gift of Mana].ID} && !${Select[${Me.Class.ShortName},CLR]} && ${Spawn[id ${_tmpID}].Type.NotEqual[pc]}) {
		
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

		/if (${Me.Gem[${_spell}]}) {

			| give this a try
			/while (${_castLoop}) {
				/varset _fizzle FALSE
			
				| can we say no MQ2Cast ???
				/cast ${Me.Gem[${_spell}]}

				:cast_in_progress
				| cast global cooldown spells
				/if (${_tmpID} != 0) {
					/if (!${Spawn[id ${_tmpID}].ID}) {
						/if (${Me.Casting.ID}) /stopcast
						/delay 1s !${Me.Casting.ID}
						/return
					}
				}
				/if (${Me.SpellInCooldown} && ${_tmpID} != 0 && !${Spell[${_spell}].SpellType.Equal[Beneficial]}) /call global_cooldown_spells ${_tmpID}

				/if (${Me.Casting.ID} || ${Window[CastingWindow].Open} || ${Me.SpellInCooldown}) /goto :cast_in_progress

				| check fizzle
				/call check_cast_events "${_spell}" CAST_FIZZLE ${_tmpID}
				/varset _fizzle ${Macro.Return}
				
				/if (!${_fizzle} || ${_fizzleCount} == ${allowedFizzleCount}) {
					/varcalc _castLoop ${_castLoop} - 1
				} else {
					/varcalc _fizzleCount ${_fizzleCount} + 1
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

		| delay for aa casting
		/delay ${Math.Calc[${Spell[${_spell}].MyCastTime.Float}+5]}s !${Me.Casting.ID}
		
		| .AltAbility .AltAbilityReady .AltAbilityTimer .AltCurrency .AltTimer .AltTimerReady
		
		| is the spell memed
		/if (${Me.AltAbilityReady[${_spell}]}) {

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

		| is the item ready?
		/if (${Me.ItemReady[${_spell}]}) {	


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
					/varcalc _castLoop ${_castLoop} - 1
					/delay 2
				}

			}

		}
		/return
		
	| disc
	} else /if (${Select[${_type},disc,activedisc]}) {
		|DEBUG ${dep}disc,activedisc${dep}${_spell}
		/varset _spell ${Spell[${_spell}].RankName}

		|/if (${Select[${Me.Class.ShortName},BRD]} && ${Me.XTarget}) /call engage

		|/if (${_tmpID} == 0) VDISC Disc ${sep} ${csp}${_spell}\ax
		|/if (${_tmpID} != 0 && ${Target.ID}) VDISC Disc ${sep} ${csp}${_spell}\ax ${sep} [${ctar}${Spawn[ID ${_tmpID}].DisplayName}\ax]
		|VBC Disc "${_spell}" ${_tmpID} 0 
		/disc ${Me.CombatAbility[${Me.CombatAbility[${_spell}]}].ID}
		| /disc ${_spell}
		/delay 5
		/while (${Me.Casting.ID} && ${Window[CastingWindow].Open}) {
			/delay 5
		}
		/return
	| bard song	
	} else /if (${Select[${_type},pulse]}) {
	|	DEBUG ${dep}pulse${dep}${_spell}
		/declare _fizzle bool local FALSE
		/declare _fizzleCount int local 0
		/declare _castLoop int local 1
		/varset castReturn CAST_NOTREADY
		/varset _spell ${Spell[${_spell}].RankName}
		
		/if (${Me.BardSongPlaying}) /call pulse_stop core_cast_pulsestop

		/if (!${Me.Gem[${_spell}]}) /call mem_spell FALSE TRUE "${_spell}" ${_type} TRUE

		| is the gem ready?
		/if (${Me.Gem[${_spell}]}) {	

			| gonna try this 2 times.

			/while (${_castLoop}) {
				/varset _fizzle FALSE
			
				| can we say no MQ2Cast ???
				/cast ${Me.Gem[${_spell}]}

				:cast_in_progress
				| cast global cooldown spells
				/if (${_tmpID} != 0) {
					/if (!${Spawn[id ${_tmpID}].ID}) {
						/if (${Me.Casting.ID}) /call pulse_stop core_cast_pulsestop
						/delay 1s !${Me.Casting.ID}
						/return
					} else {
						/call get_target
						/call engage
					}
				}
				
				/if (${Window[CastingWindow].Open}) /goto :cast_in_progress

				| check fizzle
				/call check_cast_events "${_spell}" CAST_FIZZLE ${_tmpID}
				/varset _fizzle ${Macro.Return}
				
				/if (!${_fizzle} || ${_fizzleCount} == ${allowedFizzleCount}) {
					/varcalc _castLoop ${_castLoop} - 1
				} else {
					/varcalc _fizzleCount ${_fizzleCount} + 1
				}
			}
		
		|**
			/while (${_castLoop}) {
				
				/cast ${Me.Gem[${_spell}]}

				| adjust delay for Metronome AA (fuck bards)
				/if (${Me.AltAbility[Metronome]}) {
					/delay ${Spell[${_spell}].CastTime.Seconds}s
				} else {
					/delay ${Math.Calc[${Spell[${_spell}].CastTime.Seconds}+${Math.Calc[${Spell[${_spell}].CastTime.Seconds}*.05]}]}s
				}
 				
 				|CHECKINPUTS
				| /call check_cast_events 2
						
				/if (${Select[${castReturn},CAST_SUCCESS]}) /break
				
				/if (${Select[${castReturn},CAST_NOTREADY]}) {
				 	/varcalc _castLoop ${_castLoop}-1
				 	/delay 2
				}

			}
		**|
			
		}
		/return
	
	}

/return FALSE

|----------------------------------------------------------------------------
|- SUB: global_cooldown_spells - Cast between spell casts (Weave)
|---------------------------------------------------------------------------- 
Sub global_cooldown_spells(int _tmpID)
| ${Me.AltAbility[Force of Flame].Rank} >= 1

	/if (${validate_cast[FALSE, alt, "Force of Flame", ${_tmpID}]}) {
		/alt act ${Me.AltAbility[Force of Flame].ID}
		/return
	}
	/if (${validate_cast[FALSE, alt, "Force of Ice", ${_tmpID}]}) {
		/alt act ${Me.AltAbility[Force of Ice].ID}
		/return
	}
	/if (${validate_cast[FALSE, alt, "Force of Will", ${_tmpID}]}) {
		/alt act ${Me.AltAbility[Force of Will].ID}
		/return
	}
/return

|***
 *	DES: process casting results from core_ cast2()
 *	USE: 
 *	NOTE: not for public consumption
 ***|
|sub check_cast_events(bool _debug)

|	/doevents CAST_BEGIN
|	/doevents CAST_CANNOTSEE    
|	/doevents CAST_COLLAPSE
|	/doevents CAST_COMPONENTS
|	/doevents CAST_DISTRACTED    
|	/doevents CAST_FDFAIL    
|	/doevents CAST_FIZZLE  
|	/doevents CAST_IMMUNE
|	/doevents CAST_INTERRUPTED
|	/doevents CAST_NOMOUNT   
|	/doevents CAST_NOTARGET
|	/doevents CAST_NOTREADY
|	/doevents CAST_OUTDOORS
|	/doevents CAST_OUTOFMANA  
|	/doevents CAST_OUTOFRANGE
|	/doevents CAST_RECOVER    
	| /varset CheckResisted 1
	| /doevents CAST_RESISTED    
	| /varset CheckResisted 0  
	| /doevents CAST_RESISTEDYOU    
|	/doevents CAST_STANDING 
|	/doevents CAST_STUNNED
|	/doevents CAST_TAKEHOLD    
|	/varcalc _checkLoops ${_checkLoops}-1
	
|/return

|***
 *	DES: Memorize a spell/song
 *	USE: /call mem_spell [DEBUG T/F] [echo memming T/F] ["spell name"] [gem to mem it in] [wait for recycle to cast T/F]
 *	NOTE: 
 ***|
sub mem_spell(bool _debug, bool _echo, string _spellname, string _spellgem, bool _wait)
	
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
	/if (!${Me.Book[${Spell[${_spellname}].RankName}]}) {
		/return FALSE
	}
	
	| just the facts ma'am
	/call fix_gem_id "${_spellgem}"
	/declare _gem int local ${Macro.Return}

	/if (${Me.State.NotEqual[SIT]} && !${Me.Mount.ID}) {
		/sit
		/delay 1s ${Me.State.Equal[SIT]}
	}
	
	| mem the spell
	/memspell ${_gem} "${Spell[${_spellname}].RankName}"
	/delay 5
	/delay 2s ${Me.Gem[${_gem}].Name.Equal[${Spell[${_spellname}].RankName}]}
	
	| wait for spell to be ready
	/while (${_wait}) {
		/if (!${_breakTimer}) /return FALSE
		/if (${Me.SpellReady[${Spell[${_spellname}].RankName}]}) /break
		/delay 2
	}

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

	| no rez spell in book
	/if (!${Me.Book[${RezSpell}]}) /return FALSE

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
	
	/if (${SpawnCount[pccorpse group radius ${setMaxRezRange}]} > 2) {
		/call cast_rez ${Me.ID} "${MassRezSpell}"
		/return
	}

	| clerics first group or raid
	/if (${SpawnCount[pccorpse cleric group radius ${setMaxRezRange}]} || ${SpawnCount[pccorpse cleric raid radius ${setMaxRezRange}]}) {

		/for _count 1 to ${SpawnCount[pccorpse group cleric radius ${setMaxRezRange}]}
			/varset _tmpID ${NearestSpawn[${_count},pccorpse group cleric radius ${setMaxRezRange}].ID}
			|/if (${Select[${Me.Class.ShortName},CLR]} && ${Me.AltAbilityReady[${_divinerezCLR}]} && ${DivineRezCleric}) {
			|	/call cast_rez ${_tmpID} ${_divinerezCLR}		
			|} else 
			
			/call cast_rez ${_tmpID} "${RezSpell}"		
			
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
				
				/call cast_rez ${_tmpID} "${RezSpell}"		
				
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
			
			/call cast_rez ${_tmpID} "${RezSpell}"		
			
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
	
			/call cast_rez ${_tmpID} "${RezSpell}"		
			
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
			
			/call cast_rez ${_tmpID} "${RezSpell}"		
			
			| else /if (${Select[${Me.Class.ShortName},CLR]} && ${Me.Book[Resurrection]}) {
			|	/call cast_rez ${_tmpID} "Resurrection"		
			|} |else /if (${Select[${Me.Class.ShortName},CLR,DRU,PAL,SHM,NEC]} && ${Me.AltAbilityReady[${_rez${Me.Class.ShortName}}]}) {
			|	/call cast_rez ${_tmpID} ${_rez${Me.Class.ShortName}}
			|} 
		/next _count

	/if (${Spawn[${Me.Name} pccorpse radius ${setMaxRezRange}].ID}) {
		/varset _tmpID ${Spawn[${Me.Name} pccorpse radius 40].ID}
		/call cast_rez ${_tmpID} "${RezSpell}"	
	}
	
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
	/declare _count int local 0

	| ignore the people we dont like
	|/if (${lstNoRez.Find[${Spawn[pccorpse ${_tmpID}].DisplayName}]}) {
	|	/call timer_update timer_corpse_${_tmpID}} 30m
	|	/return FALSE
	|}
		
	| get the corpse close to us

	/if (${_rez.Equal[${MassRezSpell}]}) {
		/declare _corpsessInRadius 		int local 0
		/declare _corpseID				int local 0
		/varset _corpsessInRadius ${SpawnCount[pccorpse radius ${setMaxRezRange}]}
		
		/while (${_count} <= ${_corpsessInRadius}) {
			
			/varset _corpseID ${NearestSpawn[${_count}, pccorpse radius ${setMaxRezRange}].ID}
			
			/if (${NearestSpawn[${_count}, pccorpse radius ${setMaxRezRange}].Distance} > 20) {
				/squelch /target ID ${_corpseID}
				/delay 1s ${Target.ID} == ${_corpseID}
				/squelch /corpse
			}
		
			/varcalc _count ${_count}+1
			/delay 1		
		}
	} else {
		/if (${Spawn[pccorpse ${_tmpID}].Distance} <= 100) {
			/squelch /target ID ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}
			/squelch /corpse
		}
	}
	
	/if (!${Me.Gem[${_rez}]}) /call mem_spell FALSE TRUE "${_rez}" 8 TRUE

	| can we AA res or token, maybe spell?
	/if (${Me.AltAbilityReady[${_rez}]} || (${Me.ItemReady[Token of Resurrection]} && ${rezToken}) || ${Me.SpellReady[${_rez}]}) {	

		| res the damn person
		| AA rez
		/if (!${rezToken}) {
			| /if (!${Spawn[pccorpse ${_tmpID}].ID}) /return
			/delay 5s !${Me.Casting.ID}
			/squelch /target ID ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}
			/if (${validate_cast[FALSE, FIND, "${_rez}", ${_tmpID}]}) {
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Rezzing with ${_rez}
				/call core_cast2 "${_rez}" FIND ${_tmpID} FALSE
			}

		| token rez
		} else /if (${rezToken}) {
			/delay 5s !${Me.Casting.ID}
			/squelch /target ID ${_tmpID}
			/delay 1s ${Target.ID} == ${_tmpID}
			/if (${validate_cast[FALSE, item, "Token of Resurrection", ${Me.ID}]}) {	
				/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Rezzing with Token of Resurrection
				/call core_cast2 "Token of Resurrection" item ${_tmpID} FALSE
			}
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

Sub get_corpses
	/declare _count 				int local 1
	/declare _corpse 				int local 0
	/declare _corpsessInRadius 		int local 0
	/declare _radius 				int local 9999
	/declare _corpseTargetID 		int local 0


	/if (${Me.XTarget[1].ID}) {
		/varset _corpseTargetID ${Me.XTarget[1].ID}
		/return ${_corpseTargetID}
	}
	
	|${Spawn[pccorpse radius ${setMaxRezRange}]}

	/varset _corpsessInRadius ${SpawnCount[pccorpse radius ${setMaxRezRange}]}

	/while (${_count} <= ${_corpsessInRadius}) {
		/if (!${NearestSpawn[${_count}, pccorpse radius ${setMaxRezRange}].ID}) /continue
		
		/varset _corpse ${NearestSpawn[${_count}, pccorpse radius ${setMaxRezRange}].ID}

		/if (${_radius} > ${Navigation.PathLength[id ${_corpse}]}) {
			/varset _radius ${Navigation.PathLength[id ${_corpse}]}
			/varset _corpseTargetID ${_corpse}
		}
		
		/varcalc _count ${_count}+1
		/delay 1		
	}
/return ${_corpseTargetID}
|***
 *	DES: check  health
 *	USE: /call check_hurt [DEBUG T/F] [group|pet|xtarget|self|mypet]} || ${check_hurt[DEBUG, group|pet|xtarget|self|mypet]}
 *	NOTE: shared by PAL,DRU,CLR,SHM this returns the # of "hurt" for the group check you request as the pass/fail marker
 ***|
sub check_hurt(bool _debug, string _type, int _hpLimit)

	/declare _count		 				int local 0
	/declare countGroupHeal				int local 3
	/declare hurtCount	 				int local 0

	| check group hurt
	/if (${_type.Equal[group]}) {
		/for _count 0 to ${Group}
		
			/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
			/if (${Group.Member.OtherZone}) /continue
			
			/if (${Group.Member[${_count}].Distance} <= 200 && ${Group.Member[${_count}].PctHPs} < ${_hpLimit}) {
				/varcalc hurtCount ${hurtCount}+1
			}
			/if (${hurtCount} >= ${countGroupHeal}) /break

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

|***
 *	DES: check  health
 *	USE: /call check_hurt [DEBUG T/F] [group|pet|xtarget|self|mypet]} || ${check_hurt[DEBUG, group|pet|xtarget|self|mypet]}
 *	NOTE: shared by PAL,DRU,CLR,SHM this returns the # of "hurt" for the group check you request as the pass/fail marker

Sub get_heal_target(int _hpLimit)

	/declare _worstHurtId		int local 0
	/declare _count		     	int local 0
	
	/if (${Group.MercenaryCount}) {

		| Includes mercs
		/for _count 0 to ${Group}
		
			/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		
			/if (${Group.Member[${_count}].Distance} > 200 || ${Group.Member[${_count}].PctHPs} > ${_hpLimit}) /continue

			/if (${Group.Member[${_count}].PctHPs} < ${_hpLimit}) {
				/varset _worstHurtId ${Group.Member[${_count}].ID}
				/varset _hpLimit ${Group.Member[${_count}].PctHPs}
			}

		/next _count

	} else {
		| This only checks pcs
		/if (${Spawn[${WorstHurt[group,1,200,FALSE]}].Type.NotEqual[Corpse]} && ${Spawn[${WorstHurt[group,1,200,FALSE]}].PctHPs} < ${_hpLimit}) {
			/varset _worstHurtId ${Spawn[${WorstHurt[group,1,200,FALSE]}].ID}
		}
	}

/return ${_worstHurtId}
 ***|

Sub get_heal_target(int _hpLimit)

	/declare _worstHurtId		int local 0
	/declare _count		     	int local 0
	
	/for _count 0 to ${Group}
	
		/if (${Group.Member[${_count}].Type.Equal[Corpse]}) /continue
		/if (${Group.Member.OtherZone}) /continue
		/if (${Group.Member[${_count}].Type.Equal[Mercenary]}) {
			/if (${Mercenary.State.Equal[DEAD]} || ${Mercenary.State.Equal[SUSPENDED]}) /continue
		}
	
		/if (${Group.Member[${_count}].Distance} > 200 || ${Group.Member[${_count}].PctHPs} > ${_hpLimit}) /continue

		/if (${Group.Member[${_count}].PctHPs} < ${_hpLimit}) {
			/varset _worstHurtId ${Group.Member[${_count}].ID}
			/varset _hpLimit ${Group.Member[${_count}].PctHPs}
		}

	/next _count

/return ${_worstHurtId}

Sub validate_tank_heal(int _hpLimit)

	/if (${Group.MaintTank.Type.Equal[Mercenary]}) {
		/if (${Mercenary.State.Equal[DEAD]} || ${Mercenary.State.Equal[SUSPENDED]}) /return FALSE
	}

	/if (${Spawn[id ${Group.MainTank.ID} pccorpse radius 150].ID}) /return FALSE

	/if (${Spawn[id ${Group.MainTank.ID}].Type.Equal[Corpse]}) /return FALSE

	/if (${Target.ID} != ${Group.MainTank.ID}) {
		/target id ${Group.MainTank.ID}
		/delay 1s ${Target.ID} == ${Group.MainTank.ID}
		/delay 5
	}

	/if (${Target.Distance} > 200) /return FALSE

	/if (${Target.PctHPs} >= ${_hpLimit}) {
		/return TRUE
	} else {
		/return FALSE
	}
	
/return FALSE


|***
 *	DES: check  health
 *	USE: /call check_hurt [DEBUG T/F] [group|pet|xtarget|self|mypet]} || ${check_hurt[DEBUG, group|pet|xtarget|self|mypet]}
 *	NOTE: shared by PAL,DRU,CLR,SHM this returns the # of "hurt" for the group check you request as the pass/fail marker
 ***|
sub setup_skill_melee(bool _debug)

	/if (${Select[${Me.Class.ShortName},BRD,ROG,MNK,BER]} && ${Me.AltAbility[Intimidation].Rank} >= 2) {
		/varset intimidation TRUE
		/if (!${Skill[Intimidation].Auto}) /autoskill Intimidation
	}

	/if (${Select[${Me.Class.ShortName},BRD]}) {
		/varset kick TRUE
		/if (!${Skill[Kick].Auto}) /autoskill Kick
	}

	/if (${Select[${Me.Class.ShortName},BST]}) {
		/if (${Me.Level} < 70) {
			/varset kick FALSE
		} else {
			/varset eaglestrike TRUE
			/varset tigerclaw TRUE
			/varset kick FALSE
			/if (!${Skill[Eagle Strike].Auto}) /autoskill Eagle Strike
			/if (!${Skill[Round Kick].Auto}) /autoskill Round Kick
		}	
	}

	/if (${Select[${Me.Class.ShortName},ROG]}) {
		/if (${Me.Level} >= 10) {
			/varset backstab TRUE
			/if (!${Skill[Backstab].Auto}) /autoskill Backstab
		}
	}

	/if (${Select[${Me.Class.ShortName},BER]}) {
		/if (${Me.Level} >= 6) {
			/varset frenzy TRUE
			/if (!${Skill[Frenzy].Auto}) /autoskill Frenzy
		}
	}

	/if (${Select[${Me.Class.ShortName},MNK]}) {
		/if (${Me.Level} >= 70) {
			/varset tigerclaw TRUE
			/if (!${Skill[Tiger Claw].Auto}) /autoskill Tiger Claw
		}	
		
		/if (${Me.Level} >= 30) {
			/varset flyingkick TRUE
			/varset roundkick FALSE
			/varset kick FALSE
			/if (!${Skill[Flying Kick].Auto}) /autoskill Flying Kick
		} else /if (${Me.Level} >= 5) {
			/varset kick FALSE
			/varset roundkick TRUE
		} else /if (${Me.Level} < 5) {
			/varset kick TRUE
		} 
	}

	/if (${Select[${Me.Class.ShortName},WAR,PAL,SHD]}) {
		/varset bash TRUE
		/if (!${Skill[Bash].Auto}) /autoskill Bash
	}

	|/if (${Me.AbilityReady[Disarm]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD,BER,ROG,MNK,BRD,BST]}) {
	|	/if (!${Skill[Disarm].Auto}) /autoskill Disarm
	|}

	/if (${Select[${Me.Class.ShortName},BER,BRD,MNK,ROG,BST]}) {
		/if (${PowerLevel} && ${Me.ID} != ${Group.MainTank.ID}) {
			/varset autoAssistAt 20
			/varset assistRange 55
		} else {
			/varset autoAssistAt 100
			/varset assistRange 55
		}
	}
	/if (${Select[${Me.Class.ShortName},WAR,PAL,SHD]}) {
		/if (${PowerLevel} && ${Me.ID} != ${Group.MainTank.ID}) {
			/varset autoAssistAt 20
			/varset assistRange 55
		} else {
			/varset autoAssistAt 100
			/varset assistRange 55
		}
	}

	/if (${Select[${Me.Class.ShortName},WIZ,DRU,MAG,SHM]}) {
		/if (${PowerLevel} && ${Me.ID} != ${Group.MainTank.ID}) {
			/varset autoAssistAt 60
			/varset assistRange 55
		} else {
			/varset autoAssistAt 100
			/varset assistRange 55
		}
	}

	/if (${Select[${Me.Class.ShortName},ENC]}) {
		/if (${PowerLevel} && ${Me.ID} != ${Group.MainTank.ID}) {
			/varset autoAssistAt 60
			/varset assistRange 55
		} else {
			/varset autoAssistAt 100
			/varset assistRange 55
		}
	}

/return

|***
 *	DES: use base melee discs
 *	USE: /call use_skill_melee TARGET
 *	NOTE: 
 ***|
sub use_skill_melee(int _tmpID, bool _debug)
	
	/if (${Target.ID} != ${_tmpID}) {
		/squelch /target ID ${_tmpID}
		/delay 5 ${Target.ID} == ${_tmpID}
	}

	| taunt /onoff agro
	/if (${Me.ID} == ${Group.MainTank.ID} && ${Me.AbilityReady[Taunt]} && ${Spawn[id ${_tmpID}].Distance} <= 18 && ${Me.TargetOfTarget.Name.NotEqual[${Me.DisplayName}]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD]}) {
		/if (${Target.ID}) /doability Taunt
	}
	
	| disarm
	/if (!${Skill[Disarm].Auto}) {
		/if (${Me.AbilityReady[Disarm]} && ${Spawn[id ${_tmpID}].Distance} <= 15 && ${Select[${Me.Class.ShortName},WAR,SHD,PAL,MNK]}) {
			/if (${Target.ID}) /doability Disarm
		}
	}
		
	| kick
	/if (${Bool[${kick}]} && !${Skill[Kick].Auto}) {
	 	/if (${Me.AbilityReady[Kick]} && ${Spawn[id ${_tmpID}].Distance} <= 15) {
			/if (${Target.ID}) /doability Kick
		}
	}
	
	| bash
	/if (${Bool[${bash}]} && !${Skill[Bash].Auto}) {
		/if (${Me.AbilityReady[Bash]} && ${Spawn[id ${_tmpID}].Distance} <= 15) {
			/if (${Target.ID}) /doability Bash
		}
	}
	
	| Intimidation
	/if (${Select[${Me.Class.ShortName},BRD,ROG,MNK,BER]}) {
		/if (${intimidation} && ${Bool[${intimidation}]}) {
			/if (${Me.AbilityReady[Intimidation]} && ${Spawn[id ${_tmpID}].Distance} <= 15) {
				/if (${Target.ID}) /doability Intimidation		
			}
		}
	}

	| Zerker only skill
	/if (${Select[${Me.Class.ShortName},BER]}) {
		/if (${frenzy} && !${Skill[Frenzy].Auto}) {
			/if (${Me.AbilityReady[Frenzy]} && ${Spawn[id ${_tmpID}].Distance} <= 13) {
				/if (${Target.ID}) /doability Frenzy
			}
		}
	}

	| rogue only skill
	/if (${Select[${Me.Class.ShortName},ROG]}) { 
		/if (${backstab} && !${Skill[Backstab].Auto}) {
			/if (${Me.AbilityReady[Backstab]} && ${Spawn[id ${_tmpID}].Distance} <= 13) {
				/if (${Target.ID}) /doability Backstab
			}
		}
	}
	
	| monk/bst only skill 
	/if (${Select[${Me.Class.ShortName},MNK,BST]} && ${Spawn[id ${_tmpID}].Distance} <= 15) {
		| fist
		/if (${Bool[${dragonpunch}]} && !${Skill[Dragon Punch].Auto} && (${Me.AbilityReady[Dragon Punch]} || ${Me.AbilityReady[Tail Rake]})) {
			/if (${Target.ID}) /doability "Dragon Punch"
		} else /if (${Bool[${eaglestrike}]} && !${Skill[Eagle Strike].Auto} && ${Me.AbilityReady[Eagle Strike]}) {
			/if (${Target.ID}) /doability "Eagle Strike"
		} else /if (${Bool[${tigerclaw}]} && !${Skill[Tiger Claw].Auto} && ${Me.AbilityReady[Tiger Claw]}) {
			/if (${Target.ID}) /doability "Tiger Claw"
		}
		| kick
	 	/if (${Bool[${flyingkick}]} && !${Skill[Flying Kick].Auto} && ${Me.AbilityReady[Flying Kick]}) {
			/if (${Target.ID}) /doability "Flying Kick"
		} else /if (${Bool[${roundkick}]} && !${Skill[Round Kick].Auto} && ${Me.AbilityReady[Round Kick]}) {
			/if (${Target.ID}) /doability "Round Kick"
		}		
	}

/return

|***
 *	DES: creates observers
 *	USE: /call observer [DEBUG T/F] [string of things to observe] [add|drop] [SILENT T/F]
 *	NOTE: the variable passed to this sub, _observer, is a list. 
 *	NOTE: the first item in the list is the tlo, all the other items are members you want to check
 *	NOTE: if you want to use more then 1 TLO, call the sub multiple times with different lists
 ***|

sub set_observers(bool _debug, string _observer, string _action, bool _silent)

	/declare _countT 					int 		local 0
	/declare _countE					int 		local 0
	/declare _actionD					string	local FALSE
	/declare _actionO					string	local FALSE
	/declare _name		 				string 	local FALSE
	/declare _element					string	local FALSE
	/declare _TLO						string 	local ${lstObserver${_observer}.Arg[1,|]}
	/declare _timestart					int			local 0
	/declare _timeend					int			local 0
	/declare DanNetMacroChannel 		string local all

	| correct/check the action variable
	/if (${_action.Equal[drop]}) {
		/varset _actionO -drop
		/varset _actionD Drop
	} else /if (${_action.Equal[add]}) {
		/varset _actionO
		/varset _actionD Add
	} else {
		/return FALSE
	}

	
	/varset _timestart ${MacroQuest.Running}
	
	| cycle the toons inside the dan group
	/for _countT 1 to ${DanNet.PeerCount[${DanNetMacroChannel}]}
		/varset _timestart ${MacroQuest.Running}
		/varset _name ${DanNet.Peers[${DanNetMacroChannel}].Arg[${_countT},|]}

		| loop the string, skip the first one
		/for _countE 2 to ${lstObserver${_observer}.Count[|]}

			| set the element
			/varset _element ${lstObserver${_observer}.Arg[${_countE},|]}
		
			| existing
			/if (${_action.Equal[add]}) {
				/if (${DanNet[${_name}].ObserveSet["${_TLO}.${_element}"]} && ${Defined[${_name}_${_element}]}) /continue 
			}
			
			| create or delete the variables as we need
			/if (${_action.Equal[drop]}) {
				/if (${Defined[${_name}_${_element}]}) /deletevar ${_name}_${_element}
			} else /if (${_action.Equal[add]}) {
				/if (!${Defined[${_name}_${_element}]}) /declare ${_name}_${_element} string outer
			}

			| set observer
			/dobserve ${_name} -q "${_TLO}.${_element}" -o ${_name}_${_element} ${_actionO}

		/next _countE

		/varset _timeend ${MacroQuest.Running}

	/next _countT

/return


Sub check_cast_events(string _spell, string _event, int _tmpID)
	
	/doevents ${_event}

	/if (!${Select[${castReturn},${_event}]}) /return
	
	DEBUG Doing event ${_event}

	/if (${_event.Equal[CAST_IMMUNE]}) {
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \ar ${Target.Name} \ax is IMMUNE to =>> \ag ${_spell} \ax <<=
			
		/if (!${immuneSet.Add[${_tmpID}]}) {
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Set Add of ${_tmpID} failed.
		}
	}

	/if (${_event.Equal[CAST_CANNOTCAST]}) {
		/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \ar ${Target.Name} \ax is \ar UNPULLABLE \ax with =>> \ag ${_spell} \ax <<=
		/squelch /alert add 1 id ${_tmpID}
		/varset cannotCast TRUE

	}

	/if (${_event.Equal[CAST_FIZZLE]}) {
		/return TRUE
	}

	/if (${_event.Equal[CAST_PULLERCANNOTSEE]}) {
		/if (${Spawn[id ${_tmpID}].Distance} > 15) {
			/call core_cast2 "${pullAbility}" FIND ${_tmpID} FALSE
		} else {
			/call core_cast2 "${pullAbility}" FIND ${_tmpID} FALSE
			/if (${Navigation.Active}) /nav stop
			/stick 12 moveback loose
			/attack on
			/delay 3s ${Me.XTarget}
			/stick off
		}
	}

	/if (${_event.Equal[CANNOT_HIT]}) {
		/if (${Navigation.Active}) /nav stop
		/if (${Stick.Status.Equal[ON]}) /stick off
		/nav id ${_tmpID}
		/while (${Navigation.Active}) {
			/call core_cast2 "${pullAbility}" FIND ${_tmpID} FALSE
			/if (${Me.XTarget}) /return
			/delay 5
		}
	}

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


|----------------------------------------------------------------------------
|- SUB: ignore_mobs_to_pull
|---------------------------------------------------------------------------- 
Sub ignore_mobs_to_pull
	/declare _count 	int local 0
	/declare ignoreList string local NULL
	/declare Ignore 	string local NULL
	/declare fileLoc 	string local IHCMercs\IgnoreMobs.ini 

	/squelch /alert clear 1

	/varset Ignore ${Ini[${fileLoc},${Zone.ShortName},Ignore]}

	/if (${Ignore.Equal[NULL]}) {
		/ini "${fileLoc}" "${Zone.ShortName}" "Ignore" "NONE"
		/varset Ignore NONE
	}

	/if (!${Ignore.Equal[NULL]}) {
		/if (!${Ignore.Count[|]}) {
			DEBUG Adding ${Ignore} to ignore
			/squelch /alert add 1 ${Ignore}
		} else /if (${Ignore.Count[|]}) {
			/for _count 1 to ${Math.Calc[${Ignore.Count[|]}+1]}
				DEBUG Adding ${Ignore.Arg[${_count},|]} to ignore
				/squelch /alert add 1 ${Ignore.Arg[${_count},|]}
			/next _count
		}
	}
/return

Sub Bind_ad(string Command)
	
	|		Write: /inix FileName Section Key Value
	| 		https://www.macroquest2.com/wiki/index.php/TLO:Ini
	|		https://www.redguides.com/community/threads/mq2inix.68308/
	|		https://www.redguides.com/community/threads/pocketfarm-mac.67122/

	/if (${Command.Equal[reload_ignore]}) {
		/docommand /dgt \arReloading ignore list.
		/call ignore_mobs_to_pull
	} else /if (${Command.Equal[ignore]}) {
		/docommand /dgt \awAdding \ar${Target.CleanName} \awto ignore and reloading ignore list.
		| https://www.redguides.com/community/threads/ignore-mobs.70532/
		/inix "IgnoreMobs.ini" "${Zone.ShortName}" "Ignore" "${Target.ID}|"
		/alert add 1 "${Target.CleanName}"
	} else /if (${Command.Equal[session_ignore]}) {
		/docommand /dgt \awAdding \ar${Target.CleanName} \awto session ignore.
		/alert add 1 "${Target.CleanName}"
	}

/return
|**
	/if (${Command.Equal[load]}) {
		/message \arReloading INI.
		/call IniFile
	} else /if (${Command.Equal[clear]}) {
		/if (${Command2.Equal[ignore]}) {
			/squelch /alert clear 1
			/message \arIgnore list cleared.
		}
		/if (${Command2.Equal[pull]}) {
			/squelch /alert clear 10
			/message \arPull list cleared.
		}	
	} else /if (${Command.Equal[list]}) {
		/alert list 1
		/alert list 10
	} else /if (${Command.Equal[radius]}) {
		/varset Radius ${Command2}
		/if (${CampOn}) {
			/squelch /maploc ${CampY} ${CampX} Size 20 width 5 color 0 0 255 radius ${Radius} color 0 0 255
			/squelch /mapfilter SpellRadius 0
		} else {
			/squelch /mapfilter SpellRadius ${Radius}
		}
		/message \agSetting Radius to \at ${Radius}
		/ini "PocketFarm.ini" "${Zone.ShortName}" "Radius" "${Radius}"
	} else /if (${Command.Equal[zradius]}) {
		/varset ZRadius ${Command2}
		/message \agSetting Z-Radius to \at${ZRadius}
		/ini "PocketFarm.ini" "${Zone.ShortName}" "ZRadius" "${ZRadius}"
	} else /if (${Command.Equal[ignore]}) {
		/alert add 1 "${Command2}"
	} else /if (${Command.Equal[pull]}) {
		/alert add 10 "${Command2}"
	} else /if (${Command.Equal[go]}) {
		/varset goFarming true
		/message PocketFarm \agGO
	} else /if (${Command.Equal[pause]}) {
		/varset goFarming false
		/message PocketFarm \arPause
	} else {
		/message \ag Commands while running:
		/message \ag- \at/pkf go \agmakes PocketFarm start farming
		/message \ag- \at/pkf pause \agmakes PocketFarm pause farming, but will self defend.
		/message \ag- \at/pkf list \agShows both ignore and pull lists
		/message \ag- \at/pkf ignore "<spawn search>" \ag- Add spawns to temp ignore list, remember to use " ". \arWill not be saved in ini.
		/message \ag- \at/pkf pull "<spawn search>" \ag- Add spawns to temp pull list, remember to use " ". \arWill not be saved in ini.
		/message \ag- \at/pkf clear <ignore/pull> ## \ag- Clear the ignore or pull list.
		/message \ag- \at/pkf radius ## \ag- Change the radius around you to look for mobs in.
		/message \ag- \at/pkf zradius ## \ag- Change the  Z radius.
		/message \ag- \at/pkf load \ag load reload the ini.
	}
**|

|----------------------------------------------------------------------------
|- SUB: mezz_xtarget
|---------------------------------------------------------------------------- 
Sub mezz_xtarget(string _mezAE, string _mezSingle)
	/declare _count				 	int local 1
	/declare _numberOfSpawn 	 	int local 0
	/declare _mezAERange		int local 0

	| Is there something to mez or debuff?
	/if (${Me.XTarget} < 2) /return FALSE
	/if (!(${Me.Gem[${_mezAE}]} || ${Me.Gem[${_mezSingle}]})) /return

	/call get_target
	
	/attack off

	/while (${Target.Distance3D} > 150 && !${Spawn[id ${Target.ID}].LineOfSight}) {
		/delay 5
	}

	/if (${Select[${Me.Class.ShortName},ENC]}) {
		/varset _mezAERange ${Spell[${_mezAE}].AERange}
	} else /if (${Select[${Me.Class.ShortName},BRD]}) {
		/varset _mezAERange ${Spell[${_mezAE}].AERange}
		/varcalc _mezAERange ${_mezAERange} + 20
	}

	/if (${Me.Gem[${_mezAE}]}) {
		| How many mobs are there?
		/if (${SpawnCount[npc targetable noalert 1 radius ${_mezAERange} zradius ${_mezAERange}]} > 1) {
			
			/if (${Select[${Me.Class.ShortName},BRD]}) {
				/if (${Me.Casting.Name.NotEqual[${_mezAERange}]}) /call pulse_stop 18
			}

			/for _count 1 to ${Me.XTarget}

				| If xtarget is not mezzed, add it to count
				/if (${If[${Select[${Me.XTarget[${_count}].Animation},110,26,32,71,72,111]}, 0, 1]} == 1) {
					/varcalc _numberOfSpawn ${_numberOfSpawn}+1
				}

			/next _count
			
			| If there are more than 1 mobs counted then aoe mez
			/if (${_numberOfSpawn} > 1) {
				/if (${Me.CombatState.Equal[COMBAT]}) /attack off
				/delay 1s

				/if (${Select[${Me.Class.ShortName},ENC]}) {
					/if (${validate_cast[FALSE, spell, "${_mezAE}", ${Target.ID}]}) {
						/if (${verbose${Me.Class.ShortName}}) /docommand /dgt AoE mezzing with =>> \ag ${_mezAE} \ax <<=
						/call core_cast2 "${_mezAE}" spell ${Target.ID} FALSE
					}
				} else /if (${Select[${Me.Class.ShortName},BRD]}) {
					/if (${validate_cast[FALSE, pulse, "${_mezAE}", ${Target.ID}]}) {
						/if (${verbose${Me.Class.ShortName}}) /docommand /dgt AoE mezzing with =>> \ag ${_mezAE} \ax <<=
						/call core_cast2 "${_mezAE}" pulse ${Target.ID} FALSE
					}
				}
			}
		}
	}
	
	
	/if (${Me.Gem[${_mezSingle}]}) {

		/if (${Me.CombatState.Equal[COMBAT]}) /attack off

		| Loop through xtarget if we should mezz adds, even if we just did aoe mezz
		/for _count 1 to ${Me.XTarget}

			/if (${immuneSet.Contains[${Me.XTarget[${_count}].ID}]}) /continue

			| If target is too far away then skip
			/if (${Me.XTarget[${_count}].Distance} > 200) /continue

			| If the xtarget is already mezzed then skip
			/if (${If[${Select[${Me.XTarget[${_count}].Animation},110,26,32,71,72,111]}, 0, 1]} == 0) /continue

			| Query MA and MT on what is currently being killed
			/call Gquery ${Group.MainAssist.Name.Lower} "Target.ID" "MATargetID" "int"
			/call Gquery ${Group.MainTank.Name.Lower} "Target.ID" "MTTargetID" "int"

			| If xtarget is being targetted by MA or MT then skip
			/if (${Me.XTarget[${_count}].ID} == ${MATargetID} || ${Me.XTarget[${_count}].ID} == ${MTTargetID}) /continue

			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt MA Target is \ar${MATargetID}
			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt MT Target is \ar${MTTargetID}

			/if (${Me.CombatState.Equal[COMBAT]}) /attack off
			/if (${Stick.Status.Equal[ON]}) /stick off
			/if (${Stick.Active}) /stick off
			/delay 2s !${Stick.Status.Equal[ON]}
			/delay 2s !${Stick.Active}
			/attack off
			| If not then target it
			/target id ${Me.XTarget[${_count}].ID}
			/delay 2s ${Me.XTarget[${_count}].ID} == ${Target.ID}

			/if (${verbose${Me.Class.ShortName}}) /docommand /dgt MY Target is \ar${Target.Name} - ${Target.ID}
			/delay 1s

			/if (${Spawn[id ${Target.ID}].Body.Name.Equal[Giant]}) {
				/if (!${immuneSet.Add[${_tmpID}]}) {
					/if (${verbose${Me.Class.ShortName}}) /docommand /dgt \aw Set Add of ${_tmpID} failed.
				}
				/continue
			}

			/if (${Select[${Me.Class.ShortName},ENC]}) {
				| If target is not tashed then tash
				/if (!${Target.Tashed.ID} && !${Target.Buff[${TashSpell}].ID}) {
					/if (${validate_cast[FALSE, spell, "${TashSpell}", ${Target.ID}]}) /call core_cast2 "${TashSpell}" spell ${Target.ID} FALSE
				}

				| If target is not mezzed then mez
				/if (!${Target.Mezzed.ID} && !${Target.Buff[${_mezSingle}].ID}) {
					
					/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Mezzing \ar${Target.Name} \ax with =>> \ag${_mezSingle} \ax <<=
					/call core_cast2 "${_mezSingle}" spell ${Target.ID} FALSE
					/call check_cast_events "${_mezSingle}" CAST_IMMUNE ${Target.ID}
					
				}
			} else /if (${Select[${Me.Class.ShortName},BRD]}) {

				/if (${Me.Casting.Name.NotEqual[${_mezSingle}]}) /call pulse_stop 18
				
				/call pulse_stop pulse_line_start
				/delay 1s
				| If target is not mezzed then mez
				/if (!${Target.Mezzed.ID} && !${Target.Buff[${_mezSingle}].ID} && ${Stick.Status.Equal[OFF]}) {
					
					/if (${verbose${Me.Class.ShortName}}) /docommand /dgt Mezzing \ar${Target.Name} \ax with =>> \ag${_mezSingle} \ax <<=
					/call core_cast2 "${_mezSingle}" pulse ${Target.ID} FALSE
					/call check_cast_events "${_mezSingle}" CAST_IMMUNE ${Target.ID}
					
				}
				/call get_target
			}

			/delay 1s

		/next _count
		/if (${Defined[MATargetID]}) /deletevar MATargetID
		/if (${Defined[MTTargetID]}) /deletevar MTTargetID
	}

	/call get_target

/return