|-ihcmez.inc
|- Version 2.0
|- Updated: 4/25/2019
|-------------------------------------------------------------------------------------
|- SUB: Add CC Target
|-------------------------------------------------------------------------------------
Sub AddCCTarget(int AddMobID)
    /if (!${AddMobID}) /return
	/if (${MezMobCount}>${MaxMezCount}) {
		/echo Max Mez Limit Reached
		/return
	}
    /declare i int local 1
	:newcctarget 
	/if (!${Defined[MezTimer${i}]} && !${Defined[CCTarget${i}Info]} && !${Defined[MezCount${i}]}) {
		/declare CCTarget${i}Info string outer ${Spawn[${AddMobID}].ID}|${Spawn[${AddMobID}].Level}|${Spawn[${AddMobID}].CleanName}| 
		/declare MezTimer${i} timer outer 0
		/declare MezCount${i} int outer 0
		/varcalc MezMobCount ${MezMobCount}+1
	} else {
		/varcalc i ${i}+1
		/goto :newcctarget
	}
	/if (${i}>${MezCheckElements}) {
		/varset MezCheckElements ${i}
	}
	/varset NewTargetAdd 1
/return
|-------------------------------------------------------------------------------------
|- SUB: Remove CC Target
|-------------------------------------------------------------------------------------
Sub RemoveCCTarget(int ArNum)
	/if (${MezImmuneIDs.Find[|${CCTarget${ArNum}Info.Arg[1,|]}]}) /varset MezImmuneIDs ${MezImmuneIDs.Replace[|${CCTarget${ArNum}Info.Arg[1,|]},]}
	/if (${Defined[CCTarget${ArNum}Info]}) /deletevar CCTarget${ArNum}Info
	/if (${Defined[MezCount${ArNum}]}) /deletevar MezCount${ArNum}
    /if (${Defined[MezTimer${ArNum}]}) {
		/deletevar MezTimer${ArNum}
		/varcalc MezMobCount ${MezMobCount}-1
		/if (${MezMobCount}==0) /varset MezCheckElements 0
	}
/return
|-------------------------------------------------------------------------------------
|-   Sub MezRadar
|-------------------------------------------------------------------------------------
Sub MezRadar
    /declare NMMob int local 0
    /declare i int local 1
	/declare ii int local
	/declare iii int local
	/declare NewMobToMez int local 0
    /varset MezMobAECount 0
    /varset MezAEClosest 0
	|-Code below is an attempt to expand beyond the 13 target limit of Xtarget. 2/14/18 added check for npcpets
		:loopradar
		/if (${NearestSpawn[${i},npc radius ${MezWatchRadius} zradius 15 range ${MezMinLevel} ${MezMaxLevel} targetable playerstate 4].ID} || ${NearestSpawn[${i},npcpet radius ${MezWatchRadius} zradius 15 range ${MezMinLevel} ${MezMaxLevel} targetable playerstate 4].ID}) {
			/if (${Defined[CCTarget${i}Info]}) {
				/if (${Spawn[${CCTarget${i}Info.Arg[1,|]}].Type.Equal[Corpse]} || ${Spawn[${CCTarget${i}Info.Arg[1,|]}].PctHPs}<=0 || !${Spawn[${CCTarget${i}Info.Arg[1,|]}].ID}) /call RemoveCCTarget ${i}
			}
			/if (${NearestSpawn[${i},npc radius ${MezWatchRadius} zradius 15 range ${MezMinLevel} ${MezMaxLevel} targetable playerstate 4].ID}) {
				/varset NMMob ${NearestSpawn[${i},npc radius ${MezWatchRadius} zradius 15 range ${MezMinLevel} ${MezMaxLevel} targetable playerstate 4].ID}
			} else /if (${NearestSpawn[${i},npcpet radius ${MezWatchRadius} zradius 15 range ${MezMinLevel} ${MezMaxLevel} targetable playerstate 4].ID}) {
				/varset NMMob ${NearestSpawn[${i},npcpet radius ${MezWatchRadius} zradius 15 range ${MezMinLevel} ${MezMaxLevel} targetable playerstate 4].ID}
			}
			/varcalc NewMobToMez ${NewMobToMez}+1	
            |- Setup closest mob for AE mez target
            /if (!${MezAEClosest} && ${Spawn[${NMMob}].Distance}<=${MezRadius}) /varset MezAEClosest ${NMMob}
            /if (${MezAEClosest} && ${Spawn[${NMMob}].Distance}<${Spawn[${MezAEClosest}].Distance} && ${Spawn[${NMMob}].Distance}<=${MezRadius}) /varset MezAEClosest ${NMMob}
            /if (${Spawn[${NMMob}].Distance}<=${MezRadius}) /varcalc MezMobAECount ${MezMobAECount}+1 
            /if (${NMMob} && (${Spawn[${NMMob}].Type.Equal[Corpse]} || !${Spawn[${NMMob}].ID} || ${Spawn[${NMMob}].Distance}>${MezWatchRadius})) {
				/if (${MezCheckElements}>0) {
					/for ii 1 to ${MezCheckElements}
						/if (${Defined[CCTarget${ii}Info]}) {
							/if (${CCTarget${ii}Info.Arg[1,|].Find[${NMMob}]}) {
								/call RemoveCCTarget ${ii}
								/goto :loop2done
							}
						}
					/next ii
					:loop2done
				}
			}
			/if (${NewMobToMez}>0) {
				/if (${MezCheckElements}>0) {
					/for iii 1 to ${MezCheckElements}
						/if (${Defined[CCTarget${iii}Info]}) {
							/if (${CCTarget${iii}Info.Arg[1,|].Find[${NMMob}]}) {
								/goto :loop3done
							}
						}
					/next iii
				}
				/if (${NMMob}!=0 && !${Spawn[${NMMob}].Name.Equal[NULL]}) {
					/call AddCCTarget ${NMMob}
					/if (${Me.Casting.ID}!=${Spell[${MezSpell}].ID}) /interrupt
				}
				:loop3done
            }
            /varset NMMob 0
			/varcalc i ${i}+1
			/goto :loopradar
        }
/return
|-------------------------------------------------------------------------------------
|- SUB: Do Mez Stuff
|-------------------------------------------------------------------------------------
Sub DoMezStuff
    /doevents 
    /declare i int local 0
    /declare j int local 0
	/varset MezWait 0
    |- Reset skip mez on health setting if tank dies to 1%
    /if (!${Spawn[=${assistname}].ID}) /varset MezStopHPs 1
    /call MezRadar
	/if (${MezCheckElements}==0) /return
   /if (${Select[${MezOn},1,3]} && ((${MezAECount}>0 && ${MezMobAECount}>=${MezAECount}) || ${SpawnCount[npc radius ${MezRadius} targetable los playerstate 4]}>=${MezAECount}) && ${MezAETimer}==0 && ${Select[${Me.Class.ShortName},BRD,ENC]})  {
		/if (${SpawnCount[npc xtarhater loc ${Spawn[id ${MezAEClosest}].X} ${Spawn[id ${MezAEClosest}].Y} radius ${Spell[${MezAEAA}].AERange}]}>=${SpawnCount[npc loc ${Spawn[id ${MezAEClosest}].X} ${Spawn[id ${MezAEClosest}].Y} radius ${Spell[${MezAEAA}].AERange}]} && ${UseAEAAMez} && ${Me.AltAbilityReady[${MezAEAA}]}) {
			/call AAMezAE ${MezAEClosest}
		} else /if (${SpawnCount[npc xtarhater loc ${Spawn[id ${MezAEClosest}].X} ${Spawn[id ${MezAEClosest}].Y} radius ${Spell[${MezAESpell}].AERange}]}>=${SpawnCount[npc loc ${Spawn[id ${MezAEClosest}].X} ${Spawn[id ${MezAEClosest}].Y} radius ${Spell[${MezAESpell}].AERange}]}) {
			/call MezMobsAE ${MezAEClosest}
		}
    }
	/for i 1 to ${MezCheckElements} 
        /if (!${Me.SpellReady[${MezSpell}]}) {
			/varset MezWait 1
            /return
        }
		/if (!${Defined[CCTarget${i}Info]}) {
            /goto :SkipMez
        }
        /if (${CCTarget${i}Info.Arg[1,|].Equal[NULL]}) {
            /goto :SkipMez
        }
        /if (${CCTarget${i}Info.Arg[3,|].Find[corpse]} || !${Spawn[${CCTarget${i}Info.Arg[1,|]}].ID} || ${Spawn[${CCTarget${i}Info.Arg[1,|]}].Type.Equal[Corpse]}) {
            /call RemoveCCTarget ${i}
			/goto :SkipMez
        }
        /if (${Spawn[${CCTarget${i}Info.Arg[1,|]}].Distance}>=${MezRadius}) {
            /goto :SkipMez
        }
        /if (${Spawn[${CCTarget${i}Info.Arg[1,|]}].ID}==${Me.GroupAssistTarget.ID} && ${Spawn[=${assistname}].ID}) {
			/goto :SkipMez
        }
        /if (${Spawn[${CCTarget${i}Info.Arg[1,|]}].PctHPs}<${MezStopHPs}) {
            /goto :SkipMez
        }
        /if (${CCTarget${i}Info.Arg[2,|]}>${MezMaxLevel} || ${CCTarget${i}Info.Arg[2,|]}<${MezMinLevel}) {
            /goto :SkipMez
        }
        /if (!${Spawn[${CCTarget${i}Info.Arg[1,|]}].LineOfSight}) {
            /goto :SkipMez
        }
        /if (${Spawn[${CCTarget${i}Info.Arg[1,|]}].Body.Name.Equal[Giant]}) {
            /goto :SkipMez
        } 
        /if (${Me.CurrentMana}<${Spell[${MezSpell}].Mana}) {
            /goto :SkipMez
        }
        /if (${MezTimer${i}} > 0) {
            /goto :SkipMez
        }
        /if (${MezMobCount}<=1 && ${Spawn[=${assistname}].ID} && (${Spawn[=${assistname}].Type.Equal[Mercenary]} || ${Spawn[=${assistname}].Type.Equal[Pet]})) {
            /goto :SkipMez
        }
        /if (${MezImmuneIDs.Find[|${CCTarget${i}Info.Arg[1,|]}]}) {
            /goto :SkipMez
        }
        /if (${Select[${MezOn},1,2]}) {
            /call MezMobs ${CCTarget${i}Info.Arg[1,|]} ${i}
        }
        :SkipMez
    /next i
/return
|-------------------------------------------------------------------------------------
|- SUB: Mez Mobs AE
|-------------------------------------------------------------------------------------
Sub MezMobsAE(int AEMezID)
    /declare i int local 1
    /declare WasChasing int local 0
    | Enchanter AE mez code
    /if (${Me.Class.Name.Equal[Enchanter]}) {
        /if (${ChaseAssist}) {
            /varset ChaseAssist 0
            /varset WasChasing 1
            /squelch /stick off
            /moveto off
            /delay 30 !${Me.Moving}
        }
		/if (${MezAnnounce}!=0) {
			/docommand /dgt \aw I AM \ar AE MEZZING \ag ${MezAESpell}
		} else {
			/echo \aw I AM \ar AE MEZZING \ag ${MezAESpell}
		}
		/call CastSpell "${MezAESpell}" ${AEMezID} Mez
		/varset groupbufftimer 1m
            
		/if (${MezAnnounce}!=0) {
			/docommand /dgt \aw I JUST CAST \ar AE MEZ \ag ${MezAESpell}
		} else {
			/echo \aw I JUST CAST \ar AE MEZ \ag ${MezAESpell}
		}
        /delay 10 ${Me.SpellReady[${MezAESpell}]}
        /varset MezAETimer ${Spell[${MezAESpell}].Duration.TotalSeconds}s
        /if (${WasChasing}) /varset ChaseAssist 1
    }
    | Reset all mez timers to 0 after AE Mez
    /for i 1 to ${MezCheckElements}
       /if (${Defined[MezTimer${i}]}) /varset MezTimer${i} 0
    /next i
/return	
|-------------------------------------------------------------------------------------
|- SUB: AAMezAE
|-------------------------------------------------------------------------------------
Sub AAMezAE(int AEMezID)
    /declare i int local 1
    /declare WasChasing int local 0
	/target id ${AEMezID}
	/delay 10 ${Target.ID}==${AEMezID}
    | Enchanter AE mez code
    /if (${Me.Class.Name.Equal[Enchanter]}) {
        /if (${ChaseAssist}) {
            /varset ChaseAssist 0
            /varset WasChasing 1
            /squelch /stick off
            /moveto off
            /delay 30 !${Me.Moving}
        }
		/if (${MezAnnounce}!=0) {
			/docommand /dgt \aw I AM \ar AE MEZZING \ag ${MezAEAA}
		} else {
			/echo \aw I AM \ar AE MEZZING \ag ${MezAEAA}
		}
		/face fast
		/delay 5
		/casting "Beam of Slumber" alt -targetid|${AEMezID}
		/varset groupbufftimer 1m
        /delay 10
		/if (${MezAnnounce}!=0) {
			/docommand /dgt \aw I JUST CAST \ar AE MEZ \ag ${MezAEAA}
		} else {
			/echo \aw I JUST CAST \ar AE MEZ \ag ${MezAEAA}
		}
|-        /varset MezAETimer ${Spell[${MezAEAA}].Duration.TotalSeconds}s
        /if (${WasChasing}) /varset ChaseAssist 1
    }
    | Reset all mez timers to 0 after AE Mez
    /for i 1 to ${MezCheckElements}
       /if (${Defined[MezTimer${i}]}) /varset MezTimer${i} 0
    /next i
/return	
|-------------------------------------------------------------------------------------
|- SUB: Mez Mobs
|-------------------------------------------------------------------------------------
Sub MezMobs(int MobID, int TimerNum)
    /declare MezFail int local 0
    /declare MezTry int local 1
    /declare ReMez int local 0
    /if (${Me.Combat}) {
        /attack off
        /delay 25 !${Me.Combat}
    }
    /squelch /target id ${MobID}
    /delay 20 ${Target.ID}==${MobID} && ${Target.BuffsPopulated}==TRUE
    /if (${Target.ID}==${MobID}) {
        /if (${Int[${Target.Mezzed.ID}]} && ${Target.Mezzed.Name.Equal[${MezSpell}]}) {
            /if (${Target.BuffDuration[${Target.Mezzed.Name}].TotalSeconds}>${Math.Calc[(${Spell[${MezSpell}].Duration.TotalSeconds}+${MezMod})*.10]}) {
                /varcalc MezCount${TimerNum} 1
                /varcalc MezTimer${TimerNum} (${Target.BuffDuration[${Target.Mezzed.Name}].TotalSeconds}*10)*.85
                /return
            }            
        }
        /if (${MezCount${TimerNum}}<1) {
			/if (${MezAnnounce}!=0) {
				/docommand /dgt \ar MEZZING \ag -> \ay ${Spawn[${MobID}].CleanName} \ag <- \ar ID:${MobID}
			} else {
				/echo \ar MEZZING \ag -> \ay ${Spawn[${MobID}].CleanName} \ag <- \ar ID:${MobID}
			}
        } else {
			/if (${MezAnnounce}!=0) {
				/docommand /dgt \ar ReMEZZING \ag -> \ay ${Spawn[${MobID}].CleanName} \ag <- \ar ID:${MobID}
			} else {
				/echo \ar ReMEZZING \ag -> \ay ${Spawn[${MobID}].CleanName} \ag <- \ar ID:${MobID}
			}
            /varset ReMez 1
        }
        | Chanter mez code
        :retrymez
        /if (${Me.Class.Name.Equal[Enchanter]}) {
			/call CastSpell "${MezSpell}" ${MobID} Mez
			/varset groupbufftimer 1m
            /varcalc MezFail ${MezFail}+1
			/doevents
            /if (${Macro.Return.Equal[CAST_SUCCESS]}) {
                /if (!${ReMez}) {
					/if (${MezAnnounce}!=0) {
						/docommand /dgt \ar JUST MEZZED \aw -> \ag ${MezSpell} \aw on \ay ${Spawn[${MobID}].CleanName} \aw : \ar ${MobID}
					} else {
						/echo \ar JUST MEZZED \aw -> \ag ${MezSpell} \aw on \ay ${Spawn[${MobID}].CleanName} \aw : \ar ${MobID}
					}
				}
                /if (${ReMez}) {
					/if (${MezAnnounce}!=0) {
						/docommand /dgt \ar JUST REMEZZED \aw -> \ag ${MezSpell} \aw on \ay ${Spawn[${MobID}].CleanName} \aw : \ar ${MobID}
					} else {
						/echo \ar JUST REMEZZED \aw -> \ag ${MezSpell} \aw on \ay ${Spawn[${MobID}].CleanName} \aw : \ar ${MobID}
					}
				}
                /varcalc MezCount${TimerNum} ${MezCount${TimerNum}}+1
                /varcalc MezTimer${TimerNum} ((${Spell[${MezSpell}].Duration.TotalSeconds}+${MezMod})*10)*.90
            }
            /if (${Macro.Return.Equal[CAST_RESIST]} && ${MezFail}<2) {
				/if (${MezAnnounce}!=0) {
					/docommand /dgt \ar MEZ Resisted \ag -> \ay ${Spawn[${MobID}].CleanName} \ag <- \ar ID:${MobID}
				} else {
					/echo \ar MEZ Resisted \ag -> \ay ${Spawn[${MobID}].CleanName} \ag <- \ar ID:${MobID}
				}
				|- /if (${DoTash} && ${Target.ID}==${MobID} && ${Target.Distance}<50 && (!${Target.Tashed.ID}) && ${Me.AltAbilityReady[Bite of Tashani]} && !${Me.Moving} && !${Target.Type.Equal[Corpse]} && ${Target.LineOfSight}) {
				|-	/call AANow ${Me.AltAbility[Bite of Tashani].ID}
				|-	/delay 16
				|- }
                /goto :retrymez
            }
            /if (${Macro.Return.Equal[CAST_IMMUNE]}) {
                /if (!${MezImmuneIDs.Find[|${Target.ID}]}) /call AddMezImmune ${Target.ID}
            }
        }
        /varset MezTry 0
    }
/return 
|-------------------------------------------------------------------------------------
|- SUB: AddMezImmune
|-------------------------------------------------------------------------------------
Sub AddMezImmune(int MezID)
	/if (${Select[${Me.Class.ShortName},Brd,Enc,Nec]}==0) /return
    /if (${MezImmuneIDs.Find[|${MezID}]}) /return
    /varset MezImmuneIDs ${MezImmuneIDs}|${MezID} 
	/if (${MezAnnounce}!=0) {
		/docommand /dgt \ar MEZ Immune \ag -> \ay ${Spawn[${MezID}].CleanName} \ag <- \ar ID:${MezID} \aw Skipping.
	} else {
		/echo \ar MEZ Immune \ag -> \ay ${Spawn[${MezID}].CleanName} \ag <- \ar ID:${MezID} \aw Skipping.
	}
/return
|-------------------------------------------------------------------------------------
|- SUB: Event MezBroke
|-------------------------------------------------------------------------------------
Sub Event_MezBroke(meztext,mezmob,mezbreaker)
    /if (!${MezOn}) /return
|-    /if (${Spawn[${mezbreaker}].CleanName.Equal[${assistname}]}) /return
|-    /if (${Spawn[${assistname}].Type.Equal[pet]} && ${Spawn[${assistname}].Master.CleanName.Equal[${mezbreaker}]}) /return
    /declare tempMobID int local ${Target.ID}
    /assist ${mezbreaker}
    /delay 5s ${Me.AssistComplete}==TRUE
|-   /if (${Target.ID} && ${Target.ID}==${Me.GroupAssistTarget.ID}) {
|-        /target id ${tempMobID}
|-        /delay 10 ${Target.ID}==${tempMobID}
|-        /return
|-    }
    /declare i int local
	/if (${MezAnnounce}!=0) {
		/docommand /dgt \ag >> \ar ${Spawn[${mezbreaker}].CleanName} \ag << \aw has awakened \ag -> \ay ${mezmob} \ag <-
	} else {
		/echo \ag >> \ar ${Spawn[${mezbreaker}].CleanName} \ag << \aw has awakened \ag -> \ay ${mezmob} \ag <-
	}    
    /for i 1 to ${MezCheckElements}
        /if (${CCTarget${i}Info.Arg[3,|].Equal[${mezmob}]}) {
            /echo Resetting Mez Timer ${mezmob} ID: ${CCTarget${i}Info.Arg[1,|]}
            /varset MezTimer${i} 0
        }
    /next i
    /doevents flush MezBroke
    /call DoMezStuff
    | Set MezOn = 2 to let us know that the event was triggered. Will be set back to 1 in other location
    /varset MezBroke 1
	/varset groupbufftimer 1m
/return
|-------------------------------------------------------------------------------------
|- SUB: Event MezImmune
|-------------------------------------------------------------------------------------
Sub Event_MezImmune(int MezID)
| Sub
    /if (${Select[${Me.Class.ShortName},Brd,Enc,Nec]}==0) /return
    | Assign temp var MezImmune list
    /declare ImmuneAdd string local ${MezImmune}
    | If mezimmune default text with the word null in it assign var spawn clean name
    /if (${ImmuneAdd.Find[null]}) {
        /varset ImmuneAdd ${Spawn[${MezID}].CleanName}
    } else {
        /varset ImmuneAdd ${ImmuneAdd},${Spawn[${MezID}].CleanName}
    }
|    /if (!${MezImmune.Find[${Spawn[${MezID}].CleanName}]}) /ini "${InfoFileName}" "${Zone}${If[${Me.InInstance},_I,]}" "MezImmune" "${ImmuneAdd}"
	/if (${MezAnnounce}!=0) {
		/docommand /dgt \ar MEZ Immune \ag -> \ay ${Spawn[${MezID}].CleanName} \ag <- \ar ID:${MezID} \aw Adding to MezImmune list."
	} else {
		/echo \ar MEZ Immune \ag -> \ay ${Spawn[${MezID}].CleanName} \ag <- \ar ID:${MezID} \aw Adding to MezImmune list."
	}		
	| Reassign mezimmune var the new list
    /varset MezImmune ${ImmuneAdd}
	/varset groupbufftimer 1m
/return 