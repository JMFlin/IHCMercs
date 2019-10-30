|- ihcmnkutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub MnkSetup
|-Create Alias's
	|-Toggles
	/squelch /alias /tglalliance 	/setvarint Toggle UseAlliance
	/squelch /alias /tglaoe			/setvarint Toggle UseAoE
	/squelch /alias /tglbp			/setvarint Toggle ChestCombatCast
	/squelch /alias /tglforce		/setvarint Toggle ForceAlliance
	/squelch /alias /tglintim		/setvarint Toggle UseIntimidate
	/squelch /alias /tglmezbreak	/setvarint Toggle AllowMezBreak
	/squelch /alias /tglpoison		/setvarint Toggle UsePoisons	
	/squelch /alias /tgldrive		/setvarint Toggle Drive
|-Declare AA's and Discs
	/declare endregen				string outer NULL
	/declare mnkaura				string outer NULL
	/declare DichoSpell				string outer NULL
	/declare Drunken				string outer NULL
	/declare Curse					string outer NULL
	/declare Fang					string outer NULL
	/declare Fists					string outer NULL
	/declare Precision				string outer NULL
	/declare Shuriken				string outer NULL
	/declare Crane					string outer NULL
	/declare Synergy				string outer NULL
	/declare Alliance				string outer NULL
	/declare Storm					string outer NULL

|-Defensives
	/declare EarthForce				string outer NULL
	/declare ShadedStep				string outer NULL
	/declare RejectDeath			string outer NULL
	
|-Declare Main discs
	/declare Iron					string outer NULL	
	/declare Heel					string outer NULL
	/declare Speed					string outer NULL
	/declare Palm					string outer NULL
	/declare Poise 					string outer NULL
|-	/declare FlurryDisc				string outer NULL
|-	/declare FlurryDiscID			int outer 0
|-	/declare DisconDisc				string outer NULL
|-	/declare DisconDiscID			int outer 0
|-	/declare ResolveDisc			string outer NULL
|-	/declare ResolveDiscID			int outer 0
|-	/declare HHEBuff				string outer NULL

|-Config Options
	/call LoadCommonConfig
	/call LoadIni Combat AllowMezBreak		 	int 0
	/call LoadIni Combat ForceAlliance		 	int 0
	/call LoadIni Combat StickHow				string behind
	/call LoadIni Combat UseAlliance		 	int 1
	/call LoadIni Combat UseIntimidate		 	int 1
	/call LoadIni Combat UseMelee		 		int 1
	/call LoadIni Item ChestItemName			string "${Me.Inventory[17].Name}"
	/call LoadIni Item ChestCombatCast			int 0
	/call LoadIni Item PoisonName				string NULL
	/call LoadIni Item PoisonBuffName			string NULL
	/call LoadIni Item UsePoisons		 		int 0
	/call LoadIni General Drive		 			int 0
	
	/declare MonkCount				int outer 1
	/declare epicfists				string outer NULL
	/declare UseEpic				int outer 0
	/declare CastResult             string outer
|- Check for epic
	/if (${FindItem[Transcended Fistwraps of Immortality].ID}) {
		/varset epicfists		Transcended Fistwraps of Immortality
		/varset UseEpic 1
	}
	/varset ChestItemName		"${Me.Inventory[17].Name}"
/return 
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges
	/varset changetoini 0
	/call SaveCommonConfig
	/call SetIni Combat AllowMezBreak		int ${AllowMezBreak}
	/call SetIni Combat ForceAlliance		int ${ForceAlliance}
	/call SetIni Combat UseAlliance		 	int ${UseAlliance}
	/call SetIni Combat UseIntimidate		int ${UseIntimidate}
	/call SetIni Combat UseMelee		 	int ${UseMelee}
	/call SetIni Item ChestCombatCast		int ${ChestCombatCast}
	/call SetIni Item UsePoisons		 	int ${UsePoisons}
	/call SetIni General Drive		 		int ${Drive}
/return
|----------------------------------------------------------------------------
|- SUB: PullAbilitySetup
|----------------------------------------------------------------------------
Sub PullAbilitySetup
	/varset PullAbility 376
	/if (${FindItem[Staff of Viral Flux].ID}) /varset PullAbility2 ${FindItem[Staff of Viral Flux]}
	/varset PullDistance 190
/return
|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub SetupDiscs

|--RejectDeath line
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Reject Death].RankName}]}) {
		/varset RejectDeath ${Spell[Reject Death].RankName}
	}
|--Earthforce line
	/if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Earthforce Discipline].RankName}]}) {
		/varset EarthForce ${Spell[Earthforce Discipline].RankName}
	}
|--ShadedStep line
	/if (${Me.Level}>=97 && ${Me.CombatAbility[${Spell[Shaded Step].RankName}]}) {
		/varset ShadedStep ${Spell[Shaded Step].RankName}
	}
|---Strom line
	/if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Eye of the Storm].RankName}]}) {
		/varset Storm ${Spell[Eye of the Storm].RankName}
	}
|---Alliance line
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Firewalker's Covenant].RankName}]}) {
		/varset Alliance ${Spell[Firewalker's Covenant].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Doomwalker's Alliance].RankName}]}) {
		/varset Alliance ${Spell[Doomwalker's Alliance].RankName}
	}
|---Synergy Line
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Firewalker's Synergy].RankName}]}) {
		/varset Synergy ${Spell[Firewalker's Synergy].RankName}
	}
|---DM Line
	/if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Drunken Monkey Style].RankName}]}) {
		/varset Drunken ${Spell[Drunken Monkey Style].RankName}
	} 
|---Curse Line
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Curse of Fourteen Fists].RankName}]}) {
		/varset Curse ${Spell[Curse of Fourteen Fists].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Curse of the Thirteen Fingers].RankName}]}) {
		/varset Curse ${Spell[Curse of the Thirteen Fingers].RankName}
	} 
|---Fang Line
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Hoshkar's Fang].RankName}]}) {
		/varset Fang ${Spell[Hoshkar's Fang].RankName}
	} 
|---Fists Line
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Firestorm of Fists].RankName}]}) {
		/varset Fists ${Spell[Firestorm of Fists].RankName}
	}
|---Precision Line
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Firewalker's Precision Strike].RankName}]}) {
		/varset Precision ${Spell[Firewalker's Precision Strike].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Doomwalker's Precision Strike].RankName}]}) {
		/varset Precision ${Spell[Doomwalker's Precision Strike].RankName}
	}
|---Shuriken Line
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Vigorous Shuriken].RankName}]}) {
		/varset Shuriken ${Spell[Vigorous Shuriken].RankName}
	} 
|---Crane Line
	/if (${Me.Level}>=93 && ${Me.CombatAbility[${Spell[Crane Stance].RankName}]}) {
		/varset Crane ${Spell[Crane Stance].RankName}
	} 
|-Dicho Spell*
	/if (${Me.Level}>=${Spell[Dissident Form].Level} && ${Me.CombatAbility[${Spell[Dissident Form].RankName}]}) {
		/varset DichoSpell ${Spell[Dissident Form].RankName}
	} else /if (${Me.Level}>=${Spell[Dichotomic Form].Level} && ${Me.CombatAbility[${Spell[Dichotomic Form].RankName}]}) {
		/varset DichoSpell ${Spell[Dichotomic Form].RankName}
	}
|---Fast Endurance regen - No Update
	/if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Breather].RankName}]}) {
		/varset endregen ${Spell[Breather].RankName}
	} else /if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Rest].RankName}]}) {
		/varset endregen ${Spell[Rest].RankName}
	} else /if (${Me.Level}>=91 && ${Me.CombatAbility[${Spell[Reprieve].RankName}]}) {
		/varset endregen ${Spell[Reprieve].RankName}
	} else /if (${Me.Level}>=86 && ${Me.CombatAbility[${Spell[Respite].RankName}]}) {
		/varset endregen ${Spell[Respite].RankName}
	} else /if (${Me.Level}>=82 && ${Me.CombatAbility[${Spell[Fourth Wind].RankName}]}) {
		/varset endregen ${Spell[Fourth Wind].RankName}
	} else /if (${Me.Level}>=77 && ${Me.CombatAbility[${Spell[Third Wind].RankName}]}) {
		/varset endregen ${Spell[Third Wind].RankName}
	} else /if (${Me.Level}>=72 && ${Me.CombatAbility[${Spell[Second Wind].RankName}]}) {
		/varset endregen ${Spell[Second Wind].RankName}
	}
|-Aura Set up	
	/if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Master's Aura].RankName}]}) {
		/varset mnkaura ${Spell[Master's Aura].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Disciple's Aura].RankName}]}) {
		/varset mnkaura ${Spell[Disciple's Aura].RankName}
	}

|-Ironfist line
	/if (${Me.Level}>=88 && ${Me.CombatAbility[${Spell[Ironfist Discipline].RankName}]}) {
		/varset Iron ${Spell[Ironfist Discipline].RankName}
	}

|-Heel line
	/if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Heel of Zagali].RankName}]}) {
		/varset Heel ${Spell[Heel of Zagali].RankName}
	}

|-Speed line
	/if (${Me.Level}>=63 && ${Me.CombatAbility[${Spell[Speed Focus Discipline].RankName}]}) {
		/varset Speed ${Spell[Speed Focus Discipline].RankName}
	}

|-Palm line
	/if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Terrorpalm Discipline].RankName}]}) {
		/varset Palm ${Spell[Terrorpalm Discipline].RankName}
	}

|-Tiger's Poise line
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Tiger's Poise].RankName}]}) {
		/varset Poise ${Spell[Tiger's Poise].RankName}
	}
	
/return
|----------------------------------------------------------------------------
|-SUB: Bind Change Var Int resets various interger settings from ini file
|----------------------------------------------------------------------------
Sub Bind_SetVarInt(string ISection, string IName, int IVar)
    /docommand /varset changetoini 1
 |-Toggles
	/if (${ISection.Equal[Toggle]}) {
  |--Alliance
		/if (${IName.Equal[UseAlliance]}) {
			/if (!${UseAlliance}) {
				/echo \aw Setting UseAlliance to \ag ON
				/varset UseAlliance 1
				/call AllianceCheck
			} else {
				/echo \aw Resetting UseAlliance to \ar OFF
				/varset UseAlliance 0
			}
  |--LootOn
		} else /if (${IName.Equal[LootOn]}) {
			/if (!${LootOn}) {
				/echo \aw Setting LootOn to \ag ON
				/varset LootOn 1
			} else {
				/echo \aw Resetting LootOn to \ar OFF
				/varset LootOn 0
			}
  |--Intimidate
		} else /if (${IName.Equal[UseIntimidate]}) {
			/if (!${UseIntimidate}) {
				/echo \aw Setting UseIntimidate to \ag ON
				/varset UseIntimidate 1
			} else {
				/echo \aw Resetting UseIntimidate to \ar OFF
				/varset UseIntimidate 0
			}
  |--Allow MezBreak
		} else /if (${IName.Equal[AllowMezBreak]}) {
			/if (!${AllowMezBreak}) {
				/echo \aw Setting AllowMezBreak to \ag ON
				/varset AllowMezBreak 1
			} else {
				/echo \aw Resetting AllowMezBreak to \ar OFF
				/varset AllowMezBreak 0
			}
  |--Force Alliance
		} else /if (${IName.Equal[ForceAlliance]}) {
			/if (!${ForceAlliance}) {
				/echo \aw Setting ForceAlliance to \ag ON
				/varset ForceAlliance 1
			} else {
				/echo \aw Resetting ForceAlliance to \ar OFF
				/varset ForceAlliance 0
			}
  |--Chest Combat Cast
		} else /if (${IName.Equal[ChestCombatCast]}) {
			/if (!${ChestCombatCast}) {
				/echo \aw Setting ChestCombatCast to \ag ON
				/varset ChestCombatCast 1
			} else {
				/echo \aw Resetting ChestCombatCast to \ar OFF
				/varset ChestCombatCast 0
			}
  |--Use Poisons
		} else /if (${IName.Equal[UsePoisons]}) {
			/if (!${UsePoisons}) {
				/echo \aw Setting UsePoisons to \ag ON
				/varset UsePoisons 1
			} else {
				/echo \aw Resetting UsePoisons to \ar OFF
				/varset UsePoisons 0
			}
		}
	}
/return
|----------------------------------------------------------------------------
|-SUB: BIND CmdList - 
|----------------------------------------------------------------------------
Sub Bind_CmdList
/call CommonHelp
/echo \ag===${MacroName} Commands=== 
/echo \ag/tglalliance\aw - Use mnk alliance? there still needs to be >=3 monks for it to fire
/echo \ag/tglaoe\aw - Turn the use of AE abilities on/off
/echo \ag/tglautoaxe\aw - Turn the Auto Axe summoning feature on/off
/echo \ag/tglautoaxe2\aw - Turn the Auto Axe 2 summoning feature on/off
/echo \ag/tglbp\aw - Turn on/off the use of a Chest piece defined in the ini
/echo \ag/tglforce\aw - Force Alliance Use. Use when other Zerkers are present but not in the same group 
/echo \ag/tglintim\aw - Use Intimidation skill?
/echo \ag/tglloot\aw - Turn auto looting on/off
/echo \ag/tglmezbreak\aw - Allow attacking mez'd mobs if below assistat % - Ignores waiting for MA
/echo \ag/tglopener\aw - Toggle ${cheapshot} ability ON/OFF
/echo \ag/tglpet\aw - Pet toggle...cause sometimes they arent allowed
/echo \ag/tglpoison\aw - Turn on/off the use of poison buffs
/echo \ag/tgldrive\aw - Turn editing dirve
/return 