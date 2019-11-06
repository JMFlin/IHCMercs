|- ihcwarutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub WarSetup
|-Create Alias
	|-- Toggles
	/squelch /alias /autotank		/setvarint Toggle AutoTank
	/squelch /alias /tglaggro		/setvarint Toggle DoAggro
	/squelch /alias /tglaeaggro		/setvarint Toggle DoAEAggro
	/squelch /alias /tglbuff		/setvarint Toggle DoBuffs
	/squelch /alias /tgldefense		/setvarint Toggle DoDefense
	/squelch /alias /tglengage		/setvarint Toggle DoAutoEngage
	/squelch /alias /tgltargeting	/setvarint Toggle DoAutoTarget
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
	/declare waraura		string outer NULL
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
|-Config Options
	/call LoadCommonConfig
	/call LoadIni Buffs UseAEHateBuff	int 0
	/call LoadIni Combat AutoTank		int 0
	/call LoadIni Combat DoAEAggro		int 1
	/call LoadIni Combat DoAggro		int 1
	/call LoadIni Combat DoBattleLeap	int 1
	/call LoadIni Combat DoDefense		int 1
	/call LoadIni Combat StickHow		string front
	/call LoadIni Combat UseMelee		int 1
	/call LoadIni Options DoAutoBag		int 1
	/call LoadIni Options DoAutoPDH		int 0
	/call LoadIni Options DoBuffs		int 1
	/call LoadIni Item ChestItemName	string "${Me.Inventory[17].Name}"
	/declare stayontarget				int outer 0
	/declare CastResult             	string outer
|- Warrior logic
	/declare TimeForMez					timer outer	0
	/declare TimeForMezVariable			int outer 0
|- Balance events
	/declare HighHPID 					int outer 0
    /declare highhppct 					int outer 99
    /declare Balance 					int outer 0

	/if (${FindItem[Gladiator's Plate Chestguard of War].ID}) /varset ItemOoWBP Gladiator's Plate Chestguard of War
	/if (${FindItem[Diplomatic Papers].ID}) /varset ItemDipPapers Diplomatic Papers
/return 
|----------------------------------------------------------------------------
|- SUB: CheckOptions
|---------------------------------------------------------------------------- 
Sub CheckOptions
	/if (${AutoTank}) /varset changetoini 1
	/if (${AutoTank} && ${AutoAssistAt}<100) /varset AutoAssistAt 100
	/if (${AutoTank} && !${DoAggro}) /varset DoAggro 1
	/if (${AutoTank} && !${DoAutoTarget}) /varset DoAutoTarget 1
	/if (${AutoTank} && ${stayontarget}) /varset stayontarget 0
	/if (${AutoTank} && !${DoAutoEngage}) /varset DoAutoEngage 1
	/if (${AutoTank} && !${DoDefense}) /varset DoDefense 1
	/if (${AutoTank} && ${UseSmartAssist}) /varset UseSmartAssist 0
	/if (!${UseMelee}) /varset UseMelee 1
	/if (${DoAggro}) {
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
	}
/return
|----------------------------------------------------------------------------
|- SUB: INIChanges
|---------------------------------------------------------------------------- 
Sub INIChanges
	/varset changetoini 0
	/call SaveCommonConfig
	/call SetIni Combat AutoTank		int ${AutoTank}
	/call SetIni Combat DoAEAggro		int ${DoAEAggro}
	/call SetIni Combat DoAggro			int ${DoAggro}
	/call SetIni Combat DoAutoTarget	int ${DoAutoTarget}
	/call SetIni Combat DoAutoEngage	int ${DoAutoEngage}
	/call SetIni Combat DoBattleLeap	int ${DoBattleLeap}
	/call SetIni Combat DoDefense		int ${DoDefense}
	/call SetIni Combat UseMelee		int ${UseMelee}
	/call SetIni Options DoAutoBag		int ${DoAutoBag}
	/call SetIni Options DoAutoPDH		int ${DoAutoPDH}
	/call SetIni Options DoBuffs		int ${DoBuffs}
/return 
|----------------------------------------------------------------------------
|- SUB: PullAbilitySetup
|----------------------------------------------------------------------------
Sub PullAbilitySetup
	/if (${Me.CombatAbilityReady[${insult}]}) /varset PullAbility ${insult}
	/if (${Me.CombatAbilityReady[${insult}]}) /varset PullDistance 90
	/if (!${Me.CombatAbilityReady[${insult}]}) /varset PullAbility ${Spell[Throw Stone].RankName}
	/if (!${Me.CombatAbilityReady[${insult}]}) /varset PullDistance 68
	/if (${FindItem[Staff of Viral Flux].ID}) /varset PullAbility2 ${FindItem[Staff of Viral Flux]}
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
	}

	/if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Throat Jab].RankName}]}) {
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
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Ancient Chaos Cry].RankName}]})  {
		/varset roar ${Spell[Ancient Chaos Cry].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Bellow of the Mastruq].RankName}]})  {
		/varset roar ${Spell[Bellow of the Mastruq].RankName}
	} else /if (${Me.Level}>=63 && ${Me.CombatAbility[${Spell[Incite].RankName}]})  {
		/varset roar ${Spell[Incite].RankName}
	} else /if (${Me.Level}>=56 && ${Me.CombatAbility[${Spell[Berate].RankName}]})  {
		/varset roar ${Spell[Berate].RankName}
	} else /if (${Me.Level}>=52 && ${Me.CombatAbility[${Spell[Bellow].RankName}]})  {
		/varset roar ${Spell[Bellow].RankName}
	} else /if (${Me.Level}>=20 && ${Me.CombatAbility[${Spell[Provoke].RankName}]})  {
		/varset roar ${Spell[Provoke].RankName}
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
	|---AE Hit all
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
		/varset waraura ${Spell[Champion's Aura].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Myrmidon's Aura].RankName}]})  {
		/varset waraura ${Spell[Myrmidon's Aura].RankName}
	}
/return
|----------------------------------------------------------------------------
|-SUB: Bind Change Var Int resets various interger settings from ini file
|----------------------------------------------------------------------------
Sub Bind_SetVarInt(string ISection, string IName, int IVar)
    /docommand /varset changetoini 1
 |-Toggles
	/if (${ISection.Equal[Toggle]}) {
		/if (${IName.Equal[AutoTank]}) {
			/if (!${AutoTank}) {
				/echo \aw Setting AutoTank to \ag ON
				/varset AutoTank 1
			} else {
				/echo \aw Resetting AutoTank to \ar OFF
				/varset AutoTank 0
			}
		} else /if (${IName.Equal[DoAggro]}) {
			/if (!${DoAggro}) {
				/echo \aw Setting DoAggro to \ag ON
				/varset DoAggro 1
			} else {
				/echo \aw Resetting DoAggro to \ar OFF
				/varset DoAggro 0
			}
		} else /if (${IName.Equal[DoBuffs]}) {
			/if (!${DoBuffs}) {
				/echo \aw Setting DoBuffs to \ag ON
				/varset DoBuffs 1
			} else {
				/echo \aw Resetting DoBuffs to \ar OFF
				/varset DoBuffs 0
			}
		} else /if (${IName.Equal[DoDefense]}) {
			/if (!${DoDefense}) {
				/echo \aw Setting DoDefense to \ag ON
				/varset DoDefense 1
			} else {
				/echo \aw Resetting DoDefense to \ar OFF
				/varset DoDefense 0
			}
		} else /if (${IName.Equal[DoAutoEngage]}) {
			/if (!${DoAutoEngage}) {
				/echo \aw Setting DoAutoEngage to \ag ON
				/varset DoAutoEngage 1
			} else {
				/echo \aw Resetting DoAutoEngage to \ar OFF
				/varset DoAutoEngage 0
			}
		} else /if (${IName.Equal[DoAutoTarget]}) {
			/if (!${DoAutoTarget}) {
				/echo \aw Setting DoAutoTarget to \ag ON
				/varset DoAutoTarget 1
				/varset stayontarget 0
			} else {
				/echo \aw Resetting DoAutoTarget to \ar OFF
				/varset DoAutoTarget 0
				/varset stayontarget 1
			}
		} else /if (${IName.Equal[DoAEAggro]}) {
			/if (!${DoAEAggro}) {
				/echo \aw Setting DoAEAggro to \ag ON
				/varset DoAEAggro 1
			} else {
				/echo \aw Resetting DoAEAggro to \ar OFF
				/varset DoAEAggro 0
			}
		}
	}
	/call CheckOptions
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
|----------------------------------------------------------------------------
|-SUB: BIND CmdList - 
|----------------------------------------------------------------------------
Sub Bind_CmdList
/call CommonHelp
/echo \ag===${MacroName} Commands=== 
/echo \ag/autotank\aw - Turns on all Tanking features
/echo \ag/tglaeaggro\aw - Toggle use of AE Aggro Abilities
/echo \ag/tglaggro\aw - Toggle use of Aggro Abilities
/echo \ag/tglbuff\aw - Toggle use of Warrior buffs ( Aura, AC, Dodge)
/echo \ag/tgldefense\aw - Toggle use of defensive abilities during combat
/echo \ag/tglengage\aw - Toggle use of Auto Engaging target
/echo \ag/tgltargeting\aw - Toggle use of Auto Targeting 
/return 