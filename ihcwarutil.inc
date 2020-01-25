|- ihcwarutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub WarSetup
|-Declare Discs
	/declare meleemit		string outer NULL
	/declare missall		string outer NULL
	/declare absorball		string outer NULL
	/declare parryall		string outer NULL
	/declare shieldhit		string outer NULL
	/declare groupac		string outer NULL
	/declare groupdodge		string outer NULL
	/declare defenseac		string outer NULL
	/declare bmdisc			string outer NULL
	/declare aeroar			string outer NULL
	/declare aeselfbuff		string outer NULL
	/declare aehealhate		string outer NULL
	/declare singlehealhate	string outer NULL
	/declare aehitall		string outer NULL
	/declare StrikeDisc		string outer NULL
	/declare endregen		string outer NULL
	/declare Aura1			string outer NULL
	/declare Aura2			string outer NULL
	/declare ItemOoWBP		string outer NULL
	/declare ItemDipPapers	string outer NULL
	/declare warbulwark		string outer NULL
	/declare shout			string outer NULL
	/declare insult			string outer NULL
	/declare roar			string outer NULL
	/declare phantom		string outer NULL
	/declare knuckle		string outer NULL
	/declare throat			string outer NULL
	/declare reprisal		string outer NULL
	/declare tongue			string outer NULL
	/declare attention		string outer NULL
	/declare FortitudeDiscID		int outer 0
	/declare CulminatingStandID 	int outer 0
	/declare ACDiscID				int outer 0

	/declare ChestItemName				string outer "${Me.Inventory[17].Name}"
	/declare CastResult             	string outer

	/if (${FindItem[Gladiator's Plate Chestguard of War].ID}) /varset ItemOoWBP Gladiator's Plate Chestguard of War
	/if (${FindItem[Diplomatic Papers].ID}) /varset ItemDipPapers Diplomatic Papers
/return 
|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub SetupDiscs


	|--One off discs
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Dissident Shield].RankName}]}) {
		/varset bmdisc ${Spell[Dissident Shield].RankName}
	} else /if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Dichotomic Shield].RankName}]}) {
		/varset bmdisc ${Spell[Dichotomic Shield].RankName}
	}

	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Phantom Aggressor].RankName}]}) {
		/varset phantom ${Spell[Phantom Aggressor].RankName}
	}

	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Knuckle Crush].RankName}]}) {
		/varset knuckle ${Spell[Knuckle Crush].RankName}
	} else /if (${Me.Level}>=80 && ${Me.CombatAbility[${Spell[Knuckle Smash].RankName}]}) {
		/varset knuckle ${Spell[Knuckle Smash].RankName}
	}

	/if (${Me.Level}>=73 && ${Me.CombatAbility[${Spell[Throat Jab].RankName}]}) {
		/varset throat ${Spell[Throat Jab].RankName}
	}

	/if (${Me.Level}>=97 && ${Me.CombatAbility[${Spell[Determined Reprisal].RankName}]}) {
		/varset reprisal ${Spell[Determined Reprisal].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Biting Tongue Discipline].RankName}]}) {
		/varset tongue ${Spell[Biting Tongue Discipline].RankName}
	}

	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Unyielding Attention].RankName}]}) {
		/varset attention ${Spell[Unyielding Attention].RankName}
	}
	
	/if (${Me.Level}>=59 && ${Me.CombatAbility[${Spell[Fortitude Discipline].RankName}]}) {
		/varset missall ${Spell[Fortitude Discipline].RankName}
		/varset FortitudeDiscID ${Spell[Fortitude Discipline].ID}
	}
	/if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Pain Doesn't Hurt].RankName}]}) /varset absorball ${Spell[Pain Doesn't Hurt].RankName}
	/if (${Me.Level}>=87 && ${Me.CombatAbility[${Spell[Flash of Anger].RankName}]}) /varset parryall ${Spell[Flash of Anger].RankName}
	/if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Wade in to Battle].RankName}]}) /varset aeselfbuff ${Spell[Wade in to Battle].RankName}
	
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Concordant Precision].RankName}]}) {
		/varset singlehealhate ${Spell[Concordant Precision].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Harmonious Precision].RankName}]}) {
		/varset singlehealhate ${Spell[Harmonious Precision].RankName}
	}
	
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Concordant Expanse].RankName}]}) {
		/varset aehealhate ${Spell[Concordant Expanse].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Harmonious Expanse].RankName}]}) {
		/varset aehealhate ${Spell[Harmonious Expanse].RankName}
	}
	
	/if (${Me.Level}>=68 && ${Me.CombatAbility[${Spell[Commanding Voice].RankName}]}) /varset groupdodge ${Spell[Commanding Voice].RankName}
	|---Melee Mitigation Disc
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Culminating Stand Discipline].RankName}]})  {
		/varset meleemit ${Spell[Culminating Stand Discipline].RankName}
		/varset CulminatingStandID ${Spell[Culminating Stand Discipline].ID}
	} else /if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Last Stand Discipline].RankName}]})  {
		/varset meleemit ${Spell[Last Stand Discipline].RankName}
	} else /if (${Me.Level}>=72 && ${Me.CombatAbility[${Spell[Final Stand Discipline].RankName}]})  {
		/varset meleemit ${Spell[Final Stand Discipline].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Stonewall Discipline].RankName}]})  {
		/varset meleemit ${Spell[Stonewall Discipline].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Defensive Discipline].RankName}]})  {
		/varset meleemit ${Spell[Defensive Discipline].RankName}
	} 
	
	
	|---Defense AC Disc
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Resolute Defense].RankName}]})  {
		/varset defenseac ${Spell[Resolute Defense].RankName}
	} else /if (${Me.Level}>=105 && ${Me.CombatAbility[${Spell[Stout Defense].RankName}]})  {
		/varset defenseac ${Spell[Stout Defense].RankName}
	} else /if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Steadfast Defense].RankName}]})  {
		/varset defenseac ${Spell[Steadfast Defense].RankName}
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Stalwart Defense].RankName}]})  {
		/varset defenseac ${Spell[Stalwart Defense].RankName}
	} else /if (${Me.Level}>=90 && ${Me.CombatAbility[${Spell[Staunch Defense].RankName}]})  {
		/varset defenseac ${Spell[Staunch Defense].RankName}
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Bracing Defense].RankName}]})  {
		/varset defenseac ${Spell[Bracing Defense].RankName}
	} else /if (${Me.Level}>=81 && ${Me.CombatAbility[${Spell[Armor of Timeworn Runes].RankName}]})  {
		/varset defenseac ${Spell[Armor of Timeworn Runes].RankName}
	} else /if (${Me.Level}>=76 && ${Me.CombatAbility[${Spell[Armor of Draconic Runes].RankName}]})  {
		/varset defenseac ${Spell[Armor of Draconic Runes].RankName}
	} else /if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Shocking Defence Discipline].RankName}]})  {
		/varset defenseac ${Spell[Shocking Defence Discipline].RankName}
	} else /if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Aura of Runes Discipline].RankName}]})  {
		/varset defenseac ${Spell[Aura of Runes Discipline].RankName}
	} 

	/if (${Me.Level}>=85) {
		/varset ACDiscID ${Spell[${defenseac}].ID}
	}

	|---Bulwark disc
	/if  (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Warrior's Bastion].RankName}]})  {
		/varset warbulwark ${Spell[Warrior's Bastion].RankName}
	}
	|---Group AC Disc
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Field Champion].RankName}]})  {
		/varset groupac ${Spell[Field Champion].RankName}
	} else /if (${Me.Level}>=105 && ${Me.CombatAbility[${Spell[Field Protector].RankName}]})  {
		/varset groupac ${Spell[Field Protector].RankName}
	} else /if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Field Guardian].RankName}]})  {
		/varset groupac ${Spell[Field Guardian].RankName}
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Field Defender].RankName}]})  {
		/varset groupac ${Spell[Field Defender].RankName}
	} else /if (${Me.Level}>=90 && ${Me.CombatAbility[${Spell[Field Outfitter].RankName}]})  {
		/varset groupac ${Spell[Field Outfitter].RankName}
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Field Armorer].RankName}]})  {
		/varset groupac ${Spell[Field Armorer].RankName}
	} 
	|---AE Taunt
	/if (${Me.Level}>=93 && ${Me.CombatAbility[${Spell[Roar of Challenge].RankName}]})  {
		/varset aeroar ${Spell[Roar of Challenge].RankName}
	} else /if (${Me.Level}>=88 && ${Me.CombatAbility[${Spell[Rallying Roar].RankName}]})  {
		/varset aeroar ${Spell[Rallying Roar].RankName}
	}
	|---shout
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Burning Shout].RankName}]})  {
		/varset shout ${Spell[Burning Shout].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Tormenting Shout].RankName}]})  {
		/varset shout ${Spell[Tormenting Shout].RankName}
	} else /if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Harassing Shout].RankName}]})  {
		/varset shout ${Spell[Harassing Shout].RankName}
	}
	|---roar
	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Kluzen's Roar].RankName}]})  {
		/varset roar ${Spell[Kluzen's Roar].RankName}
	} else /if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Cyclone Roar].RankName}]})  {
		/varset roar ${Spell[Cyclone Roar].RankName}
	} else /if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Krondal's Roar].RankName}]})  {
		/varset roar ${Spell[Krondal's Roar].RankName}
	} else /if (${Me.Level}>=91 && ${Me.CombatAbility[${Spell[Grendlaen Roar].RankName}]})  {
		/varset roar ${Spell[Grendlaen Roar].RankName}
	} else /if (${Me.Level}>=86 && ${Me.CombatAbility[${Spell[Bazu Roar].RankName}]})  {
		/varset roar ${Spell[Bazu Roar].RankName}
	} else /if (${Me.Level}>=81 && ${Me.CombatAbility[${Spell[Bazu Bluster].RankName}]})  {
		/varset roar ${Spell[Bazu Bluster].RankName}
	} else /if (${Me.Level}>=69 && ${Me.CombatAbility[${Spell[Bazu Bellow].RankName}]})  {
		/varset roar ${Spell[Bazu Bellow].RankName}
	} 
	|---insult
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Slander].RankName}]})  {
		/varset insult ${Spell[Slander].RankName}
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Insult].RankName}]})  {
		/varset insult ${Spell[Insult].RankName}
	} else /if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Ridicule].RankName}]})  {
		/varset insult ${Spell[Ridicule].RankName}
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Scorn].RankName}]})  {
		/varset insult ${Spell[Scorn].RankName}
	} else /if (${Me.Level}>=90 && ${Me.CombatAbility[${Spell[Scoff].RankName}]})  {
		/varset insult ${Spell[Scoff].RankName}
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Jeer].RankName}]})  {
		/varset insult ${Spell[Jeer].RankName}
	} else /if (${Me.Level}>=80 && ${Me.CombatAbility[${Spell[Sneer].RankName}]})  {
		/varset insult ${Spell[Sneer].RankName}
	} else /if (${Me.Level}>=75 && ${Me.CombatAbility[${Spell[Scowl].RankName}]})  {
		/varset insult ${Spell[Scowl].RankName}
	} else /if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Mock].RankName}]})  {
		/varset insult ${Spell[Mock].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Bellow of the Mastruq].RankName}]})  {
		/varset insult ${Spell[Bellow of the Mastruq].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Ancient Chaos Cry].RankName}]})  {
		/varset insult ${Spell[Ancient Chaos Cry].RankName}
	} else /if (${Me.Level}>=63 && ${Me.CombatAbility[${Spell[Incite].RankName}]})  {
		/varset insult ${Spell[Incite].RankName}
	} else /if (${Me.Level}>=56 && ${Me.CombatAbility[${Spell[Berate].RankName}]})  {
		/varset insult ${Spell[Berate].RankName}
	} else /if (${Me.Level}>=52 && ${Me.CombatAbility[${Spell[Bellow].RankName}]})  {
		/varset insult ${Spell[Bellow].RankName}
	} else /if (${Me.Level}>=20 && ${Me.CombatAbility[${Spell[Provoke].RankName}]})  {
		/varset insult ${Spell[Provoke].RankName}
	} 

	|---Strike
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Cunning Strike].RankName}]})  {
		/varset StrikeDisc ${Spell[Cunning Strike].RankName}
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Calculated Strike].RankName}]})  {
		/varset StrikeDisc ${Spell[Calculated Strike].RankName}
	} else /if (${Me.Level}>=93 && ${Me.CombatAbility[${Spell[Vital Strike].RankName}]})  {
		/varset StrikeDisc ${Spell[Vital Strike].RankName}
	} else /if (${Me.Level}>=88 && ${Me.CombatAbility[${Spell[Strategic Strike].RankName}]})  {
		/varset StrikeDisc ${Spell[Strategic Strike].RankName}
	} else /if (${Me.Level}>=78 && ${Me.CombatAbility[${Spell[Opportunistic Strike].RankName}]})  {
		/varset StrikeDisc ${Spell[Opportunistic Strike].RankName}
	}
	|---AE Hit all 50 range
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Dragonstrike Blades].RankName}]})  {
		/varset aehitall ${Spell[Dragonstrike Blades].RankName}
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Stormstrike Blades].RankName}]})  {
		/varset aehitall ${Spell[Stormstrike Blades].RankName}
	} else /if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Stormwheel Blades].RankName}]})  {
		/varset aehitall ${Spell[Stormwheel Blades].RankName}
	} else /if (${Me.Level}>=94 && ${Me.CombatAbility[${Spell[Cyclonic Blades].RankName}]})  {
		/varset aehitall ${Spell[Cyclonic Blades].RankName}
	} else /if (${Me.Level}>=89 && ${Me.CombatAbility[${Spell[Wheeling Blades].RankName}]})  {
		/varset aehitall ${Spell[Wheeling Blades].RankName}
	} else /if (${Me.Level}>=84 && ${Me.CombatAbility[${Spell[Maelstrom Blade].RankName}]})  {
		/varset aehitall ${Spell[Maelstrom Blade].RankName}
	} else /if (${Me.Level}>=79 && ${Me.CombatAbility[${Spell[Whorl Blade].RankName}]})  {
		/varset aehitall ${Spell[Whorl Blade].RankName}
	} else /if (${Me.Level}>=74 && ${Me.CombatAbility[${Spell[Vortex Blade].RankName}]})  {
		/varset aehitall ${Spell[Vortex Blade].RankName}
	} else /if (${Me.Level}>=69 && ${Me.CombatAbility[${Spell[Cyclone Blade].RankName}]})  {
		/varset aehitall ${Spell[Cyclone Blade].RankName}
	} else /if (${Me.Level}>=61 && ${Me.CombatAbility[${Spell[Whirlwind Blade].RankName}]})  {
		/varset aehitall ${Spell[Whirlwind Blade].RankName}
	} 
	|--- Shield Hit and Block
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Shield Sunder].RankName}]})  {
		/varset shieldhit ${Spell[Shield Sunder].RankName}
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Shield Break].RankName}]})  {
		/varset shieldhit ${Spell[Shield Break].RankName}
	} else /if (${Me.Level}>=83 && ${Me.CombatAbility[${Spell[Shield Topple].RankName}]})  {
		/varset shieldhit ${Spell[Shield Topple].RankName}
	}
	|---Fast Endurance regen
	/if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Breather].RankName}]})  {
		/varset endregen ${Spell[Breather].RankName}
	} else /if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Rest].RankName}]})  {
		/varset endregen ${Spell[Rest].RankName}
	} else /if (${Me.Level}>=91 && ${Me.CombatAbility[${Spell[Reprieve].RankName}]})  {
		/varset endregen ${Spell[Reprieve].RankName}
	} else /if (${Me.Level}>=86 && ${Me.CombatAbility[${Spell[Respite].RankName}]})  {
		/varset endregen ${Spell[Respite].RankName}
	} else /if (${Me.Level}>=82 && ${Me.CombatAbility[${Spell[Fourth Wind].RankName}]})  {
		/varset endregen ${Spell[Fourth Wind].RankName}
	} else /if (${Me.Level}>=77 && ${Me.CombatAbility[${Spell[Third Wind].RankName}]})  {
		/varset endregen ${Spell[Third Wind].RankName}
	} else /if (${Me.Level}>=72 && ${Me.CombatAbility[${Spell[Second Wind].RankName}]})  {
		/varset endregen ${Spell[Second Wind].RankName}
	}
	|---Aura usage
	/if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Champion's Aura].RankName}]})  {
		/varset Aura1 ${Spell[Champion's Aura].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Myrmidon's Aura].RankName}]})  {
		/varset Aura1 ${Spell[Myrmidon's Aura].RankName}
	}

	/if (${Me.AltAbility[692].Name.Find[disabled]} && ${Me.AltAbilityReady[692]}) {
		/alt act 692
		/delay 2s
	}
	/if (${Me.AltAbility[684].Name.Find[disabled]} && ${Me.AltAbilityReady[684]}) {
		/alt act 684
		/delay 2s
	}
	/if (${Me.AltAbility[1126].Name.Find[disabled]} && ${Me.AltAbilityReady[1126]}) {
		/alt act 1126
		/delay 2s
	}
	/if (${Me.AltAbility[2001].Name.Find[disabled]} && ${Me.AltAbilityReady[2001]}) {
		/alt act 2001
		/delay 2s
	}

	/if (${Me.CombatAbility[${insult}]}) {
		/varset PullAbility ${insult}
		/varset PullDistance 85
	} else {
		/varset PullAbility ${Spell[Throw Stone].RankName}
		/varset PullDistance 55
	}
/return
|----------------------------------------------------------------------------
|-SUB: BIND DefenseDisc - 
|----------------------------------------------------------------------------
Sub Bind_DefenseDisc
	/if (${Me.CombatAbilityReady[${meleemit}]}) {
		/if (${Me.Buff[Night's Endless Terror].ID}) {
			/docommand /removebuff "Night's Endless Terror"
			/delay 5
			/call DiscQueue "${meleemit}"
		} else { 
			/call DiscQueue "${meleemit}"
		}
	} else {
		/echo \ar COOL DOWN \ag >> \aw ${meleemit} \ag << 
	}
/return 
|----------------------------------------------------------------------------
|-SUB: BIND FortitudeDisc - 
|----------------------------------------------------------------------------
Sub Bind_FortitudeDisc
	/if (${Me.CombatAbilityReady[${missall}]}) {
		/call DiscQueue "${missall}"
	} else {
		/echo \ar COOL DOWN \ag >> \aw ${missall} \ag << 
	}
/return 