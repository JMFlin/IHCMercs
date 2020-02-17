|- ihcclrutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub clr_setup
|-Declare spell variables
	/declare promgem				int             outer 0
	/declare divinegem				int             outer 0
	/declare WardSpell		        string          outer NULL
	/declare Remedy1	        string          outer NULL
	/declare Remedy2	        string          outer NULL
	/declare Remedy3	        string          outer NULL
	/declare patchheal		        string          outer NULL
	/declare patchheal2		        string          outer NULL
	/declare groupfastheal	        string          outer NULL
	/declare GroupHealSpell1		string          outer NULL
	/declare grouphealnocure        string          outer NULL
	/declare PromisedHeal		    string          outer NULL
	/declare Renewal		        string          outer NULL
	/declare bigheal2		        string          outer NULL
	/declare yaulpspell		        string          outer NULL
	/declare stunnuke		        string          outer NULL
	/declare Intervention1		        string          outer NULL
	/declare Intervention2		        string          outer NULL
	/declare Intervention3		        string          outer NULL
	/declare nukeheal1		        string          outer NULL
	/declare nukeheal2		        string          outer NULL
	/declare patchhealpoint			int             outer 44
	/declare patchheal2point		int             outer 34
	/declare clickhealpoint			int             outer 35
	/declare healpoint				int 			outer 99
	/declare reversenpcid			int             outer 0
	/declare reztimer				timer           outer 0
	/declare hottimer				timer           outer 0
	/declare bufftimer				timer           outer 0
	/declare groupbufftimer			timer           outer 0
	/declare ReverseDS				string          outer NULL
	/declare SelfBuff				string          outer NULL
	/declare Retaliation			string			outer NULL
	/declare GroupHealProcBuff		string          outer NULL
	/declare GroupHPBuff			string          outer NULL
	/declare GroupHPBuffName 		string 			outer NULL
	/declare GroupBuff				string          outer NULL
	/declare TankBuff				string          outer NULL
	/declare GroupVieBuff			string          outer NULL
	/declare GroupSymbolBuff		string          outer NULL
	/declare StunLevel				int             outer 0
	/declare SymbolBuff		        string          outer NULL
	/declare HPBuff			        string          outer NULL
	/declare Aura1					string 			outer NULL
	/declare Aura2					string 			outer NULL
	/declare DivineBuff		        string          outer NULL
	/declare PromisedTimer			timer			outer 0
	/declare GroupBuffRecast    	int 			outer 0
	/declare GroupDeBuffed			int 			outer 0
	/declare TankBuffRecast     	int 			outer 0
	/declare DivineBuffRecast   	int 			outer 0
	/declare SymbolBuffRecast   	int 			outer 0
	/declare HPBuffRecast       	int 			outer 0
	/declare ShiningBuffRecast  	int 			outer 0
	/declare GroupVieBuffRecast 	int 			outer 0
	/declare BuffRecastTimer		timer 			outer 0
	/declare ClickHealTimer			timer 			outer 0
	/declare CureTimer				timer 			outer 0
	/declare healspellrange     	int 			outer 200
	/declare promhealrange      	int 			outer 200
    /declare grouphealrange     	int 			outer 100
	/declare GoMana 				int 			outer 0
	/declare Emeralds				int 			outer 0
	/declare Pearls					int 			outer 0
	/declare TankBuffMatch 			string 			outer NULL
	/declare epicshield				string 			outer NULL
	/declare epicwand				string 			outer NULL
	/declare extrahealcasttime 		timer 			outer 0
	/declare oldtank				string 			outer NULL
	/declare oldtankid				string 			outer NULL
	/declare newtank				int 			outer 0
	/declare DurationMod			int 			outer 1
	/declare AllianceBuff			string 			outer NULL
	/declare CureCount				int				outer 0
	/declare CureID					int				outer 0
	/declare grouphealpoint 		int 			outer 75
	/declare MassRezSpell 			string 			outer NULL
	/declare RezSpell	 			string 			outer NULL
	/declare CasterSpeedBuff 		string 			outer NULL
	/declare SingleElixirSpell 		string 			outer NULL
	/declare GroupElixirSpell 		string			outer NULL
	
	/declare spellmisc 				int outer 8
	/declare spellgem				int outer 1	
	/declare CastResult             string outer
	/declare miscspellremem			string outer NULL
	/declare tempid					string outer NULL
	/declare spellrememtimer		timer outer 0
	/declare spellslots				int outer 8
/return 
|----------------------------------------------------------
|- SUB: ${Me.Class.ShortName.Lower}_load_spellbar
|------------------------------------------------------------------------------------------
Sub clr_load_spellbar
	
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar
	
	/call LoadSpellGem "${SingleElixirSpell}" 1
	/call LoadSpellGem "${PromisedHeal}" 2
	/call LoadSpellGem "${Remedy1}" 3
	/call LoadSpellGem "${Remedy2}" 4
	/call LoadSpellGem "${WardSpell}" 5
	/call LoadSpellGem "${Intervention1}" 6
	/call LoadSpellGem "${Intervention2}" 7
	/call LoadSpellGem "${Intervention3}" 8

	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) {
		/call LoadSpellGem "${GroupElixirSpell}" 9
	}
	/delay 2s
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub clr_abilities
	|---Ward Spell Slot 1 or Heal over time for low level
	
	/if (${Me.Level}>=112 && ${Me.Book[${Spell[Ward of Righteousness].RankName}]})  {
		/varset WardSpell ${Spell[Ward of Assurance].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Ward of Assurance].RankName}]})  {
		/varset WardSpell ${Spell[Ward of Assurance].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Ward of Surety].RankName}]})  {
		/varset WardSpell ${Spell[Ward of Surety].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Ward of Certitude].RankName}]})  {
		/varset WardSpell ${Spell[Ward of Certitude].RankName}
	}


	/if (${Me.Level}>=${Spell[Merciful Acquittal].Level} && ${Me.Book[${Spell[Merciful Acquittal].RankName}]})  {
		/varset GroupElixirSpell ${Spell[Merciful Acquittal].RankName}
	}

	/if (${Me.Level}>=${Spell[Sincere Elixir].Level} && ${Me.Book[${Spell[Sincere Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Sincere Elixir].RankName}
	} else /if (${Me.Level}>=${Spell[Merciful Elixir].Level} && ${Me.Book[${Spell[Merciful Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Merciful Elixir].RankName}
	} else /if (${Me.Level}>=${Spell[Ardent Elixir].Level} && ${Me.Book[${Spell[Ardent Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Ardent Elixir].RankName}
	} else /if (${Me.Level}>=${Spell[Reverent Elixir].Level} && ${Me.Book[${Spell[Reverent Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Reverent Elixir].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Zealous Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Zealous Elixir].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Earnest Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Earnest Elixir].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Devout Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Devout Elixir].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Solemn Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Solemn Elixir].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Sacred Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Sacred Elixir].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Pious Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Pious Elixir].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Holy Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Holy Elixir].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Supernal Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Supernal Elixir].RankName}
	} else /if (${Me.Level}>=59 && ${Me.Book[${Spell[Celestial Elixir].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Celestial Elixir].RankName}
	} else /if (${Me.Level}>=44 && ${Me.Book[${Spell[Celestial Healing].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Celestial Healing].RankName}
	} else /if (${Me.Level}>=29 && ${Me.Book[${Spell[Celestial Health].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Celestial Health].RankName}
	} else /if (${Me.Level}>=19 && ${Me.Book[${Spell[Celestial Remedy].RankName}]})  {
		/varset SingleElixirSpell ${Spell[Celestial Remedy].RankName}
	}
|---Remedy Slot 2 and 3

	/if (${Me.Level}>=${Spell[Sincere Remedy].Level} && ${Me.Book[${Spell[Sincere Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Sincere Remedy].RankName}
		/varset Remedy2 ${Spell[Merciful Remedy].RankName}
		/varset Remedy3 ${Spell[Spiritual Remedy].RankName}
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Merciful Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Merciful Remedy].RankName}
		/varset Remedy2 ${Spell[Spiritual Remedy].RankName}
		/varset Remedy3 ${Spell[Graceful Remedy].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Spiritual Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Spiritual Remedy].RankName}
		/varset Remedy2 ${Spell[Graceful Remedy].RankName}
		/varset Remedy3 ${Spell[Faithful Remedy].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Graceful Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Graceful Remedy].RankName}
		/varset Remedy2 ${Spell[Faithful Remedy].RankName}
		/varset Remedy3 ${Spell[Earnest Remedy].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Faithful Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Faithful Remedy].RankName}
		/varset Remedy2 ${Spell[Earnest Remedy].RankName}
		/varset Remedy3 ${Spell[Devout Remedy].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Earnest Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Earnest Remedy].RankName}
		/varset Remedy2 ${Spell[Devout Remedy].RankName}
		/varset Remedy3 ${Spell[Solemn Remedy].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Devout Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Devout Remedy].RankName}
		/varset Remedy2 ${Spell[Solemn Remedy].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Solemn Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Solemn Remedy].RankName}
		/varset Remedy2 ${Spell[Sacred Remedy].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Sacred Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Sacred Remedy].RankName}
		/varset Remedy2 ${Spell[Supernal Remedy].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Pious Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Pious Remedy].RankName}
		/varset Remedy2 ${Spell[Supernal Remedy].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Supernal Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Supernal Remedy].RankName}
		/varset Remedy2 ${Spell[Ethereal Remedy].RankName}
	} else /if (${Me.Level}>=59 && ${Me.Book[${Spell[Ethereal Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Ethereal Remedy].RankName}
		/varset Remedy2 ${Spell[Solemn Remedy].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Ethereal Light].RankName}]}) {
		/varset Remedy1 ${Spell[Ethereal Light].RankName}
		/varset Remedy2 ${Spell[Remedy].RankName}
	} else /if (${Me.Level}>=51 && ${Me.Book[${Spell[Remedy].RankName}]}) {
		/varset Remedy1 ${Spell[Remedy].RankName}
		/varset Remedy2 ${Spell[Superior Healing].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Healing Light].RankName}]}) {
		/varset Remedy1 ${Spell[Healing Light].RankName}
		/varset Remedy2 ${Spell[Greater Healing].RankName}
	} else /if (${Me.Level}>=39 && ${Me.Book[${Spell[Superior Healing].RankName}]}) {
		/varset Remedy1 ${Spell[Superior Healing].RankName}
		/varset Remedy2 ${Spell[Celestial Health].RankName}
	} else /if (${Me.Level}>=30 && ${Me.Book[${Spell[Superior Healing].RankName}]}) {
		/varset Remedy1 ${Spell[Superior Healing].RankName}
		/varset Remedy2 ${Spell[Celestial Health].RankName}
	} else /if (${Me.Level}>=29 && ${Me.Book[${Spell[Celestial Health].RankName}]}) {
		/varset Remedy1 ${Spell[Celestial Health].RankName}
		/varset Remedy2 ${Spell[Greater Healing].RankName}
	} else /if (${Me.Level}>=20 && ${Me.Book[${Spell[Greater Healing].RankName}]}) {
		/varset Remedy1 ${Spell[Greater Healing].RankName}
		/varset Remedy2 ${Spell[Healing].RankName}
	} else /if (${Me.Level}>=10 && ${Me.Book[${Spell[Healing].RankName}]}) {
		/varset Remedy1 ${Spell[Healing].RankName}
		/varset Remedy2 ${Spell[Light Healing].RankName}
	} else /if (${Me.Level}>=4 && ${Me.Book[${Spell[Light Healing].RankName}]}) {
		/varset Remedy1 ${Spell[Light Healing].RankName}
		/varset Remedy2 ${Spell[Minor Healing].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Minor Healing].RankName}]}) {
		/varset Remedy1 ${Spell[Minor Healing].RankName}
	}
|---Patch Heals Slot 4 Dissident Blessing
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Sixteenth Serenity].RankName}]} && ${Me.Book[${Spell[Dissident Blessing].RankName}]})  {
		/varset patchheal ${Spell[Dissident Blessing].RankName}
		/varset patchheal2 ${Spell[Sixteenth Serenity].RankName}
		/varset patchhealpoint 44
		/varset patchheal2point 34
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Dissident Blessing].RankName}]})  {
		/varset patchheal ${Spell[Dissident Blessing].RankName}
		/varset patchheal2 ${Spell[Fifteenth Emblem].RankName}
		/varset patchhealpoint 44
		/varset patchheal2point 34
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Undying Life].RankName}]})  {
		/varset patchheal ${Spell[Undying Life].RankName}
		/varset patchheal2 ${Spell[Fifteenth Emblem].RankName}
		/varset patchhealpoint 44
		/varset patchheal2point 34
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Fifteenth Emblem].RankName}]})  {
		/varset patchheal ${Spell[Fifteenth Emblem].RankName}
		/varset patchhealpoint 34
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Fourteenth Catalyst].RankName}]})  {
		/varset patchheal ${Spell[Fourteenth Catalyst].RankName}
		/varset patchhealpoint 34
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Thirteenth Salve].RankName}]})  {
		/varset patchheal ${Spell[Thirteenth Salve].RankName}
		/varset patchhealpoint 34
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Twelfth Night].RankName}]})  {
		/varset patchheal ${Spell[Twelfth Night].RankName}
		/varset patchhealpoint 34
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Eleventh-Hour].RankName}]})  {
		/varset patchheal ${Spell[Eleventh-Hour].RankName}
		/varset patchhealpoint 34
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Sacred Light].RankName}]})  {
		/varset patchheal ${Spell[Sacred Light].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Ancient Hallowed Light].RankName}]})  {
		/varset patchheal ${Spell[Ancient Hallowed Light].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Pious Light].RankName}]})  {
		/varset patchheal ${Spell[Pious Light].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Holy Light].RankName}]})  {
		/varset patchheal ${Spell[Holy Light].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Supernal Light].RankName}]})  {
		/varset patchheal ${Spell[Supernal Light].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Ethereal Light].RankName}]})  {
		/varset patchheal ${Spell[Ethereal Light].RankName}
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Divine Light].RankName}]})  {
		/varset patchheal ${Spell[Divine Light].RankName}
	}
|---Group Heals Slot 5
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Word of Greater Restoration].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Greater Restoration].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Word of Greater Reformation].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Greater Reformation].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Word of Reformation].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Reformation].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Word of Rehabilitation].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Rehabilitation].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Word of Resurgence].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Resurgence].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Word of Recovery].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Recovery].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Word of Vivacity].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Vivacity].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Word of Vivification].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Vivification].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Word of Replenishment].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Replenishment].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Word of Redemption].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Redemption].RankName}
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[Word of Restoration].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Restoration].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Word of Vigor].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Vigor].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Word of Healing].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Healing].RankName}
	} else /if (${Me.Level}>=30 && ${Me.Book[${Spell[Word of Health].RankName}]})  {
		/varset GroupHealSpell1 ${Spell[Word of Health].RankName}
	}
|---Group Heals No Cure Slot 5
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Word of Mending].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Mending].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Word of Convalescence].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Convalescence].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Word of Renewal].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Renewal].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Word of Recuperation].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Recuperation].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Word of Awakening].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Awakening].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Word of Redemption].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Redemption].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Word of Vigor].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Vigor].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Word of Healing].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Healing].RankName}
	} else /if (${Me.Level}>=30 && ${Me.Book[${Spell[Word of Health].RankName}]})  {
		/varset grouphealnocure ${Spell[Word of Health].RankName}
	}
|---Group Fast Heal 103+ Only
	/if (${Me.Level}>=${Spell[Syllable of Soothing].Level} && ${Me.Book[${Spell[Syllable of Soothing].RankName}]})  {
		/varset groupfastheal ${Spell[Syllable of Soothing].RankName}
	} else /if (${Me.Level}>=108 && ${Me.Book[${Spell[Syllable of Mending].RankName}]})  {
		/varset groupfastheal ${Spell[Syllable of Mending].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Syllable of Convalescence].RankName}]})  {
		/varset groupfastheal ${Spell[Syllable of Convalescence].RankName}
	} else /if (${Me.Level}>=${Spell[Syllable of Renewal].Level} && ${Me.Book[${Spell[Syllable of Renewal].RankName}]})  {
		/varset groupfastheal ${Spell[Syllable of Renewal].RankName}
	}
|---Yaulp Setup Pre-91 AA
	/if (${Me.Level}>=91) {
		/if (!${Me.AltAbility[489]}) /echo BUY YAULP AA YOU CHEAP BASTARD!
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Yaulp XI].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp XI].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Yaulp X].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp X].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Yaulp IX].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp IX].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Yaulp VIII].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp VIII].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Yaulp VII].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp VII].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Yaulp VI].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp VI].RankName}
	} else /if (${Me.Level}>=56 && ${Me.Book[${Spell[Yaulp V].RankName}]})  {
		/varset yaulpspell ${Spell[Yaulp V].RankName}
	} 
|---Renewal Big Heal Lines
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Furial Renewal].RankName}]})  {
		/varset Renewal ${Spell[Furial Renewal].RankName}
		/varset bigheal2 ${Spell[Fervid Renewal].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Fervid Renewal].RankName}]})  {
		/varset Renewal ${Spell[Fervid Renewal].RankName}
		/varset bigheal2 ${Spell[Fraught Renewal].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Fraught Renewal].RankName}]})  {
		/varset Renewal ${Spell[Fraught Renewal].RankName}
		/varset bigheal2 ${Spell[Fervent Renewal].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Fervent Renewal].RankName}]})  {
		/varset Renewal ${Spell[Fervent Renewal].RankName}
		/varset bigheal2 ${Spell[Frenzied Renewal].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Frenzied Renewal].RankName}]})  {
		/varset Renewal ${Spell[Frenzied Renewal].RankName}
		/varset bigheal2 ${Spell[Frenetic Renewal].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Frenetic Renewal].RankName}]})  {
		/varset Renewal ${Spell[Frenetic Renewal].RankName}
		/varset bigheal2 ${Spell[Frantic Renewal].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Frantic Renewal].RankName}]})  {
		/varset Renewal ${Spell[Frantic Renewal].RankName}
		/varset bigheal2 ${Spell[Desperate Renewal].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Desperate Renewal].RankName}]})  {
		/varset Renewal ${Spell[Desperate Renewal].RankName}
	}

|---Heal Tank and Nuke Tanks Target
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Merciful Intervention].RankName}]})  {
		/varset Intervention1 ${Spell[Merciful Intervention].RankName}
		/varset Intervention2 ${Spell[Mystical Intervention].RankName}
		/varset Intervention3 ${Spell[Virtuous Intervention].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Mystical Intervention].RankName}]})  {
		/varset Intervention1 ${Spell[Mystical Intervention].RankName}
		/varset Intervention2 ${Spell[Virtuous Intervention].RankName}
		/varset Intervention3 ${Spell[Elysian Intervention].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Virtuous Intervention].RankName}]})  {
		/varset Intervention1 ${Spell[Virtuous Intervention].RankName}
		/varset Intervention2 ${Spell[Elysian Intervention].RankName}
		/varset Intervention3 ${Spell[Celestial Intervention].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Elysian Intervention].RankName}]})  {
		/varset Intervention1 ${Spell[Elysian Intervention].RankName}
		/varset Intervention2 ${Spell[Celestial Intervention].RankName}
		/varset Intervention3 ${Spell[Holy Intervention].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Celestial Intervention].RankName}]})  {
		/varset Intervention1 ${Spell[Celestial Intervention].RankName}
		/varset Intervention2 ${Spell[Holy Intervention].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Holy Intervention].RankName}]})  {
		/varset Intervention1 ${Spell[Holy Intervention].RankName}
	}
|---Nuke Target and Heal Tank - DISABLED Auto mem
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Merciful Contravention].RankName}]})  {
		/varset nukeheal1 ${Spell[Merciful Contravention].RankName}
		/varset nukeheal2 ${Spell[Ardent Contravention].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Ardent Contravention].RankName}]})  {
		/varset nukeheal1 ${Spell[Ardent Contravention].RankName}
		/varset nukeheal2 ${Spell[Virtuous Contravention].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Virtuous Contravention].RankName}]})  {
		/varset nukeheal1 ${Spell[Virtuous Contravention].RankName}
		/varset nukeheal2 ${Spell[Elysian Contravention].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Elysian Contravention].RankName}]})  {
		/varset nukeheal1 ${Spell[Elysian Contravention].RankName}
		/varset nukeheal2 ${Spell[Celestial Contravention].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Celestial Contravention].RankName}]})  {
		/varset nukeheal1 ${Spell[Celestial Contravention].RankName}
		/varset nukeheal2 ${Spell[Holy Contravention].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Holy Contravention].RankName}]})  {
		/varset nukeheal1 ${Spell[Holy Contravention].RankName}
	}
|---Stun Nukes - DISABLED Auto mem
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Awestrike].RankName}]})  {
		/varset stunnuke ${Spell[Awestrike].RankName}
		/varset StunLevel 110
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Awecrush].RankName}]})  {
		/varset stunnuke ${Spell[Awecrush].RankName}
		/varset StunLevel 105
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Aweclash].RankName}]})  {
		/varset stunnuke ${Spell[Aweclash].RankName}
		/varset StunLevel 100
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Aweburst].RankName}]})  {
		/varset stunnuke ${Spell[Aweburst].RankName}
		/varset StunLevel 95
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Awecrash].RankName}]})  {
		/varset stunnuke ${Spell[Awecrash].RankName}
		/varset StunLevel 90
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Aweshake].RankName}]})  {
		/varset stunnuke ${Spell[Aweshake].RankName}
		/varset StunLevel 85
	} 
|---Promised Heals
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Promised Remedy].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Remedy].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Promised Rehabilitation].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Rehabilitation].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Promised Reformation].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Reformation].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Promised Restitution].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Restitution].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Promised Resurgence].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Resurgence].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Promised Recuperation].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Recuperation].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Promised Restoration].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Restoration].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Promised Renewal].RankName}]})  {
		/varset PromisedHeal ${Spell[Promised Renewal].RankName}
	}
	|**
	/if (${DivineBuffOn}==1) {
		/varcalc promgem ${spellslots}-1
	} else {
		/varset promgem ${spellslots}
	}
	**|

|--Group Buff All Levels starts at 45
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Unified Hand of Assurance].RankName}]})  {
		/varset GroupHPBuff ${Spell[Unified Hand of Assurance].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Unified Hand of Surety].RankName}]})  {
		/varset GroupHPBuff ${Spell[Unified Hand of Surety].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Unified Hand of Certitude].RankName}]})  {
		/varset GroupHPBuff ${Spell[Unified Hand of Certitude].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Unified Hand of Credence].RankName}]})  {
		/varset GroupHPBuff ${Spell[Unified Hand of Credence].RankName}
		/varset GroupHPBuffName Credence
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Hand of Reliance].RankName}]})  {
		/varset GroupHPBuff ${Spell[Hand of Reliance].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Hand of Gallantry].RankName}]})  {
		/varset GroupHPBuff ${Spell[Hand of Gallantry].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Hand of Temerity].RankName}]})  {
		/varset GroupHPBuff ${Spell[Hand of Temerity].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Hand of Tenacity].RankName}]})  {
		/varset GroupHPBuff ${Spell[Hand of Tenacity].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Hand of Conviction].RankName}]})  {
		/varset GroupHPBuff ${Spell[Hand of Conviction].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Hand of Virtue].RankName}]})  {
		/varset GroupHPBuff ${Spell[Hand of Virtue].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Blessing of Aegolism].RankName}]})  {
		/varset GroupHPBuff ${Spell[Blessing of Aegolism].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Heroic Bond].RankName}]} && !${Me.Book[${Spell[Blessing of Temperance].RankName}]})  {
		/varset GroupHPBuff ${Spell[Heroic Bond].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Blessing of Temperance].RankName}]})  {
		/varset GroupHPBuff ${Spell[Blessing of Temperance].RankName}
	}

	/if (${Me.Level}>=86 && ${Me.Book[${Spell[Blessing of Will].RankName}]})  {
		/varset CasterSpeedBuff ${Spell[Blessing of Will].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Blessing of Loyalty].RankName}]})  {
		/varset CasterSpeedBuff ${Spell[Blessing of Loyalty].RankName}
	}

|--Self Buff for Mana Regen and armor
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Armor of the Merciful].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Merciful].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Armor of the Ardent].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Ardent].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Armor of the Reverent].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Reverent].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Armor of the Zealous].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Zealous].RankName}
    } else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Armor of the Earnest].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Earnest].RankName}
    } else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Armor of the Devout].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Devout].RankName}
    } else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Armor of the Solemn].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Solemn].RankName}
    } else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Armor of the Sacred].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Sacred].RankName}
    } else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Armor of the Pious].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Pious].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Armor of the Zealot].RankName}]})  {
		/varset SelfBuff ${Spell[Armor of the Zealot].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Ancient High Priest's Bulwark].RankName}]})  {
		/varset SelfBuff ${Spell[Ancient High Priest's Bulwark].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Blessed Armor of the Risen].RankName}]})  {
		/varset SelfBuff ${Spell[Blessed Armor of the Risen].RankName}
	}

	/if (${Me.Level}>=${Spell[Ward of Retaliation].Level} && ${Me.Book[${Spell[Ward of Retaliation].RankName}]})  {
		/varset Retaliation ${Spell[Ward of Retaliation].RankName}
	}
|--Self buff casts group heal on AE spell damage
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Divine Reaction].RankName}]})  {
		/varset GroupHealProcBuff ${Spell[Divine Reaction].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Divine Response].RankName}]})  {
		/varset GroupHealProcBuff ${Spell[Divine Response].RankName}
	}
|--Tank Buff Traditionally Shining Series of Buffs
    /if (${Me.Level}>=109 && ${Me.Book[${Spell[Shining Fortress].RankName}]})  {
		/varset TankBuff ${Spell[Shining Fortress].RankName}
    } else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Shining Bulwark].RankName}]})  {
		/varset TankBuff ${Spell[Shining Bulwark].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Shining Bastion].RankName}]})  {
		/varset TankBuff ${Spell[Shining Bastion].RankName}
    } else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Shining Armor].RankName}]})  {
		/varset TankBuff ${Spell[Shining Armor].RankName}
    } else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Shining Rampart].RankName}]})  {
		/varset TankBuff ${Spell[Shining Rampart].RankName}
    }
	/varset TankBuffMatch Shining Defense
|--Group Vie Buff
	/if (${Me.Book[${Spell[Rallied Greater Guard of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Greater Guard of Vie].RankName}
	} else /if (${Me.Book[${Spell[Rallied Greater Ward of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Greater Ward of Vie].RankName}
	} else /if (${Me.Book[${Spell[Rallied Bastion of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Bastion of Vie].RankName}
    } else /if (${Me.Book[${Spell[Rallied Armor of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Armor of Vie].RankName}
    } else /if (${Me.Book[${Spell[Rallied Rampart of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Rampart of Vie].RankName}
    } else /if (${Me.Book[${Spell[Rallied Palladium of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Palladium of Vie].RankName}
    } else /if (${Me.Book[${Spell[Rallied Shield of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Shield of Vie].RankName}
    } else /if (${Me.Book[${Spell[Rallied Aegis of Vie].RankName}]})  {
		/varset GroupVieBuff ${Spell[Rallied Aegis of Vie].RankName}
    }
|--Aura Buffs
	/if (${Me.Level}>=100 && ${Me.Book[${Spell[Aura of the Reverent].RankName}]})  {
		/varset Aura1 ${Spell[Aura of the Reverent].RankName}
		/if (${Me.Book[${Spell[Aura of Divinity].RankName}]}&&${Me.AltAbility[Spirit Mastery].ID}) {
			/varset Aura2 ${Spell[Aura of Divinity].RankName}
		} else /if (${Me.Book[${Spell[Circle of Divinity].RankName}]}&&${Me.AltAbility[Spirit Mastery].ID}) {
			/varset Aura2 ${Spell[Circle of Divinity].RankName}
		}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Circle of Divinity].RankName}]})  {
		/varset Aura1 ${Spell[Circle of Divinity].RankName}
		/if (${Me.Book[${Spell[Aura of the Pious].RankName}]}&&${Me.AltAbility[Spirit Mastery].ID}) {
			/varset Aura2 ${Spell[Aura of the Pious].RankName}
			}
    } else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Aura of the Pious].RankName}]})  {
		/varset Aura1 ${Spell[Aura of the Pious].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Aura of the Zealot].RankName}]})  {
		/varset Aura1 ${Spell[Aura of the Zealot].RankName}
	}
|--Divine Buffs REQUIRES extra spell slot because of the 90s recast
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Divine Imposition].RankName}]}) {
		/varset DivineBuff ${Spell[Divine Imposition].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Divine Indemnification].RankName}]})  {
		/varset DivineBuff ${Spell[Divine Indemnification].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Divine Interposition].RankName}]})  {
		/varset DivineBuff ${Spell[Divine Interposition].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Divine Invocation].RankName}]})  {
		/varset DivineBuff ${Spell[Divine Invocation].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Divine Intercession].RankName}]})  {
		/varset DivineBuff ${Spell[Divine Intercession].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Divine Intervention].RankName}]})  {
		/varset DivineBuff ${Spell[Divine Intervention].RankName}
	} else /if (${Me.Level}>=51 && ${Me.Book[${Spell[Death Pact].RankName}]})  {
		/varset DivineBuff ${Spell[Death Pact].RankName}
	}
|--Reverse Damage Shield
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Curate's Retort].RankName}]})  {
		/varset ReverseDS ${Spell[Curate's Retort].RankName}
	} else /if (${Me.Level}>=109 && ${Me.Book[${Spell[Mark of Shandral].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of Shandral].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Mark of the Vicarum].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Vicarum].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Mark of the Zealot].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Zealot].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Mark of the Adherent].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Adherent].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Mark of the Devout].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Devout].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Mark of the Unsullied].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Unsullied].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Mark of the Devoted].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Devoted].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Mark of the Martyr].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Martyr].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Mark of the Blameless].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Blameless].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Mark of the Righteous].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of the Righteous].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Mark of Retribution].RankName}]})  {
		/varset ReverseDS ${Spell[Mark of Retribution].RankName}
	}
|--Symbols
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Unity of Emra].RankName}]})  {
		/varset SymbolBuff ${Spell[Unity of Emra].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Unity of Nonia].RankName}]})  {
		/varset SymbolBuff ${Spell[Unity of Nonia].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Unity of Gezat].RankName}]})  {
		/varset SymbolBuff ${Spell[Unity of Gezat].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Unity of the Triumvirate].RankName}]})  {
		/varset SymbolBuff ${Spell[Unity of the Triumvirate].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Symbol of Ealdun].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Ealdun].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Symbol of Darianna].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Darianna].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Symbol of Kaerra].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Kaerra].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Symbol of Elushar].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Elushar].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Symbol of Balikor].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Balikor].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Symbol of Kazad].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Kazad].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Symbol of Marzin].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Marzin].RankName}
	} else /if (${Me.Level}>=41 && ${Me.Book[${Spell[Symbol of Naltron].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Naltron].RankName}
	} else /if (${Me.Level}>=31 && ${Me.Book[${Spell[Symbol of Pinzarn].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Pinzarn].RankName}
	} else /if (${Me.Level}>=21 && ${Me.Book[${Spell[Symbol of Ryltan].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Ryltan].RankName}
	} else /if (${Me.Level}>=11 && ${Me.Book[${Spell[Symbol of Transal].RankName}]})  {
		/varset SymbolBuff ${Spell[Symbol of Transal].RankName}
	}
|--Group Symbols
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Unified Hand of Emra].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Unified Hand of Emra].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Unified Hand of Nonia].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Unified Hand of Nonia].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Unified Hand of Gezat].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Unified Hand of Gezat].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Unified Hand of the Triumvirate].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Unified Hand of the Triumvirate].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Ealdun's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Ealdun's Mark].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Darianna's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Darianna's Mark].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Kaerra's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Kaerra's Mark].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Elushar's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Elushar's Mark].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Balikor's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Balikor's Mark].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Kazad's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Kazad's Mark].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Naltron's Mark].RankName}]})  {
		/varset GroupSymbolBuff ${Spell[Naltron's Mark].RankName}
	}
|--Single Target HP Buffs
	/if (${Me.Level}>=102 && ${Me.Book[${Spell[Unified Surety].RankName}]})  {
		/varset HPBuff ${Spell[Unified Surety].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Unified Certitude].RankName}]})  {
		/varset HPBuff ${Spell[Unified Certitude].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Unified Credence].RankName}]})  {
		/varset HPBuff ${Spell[Unified Credence].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Reliance].RankName}]})  {
		/varset HPBuff ${Spell[Reliance].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Gallantry].RankName}]})  {
		/varset HPBuff ${Spell[Gallantry].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Temerity].RankName}]})  {
		/varset HPBuff ${Spell[Temerity].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Tenacity].RankName}]})  {
		/varset HPBuff ${Spell[Tenacity].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Conviction].RankName}]})  {
		/varset HPBuff ${Spell[Conviction].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Virtue].RankName}]})  {
		/varset HPBuff ${Spell[Virtue].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Aegolism].RankName}]})  {
		/varset HPBuff ${Spell[Aegolism].RankName}
	} else /if (${Me.Level}>=40 && ${Me.Book[${Spell[Temperance].RankName}]})  {
		/varset HPBuff ${Spell[Temperance].RankName}
|	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Heroism].RankName}]})  {
		/varset HPBuff ${Spell[Heroism].RankName}
	} else /if (${Me.Level}>=32 && ${Me.Book[${Spell[Valor].RankName}]})  {
		/varset HPBuff ${Spell[Valor].RankName}
	} else /if (${Me.Level}>=22 && ${Me.Book[${Spell[Bravery].RankName}]})  {
		/varset HPBuff ${Spell[Bravery].RankName}
	} else /if (${Me.Level}>=17 && ${Me.Book[${Spell[Daring].RankName}]})  {
		/varset HPBuff ${Spell[Daring].RankName}
	} else /if (${Me.Level}>=7 && ${Me.Book[${Spell[Center].RankName}]})  {
		/varset HPBuff ${Spell[Center].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Courage].RankName}]})  {
		/varset HPBuff ${Spell[Courage].RankName}
	}
|--AllianceBuff
	/if (${Me.Level}>=103 && ${Me.Book[${Spell[Divine Alliance].RankName}]})  {
		/varset AllianceBuff ${Spell[Divine Alliance].RankName}
	}
|-Setup Group Buff
	|**
	/if (${usedruid}==1) {
		/varset GroupBuff ${GroupSymbolBuff}
	} else {
		/varset GroupBuff ${GroupHPBuff}
	}
	**|


	/if (${Me.Level}>=56 && ${Me.Book[${Spell[Reviviscence].RankName}]})  {
		/varset RezSpell ${Spell[Reviviscence].RankName}
	} else /if (${Me.Level}>=47 && ${Me.Book[${Spell[Resurrection].RankName}]})  {
		/varset RezSpell ${Spell[Resurrection].RankName}
	} 

	/if (${Me.Level}>=76 && ${Me.Book[${Spell[Superior Reviviscence].RankName}]})  {
		/varset MassRezSpell ${Spell[Superior Reviviscence].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Greater Reviviscence].RankName}]})  {
		/varset MassRezSpell ${Spell[Greater Reviviscence].RankName}
	} 

	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellslots 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellslots 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellslots 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellslots 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellslots 9
|-	/call CheckPlugin MQ2WorstHurt
	/if (${Me.AltAbility[252].Name.Find[disabled]} && ${Me.AltAbilityReady[252]}) {
		/alt act 252
		/delay 5
	}

	/call clr_load_spellbar

/return
|----------------------------------------------------------------------------
|- SUB: BIND BNDGroupCure - 
|----------------------------------------------------------------------------
Sub Bind_BNDGroupCure(int RequestorID)
	|-/call GroupCure
	/varcalc CureCount ${CureCount}+1
	/varset CureID ${RequestorID}
/return 
|----------------------------------------------------------------------------
|- SUB: BIND CureOff - 
|----------------------------------------------------------------------------
Sub Bind_CureOff
	/varset NoCures 1
	/varset CureOther 0
	/call ${Me.Class.ShortName.Lower}_load_spellbar
	/echo WILL NOT CAST ANY CURES
/return 