|- ihcbstutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub DruSetup
|-Create Alias
	/declare Aura1			string outer NULL
	/declare Aura2			string outer NULL
	
	/declare HealSpell1			string outer NULL
	/declare HealSpell2			string outer NULL
	/declare GroupHealSpell1	string outer NULL
	/declare NukeSpell1			string outer NULL
	/declare NukeSpell2			string outer NULL
	/declare DoTSpell2			string outer NULL
	/declare DoTSpell1			string outer NULL
	/declare SnareSpell			string outer NULL
	/declare Skin				string outer NULL
	/declare SoW				string outer NULL
	/declare DamageShield 		string outer NULL

	/declare GroupSkin 			string outer NULL
/return 
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges

/return
|* ------------------------------------------------------------------------------------------
| SUB: LoadSpellBar
|------------------------------------------------------------------------------------------ *|
Sub LoadSpellBar
/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar

	/call LoadSpellGem "${HealSpell1}" 1
	/call LoadSpellGem "${HealSpell2}" 2
	/call LoadSpellGem "${GroupHealSpell1}" 3

	/call LoadSpellGem "${NukeSpell1}" 4
	/call LoadSpellGem "${NukeSpell2}" 5
	/call LoadSpellGem "${DoTSpell1}" 6
	/call LoadSpellGem "${DoTSpell2}" 7
	/call LoadSpellGem "${SnareSpell}" 8
	
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: SetupSpells
|---------------------------------------------------------------------------- 
Sub SetupSpells

	/if (${Me.Level}>=${Spell[Light Healing].Level} && ${Me.Book[${Spell[Light Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Light Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Minor Healing].Level} && ${Me.Book[${Spell[Minor Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Minor Healing].RankName}
	}

	/if (${Me.Level}>=${Spell[Akalit's Feralgia].Level} && ${Me.Book[${Spell[Akalit's Feralgia].RankName}]}) {
		/varset HealSpell2 ${Spell[Akalit's Feralgia].RankName}
	}

	/if (${Me.Level}>=${Spell[Akalit's Feralgia].Level} && ${Me.Book[${Spell[Akalit's Feralgia].RankName}]}) {
		/varset GroupHealSpell1 ${Spell[Akalit's Feralgia].RankName}
	}

	/if (${Me.Level}>=${Spell[Ignite].Level} && ${Me.Book[${Spell[Ignite].RankName}]}) {
		/varset NukeSpell1 ${Spell[Ignite].RankName}
	} else /if (${Me.Level}>=${Spell[Burst of Fire].Level} && ${Me.Book[${Spell[Burst of Fire].RankName}]}) {
		/varset NukeSpell1 ${Spell[Burst of Fire].RankName}
	} else /if (${Me.Level}>=${Spell[Burst of Flame].Level} && ${Me.Book[${Spell[Burst of Flame].RankName}]}) {
		/varset NukeSpell1 ${Spell[Burst of Flame].RankName}
	}

	/if (${Me.Level}>=${Spell[Akalit's Feralgia].Level} && ${Me.Book[${Spell[Akalit's Feralgia].RankName}]}) {
		/varset NukeSpell2 ${Spell[Akalit's Feralgia].RankName}
	}

	/if (${Me.Level}>=${Spell[Flame Lick].Level} && ${Me.Book[${Spell[Flame Lick].RankName}]}) {
		/varset DoTSpell1 ${Spell[Flame Lick].RankName}
	}

	/if (${Me.Level}>=${Spell[Akalit's Feralgia].Level} && ${Me.Book[${Spell[Akalit's Feralgia].RankName}]}) {
		/varset DoTSpell2 ${Spell[Akalit's Feralgia].RankName}
	}

	
	/if (${Me.Level}>=${Spell[Ensnare].Level} && ${Me.Book[${Spell[Ensnare].RankName}]}) {
		/varset SnareSpell ${Spell[Ensnare].RankName}
	} else /if (${Me.Level}>=${Spell[Snare].Level} && ${Me.Book[${Spell[Snare].RankName}]}) {
		/varset SnareSpell ${Spell[Snare].RankName}
	}

	/if (${Me.Level}>=${Spell[Protection of Wood].Level} && ${Me.Book[${Spell[Protection of Wood].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of Wood].RankName}
	}

	/if (${Me.Level}>=${Spell[Skin like Wood].Level} && ${Me.Book[${Spell[Skin like Wood].RankName}]}) {
		/varset Skin ${Spell[Skin like Wood].RankName}
	}

	/if (${Me.Level}>=${Spell[Spirit of Wolf].Level} && ${Me.Book[${Spell[Spirit of Wolf].RankName}]}) {
		/varset SoW ${Spell[Spirit of Wolf].RankName}
	}

	/if (${Me.Level}>=${Spell[Shield of Barbs].Level} && ${Me.Book[${Spell[Shield of Barbs].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Barbs].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Thistles].Level} && ${Me.Book[${Spell[Shield of Thistles].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Thistles].RankName}
	}
	

/return
