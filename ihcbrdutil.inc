|- ihcbrdutil.inc
|- Version 1.0
|- Updated: 6/1/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub BrdSetup
|-Spells
	/declare BardAura				string outer NULL
	/declare BardDPSAura			string outer NULL
	/declare BardRegenAura			string outer NULL
	/declare PulseRegenSong			string outer NULL
	/declare ChorusRegenSong		string outer NULL
	/declare AEMezSong				string outer NULL
	/declare MezSong				string outer NULL
	/declare DichoSong				string outer NULL
	/declare MainAriaSong			string outer NULL
	/declare CasterAriaSong			string outer NULL
	/declare WarMarchSong			string outer NULL
	/declare SufferingSong			string outer NULL
	/declare ArcaneSong				string outer NULL
	/declare SprySonataSong			string outer NULL
	/declare CrescendoSong			string outer NULL
	/declare InsultSong1			string outer NULL
	/declare InsultSong2			string outer NULL
	/declare SlowSong				string outer NULL
	/declare AESlowSong				string outer NULL
	/declare AccelerandoSong		string outer NULL
	/declare SpitefulSong			string outer NULL
	/declare RecklessSong			string outer NULL
|-Special
	/declare Epicsword				string outer NULL
	/declare UseEpic 				int outer 1
|- Misc Variables
	/declare SpellGem1				string outer NULL
	/declare SpellGem2				string outer NULL
	/declare SpellGem3				string outer NULL
	/declare SpellGem4				string outer NULL
	/declare SpellGem5				string outer NULL
	/declare SpellGem6				string outer NULL
	/declare SpellGem7				string outer NULL
	/declare SpellGem8				string outer NULL
	/declare SpellGem9				string outer NULL
	/declare SpellGem10				string outer NULL
	/declare SpellGem11				string outer NULL
	/declare SpellGem12				string outer NULL
	/declare SpellGem13				string outer NULL
	/declare BattleMelody			string outer 1 2 3 4 1 5 2 3 1 4 5 2 1 3 4 5 7 1 2 10
	/declare ExtBattleMelody		string outer 1 2 3 4 5 6 1 2 3 4 5 6 1 2 7 3 4 5 1 10
	/declare BurnMelody				string outer 8 9 1 8 9 2 8 9 1 8 9 3
	/declare ExtBurnMelody			string outer 8 1 2 8 3 4 8 1 5 8 2 3 8 1 4 8 5 2 8 1 10
	/declare MelodyType				string outer "Valid Settings are Melee (Default), Caster, Tank"
	/declare CurrentMelody			string outer NULL
	/declare IniMelody				string outer NULL
	/declare MezAETimer             timer	outer	0
	/declare TuneStuckActive		int outer 0
	/declare PlaySongs				int outer 0
	/declare DoBurn					int outer 0
|-Config Options
	/call LoadCommonConfig
	/call LoadIni Combat AllowMezBreak		 	int 0
	/call LoadIni Combat DoSlow					int 0
	/call LoadIni Combat StickHow				string behind
	/call LoadIni Combat UseMelee		 		int 1
	/call LoadIni Combat UseIntimidate		 	int 1
	/call LoadIni Combat MelodyType				String ${MelodyType}
	/call LoadIni Combat UseCustomMelody		int 0
	/call LoadIni Combat CustomMelody			String NULL
	/call LoadIni Combat UseRaidMelodies		int 1
	/call LoadIni Item ChestItemName			string "${Me.Inventory[17].Name}"
	/call LoadIni Item ChestCombatCast			int 0
	/call LoadIni Item UsePoisons		 		int 0
	/call LoadIni Item PoisonName				string NULL
	/call LoadIni Item PoisonBuffName			string NULL
	/call LoadIni Mez MezOn                 	int 1
	/call LoadIni Mez MezAnnounce               int 1	
	/call LoadIni Mez MezStartCount             int 2
	/call LoadIni Options BringYourOwnSpells	int 0
	/call LoadIni Options OOCManaSong			int 1
	/call LoadIni Options UseAura				int 1
	/call LoadIni Options UseRegenAura			int 0
	/call LoadIni Options UseAASelo				int 1
	/call LoadIni Options UseIniSongs			int 1
	/call LoadIni Pet UseSwarmpet		 		int 1
|- Check for epic
	/if (${FindItem[=Prismatic Dragon Blade].ID}) {
		/varset Epicsword	Prismatic Dragon Blade	
		/varset UseEpic 1
	} else /if (${FindItem[=Blade of Vesagran].ID}) {
		/varset Epicsword	Blade of Vesagran
		/varset UseEpic 1
	}
|-Declare spell variables
	/declare spellmisc 			int outer 8
	/declare GroupBuffRecast 	int outer 0
	/declare miscspellremem		string outer NULL
	/declare CastResult         string outer
	/declare spellrememtimer	timer outer 0
	/declare groupbufftimer		timer outer 0
	/declare ReadyToCast	  	timer outer 0
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
|-Create Alias
	|-- Toggles
	/squelch /alias /byos			/togglevariable BringYourOwnSpells
	/squelch /alias /tglaoe			/togglevariable UseAoE
	/squelch /alias /tglbp			/togglevariable ChestCombatCast
	/squelch /alias /tglpet			/togglevariable UsePet
	/squelch /alias /tglpoison		/togglevariable UsePoisons
	/squelch /alias /tgldots		/togglevariable DoDot
	/squelch /alias /tglmezbreak	/togglevariable AllowMezBreak
	/squelch /alias /tglslow		/togglevariable DoSlow
	/squelch /alias /tglselo		/togglevariable UseAASelo
	/squelch /alias /tglmanasong	/togglevariable OOCManaSong
	/squelch /alias /tglaura		/togglevariable UseAura
	/squelch /alias /tglpet			/togglevariable UseSwarmpet
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
	/call SetIni Combat DoSlow					int ${DoSlow}
	/call SetIni Combat UseMelee		 		int ${UseMelee}
	/call SetIni Item ChestCombatCast			int ${ChestCombatCast}
	/call SetIni Item UsePoisons		 		int ${UsePoisons}
	/call SetIni Options BringYourOwnSpells		int ${BringYourOwnSpells}
	/call SetIni Options UseAASelo				int ${UseAASelo}
	/call SetIni Options UseAura				int ${UseAura}
	/call SetIni Options OOCManaSong			int ${OOCManaSong}
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
		/declare sl int local 0
		/for sl 1 to 8
			/call LoadSpellGem "${SpellGem${sl}}" ${sl}
		/next sl
		/if (${spellmisc}>8) {
			/call LoadSpellGem "${SpellGem9}" 9
			/varset miscspellremem ${SpellGem9}
		}
		/if (${spellmisc}>9) {
			/call LoadSpellGem "${SpellGem10}" 10
			/varset miscspellremem ${SpellGem10}
		}
		/if (${spellmisc}>10) {
			/call LoadSpellGem "${SpellGem11}" 11
		}
		/if (${spellmisc}>11) {
			/call LoadSpellGem "${SpellGem12}" 12
			/varset miscspellremem ${SpellGem12}
		}
		/if (${spellmisc}>12) {
			/call LoadSpellGem "${SpellGem13}" 13
			/varset miscspellremem ${SpellGem13}
		}
	}
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub CheckSpells
|- BardDPSAura
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Aura of Begalru].RankName}]})  {
		/varset BardDPSAura ${Spell[Aura of Begalru].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Aura of Maetanrus].RankName}]})  {
		/varset BardDPSAura ${Spell[Aura of Maetanrus].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Aura of Va'Ker].RankName}]})  {
		/varset BardDPSAura ${Spell[Aura of Va'Ker].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Aura of the Orator].RankName}]})  {
		/varset BardDPSAura ${Spell[Aura of the Orator].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Aura of the Composer].RankName}]})  {
		/varset BardDPSAura ${Spell[Aura of the Composer].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Aura of the Poet].RankName}]})  {
		/varset BardDPSAura ${Spell[Aura of the Poet].RankName}
	}
|- BardRegenAura
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Aura of Xigam].RankName}]})  {
		/varset BardRegenAura ${Spell[Aura of Xigam].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Aura of Sionachie].RankName}]})  {
		/varset BardRegenAura ${Spell[Aura of Sionachie].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Aura of Salarra].RankName}]})  {
		/varset BardRegenAura ${Spell[Aura of Salarra].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Aura of Lunanyn].RankName}]})  {
		/varset BardRegenAura ${Spell[Aura of Lunanyn].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Aura of Renewal].RankName}]})  {
		/varset BardRegenAura ${Spell[Aura of Renewal].RankName}
	}
	/call SetupAura
|- MainAriaSong
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Aria of Begalru].RankName}]})  {
		/varset MainAriaSong ${Spell[Aria of Begalru].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Aria of Maetanrus].RankName}]})  {
		/varset MainAriaSong ${Spell[Aria of Maetanrus].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Aria of Va'Ker].RankName}]})  {
		/varset MainAriaSong ${Spell[Aria of Va'Ker].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Aria of the Orator].RankName}]})  {
		/varset MainAriaSong ${Spell[Aria of the Orator].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Aria of the Composer].RankName}]})  {
		/varset MainAriaSong ${Spell[Aria of the Composer].RankName}
	}
|- CasterAriaSong
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Qunard's Aria].RankName}]})  {
		/varset CasterAriaSong ${Spell[Qunard's Aria].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Nilsara's Aria].RankName}]})  {
		/varset CasterAriaSong ${Spell[Nilsara's Aria].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Gosik's Aria].RankName}]})  {
		/varset CasterAriaSong ${Spell[Gosik's Aria].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Daevan's Aria].RankName}]})  {
		/varset CasterAriaSong ${Spell[Daevan's Aria].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Sotor's Aria].RankName}]})  {
		/varset CasterAriaSong ${Spell[Sotor's Aria].RankName}
	}
|- WarMarchSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[War March of Dekloaz].RankName}]})  {
		/varset WarMarchSong ${Spell[War March of Dekloaz].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[War March of Jocelyn].RankName}]})  {
		/varset WarMarchSong ${Spell[War March of Jocelyn].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[War March of Protan].RankName}]})  {
		/varset WarMarchSong ${Spell[War March of Protan].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[War March of Illdaera].RankName}]})  {
		/varset WarMarchSong ${Spell[War March of Illdaera].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[War March of Dagda].RankName}]})  {
		/varset WarMarchSong ${Spell[War March of Dagda].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[War March of Brekt].RankName}]})  {
		/varset WarMarchSong ${Spell[War March of Brekt].RankName}
	} 
|- SufferingSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Travenro's Song of Suffering].RankName}]})  {
		/varset SufferingSong ${Spell[Travenro's Song of Suffering].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Fjilnauk's Song of Suffering].RankName}]})  {
		/varset SufferingSong ${Spell[Fjilnauk's Song of Suffering].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Kaficus' Song of Suffering].RankName}]})  {
		/varset SufferingSong ${Spell[Kaficus' Song of Suffering].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Hykast's Song of Suffering].RankName}]})  {
		/varset SufferingSong ${Spell[Hykast's Song of Suffering].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Noira's Song of Suffering].RankName}]})  {
		/varset SufferingSong ${Spell[Noira's Song of Suffering].RankName}
	} 
|- ArcaneSong
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Arcane Ballad].RankName}]})  {
		/varset ArcaneSong ${Spell[Arcane Ballad].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Arcane Melody].RankName}]})  {
		/varset ArcaneSong ${Spell[Arcane Melody].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Arcane Hymn].RankName}]})  {
		/varset ArcaneSong ${Spell[Arcane Hymn].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Arcane Address].RankName}]})  {
		/varset ArcaneSong ${Spell[Arcane Address].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Arcane Chorus].RankName}]})  {
		/varset ArcaneSong ${Spell[Arcane Chorus].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Arcane Arietta].RankName}]})  {
		/varset ArcaneSong ${Spell[Arcane Arietta].RankName}
	}
|- SprySonataSong
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Kluzen's Spry Sonata].RankName}]})  {
		/varset SprySonataSong ${Spell[Kluzen's Spry Sonata].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Doben's Spry Sonata].RankName}]})  {
		/varset SprySonataSong ${Spell[Doben's Spry Sonata].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Terasal's Spry Sonata].RankName}]})  {
		/varset SprySonataSong ${Spell[Terasal's Spry Sonata].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Sionachie's Spry Sonata].RankName}]})  {
		/varset SprySonataSong ${Spell[Sionachie's Spry Sonata].RankName}
	}
|- PulseRegenSong
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Pulse of Xigam].RankName}]})  {
		/varset PulseRegenSong ${Spell[Pulse of Xigam].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Pulse of Sionachie].RankName}]})  {
		/varset PulseRegenSong ${Spell[Pulse of Sionachie].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Pulse of Salarra].RankName}]})  {
		/varset PulseRegenSong ${Spell[Pulse of Salarra].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Pulse of Lunanyn].RankName}]})  {
		/varset PulseRegenSong ${Spell[Pulse of Lunanyn].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Pulse of Renewal].RankName}]})  {
		/varset PulseRegenSong ${Spell[Pulse of Renewal].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Pulse of Rodcet].RankName}]})  {
		/varset PulseRegenSong ${Spell[Pulse of Rodcet].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Rhythm of Restoration].RankName}]})  {
		/varset PulseRegenSong ${Spell[Rhythm of Restoration].RankName}
	}
|- ChorusRegenSong
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Chorus of Xigam].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Xigam].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Chorus of Sionachie].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Sionachie].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Chorus of Salarra].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Salarra].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Chorus of Lunanyn].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Lunanyn].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Chorus of Renewal].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Renewal].RankName}
	}
|- CrescendoSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Jembel's Lively Crescendo].RankName}]})  {
		/varset CrescendoSong ${Spell[Jembel's Lively Crescendo].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Silisia's Lively Crescendo].RankName}]})  {
		/varset CrescendoSong ${Spell[Silisia's Lively Crescendo].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Motlak's Lively Crescendo].RankName}]})  {
		/varset CrescendoSong ${Spell[Motlak's Lively Crescendo].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Kolain's Lively Crescendo].RankName}]})  {
		/varset CrescendoSong ${Spell[Kolain's Lively Crescendo].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Lyssa's Lively Crescendo].RankName}]})  {
		/varset CrescendoSong ${Spell[Lyssa's Lively Crescendo].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Gruber's Lively Crescendo].RankName}]})  {
		/varset CrescendoSong ${Spell[Gruber's Lively Crescendo].RankName}
	} 
|- InsultSong1
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Sathir's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Sathir's Insult].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Travenro's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Travenro's Insult].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Tsaph's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Tsaph's Insult].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Fjilnauk's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Fjilnauk's Insult].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Kaficus' Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Kaficus' Insult].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Garath's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Garath's Insult].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Hykast's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Hykast's Insult].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Lyrin's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Lyrin's Insult].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Venimor's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Venimor's Insult].RankName}
	}
|- InsultSong2
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Travenro's Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Travenro's Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Travenro's Insult].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Tsaph's Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Tsaph's Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Tsaph's Insult].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Fjilnauk's Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Fjilnauk's Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Fjilnauk's Insult].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Kaficus' Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Kaficus' Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Kaficus' Insult].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Garath's Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Garath's Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Garath's Insult].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Hykast's Insult].RankName}]} && ${InsultSong1.NotEqual[${Me.Book[${Spell[Hykast's Insult].RankName}]}]})  {
		/varset InsultSong2 ${Spell[Hykast's Insult].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Lyrin's Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Lyrin's Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Lyrin's Insult].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Venimor's Insult].RankName}]} && ${InsultSong1.NotEqual[${Spell[Venimor's Insult].RankName}]})  {
		/varset InsultSong2 ${Spell[Venimor's Insult].RankName}
	}
|- DichoSong
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Dissident Psalm].RankName}]})  {
		/varset DichoSong ${Spell[Dissident Psalm].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Dichotomic Psalm].RankName}]})  {
		/varset DichoSong ${Spell[Dichotomic Psalm].RankName}
	}
|- MezSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Slumber of Jembel].RankName}]})  {
		/varset MezSong ${Spell[Slumber of Jembel].RankName}
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Lullaby of Jembel].RankName}]})  {
		/varset MezSong ${Spell[Lullaby of Jembel].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Slumber of Silisia].RankName}]})  {
		/varset MezSong ${Spell[Slumber of Silisia].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Lullaby of Silisia].RankName}]})  {
		/varset MezSong ${Spell[Lullaby of Silisia].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Slumber of Motlak].RankName}]})  {
		/varset MezSong ${Spell[Slumber of Motlak].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Lullaby of the Forsaken].RankName}]})  {
		/varset MezSong ${Spell[Lullaby of the Forsaken].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Slumber of Kolain].RankName}]})  {
		/varset MezSong ${Spell[Slumber of Kolain].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Lullaby of the Forlorn].RankName}]})  {
		/varset MezSong ${Spell[Lullaby of the Forlorn].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Slumber of Sionachie].RankName}]})  {
		/varset MezSong ${Spell[Slumber of Sionachie].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Lullaby of the Lost].RankName}]})  {
		/varset MezSong ${Spell[Lullaby of the Lost].RankName}
	}
|- AEMezSong
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Wave of Somnolence].RankName}]})  {
		/varset AEMezSong ${Spell[Wave of Somnolence].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Wave of Torpor].RankName}]})  {
		/varset AEMezSong ${Spell[Wave of Torpor].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Wave of Quietude].RankName}]})  {
		/varset AEMezSong ${Spell[Wave of Quietude].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Wave of the Conductor].RankName}]})  {
		/varset AEMezSong ${Spell[Wave of the Conductor].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Wave of Dreams].RankName}]})  {
		/varset AEMezSong ${Spell[Wave of Dreams].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Wave of Slumber].RankName}]})  {
		/varset AEMezSong ${Spell[Wave of Slumber].RankName}
	} 
|- SlowSong
	/if (${Me.Level}>=64 && ${Me.Book[${Spell[Requiem of Time].RankName}]})  {
		/varset SlowSong ${Spell[Requiem of Time].RankName}
	} 
|- AESlowSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Dekloaz's Melodic Binding].RankName}]})  {
		/varset AESlowSong ${Spell[Dekloaz's Melodic Binding].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Protan's Melodic Binding].RankName}]})  {
		/varset AESlowSong ${Spell[Protan's Melodic Binding].RankName}
	}
 |- AccelerandoSong
 	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Atoning Accelerando].RankName}]})  {
		/varset AccelerandoSong ${Spell[Atoning Accelerando].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Allaying Accelerando].RankName}]})  {
		/varset AccelerandoSong ${Spell[Allaying Accelerando].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Ameliorating Accelerando].RankName}]})  {
		/varset AccelerandoSong ${Spell[Ameliorating Accelerando].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Assuaging Accelerando].RankName}]})  {
		/varset AccelerandoSong ${Spell[Assuaging Accelerando].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Alleviating Accelerando].RankName}]})  {
		/varset AccelerandoSong ${Spell[Alleviating Accelerando].RankName}
	}
 |- SpitefulSong
 	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Travenro's Spiteful Lyric].RankName}]})  {
		/varset SpitefulSong ${Spell[Travenro's Spiteful Lyric].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Fjilnauk's Spiteful Lyric].RankName}]})  {
		/varset SpitefulSong ${Spell[Fjilnauk's Spiteful Lyric].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Kaficus' Spiteful Lyric].RankName}]})  {
		/varset SpitefulSong ${Spell[Kaficus' Spiteful Lyric].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Hykast's Spiteful Lyric].RankName}]})  {
		/varset SpitefulSong ${Spell[Hykast's Spiteful Lyric].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Lyrin's Spiteful Lyric].RankName}]})  {
		/varset SpitefulSong ${Spell[Lyrin's Spiteful Lyric].RankName}
	}
 |- RecklessSong
 	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Rigelon's Reckless Renewal].RankName}]})  {
		/varset RecklessSong ${Spell[Rigelon's Reckless Renewal].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Rytan's Reckless Renewal].RankName}]})  {
		/varset RecklessSong ${Spell[Rytan's Reckless Renewal].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Ruaabri's Reckless Renewal].RankName}]})  {
		/varset RecklessSong ${Spell[Ruaabri's Reckless Renewal].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Ryken's Reckless Renewal].RankName}]})  {
		/varset RecklessSong ${Spell[Ryken's Reckless Renewal].RankName}
	}
	/call LoadSongData
	/declare bb int local 0
	/if (${UseIniSongs}) {
		/for bb 1 to 13
			/call LoadIni SpellGems SpellGem${bb}			String "${SpellGem${bb}}"
		/next bb
	}
/return
|----------------------------------------------------------------------------
|- SUB: Load Song Data
|----------------------------------------------------------------------------
Sub LoadSongData
	/call LoadSongIni Info Info1	string "Format for song#= Song Name|Time|Condition or 1"
	/call LoadSongIni Info Info2	string "Song Name= The song you want to play ex:${MainAriaSong}"
	/call LoadSongIni Info Info3	string "Time= The time you expect the buff to last, must be a MathCalc expression, Internal Variable:TuneStuckActive can be used to extend timer, see example below"
	/call LoadSongIni Info Info4	string "Condtion= 1 for always or can use MQ data. If using MQ data Replace $ with ^, ex:^{Me.PctEndurance} > 10"
	/call LoadSongIni Info Info5	string "Example using timer extension if A Tune Stuck in Your Head is active"
	/call LoadSongIni Info ExSong1	string "Aria of Begalru Rk. II|16 + (6*^{TuneStuckActive})|^{Me.Combat}"
	/call LoadSongIni Info MacVar1	string "TuneStuckActive - Internal variable used to evaluate if the Buff a Tune Stuck in your head is active. 1 if True 0 is false"
	/call LoadSongIni Info MacVar2	string "DoBurn - used to evaluate if all burn conditions (based on ini settings) have been met and its time to burn. 1 if True 0 is false"
	/call LoadSongIni Info MacVar3	string "Ini Key names that have a 0 or 1 setting can also be used for evaluation if formatted properly, ex: ^{UseAASelo}"
	/call LoadSongIni Info ExSong2	string "Selo's Sonata|0|!^{Me.XTarget[1].ID} && ^{UseAASelo} && !^{Me.Buff[Selo's Sonata].ID} && !^{Me.Invis}"
	/if (${Defined[Info1]}) /deletevar Info1
	/if (${Defined[Info2]}) /deletevar Info2
	/if (${Defined[Info3]}) /deletevar Info3
	/if (${Defined[Info4]}) /deletevar Info4
	/if (${Defined[Info5]}) /deletevar Info5
	/if (${Defined[ExSong1]}) /deletevar ExSong1
	/if (${Defined[MacVar1]}) /deletevar MacVar1
	/if (${Defined[MacVar2]}) /deletevar MacVar2
	/if (${Defined[MacVar3]}) /deletevar MacVar3
	/if (${Defined[ExSong2]}) /deletevar ExSong2
		/varset SpellGem1 ${MainAriaSong}
		/varset SpellGem2 ${WarMarchSong}
		/varset SpellGem3 ${SufferingSong}
		/varset SpellGem4 ${ArcaneSong}
		/varset SpellGem5 ${SprySonataSong}
		/varset SpellGem6 ${PulseRegenSong}
		/varset SpellGem7 ${CrescendoSong}
		/varset SpellGem8 ${DichoSong}
		/varset SpellGem9 ${ChorusRegenSong}
		/varset SpellGem10 ${InsultSong1}
		/varset SpellGem11 ${InsultSong2}
		/varset SpellGem12 ${AEMezSong}
		/varset SpellGem13 ${MezSong}
	/if (${MelodyType.Equal[Caster]}) {
		/if (${UseRaidMelodies}) {
			/call LoadSongIni RaidCaster TwistSize	int 13
			/call LoadSongIni RaidCaster Song1 string "${MainAriaSong}|16 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidCaster Song2 string "${ArcaneSong}|20 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidCaster Song3 string "${SufferingSong}|20|^{Me.Combat}"
			/call LoadSongIni RaidCaster Song4 string "${WarMarchSong}|20 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidCaster Song5 string "${CasterAriaSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidCaster Song6 string "${PulseRegenSong}|22 + (6*^{TuneStuckActive})|^{TuneStuckActive} && ^{Me.Combat}"
			/call LoadSongIni RaidCaster Song7 string "${CrescendoSong}|45|^{Me.PctMana}>5 && ^{Me.Combat}"
			/call LoadSongIni RaidCaster Song8 string "${DichoSong}|60|^{Me.PctEndurance}>10 && ^{Me.Combat}"
			/call LoadSongIni RaidCaster Song9 string "${ChorusRegenSong}|22 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni RaidCaster Song10 string "${InsultSong1}|6|0"
			/call LoadSongIni RaidCaster Song11 string "${InsultSong2}|6|0"
			/call LoadSongIni RaidCaster Song12 string "${AEMezSong}|30 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni RaidCaster Song13 string "${MezSong}|18 + (6*^{TuneStuckActive})|0"
			/varset IniMelody RaidCaster
		} else {
			/call LoadSongIni GroupCaster TwistSize	int 13
			/call LoadSongIni GroupCaster Song1	string "${MainAriaSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupCaster Song2	string "${ArcaneSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupCaster Song3	string "${SufferingSong}|22|^{Me.Combat}"
			/call LoadSongIni GroupCaster Song4	string "${WarMarchSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupCaster Song5	string "${CasterAriaSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupCaster Song6	string "${PulseRegenSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupCaster Song7	string "${CrescendoSong}|45|^{Me.PctMana}>5 && ^{Me.Combat}"
			/call LoadSongIni GroupCaster Song8	string "${DichoSong}|60|^{Me.PctEndurance}>10 && ^{Me.Combat}"
			/call LoadSongIni GroupCaster Song9	string "${ChorusRegenSong}|22 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni GroupCaster Song10 string "${InsultSong1}|6|0"
			/call LoadSongIni GroupCaster Song11 string "${InsultSong2}|6|0"
			/call LoadSongIni GroupCaster Song12 string "${AEMezSong}|30 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni GroupCaster Song13 string "${MezSong}|18 + (6*^{TuneStuckActive})|0"
			/varset IniMelody GroupCaster
		}
		/varset SpellGem2 ${ArcaneSong}
		/varset SpellGem4 ${WarMarchSong}
		/varset SpellGem5 ${CasterAriaSong}
	} else /if (${MelodyType.Equal[Tank]}) {
		/if (${UseRaidMelodies}) {
			/call LoadSongIni RaidTank TwistSize	int 13
			/call LoadSongIni RaidTank Song1 string "${AccelerandoSong}|16 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidTank Song2 string "${SprySonataSong}|20 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidTank Song3 string "${SpitefulSong}|20|^{Me.Combat}"
			/call LoadSongIni RaidTank Song4 string "${PulseRegenSong}|20 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidTank Song5 string "${RecklessSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidTank Song6 string "${ChorusRegenSong}|22 + (6*^{TuneStuckActive})|^{TuneStuckActive} && ^{Me.Combat}"
			/call LoadSongIni RaidTank Song7 string "${CrescendoSong}|45|^{Me.PctMana}>5 && ^{Me.Combat}"
			/call LoadSongIni RaidTank Song8 string "${DichoSong}|60|^{Me.PctEndurance}>10 && ^{Me.Combat}"
			/call LoadSongIni RaidTank Song9 string "${WarMarchSong}|22 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni RaidTank Song10 string "${InsultSong1}|6|0"
			/call LoadSongIni RaidTank Song11 string "${InsultSong2}|6|0"
			/call LoadSongIni RaidTank Song12 string "${AEMezSong}|30 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni RaidTank Song13 string "${MezSong}|18 + (6*^{TuneStuckActive})|0"
			/varset IniMelody RaidTank
		} else {
			/call LoadSongIni GroupTank TwistSize	int 13
			/call LoadSongIni GroupTank Song1 string "${AccelerandoSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupTank Song2 string "${SprySonataSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupTank Song3 string "${SpitefulSong}|22|^{Me.Combat}"
			/call LoadSongIni GroupTank Song4 string "${PulseRegenSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupTank Song5 string "${RecklessSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupTank Song6 string "${ChorusRegenSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupTank Song7 string "${CrescendoSong}|45|^{Me.PctMana}>5 && ^{Me.Combat}"
			/call LoadSongIni GroupTank Song8 string "${DichoSong}|60|^{Me.PctEndurance}>10 && ^{Me.Combat}"
			/call LoadSongIni GroupTank Song9 string "${WarMarchSong}|22 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni GroupTank Song10 string "${InsultSong1}|6|0"
			/call LoadSongIni GroupTank Song11 string "${InsultSong2}|6|0"
			/call LoadSongIni GroupTank Song12 string "${AEMezSong}|30 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni GroupTank Song13 string "${MezSong}|18 + (6*^{TuneStuckActive})|0"
			/varset IniMelody GroupTank
		}
		/varset SpellGem1 ${AccelerandoSong}
		/varset SpellGem2 ${SprySonataSong}
		/varset SpellGem3 ${SpitefulSong}
		/varset SpellGem4 ${PulseRegenSong}
		/varset SpellGem5 ${RecklessSong}
		/varset SpellGem6 ${ChorusRegenSong}
		/varset SpellGem9 ${WarMarchSong}
	} else {
		/if (${UseRaidMelodies}) {
			/call LoadSongIni RaidMelee TwistSize	int 13
			/call LoadSongIni RaidMelee Song1 string "${MainAriaSong}|16 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidMelee Song2 string "${WarMarchSong}|20 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidMelee Song3 string "${SufferingSong}|20|^{Me.Combat}"
			/call LoadSongIni RaidMelee Song4 string "${ArcaneSong}|20 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidMelee Song5 string "${SprySonataSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni RaidMelee Song6 string "${PulseRegenSong}|22 + (6*^{TuneStuckActive})|^{TuneStuckActive} && ^{Me.Combat}"
			/call LoadSongIni RaidMelee Song7 string "${CrescendoSong}|45|^{Me.PctMana}>5 && ^{Me.Combat}"
			/call LoadSongIni RaidMelee Song8 string "${DichoSong}|60|^{Me.PctEndurance}>10 && ^{Me.Combat}"
			/call LoadSongIni RaidMelee Song9 string "${ChorusRegenSong}|22 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni RaidMelee Song10 string "${InsultSong1}|6|0"
			/call LoadSongIni RaidMelee Song11 string "${InsultSong2}|6|0"
			/call LoadSongIni RaidMelee Song12 string "${AEMezSong}|30 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni RaidMelee Song13 string "${MezSong}|18 + (6*^{TuneStuckActive})|0"
			/varset IniMelody RaidMelee
		} else {
			/call LoadSongIni GroupMelee TwistSize	int 13
			/call LoadSongIni GroupMelee Song1 string "${MainAriaSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupMelee Song2 string "${WarMarchSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupMelee Song3 string "${SufferingSong}|22|^{Me.Combat}"
			/call LoadSongIni GroupMelee Song4 string "${ArcaneSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupMelee Song5 string "${SprySonataSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupMelee Song6 string "${PulseRegenSong}|22 + (6*^{TuneStuckActive})|^{Me.Combat}"
			/call LoadSongIni GroupMelee Song7 string "${CrescendoSong}|45|^{Me.PctMana}>5 && ^{Me.Combat}"
			/call LoadSongIni GroupMelee Song8 string "${DichoSong}|60|^{Me.PctEndurance}>10 && ^{Me.Combat}"
			/call LoadSongIni GroupMelee Song9 string "${ChorusRegenSong}|22 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni GroupMelee Song10 string "${InsultSong1}|6|0"
			/call LoadSongIni GroupMelee Song11 string "${InsultSong2}|6|0"
			/call LoadSongIni GroupMelee Song12 string "${AEMezSong}|30 + (6*^{TuneStuckActive})|0"
			/call LoadSongIni GroupMelee Song13 string "${MezSong}|18 + (6*^{TuneStuckActive})|0"
			/varset IniMelody GroupMelee
		}
	}
	/if (!${Defined[TwistSize]}) /declare TwistSize int outer 0
	/declare aa int local 0
	/for aa 1 to ${TwistSize}
		/if (!${Defined[Song${aa}]}) /call LoadSongIni ${IniMelody} Song${aa} string "SongNameHere|60|0"
		/if (!${Defined[SongTimer${aa}]}) /declare SongTimer${aa} timer outer 0
	/next aa
/return
|----------------------------------------------------------------------------
|- SUB: Load Song Ini
|----------------------------------------------------------------------------
Sub LoadSongIni(string sectionName, string varName, string varType, string varValue)     
	/if (!${Defined[${varName}]} && ${Defined[varType]}) /declare ${varName} ${varType} outer NULL
	/if (!${Ini[${SongFileName},${sectionName},${varName}].Length}) {
		/if (${varValue.Length}) {
			/ini "${SongFileName}" "${sectionName}" "${varName}" "${varValue}"
			/varset ${varName} ${varValue}
		}
	} else {
		/varset ${varName} ${Ini[${SongFileName},${sectionName},${varName}]}
	}
/return
|----------------------------------------------------------------------------
|- SUB: SetupAura
|---------------------------------------------------------------------------- 
Sub SetupAura
	/if (${UseRegenAura}) {
		/varset BardAura ${BardRegenAura}
	} else {
		/varset BardAura ${BardDPSAura}
	}
	/if (${Me.Aura[1].ID} && ${Me.Aura[1].Name.NotEqual[${BardAura}]}) {
		/squelch /docommand ${Me.Aura[1].Remove}
	}
/return
|----------------------------------------------------------------------------
|- SUB: Bind Change Var Int resets various interger settings from ini file
|----------------------------------------------------------------------------
Sub Bind_SetVarInt(string ISection, string IName, int IVar)
    /docommand /varset changetoini 1
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
/echo \ag/tglpoison\aw - Turn on/off the use of poison buffs
/echo \ag/tglmezbreak\aw - Allow attacking mez'd mobs if below assistat % - Ignores waiting for MA
/return