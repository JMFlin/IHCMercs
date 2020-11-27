|- ihcwarutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub shd_setup
|-Create Alias
	|-- Toggles
|-Declare Discs
	/declare endregen		string outer NULL
	/declare Aura1			string outer NULL
	/declare Aura2			string outer NULL
	/declare Aura1Name string outer NULL
	/declare Aura2Name string outer NULL

	/declare IchorGuardDisc	string outer NULL
	/declare IchorGuardID	int outer 0
	/declare UnholyAuraDisc	string outer NULL
	/declare UnholyAuraID	int outer 0
	/declare DeflectionDisc	string outer NULL
	/declare DeflectionID	int outer 0
	/declare LeechcurseDisc	string outer NULL
	/declare LeechcurseID	int outer 0
	/declare Withstand 		string outer NULL
	/declare WithstandID 	int outer 0

	/declare AllianceSpell			string	outer	NULL
	/declare AllianceSpellRankCheck string 	outer 	NULL

	/declare ClaretBlade string	outer	NULL
	/declare ImpenitentInfluence string	outer	NULL
	/declare PetSpell				string	outer	NULL
|-Config Options
	/declare ChestItemName string outer "${Me.Inventory[17].Name}"

|- Spells
	/declare DichotomicFang	string outer NULL
	/declare Stance			string outer NULL
	/declare Touch1			string outer NULL
	/declare Touch2			string outer NULL
	/declare Touch3			string outer NULL
	/declare DireTestemony 	string outer NULL
	/declare Terror1	 	string outer NULL
	/declare Terror2		string outer NULL
	/declare Bond			string outer NULL
	/declare Denial			string outer NULL
	/declare Bargain		string outer NULL
	/declare Skin			string outer NULL
	/declare SnareSpell 	string outer NULL
	/declare Torrent		string outer NULL
	/declare Disruption		string outer NULL
	/declare PosseSpell		string outer Origin
	/declare Spear 			string outer NULL
	/declare Power 			string outer NULL


	/declare Cloak 			string outer NULL
	/declare HPShroud 		string outer NULL
	/declare MPShroud 		string outer NULL

	/declare Recourse 		string outer NONE 
	/declare PullTowards 	string outer NULL

	/declare GoMNuke				string outer NULL
	/declare GoMNuke2				string outer NULL

	/if (${FindItem[Diplomatic Papers].ID}) /varset ItemDipPapers Diplomatic Papers
/return 
|----------------------------------------------------------------------------
|- SUB: ${Me.Class.ShortName.Lower}_load_spellbar
|---------------------------------------------------------------------------- 
Sub shd_load_spellbar
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar


	/if (${Me.AltAbility[Mnemonic Retention].Rank} == 5) {
		
		/call LoadSpellGem "${Touch1}" 1
		/call LoadSpellGem "${Touch2}" 2
		|/call LoadSpellGem "${Touch3}" 4
		/call LoadSpellGem "${DireTestemony}" 3
		/call LoadSpellGem "${DichotomicFang}" 4
		/call LoadSpellGem "${Spear}" 5
		/call LoadSpellGem "${Terror1}" 6
		/call LoadSpellGem "${Terror2}" 7
		/call LoadSpellGem "${Power}" 8
		| /call LoadSpellGem "${Bond}" 8
		|/call LoadSpellGem "${AllianceSpell}" 9
		/call LoadSpellGem "${Denial}" 9
		/call LoadSpellGem "${Bargain}" 10
		/call LoadSpellGem "${Disruption}" 11
		/call LoadSpellGem "${Stance}" 12
		/call LoadSpellGem "${Skin}" 13

	} else /if (${Me.AltAbility[Mnemonic Retention].Rank} == 4) {

		/call LoadSpellGem "${Touch1}" 1
		/call LoadSpellGem "${Touch2}" 2
		|/call LoadSpellGem "${Touch3}" 4
		/call LoadSpellGem "${DireTestemony}" 3
		|/call LoadSpellGem "${DichotomicFang}" 4
		/call LoadSpellGem "${Spear}" 4
		/call LoadSpellGem "${Terror1}" 5
		/call LoadSpellGem "${Terror2}" 6
		/call LoadSpellGem "${Power}" 7
		| /call LoadSpellGem "${Bond}" 8
		/call LoadSpellGem "${Denial}" 8
		/call LoadSpellGem "${Bargain}" 9
		/call LoadSpellGem "${Disruption}" 10
		/call LoadSpellGem "${Stance}" 11
		/call LoadSpellGem "${Skin}" 12


	} else {

		/call LoadSpellGem "${Touch1}" 1
		/call LoadSpellGem "${Touch2}" 2
		/call LoadSpellGem "${DireTestemony}" 3

		/call LoadSpellGem "${Power}" 4
		|/call LoadSpellGem "${Touch3}" 3
		/call LoadSpellGem "${Terror1}" 5
		/call LoadSpellGem "${Terror2}" 6
		|/call LoadSpellGem "${Bond}" 6
		
		/if (${Me.Book[${Spell[${Stance}].RankName}]}) {
			/call LoadSpellGem "${Stance}" 7
		} else {
			/if (!${Me.AltAbility[Encroaching Darkness].Rank} >= 1) /call LoadSpellGem "${SnareSpell}" 7
		}

		/call LoadSpellGem "${Spear}" 8
	}
	/delay 2s
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: SetupSpells
|---------------------------------------------------------------------------- 
Sub shd_abilities
	| Spells

	| Dicho
	/if (${Me.Level}>=${Spell[Dissident Fang].Level} && ${Me.CombatAbility[${Spell[Dissident Fang].RankName}]}) {
		/varset DichotomicFang ${Spell[Dissident Fang].RankName}
	} else /if (${Me.Level}>=${Spell[Dichotomic Fang].Level} && ${Me.CombatAbility[${Spell[Dichotomic Fang].RankName}]}) {
		/varset DichotomicFang ${Spell[Dichotomic Fang].RankName}
	}

	/if (${Me.Level}>=${Spell[Minion of Drendar].Level} && ${Me.Book[${Spell[Minion of Drendar].RankName}]}) {
		/varset PetSpell ${Spell[Minion of Drendar].RankName}
	} else /if (${Me.Level}>=${Spell[Minion of T'Vem].Level} && ${Me.Book[${Spell[Minion of T'Vem].RankName}]}) {
		/varset PetSpell ${Spell[Minion of T'Vem].RankName}
	} else /if (${Me.Level}>=${Spell[Minion of Vizat].Level} && ${Me.Book[${Spell[Minion of Vizat].RankName}]}) {
		/varset PetSpell ${Spell[Minion of Vizat].RankName}
	} else /if (${Me.Level}>=${Spell[Minion of Grelleth].Level} && ${Me.Book[${Spell[Minion of Grelleth].RankName}]}) {
		/varset PetSpell ${Spell[Minion of Grelleth].RankName}
	} else /if (${Me.Level}>=${Spell[Minion of Sholoth].Level} && ${Me.Book[${Spell[Minion of Sholoth].RankName}]}) {
		/varset PetSpell ${Spell[Minion of Sholoth].RankName}
	} else /if (${Me.Level}>=${Spell[Minion of Fear].Level} && ${Me.Book[${Spell[Minion of Fear].RankName}]}) {
		/varset PetSpell ${Spell[Minion of Fear].RankName}
	} else /if (${Me.Level}>=${Spell[Minion of Sebilis].Level} && ${Me.Book[${Spell[Minion of Sebilis].RankName}]}) {
		/varset PetSpell ${Spell[Minion of Sebilis].RankName}
	} else /if (${Me.Level}>=${Spell[Maladroit Minion].Level} && ${Me.Book[${Spell[Maladroit Minion].RankName}]}) {
		/varset PetSpell ${Spell[Maladroit Minion].RankName}
	} else /if (${Me.Level}>=${Spell[Shambling Minion].Level} && ${Me.Book[${Spell[Shambling Minion].RankName}]}) {
		/varset PetSpell ${Spell[Shambling Minion].RankName}
	} else /if (${Me.Level}>=${Spell[Son of Decay].Level} && ${Me.Book[${Spell[Son of Decay].RankName}]}) {
		/varset PetSpell ${Spell[Son of Decay].RankName}
	} else /if (${Me.Level}>=${Spell[Cackling Bones].Level} && ${Me.Book[${Spell[Cackling Bones].RankName}]}) {
		/varset PetSpell ${Spell[Cackling Bones].RankName}
	} else /if (${Me.Level}>=${Spell[Malignant Dead].Level} && ${Me.Book[${Spell[Malignant Dead].RankName}]}) {
		/varset PetSpell ${Spell[Malignant Dead].RankName}
	} else /if (${Me.Level}>=${Spell[Restless Bones].Level} && ${Me.Book[${Spell[Restless Bones].RankName}]}) {
		/varset PetSpell ${Spell[Restless Bones].RankName}
	}

	

	| Power
	/if (${Me.Level}>=${Spell[Protest for Power].Level} && ${Me.Book[${Spell[Protest for Power].RankName}]}) {
		/varset Power ${Spell[Protest for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Refute for Power].Level} && ${Me.Book[${Spell[Refute for Power].RankName}]}) {
		/varset Power ${Spell[Refute for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Impose for Power].Level} && ${Me.Book[${Spell[Impose for Power].RankName}]}) {
		/varset Power ${Spell[Impose for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Demand for Power].Level} && ${Me.Book[${Spell[Demand for Power].RankName}]}) {
		/varset Power ${Spell[Demand for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Provocation for Power].Level} && ${Me.Book[${Spell[Provocation for Power].RankName}]}) {
		/varset Power ${Spell[Provocation for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Confrontation for Power].Level} && ${Me.Book[${Spell[Confrontation for Power].RankName}]}) {
		/varset Power ${Spell[Confrontation for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Charge for Power].Level} && ${Me.Book[${Spell[Charge for Power].RankName}]}) {
		/varset Power ${Spell[Charge for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Trial for Power].Level}  && ${Me.Book[${Spell[Trial for Power].RankName}]}) {
		/varset Power ${Spell[Trial for Power].RankName}
	} else /if (${Me.Level}>=${Spell[Challenge for Power].Level}  && ${Me.Book[${Spell[Challenge for Power].RankName}]}) {
		/varset Power ${Spell[Challenge for Power].RankName}
	} 

	| Spear
	/if (${Me.Level}>=${Spell[Spear of Cadcane].Level} && ${Me.Book[${Spell[Spear of Cadcane].RankName}]}) {
		/varset Spear ${Spell[Spear of Cadcane].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Tylix].Level} && ${Me.Book[${Spell[Spear of Tylix].RankName}]}) {
		/varset Spear ${Spell[Spear of Tylix].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Vizat].Level} && ${Me.Book[${Spell[Spear of Vizat].RankName}]}) {
		/varset Spear ${Spell[Spear of Vizat].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Grelleth].Level} && ${Me.Book[${Spell[Spear of Grelleth].RankName}]}) {
		/varset Spear ${Spell[Spear of Grelleth].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Sholoth].Level} && ${Me.Book[${Spell[Spear of Sholoth].RankName}]}) {
		/varset Spear ${Spell[Spear of Sholoth].RankName}
	} else /if (${Me.Level}>=${Spell[Gorgon Spear].Level} && ${Me.Book[${Spell[Gorgon Spear].RankName}]}) {
		/varset Spear ${Spell[Gorgon Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Malarian Spear].Level} && ${Me.Book[${Spell[Malarian Spear].RankName}]}) {
		/varset Spear ${Spell[Malarian Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Rotmarrow Spear].Level} && ${Me.Book[${Spell[Rotmarrow Spear].RankName}]}) {
		/varset Spear ${Spell[Rotmarrow Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Rotroot Spear].Level} && ${Me.Book[${Spell[Rotroot Spear].RankName}]}) {
		/varset Spear ${Spell[Rotroot Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Muram].Level} && ${Me.Book[${Spell[Spear of Muram].RankName}]}) {
		/varset Spear ${Spell[Spear of Muram].RankName}
	} else /if (${Me.Level}>=${Spell[Miasmic Spear].Level} && ${Me.Book[${Spell[Miasmic Spear].RankName}]}) {
		/varset Spear ${Spell[Miasmic Spear].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Decay].Level} && ${Me.Book[${Spell[Spear of Decay].RankName}]}) {
		/varset Spear ${Spell[Spear of Decay].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Plague].Level} && ${Me.Book[${Spell[Spear of Plague].RankName}]}) {
		/varset Spear ${Spell[Spear of Plague].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Pain].Level} && ${Me.Book[${Spell[Spear of Pain].RankName}]}) {
		/varset Spear ${Spell[Spear of Pain].RankName}
	} else /if (${Me.Level}>=${Spell[Spear of Disease].Level} && ${Me.Book[${Spell[Spear of Disease].RankName}]}) {
		/varset Spear ${Spell[Spear of Disease].RankName}
	} 


	| Touches
	/if (${Me.Level}>=${Spell[Touch of Drendar].Level} && ${Me.Book[${Spell[Touch of Drendar].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Drendar].RankName}
		/varset Touch2 ${Spell[Touch of T'vem].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of T'vem].Level} && ${Me.Book[${Spell[Touch of T'vem].RankName}]}) {
		/varset Touch1 ${Spell[Touch of T'vem].RankName}
		/varset Touch2 ${Spell[Touch of Lutzen].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Lutzen].Level} && ${Me.Book[${Spell[Touch of Lutzen].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Lutzen].RankName}
		/varset Touch2 ${Spell[Touch of Falsin].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Falsin].Level} && ${Me.Book[${Spell[Touch of Falsin].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Falsin].RankName}
		/varset Touch2 ${Spell[Touch of Urash].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Urash].Level} && ${Me.Book[${Spell[Touch of Urash].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Urash].RankName}
		/varset Touch2 ${Spell[Touch of Dyalgem].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Dyalgem].Level} && ${Me.Book[${Spell[Touch of Dyalgem].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Dyalgem].RankName}
		/varset Touch2 ${Spell[Touch of Tharoff].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Tharoff].Level} && ${Me.Book[${Spell[Touch of Tharoff].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Tharoff].RankName}
		/varset Touch2 ${Spell[Touch of Kildrukaun].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Kildrukaun].Level}  && ${Me.Book[${Spell[Touch of Kildrukaun].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Kildrukaun].RankName}
		/varset Touch2 ${Spell[Touch of Severan].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Severan].Level}  && ${Me.Book[${Spell[Touch of Severan].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Severan].RankName}
		/varset Touch2 ${Spell[Touch of Inruku].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Inruku].Level}  && ${Me.Book[${Spell[Touch of Inruku].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Inruku].RankName}
		/varset Touch2 ${Spell[Touch of Innoruuk].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Innoruuk].Level}  && ${Me.Book[${Spell[Touch of Innoruuk].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Innoruuk].RankName}
		/varset Touch2 ${Spell[Touch of Volatis].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Volatis].Level}  && ${Me.Book[${Spell[Touch of Volatis].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Volatis].RankName}
		/varset Touch2 ${Spell[Drain Soul].RankName}
	} else /if (${Me.Level}>=${Spell[Drain Soul].Level}  && ${Me.Book[${Spell[Drain Soul].RankName}]}) {
		/varset Touch1 ${Spell[Drain Soul].RankName}
		/varset Touch2 ${Spell[Drain Spirit].RankName}
	} else /if (${Me.Level}>=${Spell[Drain Spirit].Level}  && ${Me.Book[${Spell[Drain Spirit].RankName}]}) {
		/varset Touch1 ${Spell[Drain Spirit].RankName}
		/varset Touch2 ${Spell[Drain Spirit].RankName}
	} else /if (${Me.Level}>=${Spell[Drain Soul].Level}  && ${Me.Book[${Spell[Drain Soul].RankName}]}) {
		/varset Touch1 ${Spell[Drain Soul].RankName}
		/varset Touch2 ${Spell[Spirit Tap].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit Tap].Level}  && ${Me.Book[${Spell[Spirit Tap].RankName}]}) {
		/varset Touch1 ${Spell[Spirit Tap].RankName}
		/varset Touch2 ${Spell[Siphon Life].RankName}
	} else /if (${Me.Level}>=${Spell[Siphon Life].Level}  && ${Me.Book[${Spell[Siphon Life].RankName}]}) {
		/varset Touch1 ${Spell[Siphon Life].RankName}
		/varset Touch2 ${Spell[Life Leech].RankName}
	} else /if (${Me.Level}>=${Spell[Life Leech].Level}  && ${Me.Book[${Spell[Life Leech].RankName}]}) {
		/varset Touch1 ${Spell[Life Leech].RankName}
		/varset Touch2 ${Spell[Lifedraw].RankName}
	} else /if (${Me.Level}>=${Spell[Lifedraw].Level}  && ${Me.Book[${Spell[Lifedraw].RankName}]}) {
		/varset Touch1 ${Spell[Lifedraw].RankName}
		/varset Touch2 ${Spell[Lifespike].RankName}
	} else /if (${Me.Level}>=${Spell[Lifetap].Level}  && ${Me.Book[${Spell[Lifetap].RankName}]}) {
		/varset Touch1 ${Spell[Lifetap].RankName}
	} 

		
|**
	/if (${Me.Level}>=${Spell[Touch of Hemofax].Level} && ${Me.Book[${Spell[Touch of Hemofax].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Hemofax].RankName}
	} else /if (${Me.Level}>=${Spell[Touch of Severan].Level} && ${Me.Book[${Spell[Touch of Severan].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Severan].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Touch of the Devourer].RankName}]}) {
		/varset Touch2 ${Spell[Touch of the Devourer].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Touch of Innoruuk].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Innoruuk].RankName}
	} else /if (${Me.Level}>=51 && ${Me.Book[${Spell[Siphon Life].RankName}]}) {
		/varset Touch2 ${Spell[Siphon Life].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Lifetap].RankName}]}) {
		/varset Touch2 ${Spell[Lifetap].RankName}
	}
**|

	/if (${Me.Level}>=100 && ${Me.Book[${Spell[Touch of Holmein].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Holmein].RankName}
		/varset Recourse "Gift of the Holmein"
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Touch of Klonda].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Klonda].RankName}
		/varset Recourse "Gift of the Klonda"
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Touch of Piqiorn].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Piqiorn].RankName}
		/varset Recourse "Gift of Piqiorn"
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Touch of Dyalgem].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Dyalgem].RankName}
		/varset Recourse "Gift of Dyalgem"
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Touch of the Soulbleeder].RankName}]}) {
		/varset Touch3 ${Spell[Touch of the Soulbleeder].RankName}
		/varset Recourse "Gift of the Soulbleeder"
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Touch of Volatis].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Volatis].RankName}
		/varset Recourse "Gift of Volatis"
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Touch of Draygun].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Draygun].RankName}
		/varset Recourse "Gift of Draygun"
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[Drain Spirit].RankName}]}) {
		/varset Touch3 ${Spell[Drain Spirit].RankName}
	} else /if (${Me.Level}>=29 && ${Me.Book[${Spell[Lifedraw].RankName}]}) {
		/varset Touch3 ${Spell[Lifedraw].RankName}
	}  else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Lifespike].RankName}]}) {
		/varset Touch3 ${Spell[Lifespike].RankName}
	} else /if (${Me.Level}>=8 && ${Me.Book[${Spell[Lifetap].RankName}]}) {
		/varset Touch3 ${Spell[Lifetap].RankName}
	}

	| Dire
	/if (${Me.Level}>=${Spell[Dire Indictment].Level} && ${Me.Book[${Spell[Dire Indictment].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Indictment].RankName}
	} else /if (${Me.Level}>=${Spell[Dire Testimony].Level} && ${Me.Book[${Spell[Dire Testimony].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Testimony].RankName}
	} else /if (${Me.Level}>=${Spell[Dire Declaration].Level} && ${Me.Book[${Spell[Dire Declaration].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Declaration].RankName}
	} else /if (${Me.Level}>=${Spell[Dire Insinuation].Level} && ${Me.Book[${Spell[Dire Insinuation].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Insinuation].RankName}
	} else /if (${Me.Level}>=${Spell[Dire Allegation].Level} && ${Me.Book[${Spell[Dire Allegation].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Allegation].RankName}
	} else /if (${Me.Level}>=${Spell[Dire Accusation].Level} && ${Me.Book[${Spell[Dire Accusation].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Accusation].RankName}
	} else /if (${Me.Level}>=${Spell[Dire Implication].Level} && ${Me.Book[${Spell[Dire Implication].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Implication].RankName}
	}


	| Terrors
	/if (${Me.Level}>=${Spell[Terror of Mirenilla].Level} && ${Me.Book[${Spell[Terror of Mirenilla].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Mirenilla].RankName}
		/varset Terror2 ${Spell[Terror of Kra'Du].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Kra'Du].Level} && ${Me.Book[${Spell[Terror of Kra'Du].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Kra'Du].RankName}
		/varset Terror2 ${Spell[Terror of Narus].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Narus].Level} && ${Me.Book[${Spell[Terror of Narus].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Narus].RankName}
		/varset Terror2 ${Spell[Terror of Poira].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Poira].Level} && ${Me.Book[${Spell[Terror of Poira].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Poira].RankName}
		/varset Terror2 ${Spell[Terror of Desalin].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Desalin].Level} && ${Me.Book[${Spell[Terror of Desalin].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Desalin].RankName}
		/varset Terror2 ${Spell[Terror of Rerekalen].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Rerekalen].Level} && ${Me.Book[${Spell[Terror of Rerekalen].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Rerekalen].RankName}
		/varset Terror2 ${Spell[Terror of Jelvalak].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Jelvalak].Level} && ${Me.Book[${Spell[Terror of Jelvalak].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Jelvalak].RankName}
		/varset Terror2 ${Spell[Terror of Vergalid].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Vergalid].Level} && ${Me.Book[${Spell[Terror of Vergalid].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Vergalid].RankName}
		/varset Terror2 ${Spell[Terror of Discord].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Discord].Level} && ${Me.Book[${Spell[Terror of Discord].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Discord].RankName}
		/varset Terror2 ${Spell[Terror of Terris].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Terris].Level} && ${Me.Book[${Spell[Terror of Terris].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Terris].RankName}
		/varset Terror2 ${Spell[Terror of Shadows].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of Shadows].Level} && ${Me.Book[${Spell[Terror of Shadows].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Shadows].RankName}
		/varset Terror2 ${Spell[Terror of Darkness].RankName}
	} 

	| Bonds
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Bond of Xalgoz].RankName}]}) {
		/varset Bond ${Spell[Bond of Xalgoz].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Bond of Xalgoz].RankName}]}) {
		/varset Bond ${Spell[Bond of Xalgoz].RankName}
	} else /if (${Me.Level}>=${Spell[Bond of Malthiasiss].Level} && ${Me.Book[${Spell[Bond of Malthiasiss].RankName}]}) {
		/varset Bond ${Spell[Bond of Malthiasiss].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Bond of Laarthik].RankName}]}) {
		/varset Bond ${Spell[Bond of Laarthik].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Bond of the Blackwater].RankName}]}) {
		/varset Bond ${Spell[Bond of the Blackwater].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Bond of the Blacktalon].RankName}]}) {
		/varset Bond ${Spell[Bond of the Blacktalon].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Bond of Inruku].RankName}]}) {
		/varset Bond ${Spell[Bond of Inruku].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Bond of Death].RankName}]}) {
		/varset Bond ${Spell[Bond of Death].RankName}
	} else /if (${Me.Level}>=57 && ${Me.Book[${Spell[Vampiric Curse].RankName}]}) {
		/varset Bond ${Spell[Vampiric Curse].RankName}
	}


	| AoE Hate
	/if (${Me.Level}>=${Spell[Insidious Rejection].Level} && ${Me.Book[${Spell[Insidious Rejection].RankName}]}) {
		/varset Denial ${Spell[Insidious Rejection].RankName}
	} else /if (${Me.Level}>=${Spell[Insidious Denial].Level} && ${Me.Book[${Spell[Insidious Denial].RankName}]}) {
		/varset Denial ${Spell[Insidious Denial].RankName}
	} else /if (${Me.Level}>=${Spell[Deceitful Deflection].Level} && ${Me.Book[${Spell[Deceitful Deflection].RankName}]}) {
		/varset Denial ${Spell[Deceitful Deflection	].RankName}
	} else /if (${Me.Level}>=${Spell[Insidious Deflection].Level} && ${Me.Book[${Spell[Insidious Deflection].RankName}]}) {
		/varset Denial ${Spell[Insidious Deflection].RankName}
	} else /if (${Me.Level}>=${Spell[Word of Spirit].Level} && ${Me.Book[${Spell[Word of Spirit].RankName}]}) {
		/varset Denial ${Spell[Word of Spirit].RankName}
	}



	
	| AoE Hate
	/if (${Me.Level}>=${Spell[Abhorrent Bargain].Level} && ${Me.Book[${Spell[Abhorrent Bargain].RankName}]}) {
		/varset Bargain ${Spell[Abhorrent Bargain].RankName}
	} else /if (${Me.Level}>=${Spell[Hateful Bargain].Level} && ${Me.Book[${Spell[Hateful Bargain].RankName}]}) {
		/varset Bargain ${Spell[Hateful Bargain].RankName}
	} else /if (${Me.Level}>=${Spell[Distasteful Bargain].Level} && ${Me.Book[${Spell[Distasteful Bargain].RankName}]}) {
		/varset Bargain ${Spell[Distasteful Bargain].RankName}
	} else /if (${Me.Level}>=${Spell[Repugnant Bargain].Level} && ${Me.Book[${Spell[Repugnant Bargain].RankName}]}) {
		/varset Bargain ${Spell[Repugnant Bargain].RankName}
	} else /if (${Me.Level}>=${Spell[Loathing].Level} && ${Me.Book[${Spell[Loathing].RankName}]}) {
		/varset Denial ${Spell[Loathing].RankName}
	} else /if (${Me.Level}>=${Spell[Burst of Spite].Level} && ${Me.Book[${Spell[Burst of Spite].RankName}]}) {
		/varset Denial ${Spell[Burst of Spite].RankName}
	} else /if (${Me.Level}>=${Spell[Revile].Level} && ${Me.Book[${Spell[Revile].RankName}]}) {
		/varset Denial ${Spell[Revile].RankName}
	} else /if (${Me.Level}>=${Spell[Vilify].Level} && ${Me.Book[${Spell[Vilify].RankName}]}) {
		/varset Denial ${Spell[Vilify].RankName}
	} else /if (${Me.Level}>=${Spell[Dread Gaze].Level} && ${Me.Book[${Spell[Dread Gaze].RankName}]}) {
		/varset Denial ${Spell[Dread Gaze].RankName}
	} 

	

	| Torrent
	/if (${Me.Level}>=${Spell[Torrent of Anguish].Level} && ${Me.Book[${Spell[Torrent of Anguish].RankName}]}) {
		/varset Torrent ${Spell[Torrent of Anguish].RankName}
	} else /if (${Me.Level}>=${Spell[Torrent of Suffering].Level} && ${Me.Book[${Spell[Torrent of Suffering].RankName}]}) {
		/varset Torrent ${Spell[Torrent of Suffering].RankName}
	} else /if (${Me.Level}>=${Spell[Torrent of Misery].Level} && ${Me.Book[${Spell[Torrent of Misery].RankName}]}) {
		/varset Torrent ${Spell[Torrent of Misery].RankName}
	} else /if (${Me.Level}>=${Spell[Torrent of Agony].Level}  && ${Me.Book[${Spell[Torrent of Agony].RankName}]}) {
		/varset Torrent ${Spell[Torrent of Agony].RankName}
	}

	| Disruption
	/if (${Me.Level}>=${Spell[Concordant Disruption].Level} && ${Me.Book[${Spell[Concordant Disruption].RankName}]}) {
		/varset Disruption ${Spell[Concordant Disruption].RankName}
	} else /if (${Me.Level}>=${Spell[Harmonious Disruption].Level}  && ${Me.Book[${Spell[Harmonious Disruption].RankName}]}) {
		/varset Disruption ${Spell[Harmonious Disruption].RankName}
	}
	
	
	
	| Skin
	/if (${Me.Level}>=${Spell[Cadcane's Skin].Level} && ${Me.Book[${Spell[Cadcane's Skin].RankName}]}) {
		/varset Skin ${Spell[Cadcane's Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Tylix's Skin].Level} && ${Me.Book[${Spell[Tylix's Skin].RankName}]}) {
		/varset Skin ${Spell[Tylix's Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Vizat's Skin].Level} && ${Me.Book[${Spell[Vizat's Skin].RankName}]}) {
		/varset Skin ${Spell[Vizat's Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Grelleth's Skin].Level} && ${Me.Book[${Spell[Grelleth's Skin].RankName}]}) {
		/varset Skin ${Spell[Grelleth's Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Sholothian Skin].Level} && ${Me.Book[${Spell[Sholothian Skin].RankName}]}) {
		/varset Skin ${Spell[Sholothian Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Gorgon Skin].Level} && ${Me.Book[${Spell[Gorgon Skin].RankName}]}) {
		/varset Skin ${Spell[Gorgon Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Malarian Skin].Level} && ${Me.Book[${Spell[Malarian Skin].RankName}]}) {
		/varset Skin ${Spell[Malarian Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Umbral Skin].Level} && ${Me.Book[${Spell[Umbral Skin].RankName}]}) {
		/varset Skin ${Spell[Umbral Skin].RankName}
	} else /if (${Me.Level}>=${Spell[Decrepit Skin].Level} && ${Me.Book[${Spell[Decrepit Skin].RankName}]}) {
		/varset Skin ${Spell[Decrepit Skin].RankName}
	}

	| Cloak
	/if (${Me.Level}>=${Spell[Drape of Iceforged].Level} && ${Me.Book[${Spell[Drape of Iceforged].RankName}]}) {
		/varset Cloak ${Spell[Drape of Iceforged].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of Magmaforged].Level} && ${Me.Book[${Spell[Drape of Magmaforged].RankName}]}) {
		/varset Cloak ${Spell[Drape of Magmaforged].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of Wrathforged].Level} && ${Me.Book[${Spell[Drape of Wrathforged].RankName}]}) {
		/varset Cloak ${Spell[Drape of Wrathforged].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of the Fallen].Level} && ${Me.Book[${Spell[Drape of the Fallen].RankName}]}) {
		/varset Cloak ${Spell[Drape of the Fallen].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of the Sepulcher].Level} && ${Me.Book[${Spell[Drape of the Sepulcher].RankName}]}) {
		/varset Cloak ${Spell[Drape of the Sepulcher].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of Fear].Level} && ${Me.Book[${Spell[Drape of Fear].RankName}]}) {
		/varset Cloak ${Spell[Drape of Fear].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of Korafax].Level} && ${Me.Book[${Spell[Drape of Korafax].RankName}]}) {
		/varset Cloak ${Spell[Drape of Korafax].RankName}
	} else /if (${Me.Level}>=${Spell[Drape of Corruption].Level} && ${Me.Book[${Spell[Drape of Corruption].RankName}]}) {
		/varset Cloak ${Spell[Drape of Corruption].RankName}
	} else /if (${Me.Level}>=${Spell[Cloak of Corruption].Level} && ${Me.Book[${Spell[Cloak of Corruption].RankName}]}) {
		/varset Cloak ${Spell[Cloak of Corruption].RankName}
	} else /if (${Me.Level}>=${Spell[Cloak of Discord].Level} && ${Me.Book[${Spell[Cloak of Discord].RankName}]}) {
		/varset Cloak ${Spell[Cloak of Discord].RankName}
	} else /if (${Me.Level}>=${Spell[Cloak of Luclin].Level} && ${Me.Book[${Spell[Cloak of Luclin].RankName}]}) {
		/varset Cloak ${Spell[Cloak of Luclin].RankName}
	} else /if (${Me.Level}>=${Spell[Cloak of the Akheva].Level} && ${Me.Book[${Spell[Cloak of the Akheva].RankName}]}) {
		/varset Cloak ${Spell[Cloak of the Akheva].RankName}
	} else /if (${Me.Level}>=${Spell[Grim Aura].Level} && ${Me.Book[${Spell[Grim Aura].RankName}]}) {
		/varset Cloak ${Spell[Grim Aura].RankName}
	}
	
	| Stance
	/if (${Me.Level}>=${Spell[Stormwall Stance].Level} && ${Me.Book[${Spell[Stormwall Stance].RankName}]}) {
		/varset Stance ${Spell[Stormwall Stance].RankName}
	} else /if (${Me.Level}>=${Spell[Staunch Stance].Level} && ${Me.Book[${Spell[Staunch Stance].RankName}]}) {
		/varset Stance ${Spell[Staunch Stance].RankName}
	} else /if (${Me.Level}>=${Spell[Defiant Stance].Level} && ${Me.Book[${Spell[Defiant Stance].RankName}]}) {
		/varset Stance ${Spell[Defiant Stance].RankName}
	} else /if (${Me.Level}>=${Spell[Steely Stance].Level} && ${Me.Book[${Spell[Steely Stance].RankName}]}) {
		/varset Stance ${Spell[Steely Stance].RankName}
	}

	| Shrouds
	/if (${Me.Level}>=${Spell[Shroud of the Restless].Level} && ${Me.Book[${Spell[Shroud of the Restless].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Restless].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Krellnakor].Level} && ${Me.Book[${Spell[Shroud of the Krellnakor].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Krellnakor].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Doomscale].Level} && ${Me.Book[${Spell[Shroud of the Doomscale].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Doomscale].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Darksworn].Level} && ${Me.Book[${Spell[Shroud of the Darksworn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Darksworn].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Shadeborne].Level} && ${Me.Book[${Spell[Shroud of the Shadeborne].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Shadeborne].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Plagueborne].Level} && ${Me.Book[${Spell[Shroud of the Plagueborne].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Plagueborne].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Blightborn].Level} && ${Me.Book[${Spell[Shroud of the Blightborn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Blightborn].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Gloomborn].Level} && ${Me.Book[${Spell[Shroud of the Gloomborn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Gloomborn].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of the Nightborn].Level} && ${Me.Book[${Spell[Shroud of the Nightborn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Nightborn].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of Discord].Level} && ${Me.Book[${Spell[Shroud of Discord].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of Discord].RankName}
	} else /if (${Me.Level}>=${Spell[Black Shroud].Level} && ${Me.Book[${Spell[Black Shroud].RankName}]}) {
		/varset HPShroud ${Spell[Black Shroud].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of Chaos].Level} && ${Me.Book[${Spell[Shroud of Chaos].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of Chaos].RankName}
	} else /if (${Me.Level}>=${Spell[Shroud of Death].Level} && ${Me.Book[${Spell[Shroud of Death].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of Death].RankName}
	} else /if (${Me.Level}>=${Spell[Scream of Death].Level} && ${Me.Book[${Spell[Scream of Death].RankName}]}) {
		/varset HPShroud ${Spell[Scream of Death].RankName}
	} else /if (${Me.Level}>=${Spell[Vampiric Embrace].Level} && ${Me.Book[${Spell[Vampiric Embrace].RankName}]}) {
		/varset HPShroud ${Spell[Vampiric Embrace].RankName}
	}

	/if (${Me.Level}>=96 && ${Me.Book[${Spell[Mental Terror].RankName}]}) {
		/varset MPShroud ${Spell[Mental Terror].RankName}
	} else /if (${Me.Level}>${Spell[Amygdalan Horror].Level} && ${Me.Book[${Spell[Amygdalan Horror].RankName}]}) {
		/varset MPShroud ${Spell[Amygdalan Horror].RankName}
	} else /if (${Me.Level}>81 && ${Me.Book[${Spell[Mindshear Horror].RankName}]}) {
		/varset MPShroud ${Spell[Mindshear Horror].RankName}
	} else /if (${Me.Level}>65 && ${Me.Book[${Spell[Mental Horror].RankName}]}) {
		/varset MPShroud ${Spell[Mental Horror].RankName}
	} else /if (${Me.Level}>=52 && ${Me.Book[${Spell[Mental Corruption].RankName}]}) {
		/varset MPShroud ${Spell[Mental Corruption].RankName}
	} 

	| Darkness
	
	/if (${Me.AltAbility[Encroaching Darkness].Rank} >= 1) {
		/varset SnareSpell Encroaching Darkness
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Festering Darkness].RankName}]}) {
		/varset SnareSpell ${Spell[Festering Darkness].RankName}
	} else /if (${Me.Level}>=44 && ${Me.Book[${Spell[Dooming Darkness].RankName}]}) {
		/varset SnareSpell ${Spell[Dooming Darkness].RankName}
	} else /if (${Me.Level}>=4 && ${Me.Book[${Spell[Clinging Darkness].RankName}]}) {
		/varset SnareSpell ${Spell[Clinging Darkness].RankName}
	}


	| Discs
	/if (${Me.Level}>=${Spell[Restless Mantle].Level} && ${Me.CombatAbility[${Spell[Restless Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Restless Mantle].RankName}
		/varset IchorGuardID ${Spell[Restless Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Krellnakor Mantle].Level} && ${Me.CombatAbility[${Spell[Krellnakor Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Krellnakor Mantle].RankName}
		/varset IchorGuardID ${Spell[Krellnakor Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Doomscale Mantle].Level} && ${Me.CombatAbility[${Spell[Doomscale Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Doomscale Mantle].RankName}
		/varset IchorGuardID ${Spell[Doomscale Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Bonebrood Mantle].Level} && ${Me.CombatAbility[${Spell[Bonebrood Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Bonebrood Mantle].RankName}
		/varset IchorGuardID ${Spell[Bonebrood Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Recondite Mantle].Level} && ${Me.CombatAbility[${Spell[Recondite Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Recondite Mantle].RankName}
		/varset IchorGuardID ${Spell[Recondite Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Gorgon Mantle].Level} && ${Me.CombatAbility[${Spell[Gorgon Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Gorgon Mantle].RankName}
		/varset IchorGuardID ${Spell[Gorgon Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Malarian Mantle].Level} && ${Me.CombatAbility[${Spell[Malarian Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Malarian Mantle].RankName}
		/varset IchorGuardID ${Spell[Malarian Mantle].ID}
	} else /if (${Me.Level}>=${Spell[Umbral Carapace].Level} && ${Me.CombatAbility[${Spell[Umbral Carapace].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Umbral Carapace].RankName}
		/varset IchorGuardID ${Spell[Umbral Carapace].ID}
	} else /if (${Me.Level}>=${Spell[Soul Carapace].Level} && ${Me.CombatAbility[${Spell[Soul Carapace].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Soul Carapace].RankName}
		/varset IchorGuardID ${Spell[Soul Carapace].ID}
	} else /if (${Me.Level}>=${Spell[Soul Shield].Level} && ${Me.CombatAbility[${Spell[Soul Shield].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Soul Shield].RankName}
		/varset IchorGuardID ${Spell[Soul Shield].ID}
	} else /if (${Me.Level}>=${Spell[Soul Guard].Level} && ${Me.CombatAbility[${Spell[Soul Guard].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Soul Guard].RankName}
		/varset IchorGuardID ${Spell[Soul Guard].ID}
	} else /if (${Me.Level}>=${Spell[Ichor Guard].Level} && ${Me.CombatAbility[${Spell[Ichor Guard].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Ichor Guard].RankName}
		/varset IchorGuardID ${Spell[Ichor Guard].ID}
	}

	/if (${Me.Level}>=${Spell[Unholy Aura Discipline].Level} && ${Me.CombatAbility[${Spell[Unholy Aura Discipline].RankName}]}) {
		/varset UnholyAuraDisc ${Spell[Unholy Aura Discipline].RankName}
		/varset UnholyAuraID ${Spell[Unholy Aura Discipline].ID}
	}
	/if (${Me.Level}>=${Spell[Deflection Discipline].Level} && ${Me.CombatAbility[${Spell[Deflection Discipline].RankName}]}) {
		/varset DeflectionDisc ${Spell[Deflection Discipline].RankName}
		/varset DeflectionID ${Spell[Deflection Discipline].ID}
	}

	/if (${Me.Level}>=${Spell[Leechcurse Discipline].Level} && ${Me.CombatAbility[${Spell[Leechcurse Discipline].RankName}]}) {
		/varset LeechcurseDisc ${Spell[Leechcurse Discipline].RankName}
		/varset LeechcurseID ${Spell[Leechcurse Discipline].ID}
	}


	/if (${Me.Level}>=${Spell[Repel].Level} && ${Me.CombatAbility[${Spell[Repel].RankName}]}) {
		/varset Withstand ${Spell[Repel].RankName}
		/varset WithstandID ${Spell[Repel].ID}
	} else /if (${Me.Level}>=${Spell[Reprove].Level} && ${Me.CombatAbility[${Spell[Reprove].RankName}]}) {
		/varset Withstand ${Spell[Reprove].RankName}
		/varset WithstandID ${Spell[Reprove].ID}
	} else /if (${Me.Level}>=${Spell[Renounce].Level} && ${Me.CombatAbility[${Spell[Renounce].RankName}]}) {
		/varset Withstand ${Spell[Renounce].RankName}
		/varset WithstandID ${Spell[Renounce].ID}
	} else /if (${Me.Level}>=${Spell[Defy].Level} && ${Me.CombatAbility[${Spell[Defy].RankName}]}) {
		/varset Withstand ${Spell[Defy].RankName}
		/varset WithstandID ${Spell[Defy].ID}
	} else /if (${Me.Level}>=${Spell[Withstand].Level} && ${Me.CombatAbility[${Spell[Withstand].RankName}]}) {
		/varset Withstand ${Spell[Withstand].RankName}
		/varset WithstandID ${Spell[Withstand].ID}
	}

	/if (${Me.Level}>=${Spell[Cerise Blade].Level} && ${Me.CombatAbility[${Spell[Cerise Blade].RankName}]}) {
		/varset ClaretBlade ${Spell[Cerise Blade].RankName}
	} else /if (${Me.Level}>=${Spell[Claret Blade].Level} && ${Me.CombatAbility[${Spell[Claret Blade].RankName}]}) {
		/varset ClaretBlade ${Spell[Claret Blade].RankName}
	} else /if (${Me.Level}>=${Spell[Carmine Blade].Level} && ${Me.CombatAbility[${Spell[Carmine Blade].RankName}]}) {
		/varset ClaretBlade ${Spell[Carmine Blade].RankName}
	} else /if (${Me.Level}>=${Spell[Scarlet Blade].Level} && ${Me.CombatAbility[${Spell[Scarlet Blade].RankName}]}) {
		/varset ClaretBlade ${Spell[Scarlet Blade].RankName}
	}

	/if (${Me.Level}>=${Spell[Impenitent Influence].Level} && ${Me.CombatAbility[${Spell[Impenitent Influence].RankName}]}) {
		/varset ImpenitentInfluence ${Spell[Impenitent Influence].RankName}
	} else /if (${Me.Level}>=${Spell[Impudent Influence].Level} && ${Me.CombatAbility[${Spell[Impudent Influence].RankName}]}) {
		/varset ImpenitentInfluence ${Spell[Impudent Influence].RankName}
	} else /if (${Me.Level}>=${Spell[Impudent Influence].Level} && ${Me.CombatAbility[${Spell[Impudent Influence].RankName}]}) {
		/varset ImpenitentInfluence ${Spell[Impudent Influence].RankName}
	} else /if (${Me.Level}>=${Spell[Insolent Influence].Level} && ${Me.CombatAbility[${Spell[Insolent Influence].RankName}]}) {
		/varset ImpenitentInfluence ${Spell[Insolent Influence].RankName}
	}

	/if (${Me.Level}>=${Spell[Cursed Guardian Discipline].Level} && ${Me.CombatAbility[${Spell[Cursed Guardian Discipline].RankName}]}) {
		/varset Guardian ${Spell[Cursed Guardian Discipline].RankName}
	} else /if (${Me.Level}>=${Spell[Unholy Guardian Discipline].Level} && ${Me.CombatAbility[${Spell[Unholy Guardian Discipline].RankName}]}) {
		/varset Guardian ${Spell[Unholy Guardian Discipline].RankName}
	}

	

	/if (${Me.AltAbilityReady[Hate's Attraction]}) {
		/varset PullTowards Hate's Attraction
	}

	|-AllianceSpell
	/if (${Me.Level}>=${Spell[Bloodletting Covenant].Level} && ${Me.Book[${Spell[Bloodletting Covenant].RankName}]}) {
		/varset AllianceSpell ${Spell[Bloodletting Covenant].RankName}
		/varset AllianceSpellRankCheck ${Spell[Bloodletting Covenant]}
	} else /if (${Me.Level}>=${Spell[Bloodletting Alliance].Level} && ${Me.Book[${Spell[Bloodletting Alliance].RankName}]}) {
		/varset AllianceSpell ${Spell[Bloodletting Alliance].RankName}
		/varset AllianceSpellRankCheck ${Spell[Bloodletting Alliance]}
	}

	/varset GoMNuke ${DichotomicFang}

	| Pull ability
	/if (${Me.Level}>=42) {
		/varset pullAbility ${Terror1}
		/varset pullDistance 190
	} else /if (${Me.Level}>=33) {
		/varset pullAbility ${Terror2}
		/varset pullDistance 190
	} else /if (${Me.Level}>=8) {
		/varset pullAbility ${Touch3}
		/varset pullDistance 190
	} else {
		/varset pullAbility Melee
		/varset pullDistance 5
	}

	/if (${Me.AltAbility[865].Name.Find[disabled]} && ${Me.AltAbilityReady[865]}) {
		/alt act 865
		/delay 5
	}
	/if (${Me.AltAbility[1278].Name.Find[disabled]} && ${Me.AltAbilityReady[1278]}) {
		/alt act 1278
		/delay 5
	}
	/if (${Me.AltAbility[793].Name.Find[disabled]} && ${Me.AltAbilityReady[793]}) {
		/alt act 793
		/delay 5
	}
	/if (${Me.AltAbility[970].Name.Find[disabled]} && ${Me.AltAbilityReady[970]}) {
		/alt act 970
		/delay 5
	}

	/call shd_load_spellbar

/return

