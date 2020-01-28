|- ihcenchutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub enc_setup
|-Create Alias
|-Declare AA and Spell variables
  |-Buffs
	/declare Aura1					string outer NULL
	/declare Aura2					string outer NULL
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
	/declare Drown				string 	outer	"NULL"
	/declare DoTSpell2				string 	outer	"NULL"
	/declare DoTSpell3				string 	outer	"NULL"
	/declare DPSRecastTimer			timer 	outer	0
	/declare FastNukePct 			int 	outer	90
	/declare MindNukeMain				string 	outer	"NULL"
	/declare MindNukeSub				string 	outer	"NULL"
	/declare Chromatic				string 	outer	"NULL"
	/declare NukeSpell4				string 	outer	"NULL"
  |-Pet
	/declare PetSpell				string	outer	"NULL"
	/declare PetBuffSpell			string	outer	"NULL"
	/declare PetAssistTimer			timer 	outer	0
  |- Mez
	/declare LastMobCount           int		outer	0
	/declare MezAEClosest           int		outer	0
	/declare MezAEAA				string	outer	"NULL"
	/declare AEMezSpell				string	outer	"NULL"
	/declare AEMezSpellFast			string	outer	"NULL"
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
	/declare HarvestSpell1 			string 	outer	"NULL"
	/declare UnityRune 				string 	outer	 NULL
|-Config Options	

	/declare ChestItemName		string outer "${Me.Inventory[17].Name}"
	|-Set AA DurationMod for mez timer from Spell Casting Reinforcement AA
	/declare spellmisc 				int outer 8
	/declare spellgem				int outer 1	
	/declare CastResult             string outer
	/declare miscspellremem			string outer NULL
	/declare spellrememtimer		timer outer 0
	/declare groupbufftimer		timer outer 0
	/declare DeBuffTimer		timer outer 0
|- Below Code is only needed for using ihcxtenchmez.inc
|-	/declare MezCount[13]           			int         outer 	0
|-	/declare MezArray[50,3]			            string      outer       NULL
|-	/declare DebugMez							int			outer	0
|-	/declare DEBUGALL							int 		outer	0

|-	/if (${MezOn}) /call CreateTimersMez
/return
|* ------------------------------------------------------------------------------------------
| SUB: ${Me.Class.ShortName.Lower}_load_spellbar
|------------------------------------------------------------------------------------------ *|
Sub enc_load_spellbar

	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar
	/call LoadSpellGem "${MezSpell}" 1
	/call LoadSpellGem "${AEMezSpell}" 2
	/call LoadSpellGem "${TashSpell}" 3
	/call LoadSpellGem "${SlowSpell}" 4
	/call LoadSpellGem "${Drown}" 5
	/call LoadSpellGem "${MindNukeSub}" 6
	/call LoadSpellGem "${MindNukeMain}" 7
	/call LoadSpellGem "${SingleStunSpell1}" 8
	
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) {
		/call LoadSpellGem "${SingleStunSpell1}" 5
		/if (${UseDicho} && ${Me.Level}>=101 && ${DichoSpell.NotEqual[null]}) {
			/call LoadSpellGem "${DichoSpell}" 6
		} else {
			/call LoadSpellGem "${PBAEStunSpell}" 6
		}
		/call LoadSpellGem "${MindNukeMain}" 7
		/call LoadSpellGem "${MindNukeSub}" 8
		/if (${UseCharmPet}) {
			/call LoadSpellGem "${CharmSpell1}" 11
		} else /if (${UseDoTs}) {
			/call LoadSpellGem "${DoTSpell3}" 11
		} else {
			/call LoadSpellGem "${MezPBAESpell}" 11
		}
		/if (${UseDoTs}) {
			/call LoadSpellGem "${Drown}" 9
			/call LoadSpellGem "${DoTSpell2}" 10
		} else {
			/call LoadSpellGem "${Chromatic}" 9
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
				/call LoadSpellGem "${Drown}" 9
				/call LoadSpellGem "${DoTSpell2}" 10
			} else {
				/call LoadSpellGem "${Chromatic}" 9
				/call LoadSpellGem "${NukeSpell4}" 10
			}
			/call LoadSpellGem "${MindNukeSub}" 8
		} else /if (${Me.Level}>=96) {
			/call LoadSpellGem "${StripBuffSpell}" 5
			/call LoadSpellGem "${MindNukeSub}" 8
			/call LoadSpellGem "${Drown}" 9
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${CharmSpell1}" 10
				/call LoadSpellGem "${SingleStunSpell1}" 6
			} else /if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell2}" 10
				/call LoadSpellGem "${DoTSpell3}" 6
			} else {
				/call LoadSpellGem "${Chromatic}" 10
				/call LoadSpellGem "${SingleStunSpell1}" 6
			}
		} else /if (${Me.Level}>=89) {
			/call LoadSpellGem "${StripBuffSpell}" 5
			/call LoadSpellGem "${MindNukeSub}" 8
			/call LoadSpellGem "${Drown}" 9
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${CharmSpell1}" 10
				/call LoadSpellGem "${SingleStunSpell1}" 6
			} else /if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell3}" 6
				/call LoadSpellGem "${DoTSpell2}" 10
			} else {
				/call LoadSpellGem "${SingleStunSpell1}" 6
				/call LoadSpellGem "${Chromatic}" 10
			}
		} else /if (${Me.Level}>=88) {
		|- Level 88 - Slow+Cripple in 1 spell
			/call LoadSpellGem "${StripBuffSpell}" 5
			/call LoadSpellGem "${SingleStunSpell1}" 6
			/call LoadSpellGem "${MindNukeSub}" 8
			/call LoadSpellGem "${Drown}" 9
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${CharmSpell1}" 10
			} else /if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell2}" 10
			} else {
				/call LoadSpellGem "${Chromatic}" 10
			}
		} else /if (${Me.Level}>=86) {
		|- Level 86 - AA slow becomes available 
			/call LoadSpellGem "${StripBuffSpell}" 5
			/call LoadSpellGem "${CrippleSpell1}" 6
			/call LoadSpellGem "${Drown}" 9
			/call LoadSpellGem "${MindNukeSub}" 8
			/if (${UseCharmPet}) {
				/call LoadSpellGem "${CharmSpell1}" 10
			} else /if (${UseDoTs}) {
				/call LoadSpellGem "${DoTSpell2}" 10
			} else {
				/call LoadSpellGem "${Chromatic}" 10
			}
		} else /if (${Me.Level}>=81) {
		|- Level 81 - AA Single Memblur becomes available? 
			/call LoadSpellGem "${StripBuffSpell}" 5
			/call LoadSpellGem "${Drown}" 9
			/call LoadSpellGem "${MindNukeSub}" 8
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
				/call LoadSpellGem "${MindNukeSub}" 8
			}
			/call LoadSpellGem "${Drown}" 9
			/call LoadSpellGem "${BlurSpell}" 10
		}
		/call LoadSpellGem "${MindNukeMain}" 7
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
		/call LoadSpellGem "${MindNukeMain}" 7
		/if (${UseDoTs}) {
			/call LoadSpellGem "${Drown}" 8
		} else {
			/call LoadSpellGem "${MindNukeSub}" 8
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
		/call LoadSpellGem "${MindNukeMain}" 7
		/if (${UseDoTs}) {
			/call LoadSpellGem "${Drown}" 8
		} else {
			/call LoadSpellGem "${MindNukeSub}" 8
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
			/call LoadSpellGem "${Drown}" 7
		} else {
			/call LoadSpellGem "${MindNukeMain}" 7
		}
		/call LoadSpellGem "${ProcBuff}" 8
		/call LoadSpellGem "${BlurSpell}" 9
		/varset spellmisc 9
		/varset miscspellremem ${BlurSpell}
	} 
	
	/delay 2s
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|* ------------------------------------------------------------------------------------------
| SUB: SetEncSpells
|------------------------------------------------------------------------------------------ *|
Sub enc_abilities
|-AE Mez AA * Var Name : MezAEAA string outer
	/if (${Me.Level}>=85 && ${Me.AltAbilityReady[Beam of Slumber]}) {
		/varset MezAEAA Beam of Slumber
	}
	/if (${Me.AltAbilityReady[Gather Mana]}) {
		/varset HarvestSpell1 Gather Mana
	}
|-Mez Spell * Var Name: MezSpell string	outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Chaotic Delusion].RankName}]}) {
		/varset MezSpell ${Spell[Chaotic Delusion].RankName}
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Delude].RankName}]}) {
		/varset MezSpell ${Spell[Delude].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Chaotic Bewildering].RankName}]}) {
		/varset MezSpell ${Spell[Chaotic Bewildering].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Bewilder].RankName}]}) {
		/varset MezSpell ${Spell[Bewilder].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Chaotic Confounding].RankName}]}) {
		/varset MezSpell ${Spell[Chaotic Confounding].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Confound].RankName}]}) {
		/varset MezSpell ${Spell[Confound].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Chaotic Confusion].RankName}]}) {
		/varset MezSpell ${Spell[Chaotic Confusion].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Mislead].RankName}]}) {
		/varset MezSpell ${Spell[Mislead].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Chaotic Baffling].RankName}]}) {
		/varset MezSpell ${Spell[Chaotic Baffling].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Baffle].RankName}]}) {
		/varset MezSpell ${Spell[Baffle].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Chaotic Befuddling].RankName}]}) {
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
|-AE Mez * Var Name: AEMezSpell	string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Perplexing Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Perplexing Wave].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Deadening Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Deadening Wave].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Slackening Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Slackening Wave].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Peaceful Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Peaceful Wave].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Serene Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Serene Wave].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Ensorcelling Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Ensorcelling Wave].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Quelling Wave].RankName}]}) {
		/varset AEMezSpell ${Spell[Quelling Wave].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Wake of Subdual].RankName}]}) {
		/varset AEMezSpell ${Spell[Wake of Subdual].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Wake of Felicity].RankName}]}) {
		/varset AEMezSpell ${Spell[Wake of Felicity].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Echoing Madness].RankName}]}) {
		/varset AEMezSpell ${Spell[Echoing Madness].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Bliss of the Nihil].RankName}]}) {
		/varset AEMezSpell ${Spell[Bliss of the Nihil].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Fascination].RankName}]}) {
		/varset AEMezSpell ${Spell[Fascination].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Mesmerization].RankName}]}) {
		/varset AEMezSpell ${Spell[Mesmerization].RankName}
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

|-AE Mez Fast Cast * Var Name: AEMezSpellFast string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Perplexing Glance].RankName}]}) {
		/varset AEMezSpellFast ${Spell[Perplexing Glance].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Slackening Glance].RankName}]}) {
		/varset AEMezSpellFast ${Spell[Slackening Glance].RankName}
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
|	/if (${Me.AltAbilityReady[${SlowSpell}]}) /varset SlowSpell ${SlowSpell}

|-Nuke 1 * Var Name: MindNukeMain string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mindslash].RankName}]}) {
		/varset MindNukeMain ${Spell[Mindslash].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mindsunder].RankName}]}) {
		/varset MindNukeMain ${Spell[Mindsunder].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mindcleave].RankName}]}) {
		/varset MindNukeMain ${Spell[Mindcleave].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mindscythe].RankName}]}) {
		/varset MindNukeMain ${Spell[Mindscythe].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Mindblade].RankName}]}) {
		/varset MindNukeMain ${Spell[Mindblade].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Spectral Assault].RankName}]}) {
		/varset MindNukeMain ${Spell[Spectral Assault].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Chromarcana].RankName}]}) {
		/varset MindNukeMain ${Spell[Chromarcana].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Chromatic Jab].RankName}]}) {
		/varset MindNukeMain ${Spell[Chromatic Jab].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Polychaotic Assault].RankName}]}) {
		/varset MindNukeMain ${Spell[Polychaotic Assault].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Multichromatic Assault].RankName}]}) {
		/varset MindNukeMain ${Spell[Multichromatic Assault].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Polychromatic Assault].RankName}]}) {
		/varset MindNukeMain ${Spell[Polychromatic Assault].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Ancient Neurosis].RankName}]}) {
		/varset MindNukeMain ${Spell[Ancient Neurosis].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Colored Chaos].RankName}]}) {
		/varset MindNukeMain ${Spell[Colored Chaos].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Psychosis].RankName}]}) {
		/varset MindNukeMain ${Spell[Psychosis].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Ancient Chaos Madness].RankName}]}) {
		/varset MindNukeMain ${Spell[Ancient Chaos Madness].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Madness of Ikkibi].RankName}]}) {
		/varset MindNukeMain ${Spell[Madness of Ikkibi].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Insanity].RankName}]}) {
		/varset MindNukeMain ${Spell[Insanity].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Ancient Chaotic Visions].RankName}]}) {
		/varset MindNukeMain ${Spell[Ancient Chaotic Visions].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Dementing Visions].RankName}]}) {
		/varset MindNukeMain ${Spell[Dementing Visions].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Dementia].RankName}]}) {
		/varset MindNukeMain ${Spell[Dementia].RankName}
	} else /if (${Me.Level}>=43 && ${Me.Book[${Spell[Discordant Mind].RankName}]}) {
		/varset MindNukeMain ${Spell[Discordant Mind].RankName}
	} else /if (${Me.Level}>=32 && ${Me.Book[${Spell[Anarchy].RankName}]}) {
		/varset MindNukeMain ${Spell[Anarchy].RankName}
	} else /if (${Me.Level}>=21 && ${Me.Book[${Spell[Chaos Flux].RankName}]}) {
		/varset MindNukeMain ${Spell[Chaos Flux].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Sanity Warp].RankName}]}) {
		/varset MindNukeMain ${Spell[Sanity Warp].RankName}
	} else /if (${Me.Level}>=7 && ${Me.Book[${Spell[Chaotic Feedback].RankName}]}) {
		/varset MindNukeMain ${Spell[Chaotic Feedback].RankName}
	}
|-Nuke 2 * Var Name: MindNukeSub string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mindsunder].RankName}]}) {
		/varset MindNukeSub ${Spell[Mindsunder].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mindcleave].RankName}]}) {
		/varset MindNukeSub ${Spell[Mindcleave].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mindscythe].RankName}]}) {
		/varset MindNukeSub ${Spell[Mindscythe].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mindblade].RankName}]}) {
		/varset MindNukeSub ${Spell[Mindblade].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Spectral Assault].RankName}]}) {
		/varset MindNukeSub ${Spell[Spectral Assault].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Chromarcana].RankName}]}) {
		/varset MindNukeSub ${Spell[Chromarcana].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Polychaotic Assault].RankName}]}) {
		/varset MindNukeSub ${Spell[Polychaotic Assault].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Multichromatic Assault].RankName}]}) {
		/varset MindNukeSub ${Spell[Multichromatic Assault].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Polychromatic Assault].RankName}]}) {
		/varset MindNukeSub ${Spell[Polychromatic Assault].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Ancient Neurosis].RankName}]}) {
		/varset MindNukeSub ${Spell[Ancient Neurosis].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Colored Chaos].RankName}]}) {
		/varset MindNukeSub ${Spell[Colored Chaos].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Psychosis].RankName}]}) {
		/varset MindNukeSub ${Spell[Psychosis].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Ancient Chaos Madness].RankName}]}) {
		/varset MindNukeSub ${Spell[Ancient Chaos Madness].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Madness of Ikkibi].RankName}]}) {
		/varset MindNukeSub ${Spell[Madness of Ikkibi].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Insanity].RankName}]}) {
		/varset MindNukeSub ${Spell[Insanity].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Ancient Chaotic Visions].RankName}]}) {
		/varset MindNukeSub ${Spell[Ancient Chaotic Visions].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Dementing Visions].RankName}]}) {
		/varset MindNukeSub ${Spell[Dementing Visions].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Dementia].RankName}]}) {
		/varset MindNukeSub ${Spell[Dementia].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Discordant Mind].RankName}]}) {
		/varset MindNukeSub ${Spell[Discordant Mind].RankName}
	} else /if (${Me.Level}>=43 && ${Me.Book[${Spell[Anarchy].RankName}]}) {
		/varset MindNukeSub ${Spell[Anarchy].RankName}
	} else /if (${Me.Level}>=32 && ${Me.Book[${Spell[Chaos Flux].RankName}]}) {
		/varset MindNukeSub ${Spell[Chaos Flux].RankName}
	} else /if (${Me.Level}>=21 && ${Me.Book[${Spell[Sanity Warp].RankName}]}) {
		/varset MindNukeSub ${Spell[Sanity Warp].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Chaotic Feedback].RankName}]}) {
		/varset MindNukeSub ${Spell[Chaotic Feedback].RankName}
	}
|-Nuke 3 - Fast * Var Name: Chromatic string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Chromatic Flicker].RankName}]}) {
		/varset Chromatic ${Spell[Chromatic Flicker].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Chromatic Blink].RankName}]}) {
		/varset Chromatic ${Spell[Chromatic Blink].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Chromatic Percussion].RankName}]}) {
		/varset Chromatic ${Spell[Chromatic Percussion].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Chromatic Flash].RankName}]}) {
		/varset Chromatic ${Spell[Chromatic Flash].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Chromatic Jab].RankName}]}) {
		/varset Chromatic ${Spell[Chromatic Jab].RankName}
	}
|-Nuke 4 - Fast * Var Name: NukeSpell4 string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Psychic Appropriation].RankName}]}) {
		/varset NukeSpell4 ${Spell[Psychic Appropriation].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Intellectual Appropriation].RankName}]}) {
		/varset NukeSpell4 ${Spell[Intellectual Appropriation].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Mental Appropriation].RankName}]}) {
		/varset NukeSpell4 ${Spell[Mental Appropriation].RankName}
	}
|-DoT 1 * Var Name: Drown string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Strangulate].RankName}]}) {
		/varset Drown ${Spell[Strangulate].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Drown].RankName}]}) {
		/varset Drown ${Spell[Drown].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Stifle].RankName}]}) {
		/varset Drown ${Spell[Stifle].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Suffocation].RankName}]}) {
		/varset Drown ${Spell[Suffocation].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Constrict].RankName}]}) {
		/varset Drown ${Spell[Constrict].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Smother].RankName}]}) {
		/varset Drown ${Spell[Smother].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Strangling Air].RankName}]}) {
		/varset Drown ${Spell[Strangling Air].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Thin Air].RankName}]}) {
		/varset Drown ${Spell[Thin Air].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Arcane Noose].RankName}]}) {
		/varset Drown ${Spell[Arcane Noose].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Strangle].RankName}]}) {
		/varset Drown ${Spell[Strangle].RankName}
	} else /if (${Me.Level}>=59 && ${Me.Book[${Spell[Asphyxiate].RankName}]}) {
		/varset Drown ${Spell[Asphyxiate].RankName}
	} else /if (${Me.Level}>=47 && ${Me.Book[${Spell[Gasping Embrace].RankName}]}) {
		/varset Drown ${Spell[Gasping Embrace].RankName}
	} else /if (${Me.Level}>=26 && ${Me.Book[${Spell[Suffocate].RankName}]}) {
		/varset Drown ${Spell[Suffocate].RankName}
	} else /if (${Me.Level}>=11 && ${Me.Book[${Spell[Choke].RankName}]}) {
		/varset Drown ${Spell[Choke].RankName}
	} else /if (${Me.Level}>=4 && ${Me.Book[${Spell[Suffocating Sphere].RankName}]}) {
		/varset Drown ${Spell[Suffocating Sphere].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Shallow Breath].RankName}]}) {
		/varset Drown ${Spell[Shallow Breath].RankName}
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
||	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Transfixer's Aura].RankName}]}) {
|		/varset MeleeAura ${Spell[Transfixer's Aura].RankName}
|		/varset MeleeAuraName Transfixer's Aura
|	}

|-Aura Buff 1 * Var Name: AuraBuff1 string outer
	/if (${Me.Level}>=84 && ${Me.Book[${Spell[Twincast Aura].RankName}]}) {
		/varset Aura2 ${Spell[Twincast Aura].RankName}
	}
|-Aura Buff 2 * Var Name: AuraBuff2 string outer
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Mana Repetition Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Repetition Aura].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Mana Reciprocation Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Reciprocation Aura].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Mana Reverberation Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Reverberation Aura].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Mana Repercussion Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Repercussion Aura].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Mana Reiteration Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Reiteration Aura].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Mana Reiterate Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Reiterate Aura].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Mana Resurgence Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mana Resurgence Aura].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Mystifier's Aura].RankName}]}) {
		/varset Aura1 ${Spell[Mystifier's Aura].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Entrancer's Aura].RankName}]}) {
		/varset Aura1 ${Spell[Entrancer's Aura].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Illusionist's Aura].RankName}]}) {
		/varset Aura1 ${Spell[Illusionist's Aura].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Beguiler's Aura].RankName}]}) {
		/varset Aura1 ${Spell[Beguiler's Aura].RankName}
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
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Speed of Novak].RankName}]}) {
		/varset SingleHaste ${Spell[Speed of Novak].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Speed of Erradin].RankName}]}) {
		/varset SingleHaste ${Spell[Speed of Erradin].RankName}
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Aanya's Quickening].RankName}]}) {
		/varset SingleHaste ${Spell[Aanya's Quickening].RankName}
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

	/if (${Me.Level}>=90 && ${Me.Book[${Spell[Spectral Unity].RankName}]}) {
		/varset UnityRune ${Spell[Spectral Unity].RankName}
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

	/if (!${Me.Book[${SingleStunSpell1}]}) {
		/varset SingleStunSpell1 ${PBAEStunSpell}
	}

|-Single Stun Spell * Var Name: SingleStunSpell2 string outer
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Dizzying Storm].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Dizzying Storm].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Dizzying Squall].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Dizzying Squall].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Dizzying Gyre].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Dizzying Gyre].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Dizzying Helix].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Dizzying Helix].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[The Downward Spiral].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[The Downward Spiral].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Whirling into the Hollow].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Whirling into the Hollow].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Spinning into the Void].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Spinning into the Void].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Largarn's Lamentation].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Largarn's Lamentation].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Dyn's Dizzying Draught].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Dyn's Dizzying Draught].RankName}
	} else /if (${Me.Level}>=28 && ${Me.Book[${Spell[Whirl till you hurl].RankName}]}) {
		/varset SingleStunSpell2 ${Spell[Whirl till you hurl].RankName}
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

	/if (${Me.AltAbility[25].Name.Find[disabled]} && ${Me.AltAbilityReady[25]}) {
		/alt act 25
		/delay 5
	}
	
	/call enc_load_spellbar

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