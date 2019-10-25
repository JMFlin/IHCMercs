|- ihcbstutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub BstSetup
|-Create Alias
	|-- Toggles
	/squelch /alias /byos			/setvarint Toggle BringYourOwnSpells
	/squelch /alias /tglaoe			/setvarint Toggle UseAoE
	/squelch /alias /tglbp			/setvarint Toggle ChestCombatCast
	/squelch /alias /tglpet			/setvarint Toggle UsePet
	/squelch /alias /tglpoison		/setvarint Toggle UsePoisons
	/squelch /alias /tgldots		/setvarint Toggle DoDot
	/squelch /alias /tglmezbreak	/setvarint Toggle AllowMezBreak
	/squelch /alias /tglslow		/setvarint Toggle DoSlow
	/squelch /alias /tglferocity	/setvarint Toggle DoFerocity
	/squelch /alias /tglpetslow		/setvarint Toggle DoPetSlow
|-Spells
	/declare SwarmPet			string outer NULL
	/declare NukeSpell1			string outer NULL
	/declare NukeSpell2			string outer NULL
	/declare NukeSpell3			string outer NULL
	/declare NukeSpell4			string outer NULL
	/declare NukeSpell5			string outer NULL
	/declare DoTSpell1			string outer NULL
	/declare DoTSpell2			string outer NULL
	/declare SlowSpell			string outer NULL
	/declare DichoSpell			string outer NULL
	/declare HealSpell1			string outer NULL
	/declare PetHealSpell		string outer NULL
	/declare FocusSpell			string outer NULL
	/declare AtkBuff			string outer NULL
	/declare PetSpell			string outer NULL
	/declare PetEnduranceProc	string outer NULL
	/declare PetSpellGuard		string outer NULL
	/declare PetSlowProc		string outer NULL
	/declare PetOffenseBuff		string outer NULL
	/declare PetDefenseBuff		string outer NULL
	/declare PetHaste			string outer NULL
	/declare PetGrowl			string outer NULL
	/declare PetHealProc		string outer NULL
	/declare PetDamageProc		string outer NULL
	/declare UnityBuff			string outer NULL
	/declare KillShotBuff		string outer NULL
	/declare RunSpeedBuff		string outer NULL
	/declare ManaRegenBuff		string outer NULL
	/declare ManaRegenBuffName	string outer NULL
	/declare AtkHPBuff			string outer NULL
	/declare AtkHPBuffName		string outer NULL
|-discs
	/declare EndRegenDisc		string outer NULL
	/declare Maul				string outer NULL
	/declare SingleClaws		string outer NULL
	/declare BeastialBuffDisc	string outer NULL
	/declare AEClaws			string outer NULL
	/declare HHEFuryDisc		string outer NULL
	/declare DmgModDisc			string outer NULL
	/declare EndRegenProcDisc	string outer NULL
|-Config Options
	/call LoadCommonConfig
	/call LoadIni Buffs UseFocus				int 1
	/call LoadIni Buffs UseRunSpeed				int 1
	/call LoadIni Combat AllowMezBreak		 	int 0
	/call LoadIni Combat DoSlow					int 1
	/call LoadIni Combat DoDot					int 1
	/call LoadIni Combat Manatonuke				int 5
	/call LoadIni Combat StickHow				string behind
	/call LoadIni Combat StopNukeAggro			int 80
	/call LoadIni Combat UseAoE					int 0
	/call LoadIni Combat UseMelee		 		int 1
	/call LoadIni Healing DoHeals				int 1
	/call LoadIni Healing DynamicHealing		int 0
	/call LoadIni Healing Healpoint				int 30
	/call LoadIni Healing PetHealpoint			int 40
	/call LoadIni Healing TBMHealpoint			int 65
	/call LoadIni Healing RaidHealpoint			int 65
	/call LoadIni Item ChestItemName			string NULL
	/call LoadIni Item ChestCombatCast			int 0
	/call LoadIni Item UsePoisons		 		int 0
	/call LoadIni Item PoisonName				string NULL
	/call LoadIni Item PoisonBuffName			string NULL
	/call LoadIni Options BringYourOwnSpells	int 0
	/call LoadIni Options DoFerocity			int 0
	/call LoadIni Options FocParagonManaPct		int 80
	/call LoadIni Options FocParagonEndPct		int 80
	/call LoadIni Options ParagonManaPct		int 80
	/call LoadIni Pet UsePet		 			int 1
	/call LoadIni Pet DoPetTank		 			int 0
	/call LoadIni Pet UseSwarmpet		 		int 0
	/call LoadIni Pet DoPetSlow					int 0
|-Declare spell variables
	/declare spellmisc 			int outer 8
	/declare GroupBuffRecast 	int outer 0
	/declare miscspellremem		string outer NULL
	/declare CastResult         string outer
	/declare spellrememtimer	timer outer 0
	/declare fparatimer2		timer outer 60s
	/declare groupbufftimer		timer outer 0
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9
	/if (${Me.AltAbility[8300].Name.Find[disabled]} && ${Me.AltAbilityReady[8300]}) {
		/alt act 8300
		/delay 5
	}
/return 
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges
	/varset changetoini 0
	/call SaveCommonConfig
	/call SetIni Combat AllowMezBreak		 	int ${AllowMezBreak}
	/call SetIni Combat DoSlow					int ${DoSlow}
	/call SetIni Combat DoDot					int ${DoDot}
	/call SetIni Combat Manatonuke				int ${Manatonuke}
	/call SetIni Combat StopNukeAggro			int ${StopNukeAggro}
	/call SetIni Combat UseAoE					int ${UseAoE}
	/call SetIni Combat UseMelee		 		int ${UseMelee}
	/call SetIni Healing DoHeals				int ${DoHeals}
	/call SetIni Healing DynamicHealing			int ${DynamicHealing}
	/call SetIni Healing Healpoint				int ${Healpoint}
	/call SetIni Healing PetHealpoint			int ${PetHealpoint}
	/call SetIni Healing TBMHealpoint			int ${TBMHealpoint}
	/call SetIni Healing RaidHealpoint			int ${RaidHealpoint}
	/call SetIni Item ChestCombatCast			int ${ChestCombatCast}
	/call SetIni Item UsePoisons		 		int ${UsePoisons}
	/call SetIni Options BringYourOwnSpells		int ${BringYourOwnSpells}
	/call SetIni Options DoFerocity				int ${DoFerocity}
	/call SetIni Options FocParagonManaPct		int ${FocParagonManaPct}
	/call SetIni Options FocParagonEndPct		int ${FocParagonEndPct}
	/call SetIni Options ParagonManaPct			int ${ParagonManaPct}
	/call SetIni Pet UsePet		 				int ${UsePet}
	/call SetIni Pet DoPetTank		 			int ${DoPetTank}
	/call SetIni Pet UseSwarmpet		 		int ${UseSwarmpet}
	/call SetIni Pet DoPetSlow			 		int ${DoPetSlow}
/return
|* ------------------------------------------------------------------------------------------
| SUB: LoadSpellBar
|------------------------------------------------------------------------------------------ *|
Sub LoadSpellBar
	/if (!${BringYourOwnSpells}) {
		/if (${Me.Standing}) /sit
		/delay 10 ${Me.Sitting}
		/echo \aw Loading Spell Bar
		/call LoadSpellGem "${HealSpell1}" 1
		/call LoadSpellGem "${PetHealSpell}" 2
		/call LoadSpellGem "${NukeSpell5}" 3
		/call LoadSpellGem "${NukeSpell4}" 4
		/call LoadSpellGem "${DoTSpell1}" 5		
		/if (${Me.Level}>105 && ${spellmisc}>=13) {
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${DoTSpell2}" 7
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${DichoSpell}" 9
			/call LoadSpellGem "${NukeSpell2}" 10
			/call LoadSpellGem "${NukeSpell1}" 11
			/call LoadSpellGem "${AtkBuff}" 12
			/call LoadSpellGem "${PetSlowProc}" 13
			/varset miscspellremem ${PetSlowProc}
		} else /if (${Me.Level}>100 && ${spellmisc}>=12 && ${DichoSpell.NotEqual[NULL]}) {
			/call LoadSpellGem "${SwarmPet}" 6
			/if (${DoDot}) {
				/call LoadSpellGem "${DoTSpell2}" 7
			} else {
				/call LoadSpellGem "${PetSlowProc}" 7
			}
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${DichoSpell}" 9
			/call LoadSpellGem "${NukeSpell2}" 10
			/call LoadSpellGem "${NukeSpell1}" 11
			/call LoadSpellGem "${AtkBuff}" 12
			/varset miscspellremem ${AtkBuff}
		} else /if (${Me.Level}>89 && ${spellmisc}>=12 && ${NukeSpell1.NotEqual[NULL]}) {
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${PetSlowProc}" 9
			/call LoadSpellGem "${NukeSpell2}" 10
			/call LoadSpellGem "${NukeSpell1}" 11
			/call LoadSpellGem "${AtkBuff}" 12
			/varset miscspellremem ${AtkBuff}
		} else /if (${Me.Level}>83 && ${spellmisc}>=12 && ${NukeSpell2.NotEqual[NULL]}) {
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${PetGrowl}" 9
			/call LoadSpellGem "${NukeSpell2}" 10
			/call LoadSpellGem "${PetSlowProc}" 11
			/call LoadSpellGem "${AtkBuff}" 12
			/varset miscspellremem ${AtkBuff}
		} else /if (${Me.Level}>79 && ${spellmisc}>=11) {
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${PetGrowl}" 9
			/call LoadSpellGem "${AtkBuff}" 10
			/call LoadSpellGem "${PetSlowProc}" 11
			/if (${spellmisc}==11) /varset miscspellremem ${PetSlowProc}
		} else /if (${Me.Level}>74 && ${Me.Level}<81 && ${spellmisc}>=10) {
			/if (!${DoDot}) {
				/call LoadSpellGem "${PetSlowProc}" 5
			}
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${PetGrowl}" 9
			/call LoadSpellGem "${AtkBuff}" 10
			/varset miscspellremem ${AtkBuff}
		} else /if (${Me.Level}>72 && ${Me.Level}<75) {
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${NukeSpell3}" 8
			/call LoadSpellGem "${PetGrowl}" 9
			/varset miscspellremem ${PetGrowl}
		} else /if (${Me.Level}>67 && ${Me.Level}<73) {
			/call LoadSpellGem "${SwarmPet}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${PetGrowl}" 8
		} else {
			/call LoadSpellGem "${PetDamageProc}" 6
			/call LoadSpellGem "${SlowSpell}" 7
			/call LoadSpellGem "${PetSpell}" 8
			/if (${Me.Level}<=55) /varset miscspellremem ${PetSpell}
		}
	}
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub CheckSpells
|-Swarm Pet*
	/if (${Me.Level}>=${Spell[Akalit's Feralgia].Level} && ${Me.Book[${Spell[Akalit's Feralgia].RankName}]}) {
		/varset SwarmPet ${Spell[Akalit's Feralgia].RankName}
	} else /if (${Me.Level}>=${Spell[Krenk's Feralgia].Level} && ${Me.Book[${Spell[Krenk's Feralgia].RankName}]}) {
		/varset SwarmPet ${Spell[Krenk's Feralgia].RankName}
	} else /if (${Me.Level}>=${Spell[Kesar's Feralgia].Level} && ${Me.Book[${Spell[Kesar's Feralgia].RankName}]}) {
		/varset SwarmPet ${Spell[Kesar's Feralgia].RankName}
	} else /if (${Me.Level}>=${Spell[Yahnoa's Feralgia].Level} && ${Me.Book[${Spell[Yahnoa's Feralgia].RankName}]}) {
		/varset SwarmPet ${Spell[Yahnoa's Feralgia].RankName}
	} else /if (${Me.Level}>=${Spell[Tuzil's Feralgia].Level} && ${Me.Book[${Spell[Tuzil's Feralgia].RankName}]}) {
		/varset SwarmPet ${Spell[Tuzil's Feralgia].RankName}
	} else /if (${Me.Level}>=${Spell[Haergen's Feralgia].Level} && ${Me.Book[${Spell[Haergen's Feralgia].RankName}]}) {
		/varset SwarmPet ${Spell[Haergen's Feralgia].RankName}
	} else /if (${Me.Level}>=${Spell[Howl at the Moon].Level} && ${Me.Book[${Spell[Howl at the Moon].RankName}]}) {
		/varset SwarmPet ${Spell[Howl at the Moon].RankName}
	} else /if (${Me.Level}>=${Spell[Bark at the Moon].Level} && ${Me.Book[${Spell[Bark at the Moon].RankName}]}) {
		/varset SwarmPet ${Spell[Bark at the Moon].RankName}
	} else /if (${Me.Level}>=${Spell[Bestial Empathy].Level} && ${Me.Book[${Spell[Bestial Empathy].RankName}]}) {
		/varset SwarmPet ${Spell[Bestial Empathy].RankName}
	}
|-Cold/Poison Nuke fast cast*
	/if (${Me.Level}>=${Spell[Frozen Toxin].Level} && ${Me.Book[${Spell[Frozen Toxin].RankName}]}) {
		/varset NukeSpell1 ${Spell[Frozen Toxin].RankName}
	} else /if (${Me.Level}>=${Spell[Frozen Miasma].Level} && ${Me.Book[${Spell[Frozen Miasma].RankName}]}) {
		/varset NukeSpell1 ${Spell[Frozen Miasma].RankName}
	} else /if (${Me.Level}>=${Spell[Frozen Carbomate].Level} && ${Me.Book[${Spell[Frozen Carbomate].RankName}]}) {
		/varset NukeSpell1 ${Spell[Frozen Carbomate].RankName}
	} else /if (${Me.Level}>=${Spell[Frozen Cyanin].Level} && ${Me.Book[${Spell[Frozen Cyanin].RankName}]}) {
		/varset NukeSpell1 ${Spell[Frozen Cyanin].RankName}
	} else /if (${Me.Level}>=${Spell[Frozen Venin].Level} && ${Me.Book[${Spell[Frozen Venin].RankName}]}) {
		/varset NukeSpell1 ${Spell[Frozen Venin].RankName}
	} else /if (${Me.Level}>=${Spell[Frozen Venom].Level} && ${Me.Book[${Spell[Frozen Venom].RankName}]}) {
		/varset NukeSpell1 ${Spell[Frozen Venom].RankName}
	}
|-Cold/Poison/Disease Nuke fast cast*
	/if (${Me.Level}>=${Spell[Beramos' Maelstrom].Level} && ${Me.Book[${Spell[Beramos' Maelstrom].RankName}]})  {
		/varset NukeSpell2 ${Spell[Beramos' Maelstrom].RankName}
	} else /if (${Me.Level}>=${Spell[Visoracius' Maelstrom].Level} && ${Me.Book[${Spell[Visoracius' Maelstrom].RankName}]})  {
		/varset NukeSpell2 ${Spell[Visoracius' Maelstrom].RankName}
	} else /if (${Me.Level}>=${Spell[Nak's Maelstrom].Level} && ${Me.Book[${Spell[Nak's Maelstrom].RankName}]})  {
		/varset NukeSpell2 ${Spell[Nak's Maelstrom].RankName}
	} else /if (${Me.Level}>=${Spell[Bale's Maelstrom].Level} && ${Me.Book[${Spell[Bale's Maelstrom].RankName}]})  {
		/varset NukeSpell2 ${Spell[Bale's Maelstrom].RankName}
	} else /if (${Me.Level}>=${Spell[Kron's Maelstrom].Level} && ${Me.Book[${Spell[Kron's Maelstrom].RankName}]})  {
		/varset NukeSpell2 ${Spell[Kron's Maelstrom].RankName}
	}
|-Poison Nuke fast cast*
	/if (${Me.Level}>=${Spell[Mawmun's Bite].Level} && ${Me.Book[${Spell[Mawmun's Bite].RankName}]})  {
		/varset NukeSpell3 ${Spell[Mawmun's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Kreig's Bite].Level} && ${Me.Book[${Spell[Kreig's Bite].RankName}]})  {
		/varset NukeSpell3 ${Spell[Kreig's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Poantaar's Bite].Level} && ${Me.Book[${Spell[Poantaar's Bite].RankName}]})  {
		/varset NukeSpell3 ${Spell[Poantaar's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Rotsil's Bite].Level} && ${Me.Book[${Spell[Rotsil's Bite].RankName}]})  {
		/varset NukeSpell3 ${Spell[Rotsil's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Sarsez' Bite].Level} && ${Me.Book[${Spell[Sarsez' Bite].RankName}]})  {
		/varset NukeSpell3 ${Spell[Sarsez' Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Bite of the Vitrik].Level} && ${Me.Book[${Spell[Bite of the Vitrik].RankName}]})  {
		/varset NukeSpell3 ${Spell[Bite of the Vitrik].RankName}
	} else /if (${Me.Level}>=${Spell[Bite of the Borrower].Level} && ${Me.Book[${Spell[Bite of the Borrower].RankName}]})  {
		/varset NukeSpell3 ${Spell[Bite of the Borrower].RankName}
	} else /if (${Me.Level}>=${Spell[Bite of the Empress].Level} && ${Me.Book[${Spell[Bite of the Empress].RankName}]})  {
		/varset NukeSpell3 ${Spell[Bite of the Empress].RankName}
	}
|-Lance#1 Timer#11 Ice Nuke fast cast* 
	/if (${Me.Level}>=${Spell[Kromtus Lance].Level} && ${Me.Book[${Spell[Kromtus Lance].RankName}]})  {
		/varset NukeSpell4 ${Spell[Kromtus Lance].RankName}
	} else /if (${Me.Level}>=${Spell[Frostrift Lance].Level} && ${Me.Book[${Spell[Frostrift Lance].RankName}]})  {
		/varset NukeSpell4 ${Spell[Frostrift Lance].RankName}
	} else /if (${Me.Level}>=${Spell[Frigid Lance].Level} && ${Me.Book[${Spell[Frigid Lance].RankName}]})  {
		/varset NukeSpell4 ${Spell[Frigid Lance].RankName}
	} else /if (${Me.Level}>=${Spell[Spiked Sleet].Level} && ${Me.Book[${Spell[Spiked Sleet].RankName}]})  {
		/varset NukeSpell4 ${Spell[Spiked Sleet].RankName}
	} else /if (${Me.Level}>=${Spell[Glacier Spear].Level} && ${Me.Book[${Spell[Glacier Spear].RankName}]})  {
		/varset NukeSpell4 ${Spell[Glacier Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Trushar's Frost].Level} && ${Me.Book[${Spell[Trushar's Frost].RankName}]})  {
		/varset NukeSpell4 ${Spell[Trushar's Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Ice Shard].Level} && ${Me.Book[${Spell[Ice Shard].RankName}]})  {
		/varset NukeSpell4 ${Spell[Ice Shard].RankName}
	} else /if (${Me.Level}>=${Spell[Ice Spear].Level} && ${Me.Book[${Spell[Ice Spear].RankName}]})  {
		/varset NukeSpell4 ${Spell[Ice Spear].RankName}
	}
|-Lance#2 Timer#7 Ice Nuke fast cast*
	/if (${Me.Level}>=${Spell[Frostbite Lance].Level} && ${Me.Book[${Spell[Frostbite Lance].RankName}]})  {
		/varset NukeSpell5 ${Spell[Frostbite Lance].RankName}
	} else /if (${Me.Level}>=${Spell[Kromrif Lance].Level} && ${Me.Book[${Spell[Kromrif Lance].RankName}]})  {
		/varset NukeSpell5 ${Spell[Kromrif Lance].RankName}
	} else /if (${Me.Level}>=${Spell[Glacial Lance].Level} && ${Me.Book[${Spell[Glacial Lance].RankName}]})  {
		/varset NukeSpell5 ${Spell[Glacial Lance].RankName}
	} else /if (${Me.Level}>=${Spell[Jagged Torrent].Level} && ${Me.Book[${Spell[Jagged Torrent].RankName}]})  {
		/varset NukeSpell5 ${Spell[Jagged Torrent].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Savage Ice].Level} && ${Me.Book[${Spell[Ancient Savage Ice].RankName}]})  {
		/varset NukeSpell5 ${Spell[Ancient Savage Ice].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Frozen Chaos].Level} && ${Me.Book[${Spell[Ancient Frozen Chaos].RankName}]})  {
		/varset NukeSpell5 ${Spell[Ancient Frozen Chaos].RankName}
	} else /if (${Me.Level}>=${Spell[Frost Spear].Level} && ${Me.Book[${Spell[Frost Spear].RankName}]})  {
		/varset NukeSpell5 ${Spell[Frost Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Frost Shard].Level} && ${Me.Book[${Spell[Frost Shard].RankName}]})  {
		/varset NukeSpell5 ${Spell[Frost Shard].RankName}
	} else /if (${Me.Level}>=${Spell[Blast of Frost].Level} && ${Me.Book[${Spell[Blast of Frost].RankName}]})  {
		/varset NukeSpell5 ${Spell[Blast of Frost].RankName}
	}
|-Poison DoT Instant Cast*
	/if (${Me.Level}>=${Spell[Polybiad Blood].Level} && ${Me.Book[${Spell[Polybiad Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Polybiad Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Glistenwing Blood].Level} && ${Me.Book[${Spell[Glistenwing Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Glistenwing Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Asp Blood].Level} && ${Me.Book[${Spell[Asp Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Asp Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Binaesa Blood].Level} && ${Me.Book[${Spell[Binaesa Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Binaesa Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Spinechiller Blood].Level} && ${Me.Book[${Spell[Spinechiller Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Spinechiller Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Ikaav Blood].Level} && ${Me.Book[${Spell[Ikaav Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Ikaav Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Falrazim's Gnashing].Level} && ${Me.Book[${Spell[Falrazim's Gnashing].RankName}]}) {
		/varset DoTSpell1 ${Spell[Falrazim's Gnashing].RankName}
	} else /if (${Me.Level}>=${Spell[Diregriffon's Bite].Level} && ${Me.Book[${Spell[Diregriffon's Bite].RankName}]}) {
		/varset DoTSpell1 ${Spell[Diregriffon's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Chimera Blood].Level} && ${Me.Book[${Spell[Chimera Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Chimera Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Turepta Blood].Level} && ${Me.Book[${Spell[Turepta Blood].RankName}]}) {
		/varset DoTSpell1 ${Spell[Turepta Blood].RankName}
	} else /if (${Me.Level}>=${Spell[Scorpion Venom].Level} && ${Me.Book[${Spell[Scorpion Venom].RankName}]}) {
		/varset DoTSpell1 ${Spell[Scorpion Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Venom of the Snake].Level} && ${Me.Book[${Spell[Venom of the Snake].RankName}]}) {
		/varset DoTSpell1 ${Spell[Venom of the Snake].RankName}
	} else /if (${Me.Level}>=${Spell[Envenomed Breath].Level} && ${Me.Book[${Spell[Envenomed Breath].RankName}]}) {
		/varset DoTSpell1 ${Spell[Envenomed Breath].RankName}
	} else /if (${Me.Level}>=${Spell[Tainted Breath].Level} && ${Me.Book[${Spell[Tainted Breath].RankName}]}) {
		/varset DoTSpell1 ${Spell[Tainted Breath].RankName}
	}
|-Cold DoT Instant Cast*
/if (${Me.Level}>=${Spell[Ekron's Chill].Level} && ${Me.Book[${Spell[Ekron's Chill].RankName}]}) {
		/varset DoTSpell2 ${Spell[Ekron's Chill].RankName}
	} else /if (${Me.Level}>=${Spell[Kirchen's Chill].Level} && ${Me.Book[${Spell[Kirchen's Chill].RankName}]}) {
		/varset DoTSpell2 ${Spell[Kirchen's Chill].RankName}
	} else /if (${Me.Level}>=${Spell[Edoth's Chill].Level} && ${Me.Book[${Spell[Edoth's Chill].RankName}]}) {
		/varset DoTSpell2 ${Spell[Edoth's Chill].RankName}
	}
|-Dicho Spell*
/if (${Me.Level}>=${Spell[Dissident Fury].Level} && ${Me.Book[${Spell[Dissident Fury].RankName}]}) {
	/varset DichoSpell ${Spell[Dissident Fury].RankName}
	} else /if (${Me.Level}>=${Spell[Dichotomic Fury].Level} && ${Me.Book[${Spell[Dichotomic Fury].RankName}]}) {
	/varset DichoSpell ${Spell[Dichotomic Fury].RankName}
	}
|-Slow Spell*
	/if (${Me.Level}>=${Spell[Sha's Reprisal].Level} && ${Me.Book[${Spell[Sha's Reprisal].RankName}]}) {
		/varset SlowSpell ${Spell[Sha's Reprisal].RankName}
	} else /if (${Me.Level}>=${Spell[Sha's Legacy].Level} && ${Me.Book[${Spell[Sha's Legacy].RankName}]}) {
		/varset SlowSpell ${Spell[Sha's Legacy].RankName}
	} else /if (${Me.Level}>=${Spell[Sha's Revenge].Level} && ${Me.Book[${Spell[Sha's Revenge].RankName}]}) {
		/varset SlowSpell ${Spell[Sha's Revenge].RankName}
	} else /if (${Me.Level}>=${Spell[Sha's Advantage].Level} && ${Me.Book[${Spell[Sha's Advantage].RankName}]}) {
		/varset SlowSpell ${Spell[Sha's Advantage].RankName}
	} else /if (${Me.Level}>=${Spell[Sha's Lethargy].Level} && ${Me.Book[${Spell[Sha's Lethargy].RankName}]}) {
		/varset SlowSpell ${Spell[Sha's Lethargy].RankName}
	} else /if (${Me.Level}>=${Spell[Drowsy].Level} && ${Me.Book[${Spell[Drowsy].RankName}]}) {
		/varset SlowSpell ${Spell[Drowsy].RankName}
	}
|-Single target HealSpell1*
	/if (${Me.Level}>=${Spell[Deltro's Mending].Level} && ${Me.Book[${Spell[Deltro's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Deltro's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Sabhattin's Mending].Level} && ${Me.Book[${Spell[Sabhattin's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Sabhattin's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Jaerol's Mending].Level} && ${Me.Book[${Spell[Jaerol's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Jaerol's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Mending of the Izon].Level} && ${Me.Book[${Spell[Mending of the Izon].RankName}]}) {
		/varset HealSpell1 ${Spell[Mending of the Izon].RankName}
	} else /if (${Me.Level}>=${Spell[Jorra's Mending].Level} && ${Me.Book[${Spell[Jorra's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Jorra's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Cadmael's Mending].Level} && ${Me.Book[${Spell[Cadmael's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Cadmael's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Daria's Mending].Level} && ${Me.Book[${Spell[Daria's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Daria's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Minohten Mending].Level} && ${Me.Book[${Spell[Minohten Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Minohten Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Muada's Mending].Level} && ${Me.Book[${Spell[Muada's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Muada's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Trushar's Mending].Level} && ${Me.Book[${Spell[Trushar's Mending].RankName}]}) {
		/varset HealSpell1 ${Spell[Trushar's Mending].RankName}
	} else /if (${Me.Level}>=${Spell[Chloroblast].Level} && ${Me.Book[${Spell[Chloroblast].RankName}]}) {
		/varset HealSpell1 ${Spell[Chloroblast].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit Salve].Level} && ${Me.Book[${Spell[Spirit Salve].RankName}]}) {
		/varset HealSpell1 ${Spell[Spirit Salve].RankName}
	} else /if (${Me.Level}>=${Spell[Greater Healing].Level} && ${Me.Book[${Spell[Greater Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Greater Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Healing].Level} && ${Me.Book[${Spell[Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Light Healing].Level} && ${Me.Book[${Spell[Light Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Light Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Minor Healing].Level} && ${Me.Book[${Spell[Minor Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Minor Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Salve].Level} && ${Me.Book[${Spell[Salve].RankName}]}) {
		/varset HealSpell1 ${Spell[Salve].RankName}
	}
|-Pet Heal*
	/if (${Me.Level}>=${Spell[Salve of Artikla].Level} && ${Me.Book[${Spell[Salve of Artikla].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Artikla].RankName}
	} else /if (${Me.Level}>=${Spell[Salve of Clorith].Level} && ${Me.Book[${Spell[Salve of Clorith].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Clorith].RankName}
	} else /if (${Me.Level}>=${Spell[Salve of Blezon].Level} && ${Me.Book[${Spell[Salve of Blezon].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Blezon].RankName}
	} else /if (${Me.Level}>=${Spell[Salve of Yubai].Level} && ${Me.Book[${Spell[Salve of Yubai].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Yubai].RankName}
	} else /if (${Me.Level}>=${Spell[Salve of Sevna].Level} && ${Me.Book[${Spell[Salve of Sevna].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Sevna].RankName}
	} else /if (${Me.Level}>=${Spell[Salve of Reshan].Level} && ${Me.Book[${Spell[Salve of Reshan].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Reshan].RankName}
	} else /if (${Me.Level}>=${Spell[Salve of Feldan].Level} && ${Me.Book[${Spell[Salve of Feldan].RankName}]}) {
		/varset PetHealSpell ${Spell[Salve of Feldan].RankName}
	} else /if (${Me.Level}>=${Spell[Healing of Uluanes].Level} && ${Me.Book[${Spell[Healing of Uluanes].RankName}]}) {
		/varset PetHealSpell ${Spell[Healing of Uluanes].RankName}
	} else /if (${Me.Level}>=${Spell[Healing of Mikkily].Level} && ${Me.Book[${Spell[Healing of Mikkily].RankName}]}) {
		/varset PetHealSpell ${Spell[Healing of Mikkily].RankName}
	} else /if (${Me.Level}>=${Spell[Healing of Sorsha].Level} && ${Me.Book[${Spell[Healing of Sorsha].RankName}]}) {
		/varset PetHealSpell ${Spell[Healing of Sorsha].RankName}
	} else /if (${Me.Level}>=${Spell[Sha's Restoration].Level} && ${Me.Book[${Spell[Sha's Restoration].RankName}]}) {
		/varset PetHealSpell ${Spell[Sha's Restoration].RankName}
	} else /if (${Me.Level}>=${Spell[Aid of Khurenz].Level} && ${Me.Book[${Spell[Aid of Khurenz].RankName}]}) {
		/varset PetHealSpell ${Spell[Aid of Khurenz].RankName}
	} else /if (${Me.Level}>=${Spell[Vigor of Zehkes].Level} && ${Me.Book[${Spell[Vigor of Zehkes].RankName}]}) {
		/varset PetHealSpell ${Spell[Vigor of Zehkes].RankName}
	} else /if (${Me.Level}>=${Spell[Yekan's Recovery].Level} && ${Me.Book[${Spell[Yekan's Recovery].RankName}]}) {
		/varset PetHealSpell ${Spell[Yekan's Recovery].RankName}
	} else /if (${Me.Level}>=${Spell[Herikol's Soothing].Level} && ${Me.Book[${Spell[Herikol's Soothing].RankName}]}) {
		/varset PetHealSpell ${Spell[Herikol's Soothing].RankName}
	} else /if (${Me.Level}>=${Spell[Keshuval's Rejuvenation].Level} && ${Me.Book[${Spell[Keshuval's Rejuvenation].RankName}]}) {
		/varset PetHealSpell ${Spell[Keshuval's Rejuvenation].RankName}
	} else /if (${Me.Level}>=${Spell[Sharik's Replenishing].Level} && ${Me.Book[${Spell[Sharik's Replenishing].RankName}]}) {
		/varset PetHealSpell ${Spell[Sharik's Replenishing].RankName}
	}
|-ATK Buff*
	/if (${Me.Level}>=${Spell[Shared Merciless Ferocity].Level} && ${Me.Book[${Spell[Shared Merciless Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Shared Merciless Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Shared Brutal Ferocity].Level} && ${Me.Book[${Spell[Shared Brutal Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Shared Brutal Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Brutal Ferocity].Level} && ${Me.Book[${Spell[Brutal Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Brutal Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Callous Ferocity].Level} && ${Me.Book[${Spell[Callous Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Callous Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Savage Ferocity].Level} && ${Me.Book[${Spell[Savage Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Savage Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Vicious Ferocity].Level} && ${Me.Book[${Spell[Vicious Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Vicious Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Ruthless Ferocity].Level} && ${Me.Book[${Spell[Ruthless Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Ruthless Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Ferocity of Irionu].Level} && ${Me.Book[${Spell[Ferocity of Irionu].RankName}]}) {
		/varset AtkBuff ${Spell[Ferocity of Irionu].RankName}
	} else /if (${Me.Level}>=${Spell[Ferocity].Level} && ${Me.Book[${Spell[Ferocity].RankName}]}) {
		/varset AtkBuff ${Spell[Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Savagery].Level} && ${Me.Book[${Spell[Savagery].RankName}]}) {
		/varset AtkBuff ${Spell[Savagery].RankName}
	}
|--- Pet*
	/if (${Me.Level}>=${Spell[Spirit of Akalit].Level} && ${Me.Book[${Spell[Spirit of Akalit].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Akalit].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Avalit].Level} && ${Me.Book[${Spell[Spirit of Avalit].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Avalit].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Lachemit].Level} && ${Me.Book[${Spell[Spirit of Lachemit].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Lachemit].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Kolos].Level} && ${Me.Book[${Spell[Spirit of Kolos].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Kolos].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Averc].Level} && ${Me.Book[${Spell[Spirit of Averc].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Averc].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Hoshkar].Level} && ${Me.Book[${Spell[Spirit of Hoshkar].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Hoshkar].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Silverwing].Level} && ${Me.Book[${Spell[Spirit of Silverwing].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Silverwing].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Uluanes].Level} && ${Me.Book[${Spell[Spirit of Uluanes].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Uluanes].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Rashara].Level} && ${Me.Book[${Spell[Spirit of Rashara].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Rashara].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Alladnu].Level} && ${Me.Book[${Spell[Spirit of Alladnu].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Alladnu].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Sorsha].Level} && ${Me.Book[${Spell[Spirit of Sorsha].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Sorsha].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Arag].Level} && ${Me.Book[${Spell[Spirit of Arag].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Arag].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Khati Sha].Level} && ${Me.Book[${Spell[Spirit of Khati Sha].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Khati Sha].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Khurenz].Level} && ${Me.Book[${Spell[Spirit of Khurenz].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Khurenz].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Zehkes].Level} && ${Me.Book[${Spell[Spirit of Zehkes].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Zehkes].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Omakin].Level} && ${Me.Book[${Spell[Spirit of Omakin].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Omakin].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Kashek].Level} && ${Me.Book[${Spell[Spirit of Kashek].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Kashek].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Yekan].Level} && ${Me.Book[${Spell[Spirit of Yekan].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Yekan].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Herikol].Level} && ${Me.Book[${Spell[Spirit of Herikol].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Herikol].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Keshuval].Level} && ${Me.Book[${Spell[Spirit of Keshuval].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Keshuval].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Khaliz].Level} && ${Me.Book[${Spell[Spirit of Khaliz].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Khaliz].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Sharik].Level} && ${Me.Book[${Spell[Spirit of Sharik].RankName}]}) {
		/varset PetSpell ${Spell[Spirit of Sharik].RankName}
	}
|-Buffs
 |-Focus*
	/if (${Me.Level}>=${Spell[Focus of Artikla].Level} && ${Me.Book[${Spell[Focus of Artikla].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Artikla].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Okasi].Level} && ${Me.Book[${Spell[Focus of Okasi].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Okasi].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Sanera].Level} && ${Me.Book[${Spell[Focus of Sanera].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Sanera].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Klar].Level} && ${Me.Book[${Spell[Focus of Klar].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Klar].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Emiq].Level} && ${Me.Book[${Spell[Focus of Emiq].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Emiq].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Yemall].Level} && ${Me.Book[${Spell[Focus of Yemall].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Yemall].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Zott].Level} && ${Me.Book[${Spell[Focus of Zott].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Zott].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Amilan].Level} && ${Me.Book[${Spell[Focus of Amilan].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Amilan].RankName}
	} else /if (${Me.Level}>=${Spell[Focus of Alladnu].Level} && ${Me.Book[${Spell[Focus of Alladnu].RankName}]}) {
		/varset FocusSpell ${Spell[Focus of Alladnu].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of Kragg].Level} && ${Me.Book[${Spell[Talisman of Kragg].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of Kragg].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of Altuna].Level} && ${Me.Book[${Spell[Talisman of Altuna].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of Altuna].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of Tnarg].Level} && ${Me.Book[${Spell[Talisman of Tnarg].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of Tnarg].RankName}
	} else /if (${Me.Level}>=${Spell[Inner Fire].Level} && ${Me.Book[${Spell[Inner Fire].RankName}]}) {
		/varset FocusSpell ${Spell[Inner Fire].RankName}
	}
 |- Unity Mana/Hp/End Regen + Atk/HP Buff*
	/if (${Me.Level}>=${Spell[Feralist's Unity].Level} && ${Me.Book[${Spell[Feralist's Unity].RankName}]}) {
		/varset UnityBuff ${Spell[Feralist's Unity].RankName}
	} else /if (${Me.Level}>=${Spell[Stormblood's Unity].Level} && ${Me.Book[${Spell[Stormblood's Unity].RankName}]}) {
		/varset UnityBuff ${Spell[Stormblood's Unity].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Unity].Level} && ${Me.Book[${Spell[Spiritual Unity].RankName}]}) {
		/varset UnityBuff ${Spell[Spiritual Unity].RankName}
	}
 |-Mana/Hp/End Regen Buff*
	/if (${Me.Level}>=${Spell[Spiritual Empowerment].Level} && ${Me.Book[${Spell[Spiritual Empowerment].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Empowerment].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Elaboration].Level} && ${Me.Book[${Spell[Spiritual Elaboration].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Elaboration].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Evolution].Level} && ${Me.Book[${Spell[Spiritual Evolution].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Evolution].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Enrichment].Level} && ${Me.Book[${Spell[Spiritual Enrichment].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Enrichment].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Enhancement].Level} && ${Me.Book[${Spell[Spiritual Enhancement].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Enhancement].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Edification].Level} && ${Me.Book[${Spell[Spiritual Edification].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Edification].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Epiphany].Level} && ${Me.Book[${Spell[Spiritual Epiphany].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Epiphany].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Enlightenment].Level} && ${Me.Book[${Spell[Spiritual Enlightenment].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Enlightenment].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Ascendance].Level} && ${Me.Book[${Spell[Spiritual Ascendance].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Ascendance].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Dominion].Level} && ${Me.Book[${Spell[Spiritual Dominion].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Dominion].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Purity].Level} && ${Me.Book[${Spell[Spiritual Purity].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Purity].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Radiance].Level} && ${Me.Book[${Spell[Spiritual Radiance].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Radiance].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Light].Level} && ${Me.Book[${Spell[Spiritual Light].RankName}]}) {
		/varset ManaRegenBuff ${Spell[Spiritual Light].RankName}
	}
 |-Atk+HP Buff*
	/if (${Me.Level}>=${Spell[Spiritual Vibrancy].Level} && ${Me.Book[${Spell[Spiritual Vibrancy].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vibrancy].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Vivification].Level} && ${Me.Book[${Spell[Spiritual Vivification].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vivification].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Vindication].Level} && ${Me.Book[${Spell[Spiritual Vindication].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vindication].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Valiance].Level} && ${Me.Book[${Spell[Spiritual Valiance].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Valiance].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Valor].Level} && ${Me.Book[${Spell[Spiritual Valor].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Valor].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Verve].Level} && ${Me.Book[${Spell[Spiritual Verve].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Verve].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Vivacity].Level} && ${Me.Book[${Spell[Spiritual Vivacity].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vivacity].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Vim].Level} && ${Me.Book[${Spell[Spiritual Vim].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vim].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Vitality].Level} && ${Me.Book[${Spell[Spiritual Vitality].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vitality].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Vigor].Level} && ${Me.Book[${Spell[Spiritual Vigor].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Vigor].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Strength].Level} && ${Me.Book[${Spell[Spiritual Strength].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Strength].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Brawn].Level} && ${Me.Book[${Spell[Spiritual Brawn].RankName}]}) {
		/varset AtkHPBuff ${Spell[Spiritual Brawn].RankName}
	}
 |-Pet Dmg Absorb + HoT buff*
	/if (${Me.Level}>=${Spell[Natural Cooperation].Level} && ${Me.Book[${Spell[Natural Cooperation].RankName}]}) {
		/varset KillShotBuff ${Spell[Natural Cooperation].RankName}
	} else /if (${Me.Level}>=${Spell[Natural Affiliation].Level} && ${Me.Book[${Spell[Natural Affiliation].RankName}]}) {
		/varset KillShotBuff ${Spell[Natural Affiliation].RankName}
	} else /if (${Me.Level}>=${Spell[Natural Cooperation].Level} && ${Me.Book[${Spell[Natural Cooperation].RankName}]}) {
		/varset KillShotBuff ${Spell[Natural Cooperation].RankName}
	} else /if (${Me.Level}>=${Spell[Natural Collaboration].Level} && ${Me.Book[${Spell[Natural Collaboration].RankName}]}) {
		/varset KillShotBuff ${Spell[Natural Collaboration].RankName}
	}
 |-Runspeed* 
	/if (${Me.Level}>=${Spell[Spirit of Tala'Tak].Level} && ${Me.Book[${Spell[Spirit of Tala'Tak].RankName}]}) {
		/varset RunSpeedBuff ${Spell[Spirit of Tala'Tak].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Wolf].Level} && ${Me.Book[${Spell[Spirit of Wolf].RankName}]}) {
		/varset RunSpeedBuff ${Spell[Spirit of Wolf].RankName}
	}
|-Pet Buffs
 |-Pet Group End Regen Proc*
	/if (${Me.Level}>=${Spell[Exhausting Bite].Level} && ${Me.Book[${Spell[Exhausting Bite].RankName}]}) {
		/varset PetEnduranceProc ${Spell[Exhausting Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Fatiguing Bite].Level} && ${Me.Book[${Spell[Fatiguing Bite].RankName}]}) {
		/varset PetEnduranceProc ${Spell[Fatiguing Bite].RankName}
	}
 |-Pet Growl Buff*
	/if (${Me.Level}>=${Spell[Growl of the Sabretooth].Level} && ${Me.Book[${Spell[Growl of the Sabretooth].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Sabretooth].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Leopard].Level} && ${Me.Book[${Spell[Growl of the Leopard].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Leopard].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Snow Leopard].Level} && ${Me.Book[${Spell[Growl of the Snow Leopard].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Snow Leopard].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Lion].Level} && ${Me.Book[${Spell[Growl of the Lion].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Lion].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Tiger].Level} && ${Me.Book[${Spell[Growl of the Tiger].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Tiger].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Jaguar].Level} && ${Me.Book[${Spell[Growl of the Jaguar].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Jaguar].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Puma].Level} && ${Me.Book[${Spell[Growl of the Puma].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Puma].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Panther].Level} && ${Me.Book[${Spell[Growl of the Panther].RankName}]}) {
		/varset PetGrowl ${Spell[Growl of the Panther].RankName}
	}
 |-Pet Mitigate Spell Damage*
	/if (${Me.Level}>=${Spell[Spellbreaker's Keep].Level} && ${Me.Book[${Spell[Spellbreaker's Keep].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Keep].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Palisade].Level} && ${Me.Book[${Spell[Spellbreaker's Palisade].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Palisade].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Ward].Level} && ${Me.Book[${Spell[Spellbreaker's Ward].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Ward].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Armor].Level} && ${Me.Book[${Spell[Spellbreaker's Armor].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Armor].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Rampart].Level} && ${Me.Book[${Spell[Spellbreaker's Rampart].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Rampart].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Aegis].Level} && ${Me.Book[${Spell[Spellbreaker's Aegis].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Aegis].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Bulwark].Level} && ${Me.Book[${Spell[Spellbreaker's Bulwark].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Bulwark].RankName}
	} else /if (${Me.Level}>=${Spell[Spellbreaker's Guard].Level} && ${Me.Book[${Spell[Spellbreaker's Guard].RankName}]}) {
		/varset PetSpellGuard ${Spell[Spellbreaker's Guard].RankName}
	}
 |-Pet Slow Proc*
	/if (${Me.Level}>=${Spell[Deadlock Jaws].Level} && ${Me.Book[${Spell[Deadlock Jaws].RankName}]}) {
		/varset PetSlowProc ${Spell[Deadlock Jaws].RankName}
	} else /if (${Me.Level}>=${Spell[Fellgrip Jaws].Level} && ${Me.Book[${Spell[Fellgrip Jaws].RankName}]}) {
		/varset PetSlowProc ${Spell[Fellgrip Jaws].RankName}
	} else /if (${Me.Level}>=${Spell[Lockfang Jaws].Level} && ${Me.Book[${Spell[Lockfang Jaws].RankName}]}) {
		/varset PetSlowProc ${Spell[Lockfang Jaws].RankName}
	} else /if (${Me.Level}>=${Spell[Steeltrap Jaws].Level} && ${Me.Book[${Spell[Steeltrap Jaws].RankName}]}) {
		/varset PetSlowProc ${Spell[Steeltrap Jaws].RankName}
	}
 |-Pet DPS buff*
	/if (${Me.Level}>=${Spell[Virzak's Aggression].Level} && ${Me.Book[${Spell[Virzak's Aggression].RankName}]}) {
		/varset PetOffenseBuff ${Spell[Virzak's Aggression].RankName}
	} else /if (${Me.Level}>=${Spell[Sekmoset's Aggression].Level} && ${Me.Book[${Spell[Sekmoset's Aggression].RankName}]}) {
		/varset PetOffenseBuff ${Spell[Sekmoset's Aggression].RankName}
	} else /if (${Me.Level}>=${Spell[Plakt's Aggression].Level} && ${Me.Book[${Spell[Plakt's Aggression].RankName}]}) {
		/varset PetOffenseBuff ${Spell[Plakt's Aggression].RankName}
	} else /if (${Me.Level}>=${Spell[Mea's Aggression].Level} && ${Me.Book[${Spell[Mea's Aggression].RankName}]}) {
		/varset PetOffenseBuff ${Spell[Mea's Aggression].RankName}
	} else /if (${Me.Level}>=${Spell[Neivr's Aggression].Level} && ${Me.Book[${Spell[Neivr's Aggression].RankName}]}) {
		/varset PetOffenseBuff ${Spell[Neivr's Aggression].RankName}
	}
 |-Pet Tanking buff*
	/if (${Me.Level}>=${Spell[Virzak's Protection].Level} && ${Me.Book[${Spell[Virzak's Protection].RankName}]}) {
		/varset PetDefenseBuff ${Spell[Virzak's Protection].RankName}
	} else /if (${Me.Level}>=${Spell[Sekmoset's Protection].Level} && ${Me.Book[${Spell[Sekmoset's Protection].RankName}]}) {
		/varset PetDefenseBuff ${Spell[Sekmoset's Protection].RankName}
	} else /if (${Me.Level}>=${Spell[Plakt's Protection].Level} && ${Me.Book[${Spell[Plakt's Protection].RankName}]}) {
		/varset PetDefenseBuff ${Spell[Plakt's Protection].RankName}
	} else /if (${Me.Level}>=${Spell[Mea's Protection].Level} && ${Me.Book[${Spell[Mea's Protection].RankName}]}) {
		/varset PetDefenseBuff ${Spell[Mea's Protection].RankName}
	} else /if (${Me.Level}>=${Spell[Neivr's Protection].Level} && ${Me.Book[${Spell[Neivr's Protection].RankName}]}) {
		/varset PetDefenseBuff ${Spell[Neivr's Protection].RankName}
	}
 |-Pet Haste*
	/if (${Me.Level}>=${Spell[Tremendous Velocity].Level} && ${Me.Book[${Spell[Tremendous Velocity].RankName}]}) {
		/varset PetHaste ${Spell[Tremendous Velocity].RankName}
	} else /if (${Me.Level}>=${Spell[Extraordinary Velocity].Level} && ${Me.Book[${Spell[Extraordinary Velocity].RankName}]}) {
		/varset PetHaste ${Spell[Extraordinary Velocity].RankName}
	} else /if (${Me.Level}>=${Spell[Exceptional Velocity].Level} && ${Me.Book[${Spell[Exceptional Velocity].RankName}]}) {
		/varset PetHaste ${Spell[Exceptional Velocity].RankName}
	} else /if (${Me.Level}>=${Spell[Incomparable Velocity].Level} && ${Me.Book[${Spell[Incomparable Velocity].RankName}]}) {
		/varset PetHaste ${Spell[Incomparable Velocity].RankName}
	} else /if (${Me.Level}>=${Spell[Unrivaled Rapidity].Level} && ${Me.Book[${Spell[Unrivaled Rapidity].RankName}]}) {
		/varset PetHaste ${Spell[Unrivaled Rapidity].RankName}
	} else /if (${Me.Level}>=${Spell[Peerless Penchant].Level} && ${Me.Book[${Spell[Peerless Penchant].RankName}]}) {
		/varset PetHaste ${Spell[Peerless Penchant].RankName}
	} else /if (${Me.Level}>=${Spell[Unparalleled Voracity].Level} && ${Me.Book[${Spell[Unparalleled Voracity].RankName}]}) {
		/varset PetHaste ${Spell[Unparalleled Voracity].RankName}
	} else /if (${Me.Level}>=${Spell[Growl of the Beast].Level} && ${Me.Book[${Spell[Growl of the Beast].RankName}]}) {
		/varset PetHaste ${Spell[Growl of the Beast].RankName}
	} else /if (${Me.Level}>=${Spell[Arag's Celerity].Level} && ${Me.Book[${Spell[Arag's Celerity].RankName}]}) {
		/varset PetHaste ${Spell[Arag's Celerity].RankName}
	} else /if (${Me.Level}>=${Spell[Sha's Ferocity].Level} && ${Me.Book[${Spell[Sha's Ferocity].RankName}]}) {
		/varset PetHaste ${Spell[Sha's Ferocity].RankName}
	} else /if (${Me.Level}>=${Spell[Omakin's Alacrity].Level} && ${Me.Book[${Spell[Omakin's Alacrity].RankName}]}) {
		/varset PetHaste ${Spell[Omakin's Alacrity].RankName}
	} else /if (${Me.Level}>=${Spell[Bond of the Wild].Level} && ${Me.Book[${Spell[Bond of the Wild].RankName}]}) {
		/varset PetHaste ${Spell[Bond of the Wild].RankName}
	} else /if (${Me.Level}>=${Spell[Yekan's Quickening].Level} && ${Me.Book[${Spell[Yekan's Quickening].RankName}]}) {
		/varset PetHaste ${Spell[Yekan's Quickening].RankName}
	}
 |-Pet Heal proc buff*
	/if (${Me.Level}>=${Spell[Convivial Warder].Level} && ${Me.Book[${Spell[Convivial Warder].RankName}]}) {
		/varset PetHealProc ${Spell[Convivial Warder].RankName}
	} else /if (${Me.Level}>=${Spell[Mending Warder].Level} && ${Me.Book[${Spell[Mending Warder].RankName}]}) {
		/varset PetHealProc ${Spell[Mending Warder].RankName}
	} else /if (${Me.Level}>=${Spell[Invigorating Warder].Level} && ${Me.Book[${Spell[Invigorating Warder].RankName}]}) {
		/varset PetHealProc ${Spell[Invigorating Warder].RankName}
	} else /if (${Me.Level}>=${Spell[Empowering Warder].Level} && ${Me.Book[${Spell[Empowering Warder].RankName}]}) {
		/varset PetHealProc ${Spell[Empowering Warder].RankName}
	} else /if (${Me.Level}>=${Spell[Bolstering Warder].Level} && ${Me.Book[${Spell[Bolstering Warder].RankName}]}) {
		/varset PetHealProc ${Spell[Bolstering Warder].RankName}
	} else /if (${Me.Level}>=${Spell[Friendly Pet].Level} && ${Me.Book[${Spell[Friendly Pet].RankName}]}) {
		/varset PetHealProc ${Spell[Friendly Pet].RankName}
	}
 |-Pet Damage Proc Buff*
	/if (${Me.Level}>=${Spell[Spirit of Beramos].Level} && ${Me.Book[${Spell[Spirit of Beramos].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Beramos].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Visoracius].Level} && ${Me.Book[${Spell[Spirit of Visoracius].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Visoracius].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Nak].Level} && ${Me.Book[${Spell[Spirit of Nak].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Nak].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Bale].Level} && ${Me.Book[${Spell[Spirit of Bale].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Bale].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Kron].Level} && ${Me.Book[${Spell[Spirit of Kron].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Kron].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Vaxztn].Level} && ${Me.Book[${Spell[Spirit of Vaxztn].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Vaxztn].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Jeswin].Level} && ${Me.Book[${Spell[Spirit of Jeswin].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Jeswin].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Lairn].Level} && ${Me.Book[${Spell[Spirit of Lairn].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Lairn].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Oroshar].Level} && ${Me.Book[${Spell[Spirit of Oroshar].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Oroshar].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Irionu].Level} && ${Me.Book[${Spell[Spirit of Irionu].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Irionu].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Rellic].Level} && ${Me.Book[${Spell[Spirit of Rellic].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Rellic].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Flame].Level} && ${Me.Book[${Spell[Spirit of Flame].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Flame].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Snow].Level} && ${Me.Book[${Spell[Spirit of Snow].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Snow].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of the Storm].Level} && ${Me.Book[${Spell[Spirit of the Storm].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of the Storm].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Wind].Level} && ${Me.Book[${Spell[Spirit of Wind].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Wind].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Vermin].Level} && ${Me.Book[${Spell[Spirit of Vermin].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Vermin].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of the Scorpion].Level} && ${Me.Book[${Spell[Spirit of the Scorpion].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of the Scorpion].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Inferno].Level} && ${Me.Book[${Spell[Spirit of Inferno].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Inferno].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of the Blizzard].Level} && ${Me.Book[${Spell[Spirit of the Blizzard].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of the Blizzard].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Lightning].Level} && ${Me.Book[${Spell[Spirit of Lightning].RankName}]}) {
		/varset PetDamageProc ${Spell[Spirit of Lightning].RankName}
	}
/return
|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub SetupDiscs
|------Discs*
	/if (${Me.Level}>=${Spell[Mangle].Level} && ${Me.CombatAbility[${Spell[Mangle].RankName}]}) {
		/varset Maul ${Spell[Mangle].RankName}
	} else /if (${Me.Level}>=${Spell[Maul].Level} && ${Me.CombatAbility[${Spell[Maul].RankName}]}) {
		/varset Maul ${Spell[Maul].RankName}
	} else /if (${Me.Level}>=${Spell[Pummel].Level} && ${Me.CombatAbility[${Spell[Pummel].RankName}]}) {
		/varset Maul ${Spell[Pummel].RankName}
	} else /if (${Me.Level}>=${Spell[Barrage].Level} && ${Me.CombatAbility[${Spell[Barrage].RankName}]}) {
		/varset Maul ${Spell[Barrage].RankName}
	} else /if (${Me.Level}>=${Spell[Rush].Level} && ${Me.CombatAbility[${Spell[Rush].RankName}]}) {
		/varset Maul ${Spell[Rush].RankName}
	} else /if (${Me.Level}>=${Spell[Foray].Level} && ${Me.CombatAbility[${Spell[Foray].RankName}]}) {
		/varset Maul ${Spell[Foray].RankName}
	} else /if (${Me.Level}>=${Spell[Harrow].Level} && ${Me.CombatAbility[${Spell[Harrow].RankName}]}) {
		/varset Maul ${Spell[Harrow].RankName}
	} else /if (${Me.Level}>=${Spell[Rake].Level} && ${Me.CombatAbility[${Spell[Rake].RankName}]}) {
		/varset Maul ${Spell[Rake].RankName}
	}
|-AE Claws*
	/if (${Me.Level}>=${Spell[Storm of Claws].Level} && ${Me.CombatAbility[${Spell[Storm of Claws].RankName}]}) {
		/varset AEClaws ${Spell[Storm of Claws].RankName}
	} else /if (${Me.Level}>=${Spell[Tempest of Claws].Level} && ${Me.CombatAbility[${Spell[Tempest of Claws].RankName}]}) {
		/varset AEClaws ${Spell[Tempest of Claws].RankName}
	} else /if (${Me.Level}>=${Spell[Clamor of Claws].Level} && ${Me.CombatAbility[${Spell[Clamor of Claws].RankName}]}) {
		/varset AEClaws ${Spell[Clamor of Claws].RankName}
	} else /if (${Me.Level}>=${Spell[Tumult of Claws].Level} && ${Me.CombatAbility[${Spell[Tumult of Claws].RankName}]}) {
		/varset AEClaws ${Spell[Tumult of Claws].RankName}
	} else /if (${Me.Level}>=${Spell[Flurry of Claws].Level} && ${Me.CombatAbility[${Spell[Flurry of Claws].RankName}]}) {
		/varset AEClaws ${Spell[Flurry of Claws].RankName}
	}
|-Single target claws*
	/if (${Me.Level}>=${Spell[Focused Clamor of Claws].Level} && ${Me.CombatAbility[${Spell[Focused Clamor of Claws].RankName}]}) {
		/varset SingleClaws ${Spell[Focused Clamor of Claws].RankName}
	}
|-Beastial Buff*
	/if (${Me.Level}>=${Spell[Bestial Savagery].Level} && ${Me.CombatAbility[${Spell[Bestial Savagery].RankName}]}) {
		/varset BeastialBuffDisc ${Spell[Bestial Savagery].RankName}
	} else /if (${Me.Level}>=${Spell[Bestial Evulsing].Level} && ${Me.CombatAbility[${Spell[Bestial Evulsing].RankName}]}) {
		/varset BeastialBuffDisc ${Spell[Bestial Evulsing].RankName}
	} else /if (${Me.Level}>=${Spell[Bestial Rending].Level} && ${Me.CombatAbility[${Spell[Bestial Rending].RankName}]}) {
		/varset BeastialBuffDisc ${Spell[Bestial Rending].RankName}
	} else /if (${Me.Level}>=${Spell[Bestial Vivisection].Level} && ${Me.CombatAbility[${Spell[Bestial Vivisection].RankName}]}) {
		/varset BeastialBuffDisc ${Spell[Bestial Vivisection].RankName}
	}
|-HHE Burn Disc*
	/if (${Me.Level}>=${Spell[Ruaabri's Fury].Level} && ${Me.CombatAbility[${Spell[Ruaabri's Fury].RankName}]}) {
		/varset HHEFuryDisc ${Spell[Ruaabri's Fury].RankName}
	} else /if (${Me.Level}>=${Spell[Kolos' Fury].Level} && ${Me.CombatAbility[${Spell[Kolos' Fury].RankName}]}) {
		/varset HHEFuryDisc ${Spell[Kolos' Fury].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Fury].Level} && ${Me.CombatAbility[${Spell[Nature's Fury].RankName}]}) {
		/varset HHEFuryDisc ${Spell[Nature's Fury].RankName}
	}
|-All Skills Damage Modifier*
	/if (${Me.Level}>=${Spell[Savage Rancor].Level} && ${Me.CombatAbility[${Spell[Savage Rancor].RankName}]}) {
		/varset DmgModDisc ${Spell[Savage Rancor].RankName}
	} else /if (${Me.Level}>=${Spell[Savage Rage].Level} && ${Me.CombatAbility[${Spell[Savage Rage].RankName}]}) {
		/varset DmgModDisc ${Spell[Savage Rage].RankName}
	} else /if (${Me.Level}>=${Spell[Savage Fury].Level} && ${Me.CombatAbility[${Spell[Savage Fury].RankName}]}) {
		/varset DmgModDisc ${Spell[Savage Fury].RankName}
	} else /if (${Me.Level}>=${Spell[Empathic Fury].Level} && ${Me.CombatAbility[${Spell[Empathic Fury].RankName}]}) {
		/varset DmgModDisc ${Spell[Empathic Fury].RankName}
	} else /if (${Me.Level}>=${Spell[Bestial Fury Discipline].Level} && ${Me.CombatAbility[${Spell[Bestial Fury Discipline].RankName}]}) {
		/varset DmgModDisc ${Spell[Bestial Fury Discipline].RankName}
	}
|-Group End Regen*
	/if (${Me.Level}>=${Spell[Reflexive Sundering].Level} && ${Me.CombatAbility[${Spell[Reflexive Sundering].RankName}]}) {
		/varset EndRegenProcDisc ${Spell[Reflexive Sundering].RankName}
	} else /if (${Me.Level}>=${Spell[Reflexive Rending].Level} && ${Me.CombatAbility[${Spell[Reflexive Rending].RankName}]}) {
		/varset EndRegenProcDisc ${Spell[Reflexive Rending].RankName}
	}
|-End Regen*
	/if (${Me.Level}>=${Spell[Breather].Level} && ${Me.CombatAbility[${Spell[Breather].RankName}]})  {
		/varset EndRegenDisc ${Spell[Breather].RankName}
	} else /if (${Me.Level}>=${Spell[Rest].Level} && ${Me.CombatAbility[${Spell[Rest].RankName}]})  {
		/varset EndRegenDisc ${Spell[Rest].RankName}
	} else /if (${Me.Level}>=${Spell[Reprieve].Level} && ${Me.CombatAbility[${Spell[Reprieve].RankName}]})  {
		/varset EndRegenDisc ${Spell[Reprieve].RankName}
	} else /if (${Me.Level}>=${Spell[Respite].Level} && ${Me.CombatAbility[${Spell[Respite].RankName}]})  {
		/varset EndRegenDisc ${Spell[Respite].RankName}
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
		/if (${IName.Equal[UsePet]}) {
			/if (!${UsePet}) {
				/echo \aw Setting UsePet to \ag ON
				/varset UsePet 1
			} else {
				/echo \aw Resetting UsePet to \ar OFF
				/varset UsePet 0
			}
		} else /if (${IName.Equal[AllowMezBreak]}) {
			/if (!${AllowMezBreak}) {
				/echo \aw Setting AllowMezBreak to \ag ON
				/varset AllowMezBreak 1
			} else {
				/echo \aw Resetting AllowMezBreak to \ar OFF
				/varset AllowMezBreak 0
			}
		} else /if (${IName.Equal[UseAoE]}) {
			/if (!${UseAoE}) {
				/echo \aw Setting UseAoE to \ag ON
				/varset UseAoE 1
			} else {
				/echo \aw Resetting UseAoE to \ar OFF
				/varset UseAoE 0
			}
		} else /if (${IName.Equal[DoDot]}) {
			/if (!${DoDot}) {
				/echo \aw Setting DoDot to \ag ON
				/varset DoDot 1
				/call LoadSpellBar
			} else {
				/echo \aw Resetting DoDot to \ar OFF
				/varset DoDot 0
				/call LoadSpellBar
			}
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
		} else /if (${IName.Equal[DoSlow]}) {
			/if (!${DoSlow}) {
				/echo \aw Setting DoSlow to \ag ON
				/varset DoSlow 1
			} else {
				/echo \aw Resetting DoSlow to \ar OFF
				/varset DoSlow 0
			}
		} else /if (${IName.Equal[BringYourOwnSpells]}) {
			/if (!${BringYourOwnSpells}) {
				/echo \aw Setting BringYourOwnSpells to \ag ON
				/varset BringYourOwnSpells 1
			} else {
				/echo \aw Resetting BringYourOwnSpells to \ar OFF
				/varset BringYourOwnSpells 0
				/call LoadSpellBar
			}
		} else /if (${IName.Equal[DoFerocity]}) {
			/if (!${DoFerocity}) {
				/echo \aw Setting DoFerocity to \ag ON
				/varset DoFerocity 1
			} else {
				/echo \aw Resetting DoFerocity to \ar OFF
				/varset DoFerocity 0
			}
		} else /if (${IName.Equal[DoPetSlow]}) {
			/if (!${DoPetSlow}) {
				/echo \aw Setting DoPetSlow to \ag ON
				/varset DoPetSlow 1
			} else {
				/echo \aw Resetting DoPetSlow to \ar OFF
				/varset DoPetSlow 0
			}
		}
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
/echo \ag/tglpoison\aw - Turn on/off the use of poison buffs
/echo \ag/tglmezbreak\aw - Allow attacking mez'd mobs if below assistat % - Ignores waiting for MA
/return