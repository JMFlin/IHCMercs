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

	/declare Cloak 			string outer NULL
	/declare HPShroud 		string outer NULL
	/declare MPShroud 		string outer NULL

	/declare Recourse 		string outer NULL 
	
	/if (${FindItem[Diplomatic Papers].ID}) /varset ItemDipPapers Diplomatic Papers
/return 
|----------------------------------------------------------------------------
|- SUB: ${Me.Class.ShortName.Lower}_load_spellbar
|---------------------------------------------------------------------------- 
Sub shd_load_spellbar
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar
	/call LoadSpellGem "${Touch1}" 1

	/if (${Me.Book[${Spell[${DireTestemony}].RankName}]}) {
		/call LoadSpellGem "${DireTestemony}" 2
	} else {
		/call LoadSpellGem "${Touch2}" 2
	}

	/call LoadSpellGem "${Touch3}" 3
	/call LoadSpellGem "${Terror1}" 4
	/call LoadSpellGem "${Terror2}" 5
	/call LoadSpellGem "${Bond}" 6
	
	/if (${Me.Book[${Spell[${Stance}].RankName}]}) {
		/call LoadSpellGem "${Stance}" 7
	} else {
		/call LoadSpellGem "${SnareSpell}" 7
	}

	/call LoadSpellGem "${Skin}" 8

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
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Dissident Fang].RankName}]}) {
		/varset DichotomicFang ${Spell[Dissident Fang].RankName}
	} else /if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Dichotomic Fang].RankName}]}) {
		/varset DichotomicFang ${Spell[Dichotomic Fang].RankName}
	}

	| Touches
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Touch of T'vem].RankName}]}) {
		/varset Touch1 ${Spell[Touch of T'vem].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Touch of T'vem].RankName}]}) {
		/varset Touch1 ${Spell[Touch of T'vem].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Touch of Tharoff].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Tharoff].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Touch of Kildrukaun].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Kildrukaun].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Touch of the Wailing Three].RankName}]}) {
		/varset Touch1 ${Spell[Touch of the Wailing Three].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Touch of Inruku].RankName}]}) {
		/varset Touch1 ${Spell[Touch of Inruku].RankName}
	} else /if (${Me.Level}>=47 && ${Me.Book[${Spell[Life Leech].RankName}]}) {
		/varset Touch1 ${Spell[Life Leech].RankName}
	} 

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Touch of Lutzen].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Lutzen].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Touch of Lutzen].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Lutzen].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Touch of Severan].RankName}]}) {
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

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Touch of Falsin].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Falsin].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Touch of Falsin].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Falsin].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Touch of Lanys].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Lanys].RankName}
		/varset Recourse "Gift of Lanys"
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Touch of the Soulbleeder].RankName}]}) {
		/varset Touch3 ${Spell[Touch of the Soulbleeder].RankName}
	} else /if (${Me.Level}>=62 && ${Me.Book[${Spell[Touch of Volatis].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Volatis].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Touch of Draygun].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Draygun].RankName}
	} else /if (${Me.Level}>=29 && ${Me.Book[${Spell[Lifedraw].RankName}]}) {
		/varset Touch3 ${Spell[Lifedraw].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Lifespike].RankName}]}) {
		/varset Touch3 ${Spell[Lifespike].RankName}
	} else /if (${Me.Level}>=8 && ${Me.Book[${Spell[Lifetap].RankName}]}) {
		/varset Touch3 ${Spell[Lifetap].RankName}
	}

	| Dire
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Dire Testimony].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Testimony].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Dire Testimony].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Testimony].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Dire Implication].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Implication].RankName}
	}


	| Terrors
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Terror of Kra'Du].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Kra'Du].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Terror of Kra'Du].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Kra'Du].RankName}
	} else /if (${Me.Level}>=107 && ${Me.Book[${Spell[Terror of Kra'Du].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Kra'Du].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Terror of Jelvalak].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Jelvalak].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Terror of Vergalid].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Vergalid].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Terror of Discord].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Discord].RankName}
	} else /if (${Me.Level}>=59 && ${Me.Book[${Spell[Terror of Terris].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Terris].RankName}
	} else /if (${Me.Level}>=42 && ${Me.Book[${Spell[Terror of Shadows].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Shadows].RankName}
	} 

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Terror of Narus].RankName}]}) {
		/varset Terror2 ${Spell[Terror of Narus].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Terror of Narus].RankName}]}) {
		/varset Terror2 ${Spell[Terror of Narus].RankName}
	} else /if (${Me.Level}>=${Spell[Terror of the Rerekalen].Level} && ${Me.Book[${Spell[Terror of the Rerekalen].RankName}]}) {
		/varset Terror2 ${Spell[Terror of the Rerekalen].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Terror of the Soulbleeder].RankName}]}) {
		/varset Terror2 ${Spell[Terror of the Soulbleeder].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Terror of Thule].RankName}]}) {
		/varset Terror2 ${Spell[Terror of Thule].RankName}
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Terror of Death].RankName}]}) {
		/varset Terror2 ${Spell[Terror of Death].RankName}
	} else /if (${Me.Level}>=33 && ${Me.Book[${Spell[Terror of Darkness].RankName}]}) {
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
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Insidious Denial].RankName}]}) {
		/varset Denial ${Spell[Insidious Denial].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Insidious Denial].RankName}]}) {
		/varset Denial ${Spell[Insidious Denial].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Burst of Spite].RankName}]}) {
		/varset Denial ${Spell[Burst of Spite].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Revile].RankName}]}) {
		/varset Denial ${Spell[Revile].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Vilify].RankName}]}) {
		/varset Denial ${Spell[Vilify].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Dread Gaze].RankName}]}) {
		/varset Denial ${Spell[Dread Gaze].RankName}
	} 

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Hateful Bargain].RankName}]}) {
		/varset Bargain ${Spell[Hateful Bargain].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Hateful Bargain].RankName}]}) {
		/varset Bargain ${Spell[Hateful Bargain].RankName}
	}

	
	| Skin
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Tylix's Skin].RankName}]}) {
		/varset Skin ${Spell[Tylix's Skin].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Tylix's Skin].RankName}]}) {
		/varset Skin ${Spell[Tylix's Skin].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Malarian Skin].RankName}]}) {
		/varset Skin ${Spell[Malarian Skin].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Umbral Skin].RankName}]}) {
		/varset Skin ${Spell[Umbral Skin].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Decrepit Skin].RankName}]}) {
		/varset Skin ${Spell[Decrepit Skin].RankName}
	}

	| Cloak
	/if (${Me.Level}>=84 && ${Me.Book[${Spell[Drape of Korafax].RankName}]}) {
		/varset Cloak ${Spell[Drape of Korafax].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Drape of Corruption].RankName}]}) {
		/varset Cloak ${Spell[Drape of Corruption].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Cloak of Corruption].RankName}]}) {
		/varset Cloak ${Spell[Cloak of Corruption].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Cloak of Discord].RankName}]}) {
		/varset Cloak ${Spell[Cloak of Discord].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Cloak of Luclin].RankName}]}) {
		/varset Cloak ${Spell[Cloak of Luclin].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Cloak of the Akheva].RankName}]}) {
		/varset Cloak ${Spell[Cloak of the Akheva].RankName}
	}

	| Stance
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Defiant Stance].RankName}]}) {
		/varset Stance ${Spell[Defiant Stance].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Defiant Stance].RankName}]}) {
		/varset Stance ${Spell[Defiant Stance].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Steely Stance].RankName}]}) {
		/varset Stance ${Spell[Steely Stance].RankName}
	}

	| Shrouds
	/if (${Me.Level}>=${Spell[Shroud of the Plagueborne].Level} && ${Me.Book[${Spell[Shroud of the Plagueborne].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Plagueborne].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Shroud of the Blightborn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Blightborn].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Shroud of the Gloomborn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Gloomborn].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Shroud of the Nightborn].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of the Nightborn].RankName}
	} else /if (${Me.Level}>=67 && ${Me.Book[${Spell[Shroud of Discord].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of Discord].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Black Shroud].RankName}]}) {
		/varset HPShroud ${Spell[Black Shroud].RankName}
	} else /if (${Me.Level}>63 && ${Me.Book[${Spell[Shroud of Chaos].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of Chaos].RankName}
	} else /if (${Me.Level}>=55 && ${Me.Book[${Spell[Shroud of Death].RankName}]}) {
		/varset HPShroud ${Spell[Shroud of Death].RankName}
	} else /if (${Me.Level}>=37 && ${Me.Book[${Spell[Scream of Death].RankName}]}) {
		/varset HPShroud ${Spell[Scream of Death].RankName}
	} else /if (${Me.Level}>=22 && ${Me.Book[${Spell[Vampiric Embrace].RankName}]}) {
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
	
	/if (${Me.AltAbilityReady[Encroaching Darkness]}) {
		/varset SnareSpell "Encroaching Darkness"
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Festering Darkness].RankName}]}) {
		/varset SnareSpell ${Spell[Festering Darkness].RankName}
	} else /if (${Me.Level}>=4 && ${Me.Book[${Spell[Clinging Darkness].RankName}]}) {
		/varset SnareSpell ${Spell[Clinging Darkness].RankName}
	}

	| Discs
	/if (${Me.Level}>=83 && ${Me.CombatAbility[${Spell[Malarian Mantle].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Malarian Mantle].RankName}
		/varset IchorGuardID ${Spell[Malarian Mantle].ID}
	} else /if (${Me.Level}>=78 && ${Me.CombatAbility[${Spell[Umbral Carapace].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Umbral Carapace].RankName}
		/varset IchorGuardID ${Spell[Umbral Carapace].ID}
	} else /if (${Me.Level}>=73 && ${Me.CombatAbility[${Spell[Soul Shield].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Soul Shield].RankName}
		/varset IchorGuardID ${Spell[Soul Shield].ID}
	} else /if (${Me.Level}>=61 && ${Me.CombatAbility[${Spell[Soul Guard].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Soul Guard].RankName}
		/varset IchorGuardID ${Spell[Soul Guard].ID}
	} else /if (${Me.Level}>=56 && ${Me.CombatAbility[${Spell[Ichor Guard].RankName}]}) {
		/varset IchorGuardDisc ${Spell[Ichor Guard].RankName}
		/varset IchorGuardID ${Spell[Ichor Guard].ID}
	}

	/if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Unholy Aura Discipline].RankName}]}) {
		/varset UnholyAuraDisc ${Spell[Unholy Aura Discipline].RankName}
		/varset UnholyAuraID ${Spell[Unholy Aura Discipline].ID}
	}
	/if (${Me.Level}>=59 && ${Me.CombatAbility[${Spell[Deflection Discipline].RankName}]}) {
		/varset DeflectionDisc ${Spell[Deflection Discipline].RankName}
		/varset DeflectionID ${Spell[Deflection Discipline].ID}
	}

	/if (${Me.Level}>=60 && ${Me.CombatAbility[${Spell[Leechcurse Discipline].RankName}]}) {
		/varset LeechcurseDisc ${Spell[Leechcurse Discipline].RankName}
		/varset LeechcurseID ${Spell[Leechcurse Discipline].ID}
	}

	/if (${Me.Level}>=83 && ${Me.CombatAbility[${Spell[Withstand].RankName}]}) {
		/varset Withstand ${Spell[Withstand].RankName}
		/varset WithstandID ${Spell[Withstand].ID}
	}

	| Pull ability
	/if (${Me.Level}>=42) {
		/varset PullAbility ${Terror1}
		/varset PullDistance 190
	} else /if (${Me.Level}>=33) {
		/varset PullAbility ${Terror2}
		/varset PullDistance 190
	} else /if (${Me.Level}>=8) {
		/varset PullAbility ${Touch3}
		/varset PullDistance 190
	} else {
		/varset PullAbility Melee
		/varset PullDistance 5
	}

	/call shd_load_spellbar

/return

