|- ihcbrdutil.inc
|- Version 1.0
|- Updated: 6/1/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub brd_setup
|-Spells
	/declare Aura1					string outer NULL
	/declare Aura2					string outer NULL
	/declare Aura1Name string outer NULL
	/declare Aura2Name string outer NULL
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
	/declare StormBladeSong 		string outer NULL
	/declare FateSong				string outer NULL
	/declare PosseSpell				string 	outer 	Origin
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
	/declare BattleMelody			string outer 25136
	/declare RegenMelody			string outer 37
|	/declare BattleMelody			string outer 1 2 3 4 1 5 2 3 1 4 5 2 1 3 4 5 7 1 2 10
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
	/declare AllianceSong 			string outer NULL
|-Declare spell variables
	/declare spellmisc 			int outer 8
	/declare GroupBuffRecast 	int outer 0
	/declare miscspellremem		string outer NULL
	/declare CastResult         string outer
	/declare spellrememtimer	timer outer 0
	/declare groupbufftimer		timer outer 0
	/declare ReadyToCast	  	timer outer 0
	/declare ChestItemName				string outer "${Me.Inventory[17].Name}"
/return 
|* ------------------------------------------------------------------------------------------
| SUB: ${Me.Class.ShortName.Lower}_load_spellbar /echo ${SpellGem1}
|------------------------------------------------------------------------------------------ *|
Sub brd_load_spellbar
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar	

	/if (${Me.AltAbility[Mnemonic Retention].Rank} == 5) {

		/call LoadSpellGem "${AllianceSong}" 1

		/call LoadSpellGem "${InsultSong1}" 2
		/call LoadSpellGem "${InsultSong2}" 3

		/call LoadSpellGem "${DichoSong}" 4

		/call LoadSpellGem "${MainAriaSong}" 5
		/call LoadSpellGem "${WarMarchSong}" 6
		/call LoadSpellGem "${SufferingSong}" 7
		/call LoadSpellGem "${ArcaneSong}" 8
		/call LoadSpellGem "${StormBladeSong}" 9
		
		/call LoadSpellGem "${SlowSong}" 10
		| /call LoadSpellGem "${FateSong}" 10
		/call LoadSpellGem "${ChorusRegenSong}" 11
		/call LoadSpellGem "${Aura1}" 12
		/call LoadSpellGem "${AccelerandoSong}" 13
		| /call LoadSpellGem "${AllianceSong}" 13

	} else {
		/call LoadSpellGem "${MainAriaSong}" 1
		/call LoadSpellGem "${WarMarchSong}" 2
		/call LoadSpellGem "${SufferingSong}" 3
		/call LoadSpellGem "${ArcaneSong}" 4
		/call LoadSpellGem "${StormBladeSong}" 5
		/call LoadSpellGem "${SlowSong}" 6
		/call LoadSpellGem "${ChorusRegenSong}" 7
		/call LoadSpellGem "${AccelerandoSong}" 8
	}


|**
	/call LoadSpellGem "${MainAriaSong}" 1
	/call LoadSpellGem "${WarMarchSong}" 2
	/call LoadSpellGem "${SufferingSong}" 3
	/call LoadSpellGem "${ArcaneSong}" 4
	/call LoadSpellGem "${StormBladeSong}" 5
	/call LoadSpellGem "${FateSong}" 6
	/call LoadSpellGem "${ChorusRegenSong}" 7
	/call LoadSpellGem "${Aura1}" 8
**|

	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub brd_abilities

	
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Covenant of Sticks and Stones].RankName}]}) {
		/varset AllianceSong ${Spell[Covenant of Sticks and Stones].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[].RankName}]}) {
		/varset AllianceSong ${Spell[Alliance of Sticks and Stones].RankName}
	}

|- BardDPSAura
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Aura of Begalru].RankName}]}) {
		/varset Aura1 ${Spell[Aura of Begalru].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Aura of Maetanrus].RankName}]}) {
		/varset Aura1 ${Spell[Aura of Maetanrus].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Aura of Va'Ker].RankName}]}) {
		/varset Aura1 ${Spell[Aura of Va'Ker].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Aura of the Orator].RankName}]}) {
		/varset Aura1 ${Spell[Aura of the Orator].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Aura of the Composer].RankName}]}) {
		/varset Aura1 ${Spell[Aura of the Composer].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Aura of the Poet].RankName}]}) {
		/varset Aura1 ${Spell[Aura of the Poet].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Aura of the Artist].RankName}]}) {
		/varset Aura1 ${Spell[Aura of the Artist].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Aura of the Muse].RankName}]}) {
		/varset Aura1 ${Spell[Aura of the Muse].RankName}
	}

|- BardRegenAura
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Aura of Xigam].RankName}]}) {
		/varset Aura2 ${Spell[Aura of Xigam].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Aura of Sionachie].RankName}]}) {
		/varset Aura2 ${Spell[Aura of Sionachie].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Aura of Salarra].RankName}]}) {
		/varset Aura2 ${Spell[Aura of Salarra].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Aura of Lunanyn].RankName}]}) {
		/varset Aura2 ${Spell[Aura of Lunanyn].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Aura of Renewal].RankName}]}) {
		/varset Aura2 ${Spell[Aura of Renewal].RankName}
	}
|- MainAriaSong
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Aria of Begalru].RankName}]}) {
		/varset MainAriaSong ${Spell[Aria of Begalru].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Aria of Maetanrus].RankName}]}) {
		/varset MainAriaSong ${Spell[Aria of Maetanrus].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Aria of Va'Ker].RankName}]}) {
		/varset MainAriaSong ${Spell[Aria of Va'Ker].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Aria of the Orator].RankName}]}) {
		/varset MainAriaSong ${Spell[Aria of the Orator].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Aria of the Composer].RankName}]}) {
		/varset MainAriaSong ${Spell[Aria of the Composer].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Warsong of the Vah Shir].RankName}]}) {
		/varset MainAriaSong ${Spell[Warsong of the Vah Shir].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Battlecry of the Vah Shir].RankName}]}) {
		/varset MainAriaSong ${Spell[Battlecry of the Vah Shir].RankName}
	} else /if (${Me.Level}>=50 && ${Me.Book[${Spell[Verses of Victory].RankName}]}) {
		/varset MainAriaSong ${Spell[Verses of Victory].RankName}
	} 
|- CasterAriaSong
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Qunard's Aria].RankName}]}) {
		/varset CasterAriaSong ${Spell[Qunard's Aria].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Nilsara's Aria].RankName}]}) {
		/varset CasterAriaSong ${Spell[Nilsara's Aria].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Gosik's Aria].RankName}]}) {
		/varset CasterAriaSong ${Spell[Gosik's Aria].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Daevan's Aria].RankName}]}) {
		/varset CasterAriaSong ${Spell[Daevan's Aria].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Sotor's Aria].RankName}]}) {
		/varset CasterAriaSong ${Spell[Sotor's Aria].RankName}
	}
|- WarMarchSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[War March of Dekloaz].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Dekloaz].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[War March of Jocelyn].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Jocelyn].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[War March of Protan].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Protan].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[War March of Illdaera].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Illdaera].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[War March of Dagda].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Dagda].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[War March of Brekt].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Brekt].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[War March of Meldrath].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of Meldrath].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[War March of Mastruq].RankName}]}) {
		/varset WarMarchSong ${Spell[War March of the Mastruq].RankName}
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[McVaxius' Rousing Rondo].RankName}]}) {
		/varset WarMarchSong ${Spell[McVaxius' Rousing Rondo].RankName}
	} else /if (${Me.Level}>=42 && ${Me.Book[${Spell[McVaxius' Berserker Crescendo].RankName}]}) {
		/varset WarMarchSong ${Spell[McVaxius' Berserker Crescendo].RankName}
	} else /if (${Me.Level}>=10 && ${Me.Book[${Spell[Anthem de Arms].RankName}]}) {
		/varset WarMarchSong ${Spell[Anthem de Arms].RankName}
	} 


|- SufferingSong
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Travenro's Song of Suffering].RankName}]}) {
		/varset SufferingSong ${Spell[Travenro's Song of Suffering].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Fjilnauk's Song of Suffering].RankName}]}) {
		/varset SufferingSong ${Spell[Fjilnauk's Song of Suffering].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Kaficus' Song of Suffering].RankName}]}) {
		/varset SufferingSong ${Spell[Kaficus' Song of Suffering].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Hykast's Song of Suffering].RankName}]}) {
		/varset SufferingSong ${Spell[Hykast's Song of Suffering].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Noira's Song of Suffering].RankName}]}) {
		/varset SufferingSong ${Spell[Noira's Song of Suffering].RankName}
	} 
|- ArcaneSong
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Arcane Ballad].RankName}]}) {
		/varset ArcaneSong ${Spell[Arcane Ballad].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Arcane Melody].RankName}]}) {
		/varset ArcaneSong ${Spell[Arcane Melody].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Arcane Hymn].RankName}]}) {
		/varset ArcaneSong ${Spell[Arcane Hymn].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Arcane Address].RankName}]}) {
		/varset ArcaneSong ${Spell[Arcane Address].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Arcane Chorus].RankName}]}) {
		/varset ArcaneSong ${Spell[Arcane Chorus].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Arcane Arietta].RankName}]}) {
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
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Coldcrow's Spry Sonata].RankName}]})  {
		/varset SprySonataSong ${Spell[Coldcrow's Spry Sonata].RankName}
	}
	
	/if (${Me.Level}>=69 && ${Me.Book[${Spell[Storm Blade].RankName}]})  {
		/varset StormBladeSong ${Spell[Storm Blade].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Song of the Storm].RankName}]})  {
		/varset StormBladeSong ${Spell[Song of the Storm].RankName}
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
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Chorus of Rodect].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Rodect].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Erollisi's Chorus].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Erollisi's Chorus].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Cantata of Life].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Cantata of Life].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Chorus of Replenishment].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Chorus of Replenishment].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Cantata of Replenishment].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Cantata of Replenishment].RankName}
	} else /if (${Me.Level}>=6 && ${Me.Book[${Spell[Hymn of Restoration].RankName}]})  {
		/varset ChorusRegenSong ${Spell[Hymn of Restoration].RankName}
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
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Call of the Muse].RankName}]})  {
		/varset CrescendoSong ${Spell[Call of the Muse].RankName}
	} 
|- InsultSong1
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Sathir's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Sathir's Insult].RankName}
		/varset InsultSong2 ${Spell[Travenro's Insult].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Travenro's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Travenro's Insult].RankName}
		/varset InsultSong2 ${Spell[Tsaph's Insult].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Tsaph's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Tsaph's Insult].RankName}
		/varset InsultSong2 ${Spell[Fjilnauk's Insult].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Fjilnauk's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Fjilnauk's Insult].RankName}
		/varset InsultSong2 ${Spell[Kaficus' Insult].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Kaficus' Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Kaficus' Insult].RankName}
		/varset InsultSong2 ${Spell[Garath's Insult].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Garath's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Garath's Insult].RankName}
		/varset InsultSong2 ${Spell[Hykast's Insult].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Hykast's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Hykast's Insult].RankName}
		/varset InsultSong2 ${Spell[Lyrin's Insult].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Lyrin's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Lyrin's Insult].RankName}
		/varset InsultSong2 ${Spell[Venimor's Insult].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Venimor's Insult].RankName}]})  {
		/varset InsultSong1 ${Spell[Venimor's Insult].RankName}
		/varset InsultSong2 ${Spell[Brusco's Bombastic Bellow].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Brusco's Bombastic Bellow].RankName}]})  {
		/varset InsultSong1 ${Spell[Brusco's Bombastic Bellow].RankName}
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
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Dreams of Ayonae].RankName}]})  {
		/varset MezSong ${Spell[Slumber of the Mindshear].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Slumber of the Mindshear].RankName}]})  {
		/varset MezSong ${Spell[Dreams of Ayonae].RankName}
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
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Selo's Assonant Strain].RankName}]})  {
		/varset SlowSong ${Spell[Selo's Assonant Strain].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Selo's Chords of Cessation].RankName}]})  {
		/varset SlowSong ${Spell[Selo's Chords of Cessation].RankName}
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
	}  else /if (${Me.Level}>=49 && ${Me.Book[${Spell[Selo's Accelerating Chorus].RankName}]})  {
		/varset AccelerandoSong ${Spell[Selo's Accelerating Chorus].RankName}
	} else /if (${Me.Level}>=5 && ${Me.Book[${Spell[Selo's Accelerando].RankName}]})  {
		/varset AccelerandoSong ${Spell[Selo's Accelerando].RankName}
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

|- FateSong
 	/if (${Me.Level}>=112 && ${Me.Book[${Spell[Fatesong of Radiwol].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of Radiwol].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Fatesong of Dekloaz].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of Dekloaz].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Fatesong of Jocelyn].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of Jocelyn].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Fatesong of Protan].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of Protan].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Fatesong of Illdaera].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of Illdaera].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Fatesong of Fergar].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of Fergar].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Fatesong of the Gelidran].RankName}]})  {
		/varset FateSong ${Spell[Fatesong of the Gelidran].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Garadell's Fatesong].RankName}]})  {
		/varset FateSong ${Spell[Garadell's Fatesong].RankName}
	}

	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9

	/call brd_load_spellbar

/return
