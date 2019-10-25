|- ihcenchutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub EnchSetup
|-Create Alias
	|-- Toggles
	/squelch /alias /byos			/setvarint Toggle BringYourOwnSpells
	/squelch /alias /charmstun		/setvarint Toggle CharmPreStun
	/squelch /alias /charmtash		/setvarint Toggle CharmPreTash
	/squelch /alias /tglblur		/setvarint Toggle DoBlurr
	/squelch /alias /tglcharm		/setvarint Toggle UseCharmPet
	/squelch /alias /tglcrip		/setvarint Toggle DoCripple
	/squelch /alias /tgldicho		/setvarint Toggle UseDicho
	/squelch /alias /tgldots		/setvarint Toggle UseDoTs
	/squelch /alias /tgldps			/setvarint Toggle DoDPS
	/squelch /alias /tglpet			/setvarint Toggle UsePet
	/squelch /alias /tglmez			/setvarint Toggle MezOn
	/squelch /alias /tglmezmsg		/setvarint Toggle MezAnnounce
	/squelch /alias /tglndt			/setvarint Toggle DoNDTBuff
	/squelch /alias /tgltash		/setvarint Toggle DoTash
	/squelch /alias /tglslow		/setvarint Toggle DoSlow
	/squelch /alias /tglstrip		/setvarint Toggle StripBuffs
	|-- Sets
	/squelch /alias /autodebuffat	/setvarint Set AutoDebuffAt
	/squelch /alias /blurpct		/setvarint Set BlurrAggroPct
	/squelch /alias /maxmezcount	/setvarint Set MaxMezCount
	/squelch /alias /mezaecount		/setvarint Set MezAECount
	/squelch /alias /mezmaxlevel	/setvarint Set MezMaxLevel
	/squelch /alias /mezminlevel	/setvarint Set MezMinLevel
	/squelch /alias /mezradius		/setvarint Set MezRadius
	/squelch /alias /mezstartcount	/setvarint Set MezStartCount
	/squelch /alias /mezstophp		/setvarint Set MezStopHPs	
|-Declare AA and Spell variables
  |-Buffs
	/declare AuraBuff1				string	outer	"NULL"
	/declare AuraBuff1Name			string 	outer 	"NULL"
	/declare AuraRecastDelay		timer 	outer	0
	/declare AuraBuff2				string 	outer	"NULL"
	/declare AuraBuff2Name			string 	outer	"NULL"
	/declare MeleeAura				string 	outer	"NULL"
	/declare MeleeAuraName			string 	outer	"NULL"
	/declare GroupHaste				string 	outer	"NULL"
	/declare GroupMana				string 	outer	"NULL"
	/declare MezBuff				string 	outer	"NULL"
	/declare ProcBuff				string 	outer	"NULL"
	/declare ProcBuffCount			int		outer	0
	/declare ProcBuffRecastTimer	timer	outer	0
	/declare SelfHPBuff				string	outer	"NULL"
	/declare SelfRune1				string	outer	"NULL"
	/declare SelfRune2				string	outer	"NULL"
	/declare SingleHaste			string	outer	"NULL"
	/declare SingleMana				string	outer	"NULL"
	/declare SingleRune				string	outer	"NULL"
	/declare GroupRune				string	outer	"NULL"
	/declare AggroRune				string	outer	"NULL"
	/declare AggroBuff				string	outer	"NULL"
	/declare SingleSpellShield		string	outer	"NULL"
	/declare GroupSpellShield		string	outer	"NULL"
	/declare SingleDoTShield		string	outer	"NULL"
	/declare GroupDoTShield			string	outer	"NULL"
	/declare SingleMeleeShield		string	outer	"NULL"
	/declare SelfGuardShield		string	outer	"NULL"
	/declare GroupAuspiceBuff		string	outer	"NULL"
  |-CC
	/declare AEMezReset				int		outer	0
	/declare PBAEStunSpell			string	outer	"NULL"
	/declare TargetAEStun			string	outer	"NULL"
	/declare SingleStunSpell1		string	outer	"NULL"
  |-Charm
	/declare CharmSpell1			string 	outer	"NULL"
	/declare CharmMaxLvl			int		outer	0
	/declare CharmMinMobs			int		outer	2
	/declare CharmDelay				timer	outer 	0
	/declare CharmedID				int		outer	0
	/declare OldCharmedID			int		outer	0
  |-Debuff
	/declare CrippleSpell1			string	outer	"NULL"
	/declare SlowSpell				string	outer	"NULL"
	/declare StripBuffSpell			string	outer	"NULL"
	/declare TashSpell				string 	outer 	"NULL"
	/declare ManaDrainSpell1		string 	outer 	"NULL"
  |-DPS
	/declare DichoSpell				string 	outer	"NULL"
	/declare DoTSpell1				string 	outer	"NULL"
	/declare DoTSpell2				string 	outer	"NULL"
	/declare DoTSpell3				string 	outer	"NULL"
	/declare DPSRecastTimer			timer 	outer	0
	/declare FastNukePct 			int 	outer	90
	/declare NukeSpell1				string 	outer	"NULL"
	/declare NukeSpell2				string 	outer	"NULL"
	/declare NukeSpell3				string 	outer	"NULL"
	/declare NukeSpell4				string 	outer	"NULL"
  |-Pet
	/declare PetSpell				string	outer	"NULL"
	/declare PetBuffSpell			string	outer	"NULL"
	/declare PetAssistTimer			timer 	outer	0
  |- Mez
	/declare LastMobCount           int		outer	0
	/declare MezAEClosest           int		outer	0
	/declare MezAEAA				string	outer	"NULL"
	/declare MezAESpell				string	outer	"NULL"
	/declare MezAESpellFast			string	outer	"NULL"
	/declare MezAETimer             timer	outer	0
	/declare MezBroke               int		outer	0
	/declare MezCheckElements       int		outer	0
	/declare MezImmuneIDs           string	outer
	/declare MezLowestTimer         timer	outer	0
	/declare MezMobAECount          int		outer	0
	/declare MezMobCount            int		outer	0
	/declare MezMobFlag             int		outer	0
	/declare MezMod                 int		outer	0
	/declare MezPBAESpell			string	outer	"NULL"
	/declare MezSpell				string	outer	"NULL"
	/declare MezSpellFast			string	outer	"NULL"
	/declare MezWait                int		outer	0
	/declare MezWatchRadius	        int		outer	0
	/declare MobCount               int		outer	0
	/declare MobFlag                int		outer	1
	/declare NewTargetAdd		    int		outer	0
  |-Utility
	/declare BlurSpell				string	outer	"NULL"
	/declare AEBlurSpell			string	outer	"NULL"
	/declare CalmSpell				string	outer	"NULL"
	/declare FearSpell				string	outer	"NULL"
	/declare RootSpell				string	outer	"NULL" 
|-Config Options	
	/call LoadCommonConfig
	/call LoadIni Charm UseCharmPet		 		int 0
	/call LoadIni Charm CharmMinLvl				int 0
	/call LoadIni Charm CharmPreStun			int 1
	/call LoadIni Charm CharmPreTash			int 1
	/call LoadIni Combat DoDPS					int 1
	/call LoadIni Combat Manatonuke				int 40
	/call LoadIni Combat StickHow				string NULL
	/call LoadIni Combat UseDicho				int 0
	/call LoadIni Combat UseDoTs				int 0
	/call LoadIni Combat UseMelee		 		int 0
	/call LoadIni Combat UsePet			 		int 1
	/call LoadIni Debuff AutoDebuffAt			int 99
	/call LoadIni Debuff DoTash					int 1
	/call LoadIni Debuff DoSlow					int 1
	/call LoadIni Debuff DoCripple				int 0
	/call LoadIni Debuff DoBlurr				int 0
	/call LoadIni Debuff BlurrAggroPct			int 50
	/call LoadIni Debuff StripBuffs				int 1
	/call LoadIni Mez AutoLevelRange         	int 1
	/call LoadIni Mez MezOn                 	int 1
	/call LoadIni Mez MezAnnounce               int 1	
	/call LoadIni Mez MezStartCount             int 2
	/call LoadIni Mez MezAECount               	int 3
	/call LoadIni Mez MaxMezCount               int 13
    /call LoadIni Mez MezRadius             	int 100
    /call LoadIni Mez MezMinLevel           	int 0
    /call LoadIni Mez MezMaxLevel           	int 0
    /call LoadIni Mez MezStopHPs            	int 80
	/call LoadIni Mez UseTwinCastMez         	int 1
	/call LoadIni Mez UseAEAAMez	         	int 0
	/call LoadIni Options BringYourOwnSpells	int 0
	/call LoadIni Options DoNDTBuff				int 1
	/call LoadIni Rune UseMeleeRune				int 0
	/call LoadIni Rune UseSpellRune				int 0
	/call LoadIni Rune UseDoTRune				int 0
	/call LoadIni Rune UseAuspice				int 0
	/call LoadIni Rune MeleeRuneHeal			int 0
	/call LoadIni Rune SpellRuneHeal			int 0
	/call LoadIni Rune DoTRuneHeal				int 0
	/call LoadIni Item ChestItemName			string "${Me.Inventory[17].Name}"
	/varcalc MezWatchRadius ${MezRadius}*2
	|-Set AA DurationMod for mez timer from Spell Casting Reinforcement AA
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==1) /varset MezMod 6
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==2) /varset MezMod 12
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==3) /varset MezMod 18
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==4) /varset MezMod 24
	/declare spellmisc 				int outer 8
	/declare spellgem				int outer 1	
	/declare CastResult             string outer
	/declare miscspellremem			string outer NULL
	/declare spellrememtimer		timer outer 0
	/declare groupbufftimer		timer outer 0
	/declare DeBuffTimer		timer outer 0
	/if (${Me.AltAbility[25].Name.Find[disabled]} && ${Me.AltAbilityReady[25]}) {
		/alt act 25
		/delay 5
	}
|- Below Code is only needed for using ihcxtenchmez.inc
|-	/declare MezCount[13]           			int         outer 	0
|-	/declare MezArray[50,3]			            string      outer       NULL
|-	/declare DebugMez							int			outer	0
|-	/declare DEBUGALL							int 		outer	0

|-	/if (${MezOn}) /call CreateTimersMez
/return
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges
	/varset changetoini 0
	/call SaveCommonConfig
	/call SetIni Charm UseCharmPet		 	int ${UseCharmPet}
	/call SetIni Charm CharmMinLvl			int ${CharmMinLvl}
	/call SetIni Charm CharmPreStun			int ${CharmPreStun}
	/call SetIni Charm CharmPreTash			int ${CharmPreTash}
	/call SetIni Combat DoDPS				int ${DoDPS}
	/call SetIni Combat Manatonuke			int ${Manatonuke}
	/call SetIni Combat UseDicho			int ${UseDicho}
	/call SetIni Combat UseDoTs				int ${UseDoTs}
	/call SetIni Combat UseMelee		 	int ${UseMelee}
	/call SetIni Combat UsePet			 	int ${UsePet}
	/call SetIni Debuff AutoDebuffAt		int ${AutoDebuffAt}
	/call SetIni Debuff DoTash				int ${DoTash}
	/call SetIni Debuff DoSlow				int ${DoSlow}
	/call SetIni Debuff DoCripple			int ${DoCripple}
	/call SetIni Debuff DoBlurr				int ${DoBlurr}
	/call SetIni Debuff BlurrAggroPct		int ${BlurrAggroPct}
	/call SetIni Debuff StripBuffs			int ${StripBuffs}
	/call SetIni Mez AutoLevelRange         int ${AutoLevelRange}
	/call SetIni Mez MezOn                 	int ${MezOn}
	/call SetIni Mez MezAnnounce            int ${MezAnnounce}	
	/call SetIni Mez MezStartCount          int ${MezStartCount}
	/call SetIni Mez MezAECount             int ${MezAECount}
	/call SetIni Mez MaxMezCount            int ${MaxMezCount}
    /call SetIni Mez MezRadius             	int ${MezRadius}
    /call SetIni Mez MezMinLevel           	int ${MezMinLevel}
    /call SetIni Mez MezMaxLevel           	int ${MezMaxLevel}
    /call SetIni Mez MezStopHPs            	int ${MezStopHPs}
	/call SetIni Mez UseTwinCastMez         int ${UseTwinCastMez}
	/call SetIni Options BringYourOwnSpells	int ${BringYourOwnSpells}
	/call SetIni Options DoNDTBuff			int ${DoNDTBuff}
	/call SetIni Rune UseMeleeRune			int ${UseMeleeRune}
	/call SetIni Rune UseSpellRune			int ${UseSpellRune}
	/call SetIni Rune UseDoTRune			int ${UseDoTRune}
	/call SetIni Rune UseAuspice			int ${UseAuspice}
	/call SetIni Rune MeleeRuneHeal			int ${MeleeRuneHeal}
	/call SetIni Rune SpellRuneHeal			int ${SpellRuneHeal}
	/call SetIni Rune DoTRuneHeal			int ${DoTRuneHeal}
/return
|----------------------------------------------------------------------------
|- SUB: CheckOptions - Used to sort conflicting options at startup and set basic values if needed
|---------------------------------------------------------------------------- 
Sub CheckOptions
	/if (${AutoCampHold}) /moveto dist 2
	/if (${CharmMaxLvl}==0 || ${CharmMaxLvl}>${Spell[${CharmSpell1}].MaxLevel}) {
			/varset CharmMaxLvl ${Spell[${CharmSpell1}].MaxLevel}
			/varset changetoini 1
	}
	/if (${MezMinLevel}>${MezMaxLevel} || ${AutoLevelRange}) {
		/varset MezMinLevel 0
	}
	/if (${MezMaxLevel}==0 || ${MezMaxLevel}>${Spell[${MezSpell}].MaxLevel} || ${AutoLevelRange}) {
		/varset MezMaxLevel ${Spell[${MezSpell}].MaxLevel}
		/varset changetoini 1
	}
	/if (${MezMinLevel}==0) {
		/if (${Me.Level}>=40) {
			/varcalc MezMinLevel ${Me.Level}-30 
		} else /if (${Me.Level}>=30) {
			/varcalc MezMinLevel ${Me.Level}-20
		} else {
			/varset MezMinLevel 1
		}
		/varset changetoini 1
	}
	/if (${CharmMinLvl}==0) {
		/if (${Me.Level}>=40) {
			/varcalc CharmMinLvl ${Me.Level}-30 
		} else /if (${Me.Level}>=30) {
			/varcalc CharmMinLvl ${Me.Level}-20
		} else {
			/varset CharmMinLvl 1
		}
		/varset changetoini 1
	}
	/if (${UseCharmPet} && ${Me.Pet.ID}) {
		/pet get lost
		/if (${UsePet}) {
			/varset UsePet 0
			/varset changetoini 1
		}
	}
/return
|* ------------------------------------------------------------------------------------------
| SUB: LoadSpellBar
|------------------------------------------------------------------------------------------ *|
Sub LoadSpellBar
	/if (!${BringYourOwnSpells}) {
		/if (${Me.Standing}) /sit
		/delay 10 ${Me.Sitting}
		/echo \aw Loading Spell Bar
		/call LoadSpellGem "${MezSpell}" 1
		/call LoadSpellGem "${MezAESpell}" 2
		/call LoadSpellGem "${TashSpell}" 3
		/call LoadSpellGem "${SlowSpell}" 4
		/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) {
			/call LoadSpellGem "${SingleStunSpell1}" 5
			/if (${UseDicho} && ${Me.Level}>=101 && ${DichoSpell.NotEqual[null]}) {
				/call LoadSpellGem "${DichoSpell}" 6
			} else {
				/call LoadSpellGem "${PBAEStunSpell}" 6
			}
			/call LoadSpellGem "${NukeSpell1}" 7
			/call LoadSpellGem "${NukeSpell2}" 8
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${CharmSpell1}" 11
			} else /if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell3}" 11
			} else {
				/call LoadSpellGem "${MezPBAESpell}" 11
			}
			/if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell1}" 9
				/call LoadSpellGem "${DoTSpell2}" 10
			} else {
				/call LoadSpellGem "${NukeSpell3}" 9
				/call LoadSpellGem "${NukeSpell4}" 10
			}
			/call LoadSpellGem "${ProcBuff}" 12
			/call LoadSpellGem "${RootSpell}" 13
			/varset spellmisc 13
			/varset miscspellremem ${RootSpell}
		} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==4) {
			|- Level 100 - AA strip becomes available - AA AE Memblur becomes available? 
			/if (${Me.Level}>=100) {
				/call LoadSpellGem "${SingleStunSpell1}" 5
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${CharmSpell1}" 6
				} else /if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell3}" 6
				} else {
					/call LoadSpellGem "${PBAEStunSpell}" 6
				}
				/if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell1}" 9
					/call LoadSpellGem "${DoTSpell2}" 10
				} else {
					/call LoadSpellGem "${NukeSpell3}" 9
					/call LoadSpellGem "${NukeSpell4}" 10
				}
				/call LoadSpellGem "${NukeSpell2}" 8
			} else /if (${Me.Level}>=96) {
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${NukeSpell2}" 8
				/call LoadSpellGem "${DoTSpell1}" 9
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${CharmSpell1}" 10
					/call LoadSpellGem "${SingleStunSpell1}" 6
				} else /if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell2}" 10
					/call LoadSpellGem "${DoTSpell3}" 6
				} else {
					/call LoadSpellGem "${NukeSpell3}" 10
					/call LoadSpellGem "${SingleStunSpell1}" 6
				}
			} else /if (${Me.Level}>=89) {
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${NukeSpell2}" 8
				/call LoadSpellGem "${DoTSpell1}" 9
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${CharmSpell1}" 10
					/call LoadSpellGem "${SingleStunSpell1}" 6
				} else /if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell3}" 6
					/call LoadSpellGem "${DoTSpell2}" 10
				} else {
					/call LoadSpellGem "${SingleStunSpell1}" 6
					/call LoadSpellGem "${NukeSpell3}" 10
				}
			} else /if (${Me.Level}>=88) {
			|- Level 88 - Slow+Cripple in 1 spell
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${SingleStunSpell1}" 6
				/call LoadSpellGem "${NukeSpell2}" 8
				/call LoadSpellGem "${DoTSpell1}" 9
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${CharmSpell1}" 10
				} else /if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell2}" 10
				} else {
					/call LoadSpellGem "${NukeSpell3}" 10
				}
			} else /if (${Me.Level}>=86) {
			|- Level 86 - AA slow becomes available 
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${CrippleSpell1}" 6
				/call LoadSpellGem "${DoTSpell1}" 9
				/call LoadSpellGem "${NukeSpell2}" 8
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${CharmSpell1}" 10
				} else /if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell2}" 10
				} else {
					/call LoadSpellGem "${NukeSpell3}" 10
				}
			} else /if (${Me.Level}>=81) {
			|- Level 81 - AA Single Memblur becomes available? 
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${DoTSpell1}" 9
				/call LoadSpellGem "${NukeSpell2}" 8
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${CharmSpell1}" 6
					/call LoadSpellGem "${SingleStunSpell1}" 10
				} else /if (${UseDoTs}) {
					/call LoadSpellGem "${CrippleSpell1}" 6
					/call LoadSpellGem "${DoTSpell2}" 10
				} else {
					/call LoadSpellGem "${CrippleSpell1}" 6
					/call LoadSpellGem "${SingleStunSpell1}" 10
				}
			} else {
				/if (${UseCharmPet}) {
					/call LoadSpellGem "${SingleStunSpell1}" 5
					/call LoadSpellGem "${CharmSpell1}" 6			
				} else {
					/call LoadSpellGem "${StripBuffSpell}" 5
					/call LoadSpellGem "${CrippleSpell1}" 6
				}
				/if (${UseDoTs}) {
					/call LoadSpellGem "${DoTSpell2}" 8
				} else {
					/call LoadSpellGem "${NukeSpell2}" 8
				}
				/call LoadSpellGem "${DoTSpell1}" 9
				/call LoadSpellGem "${BlurSpell}" 10
			}
			/call LoadSpellGem "${NukeSpell1}" 7
			/call LoadSpellGem "${ProcBuff}" 11
			/if (${UseDicho} && ${Me.Level}>=101 && ${DichoSpell.NotEqual[null]}) {
				/call LoadSpellGem "${DichoSpell}" 12
				/varset miscspellremem ${DichoSpell}
			} else {
				/call LoadSpellGem "${RootSpell}" 12
				/varset miscspellremem ${RootSpell}
			}
			/varset spellmisc 12	
		} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==3) {
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${SingleStunSpell1}" 5
				/call LoadSpellGem "${CharmSpell1}" 6			
			} else {
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${CrippleSpell1}" 6
			}
			/call LoadSpellGem "${NukeSpell1}" 7
			/if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell1}" 8
			} else {
				/call LoadSpellGem "${NukeSpell2}" 8
			}
			/call LoadSpellGem "${BlurSpell}" 9
			/call LoadSpellGem "${ProcBuff}" 10
			/call LoadSpellGem "${RootSpell}" 11
			/varset spellmisc 11
			/varset miscspellremem ${RootSpell}
		} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==2) {
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${SingleStunSpell1}" 5
				/call LoadSpellGem "${CharmSpell1}" 6			
			} else {
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${CrippleSpell1}" 6
			}
			/call LoadSpellGem "${NukeSpell1}" 7
			/if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell1}" 8
			} else {
				/call LoadSpellGem "${NukeSpell2}" 8
			}
			/call LoadSpellGem "${ProcBuff}" 9
			/call LoadSpellGem "${BlurSpell}" 10
			/varset spellmisc 10
			/varset miscspellremem ${BlurSpell}
		} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==1) {
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${SingleStunSpell1}" 5
				/call LoadSpellGem "${CharmSpell1}" 6			
			} else {
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${CrippleSpell1}" 6
			}
			/if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell1}" 7
			} else {
				/call LoadSpellGem "${NukeSpell1}" 7
			}
			/call LoadSpellGem "${ProcBuff}" 8
			/call LoadSpellGem "${BlurSpell}" 9
			/varset spellmisc 9
			/varset miscspellremem ${BlurSpell}
		} else {
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${SingleStunSpell1}" 5
				/call LoadSpellGem "${CharmSpell1}" 6			
			} else {
				/call LoadSpellGem "${StripBuffSpell}" 5
				/call LoadSpellGem "${CrippleSpell1}" 6
			}
			/if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell1}" 7
			} else {
				/call LoadSpellGem "${NukeSpell1}" 7
			}
			/call LoadSpellGem "${BlurSpell}" 8
			/varset spellmisc 8
			/varset miscspellremem ${BlurSpell}
		}
	}
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|* ------------------------------------------------------------------------------------------
| SUB: SetEncSpells
|------------------------------------------------------------------------------------------ *|
Sub SetEncSpells
|-AE Mez AA * Var Name : MezAEAA string outer
	/if (${Me.Level}>=85 && ${Me.AltAbilityReady[Beam of Slumber]}) {
		/varset MezAEAA Beam of Slumber
	}
|-Mez Spell * Var Name: MezSpell string	outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Chaotic Delusion].RankName}]} && ${UseTwinCastMez}) {
		/varset MezSpell ${Spell[Chaotic Delusion].RankName}
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Delude].RankName}]}) {
		/varset MezSpell ${Spell[Delude].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Chaotic Bewildering].RankName}]} && ${UseTwinCastMez}) {
		/varset MezSpell ${Spell[Chaotic Bewildering].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Bewilder].RankName}]}) {
		/varset MezSpell ${Spell[Bewilder].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Chaotic Confounding].RankName}]} && ${UseTwinCastMez}) {
		/varset MezSpell ${Spell[Chaotic Confounding].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Confound].RankName}]}) {
		/varset MezSpell ${Spell[Confound].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Chaotic Confusion].RankName}]} && ${UseTwinCastMez}) {
		/varset MezSpell ${Spell[Chaotic Confusion].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Mislead].RankName}]}) {
		/varset MezSpell ${Spell[Mislead].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Chaotic Baffling].RankName}]} && ${UseTwinCastMez}) {
		/varset MezSpell ${Spell[Chaotic Baffling].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Baffle].RankName}]}) {
		/varset MezSpell ${Spell[Baffle].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Chaotic Befuddling].RankName}]} && ${UseTwinCastMez}) {
		/varset MezSpell ${Spell[Chaotic Befuddling].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Befuddle].RankName}]}) {
		/varset MezSpell ${Spell[Befuddle].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Mystify].RankName}]}) {
		/varset MezSpell ${Spell[Mystify].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Bewilderment].RankName}]}) {
		/varset MezSpell ${Spell[Bewilderment].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Euphoria].RankName}]}) {
		/varset MezSpell ${Spell[Euphoria].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Felicity].RankName}]}) {
		/varset MezSpell ${Spell[Felicity].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Bliss].RankName}]}) {
		/varset MezSpell ${Spell[Bliss].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Sleep].RankName}]}) {
		/varset MezSpell ${Spell[Sleep].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Apathy].RankName}]}) {
		/varset MezSpell ${Spell[Apathy].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Glamour of Kintaz].RankName}]}) {
		/varset MezSpell ${Spell[Glamour of Kintaz].RankName}
	} else /if (${Me.Level}>=13 && ${Me.Book[${Spell[Enthrall].RankName}]}) {
		/varset MezSpell ${Spell[Enthrall].RankName}
	} else /if (${Me.Level}>=2 && ${Me.Book[${Spell[Mesmerize].RankName}]}) {
		/varset MezSpell ${Spell[Mesmerize].RankName}
	}
|-AE Mez * Var Name: MezAESpell	string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Perplexing Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Perplexing Wave].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Deadening Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Deadening Wave].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Slackening Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Slackening Wave].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Peaceful Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Peaceful Wave].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Serene Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Serene Wave].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Ensorcelling Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Ensorcelling Wave].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Quelling Wave].RankName}]}) {
		/varset MezAESpell ${Spell[Quelling Wave].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Wake of Subdual].RankName}]}) {
		/varset MezAESpell ${Spell[Wake of Subdual].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Wake of Felicity].RankName}]}) {
		/varset MezAESpell ${Spell[Wake of Felicity].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Bliss of the Nihil].RankName}]}) {
		/varset MezAESpell ${Spell[Bliss of the Nihil].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Fascination].RankName}]}) {
		/varset MezAESpell ${Spell[Fascination].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Mesmerization].RankName}]}) {
		/varset MezAESpell ${Spell[Mesmerization].RankName}
	}
|-Tash * Var Name: TashSpell string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Order of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Order of Tashan].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Decree of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Decree of Tashan].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Enunciation of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Enunciation of Tashan].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Declaration of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Declaration of Tashan].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Clamor of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Clamor of Tashan].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Bark of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Bark of Tashan].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Din of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Din of Tashan].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Echo of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Echo of Tashan].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Howl of Tashan].RankName}]}) {
		/varset TashSpell ${Spell[Howl of Tashan].RankName}
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[Tashanian].RankName}]}) {
		/varset TashSpell ${Spell[Tashanian].RankName}
	} else /if (${Me.Level}>=41 && ${Me.Book[${Spell[Tashania].RankName}]}) {
		/varset TashSpell ${Spell[Tashania].RankName}
	} else /if (${Me.Level}>=18 && ${Me.Book[${Spell[Tashani].RankName}]}) {
		/varset TashSpell ${Spell[Tashani].RankName}
	} else /if (${Me.Level}>=2 && ${Me.Book[${Spell[Tashina].RankName}]}) {
		/varset TashSpell ${Spell[Tashina].RankName}
	}
|-Slow - * Var Name: SlowSpell string outer -  lvl88 and above this is also cripple spell
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Constraining Helix].RankName}]}) {
		/varset SlowSpell ${Spell[Constraining Helix].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Undermining Helix].RankName}]}) {
		/varset SlowSpell ${Spell[Undermining Helix].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Diminishing Helix].RankName}]}) {
		/varset SlowSpell ${Spell[Diminishing Helix].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Attenuating Helix].RankName}]}) {
		/varset SlowSpell ${Spell[Attenuating Helix].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Curtailing Helix].RankName}]}) {
		/varset SlowSpell ${Spell[Curtailing Helix].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Desolate Deeds].RankName}]}) {
		/varset SlowSpell ${Spell[Desolate Deeds].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Dreary Deeds].RankName}]}) {
		/varset SlowSpell ${Spell[Dreary Deeds].RankName}
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[Forlorn Deeds].RankName}]}) {
		/varset SlowSpell ${Spell[Forlorn Deeds].RankName}
	} else /if (${Me.Level}>=41 && ${Me.Book[${Spell[Shiftless Deeds].RankName}]}) {
		/varset SlowSpell ${Spell[Shiftless Deeds].RankName}
	} else /if (${Me.Level}>=23 && ${Me.Book[${Spell[Tepid Deeds].RankName}]}) {
		/varset SlowSpell ${Spell[Tepid Deeds].RankName}
	} else /if (${Me.Level}>=9 && ${Me.Book[${Spell[Languid Pace].RankName}]}) {
		/varset SlowSpell ${Spell[Languid Pace].RankName}
	}
|-Nuke 1 * Var Name: NukeSpell1 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mindslash].RankName}]}) {
		/varset NukeSpell1 ${Spell[Mindslash].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mindsunder].RankName}]}) {
		/varset NukeSpell1 ${Spell[Mindsunder].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mindcleave].RankName}]}) {
		/varset NukeSpell1 ${Spell[Mindcleave].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mindscythe].RankName}]}) {
		/varset NukeSpell1 ${Spell[Mindscythe].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Mindblade].RankName}]}) {
		/varset NukeSpell1 ${Spell[Mindblade].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Spectral Assault].RankName}]}) {
		/varset NukeSpell1 ${Spell[Spectral Assault].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Chromarcana].RankName}]}) {
		/varset NukeSpell1 ${Spell[Chromarcana].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Chromatic Jab].RankName}]}) {
		/varset NukeSpell1 ${Spell[Chromatic Jab].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Polychaotic Assault].RankName}]}) {
		/varset NukeSpell1 ${Spell[Polychaotic Assault].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Multichromatic Assault].RankName}]}) {
		/varset NukeSpell1 ${Spell[Multichromatic Assault].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Polychromatic Assault].RankName}]}) {
		/varset NukeSpell1 ${Spell[Polychromatic Assault].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Ancient Neurosis].RankName}]}) {
		/varset NukeSpell1 ${Spell[Ancient Neurosis].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Colored Chaos].RankName}]}) {
		/varset NukeSpell1 ${Spell[Colored Chaos].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Psychosis].RankName}]}) {
		/varset NukeSpell1 ${Spell[Psychosis].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Ancient Chaos Madness].RankName}]}) {
		/varset NukeSpell1 ${Spell[Ancient Chaos Madness].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Madness of Ikkibi].RankName}]}) {
		/varset NukeSpell1 ${Spell[Madness of Ikkibi].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Insanity].RankName}]}) {
		/varset NukeSpell1 ${Spell[Insanity].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Ancient Chaotic Visions].RankName}]}) {
		/varset NukeSpell1 ${Spell[Ancient Chaotic Visions].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Dementing Visions].RankName}]}) {
		/varset NukeSpell1 ${Spell[Dementing Visions].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Dementia].RankName}]}) {
		/varset NukeSpell1 ${Spell[Dementia].RankName}
	} else /if (${Me.Level}>=43 && ${Me.Book[${Spell[Discordant Mind].RankName}]}) {
		/varset NukeSpell1 ${Spell[Discordant Mind].RankName}
	} else /if (${Me.Level}>=32 && ${Me.Book[${Spell[Anarchy].RankName}]}) {
		/varset NukeSpell1 ${Spell[Anarchy].RankName}
	} else /if (${Me.Level}>=21 && ${Me.Book[${Spell[Chaos Flux].RankName}]}) {
		/varset NukeSpell1 ${Spell[Chaos Flux].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Sanity Warp].RankName}]}) {
		/varset NukeSpell1 ${Spell[Sanity Warp].RankName}
	} else /if (${Me.Level}>=7 && ${Me.Book[${Spell[Chaotic Feedback].RankName}]}) {
		/varset NukeSpell1 ${Spell[Chaotic Feedback].RankName}
	}
|-Nuke 2 * Var Name: NukeSpell2 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mindsunder].RankName}]}) {
		/varset NukeSpell2 ${Spell[Mindsunder].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mindcleave].RankName}]}) {
		/varset NukeSpell2 ${Spell[Mindcleave].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mindscythe].RankName}]}) {
		/varset NukeSpell2 ${Spell[Mindscythe].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mindblade].RankName}]}) {
		/varset NukeSpell2 ${Spell[Mindblade].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Spectral Assault].RankName}]}) {
		/varset NukeSpell2 ${Spell[Spectral Assault].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Chromarcana].RankName}]}) {
		/varset NukeSpell2 ${Spell[Chromarcana].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Polychaotic Assault].RankName}]}) {
		/varset NukeSpell2 ${Spell[Polychaotic Assault].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Multichromatic Assault].RankName}]}) {
		/varset NukeSpell2 ${Spell[Multichromatic Assault].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Polychromatic Assault].RankName}]}) {
		/varset NukeSpell2 ${Spell[Polychromatic Assault].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Ancient Neurosis].RankName}]}) {
		/varset NukeSpell2 ${Spell[Ancient Neurosis].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Colored Chaos].RankName}]}) {
		/varset NukeSpell2 ${Spell[Colored Chaos].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Psychosis].RankName}]}) {
		/varset NukeSpell2 ${Spell[Psychosis].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Ancient Chaos Madness].RankName}]}) {
		/varset NukeSpell2 ${Spell[Ancient Chaos Madness].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Madness of Ikkibi].RankName}]}) {
		/varset NukeSpell2 ${Spell[Madness of Ikkibi].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Insanity].RankName}]}) {
		/varset NukeSpell2 ${Spell[Insanity].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Ancient Chaotic Visions].RankName}]}) {
		/varset NukeSpell2 ${Spell[Ancient Chaotic Visions].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Dementing Visions].RankName}]}) {
		/varset NukeSpell2 ${Spell[Dementing Visions].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Dementia].RankName}]}) {
		/varset NukeSpell2 ${Spell[Dementia].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Discordant Mind].RankName}]}) {
		/varset NukeSpell2 ${Spell[Discordant Mind].RankName}
	} else /if (${Me.Level}>=43 && ${Me.Book[${Spell[Anarchy].RankName}]}) {
		/varset NukeSpell2 ${Spell[Anarchy].RankName}
	} else /if (${Me.Level}>=32 && ${Me.Book[${Spell[Chaos Flux].RankName}]}) {
		/varset NukeSpell2 ${Spell[Chaos Flux].RankName}
	} else /if (${Me.Level}>=21 && ${Me.Book[${Spell[Sanity Warp].RankName}]}) {
		/varset NukeSpell2 ${Spell[Sanity Warp].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Chaotic Feedback].RankName}]}) {
		/varset NukeSpell2 ${Spell[Chaotic Feedback].RankName}
	}
|-Nuke 3 - Fast * Var Name: NukeSpell3 string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Chromatic Flicker].RankName}]}) {
		/varset NukeSpell3 ${Spell[Chromatic Flicker].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Chromatic Blink].RankName}]}) {
		/varset NukeSpell3 ${Spell[Chromatic Blink].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Chromatic Percussion].RankName}]}) {
		/varset NukeSpell3 ${Spell[Chromatic Percussion].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Chromatic Flash].RankName}]}) {
		/varset NukeSpell3 ${Spell[Chromatic Flash].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Chromatic Jab].RankName}]}) {
		/varset NukeSpell3 ${Spell[Chromatic Jab].RankName}
	}
|-Nuke 4 - Fast * Var Name: NukeSpell4 string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Psychic Appropriation].RankName}]}) {
		/varset NukeSpell4 ${Spell[Psychic Appropriation].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Intellectual Appropriation].RankName}]}) {
		/varset NukeSpell4 ${Spell[Intellectual Appropriation].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Mental Appropriation].RankName}]}) {
		/varset NukeSpell4 ${Spell[Mental Appropriation].RankName}
	}
|-DoT 1 * Var Name: DoTSpell1 string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Strangulate].RankName}]}) {
		/varset DoTSpell1 ${Spell[Strangulate].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Drown].RankName}]}) {
		/varset DoTSpell1 ${Spell[Drown].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Stifle].RankName}]}) {
		/varset DoTSpell1 ${Spell[Stifle].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Suffocation].RankName}]}) {
		/varset DoTSpell1 ${Spell[Suffocation].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Constrict].RankName}]}) {
		/varset DoTSpell1 ${Spell[Constrict].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Smother].RankName}]}) {
		/varset DoTSpell1 ${Spell[Smother].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Strangling Air].RankName}]}) {
		/varset DoTSpell1 ${Spell[Strangling Air].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Thin Air].RankName}]}) {
		/varset DoTSpell1 ${Spell[Thin Air].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Arcane Noose].RankName}]}) {
		/varset DoTSpell1 ${Spell[Arcane Noose].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Strangle].RankName}]}) {
		/varset DoTSpell1 ${Spell[Strangle].RankName}
	} else /if (${Me.Level}>=59 && ${Me.Book[${Spell[Asphyxiate].RankName}]}) {
		/varset DoTSpell1 ${Spell[Asphyxiate].RankName}
	} else /if (${Me.Level}>=47 && ${Me.Book[${Spell[Gasping Embrace].RankName}]}) {
		/varset DoTSpell1 ${Spell[Gasping Embrace].RankName}
	} else /if (${Me.Level}>=26 && ${Me.Book[${Spell[Suffocate].RankName}]}) {
		/varset DoTSpell1 ${Spell[Suffocate].RankName}
	} else /if (${Me.Level}>=11 && ${Me.Book[${Spell[Choke].RankName}]}) {
		/varset DoTSpell1 ${Spell[Choke].RankName}
	} else /if (${Me.Level}>=4 && ${Me.Book[${Spell[Suffocating Sphere].RankName}]}) {
		/varset DoTSpell1 ${Spell[Suffocating Sphere].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Shallow Breath].RankName}]}) {
		/varset DoTSpell1 ${Spell[Shallow Breath].RankName}
	}
|-DoT 2 * Var Name: DoTSpell2 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mind Tempest].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Tempest].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mind Storm].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Storm].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mind Squall].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Squall].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mind Spiral].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Spiral].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Mind Helix].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Helix].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Mind Twist].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Twist].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Mind Oscillate].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Oscillate].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Mind Phobiate].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Phobiate].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Mind Shatter].RankName}]}) {
		/varset DoTSpell2 ${Spell[Mind Shatter].RankName}
	}
|-DoT 3 * Var Name: DoTSpell3 string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Deluding Constriction].RankName}]}) {
		/varset DoTSpell3 ${Spell[Deluding Constriction].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Bewildering Constriction].RankName}]}) {
		/varset DoTSpell3 ${Spell[Bewildering Constriction].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Confounding Constriction].RankName}]}) {
		/varset DoTSpell3 ${Spell[Confounding Constriction].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Confusing Constriction].RankName}]}) {
		/varset DoTSpell3 ${Spell[Confusing Constriction].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Baffling Constriction].RankName}]}) {
		/varset DoTSpell3 ${Spell[Baffling Constriction].RankName}
	}

|-Aura Buff 1 * Var Name: AuraBuff1 string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Transfixer's Aura].RankName}]}) {
		/varset MeleeAura ${Spell[Transfixer's Aura].RankName}
		/varset MeleeAuraName Transfixer's Aura
	}

|-Aura Buff 1 * Var Name: AuraBuff1 string outer
	/if (${Me.Level}>=84 && ${Me.Book[${Spell[Twincast Aura].RankName}]}) {
		/varset AuraBuff1 ${Spell[Twincast Aura].RankName}
		/varset AuraBuff1Name Twincast Aura
	}
|-Aura Buff 2 * Var Name: AuraBuff2 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mana Repetition Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Repetition Aura].RankName}
		/varset AuraBuff2Name  Mana Repetition
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mana Reciprocation Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Reciprocation Aura].RankName}
		/varset AuraBuff2Name Mana Reciprocation
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mana Reverberation Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Reverberation Aura].RankName}
		/varset AuraBuff2Name Mana Rev. Aura
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mana Repercussion Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Repercussion Aura].RankName}
		/varset AuraBuff2Name Mana Rep. Aura
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Mana Reiteration Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Reiteration Aura].RankName}
		/varset AuraBuff2Name Mana Recursion
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Mana Reiterate Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Reiterate Aura].RankName}
		/varset AuraBuff2Name Mana Reiterate
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Mana Resurgence Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mana Resurgence Aura].RankName}
		/varset AuraBuff2Name Mana Resurgence
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Mystifier's Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Mystifier's Aura].RankName}
		/varset AuraBuff2Name Mystifier's
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Entrancer's Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Entrancer's Aura].RankName}
		/varset AuraBuff2Name Entrancer's
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Illusionist's Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Illusionist's Aura].RankName}
		/varset AuraBuff2Name Illusionist's
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Beguiler's Aura].RankName}]}) {
		/varset AuraBuff2 ${Spell[Beguiler's Aura].RankName}
		/varset AuraBuff2Name Beguiler's
	}
|-Self HP Buff * Var Name: SelfHPBuff string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Shield of Scales].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of Scales].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Shield of the Pellarus].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Pellarus].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Shield of the Dauntless].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Dauntless].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Shield of Bronze].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of Bronze].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Shield of Dreams].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of Dreams].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Shield of the Void].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Void].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Spellbound Shield].RankName}]}) {
		/varset SelfHPBuff ${Spell[Spellbound Shield].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Sorcerous Shield].RankName}]}) {
		/varset SelfHPBuff ${Spell[Sorcerous Shield].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Mystic Shield].RankName}]}) {
		/varset SelfHPBuff ${Spell[Mystic Shield].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Shield of Maelin].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of Maelin].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Shield of the Arcane].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Arcane].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Shield of the Magi].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Magi].RankName}
	} else /if (${Me.Level}>=40 && ${Me.Book[${Spell[Arch Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Arch Shielding].RankName}
	} else /if (${Me.Level}>=31 && ${Me.Book[${Spell[Greater Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Greater Shielding].RankName}
	} else /if (${Me.Level}>=23 && ${Me.Book[${Spell[Major Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Major Shielding].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shielding].RankName}
	} else /if (${Me.Level}>=6 && ${Me.Book[${Spell[Lesser Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Lesser Shielding].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Minor Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Minor Shielding].RankName}
	}
|-Group Mana * Var Name: GroupMana string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Voice of Perspicacity].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Perspicacity].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Voice of Precognition].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Precognition].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Voice of Foresight].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Foresight].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Voice of Premeditation].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Premeditation].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Voice of Forethought].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Forethought].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Voice of Prescience].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Prescience].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Voice of Cognizance].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Cognizance].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Voice of Intuition].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Intuition].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Voice of Clairvoyance].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Clairvoyance].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Voice of Quellious].RankName}]}) {
		/varset GroupMana ${Spell[Voice of Quellious].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Tranquility].RankName}]}) {
		/varset GroupMana ${Spell[Tranquility].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Koadic's Endless Intellect].RankName}]}) {
		/varset GroupMana ${Spell[Koadic's Endless Intellect].RankName}
	} else /if (${Me.Level}>=56 && ${Me.Book[${Spell[Gift of Pure Thought].RankName}]}) {
		/varset GroupMana ${Spell[Gift of Pure Thought].RankName}
	} else /if (${Me.Level}>=42 && ${Me.Book[${Spell[Boon of the Clear Mind].RankName}]}) {
		/varset GroupMana ${Spell[Boon of the Clear Mind].RankName}
	}
|-Single Mana * Var Name: SingleMana string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Perspicacity].RankName}]}) {
		/varset SingleMana ${Spell[Perspicacity].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Precognition].RankName}]}) {
		/varset SingleMana ${Spell[Precognition].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Foresight].RankName}]}) {
		/varset SingleMana ${Spell[Foresight].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Premeditation].RankName}]}) {
		/varset SingleMana ${Spell[Premeditation].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Forethought].RankName}]}) {
		/varset SingleMana ${Spell[Forethought].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Prescience].RankName}]}) {
		/varset SingleMana ${Spell[Prescience].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Seer's Cognizance].RankName}]}) {
		/varset SingleMana ${Spell[Seer's Cognizance].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Seer's Intuition].RankName}]}) {
		/varset SingleMana ${Spell[Seer's Intuition].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Clairvoyance].RankName}]}) {
		/varset SingleMana ${Spell[Clairvoyance].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Gift of Brilliance].RankName}]}) {
		/varset SingleMana ${Spell[Gift of Brilliance].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Gift of Insight].RankName}]}) {
		/varset SingleMana ${Spell[Gift of Insight].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Clarity II].RankName}]}) {
		/varset SingleMana ${Spell[Clarity II].RankName}
	} else /if (${Me.Level}>=26 && ${Me.Book[${Spell[Clarity].RankName}]}) {
		/varset SingleMana ${Spell[Clarity].RankName}
	} else /if (${Me.Level}>=14 && ${Me.Book[${Spell[Breeze].RankName}]}) {
		/varset SingleMana ${Spell[Breeze].RankName}
	}
|-Group Haste * Var Name: GroupHaste string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Hastening of Milyex].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Milyex].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Hastening of Prokev].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Prokev].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Hastening of Sviir].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Sviir].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Hastening of Aransir].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Aransir].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Hastening of Novak].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Novak].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Hastening of Erradien].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Erradien].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Hastening of Ellowind].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Ellowind].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Hastening of Salik].RankName}]}) {
		/varset GroupHaste ${Spell[Hastening of Salik].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Vallon's Quickening].RankName}]}) {
		/varset GroupHaste ${Spell[Vallon's Quickening].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Speed of the Brood].RankName}]}) {
		/varset GroupHaste ${Spell[Speed of the Brood].RankName}
	}
|-Single Haste * Var Name: SingleHaste string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Speed of Milyex].RankName}]}) {
		/varset SingleHaste ${Spell[Speed of Milyex].RankName}
	}
|-Self Rune 1 * Var Name: SelfRune1 string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Transfixer's Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Transfixer's Rune].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Enticer's Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Enticer's Rune].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Mastermind's Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Mastermind's Rune].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Arcanaward's Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Arcanaward's Rune].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Spectral Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Spectral Rune].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Pearlescent Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Pearlescent Rune].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Opalescent Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Opalescent Rune].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Draconic Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Draconic Rune].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Ethereal Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Ethereal Rune].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Arcane Rune].RankName}]}) {
		/varset SelfRune1 ${Spell[Arcane Rune].RankName}
	}
|-Self Rune 2 * Var Name: SelfRune2 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Polyfluorescent Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polyfluorescent Rune].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Polyrefractive Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polyrefractive Rune].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Polyiridescent Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polyiridescent Rune].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Polyarcanic Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polyarcanic Rune].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Polyspectral Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polyspectral Rune].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Polychaotic Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polychaotic Rune].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Multichromatic Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Multichromatic Rune].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Polychromatic Rune].RankName}]}) {
		/varset SelfRune2 ${Spell[Polychromatic Rune].RankName}
	}
|-Single Rune * Var Name: SingleRune string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Rune of Skrizix].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Skrizix].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Rune of Lucem].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Lucem].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Rune of Xolok].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Xolok].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Rune of Tonmek].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Tonmek].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Rune of Novak].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Novak].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Rune of Yozan].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Yozan].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Rune of Erradien].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Erradien].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Rune of Ellowind].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Ellowind].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Rune of Salik].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Salik].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Rune of Zebuxoruk].RankName}]}) {
		/varset SingleRune ${Spell[Rune of Zebuxoruk].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Rune V].RankName}]}) {
		/varset SingleRune ${Spell[Rune V].RankName}
	} else /if (${Me.Level}>=40 && ${Me.Book[${Spell[Rune IV].RankName}]}) {
		/varset SingleRune ${Spell[Rune IV].RankName}
	} else /if (${Me.Level}>=33 && ${Me.Book[${Spell[Rune III].RankName}]}) {
		/varset SingleRune ${Spell[Rune III].RankName}
	} else /if (${Me.Level}>=22 && ${Me.Book[${Spell[Rune II].RankName}]}) {
		/varset SingleRune ${Spell[Rune II].RankName}
	} else /if (${Me.Level}>=13 && ${Me.Book[${Spell[Rune I].RankName}]}) {
		/varset SingleRune ${Spell[Rune I].RankName}
	}
|-Mez Buff * Var Name: MezBuff string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Ward of the Transfixer].RankName}]}) {
		/varset MezBuff ${Spell[Ward of the Transfixer].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Ward of the Enticer].RankName}]}) {
		/varset MezBuff ${Spell[Ward of the Enticer].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Ward of the Mastermind].RankName}]}) {
		/varset MezBuff ${Spell[Ward of the Mastermind].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Ward of Arctending].RankName}]}) {
		/varset MezBuff ${Spell[Ward of Arctending].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Ward of Bafflement].RankName}]}) {
		/varset MezBuff ${Spell[Ward of Bafflement].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Ward of Befuddlement].RankName}]}) {
		/varset MezBuff ${Spell[Ward of Befuddlement].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Ward of Mystifying].RankName}]}) {
		/varset MezBuff ${Spell[Ward of Mystifying].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Ward of Bewilderment].RankName}]}) {
		/varset MezBuff ${Spell[Ward of Bewilderment].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Ward of Bedazzlement].RankName}]}) {
		/varset MezBuff ${Spell[Ward of Bedazzlement].RankName}
	}
|-Proc Buff * Var Name: ProcBuff string outer
	/if (${Me.Level}>=103 && ${Me.Book[${Spell[Night's Endless Terror].RankName}]}) {
		/varset ProcBuff ${Spell[Night's Endless Terror].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Night's Dark Terror].RankName}]}) {
		/varset ProcBuff ${Spell[Night's Dark Terror].RankName}
	} else /if (${Me.Level}>=40 && ${Me.Book[${Spell[Boon of the Garou].RankName}]}) {
		/varset ProcBuff ${Spell[Boon of the Garou].RankName}
	}
|-Charm Spell * Var Name: CharmSpell1 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Transfixer's Command].RankName}]}) {
		/varset CharmSpell1 ${Spell[Transfixer's Command].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Spellbinding].RankName}]}) {
		/varset CharmSpell1 ${Spell[Spellbinding].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Enticer's Command].RankName}]}) {
		/varset CharmSpell1 ${Spell[Enticer's Command].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Enticer's Demand].RankName}]}) {
		/varset CharmSpell1 ${Spell[Enticer's Demand].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Captivation].RankName}]}) {
		/varset CharmSpell1 ${Spell[Captivation].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Impose].RankName}]}) {
		/varset CharmSpell1 ${Spell[Impose].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Temptation].RankName}]}) {
		/varset CharmSpell1 ${Spell[Temptation].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Enforce].RankName}]}) {
		/varset CharmSpell1 ${Spell[Enforce].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Compelling Edict].RankName}]}) {
		/varset CharmSpell1 ${Spell[Compelling Edict].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Subjugate].RankName}]}) {
		/varset CharmSpell1 ${Spell[Subjugate].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Deception].RankName}]}) {
		/varset CharmSpell1 ${Spell[Deception].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Dominate].RankName}]}) {
		/varset CharmSpell1 ${Spell[Dominate].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Seduction].RankName}]}) {
		/varset CharmSpell1 ${Spell[Seduction].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Haunting Whispers].RankName}]}) {
		/varset CharmSpell1 ${Spell[Haunting Whispers].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Cajole].RankName}]}) {
		/varset CharmSpell1 ${Spell[Cajole].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Dyn'leth's Whispers].RankName}]}) {
		/varset CharmSpell1 ${Spell[Dyn'leth's Whispers].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Coax].RankName}]}) {
		/varset CharmSpell1 ${Spell[Coax].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Ancient Voice of Muram].RankName}]}) {
		/varset CharmSpell1 ${Spell[Ancient Voice of Muram].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[True Name].RankName}]}) {
		/varset CharmSpell1 ${Spell[True Name].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Compel].RankName}]}) {
		/varset CharmSpell1 ${Spell[Compel].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Command of Druzzil].RankName}]}) {
		/varset CharmSpell1 ${Spell[Command of Druzzil].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Beckon].RankName}]}) {
		/varset CharmSpell1 ${Spell[Beckon].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Dictate].RankName}]}) {
		/varset CharmSpell1 ${Spell[Dictate].RankName}
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Boltran's Agacerie].RankName}]}) {
		/varset CharmSpell1 ${Spell[Boltran's Agacerie].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Ordinance].RankName}]}) {
		/varset CharmSpell1 ${Spell[Ordinance].RankName}
	} else /if (${Me.Level}>=46 && ${Me.Book[${Spell[Allure].RankName}]}) {
		/varset CharmSpell1 ${Spell[Allure].RankName}
	} else /if (${Me.Level}>=37 && ${Me.Book[${Spell[Cajoling Whispers].RankName}]}) {
		/varset CharmSpell1 ${Spell[Cajoling Whispers].RankName}
	} else /if (${Me.Level}>=23 && ${Me.Book[${Spell[Beguile].RankName}]}) {
		/varset CharmSpell1 ${Spell[Beguile].RankName}
	} else /if (${Me.Level}>=11 && ${Me.Book[${Spell[Charm].RankName}]}) {
		/varset CharmSpell1 ${Spell[Charm].RankName}
	}
|-Cripple Spell * Var Name: CrippleSpell1 string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Constraining Helix].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Constraining Helix].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Undermining Helix].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Undermining Helix].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Diminishing Helix].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Diminishing Helix].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Attenuating Helix].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Attenuating Helix].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Curtailing Helix].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Curtailing Helix].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Splintered Consciousness].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Splintered Consciousness].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Fragmented Consciousness].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Fragmented Consciousness].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Shattered Consciousness].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Shattered Consciousness].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Fractured Consciousness].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Fractured Consciousness].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Synapsis Spasm].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Synapsis Spasm].RankName}
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Cripple].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Cripple].RankName}
	} else /if (${Me.Level}>=40 && ${Me.Book[${Spell[Incapacitate].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Incapacitate].RankName}
	} else /if (${Me.Level}>=25 && ${Me.Book[${Spell[Listless Power].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Listless Power].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Disempower].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Disempower].RankName}
	} else /if (${Me.Level}>=4 && ${Me.Book[${Spell[Enfeeblement].RankName}]}) {
		/varset CrippleSpell1 ${Spell[Enfeeblement].RankName}
	}
|-Strip Buff Spell * Var Name: StripBuffSpell string outer
	/if (${Me.Level}>=100 && ${Me.AltAbilityReady[Eradicate Magic]}) {
		/varset StripBuffSpell Eradicate Magic
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Recant Magic].RankName}]}) {
		/varset StripBuffSpell ${Spell[Recant Magic].RankName}
	} else /if (${Me.Level}>=42 && ${Me.Book[${Spell[Pillage Enchantment].RankName}]}) {
		/varset StripBuffSpell ${Spell[Pillage Enchantment].RankName}
	} else /if (${Me.Level}>=28 && ${Me.Book[${Spell[Nullify Magic].RankName}]}) {
		/varset StripBuffSpell ${Spell[Nullify Magic].RankName}
	} else /if (${Me.Level}>=22 && ${Me.Book[${Spell[Strip Enchantment].RankName}]}) {
		/varset StripBuffSpell ${Spell[Strip Enchantment].RankName}
	} else /if (${Me.Level}>=7 && ${Me.Book[${Spell[Cancel Magic].RankName}]}) {
		/varset StripBuffSpell ${Spell[Cancel Magic].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Taper Enchantment].RankName}]}) {
		/varset StripBuffSpell ${Spell[Taper Enchantment].RankName}
	}
|-Pet Spell * Var Name: PetSpell string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Nureya's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Nureya's Animation].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Gordianus' Animation].RankName}]}) {
		/varset PetSpell ${Spell[Gordianus' Animation].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Xorlex's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Xorlex's Animation].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Seronvall's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Seronvall's Animation].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Novak's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Novak's Animation].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Yozan's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Yozan's Animation].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Erradien's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Erradien's Animation].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Ellowind's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Ellowind's Animation].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Salik's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Salik's Animation].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Aeldorb's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Aeldorb's Animation].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Zumaik's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Zumaik's Animation].RankName}
	} else /if (${Me.Level}>=48 && ${Me.Book[${Spell[Kintaz's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Kintaz's Animation].RankName}
	} else /if (${Me.Level}>=41 && ${Me.Book[${Spell[Yegoreff's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Yegoreff's Animation].RankName}
	} else /if (${Me.Level}>=37 && ${Me.Book[${Spell[Aanya's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Aanya's Animation].RankName}
	} else /if (${Me.Level}>=31 && ${Me.Book[${Spell[Boltran's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Boltran's Animation].RankName}
	} else /if (${Me.Level}>=29 && ${Me.Book[${Spell[Uleen's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Uleen's Animation].RankName}
	} else /if (${Me.Level}>=22 && ${Me.Book[${Spell[Sagar's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Sagar's Animation].RankName}
	} else /if (${Me.Level}>=17 && ${Me.Book[${Spell[Sisna's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Sisna's Animation].RankName}
	} else /if (${Me.Level}>=14 && ${Me.Book[${Spell[Shalee's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Shalee's Animation].RankName}
	} else /if (${Me.Level}>=9 && ${Me.Book[${Spell[Kilan's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Kilan's Animation].RankName}
	} else /if (${Me.Level}>=7 && ${Me.Book[${Spell[Mircyl's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Mircyl's Animation].RankName}
	} else /if (${Me.Level}>=2 && ${Me.Book[${Spell[Juli's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Juli's Animation].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Pendril's Animation].RankName}]}) {
		/varset PetSpell ${Spell[Pendril's Animation].RankName}
	}
|-Pet Buff Spell * Var Name: PetBuffSpell string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Infused Minion].RankName}]}) {
		/varset PetBuffSpell ${Spell[Infused Minion].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Empowered Minion].RankName}]}) {
		/varset PetBuffSpell ${Spell[Empowered Minion].RankName}
	} else {
		/varset PetBuffSpell ${SingleHaste}
	}
|-Dicho Spell * Var Name: DichoSpell string outer
/if (${Me.Level}>=106 && ${Me.Book[${Spell[Dissident Reinforcement].RankName}]}) {
		/varset DichoSpell ${Spell[Dissident Reinforcement].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Dichotomic Reinforcement].RankName}]}) {
		/varset DichoSpell ${Spell[Dichotomic Reinforcement].RankName}
	}
|-Group Rune * Var Name: GroupRune string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Tenebrous Rune].RankName}]}) {
		/varset GroupRune ${Spell[Tenebrous Rune].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Darkened Rune].RankName}]}) {
		/varset GroupRune ${Spell[Darkened Rune].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Umbral Rune].RankName}]}) {
		/varset GroupRune ${Spell[Umbral Rune].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Shadowed Rune].RankName}]}) {
		/varset GroupRune ${Spell[Shadowed Rune].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Twilight Rune].RankName}]}) {
		/varset GroupRune ${Spell[Twilight Rune].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Rune of the Void].RankName}]}) {
		/varset GroupRune ${Spell[Rune of the Void].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Rune of the Deep].RankName}]}) {
		/varset GroupRune ${Spell[Rune of the Deep].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Rune of the Kedge].RankName}]}) {
		/varset GroupRune ${Spell[Rune of the Kedge].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Rune of Rikkukin].RankName}]}) {
		/varset GroupRune ${Spell[Rune of Rikkukin].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Rune of the Scale].RankName}]}) {
		/varset GroupRune ${Spell[Rune of the Scale].RankName}
	}
|-Aggro Rune * Var Name: AggroRune string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Dreadful Rune].RankName}]}) {
		/varset AggroRune ${Spell[Dreadful Rune].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Frightening Rune].RankName}]}) {
		/varset AggroRune ${Spell[Frightening Rune].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Terrifying Rune].RankName}]}) {
		/varset AggroRune ${Spell[Terrifying Rune].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Horrifying Rune].RankName}]}) {
		/varset AggroRune ${Spell[Horrifying Rune].RankName}
	}
|-Aggro Buff * Var Name: AggroBuff string outer
	/if (${Me.Level}>=56 && ${Me.Book[${Spell[Horrifying Visage].RankName}]}) {
		/varset AggroBuff ${Spell[Horrifying Visage].RankName}
	} else /if (${Me.Level}>=26 && ${Me.Book[${Spell[Haunting Visage].RankName}]}) {
		/varset AggroBuff ${Spell[Haunting Visage].RankName}
	}
|-Single Spell Shield * Var Name: SingleSpellShield string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Aegis of Nureya].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Nureya].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Aegis of Gordianus].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Gordianus].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Aegis of Xorbb].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Xorbb].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Aegis of Soliadal].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Soliadal].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Aegis of Zykean].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Zykean].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Aegis of Xadrith].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Xadrith].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Aegis of Qandieal].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Qandieal].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Aegis of Alendar].RankName}]}) {
		/varset SingleSpellShield ${Spell[Aegis of Alendar].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Wall of Alendar].RankName}]}) {
		/varset SingleSpellShield ${Spell[Wall of Alendar].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Bulwark of Alendar].RankName}]}) {
		/varset SingleSpellShield ${Spell[Bulwark of Alendar].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Protection of Alendar].RankName}]}) {
		/varset SingleSpellShield ${Spell[Protection of Alendar].RankName}
	} else /if (${Me.Level}>=44 && ${Me.Book[${Spell[Guard of Alendar].RankName}]}) {
		/varset SingleSpellShield ${Spell[Guard of Alendar].RankName}
	} else /if (${Me.Level}>=29 && ${Me.Book[${Spell[Ward of Alendar].RankName}]}) {
		/varset SingleSpellShield ${Spell[Ward of Alendar].RankName}
	}
|-Group Spell Shield * Var Name: GroupSpellShield string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Legion of Skrizix].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Skrizix].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Legion of Lucem].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Lucem].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Legion of Xolok].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Xolok].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Legion of Tonmek].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Tonmek].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Legion of Zykean].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Zykean].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Legion of Xadrith].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Xadrith].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Legion of Qandieal].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Qandieal].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Legion of Alendar].RankName}]}) {
		/varset GroupSpellShield ${Spell[Legion of Alendar].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Circle of Alendar].RankName}]}) {
		/varset GroupSpellShield ${Spell[Circle of Alendar].RankName}
	}
|-Sing DoT Shield * Var Name: SingleDoTShield string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Aegis of Milyex].RankName}]}) {
		/varset SingleDoTShield ${Spell[Aegis of Milyex].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Aegis of the Indagator].RankName}]}) {
		/varset SingleDoTShield ${Spell[Aegis of the Indagator].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Aegis of the Keeper].RankName}]}) {
		/varset SingleDoTShield ${Spell[Aegis of the Keeper].RankName}
	}
|-Group DoT Shield * Var Name: GroupDoTShield string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Legion of Milyex].RankName}]}) {
		/varset GroupDoTShield ${Spell[Legion of Milyex].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Legion of the Indagator].RankName}]}) {
		/varset GroupDoTShield ${Spell[Legion of the Indagator].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Legion of the Keeper].RankName}]}) {
		/varset GroupDoTShield ${Spell[Legion of the Keeper].RankName}
	}
|-Group Auspice - Dmg Shield Reduction + DoT Shield * Var Name: GroupAuspiceBuff string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Transfixer's Auspice].RankName}]}) {
		/varset GroupAuspiceBuff ${Spell[Transfixer's Auspice].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Enticer's Auspice].RankName}]}) {
		/varset GroupAuspiceBuff ${Spell[Enticer's Auspice].RankName}
	}
|-Sing Melee Shield * Var Name: SingleMeleeShield string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Tenebrous Auspice].RankName}]}) {
		/varset SingleMeleeShield ${Spell[Tenebrous Auspice].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Darkened Auspice].RankName}]}) {
		/varset SingleMeleeShield ${Spell[Darkened Auspice].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Umbral Auspice].RankName}]}) {
		/varset SingleMeleeShield ${Spell[Umbral Auspice].RankName}
	}
|-Self Guard Shield * Var Name: SelfGuardShield string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Shield of Order].RankName}]}) {
		/varset SelfGuardShield ${Spell[Shield of Order].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Shield of Consequence].RankName}]}) {
		/varset SelfGuardShield ${Spell[Shield of Consequence].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Shield of Fate].RankName}]}) {
		/varset SelfGuardShield ${Spell[Shield of Fate].RankName}
	}
|-PBAE Stun Spell * Var Name: PBAEStunSpell string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Color Congruence].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Congruence].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Color Concourse].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Concourse].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Color Confluence].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Confluence].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Color Convergence].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Convergence].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Color Clash].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Clash].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Color Conflux].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Conflux].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Color Cataclysm].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Cataclysm].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Color Collapse].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Collapse].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Color Snap].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Snap].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Color Cloud].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Cloud].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Color Slant].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Slant].RankName}
	} else /if (${Me.Level}>=43 && ${Me.Book[${Spell[Color Skew].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Skew].RankName}
	} else /if (${Me.Level}>=20 && ${Me.Book[${Spell[Color Shift].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Shift].RankName}
	} else /if (${Me.Level}>=3 && ${Me.Book[${Spell[Color Flux].RankName}]}) {
		/varset PBAEStunSpell ${Spell[Color Flux].RankName}
	}
|-Target AE Stun * Var Name: TargetAEStun string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Remote Color Congruence].RankName}]}) {
		/varset TargetAEStun ${Spell[Remote Color Congruence].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Remote Color Concourse].RankName}]}) {
		/varset TargetAEStun ${Spell[Remote Color Concourse].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Remote Color Confluence].RankName}]}) {
		/varset TargetAEStun ${Spell[Remote Color Confluence].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Remote Color Convergence].RankName}]}) {
		/varset TargetAEStun ${Spell[Remote Color Convergence].RankName}
	}
|-Single Stun Spell * Var Name: SingleStunSpell1 string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Dizzying Wheel].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Dizzying Wheel].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Dizzying Storm].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Dizzying Storm].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Dizzying Squall].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Dizzying Squall].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Dizzying Gyre].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Dizzying Gyre].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Dizzying Helix].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Dizzying Helix].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[The Downward Spiral].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[The Downward Spiral].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Whirling into the Hollow].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Whirling into the Hollow].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Spinning into the Void].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Spinning into the Void].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Largarn's Lamentation].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Largarn's Lamentation].RankName}
	} else /if (${Me.Level}>=28 && ${Me.Book[${Spell[Dyn's Dizzying Draught].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Dyn's Dizzying Draught].RankName}
	} else /if (${Me.Level}>=9 && ${Me.Book[${Spell[Whirl till you hurl].RankName}]}) {
		/varset SingleStunSpell1 ${Spell[Whirl till you hurl].RankName}
	}
|-Mana Drain DoT * Var Name: ManaDrainSpell1 string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Tears of Skrizix].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Skrizix].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Tears of Visius].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Visius].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Tears of Syrkl].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Syrkl].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Tears of Wreliard].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Wreliard].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Tears of Zykean].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Zykean].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Tears of Xadrith].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Xadrith].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Tears of Qandieal].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Tears of Qandieal].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Torment of Scio].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Torment of Scio].RankName}
	} else /if (${Me.Level}>=56 && ${Me.Book[${Spell[Torment of Argli].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Torment of Argli].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Scryer's Trespass].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Scryer's Trespass].RankName}
	} else /if (${Me.Level}>=38 && ${Me.Book[${Spell[Wandering Mind].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Wandering Mind].RankName}
	} else /if (${Me.Level}>=30 && ${Me.Book[${Spell[Mana Sieve].RankName}]}) {
		/varset ManaDrainSpell1 ${Spell[Mana Sieve].RankName}
	}
|-AE Mez Fast Cast * Var Name: MezAESpellFast string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Perplexing Glance].RankName}]}) {
		/varset MezAESpellFast ${Spell[Perplexing Glance].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Slackening Glance].RankName}]}) {
		/varset MezAESpellFast ${Spell[Slackening Glance].RankName}
	}
|-PBAE Mez Spell * Var Name: MezPBAESpell string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Perplex].RankName}]}) {
		/varset MezPBAESpell ${Spell[Perplex].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Bafflement].RankName}]}) {
		/varset MezPBAESpell ${Spell[Bafflement].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Disorientation].RankName}]}) {
		/varset MezPBAESpell ${Spell[Disorientation].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Confusion].RankName}]}) {
		/varset MezPBAESpell ${Spell[Confusion].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Serenity].RankName}]}) {
		/varset MezPBAESpell ${Spell[Serenity].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Docility].RankName}]}) {
		/varset MezPBAESpell ${Spell[Docility].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Visions of Kirathas].RankName}]}) {
		/varset MezPBAESpell ${Spell[Visions of Kirathas].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Dreams of Veldyn].RankName}]}) {
		/varset MezPBAESpell ${Spell[Dreams of Veldyn].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Circle of Dreams].RankName}]}) {
		/varset MezPBAESpell ${Spell[Circle of Dreams].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Word of Morell].RankName}]}) {
		/varset MezPBAESpell ${Spell[Word of Morell].RankName}
	} else /if (${Me.Level}>=30 && ${Me.Book[${Spell[Entrancing Lights].RankName}]}) {
		/varset MezPBAESpell ${Spell[Entrancing Lights].RankName}
	}
|-Single Mez Fast Cast * Var Name: MezSpellFast string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Deluding Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Deluding Flash].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Bewildering Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Bewildering Flash].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Confounding Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Confounding Flash].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Misleading Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Misleading Flash].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Baffling Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Baffling Flash].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Befuddling Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Befuddling Flash].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Mystifying Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Mystifying Flash].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Perplexing Flash].RankName}]}) {
		/varset MezSpellFast ${Spell[Perplexing Flash].RankName}
	}
|-Mem Blur Single * Var Name: BlurSpell string outer
	/if (${Me.Level}>=55 && ${Me.Book[${Spell[Memory Flux].RankName}]}) {
		/varset BlurSpell ${Spell[Memory Flux].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Reoccurring Amnesia].RankName}]}) {
		/varset BlurSpell ${Spell[Reoccurring Amnesia].RankName}
	} else /if (${Me.Level}>=10 && ${Me.Book[${Spell[Memory Blur].RankName}]}) {
		/varset BlurSpell ${Spell[Memory Blur].RankName}
	}
|-Mem Blur AoE * Var Name: AEBlurSpell string outer
	/if (${Me.Level}>=46 && ${Me.Book[${Spell[Blanket of Forgetfulness].RankName}]}) {
		/varset AEBlurSpell ${Spell[Blanket of Forgetfulness].RankName}
	} else /if (${Me.Level}>=36 && ${Me.Book[${Spell[Mind Wipe].RankName}]}) {
		/varset AEBlurSpell ${Spell[Mind Wipe].RankName}
	}
|-Calm Spell * Var Name: CalmSpell string outer
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Mollified Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Mollified Mind].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Pacified Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Pacified Mind].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Quiescent Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Quiescent Mind].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Halcyon Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Halcyon Mind].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Bucolic Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Bucolic Mind].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Hushed Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Hushed Mind].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Silent Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Silent Mind].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Quiet Mind].RankName}]}) {
		/varset CalmSpell ${Spell[Quiet Mind].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Placate].RankName}]}) {
		/varset CalmSpell ${Spell[Placate].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Pacification].RankName}]}) {
		/varset CalmSpell ${Spell[Pacification].RankName}
	} else /if (${Me.Level}>=35 && ${Me.Book[${Spell[Pacify].RankName}]}) {
		/varset CalmSpell ${Spell[Pacify].RankName}
	} else /if (${Me.Level}>=18 && ${Me.Book[${Spell[Calm].RankName}]}) {
		/varset CalmSpell ${Spell[Calm].RankName}
	} else /if (${Me.Level}>=6 && ${Me.Book[${Spell[Soothe].RankName}]}) {
		/varset CalmSpell ${Spell[Soothe].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Lull].RankName}]}) {
		/varset CalmSpell ${Spell[Lull].RankName}
	}
|-Fear Spell * Var Name: FearSpell string outer
	/if (${Me.Level}>=67 && ${Me.Book[${Spell[Anxiety Attack].RankName}]}) {
		/varset FearSpell ${Spell[Anxiety Attack].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Jitterskin].RankName}]}) {
		/varset FearSpell ${Spell[Jitterskin].RankName}
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[Phobia].RankName}]}) {
		/varset FearSpell ${Spell[Phobia].RankName}
	} else /if (${Me.Level}>=56 && ${Me.Book[${Spell[Trepidation].RankName}]}) {
		/varset FearSpell ${Spell[Trepidation].RankName}
	} else /if (${Me.Level}>=35 && ${Me.Book[${Spell[Invoke Fear].RankName}]}) {
		/varset FearSpell ${Spell[Invoke Fear].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Chase the Moon].RankName}]}) {
		/varset FearSpell ${Spell[Chase the Moon].RankName}
	} else /if (${Me.Level}>=3 && ${Me.Book[${Spell[Fear].RankName}]}) {
		/varset FearSpell ${Spell[Fear].RankName}
	}
|-Root Spell * Var Name: RootSpell string outer
	/if (${Me.Level}>=61 && ${Me.Book[${Spell[Greater Fetter].RankName}]}) {
		/varset RootSpell ${Spell[Greater Fetter].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Fetter].RankName}]}) {
		/varset RootSpell ${Spell[Fetter].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Paralyzing Earth].RankName}]}) {
		/varset RootSpell ${Spell[Paralyzing Earth].RankName}
	} else /if (${Me.Level}>=39 && ${Me.Book[${Spell[Immobilize].RankName}]}) {
		/varset RootSpell ${Spell[Immobilize].RankName}
	} else /if (${Me.Level}>=25 && ${Me.Book[${Spell[Instill].RankName}]}) {
		/varset RootSpell ${Spell[Instill].RankName}
	} else /if (${Me.Level}>=6 && ${Me.Book[${Spell[Root].RankName}]}) {
		/varset RootSpell ${Spell[Root].RankName}
	}
/return 
|----------------------------------------------------------------------------
|- SUB: Bind Set Var Int resets various interger settings from ini file
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
				/if (${UseCharmPet}) /varset UseCharmPet 0
			} else {
				/echo \aw Resetting UsePet to \ar OFF
				/varset UsePet 0
			}
  |--Mez
		} else /if (${IName.Equal[MezOn]}) {
			/if (!${MezOn}) {
				/echo \aw Setting MezOn to \ag ON
				/varset MezOn 1
|-				/call CreateTimersMez
			} else {
				/echo \aw Resetting MezOn to \ar OFF
				/varset MezOn 0
|-				/call DeleteTimersMez
			}
  |--DPS
		} else /if (${IName.Equal[DoDPS]}) {
			/if (!${DoDPS}) {
				/echo \aw Setting DoDPS to \ag ON
				/varset DoDPS 1
			} else {
				/echo \aw Resetting DoDPS to \ar OFF
				/varset DoDPS 0
			}
  |--DoTs
		} else /if (${IName.Equal[UseDoTs]}) {
			/if (!${UseDoTs}) {
				/echo \aw Setting UseDoTs to \ag ON
				/varset UseDoTs 1
				/call LoadSpellBar
			} else {
				/echo \aw Resetting UseDoTs to \ar OFF
				/varset UseDoTs 0
				/call LoadSpellBar
			}
  |--Tash
		} else /if (${IName.Equal[DoTash]}) {
			/if (!${DoTash}) {
				/echo \aw Setting DoTash to \ag ON
				/varset DoTash 1
			} else {
				/echo \aw Resetting DoTash to \ar OFF
				/varset DoTash 0
			}
  |--Slow
		} else /if (${IName.Equal[DoSlow]}) {
			/if (!${DoSlow}) {
				/echo \aw Setting DoSlow to \ag ON
				/varset DoSlow 1
			} else {
				/echo \aw Resetting DoSlow to \ar OFF
				/varset DoSlow 0
			}
  |--Strip Buffs
		} else /if (${IName.Equal[StripBuffs]}) {
			/if (!${StripBuffs}) {
				/echo \aw Setting StripBuffs to \ag ON
				/varset StripBuffs 1
			} else {
				/echo \aw Resetting StripBuffs to \ar OFF
				/varset StripBuffs 0
			}
  |--Mez Announce
		} else /if (${IName.Equal[MezAnnounce]}) {
			/if (!${MezAnnounce}) {
				/echo \aw Setting MezAnnounce to \ag ON
				/varset MezAnnounce 1
			} else {
				/echo \aw Resetting MezAnnounce to \ar OFF
				/varset MezAnnounce 0
			}
  |- Cripple
		} else /if (${IName.Equal[DoCripple]}) {
			/if (!${DoCripple}) {
				/echo \aw Setting DoCripple to \ag ON
				/varset DoCripple 1
			} else {
				/echo \aw Resetting DoCripple to \ar OFF
				/varset DoCripple 0
			}
  |- DoBlurr
		} else /if (${IName.Equal[DoBlurr]}) {
			/if (!${DoBlurr}) {
				/echo \aw Setting DoBlurr to \ag ON
				/varset DoBlurr 1
			} else {
				/echo \aw Resetting DoBlurr to \ar OFF
				/varset DoBlurr 0
			}
  |- 
		} else /if (${IName.Equal[CharmPreStun]}) {
			/if (!${CharmPreStun}) {
				/echo \aw Setting CharmPreStun to \ag ON
				/varset CharmPreStun 1
			} else {
				/echo \aw Resetting CharmPreStun to \ar OFF
				/varset CharmPreStun 0
			}
  |-
		} else /if (${IName.Equal[CharmPreTash]}) {
			/if (!${CharmPreTash}) {
				/echo \aw Setting CharmPreTash to \ag ON
				/varset CharmPreTash 1
			} else {
				/echo \aw Resetting CharmPreTash to \ar OFF
				/varset CharmPreTash 0
			}
  |- Use Charm UseCharmPet
		} else /if (${IName.Equal[UseCharmPet]}) {
			/if (!${UseCharmPet}) {
				/echo \aw Setting UseCharmPet to \ag ON
				/varset UseCharmPet 1
				/call LoadSpellBar
				/if (${CharmMaxLvl}==0 || ${CharmMaxLvl}>${Spell[${CharmSpell1}].MaxLevel}) {
					/varset CharmMaxLvl ${Spell[${CharmSpell1}].MaxLevel}
				}
				/if (${Me.Pet.ID}) /pet get lost
				/if (${UsePet}) /varset UsePet 0
			} else {
				/echo \aw Resetting UseCharmPet to \ar OFF
				/varset UseCharmPet 0
				/call LoadSpellBar
			}
		} else /if (${IName.Equal[UseDicho]}) {
			/if (!${UseDicho}) {
				/echo \aw Setting UseDicho to \ag ON
				/varset UseDicho 1
				/call LoadSpellBar
			} else {
				/echo \aw Resetting UseDicho to \ar OFF
				/varset UseDicho 0
				/call LoadSpellBar
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
		} else /if (${IName.Equal[DoNDTBuff]}) {
			/if (!${DoNDTBuff}) {
				/echo \aw Setting DoNDTBuff to \ag ON
				/varset DoNDTBuff 1
			} else {
				/echo \aw Resetting DoNDTBuff to \ar OFF
				/varset DoNDTBuff 0
			}
		}
 |-Set's
	} else /if (${ISection.Equal[Set]}) {
  |--MezStartCount
		/if (${IName.Equal[MezStartCount]}) {
			/if (${IVar}>=2 && ${IVar}<=100) {
				/varset MezStartCount ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw - Set between 2-100 mobs
			}
  |--MezAECount
		} else /if (${IName.Equal[MezAECount]}) {
			/if (${IVar}>=3 && ${IVar}<=100) {
				/varset MezAECount ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw - Set between 3-100 mobs
			}
  |--MaxMezCount
		} else /if (${IName.Equal[MaxMezCount]}) {
			/if (${IVar}>=3 && ${IVar}<=50) {
				/varset MaxMezCount ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw - Set between 3-50 mobs
			}
  |--MezRadius
		} else /if (${IName.Equal[MezRadius]}) {
			/if (${IVar}>=20 && ${IVar}<=150) {
				/varset MezRadius ${IVar}
				/varset MezWatchRadius 0
				/varcalc MezWatchRadius ${MezRadius}*2
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw - Set between 20-150 units
			}
  |--MezMinLevel
		} else /if (${IName.Equal[MezMinLevel]}) {
			/if (${IVar}>=1 && ${IVar}<=200 && ${IVar}<${MezMaxLevel}) {
				/varset MezMinLevel ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else /if (${IVar}>${MezMaxLevel}) {
				/beep
				/echo \ag ${IName} \aw can NOT be set higher than \ag MezMaxLevel=${MezMaxLevel}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw - Set between 1-200
			}
  |--MezMaxLevel
		} else /if (${IName.Equal[MezMaxLevel]}) {
			/if (${IVar}>=2 && ${IVar}<=201 && ${IVar}>${MezMinLevel}) {
				/varset MezMaxLevel ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}	
			} else /if (${IVar}<${MezMinLevel}) {
				/beep
				/echo \ag ${IName} \aw can NOT be set lower than \ag MezMinLevel=${MezMinLevel}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw - Set between 2-201
			}
  |--MezStopHPs
		} else /if (${IName.Equal[MezStopHPs]}) {
			/if (${IVar}>=1 && ${IVar}<=99) {
				/varset MezStopHPs ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw HP%- Set between 1-99
			}
  |--
		} else /if (${IName.Equal[BlurrAggroPct]}) {
			/if (${IVar}>=1 && ${IVar}<=99) {
				/varset BlurrAggroPct ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw Aggro%- Set between 1-99
			}
		} else /if (${IName.Equal[AutoDebuffAt]}) {
			/if (${IVar}>=1 && ${IVar}<=99) {
				/varset AutoDebuffAt ${IVar}
				/echo \aw ${IName} set to \ag ${IVar}
			} else {
				/beep
				/echo \ar Invalid \ag ${IName} \aw%- Set between 1-99
			}
		}
	}
/return
|----------------------------------------------------------------------------
|-SUB: BIND  - SingleBanish
|----------------------------------------------------------------------------
Sub Bind_SingleBanish(string BanishID)
	/target id ${BanishID}
	/delay 10 ${Target.ID}==${BanishID}
	/if (!${Target.LineOfSight}) {
		/docommand /dgt I Can Not See the Target
	} else /if (${Me.AltAbilityReady[Beguiler's Directed Banishment]} && ${BanishID}) {
		/docommand /dgt \ar BANISHING \ag -> \ay ${Spawn[${BanishID}].CleanName} \ag <- \ar ID:${BanishID} \ax
		/face fast
		/delay 5
		/casting "Beguiler's Directed Banishment" alt -targetid|${BanishID}
        /delay 10
	} else {
		/docommand /dgt \ar COOL DOWN \ag >> \aw Beguiler's Directed Banishment \ag << 
	}
	/target clear
/return
|----------------------------------------------------------------------------
|-SUB: BIND  - 
|----------------------------------------------------------------------------
Sub Bind_AEBanish(string AEBanishID)
	/target id ${AEBanishID}
	/delay 10 ${Target.ID}==${AEBanishID}
	/if (!${Target.LineOfSight}) {
		/docommand /dgt I Can Not See the Target
	} else /if (${Me.AltAbilityReady[Beguiler's Banishment]} && ${AEBanishID}) {
		/docommand /dgt \ar AE Banishing \ag -> \ay ${Spawn[${AEBanishID}].CleanName} \ag <- \ar ID:${AEBanishID} \ax
		/face fast
		/delay 5
		/casting "Beguiler's Banishment" alt -targetid|${AEBanishID}
        /delay 10
	} else {
		/docommand /dgt \ar COOL DOWN \ag >> \aw Beguiler's Banishment \ag << 
	}
	/target clear
/return
|----------------------------------------------------------------------------
|- SUB: BIND CmdList - 
|----------------------------------------------------------------------------
Sub Bind_CmdList
/call CommonHelp
/echo \ag===${MacroName} Commands=== 
/echo \ag/autodebuffat\aw - HP % to start debuffing at
/echo \ag/blurpct\aw - Aggro % to use blur spell 
/echo \ag/charmstun\aw - toggles use of stun before charming mob
/echo \ag/charmtash\aw - toggles use of tash before charming mob
/echo \ag/maxmezcount\aw - Maximum # of mobs to CC ( Default is 13 )
/echo \ag/mezaecount\aw - Sets # of mobs needed on aggro and in range to AE Mez ( Default 3 )
/echo \ag/mezmaxlevel\aw - Maximum Level a mob must be to Mez - Above this lvl are ignored
/echo \ag/mezminlevel\aw - Minimum Level a mob must be to Mez - Below this lvl are ignored
/echo \ag/mezradius\aw - Radius for mobs to be in to start Mezing, An area twice this size is monitored for aggro mobs
/echo \ag/mezstartcount\aw - Sets # of mobs needed on aggro to start mezzing at ( Default 2 )
/echo \ag/mezstophp\aw - Mob HP% to stop trying to mez
/echo \ag/tglblur\aw - Toggle use of memblur spell
/echo \ag/tglcharm\aw - Toggles use of Charm
/echo \ag/tglcrip\aw - Toggle use of Cripple spell
/echo \ag/tgldicho\aw - Toggle use of Dicho spell
/echo \ag/tgldots\aw - Turns use of DoT spells On/Off
/echo \ag/tgldps\aw - Turns ALL DPS On/Off
/echo \ag/tglmez\aw - Turns Mez On/Off
/echo \ag/tglmezmsg\aw - Turns Target Mez Messages On/Off
/echo \ag/tglndt\aw - Turns NDT (Melee proc) Buffing On/Off
/echo \ag/tglpet\aw - Pet toggle...cause sometimes they arent allowed
/echo \ag/tglslow\aw - Turns Slow Debuff On/Off
/echo \ag/tglstrip\aw - Turns Enemy Buff stripping On/Off
/echo \ag/tgltash\aw - Turns Tash Debuff On/Off
/return 