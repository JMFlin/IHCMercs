|- ihcwizutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|- Thanks to Saar for additions and bug fixes
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub wiz_setup
|-Declare AA and Spell variables
  |-Buffs
	/declare SelfHPBuff				string	outer	NULL
	/declare ACPyromancy			string	outer	NULL
	/declare FamiliarBuff			string	outer	NULL
	/declare SelfRune1				string	outer	NULL
  |-Debuff
	/declare StripBuffSpell			string	outer	NULL
  |-DPS
  	/declare Aura1					string outer NULL
	/declare Aura2					string outer NULL
	/declare AllianceSpell			string	outer	NULL
	/declare AllianceSpellRankCheck string 	outer 	NULL
	/declare DichoSpell				string 	outer	NULL
	/declare ClawNuke				string 	outer	NULL
	/declare CloudburstNuke			string 	outer	NULL
	/declare BraidNuke				string 	outer	NULL
	/declare FireEtherealNuke		string 	outer	NULL
	/declare MagmaticAENuke			string 	outer	NULL
	/declare ChaosNuke				string 	outer	NULL
	/declare VortexNuke				string 	outer	NULL
	/declare TwincastSpell			string 	outer	NULL
	/declare ColdEtherealNuke		string 	outer	NULL
	/declare GambitSpell			string 	outer	NULL
	/declare WildNuke				string 	outer	NULL
	/declare LowerWildNuke 			string 	outer 	NULL
	/declare FastNuke1				string 	outer	NULL
	/declare GeneralNuke1			string 	outer	NULL
  |-Pet
	/declare PetSpell				string	outer	NULL
	/declare PetAssistTimer			timer 	outer	0
  |-Utility
	/declare RootSpell				string	outer	NULL 
	/declare SnareSpell				string	outer	NULL
	/declare EvacSpell				string	outer	NULL
	/declare HarvestSpell1			string 	outer	NULL
	/declare StunSpell				string 	outer	NULL
	/declare JoltSpell				string 	outer	NULL
	/declare RuneGuardSpell 		string  outer 	NULL
	
	/declare SpellSet				string outer auto
	/declare CastResult             string outer

	/declare PosseSpell				string outer NULL

	/declare GoMNuke				string outer NULL
	/declare GoMNuke2				string outer NULL
	/declare ChestItemName			string outer ${Me.Inventory[17].Name}
	/declare ImprovedTwincastRank		string outer NULL
/return
|* ------------------------------------------------------------------------------------------
| SUB: load_spellbar
|------------------------------------------------------------------------------------------ *|
Sub wiz_load_spellbar
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar

	/if (${Me.AltAbility[Mnemonic Retention].Rank} == 5) {
		/call LoadSpellGem "${ClawNuke}" 1
		/call LoadSpellGem "${CloudburstNuke}" 2
		/call LoadSpellGem "${ColdEtherealNuke}" 3

		/call LoadSpellGem "${FireEtherealNuke}" 4
		/call LoadSpellGem "${BraidNuke}" 5

		/call LoadSpellGem "${TwincastSpell}" 6
		/call LoadSpellGem "${DichoSpell}" 7
		/call LoadSpellGem "${VortexNuke}" 8
		/call LoadSpellGem "${JoltSpell}" 9

		/call LoadSpellGem "${AllianceSpell}" 10
		|/call LoadSpellGem "${}" 11
		/call LoadSpellGem "${HarvestSpell1}" 12

		/call LoadSpellGem "${GambitSpell}" 13

	} else /if (${Me.AltAbility[Mnemonic Retention].Rank} == 4) {

		/call LoadSpellGem "${ClawNuke}" 1
		/call LoadSpellGem "${CloudburstNuke}" 2
		/call LoadSpellGem "${ColdEtherealNuke}" 3

		/call LoadSpellGem "${FireEtherealNuke}" 4
		/call LoadSpellGem "${BraidNuke}" 5

		/call LoadSpellGem "${TwincastSpell}" 6
		/call LoadSpellGem "${DichoSpell}" 7
		/call LoadSpellGem "${VortexNuke}" 8
		|/call LoadSpellGem "${}" 9

		/call LoadSpellGem "${AllianceSpell}" 10
		/call LoadSpellGem "${GambitSpell}" 11
		/call LoadSpellGem "${HarvestSpell1}" 12

	} else {
		
		/call LoadSpellGem "${ClawNuke}" 1
		/call LoadSpellGem "${CloudburstNuke}" 2
		/call LoadSpellGem "${ColdEtherealNuke}" 3
		/call LoadSpellGem "${FireEtherealNuke}" 4
		/call LoadSpellGem "${BraidNuke}" 5
		/call LoadSpellGem "${TwincastSpell}" 6
		/call LoadSpellGem "${JoltSpell}" 7
		/call LoadSpellGem "${HarvestSpell1}" 8

	}

	/delay 2s
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|* ------------------------------------------------------------------------------------------
| SUB: SetWizSpells
|------------------------------------------------------------------------------------------ *|
Sub wiz_abilities

	/if (${Me.Level} >= ${Spell[Knowledge Portal].Level} && ${Me.Book[${Spell[Knowledge Portal].RankName}]}) {
		/varset PosseSpell ${Spell[Knowledge Portal].RankName}
	}
	
	/if (${Me.AltAbility[Improved Twincast].Rank} == 12) {
		/varset ImprovedTwincastRank VI
	} else /if (${Me.AltAbility[Improved Twincast].Rank} == 13) {
		/varset ImprovedTwincastRank VII
	} else /if (${Me.AltAbility[Improved Twincast].Rank} == 14) {
		/varset ImprovedTwincastRank VIII
	} else /if (${Me.AltAbility[Improved Twincast].Rank} == 15) {
		/varset ImprovedTwincastRank VIII
	} else /if (${Me.AltAbility[Improved Twincast].Rank} == 16) {
		/varset ImprovedTwincastRank X
	}

|-Familiar Buff
	/if (${Me.AltAbility[Improved Familiar].Rank} >= 1) {
		/varset FamiliarBuff Improved Familiar
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Greater Familiar].RankName}]}) {
		/varset FamiliarBuff ${Spell[Greater Familiar].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Familiar].RankName}]}) {
		/varset FamiliarBuff ${Spell[Familiar].RankName}
	} else /if (${Me.Level}>=45 && ${Me.Book[${Spell[Lesser Familiar].RankName}]}) {
		/varset FamiliarBuff ${Spell[Lesser Familiar].RankName}
	} else /if (${Me.Level}>=25 && ${Me.Book[${Spell[Minor Familiar].RankName}]}) {
		/varset FamiliarBuff ${Spell[Minor Familiar].RankName}
	}
|-Self HP Buff * Var Name: SelfHPBuff string outer
	/if (${Me.AltAbility[Etherealist's Unity].Rank} >= 1) {
		/varset SelfHPBuff Etherealist's Unity
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Shield of Scales].RankName}]}) {
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
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Bulwark of the Crystalwing].RankName}]}) {
		/varset SelfHPBuff ${Spell[Bulwark of the Crystalwing].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Shield of the Crystalwing].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Crystalwing].RankName}
	} else /if (${Me.Level}>=66 && ${Me.Book[${Spell[Ether Shield].RankName}]}) {
		/varset SelfHPBuff ${Spell[Ether Shield].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Shield of Maelin].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of Maelin].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Shield of the Arcane].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Arcane].RankName}
	} else /if (${Me.Level}>=54 && ${Me.Book[${Spell[Shield of the Magi].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shield of the Magi].RankName}
	} else /if (${Me.Level}>=44 && ${Me.Book[${Spell[Arch Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Arch Shielding].RankName}
	} else /if (${Me.Level}>=33 && ${Me.Book[${Spell[Greater Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Greater Shielding].RankName}
	} else /if (${Me.Level}>=23 && ${Me.Book[${Spell[Major Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Major Shielding].RankName}
	} else /if (${Me.Level}>=15 && ${Me.Book[${Spell[Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Shielding].RankName}
	} else /if (${Me.Level}>=6 && ${Me.Book[${Spell[Lesser Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Lesser Shielding].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Minor Shielding].RankName}]}) {
		/varset SelfHPBuff ${Spell[Minor Shielding].RankName}
	}

	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Shield of Scales].RankName}]}) {
		/varset SelfHPBuffName "Shield of Scales"
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Shield of the Pellarus].RankName}]}) {
		/varset SelfHPBuffName "Shield of the Pellarus"
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Shield of the Dauntless].RankName}]}) {
		/varset SelfHPBuffName "Shield of the Dauntless"
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Shield of Bronze].RankName}]}) {
		/varset SelfHPBuffName "Shield of Bronze"
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Shield of Dreams].RankName}]}) {
		/varset SelfHPBuffName "Shield of Dreams"
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Shield of the Void].RankName}]}) {
		/varset SelfHPBuffName "Shield of the Void"
	}
|-Self Rune 1 * Var Name: SelfRune1 string outer
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Armor of Wirn].RankName}]}) {
		/varset SelfRune1 ${Spell[Armor of Wirn].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Armor of the Codex].RankName}]}) {
		/varset SelfRune1 ${Spell[Armor of the Codex].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Armor of the Stonescale].RankName}]}) {
		/varset SelfRune1 ${Spell[Armor of the Stonescale].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Armor of the Crystalwing].RankName}]}) {
		/varset SelfRune1 ${Spell[Armor of the Crystalwing].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Dermis of the Crystalwing].RankName}]}) {
		/varset SelfRune1 ${Spell[Dermis of the Crystalwing].RankName}
	} else /if (${Me.Level}>=83 && ${Me.Book[${Spell[Squamae of the Crystalwing].RankName}]}) {
		/varset SelfRune1 ${Spell[Squamae of the Crystalwing].RankName}
	} else /if (${Me.Level}>=78 && ${Me.Book[${Spell[Laminae of the Crystalwing].RankName}]}) {
		/varset SelfRune1 ${Spell[Laminae of the Crystalwing].RankName}
	} else /if (${Me.Level}>=73 && ${Me.Book[${Spell[Scales of the Crystalwing].RankName}]}) {
		/varset SelfRune1 ${Spell[Scales of the Crystalwing].RankName}
	} else /if (${Me.Level}>=68 && ${Me.Book[${Spell[Ether Skin].RankName}]}) {
		/varset SelfRune1 ${Spell[Ether Skin].RankName}
	} else /if (${Me.Level}>=63 && ${Me.Book[${Spell[Force Shield].RankName}]}) {
		/varset SelfRune1 ${Spell[Force Shield].RankName}
	}
|-StripBuffSpell
	/if (${Me.Level}>=100 && ${Me.AltAbilityReady[Eradicate Magic]}) {
		/varset StripBuffSpell Eradicate Magic
	} else /if (${Me.Level}>=53 && ${Me.Book[${Spell[Annul Magic].RankName}]}) {
		/varset StripBuffSpell ${Spell[Annul Magic].RankName}
	} else /if (${Me.Level}>=34 && ${Me.Book[${Spell[Nullify Magic].RankName}]}) {
		/varset StripBuffSpell ${Spell[Nullify Magic].RankName}
	} else /if (${Me.Level}>=11 && ${Me.Book[${Spell[Cancel Magic].RankName}]}) {
		/varset StripBuffSpell ${Spell[Cancel Magic].RankName}
	}
|-AllianceSpell
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Frostbound Covenant].RankName}]}) {
		/varset AllianceSpell ${Spell[Frostbound Covenant].RankName}
		/varset AllianceSpellRankCheck ${Spell[Frostbound Covenant]}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Frostbound Alliance].RankName}]}) {
		/varset AllianceSpell ${Spell[Frostbound Alliance].RankName}
		/varset AllianceSpellRankCheck ${Spell[Frostbound Alliance]}
	}
|-DichoSpell
/if (${Me.Level}>=106 && ${Me.Book[${Spell[Dissident Fire].RankName}]}) {
		/varset DichoSpell ${Spell[Dissident Fire].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Dichotomic Fire].RankName}]}) {
		/varset DichoSpell ${Spell[Dichotomic Fire].RankName}
	}
|-Root Spell * Var Name: RootSpell string outer
	/if (${Me.Level}>=61 && ${Me.Book[${Spell[Greater Fetter].RankName}]}) {
		/varset RootSpell ${Spell[Greater Fetter].RankName}
	} else /if (${Me.Level}>=58 && ${Me.Book[${Spell[Fetter].RankName}]}) {
		/varset RootSpell ${Spell[Fetter].RankName}
	} else /if (${Me.Level}>=48 && ${Me.Book[${Spell[Paralyzing Earth].RankName}]}) {
		/varset RootSpell ${Spell[Paralyzing Earth].RankName}
	} else /if (${Me.Level}>=39 && ${Me.Book[${Spell[Immobilize].RankName}]}) {
		/varset RootSpell ${Spell[Immobilize].RankName}
	} else /if (${Me.Level}>=17 && ${Me.Book[${Spell[Instill].RankName}]}) {
		/varset RootSpell ${Spell[Instill].RankName}
	} else /if (${Me.Level}>=3 && ${Me.Book[${Spell[Root].RankName}]}) {
		/varset RootSpell ${Spell[Root].RankName}
	}
|-TwincastSpell
	/if (${Me.Level}>=85 && ${Me.Book[${Spell[Twincast].RankName}]}) {
		/varset TwincastSpell ${Spell[Twincast].RankName}
	}
|-SnareSpell
	/if (${Me.AltAbility[Atol's Shackles].Rank} >= 1) {
		/varset SnareSpell Atol's Shackles
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Atol's Concussive Shackles].RankName}]}) {
		/varset SnareSpell ${Spell[Atol's Concussive Shackles].RankName}
	} else /if (${Me.Level}>=51 && ${Me.Book[${Spell[Atol's Spectral Shackles].RankName}]}) {
		/varset SnareSpell ${Spell[Atol's Spectral Shackles].RankName}
	} else /if (${Me.Level}>=27 && ${Me.Book[${Spell[Bonds of Force].RankName}]}) {
		/varset SnareSpell ${Spell[Bonds of Force].RankName}
	}	
|-JoltSpell
	/if (${Me.AltAbility[Concussion].Rank} >= 1) {
		/varset JoltSpell Concussion
	} else /if (${Me.Level}>=106 && ${Me.Book[${Spell[Concussive Volley].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Volley].RankName}
	} else /if (${Me.Level}>=101 && ${Me.Book[${Spell[Concussive Storm].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Storm].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Concussive Salvo].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Salvo].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Concussive Barrage].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Barrage].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Concussive Burst].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Burst].RankName}
	} else /if (${Me.Level}>=81 && ${Me.Book[${Spell[Concussive Flash].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Flash].RankName}
	} else /if (${Me.Level}>=76 && ${Me.Book[${Spell[Concussive Burst].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Burst].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Concussive Blast].RankName}]}) {
		/varset JoltSpell ${Spell[Concussive Blast].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Ancient Greater Concussion].RankName}]}) {
		/varset JoltSpell ${Spell[Ancient Greater Concussion].RankName}
	} else /if (${Me.Level}>=37 && ${Me.Book[${Spell[Concussion].RankName}]}) {
		/varset JoltSpell ${Spell[Concussion].RankName}
	}
|-HarvestSpell
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Musing Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Musing Harvest].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Quiescent Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Quiescent Harvest].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Bucolic Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Bucolic Harvest].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Placid Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Placid Harvest].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Soothing Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Soothing Harvest].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Serene Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Serene Harvest].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Tranquil Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Tranquil Harvest].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Patient Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Patient Harvest].RankName}
	} else /if (${Me.Level}>=32 && ${Me.Book[${Spell[Harvest].RankName}]}) {
		/varset HarvestSpell1 ${Spell[Harvest].RankName}
	}
|-GambitSpell
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Musing Gambit].RankName}]}) {
		/varset GambitSpell ${Spell[Musing Gambit].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Quiescent Gambit].RankName}]}) {
		/varset GambitSpell ${Spell[Quiescent Gambit].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Bucolic Gambit].RankName}]}) {
		/varset GambitSpell ${Spell[Bucolic Gambit].RankName}
	}	
|-PetSpell
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Virnax's Pyroblade].RankName}]}) {
		/varset PetSpell ${Spell[Virnax's Pyroblade].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Yulin's Pyroblade].RankName}]}) {
		/varset PetSpell ${Spell[Yulin's Pyroblade].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Mul's Pyroblade].RankName}]}) {
		/varset PetSpell ${Spell[Mul's Pyroblade].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Burnmaster's Pyroblade].RankName}]}) {
		/varset PetSpell ${Spell[Burnmaster's Pyroblade].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Lithara's Pyroblade].RankName}]}) {
		/varset PetSpell ${Spell[Lithara's Pyroblade].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Daveron's Pyroblade].RankName}]}) {
		/varset PetSpell ${Spell[Daveron's Pyroblade].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Euthanos' Flameblade].RankName}]}) {
		/varset PetSpell ${Spell[Euthanos' Flameblade].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Ethantis's Burning Blade].RankName}]}) {
		/varset PetSpell ${Spell[Ethantis's Burning Blade].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Solist's Frozen Sword].RankName}]}) {
		/varset PetSpell ${Spell[Solist's Frozen Sword].RankName}
	} else /if (${Me.Level}>=59 && ${Me.Book[${Spell[Flaming Sword of Xuzl].RankName}]}) {
		/varset PetSpell ${Spell[Flaming Sword of Xuzl].RankName}
	}
|-ClawNuke
|- ${SpellSet.Equal[cold]}
	/if (${Me.Level}>=${Spell[Claw of Travenro].Level} && ${Me.Book[${Spell[Claw of Travenro].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Travenro].RankName}
	} else /if (${Me.Level}>=${Spell[Claw of Qunard].Level} && ${Me.Book[${Spell[Claw of Qunard].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Qunard].RankName}
	} else /if (${Me.Level}>=${Spell[Claw of Ellarr].Level} && ${Me.Book[${Spell[Claw of Ellarr].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Ellarr].RankName}
	} else /if (${Me.Level}>=${Spell[Claw of the Oceanlord].Level} && ${Me.Book[${Spell[Claw of the Oceanlord].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Oceanlord].RankName}
	} else /if (${Me.Level}>=${Spell[Claw of the Flameweaver].Level} && ${Me.Book[${Spell[Claw of the Flameweaver].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Flameweaver].RankName}
	} else /if (${Me.Level}>=${Spell[Claw of the Indagatori].Level} && ${Me.Book[${Spell[Claw of the Indagatori].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Indagatori].RankName}
	} else /if (${Me.Level}>=${Spell[Claw of the Icewing].Level} && ${Me.Book[${Spell[Claw of the Icewing].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Icewing].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Claw of the Flamewing].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Flamewing].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Claw of the Ashwing].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Ashwing].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Claw of the Abyss].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of the Abyss].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Glacial Claw].RankName}]}) {
		/varset ClawNuke ${Spell[Glacial Claw].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Claw of Gorenaire].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Gorenaire].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Claw of Selig].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Selig].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Claw of Selay].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Selay].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Claw of Vox].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Vox].RankName}
	} else /if (${Me.Level}>=61 && ${Me.Book[${Spell[Claw of Frost].RankName}]}) {
		/varset ClawNuke ${Spell[Claw of Frost].RankName}
	}
|-CloudburstNuke
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Cloudburst Thunderbolt].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Thunderbolt].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Cloudburst Stormstrike].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Stormstrike].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Cloudburst Thunderbolt].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Thunderbolt].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Cloudburst Tempest].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Tempest].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Cloudburst Storm].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Storm].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Cloudburst Levin].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Levin].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Cloudburst Bolts].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Bolts].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Cloudburst Strike].RankName}]}) {
		/varset CloudburstNuke ${Spell[Cloudburst Strike].RankName}
	} 

|-BraidNuke
	/if (${Me.Level}>=${Spell[Ethereal Confluence].Level} && ${Me.Book[${Spell[Ethereal Confluence].RankName}]}) {
		/varset BraidNuke ${Spell[Ethereal Confluence].RankName}
	} else /if (${Me.Level}>=${Spell[Ethereal Braid].Level} && ${Me.Book[${Spell[Ethereal Braid].RankName}]}) {
		/varset BraidNuke ${Spell[Ethereal Braid].RankName}
	} else /if (${Me.Level}>=${Spell[Ethereal Fuse].Level} && ${Me.Book[${Spell[Ethereal Fuse].RankName}]}) {
		/varset BraidNuke ${Spell[Ethereal Fuse].RankName}
	} else /if (${Me.Level}>=${Spell[Ethereal Weave].Level} && ${Me.Book[${Spell[Ethereal Weave].RankName}]}) {
		/varset BraidNuke ${Spell[Ethereal Weave].RankName}
	}
|-WildNuke: Kizant uses Wildether barrage and wild spark barrage in TBL with fury of gods
	/if (${Me.Level}>=${Spell[Wildflash Strike].Level} && ${Me.Book[${Spell[Wildflash Strike].RankName}]}) {
		/varset WildNuke ${Spell[Wildflash Strike].RankName}
		/varset LowerWildNuke ${Spell[Wildflash Barrage].RankName}
	} else /if (${Me.Level}>=${Spell[Wildflash Barrage].Level} && ${Me.Book[${Spell[Wildflash Barrage].RankName}]}) {
		/varset WildNuke ${Spell[Wildflash Barrage].RankName}
		/varset LowerWildNuke ${Spell[Wildether Barrage].RankName}
	} else /if (${Me.Level}>=${Spell[Wildether Barrage].Level} && ${Me.Book[${Spell[Wildether Barrage].RankName}]}) {
		/varset WildNuke ${Spell[Wildether Barrage].RankName}
		/varset LowerWildNuke ${Spell[Wildspark Barrage].RankName}
	} else /if (${Me.Level}>=${Spell[Wildspark Barrage].Level} && ${Me.Book[${Spell[Wildspark Barrage].RankName}]}) {
		/varset WildNuke ${Spell[Wildspark Barrage].RankName}
		/varset LowerWildNuke ${Spell[Wildmana Barrage].RankName}
	} else /if (${Me.Level}>=${Spell[Wildmana Barrage].Level} && ${Me.Book[${Spell[Wildmana Barrage].RankName}]}) {
		/varset WildNuke ${Spell[Wildmana Barrage].RankName}
		/varset LowerWildNuke ${Spell[Wildmagic Blast].RankName}
	} else /if (${Me.Level}>=${Spell[Wildmagic Blast].Level} && ${Me.Book[${Spell[Wildmagic Blast].RankName}]}) {
		/varset WildNuke ${Spell[Wildmagic Blast].RankName}
		/varset LowerWildNuke ${Spell[Wildmagic Burst].RankName}
	} else /if (${Me.Level}>=${Spell[Wildmagic Burst].Level} && ${Me.Book[${Spell[Wildmagic Burst].RankName}]}) {
		/varset WildNuke ${Spell[Wildmagic Burst].RankName}
		/varset LowerWildNuke ${Spell[Wildmagic Strike].RankName}
	} else /if (${Me.Level}>=${Spell[Wildmagic Strike].Level} && ${Me.Book[${Spell[Wildmagic Strike].RankName}]}) {
		/varset WildNuke ${Spell[Wildmagic Strike].RankName}
	}


|-VortexNuke
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Stormjolt Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Stormjolt Vortex].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Shocking Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Shocking Vortex].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Hoarfrost Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Hoarfrost Vortex].RankName}
	} else /if (${Me.Level}>=98 && ${Me.Book[${Spell[Ether Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Ether Vortex].RankName}
	} else /if (${Me.Level}>=96 && ${Me.Book[${Spell[Incandescent Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Incandescent Vortex].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Frost Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Frost Vortex].RankName}
	} else /if (${Me.Level}>=93 && ${Me.Book[${Spell[Power Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Power Vortex].RankName}
	} else /if (${Me.Level}>=91 && ${Me.Book[${Spell[Flame Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Flame Vortex].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Ice Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Ice Vortex].RankName}
	} else /if (${Me.Level}>=88 && ${Me.Book[${Spell[Mana Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Mana Vortex].RankName}
	} else /if (${Me.Level}>=86 && ${Me.Book[${Spell[Fire Vortex].RankName}]}) {
		/varset VortexNuke ${Spell[Fire Vortex].RankName}
	}	
|-ChaosNuke
	/if (${Me.Level}>=108 && ${Me.Book[${Spell[Chaos Burn].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Burn].RankName}
	} else /if (${Me.Level}>=103 && ${Me.Book[${Spell[Chaos Scintillation].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Scintillation].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Chaos Incandescence].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Incandescence].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Chaos Blaze].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Blaze].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Chaos Char].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Char].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Chaos Conflagration].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Conflagration].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Chaos Immolation].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Immolation].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Chaos Flame].RankName}]}) {
		/varset ChaosNuke ${Spell[Chaos Flame].RankName}
	}
|-MagmaticAENuke
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Magmatic Explosion].RankName}]}) {
		/varset MagmaticAENuke ${Spell[Magmatic Explosion].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Magmatic Burst].RankName}]}) {
		/varset MagmaticAENuke ${Spell[Magmatic Burst].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Magmatic Vent].RankName}]}) {
		/varset MagmaticAENuke ${Spell[Magmatic Vent].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Magmatic Outburst].RankName}]}) {
		/varset MagmaticAENuke ${Spell[Magmatic Outburst].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Magmatic Downpour].RankName}]}) {
		/varset MagmaticAENuke ${Spell[Magmatic Downpour].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Magmatic Eruption].RankName}]}) {
		/varset MagmaticAENuke ${Spell[Magmatic Eruption].RankName}
	}	
|-FireEtherealNuke
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Ethereal Skyfire].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Skyfire].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Ethereal Skyblaze].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Skyblaze].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Ethereal Incandescence].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Incandescence].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Ethereal Blaze].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Blaze].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Ethereal Inferno].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Inferno].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Ethereal Combustion].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Combustion].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Ethereal Incineration].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Incineration].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Ethereal Conflagration].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ethereal Conflagration].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Ether Flame].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Ether Flame].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[White Fire].RankName}]}) {
		/varset FireEtherealNuke ${Spell[White Fire].RankName}
	} else /if (${Me.Level}>=60 && ${Me.Book[${Spell[Sunstrike].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Sunstrike].RankName}
	} else /if (${Me.Level}>=51 && ${Me.Book[${Spell[Draught of Fire].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Draught of Fire].RankName}
	} else /if (${Me.Level}>=43 && ${Me.Book[${Spell[Conflagration].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Conflagration].RankName}
	} else /if (${Me.Level}>=24 && ${Me.Book[${Spell[Inferno Shock].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Inferno Shock].RankName}
	} else /if (${Me.Level}>=15 && ${Me.Book[${Spell[Flame Shock].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Flame Shock].RankName}
	} else /if (${Me.Level}>=5 && ${Me.Book[${Spell[Fire Bolt].RankName}]}) {
		/varset FireEtherealNuke ${Spell[Fire Bolt].RankName}
	} 

|-ColdEtherealNuke
	/if (${Me.Level}>=109 && ${Me.Book[${Spell[Ethereal Icefloe].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Icefloe].RankName}
	} else /if (${Me.Level}>=104 && ${Me.Book[${Spell[Ethereal Rimeblast].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Rimeblast].RankName}
	} else /if (${Me.Level}>=99 && ${Me.Book[${Spell[Ethereal Hoarfrost].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Hoarfrost].RankName}
	} else /if (${Me.Level}>=94 && ${Me.Book[${Spell[Ethereal Frost].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Frost].RankName}
	} else /if (${Me.Level}>=89 && ${Me.Book[${Spell[Ethereal Glaciation].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Glaciation].RankName}
	} else /if (${Me.Level}>=84 && ${Me.Book[${Spell[Ethereal Iceblight].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Iceblight].RankName}
	} else /if (${Me.Level}>=79 && ${Me.Book[${Spell[Ethereal Rime].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ethereal Rime].RankName}
	} else /if (${Me.Level}>=74 && ${Me.Book[${Spell[Icefall Avalanche].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Icefall Avalanche].RankName}
	} else /if (${Me.Level}>=71 && ${Me.Book[${Spell[Rimelure].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Rimelure].RankName}
	} else /if (${Me.Level}>=69 && ${Me.Book[${Spell[Gelidin Comet].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Gelidin Comet].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Black Ice].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Black Ice].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Ice Meteor].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ice Meteor].RankName}
	} else /if (${Me.Level}>=49 && ${Me.Book[${Spell[Ice Comet].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Ice Comet].RankName}
	} else /if (${Me.Level}>=24 && ${Me.Book[${Spell[Frost Shock].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Frost Shock].RankName}
	} else /if (${Me.Level}>=8 && ${Me.Book[${Spell[Shock of Ice].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Shock of Ice].RankName}
	} else /if (${Me.Level}>=1 && ${Me.Book[${Spell[Blast of Cold].RankName}]}) {
		/varset ColdEtherealNuke ${Spell[Blast of Cold].RankName}
	}

	| This is for using Ice Comet line during lower levels of play before having access to Fuse. 
	| This keeps the weave correct in combatdps. 
	/if (!${Me.Book[${BraidNuke}]}) {
		/varset BraidNuke ${ColdEtherealNuke}
	}

	/if (${Me.Level}>=83 && ${Me.Book[${Spell[Nethermist Guard].RankName}]}) {
		/varset RuneGuardSpell ${Spell[Nethermist Guard].RankName}
	} 

|-EvacSpell
	/if (${Me.Level}>=57 && ${Me.Book[${Spell[Evacuate].RankName}]}) {
		/varset EvacSpell ${Spell[Evacuate].RankName}
	} else /if (${Me.Level}>=18 && ${Me.Book[${Spell[Lesser Evacuate].RankName}]}) {
		/varset EvacSpell ${Spell[Lesser Evacuate].RankName}
	}
|-StunSpell
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Telanata].RankName}]}) {
		/varset StunSpell ${Spell[Telanata].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Telanara].RankName}]}) {
		/varset StunSpell ${Spell[Telanara].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Telanaga].RankName}]}) {
		/varset StunSpell ${Spell[Telanaga].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Telanama].RankName}]}) {
		/varset StunSpell ${Spell[Telanama].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Telakama].RankName}]}) {
		/varset StunSpell ${Spell[Telakama].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Telajara].RankName}]}) {
		/varset StunSpell ${Spell[Telajara].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Telajasz].RankName}]}) {
		/varset StunSpell ${Spell[Telajasz].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Telakisz].RankName}]}) {
		/varset StunSpell ${Spell[Telakisz].RankName}
	} else /if (${Me.Level}>=70 && ${Me.Book[${Spell[Telekara].RankName}]}) {
		/varset StunSpell ${Spell[Telekara].RankName}
	} else /if (${Me.Level}>=65 && ${Me.Book[${Spell[Telaka].RankName}]}) {
		/varset StunSpell ${Spell[Telaka].RankName}
	} else /if (${Me.Level}>=64 && ${Me.Book[${Spell[Telekin].RankName}]}) {
		/varset StunSpell ${Spell[Telekin].RankName}
	} else /if (${Me.Level}>=56 && ${Me.Book[${Spell[Markar's Discord].RankName}]}) {
		/varset StunSpell ${Spell[Markar's Discord].RankName}
	} else /if (${Me.Level}>=47 && ${Me.Book[${Spell[Markar's Clash].RankName}]}) {
		/varset StunSpell ${Spell[Markar's Clash].RankName}
	} else /if (${Me.Level}>=19 && ${Me.Book[${Spell[Tishan's Clash].RankName}]}) {
		/varset StunSpell ${Spell[Tishan's Clash].RankName}
	}
|-FastNuke1 Fastest casting general nuke not already used 
	/if (${Me.Level}>=107 && ${Me.Book[${Spell[Leap of Stormjolts].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Stormjolts].RankName}
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Leap of Stormbolts].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Stormbolts].RankName}
	} else /if (${Me.Level}>=97 && ${Me.Book[${Spell[Leap of Static Sparks].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Static Sparks].RankName}
	} else /if (${Me.Level}>=92 && ${Me.Book[${Spell[Leap of Plasma].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Plasma].RankName}
	} else /if (${Me.Level}>=87 && ${Me.Book[${Spell[Leap of Corposantum].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Corposantum].RankName}
	} else /if (${Me.Level}>=82 && ${Me.Book[${Spell[Leap of Static Jolts].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Static Jolts].RankName}
	} else /if (${Me.Level}>=77 && ${Me.Book[${Spell[Leap of Static Bolts].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Static Bolts].RankName}
	} else /if (${Me.Level}>=72 && ${Me.Book[${Spell[Leap of Sparks].RankName}]}) {
		/varset FastNuke1 ${Spell[Leap of Sparks].RankName}
	}
|-GeneralNuke1 Slower casting biggest nuke not already used
	/if (${Me.Level}>=110 && ${Me.Book[${Spell[Dragoflux's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Dragoflux's Fire].RankName}
	} else /if (${Me.Level}>=105 && ${Me.Book[${Spell[Narendi's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Narendi's Fire].RankName}
	} else /if (${Me.Level}>=100 && ${Me.Book[${Spell[Gosik's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Gosik's Fire].RankName}
	} else /if (${Me.Level}>=95 && ${Me.Book[${Spell[Daevan's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Daevan's Fire].RankName}
	} else /if (${Me.Level}>=90 && ${Me.Book[${Spell[Lithara's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Lithara's Fire].RankName}
	} else /if (${Me.Level}>=85 && ${Me.Book[${Spell[Klixcxyk's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Klixcxyk's Fire].RankName}
	} else /if (${Me.Level}>=80 && ${Me.Book[${Spell[Inizen's Fire].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Inizen's Fire].RankName}
	} else /if (${Me.Level}>=75 && ${Me.Book[${Spell[Sothgar's Flame].RankName}]}) {
		/varset GeneralNuke1 ${Spell[Sothgar's Flame].RankName}
	}

	/varset GoMNuke ${DichoSpell}
	|/varset GoMNuke2 ${Alliance}

	/if (${Me.AltAbility[25].Name.Find[disabled]} && ${Me.AltAbilityReady[25]}) {
		/alt act 25
		/delay 5
	}
	/if (${Me.AltAbility[514].Name.Find[disabled]} && ${Me.AltAbilityReady[514]}) {
		/alt act 514
		/delay 5
	}
	
	/call wiz_load_spellbar

/return 
