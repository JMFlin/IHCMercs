|- ihcwarutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub ShdSetup
|-Create Alias
	|-- Toggles
|-Declare Discs
	/declare endregen		string outer NULL
	/declare Aura1			string outer NULL
	/declare Aura2			string outer NULL
|-Config Options
	/call LoadIni Item ChestItemName	string "${Me.Inventory[17].Name}"

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

|- Tank logic
	/declare TimeForMez					timer outer	0
	/declare TimeForMezVariable			int outer 0

	/if (${FindItem[Diplomatic Papers].ID}) /varset ItemDipPapers Diplomatic Papers
/return 
|----------------------------------------------------------------------------
|- SUB: CheckOptions
|---------------------------------------------------------------------------- 
Sub CheckOptions

/return
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges

/return 
|----------------------------------------------------------------------------
|- SUB: LoadSpellBar
|---------------------------------------------------------------------------- 
Sub LoadSpellBar
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar
	/call LoadSpellGem "${Touch1}" 1
	/call LoadSpellGem "${Touch2}" 2
	/call LoadSpellGem "${Terror1}" 3
	/call LoadSpellGem "${Terror2}" 4
	/call LoadSpellGem "${Bond}" 5

	/delay 2s
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub SetupSpells
	|--One off discs
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Dissident Fang].RankName}]}) {
		/varset DichotomicFang ${Spell[Dissident Fang].RankName}
	} else /if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Dichotomic Fang].RankName}]}) {
		/varset DichotomicFang ${Spell[Dichotomic Fang].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Touch of T'vem].RankName}]}) {
		/varset Touch1 ${Spell[Touch of T'vem].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Touch of T'vem].RankName}]}) {
		/varset Touch1 ${Spell[Touch of T'vem].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Lifespike].RankName}]}) {
		/varset Touch1 ${Spell[Lifespike].RankName}
	} else /if (${Me.Level}>=8 && ${Me.Book[${Spell[Lifetap].RankName}]}) {
		/varset Touch1 ${Spell[Lifetap].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Touch of Lutzen].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Lutzen].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Touch of Lutzen].RankName}]}) {
		/varset Touch2 ${Spell[Touch of Lutzen].RankName}
	} else /if (${Me.Level}>=16 && ${Me.Book[${Spell[Lifetap].RankName}]}) {
		/varset Touch2 ${Spell[Lifetap].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Touch of Falsin].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Falsin].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Touch of Falsin].RankName}]}) {
		/varset Touch3 ${Spell[Touch of Falsin].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Dire Testimony].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Testimony].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Dire Testimony].RankName}]}) {
		/varset DireTestemony ${Spell[Dire Testimony].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Terror of Kra'Du].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Kra'Du].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Terror of Kra'Du].RankName}]}) {
		/varset Terror1 ${Spell[Terror of Kra'Du].RankName}
	} 

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Terror of Narus].RankName}]}) {
		/varset Terror2 ${Spell[Terror of Narus].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Terror of Narus].RankName}]}) {
		/varset Terror2 ${Spell[Terror of Narus].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Bond of Xalgoz].RankName}]}) {
		/varset Bond ${Spell[Bond of Xalgoz].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Bond of Xalgoz].RankName}]}) {
		/varset Bond ${Spell[Bond of Xalgoz].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Insidious Denial].RankName}]}) {
		/varset Denial ${Spell[Insidious Denial].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Insidious Denial].RankName}]}) {
		/varset Denial ${Spell[Insidious Denial].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Hateful Bargain].RankName}]}) {
		/varset Bargain ${Spell[Hateful Bargain].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Hateful Bargain].RankName}]}) {
		/varset Bargain ${Spell[Hateful Bargain].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Tylix's Skin].RankName}]}) {
		/varset Skin ${Spell[Tylix's Skin].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Tylix's Skin].RankName}]}) {
		/varset Skin ${Spell[Tylix's Skin].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Defiant Stance].RankName}]}) {
		/varset Stance ${Spell[Defiant Stance].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Defiant Stance].RankName}]}) {
		/varset Stance ${Spell[Defiant Stance].RankName}
	}

	/if (${Me.Level}>=20 && ${Me.CombatAbility[${Touch1}]}) {
		/varset PullAbility ${Touch1}
		/varset PullDistance 190
	} else {
		/varset PullAbility Melee
		/varset PullDistance 5
	}

/return