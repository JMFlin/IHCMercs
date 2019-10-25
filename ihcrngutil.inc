|- ihcrngutil.inc
|- Version 0.1
|- Updated: 7/3/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub RngSetup
|-Spells
	/declare ArrowOpener			string outer NULL
	/declare CalledShotsArrow		string outer NULL
	/declare FocusedArrows			string outer NULL
	/declare DichoSpell				string outer NULL
	/declare SummerNuke				string outer NULL
	/declare SwarmDoT				string outer NULL
	/declare UnityBuff				string outer NULL
	/declare ShoutBuff				string outer NULL
	/declare AgroBuff				string outer NULL
	/declare AgroReducerBuff		string outer NULL
	/declare ParryProcBuff			string outer NULL
	/declare AtkBuff				string outer NULL
	/declare AtkHPBuff				string outer NULL
	/declare RunSpeedBuff			string outer NULL
	/declare KillShotBuff			string outer NULL
	/declare EyesManaRegenBuff		string outer NULL
	/declare GroupStrengthBuff		string outer NULL
	/declare GroupPredatorBuff		string outer NULL
	/declare GroupEnrichmentBuff	string outer NULL
	/declare BowDisc				string outer NULL
	/declare MeleeDisc				string outer NULL
	/declare DefenseDisc			string outer NULL
	/declare DurationMod			float outer 1
|-Discs
	/declare JoltingKicks			string outer NULL
	/declare AEBlades				string outer NULL
	/declare FocusedBlades			string outer NULL
	/declare ReflexSlashHeal		string outer NULL
|-Special
	/declare Epicsword				string outer NULL
	/declare UseEpic 				int outer 1
|-Config Options
	/call LoadCommonConfig
	/call LoadIni Combat AllowMezBreak		 	int 0
	/call LoadIni Combat DoDot					int 0
	/call LoadIni Combat Manatonuke				int 5
	/call LoadIni Combat StickHow				string behind
	/call LoadIni Combat StopNukeAggro			int 80
	/call LoadIni Combat UseAoE					int 0
	/call LoadIni Combat UseMelee		 		int 1
	/call LoadIni Combat UseOpener			 	int 1
	/call LoadIni Item ChestItemName			string "${Me.Inventory[17].Name}"
	/call LoadIni Item ChestCombatCast			int 0
	/call LoadIni Options BringYourOwnSpells	int 0
	/call LoadIni Pet UseSwarmpet		 		int 0
	/if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==1) /varset DurationMod 1.15
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==2) /varset DurationMod 1.3
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==3) /varset DurationMod 1.5
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==4) /varset DurationMod 1.7
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==5) /varset DurationMod 1.9
|- Check for epic
	/if (${FindItem[=Aurora, the Heartwood Blade].ID}) {
		/varset Epicsword	Aurora, the Heartwood Blade	
		/varset UseEpic 1
	} else /if (${FindItem[=Heartwood Blade].ID}) {
		/varset Epicsword	Heartwood Blade
		/varset UseEpic 1
	}
|-Declare spell variables
	/declare spellmisc 			int outer 8
	/declare GroupBuffRecast 	int outer 0
	/declare miscspellremem		string outer NULL
	/declare CastResult         string outer
	/declare spellrememtimer	timer outer 0
	/declare ReadyToCast	  	timer outer 0
	/declare groupbufftimer		timer outer 0
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9
|-	/if (${Me.AltAbility[8300].Name.Find[disabled]} && ${Me.AltAbilityReady[8300]}) {
|-		/alt act 8300
|-		/delay 5
|-	}
/return 
Sub ClassAliasSetup
|-Create Class Aliases 
	|-- Toggles
	/squelch /alias /byos			/setvarint Toggle BringYourOwnSpells
	/squelch /alias /tglaoe			/togglevariable UseAoE
	/squelch /alias /tglbp			/togglevariable ChestCombatCast
	/squelch /alias /tglpoison		/togglevariable UsePoisons
	/squelch /alias /tgldots		/togglevariable DoDot
	/squelch /alias /tglmezbreak	/togglevariable AllowMezBreak
	/call AliasSetup
	/call SetIni General IHCMacVersion			string ${IHCVersion}
/return
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges
	/varset changetoini 0
	/call SaveCommonConfig
	/call SetIni Combat AllowMezBreak		 	int ${AllowMezBreak}
	/call SetIni Combat DoDot					int ${DoDot}
	/call SetIni Combat Manatonuke				int ${Manatonuke}
	/call SetIni Combat StopNukeAggro			int ${StopNukeAggro}
	/call SetIni Combat UseAoE					int ${UseAoE}
	/call SetIni Combat UseMelee		 		int ${UseMelee}
	/call SetIni Item ChestCombatCast			int ${ChestCombatCast}
	/call SetIni Options BringYourOwnSpells		int ${BringYourOwnSpells}
	/call SetIni Pet UseSwarmpet		 		int ${UseSwarmpet}
/return
|* ------------------------------------------------------------------------------------------
| SUB: LoadSpellBar
|------------------------------------------------------------------------------------------ *|
Sub LoadSpellBar
	/if (!${BringYourOwnSpells}) {
		/if (${Me.Standing}) /sit
		/delay 10 ${Me.Sitting}
		/echo \aw Loading Spell Bar
		/call LoadSpellGem "${ArrowOpener}" 1
		/call LoadSpellGem "${CalledShotsArrow}" 2
		/call LoadSpellGem "${FocusedArrows}" 3
		/call LoadSpellGem "${DichoSpell}" 4
		/call LoadSpellGem "${SummerNuke}" 5
		/call LoadSpellGem "${SwarmDoT}" 6
	}
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub CheckSpells
|- /if (${Me.Level}>=${Spell[].Level} && ${Me.Book[${Spell[].RankName}]}) {
|-	/varset  ${Spell[].RankName}
|- } else /if (${Me.Level}>=${Spell[].Level} && ${Me.Book[${Spell[].RankName}]}) {
|-	/varset  ${Spell[].RankName}
|- }
|-DefenseDisc
	/if (${Me.Level}>=60 && ${Me.CombatAbility[${Spell[Weapon Shield Discipline].RankName}]}) {
		/varset DefenseDisc ${Spell[Weapon Shield Discipline].RankName}
	}
|-MeleeDisc
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Wildstalker's Discipline].RankName}]}) {
		/varset MeleeDisc ${Spell[Wildstalker's Discipline].RankName}
	} else /if (${Me.Level}>=105 && ${Me.CombatAbility[${Spell[Copsestalker's Discipline].RankName}]}) {
		/varset MeleeDisc ${Spell[Copsestalker's Discipline].RankName}
	} else /if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Bosquestalker's Discipline].RankName}]}) {
		/varset MeleeDisc ${Spell[Bosquestalker's Discipline].RankName}
	}
|-BowDisc
	/if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Pureshot Discipline].RankName}]}) {
		/varset BowDisc ${Spell[Pureshot Discipline].RankName}
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Sureshot Discipline].RankName}]}) {
		/varset BowDisc ${Spell[Sureshot Discipline].RankName}
	} else /if (${Me.Level}>=80 && ${Me.CombatAbility[${Spell[Aimshot Discipline].RankName}]}) {
		/varset BowDisc ${Spell[Aimshot Discipline].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Trueshot Discipline].RankName}]}) {
		/varset BowDisc ${Spell[Trueshot Discipline].RankName}
	}
|-GroupEnrichmentBuff
	/if (${Me.Level}>=${Spell[Wildstalker's Enrichment].Level} && ${Me.Book[${Spell[Wildstalker's Enrichment].RankName}]}) {
		/varset GroupEnrichmentBuff ${Spell[Wildstalker's Enrichment].RankName}
	} else /if (${Me.Level}>=${Spell[Copsestalker's Enrichment].Level} && ${Me.Book[${Spell[Copsestalker's Enrichment].RankName}]}) {
		/varset GroupEnrichmentBuff ${Spell[Copsestalker's Enrichment].RankName}
	}
|- UnityBuff
	/if (${Me.Level}>=${Spell[Wildstalker's Unity].Level} && ${Me.Book[${Spell[Wildstalker's Unity].RankName}]}) {
		/varset UnityBuff ${Spell[Wildstalker's Unity].RankName}
		/varset KillShotBuff ${Spell[Wildstalker's Unity].Trigger[1].Name}
		/varset EyesManaRegenBuff ${Spell[Wildstalker's Unity].Trigger[3].Name}
	} else /if (${Me.Level}>=${Spell[Copsestalker's Unity].Level} && ${Me.Book[${Spell[Copsestalker's Unity].RankName}]}) {
		/varset UnityBuff ${Spell[Copsestalker's Unity].RankName}
		/varset KillShotBuff ${Spell[Copsestalker's Unity].Trigger[1].Name}
		/varset EyesManaRegenBuff ${Spell[Copsestalker's Unity].Trigger[3].Name}
	} else /if (${Me.Level}>=${Spell[Bosquetender's Unity].Level} && ${Me.Book[${Spell[Bosquetender's Unity].RankName}]}) {
		/varset UnityBuff ${Spell[Bosquetender's Unity].RankName}
		/varset KillShotBuff ${Spell[Bosquetender's Unity].Trigger[1].Name}
		/varset EyesManaRegenBuff ${Spell[Bosquetender's Unity].Trigger[3].Name}
	}
|- ShoutBuff
	/if (${Me.Level}>=${Spell[Shout of the Wildstalker].Level} && ${Me.Book[${Spell[Shout of the Wildstalker].RankName}]}) {
		/varset ShoutBuff ${Spell[Shout of the Wildstalker].RankName}
		/varset GroupPredatorBuff ${Spell[Shout of the Wildstalker].Trigger[2].Name}
		/varset GroupStrengthBuff ${Spell[Shout of the Wildstalker].Trigger[3].Name}
	} else /if (${Me.Level}>=${Spell[Shout of the Copsestalker].Level} && ${Me.Book[${Spell[Shout of the Copsestalker].RankName}]}) {
		/varset ShoutBuff ${Spell[Shout of the Copsestalker].RankName}
		/varset GroupPredatorBuff ${Spell[Shout of the Copsestalker].Trigger[2].Name}
		/varset GroupStrengthBuff ${Spell[Shout of the Copsestalker].Trigger[3].Name}
	} else /if (${Me.Level}>=${Spell[Shout of the Bosquestalker].Level} && ${Me.Book[${Spell[Shout of the Bosquestalker].RankName}]}) {
		/varset ShoutBuff ${Spell[Shout of the Bosquestalker].RankName}
		/varset GroupPredatorBuff ${Spell[Shout of the Bosquestalker].Trigger[2].Name}
		/varset GroupStrengthBuff ${Spell[Shout of the Bosquestalker].Trigger[3].Name}
	} else /if (${Me.Level}>=${Spell[Shout of the Predator].Level} && ${Me.Book[${Spell[Shout of the Predator].RankName}]}) {
		/varset ShoutBuff ${Spell[Shout of the Predator].RankName}
		/varset GroupPredatorBuff ${Spell[Shout of the Predator].Trigger[2].Name}
		/varset GroupStrengthBuff ${Spell[Shout of the Predator].Trigger[3].Name}
	}
|- AgroBuff
	/if (${Me.Level}>=${Spell[Devastating Steel].Level} && ${Me.Book[${Spell[Devastating Steel].RankName}]}) {
		/varset AgroBuff ${Spell[Devastating Steel].RankName}
	} else /if (${Me.Level}>=${Spell[Devastating Swords].Level} && ${Me.Book[${Spell[Devastating Swords].RankName}]}) {
		/varset AgroBuff ${Spell[Devastating Swords].RankName}
	} else /if (${Me.Level}>=${Spell[Devastating Impact].Level} && ${Me.Book[${Spell[Devastating Impact].RankName}]}) {
		/varset AgroBuff ${Spell[Devastating Impact].RankName}
	} else /if (${Me.Level}>=${Spell[Devastating Slashes].Level} && ${Me.Book[${Spell[Devastating Slashes].RankName}]}) {
		/varset AgroBuff ${Spell[Devastating Slashes].RankName}
	} else /if (${Me.Level}>=${Spell[Devastating Edges].Level} && ${Me.Book[${Spell[Devastating Edges].RankName}]}) {
		/varset AgroBuff ${Spell[Devastating Edges].RankName}
	} else /if (${Me.Level}>=${Spell[Devastating Blades].Level} && ${Me.Book[${Spell[Devastating Blades].RankName}]}) {
		/varset AgroBuff ${Spell[Devastating Blades].RankName}
	}
|- AgroReducerBuff
	/if (${Me.Level}>=${Spell[Jolting Steel].Level} && ${Me.Book[${Spell[Jolting Steel].RankName}]}) {
		/varset AgroReducerBuff ${Spell[Jolting Steel].RankName}
	} else /if (${Me.Level}>=${Spell[Jolting Swords].Level} && ${Me.Book[${Spell[Jolting Swords].RankName}]}) {
		/varset AgroReducerBuff ${Spell[Jolting Swords].RankName}
	} else /if (${Me.Level}>=${Spell[Jolting Shock].Level} && ${Me.Book[${Spell[Jolting Shock].RankName}]}) {
		/varset AgroReducerBuff ${Spell[Jolting Shock].RankName}
	} else /if (${Me.Level}>=${Spell[Jolting Impact].Level} && ${Me.Book[${Spell[Jolting Impact].RankName}]}) {
		/varset AgroReducerBuff ${Spell[Jolting Impact].RankName}
	} else /if (${Me.Level}>=${Spell[Jolting Edges].Level} && ${Me.Book[${Spell[Jolting Edges].RankName}]}) {
		/varset AgroReducerBuff ${Spell[Jolting Edges].RankName}
	} else /if (${Me.Level}>=${Spell[Jolting Swings].Level} && ${Me.Book[${Spell[Jolting Swings].RankName}]}) {
		/varset AgroReducerBuff ${Spell[Jolting Swings].RankName}
	}
|- ParryProcBuff
	/if (${Me.Level}>=${Spell[Roaring Blades].Level} && ${Me.Book[${Spell[Roaring Blades].RankName}]}) {
		/varset ParryProcBuff ${Spell[Roaring Blades].RankName}
	} else /if (${Me.Level}>=${Spell[Roaring Weapons].Level} && ${Me.Book[${Spell[Roaring Weapons].RankName}]}) {
		/varset ParryProcBuff ${Spell[Roaring Weapons].RankName}
	} else /if (${Me.Level}>=${Spell[Deafening Weapons].Level} && ${Me.Book[${Spell[Deafening Weapons].RankName}]}) {
		/varset ParryProcBuff ${Spell[Deafening Weapons].RankName}
	} else /if (${Me.Level}>=${Spell[Deafening Edges].Level} && ${Me.Book[${Spell[Deafening Edges].RankName}]}) {
		/varset ParryProcBuff ${Spell[Deafening Edges].RankName}
	} else /if (${Me.Level}>=${Spell[Crackling Edges].Level} && ${Me.Book[${Spell[Crackling Edges].RankName}]}) {
		/varset ParryProcBuff ${Spell[Crackling Edges].RankName}
	} else /if (${Me.Level}>=${Spell[Crackling Blades].Level} && ${Me.Book[${Spell[Crackling Blades].RankName}]}) {
		/varset ParryProcBuff ${Spell[Crackling Blades].RankName}
	}
|- RunSpeedBuff
	/if (${Me.Level}>=${Spell[Spirit of Falcons].Level} && ${Me.Book[${Spell[Spirit of Falcons].RankName}]}) {
		/varset RunSpeedBuff ${Spell[Spirit of Falcons].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Eagle].Level} && ${Me.Book[${Spell[Spirit of Eagle].RankName}]}) {
		/varset RunSpeedBuff ${Spell[Spirit of Eagle].RankName}
	}
	
 /if (${Me.Level}>=${Spell[Silent Shot].Level} && ${Me.Book[${Spell[Silent Shot].RankName}]}) {
	/varset ArrowOpener ${Spell[Silent Shot].RankName}
 } else /if (${Me.Level}>=${Spell[Heartrip].Level} && ${Me.Book[${Spell[Heartrip].RankName}]}) {
	/varset ArrowOpener ${Spell[Heartrip].RankName}
 }  else /if (${Me.Level}>=${Spell[Heartpierce].Level} && ${Me.Book[${Spell[Heartpierce].RankName}]}) {
	/varset ArrowOpener ${Spell[Heartpierce].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Foreseen Shots].Level} && ${Me.Book[${Spell[Foreseen Shots].RankName}]}) {
	/varset CalledShotsArrow ${Spell[Foreseen Shots].RankName}
 } else /if (${Me.Level}>=${Spell[Anticipated Shots].Level} && ${Me.Book[${Spell[Anticipated Shots].RankName}]}) {
	/varset CalledShotsArrow ${Spell[Anticipated Shots].RankName}
 } else /if (${Me.Level}>=${Spell[Forecasted Shots].Level} && ${Me.Book[${Spell[Forecasted Shots].RankName}]}) {
	/varset CalledShotsArrow ${Spell[Forecasted Shots].RankName}
 } else /if (${Me.Level}>=${Spell[Announced Shots].Level} && ${Me.Book[${Spell[Announced Shots].RankName}]}) {
	/varset CalledShotsArrow ${Spell[Announced Shots].RankName}
 } else /if (${Me.Level}>=${Spell[Called Shots].Level} && ${Me.Book[${Spell[Called Shots].RankName}]}) {
	/varset CalledShotsArrow ${Spell[Called Shots].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Focused Arrowgale].Level} && ${Me.Book[${Spell[Focused Arrowgale].RankName}]}) {
	/varset FocusedArrows ${Spell[Focused Arrowgale].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Arrowrain].Level} && ${Me.Book[${Spell[Focused Arrowrain].RankName}]}) {
	/varset FocusedArrows ${Spell[Focused Arrowrain].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Rain of Arrows].Level} && ${Me.Book[${Spell[Focused Rain of Arrows].RankName}]}) {
	/varset FocusedArrows ${Spell[Focused Rain of Arrows].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Arrow Swarm].Level} && ${Me.Book[${Spell[Focused Arrow Swarm].RankName}]}) {
	/varset FocusedArrows ${Spell[Focused Arrow Swarm].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Tempest of Arrows].Level} && ${Me.Book[${Spell[Focused Tempest of Arrows].RankName}]}) {
	/varset FocusedArrows ${Spell[Focused Tempest of Arrows].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Storm of Arrows].Level} && ${Me.Book[${Spell[Focused Storm of Arrows].RankName}]}) {
	/varset FocusedArrows ${Spell[Focused Storm of Arrows].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Dissident Fusillade].Level} && ${Me.Book[${Spell[Dissident Fusillade].RankName}]}) {
	/varset DichoSpell ${Spell[Dissident Fusillade].RankName}
 } else /if (${Me.Level}>=${Spell[Dichotomic Fusillade].Level} && ${Me.Book[${Spell[Dichotomic Fusillade].RankName}]}) {
	/varset DichoSpell ${Spell[Dichotomic Fusillade].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Summer's Tempest].Level} && ${Me.Book[${Spell[Summer's Tempest].RankName}]}) {
	/varset SummerNuke ${Spell[Summer's Tempest].RankName}
 } else /if (${Me.Level}>=${Spell[Summer's Cyclone].Level} && ${Me.Book[${Spell[Summer's Cyclone].RankName}]}) {
	/varset SummerNuke ${Spell[Summer's Cyclone].RankName}
 } else /if (${Me.Level}>=${Spell[Summer's Gale].Level} && ${Me.Book[${Spell[Summer's Gale].RankName}]}) {
	/varset SummerNuke ${Spell[Summer's Gale].RankName}
 } else /if (${Me.Level}>=${Spell[Summer's Squall].Level} && ${Me.Book[${Spell[Summer's Squall].RankName}]}) {
	/varset SummerNuke ${Spell[Summer's Squall].RankName}
 } else /if (${Me.Level}>=${Spell[Summer's Storm].Level} && ${Me.Book[${Spell[Summer's Storm].RankName}]}) {
	/varset SummerNuke ${Spell[Summer's Storm].RankName}
 } else /if (${Me.Level}>=${Spell[Summer's Mist].Level} && ${Me.Book[${Spell[Summer's Mist].RankName}]}) {
	/varset SummerNuke ${Spell[Summer's Mist].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Bonecrawler Swarm].Level} && ${Me.Book[${Spell[Bonecrawler Swarm].RankName}]}) {
	/varset SwarmDoT ${Spell[Bonecrawler Swarm].RankName}
 } else /if (${Me.Level}>=${Spell[Blisterbeetle Swarm].Level} && ${Me.Book[${Spell[Blisterbeetle Swarm].RankName}]}) {
	/varset SwarmDoT ${Spell[Blisterbeetle Swarm].RankName}
 } else /if (${Me.Level}>=${Spell[Dreadbeetle Swarm].Level} && ${Me.Book[${Spell[Dreadbeetle Swarm].RankName}]}) {
	/varset SwarmDoT ${Spell[Dreadbeetle Swarm].RankName}
 } else /if (${Me.Level}>=${Spell[Vespid Swarm].Level} && ${Me.Book[${Spell[Vespid Swarm].RankName}]}) {
	/varset SwarmDoT ${Spell[Vespid Swarm].RankName}
 } else /if (${Me.Level}>=${Spell[Scarab Swarm].Level} && ${Me.Book[${Spell[Scarab Swarm].RankName}]}) {
	/varset SwarmDoT ${Spell[Scarab Swarm].RankName}
 } else /if (${Me.Level}>=${Spell[Beetle Swarm].Level} && ${Me.Book[${Spell[Beetle Swarm].RankName}]}) {
	/varset SwarmDoT ${Spell[Beetle Swarm].RankName}
 }
|- /if (${Me.Level}>=${Spell[].Level} && ${Me.CombatAbility[${Spell[].RankName}]}) {
|-	/varset  ${Spell[].RankName}
|- } else /if (${Me.Level}>=${Spell[].Level} && ${Me.CombatAbility[${Spell[].RankName}]}) {
|-	/varset  ${Spell[].RankName}
|- } 
 /if (${Me.Level}>=${Spell[Jolting Wheel Kicks].Level} && ${Me.CombatAbility[${Spell[Jolting Wheel Kicks].RankName}]}) {
	/varset JoltingKicks ${Spell[Jolting Wheel Kicks].RankName}
 } else /if (${Me.Level}>=${Spell[Jolting Cut Kicks].Level} && ${Me.CombatAbility[${Spell[Jolting Cut Kicks].RankName}]}) {
	/varset JoltingKicks ${Spell[Jolting Cut Kicks].RankName}
 } else /if (${Me.Level}>=${Spell[Jolting Heel Kicks].Level} && ${Me.CombatAbility[${Spell[Jolting Heel Kicks].RankName}]}) {
	/varset JoltingKicks ${Spell[Jolting Heel Kicks].RankName}
 } else /if (${Me.Level}>=${Spell[Jolting Crescent Kicks].Level} && ${Me.CombatAbility[${Spell[Jolting Crescent Kicks].RankName}]}) {
	/varset JoltingKicks ${Spell[Jolting Crescent Kicks].RankName}
 } else /if (${Me.Level}>=${Spell[Jolting Hook Kicks].Level} && ${Me.CombatAbility[${Spell[Jolting Hook Kicks].RankName}]}) {
	/varset JoltingKicks ${Spell[Jolting Hook Kicks].RankName}
 } else /if (${Me.Level}>=${Spell[Jolting Frontkicks].Level} && ${Me.CombatAbility[${Spell[Jolting Frontkicks].RankName}]}) {
	/varset JoltingKicks ${Spell[Jolting Frontkicks].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Gale of Blades].Level} && ${Me.CombatAbility[${Spell[Gale of Blades].RankName}]}) {
	/varset AEBlades ${Spell[Gale of Blades].RankName}
 } else /if (${Me.Level}>=${Spell[Squall of Blades].Level} && ${Me.CombatAbility[${Spell[Squall of Blades].RankName}]}) {
	/varset AEBlades ${Spell[Squall of Blades].RankName}
 } else /if (${Me.Level}>=${Spell[Storm of Blades].Level} && ${Me.CombatAbility[${Spell[Storm of Blades].RankName}]}) {
	/varset AEBlades ${Spell[Storm of Blades].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Focused Gale of Blades].Level} && ${Me.CombatAbility[${Spell[Focused Gale of Blades].RankName}]}) {
	/varset FocusedBlades ${Spell[Focused Gale of Blades].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Squall of Blades].Level} && ${Me.CombatAbility[${Spell[Focused Squall of Blades].RankName}]}) {
	/varset FocusedBlades ${Spell[Focused Squall of Blades].RankName}
 } else /if (${Me.Level}>=${Spell[Focused Storm of Blades].Level} && ${Me.CombatAbility[${Spell[Focused Storm of Blades].RankName}]}) {
	/varset FocusedBlades ${Spell[Focused Storm of Blades].RankName}
 }
 
 /if (${Me.Level}>=${Spell[Reflexive Nettlespears].Level} && ${Me.CombatAbility[${Spell[Reflexive Nettlespears].RankName}]}) {
	/varset ReflexSlashHeal ${Spell[Reflexive Nettlespears].RankName}
 } else /if (${Me.Level}>=${Spell[Reflexive Bladespurs].Level} && ${Me.CombatAbility[${Spell[Reflexive Bladespurs].RankName}]}) {
	/varset ReflexSlashHeal ${Spell[Reflexive Bladespurs].RankName}
 }
/return
|----------------------------------------------------------------------------
|- SUB: Bind Change Var Int resets various interger settings from ini file
|----------------------------------------------------------------------------
Sub Bind_SetVarInt(string ISection, string IName, int IVar)
    /docommand /varset changetoini 1
 |-Toggles
	/if (${ISection.Equal[Toggle]}) {
  |--Pet
	}
/return
|----------------------------------------------------------------------------
|- SUB: BIND CmdList - 
|----------------------------------------------------------------------------
Sub Bind_CmdList
/call CommonHelp
/echo \ag===${MacroName} Commands=== 
/echo \sg/byos\aw - Bring Your Own Spells! Use what ever spells you have mem'd
/echo \ag/tglaoe\aw - Turn the use of AE abilities on/off
/echo \ag/tglbp\aw - Turn on/off the use of a Chest piece defined in the ini
/echo \ag/tglpet\aw - Pet toggle...cause sometimes they arent allowed
/echo \ag/tglmezbreak\aw - Allow attacking mez'd mobs if below assistat % - Ignores waiting for MA
/return