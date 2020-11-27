|- ihcmnkutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub mnk_setup
|-Create Alias's
|-Declare AA's and Discs
	/declare endregen				string outer NULL
	/declare mnkaura				string outer NULL
	/declare DichoSpell				string outer NULL
	/declare Drunken				string outer NULL
	/declare Curse					string outer NULL
	/declare Fang					string outer NULL
	/declare Fists					string outer NULL
	/declare Precision				string outer NULL
	/declare Shuriken				string outer NULL
	/declare Crane					string outer NULL
	/declare Synergy				string outer NULL
	/declare Alliance				string outer NULL
	/declare Storm					string outer NULL
	/declare Aura1			string outer NULL
	/declare Aura2			string outer NULL
	/declare Aura1Name string outer NULL
	/declare Aura2Name string outer NULL
	/declare PosseSpell				string 	outer 	Origin
	

|-Defensives
	/declare EarthForce				string outer NULL
	/declare ShadedStep				string outer NULL
	/declare RejectDeath			string outer NULL
	
|-Declare Main discs
	/declare Iron					string outer NULL	
	/declare Heel					string outer NULL
	/declare Speed					string outer NULL
	/declare Palm					string outer NULL
	/declare Poise 					string outer NULL
	/declare ChestItemName				string outer "${Me.Inventory[17].Name}"
	/declare CastResult             	string outer
	/declare PullTowards 	string outer NULL

|-Config Options
|- Check for epic
	
/return 
|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub mnk_abilities

	/if (${Me.AltAbilityReady[Moving Mountains]}) {
		/varset PullTowards Moving Mountains
	}
	

	/if (${Me.AltAbilityReady[Distant Strike]}) {
		/varset pullAbility Distant Strike
		/varset pullDistance 150
	} else {
		/varset pullAbility ${Spell[Throw Stone].RankName}
		/varset pullDistance 55
	}
|--RejectDeath line
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Reject Death].RankName}]}) {
		/varset RejectDeath ${Spell[Reject Death].RankName}
	}
|--Earthforce line
	/if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Earthforce Discipline].RankName}]}) {
		/varset EarthForce ${Spell[Earthforce Discipline].RankName}
	}
|--ShadedStep line
	/if (${Me.Level}>=97 && ${Me.CombatAbility[${Spell[Shaded Step].RankName}]}) {
		/varset ShadedStep ${Spell[Shaded Step].RankName}
	}
|---Strom line
	/if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Eye of the Storm].RankName}]}) {
		/varset Storm ${Spell[Eye of the Storm].RankName}
	}
|---Alliance line
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Firewalker's Covenant].RankName}]}) {
		/varset Alliance ${Spell[Firewalker's Covenant].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Doomwalker's Alliance].RankName}]}) {
		/varset Alliance ${Spell[Doomwalker's Alliance].RankName}
	}
|---Synergy Line
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Firewalker's Synergy].RankName}]}) {
		/varset Synergy ${Spell[Firewalker's Synergy].RankName}
	}
|---DM Line
	/if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Drunken Monkey Style].RankName}]}) {
		/varset Drunken ${Spell[Drunken Monkey Style].RankName}
	} 
|---Curse Line
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Curse of Fourteen Fists].RankName}]}) {
		/varset Curse ${Spell[Curse of Fourteen Fists].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Curse of the Thirteen Fingers].RankName}]}) {
		/varset Curse ${Spell[Curse of the Thirteen Fingers].RankName}
	} 
|---Fang Line
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Hoshkar's Fang].RankName}]}) {
		/varset Fang ${Spell[Hoshkar's Fang].RankName}
	} 
|---Fists Line
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Firestorm of Fists].RankName}]}) {
		/varset Fists ${Spell[Firestorm of Fists].RankName}
	}
|---Precision Line
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Firewalker's Precision Strike].RankName}]}) {
		/varset Precision ${Spell[Firewalker's Precision Strike].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Doomwalker's Precision Strike].RankName}]}) {
		/varset Precision ${Spell[Doomwalker's Precision Strike].RankName}
	}
|---Shuriken Line
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Vigorous Shuriken].RankName}]}) {
		/varset Shuriken ${Spell[Vigorous Shuriken].RankName}
	} 
|---Crane Line
	/if (${Me.Level}>=93 && ${Me.CombatAbility[${Spell[Crane Stance].RankName}]}) {
		/varset Crane ${Spell[Crane Stance].RankName}
	} 
|-Dicho Spell*
	/if (${Me.Level}>=${Spell[Dissident Form].Level} && ${Me.CombatAbility[${Spell[Dissident Form].RankName}]}) {
		/varset DichoSpell ${Spell[Dissident Form].RankName}
	} else /if (${Me.Level}>=${Spell[Dichotomic Form].Level} && ${Me.CombatAbility[${Spell[Dichotomic Form].RankName}]}) {
		/varset DichoSpell ${Spell[Dichotomic Form].RankName}
	}
|---Fast Endurance regen - No Update
	/if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Breather].RankName}]}) {
		/varset endregen ${Spell[Breather].RankName}
	} else /if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Rest].RankName}]}) {
		/varset endregen ${Spell[Rest].RankName}
	} else /if (${Me.Level}>=91 && ${Me.CombatAbility[${Spell[Reprieve].RankName}]}) {
		/varset endregen ${Spell[Reprieve].RankName}
	} else /if (${Me.Level}>=86 && ${Me.CombatAbility[${Spell[Respite].RankName}]}) {
		/varset endregen ${Spell[Respite].RankName}
	} else /if (${Me.Level}>=82 && ${Me.CombatAbility[${Spell[Fourth Wind].RankName}]}) {
		/varset endregen ${Spell[Fourth Wind].RankName}
	} else /if (${Me.Level}>=77 && ${Me.CombatAbility[${Spell[Third Wind].RankName}]}) {
		/varset endregen ${Spell[Third Wind].RankName}
	} else /if (${Me.Level}>=72 && ${Me.CombatAbility[${Spell[Second Wind].RankName}]}) {
		/varset endregen ${Spell[Second Wind].RankName}
	}
|-Aura Set up	
	/if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Master's Aura].RankName}]}) {
		/varset Aura1 ${Spell[Master's Aura].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Disciple's Aura].RankName}]}) {
		/varset Aura1 ${Spell[Disciple's Aura].RankName}
	}

|-Ironfist line
	/if (${Me.Level}>=88 && ${Me.CombatAbility[${Spell[Ironfist Discipline].RankName}]}) {
		/varset Iron ${Spell[Ironfist Discipline].RankName}
	}

|-Heel line
	/if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Heel of Zagali].RankName}]}) {
		/varset Heel ${Spell[Heel of Zagali].RankName}
	}

|-Speed line
	/if (${Me.Level}>=63 && ${Me.CombatAbility[${Spell[Speed Focus Discipline].RankName}]}) {
		/varset Speed ${Spell[Speed Focus Discipline].RankName}
	}

|-Palm line
	/if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Terrorpalm Discipline].RankName}]}) {
		/varset Palm ${Spell[Terrorpalm Discipline].RankName}
	}

|-Tiger's Poise line
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Tiger's Poise].RankName}]}) {
		/varset Poise ${Spell[Tiger's Poise].RankName}
	}
	
/return
