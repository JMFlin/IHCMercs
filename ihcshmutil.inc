|- ihcshmutil.inc
|- Version 0.1
|- Updated: 5/24/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub ShmSetup
/noparse /alias /autorez /multiline ; /docommand ${If[${AutoRez}==1,/varset AutoRez 0,/varset AutoRez 1]} ; /varset changetoini 1 ; /echo Setting AutoRez to ${If[${AutoRez}==0,OFF,ON]}
|-Spells
	/declare ShamanAura				string outer NULL
	/declare FocusSpell				string outer NULL
	/declare RegenSpell				string outer NULL
	/declare CanniSpell				string outer NULL
	/declare RunSpeedBuff			string outer NULL
	/declare DichoSpell				string outer NULL
	/declare PetSpell				string outer NULL
	/declare PetBuffSpell			string outer NULL
	/declare RecklessHeal1			string outer NULL
	/declare RecklessHeal2			string outer NULL
	/declare RecklessHeal3			string outer NULL
	/declare AESpiritualHeal		string outer NULL
	/declare RecourseHeal			string outer NULL
	/declare InterventionHeal		string outer NULL
	/declare GroupRenewalHoT		string outer NULL
	/declare CurseDoT1				string outer NULL
	/declare CurseDoT2				string outer NULL
	/declare FastPoisonDoT			string outer NULL
	/declare FastDiseaseDoT			string outer NULL
	/declare TwinHealNuke			string outer NULL
	/declare PoisonNuke				string outer NULL
	/declare FastPoisonNuke			string outer NULL
	/declare FrostNuke				string outer NULL
	/declare ChaoticPoisonDoT		string outer NULL
	/declare AllianceBuff			string outer NULL
	/declare GroupHealProcBuff		string outer NULL
	/declare CureSpell				string outer NULL
	/declare PureSpiritSpell		string outer NULL
	/declare SlowSpell				string outer NULL
	/declare AESlowSpell			string outer NULL
	/declare MaloSpell				string outer NULL
	/declare AEMaloSpell			string outer NULL
	/declare GrowthBuff				string outer NULL
	/declare MeleeProcBuff			string outer NULL
	/declare PackSelfBuff			string outer NULL
	/declare SlowProcBuff			string outer NULL
	/declare SelfHealProcBuff		string outer NULL
	/declare Malo 					string outer NULL
|- Misc Variables
	/declare Spell1					string outer NULL
	/declare Spell2					string outer NULL
	/declare Spell3					string outer NULL
	/declare Spell4					string outer NULL
	/declare Spell5					string outer NULL
	/declare Spell6					string outer NULL
	/declare Spell7					string outer NULL
	/declare Spell8					string outer NULL
	/declare Spell9					string outer NULL
	/declare Spell10				string outer NULL
	/declare Spell11				string outer NULL
	/declare Spell12				string outer NULL
	/declare Spell13				string outer NULL
	/declare TravelSpell 			string outer NULL

	/declare WasStickOn				int	outer 0
	/declare PatchHealPoint			int outer 44
	/declare PatchHeal2Point		int outer 34
	/declare ClickHealPoint			int outer 35
	/declare HealPoint				int outer 99
	/declare HoTTimer				timer outer 0
	/declare CureTimer				timer outer 0
	/declare CureCheckTimer			timer outer 10s
	/declare SetHoTDurationTimer	int outer 0
	/declare DurationMod			float outer 1
	/declare oldtank				string outer NULL
	/declare oldtankid				string outer NULL
	/declare newtank				int outer 0
	/declare CureMemberCount    	int outer 0
	/declare CureMemberID     		int outer 0
|-Special
	/declare EpicSpiritStaff		string outer NULL
	/declare UseEpic 				int outer 0
|-Config Options
	/call LoadCommonConfig
	/call LoadIni Buffs UseAllianceBuff			int 0
	/call LoadIni Buffs UseAura					int 1
	/call LoadIni Buffs UseFocus				int 1
	/call LoadIni Buffs UseGrowthBuff			int 1
	/call LoadIni Buffs UseHaste				int 1
	/call LoadIni Buffs UseRunSpeed				int 1
	/call LoadIni Combat AllowMezBreak		 	int 0
	/call LoadIni Combat DoDot					int 0
	/call LoadIni Combat Manatonuke				int 5
	/call LoadIni Combat StickHow				string behind
	/call LoadIni Combat StopNukeAggro			int 80
	/call LoadIni Combat UseAoE					int 0
	/call LoadIni Combat UseMelee		 		int 1
	/call LoadIni Combat UseRoar		 		int 1
	/call LoadIni Combat UseProcBuff		 	int 0
	/call LoadIni Debuff AutoDebuffAt			int 99
	/call LoadIni Debuff DoMalo					int 1
	/call LoadIni Debuff DoAEMalo				int 1
	/call LoadIni Debuff DoRoot					int 1
	/call LoadIni Debuff DoAERoot				int 1
	/call LoadIni Debuff DoSlow					int 1
	/call LoadIni Debuff DoAESlow				int 1
	/call LoadIni General DoAACanni				int 1
	/call LoadIni General AACanniManaPct		int 70
	/call LoadIni General AACanniMinHP			int 70
	/call LoadIni General DoSpellCanni			int 1
	/call LoadIni General CanniManaPct			int 90
	/call LoadIni General CanniMinHP			int 60
	/call LoadIni General Travel				int 1
	/call LoadIni Healing DoCures				int 0
	/call LoadIni Healing DoHeals				int 1
	/call LoadIni Healing DoHoTs				int 1
	/call LoadIni Healing CureOther				int 1
	/call LoadIni Healing DynamicHealing		int 1
	/call LoadIni Healing BigHealPoint			int 70
	/call LoadIni Healing GroupHealPoint		int 80
	/call LoadIni Healing GroupHealCount		int 2
	/call LoadIni Healing HoTHealPoint			int 95
	/call LoadIni Healing PetHealPoint			int 30 
	/call LoadIni Healing RaidHealPoint			int 65
	/call LoadIni Healing TankHealPoint			int 90
	/call LoadIni Healing TBMHealPoint			int 65
	/call LoadIni Item ChestItemName			string "${Me.Inventory[17].Name}"
	/call LoadIni Item ChestCombatCast			int 0
	/call LoadIni Options BringYourOwnSpells	int 0
	/call LoadIni Options AutoRez 				int 1
	/call LoadIni Pet UsePet		 			int 1
	/call LoadIni Pet UseSwarmpet		 		int 0
	/varset ChestItemName		"${Me.Inventory[17].Name}"
	/if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==1) /varset DurationMod 1.15
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==2) /varset DurationMod 1.3
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==3) /varset DurationMod 1.5
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==4) /varset DurationMod 1.7
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==5) /varset DurationMod 1.9
|- Check for epic
	/if (${FindItem[=Crafted Talisman of Fates].ID}) {
		/varset EpicSpiritStaff	Crafted Talisman of Fates	
		/varset UseEpic 1
	} else /if (${FindItem[=Blessed Spiritstaff of the Heyokah].ID}) {
		/varset EpicSpiritStaff	Blessed Spiritstaff of the Heyokah
		/varset UseEpic 1
	}
	/declare DoCC 				int outer 0
|-Declare spell variables
	/declare spellmisc 			int outer 11
	/declare GroupBuffRecast 	int outer 0
	/declare miscspellremem		string outer NULL
	/declare tempid				string outer NULL
	/declare CastResult         string outer
	/declare spellrememtimer	timer outer 0
	/declare ReadyToCast	  	timer outer 0
	/declare groupbufftimer		timer outer 0
	/declare CCTimer			timer outer 0
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9
|-	/if (${DoHeals}) /call CheckPlugin MQ2WorstHurt
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
	/squelch /alias /tglpet			/togglevariable UsePet
	/squelch /alias /tglpoison		/togglevariable UsePoisons
	/squelch /alias /tgldots		/togglevariable DoDot
	/squelch /alias /tglmezbreak	/togglevariable AllowMezBreak
	/squelch /alias /tglslow		/togglevariable DoSlow
	/squelch /alias /tglferocity	/togglevariable DoFerocity
	/squelch /alias /tglpetslow		/togglevariable DoPetSlow
	/squelch /alias /tgltravel		/togglevariable Travel
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
	/call SetIni Combat DoDot					int ${DoDot}
	/call SetIni Combat Manatonuke				int ${Manatonuke}
	/call SetIni Combat StopNukeAggro			int ${StopNukeAggro}
	/call SetIni Combat UseAoE					int ${UseAoE}
	/call SetIni Combat UseMelee		 		int ${UseMelee}
	/call SetIni Healing DoHeals				int ${DoHeals}
	/call SetIni Healing DynamicHealing			int ${DynamicHealing}
	/call SetIni Item ChestCombatCast			int ${ChestCombatCast}
	/call SetIni Options BringYourOwnSpells		int ${BringYourOwnSpells}
	/call SetIni Pet UsePet		 				int ${UsePet}
	/call SetIni Pet UseSwarmpet		 		int ${UseSwarmpet}
	/call SetIni General Travel					int ${Travel}
	/call SetIni Options AutoRez 				int ${AutoRez}
/return
|* ------------------------------------------------------------------------------------------
| SUB: LoadSpellBar /echo ${Me.Gem[1]}
|------------------------------------------------------------------------------------------ *|
Sub LoadSpellBar
	/if (!${BringYourOwnSpells}) {
		/if (${Me.Standing}) /sit
		/delay 10 ${Me.Sitting}
		/echo \aw Loading Spell Bar
		/call LoadSpellGem "${Spell1}" 1
		/call LoadSpellGem "${Spell2}" 2
		/call LoadSpellGem "${Spell3}" 3
		/call LoadSpellGem "${Spell4}" 4
		/call LoadSpellGem "${Spell5}" 5
		/call LoadSpellGem "${Spell6}" 6
		/call LoadSpellGem "${Spell7}" 7
		/call LoadSpellGem "${Spell8}" 8
		/if (${spellmisc}>8) {
			/call LoadSpellGem "${Spell9}" 9
		}
		/if (${spellmisc}>9) {
			/call LoadSpellGem "${Spell10}" 10
		}
		/if (${spellmisc}>10) {
			/call LoadSpellGem "${Spell11}" 11
		}
		/if (${spellmisc}>11) {
			/call LoadSpellGem "${Spell12}" 12
		}
		/if (${spellmisc}>12) {
			/call LoadSpellGem "${Spell13}" 13
		}
	}
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub CheckSpells
|-*
|-	/if (${Me.Level}>=${Spell[].Level} && ${Me.Book[${Spell[].RankName}]}) {
|-		/varset  ${Spell[].RankName}
|-	} else /if (${Me.Level}>=${Spell[].Level} && ${Me.Book[${Spell[].RankName}]}) {
|-		/varset  ${Spell[].RankName}
|-	}

	/varset TravelSpell Communion of the Cheetah

	/if (${Me.Level}>=${Spell[Ward of Remediation].Level} && ${Me.Book[${Spell[Ward of Remediation].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Remediation].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Regeneration].Level} && ${Me.Book[${Spell[Ward of Regeneration].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Regeneration].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Rejuvenation].Level} && ${Me.Book[${Spell[Ward of Rejuvenation].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Rejuvenation].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Reconstruction].Level} && ${Me.Book[${Spell[Ward of Reconstruction].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Reconstruction].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Recovery].Level} && ${Me.Book[${Spell[Ward of Recovery].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Recovery].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Restoration].Level} && ${Me.Book[${Spell[Ward of Restoration].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Restoration].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Resurgence].Level} && ${Me.Book[${Spell[Ward of Resurgence].RankName}]}) {
		/varset SelfHealProcBuff ${Spell[Ward of Resurgence].RankName}
	}

	/if (${Me.Level}>=${Spell[Talisman of the Unwavering].Level} && ${Me.Book[${Spell[Talisman of the Unwavering].RankName}]}) {
		/varset RegenSpell ${Spell[Talisman of the Unwavering].RankName}
	}
|- CanniSpell
	/if (${Me.Level}>=${Spell[Tribal Bargain].Level} && ${Me.Book[${Spell[Tribal Bargain].RankName}]}) {
		/varset CanniSpell ${Spell[Tribal Bargain].RankName}
	} else /if (${Me.Level}>=${Spell[Tribal Pact].Level} && ${Me.Book[${Spell[Tribal Pact].RankName}]}) {
		/varset CanniSpell ${Spell[Tribal Pact].RankName}
	} else /if (${Me.Level}>=${Spell[Ancestral Pact].Level} && ${Me.Book[${Spell[Ancestral Pact].RankName}]}) {
		/varset CanniSpell ${Spell[Ancestral Pact].RankName}
	} else /if (${Me.Level}>=${Spell[Ancestral Arrangement].Level} && ${Me.Book[${Spell[Ancestral Arrangement].RankName}]}) {
		/varset CanniSpell ${Spell[Ancestral Arrangement].RankName}
	} else /if (${Me.Level}>=${Spell[Ancestral Covenant].Level} && ${Me.Book[${Spell[Ancestral Covenant].RankName}]}) {
		/varset CanniSpell ${Spell[Ancestral Covenant].RankName}
	} else /if (${Me.Level}>=${Spell[Ancestral Obligation].Level} && ${Me.Book[${Spell[Ancestral Obligation].RankName}]}) {
		/varset CanniSpell ${Spell[Ancestral Obligation].RankName}
	}
|- ShamanAura
	/if (${Me.AltAbility[Pact of the Wolf].ID}) {
		/varset ShamanAura Pact of the Wolf
	}
|- FocusSpell
	/if (${Me.Level}>=${Spell[Talisman of the Wulthan].Level} && ${Me.Book[${Spell[Talisman of the Wulthan].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of the Wulthan].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of the Doomscale].Level} && ${Me.Book[${Spell[Talisman of the Doomscale].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of the Doomscale].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of the Courageous].Level} && ${Me.Book[${Spell[Talisman of the Courageous].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of the Courageous].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of Kolos' Unity].Level} && ${Me.Book[${Spell[Talisman of Kolos' Unity].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of Kolos' Unity].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of Soul's Unity].Level} && ${Me.Book[${Spell[Talisman of Soul's Unity].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of Soul's Unity].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of Unity].Level} && ${Me.Book[${Spell[Talisman of Unity].RankName}]}) {
		/varset FocusSpell ${Spell[Talisman of Unity].RankName}
	}
|- RunSpeedBuff
	/if (${Me.Level}>=${Spell[Spirit of Tala'Tak].Level} && ${Me.Book[${Spell[Spirit of Tala'Tak].RankName}]}) {
		/varset RunSpeedBuff ${Spell[Spirit of Tala'Tak].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Bih'Li].Level} && ${Me.Book[${Spell[Spirit of Bih'Li].RankName}]}) {
		/varset RunSpeedBuff ${Spell[Spirit of Bih'Li].RankName}
	}
|- DichoSpell
	/if (${Me.Level}>=${Spell[Dissident Roar].Level} && ${Me.Book[${Spell[Dissident Roar].RankName}]}) {
		/varset DichoSpell ${Spell[Dissident Roar].RankName}
	} else /if (${Me.Level}>=${Spell[Roar of the Lion].Level} && ${Me.Book[${Spell[Roar of the Lion].RankName}]}) {
		/varset DichoSpell ${Spell[Roar of the Lion].RankName}
	}
|- PetSpell
	/if (${Me.Level}>=${Spell[Mirtuk's Faithful].Level} && ${Me.Book[${Spell[Mirtuk's Faithful].RankName}]}) {
		/varset PetSpell ${Spell[Mirtuk's Faithful].RankName}
	} else /if (${Me.Level}>=${Spell[Olesira's Faithful].Level} && ${Me.Book[${Spell[Olesira's Faithful].RankName}]}) {
		/varset PetSpell ${Spell[Olesira's Faithful].RankName}
	} else /if (${Me.Level}>=${Spell[Kriegas' Faithful].Level} && ${Me.Book[${Spell[Kriegas' Faithful].RankName}]}) {
		/varset PetSpell ${Spell[Kriegas' Faithful].RankName}
	} else /if (${Me.Level}>=${Spell[Hilnaah's Faithful].Level} && ${Me.Book[${Spell[Hilnaah's Faithful].RankName}]}) {
		/varset PetSpell ${Spell[Hilnaah's Faithful].RankName}
	} else /if (${Me.Level}>=${Spell[Wurt's Faithful].Level} && ${Me.Book[${Spell[Wurt's Faithful].RankName}]}) {
		/varset PetSpell ${Spell[Wurt's Faithful].RankName}
	}
|- PetBuffSpell
	/if (${Me.Level}>=${Spell[Spirit Bolstering].Level} && ${Me.Book[${Spell[Spirit Bolstering].RankName}]}) {
		/varset PetBuffSpell ${Spell[Spirit Bolstering].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit Quickening].Level} && ${Me.Book[${Spell[Spirit Quickening].RankName}]}) {
		/varset PetBuffSpell ${Spell[Spirit Quickening].RankName}
	}
|- RecklessHeal1
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Reckless Rejuvenation].RankName}]}) {
		/varset RecklessHeal1 ${Spell[Reckless Rejuvenation].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Reckless Regeneration].RankName}]}) {
		/varset RecklessHeal1 ${Spell[Reckless Regeneration].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Reckless Restoration].RankName}]}) {
		/varset RecklessHeal1 ${Spell[Reckless Restoration].RankName}
	}
|- RecklessHeal2
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Reckless Regeneration].RankName}]}) {
		/varset RecklessHeal2 ${Spell[Reckless Regeneration].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Reckless Restoration].RankName}]}) {
		/varset RecklessHeal2 ${Spell[Reckless Restoration].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Reckless Remedy].RankName}]}) {
		/varset RecklessHeal2 ${Spell[Reckless Remedy].RankName}
	}
|- RecklessHeal3
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Reckless Restoration].RankName}]}) {
		/varset RecklessHeal3 ${Spell[Reckless Restoration].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Reckless Remedy].RankName}]}) {
		/varset RecklessHeal3 ${Spell[Reckless Remedy].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Reckless Mending].RankName}]}) {
		/varset RecklessHeal3 ${Spell[Reckless Mending].RankName}
	}
|- AESpiritualHeal
	/if (${Me.Level}>=${Spell[Spiritual Squall].Level} && ${Me.Book[${Spell[Spiritual Squall].RankName}]}) {
		/varset AESpiritualHeal ${Spell[Spiritual Squall].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Swell].Level} && ${Me.Book[${Spell[Spiritual Swell].RankName}]}) {
		/varset AESpiritualHeal ${Spell[Spiritual Swell].RankName}
	} else /if (${Me.Level}>=${Spell[Spiritual Surge].Level} && ${Me.Book[${Spell[Spiritual Surge].RankName}]}) {
		/varset AESpiritualHeal ${Spell[Spiritual Surge].RankName}
	}
|- RecourseHeal
	/if (${Me.Level}>=${Spell[Eyrzekla's Recourse].Level} && ${Me.Book[${Spell[Eyrzekla's Recourse].RankName}]}) {
		/varset RecourseHeal ${Spell[Eyrzekla's Recourse].RankName}
	} else /if (${Me.Level}>=${Spell[Krasir's Recourse].Level} && ${Me.Book[${Spell[Krasir's Recourse].RankName}]}) {
		/varset RecourseHeal ${Spell[Krasir's Recourse].RankName}
	} else /if (${Me.Level}>=${Spell[Blezon's Recourse].Level} && ${Me.Book[${Spell[Blezon's Recourse].RankName}]}) {
		/varset RecourseHeal ${Spell[Blezon's Recourse].RankName}
	} else /if (${Me.Level}>=${Spell[Gotikan's Recourse].Level} && ${Me.Book[${Spell[Gotikan's Recourse].RankName}]}) {
		/varset RecourseHeal ${Spell[Gotikan's Recourse].RankName}
	} else /if (${Me.Level}>=${Spell[Qirik's Recourse].Level} && ${Me.Book[${Spell[Qirik's Recourse].RankName}]}) {
		/varset RecourseHeal ${Spell[Qirik's Recourse].RankName}
	}
|- Malo
	/if (${Me.Level}>=${Spell[Malosinata].Level} && ${Me.Book[${Spell[Malosinata].RankName}]}) {
		/varset Malo ${Spell[Malosinata].RankName}
	}

|- InterventionHeal
	/if (${Me.Level}>=${Spell[Prehistoric Intervention].Level} && ${Me.Book[${Spell[Prehistoric Intervention].RankName}]}) {
		/varset InterventionHeal ${Spell[Prehistoric Intervention].RankName}
	} else /if (${Me.Level}>=${Spell[Historian's Intervention].Level} && ${Me.Book[${Spell[Historian's Intervention].RankName}]}) {
		/varset InterventionHeal ${Spell[Historian's Intervention].RankName}
	} else /if (${Me.Level}>=${Spell[Antecessor's Intervention].Level} && ${Me.Book[${Spell[Antecessor's Intervention].RankName}]}) {
		/varset InterventionHeal ${Spell[Antecessor's Intervention].RankName}
	} else /if (${Me.Level}>=${Spell[Progenitor's Intervention].Level} && ${Me.Book[${Spell[Progenitor's Intervention].RankName}]}) {
		/varset InterventionHeal ${Spell[Progenitor's Intervention].RankName}
	} else /if (${Me.Level}>=${Spell[Ascendant's Intervention].Level} && ${Me.Book[${Spell[Ascendant's Intervention].RankName}]}) {
		/varset InterventionHeal ${Spell[Ascendant's Intervention].RankName}
	}
|- GroupRenewalHoT
	/if (${Me.Level}>=${Spell[Cloud of Renewal].Level} && ${Me.Book[${Spell[Cloud of Renewal].RankName}]}) {
		/varset GroupRenewalHoT ${Spell[Cloud of Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Shear of Renewal].Level} && ${Me.Book[${Spell[Shear of Renewal].RankName}]}) {
		/varset GroupRenewalHoT ${Spell[Shear of Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Wisp of Renewal].Level} && ${Me.Book[${Spell[Wisp of Renewal].RankName}]}) {
		/varset GroupRenewalHoT ${Spell[Wisp of Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Phantom of Renewal].Level} && ${Me.Book[${Spell[Phantom of Renewal].RankName}]}) {
		/varset GroupRenewalHoT ${Spell[Phantom of Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Penumbra of Renewal].Level} && ${Me.Book[${Spell[Penumbra of Renewal].RankName}]}) {
		/varset GroupRenewalHoT ${Spell[Penumbra of Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Shadow of Renewal].Level} && ${Me.Book[${Spell[Shadow of Renewal].RankName}]}) {
		/varset GroupRenewalHoT ${Spell[Shadow of Renewal].RankName}
	}
	/varset SetHoTDurationTimer ${Math.Calc[((${Spell[${GroupRenewalHoT}].Duration}*6)*${DurationMod})+(${Me.AltAbility[Prolonged Salve].Rank}*6)].Int}
|- CurseDoT1
	/if (${Me.Level}>=${Spell[Erogo's Curse].Level} && ${Me.Book[${Spell[Erogo's Curse].RankName}]}) {
		/varset CurseDoT1 ${Spell[Erogo's Curse].RankName}
	} else /if (${Me.Level}>=${Spell[Sraskus' Curse].Level} && ${Me.Book[${Spell[Sraskus' Curse].RankName}]}) {
		/varset CurseDoT1 ${Spell[Sraskus' Curse].RankName}
	} else /if (${Me.Level}>=${Spell[Enalam's Curse].Level} && ${Me.Book[${Spell[Enalam's Curse].RankName}]}) {
		/varset CurseDoT1 ${Spell[Enalam's Curse].RankName}
	}
|- CurseDoT2
	/if (${Me.Level}>=${Spell[Jinx].Level} && ${Me.Book[${Spell[Jinx].RankName}]}) {
		/varset CurseDoT2 ${Spell[Jinx].RankName}
	} else /if (${Me.Level}>=${Spell[Garugaru].Level} && ${Me.Book[${Spell[Garugaru].RankName}]}) {
		/varset CurseDoT2 ${Spell[Garugaru].RankName}
	} else /if (${Me.Level}>=${Spell[Naganaga].Level} && ${Me.Book[${Spell[Naganaga].RankName}]}) {
		/varset CurseDoT2 ${Spell[Naganaga].RankName}
	} else /if (${Me.Level}>=${Spell[Hoodoo].Level} && ${Me.Book[${Spell[Hoodoo].RankName}]}) {
		/varset CurseDoT2 ${Spell[Hoodoo].RankName}
	} else /if (${Me.Level}>=${Spell[Hex].Level} && ${Me.Book[${Spell[Hex].RankName}]}) {
		/varset CurseDoT2 ${Spell[Hex].RankName}
	}
|- FastPoisonDoT
	/if (${Me.Level}>=${Spell[Mawmun's Venom].Level} && ${Me.Book[${Spell[Mawmun's Venom].RankName}]}) {
		/varset FastPoisonDoT ${Spell[Mawmun's Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Serpentil's Venom].Level} && ${Me.Book[${Spell[Serpentil's Venom].RankName}]}) {
		/varset FastPoisonDoT ${Spell[Serpentil's Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Banescale's Venom].Level} && ${Me.Book[${Spell[Banescale's Venom].RankName}]}) {
		/varset FastPoisonDoT ${Spell[Banescale's Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Stranglefang's Venom].Level} && ${Me.Book[${Spell[Stranglefang's Venom].RankName}]}) {
		/varset FastPoisonDoT ${Spell[Stranglefang's Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Undaleen's Venom].Level} && ${Me.Book[${Spell[Undaleen's Venom].RankName}]}) {
		/varset FastPoisonDoT ${Spell[Undaleen's Venom].RankName}
	}
|- FastDiseaseDoT
	/if (${Me.Level}>=${Spell[Hoshkar's Malady].Level} && ${Me.Book[${Spell[Hoshkar's Malady].RankName}]}) {
		/varset FastDiseaseDoT ${Spell[Hoshkar's Malady].RankName}
	} else /if (${Me.Level}>=${Spell[Sephry's Malady].Level} && ${Me.Book[${Spell[Sephry's Malady].RankName}]}) {
		/varset FastDiseaseDoT ${Spell[Sephry's Malady].RankName}
	} else /if (${Me.Level}>=${Spell[Elsrop's Malady].Level} && ${Me.Book[${Spell[Elsrop's Malady].RankName}]}) {
		/varset FastDiseaseDoT ${Spell[Elsrop's Malady].RankName}
	} else /if (${Me.Level}>=${Spell[Giaborn's Malady].Level} && ${Me.Book[${Spell[Giaborn's Malady].RankName}]}) {
		/varset FastDiseaseDoT ${Spell[Giaborn's Malady].RankName}
	} else /if (${Me.Level}>=${Spell[Nargul's Malady].Level} && ${Me.Book[${Spell[Nargul's Malady].RankName}]}) {
		/varset FastDiseaseDoT ${Spell[Nargul's Malady].RankName}
	}
|- TwinHealNuke
	/if (${Me.Level}>=${Spell[Frostbitten Gift].Level} && ${Me.Book[${Spell[Frostbitten Gift].RankName}]}) {
		/varset TwinHealNuke ${Spell[Frostbitten Gift].RankName}
	} else /if (${Me.Level}>=${Spell[Glacial Gift].Level} && ${Me.Book[${Spell[Glacial Gift].RankName}]}) {
		/varset TwinHealNuke ${Spell[Glacial Gift].RankName}
	} else /if (${Me.Level}>=${Spell[Frigid Gift].Level} && ${Me.Book[${Spell[Frigid Gift].RankName}]}) {
		/varset TwinHealNuke ${Spell[Frigid Gift].RankName}
	} else /if (${Me.Level}>=${Spell[Freezing Gift].Level} && ${Me.Book[${Spell[Freezing Gift].RankName}]}) {
		/varset TwinHealNuke ${Spell[Freezing Gift].RankName}
	} else /if (${Me.Level}>=${Spell[Frozen Gift].Level} && ${Me.Book[${Spell[Frozen Gift].RankName}]}) {
		/varset TwinHealNuke ${Spell[Frozen Gift].RankName}
	} else /if (${Me.Level}>=${Spell[Frost Gift].Level} && ${Me.Book[${Spell[Frost Gift].RankName}]}) {
		/varset TwinHealNuke ${Spell[Frost Gift].RankName}
	}
|- PoisonNuke
	/if (${Me.Level}>=${Spell[Nexona's Spear of Venom].Level} && ${Me.Book[${Spell[Nexona's Spear of Venom].RankName}]}) {
		/varset PoisonNuke ${Spell[Nexona's Spear of Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Serisaria's Spear of Venom].Level} && ${Me.Book[${Spell[Serisaria's Spear of Venom].RankName}]}) {
		/varset PoisonNuke ${Spell[Serisaria's Spear of Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Slaunk's Spear of Venom].Level} && ${Me.Book[${Spell[Slaunk's Spear of Venom].RankName}]}) {
		/varset PoisonNuke ${Spell[Slaunk's Spear of Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Hiqork's Spear of Venom].Level} && ${Me.Book[${Spell[Hiqork's Spear of Venom].RankName}]}) {
		/varset PoisonNuke ${Spell[Hiqork's Spear of Venom].RankName}
	} else /if (${Me.Level}>=${Spell[Spinechiller's Spear of Venom].Level} && ${Me.Book[${Spell[Spinechiller's Spear of Venom].RankName}]}) {
		/varset PoisonNuke ${Spell[Spinechiller's Spear of Venom].RankName}
	}
|- FastPoisonNuke
	/if (${Me.Level}>=${Spell[Mawmun's Bite].Level} && ${Me.Book[${Spell[Mawmun's Bite].RankName}]}) {
		/varset FastPoisonNuke ${Spell[Mawmun's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Reefmaw's Bite].Level} && ${Me.Book[${Spell[Reefmaw's Bite].RankName}]}) {
		/varset FastPoisonNuke ${Spell[Reefmaw's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Seedspitter's Bite].Level} && ${Me.Book[${Spell[Seedspitter's Bite].RankName}]}) {
		/varset FastPoisonNuke ${Spell[Seedspitter's Bite].RankName}
	} else /if (${Me.Level}>=${Spell[Bite of the Grendlaen].Level} && ${Me.Book[${Spell[Bite of the Grendlaen].RankName}]}) {
		/varset FastPoisonNuke ${Spell[Bite of the Grendlaen].RankName}
	} else /if (${Me.Level}>=${Spell[Bite of the Blightwolf].Level} && ${Me.Book[${Spell[Bite of the Blightwolf].RankName}]}) {
		/varset FastPoisonNuke ${Spell[Bite of the Blightwolf].RankName}
	}
|-FrostNuke
	/if (${Me.Level}>=${Spell[Ice Shards].Level} && ${Me.Book[${Spell[Ice Shards].RankName}]}) {
		/varset FrostNuke ${Spell[Ice Shards].RankName}
	} else /if (${Me.Level}>=${Spell[Ice Squall].Level} && ${Me.Book[${Spell[Ice Squall].RankName}]}) {
		/varset FrostNuke ${Spell[Ice Squall].RankName}
	} else /if (${Me.Level}>=${Spell[Ice Burst].Level} && ${Me.Book[${Spell[Ice Burst].RankName}]}) {
		/varset FrostNuke ${Spell[Ice Burst].RankName}
	} else /if (${Me.Level}>=${Spell[Ice Mass].Level} && ${Me.Book[${Spell[Ice Mass].RankName}]}) {
		/varset FrostNuke ${Spell[Ice Mass].RankName}
	} else /if (${Me.Level}>=${Spell[Ice Floe].Level} && ${Me.Book[${Spell[Ice Floe].RankName}]}) {
		/varset FrostNuke ${Spell[Ice Floe].RankName}
	}
|- ChaoticPoisonDoT
	/if (${Me.Level}>=${Spell[Chaotic Poison].Level} && ${Me.Book[${Spell[Chaotic Poison].RankName}]}) {
		/varset ChaoticPoisonDoT ${Spell[Chaotic Poison].RankName}
	} else /if (${Me.Level}>=${Spell[Chaotic Venom].Level} && ${Me.Book[${Spell[Chaotic Venom].RankName}]}) {
		/varset ChaoticPoisonDoT ${Spell[Chaotic Venom].RankName}
	}

|- AllianceBuff
	/if (${Me.Level}>=${Spell[Ancient Alliance].Level} && ${Me.Book[${Spell[Ancient Alliance].RankName}]}) {
		/varset AllianceBuff ${Spell[Ancient Alliance].RankName}
	}
|- GroupHealProcBuff
	/if (${Me.Level}>=${Spell[Responsive Spirit].Level} && ${Me.Book[${Spell[Responsive Spirit].RankName}]}) {
		/varset GroupHealProcBuff ${Spell[Responsive Spirit].RankName}
	}
|- CureSpell
	/if (${Me.Level}>=${Spell[Blood of Tevik].Level} && ${Me.Book[${Spell[Blood of Tevik].RankName}]}) {
		/varset CureSpell ${Spell[Blood of Tevik].RankName}
	} else /if (${Me.Level}>=${Spell[Blood of Rivans].Level} && ${Me.Book[${Spell[Blood of Rivans].RankName}]}) {
		/varset CureSpell ${Spell[Blood of Rivans].RankName}
	} else /if (${Me.Level}>=${Spell[Blood of Sanera].Level} && ${Me.Book[${Spell[Blood of Sanera].RankName}]}) {
		/varset CureSpell ${Spell[Blood of Sanera].RankName}
	} else /if (${Me.Level}>=${Spell[Blood of Klar].Level} && ${Me.Book[${Spell[Blood of Klar].RankName}]}) {
		/varset CureSpell ${Spell[Blood of Klar].RankName}
	} else /if (${Me.Level}>=${Spell[Blood of Corbeth].Level} && ${Me.Book[${Spell[Blood of Corbeth].RankName}]}) {
		/varset CureSpell ${Spell[Blood of Corbeth].RankName}
	} else /if (${Me.Level}>=${Spell[Blood of Avoling].Level} && ${Me.Book[${Spell[Blood of Avoling].RankName}]}) {
		/varset CureSpell ${Spell[Blood of Avoling].RankName}
	}
|- PureSpiritSpell
	/if (${Me.Level}>=${Spell[Pure Spirit].Level} && ${Me.Book[${Spell[Pure Spirit].RankName}]}) {
		/varset PureSpiritSpell ${Spell[Pure Spirit].RankName}
	}
|- SlowSpell
	/if (${Me.AltAbility[Turgur's Swarm].ID}) {
		/varset SlowSpell Turgur's Swarm
	}
|- AESlowSpell
	/if (${Me.AltAbility[Turgur's Virulent Swarm].ID}) {
		/varset AESlowSpell Turgur's Virulent Swarm
	}
|- MaloSpell
	/if (${Me.AltAbility[Malaise].ID}) {
		/varset MaloSpell Malaise
	}
|- AEMaloSpell
	/if (${Me.AltAbility[Wind of Malaise].ID}) {
		/varset AEMaloSpell Wind of Malaise
	}
|- GrowthBuff
	/if (${Me.Level}>=${Spell[Savage Growth].Level} && ${Me.Book[${Spell[Savage Growth].RankName}]}) {
		/varset GrowthBuff ${Spell[Savage Growth].RankName}
	} else /if (${Me.Level}>=${Spell[Ferocious Growth].Level} && ${Me.Book[${Spell[Ferocious Growth].RankName}]}) {
		/varset GrowthBuff ${Spell[Ferocious Growth].RankName}
	} else /if (${Me.Level}>=${Spell[Rampant Growth].Level} && ${Me.Book[${Spell[Rampant Growth].RankName}]}) {
		/varset GrowthBuff ${Spell[Rampant Growth].RankName}
	} else /if (${Me.Level}>=${Spell[Unfettered Growth].Level} && ${Me.Book[${Spell[Unfettered Growth].RankName}]}) {
		/varset GrowthBuff ${Spell[Unfettered Growth].RankName}
	} else /if (${Me.Level}>=${Spell[Untamed Growth].Level} && ${Me.Book[${Spell[Untamed Growth].RankName}]}) {
		/varset GrowthBuff ${Spell[Untamed Growth].RankName}
	}
|- MeleeProcBuff
	/if (${Me.Level}>=${Spell[Talisman of the Sabretooth].Level} && ${Me.Book[${Spell[Talisman of the Sabretooth].RankName}]}) {
		/varset MeleeProcBuff ${Spell[Talisman of the Sabretooth].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of the Leopard].Level} && ${Me.Book[${Spell[Talisman of the Leopard].RankName}]}) {
		/varset MeleeProcBuff ${Spell[Talisman of the Leopard].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of the Snow Leopard].Level} && ${Me.Book[${Spell[Talisman of the Snow Leopard].RankName}]}) {
		/varset MeleeProcBuff ${Spell[Talisman of the Snow Leopard].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of the Lion].Level} && ${Me.Book[${Spell[Talisman of the Lion].RankName}]}) {
		/varset MeleeProcBuff ${Spell[Talisman of the Lion].RankName}
	} else /if (${Me.Level}>=${Spell[Talisman of the Tiger].Level} && ${Me.Book[${Spell[Talisman of the Tiger].RankName}]}) {
		/varset MeleeProcBuff ${Spell[Talisman of the Tiger].RankName}
	}
|- SlowProcBuff
	/if (${Me.Level}>=${Spell[Incapacity].Level} && ${Me.Book[${Spell[Incapacity].RankName}]}) {
		/varset SlowProcBuff ${Spell[Incapacity].RankName}
	} else /if (${Me.Level}>=${Spell[Sluggishness].Level} && ${Me.Book[${Spell[Sluggishness].RankName}]}) {
		/varset SlowProcBuff ${Spell[Sluggishness].RankName}
	} else /if (${Me.Level}>=${Spell[Fatigue].Level} && ${Me.Book[${Spell[Fatigue].RankName}]}) {
		/varset SlowProcBuff ${Spell[Fatigue].RankName}
	} else /if (${Me.Level}>=${Spell[Apathy].Level} && ${Me.Book[${Spell[Apathy].RankName}]}) {
		/varset SlowProcBuff ${Spell[Apathy].RankName}
	} else /if (${Me.Level}>=${Spell[Lethargy].Level} && ${Me.Book[${Spell[Lethargy].RankName}]}) {
		/varset SlowProcBuff ${Spell[Lethargy].RankName}
	} else /if (${Me.Level}>=${Spell[Listlessness].Level} && ${Me.Book[${Spell[Listlessness].RankName}]}) {
		/varset SlowProcBuff ${Spell[Listlessness].RankName}
	}
|- PackSelfBuff
	/if (${Me.Level}>=${Spell[Pack of Mirtuk].Level} && ${Me.Book[${Spell[Pack of Mirtuk].RankName}]}) {
		/varset PackSelfBuff ${Spell[Pack of Mirtuk].RankName}
	} else /if (${Me.Level}>=${Spell[Pack of Olesira].Level} && ${Me.Book[${Spell[Pack of Olesira].RankName}]}) {
		/varset PackSelfBuff ${Spell[Pack of Olesira].RankName}
	} else /if (${Me.Level}>=${Spell[Pack of Kriegas].Level} && ${Me.Book[${Spell[Pack of Kriegas].RankName}]}) {
		/varset PackSelfBuff ${Spell[Pack of Kriegas].RankName}
	} else /if (${Me.Level}>=${Spell[Pack of Hilnaah].Level} && ${Me.Book[${Spell[Pack of Hilnaah].RankName}]}) {
		/varset PackSelfBuff ${Spell[Pack of Hilnaah].RankName}
	} else /if (${Me.Level}>=${Spell[Pack of Wurt].Level} && ${Me.Book[${Spell[Pack of Wurt].RankName}]}) {
		/varset PackSelfBuff ${Spell[Pack of Wurt].RankName}
	}
	/if (${CureOther}) {
		/varset CureSpell ${PureSpiritSpell}
	}
	/varset Spell1 ${RecklessHeal1}
	/varset Spell2 ${RecklessHeal2}
	/varset Spell3 ${RecklessHeal3}
	/varset Spell4 ${RecourseHeal}
	/varset Spell5 ${InterventionHeal}
	/varset Spell6 ${AESpiritualHeal}
|-	/varset Spell7 ${AllianceBuff}
	/varset Spell7 ${GroupRenewalHoT}
	/if (${DichoSpell.NotEqual[NULL]}) {
		/varset Spell8 ${DichoSpell}
	} else /if (${MeleeProcBuff.NotEqual[NULL]}) {
		/varset Spell8 ${MeleeProcBuff}
	}
	/varset Spell9 ${GrowthBuff}
	|- ${SlowProcBuff}
	/varset Spell10 ${CurseDoT1} 
	/varset Spell11 ${TwinHealNuke}
	/if (${spellmisc}==12) {
		/varset Spell12 ${FastDiseaseDoT}
		/varset miscspellremem ${Spell12}
	} else /if (${spellmisc}==13) {
		/varset Spell12 ${FastDiseaseDoT}
		/if (${ChaoticPoisonDoT.NotEqual[NULL]}) {
			/varset Spell13 ${ChaoticPoisonDoT}
		} else {
			/varset Spell13 ${FastPoisonDoT}
		}
		/varset miscspellremem ${Spell13}
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
|- SUB: BIND BNDSingleCure - 
|----------------------------------------------------------------------------
Sub Bind_BNDSingleCure(int RequestorID)
	/call SingleCure ${RequestorID}
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
/echo \ag/tgltravel\aw - Turn the use of group cheetah/invis
/return