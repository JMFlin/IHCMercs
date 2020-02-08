|- ihcbstutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub dru_setup
|-Create Alias
	/declare Aura1			string outer NULL
	/declare Aura2			string outer NULL
	
	/declare Lunasalve			string outer NULL
	/declare NukeSpell1			string outer NULL
	/declare NukeSpell2			string outer NULL
	/declare DoTSpell2			string outer NULL
	/declare DoTSpell1			string outer NULL
	/declare SnareSpell			string outer NULL
	/declare Skin				string outer NULL
	/declare SoW				string outer NULL
	/declare DamageShield 		string outer NULL
	/declare Promised 			string outer NULL
	/declare SunflashBlessing 	string outer NULL
	/declare RemoteMoon			string outer NULL
	/declare RemoteSun			string outer NULL
	/declare Cyclonic 			string outer NULL
	/declare SelfDamageShield 	string outer NULL
	/declare SelfUnity 			string outer NULL
	/declare RezSpell 				string outer NULL
	/declare MassRezSpell			string outer NULL

	/declare Revitalization 	string outer NULL
	/declare Curavida 			string outer NULL
	/declare Adrenaline 		string outer NULL

	/declare SingleFireAtkDebuff 		string outer NULL
	/declare AEFireAtkDebuff			string outer NULL
	/declare SingleFrostAtkDebuff 		string outer NULL
	
	/declare IceDebuff 			string outer NULL
	/declare GroupWolfAtkBuff 	string outer NULL

	/declare GroupSkin 			string outer NULL
	/declare Reptile 			string outer NULL
	/declare NBW				string outer NULL
	/declare Survival 			string outer NULL
	/declare Mask 				string outer NULL
	/declare TwincastSpell 		string outer NULL

	/declare PosseSpell				string outer NULL

	/declare GoMNuke				string outer NULL
	/declare GoMNuke2				string outer NULL
/return 
|* ------------------------------------------------------------------------------------------
| SUB: ${Me.Class.ShortName.Lower}_load_spellbar
|------------------------------------------------------------------------------------------ *|
Sub dru_load_spellbar
/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar

	/call LoadSpellGem "${Revitalization}" 1
	/call LoadSpellGem "${Adrenaline}" 2
	/call LoadSpellGem "${Curavida}" 3
	/call LoadSpellGem "${Cyclonic}" 4
	|/call LoadSpellGem "${Lunasalve}" 4
	/call LoadSpellGem "${Survival}" 5
	/call LoadSpellGem "${Reptile}" 6

	/call LoadSpellGem "${NBW}" 7
	/call LoadSpellGem "${SingleFrostAtkDebuff}" 8
	
	
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: SetupSpells
|---------------------------------------------------------------------------- 
Sub dru_abilities

|**
HEAL:
1-   Revitalization
2-   Adrenaline Barrage (or Thornspike Rush if short event)
3-   Curavida
4-   Lunasalve
5-   Promised Rebirth
6-   Sunflash Blessing
7-   Survival of the Auspicious
8-   Guard of the Reptile
9-   Savage Growth
10-   Arcronite Skin (or Blessing if short event)
11-   Bosquetender’s Alliance
12-   Nature’s Response
13-   Nourishing Growth

BALANCED:
1-   Revitalization
2-   Adrenaline Barrage (or Thornspike Rush if short event)
3-   Curavida
4-   Lunasalve
5-   Survival of the Auspicious
6-   Remote Moonflash (or Remote Sunblaze)
7-   Dichotomic Winds
8-   Nature’s Blistening Wrath
9-   Sunflame
10-   Horde of Polybiads
11-   Chill of the Wildtender (Cycle with the spell Nourishing Growth for mana regen)
12-   Pearlescent Moonbeam (Cycle with the spell Bosquetener’s Fortitude for a short-burn event) OR Overwhelming Sunray (Cycle with the spell Twincast for extra Twin burn)
13-   Cyclonic Roar (Cycle with the spell Frostreave Aura or Wildspark Aura for extra cold/fire burst procs for your group)
**|

	/if (${Me.Level} >= ${Spell[Circle of Knowledge].Level} && ${Me.Book[${Spell[Circle of Knowledge].RankName}]}) {
		/varset PosseSpell ${Spell[Circle of Knowledge].RankName}
	}
	

	/if (${Me.Level}>=${Spell[Typhonic Roar].Level} && ${Me.Book[${Spell[Typhonic Roar].RankName}]}) {
		/varset Cyclonic ${Spell[Typhonic Roar].RankName}
	} else /if (${Me.Level}>=${Spell[Cyclonic Roar].Level} && ${Me.Book[${Spell[Cyclonic Roar].RankName}]}) {
		/varset Cyclonic ${Spell[Cyclonic Roar].RankName}
	} else /if (${Me.Level}>=${Spell[Anabatic Roar].Level} && ${Me.Book[${Spell[Anabatic Roar].RankName}]}) {
		/varset Cyclonic ${Spell[Anabatic Roar].RankName}
	} else /if (${Me.Level}>=${Spell[Katabatic Roar].Level} && ${Me.Book[${Spell[Katabatic Roar].RankName}]}) {
		/varset Cyclonic ${Spell[Katabatic Roar].RankName}
	} else /if (${Me.Level}>=${Spell[Roar of Kolos].Level} && ${Me.Book[${Spell[Roar of Kolos].RankName}]}) {
		/varset Cyclonic ${Spell[Roar of Kolos].RankName}
	} else /if (${Me.Level}>=${Spell[Cyclone of the Stormborn].Level} && ${Me.Book[${Spell[Cyclone of the Stormborn].RankName}]}) {
		/varset Cyclonic ${Spell[Cyclone of the Stormborn].RankName}
	} else /if (${Me.Level}>=${Spell[Shear of the Stormborn].Level} && ${Me.Book[${Spell[Shear of the Stormborn].RankName}]}) {
		/varset Cyclonic ${Spell[Shear of the Stormborn].RankName}
	} else /if (${Me.Level}>=${Spell[Squall of the Stormborn].Level} && ${Me.Book[${Spell[Squall of the Stormborn].RankName}]}) {
		/varset Cyclonic ${Spell[Squall of the Stormborn].RankName}
	} else /if (${Me.Level}>=${Spell[Tempest of the Stormborn].Level} && ${Me.Book[${Spell[Tempest of the Stormborn].RankName}]}) {
		/varset Cyclonic ${Spell[Tempest of the Stormborn].RankName}
	} else /if (${Me.Level}>=${Spell[Gale of the Stormborn].Level} && ${Me.Book[${Spell[Gale of the Stormborn].RankName}]}) {
		/varset Cyclonic ${Spell[Gale of the Stormborn].RankName}
	} else /if (${Me.Level}>=${Spell[Stormwatch].Level} && ${Me.Book[${Spell[Stormwatch].RankName}]}) {
		/varset Cyclonic ${Spell[Stormwatch].RankName}
	} else /if (${Me.Level}>=${Spell[Storm's Fury].Level} && ${Me.Book[${Spell[Storm's Fury].RankName}]}) {
		/varset Cyclonic ${Spell[Storm's Fury].RankName}
	} else /if (${Me.Level}>=${Spell[Breath of Karana].Level} && ${Me.Book[${Spell[Breath of Karana].RankName}]}) {
		/varset Cyclonic ${Spell[Breath of Karana].RankName}
	} else /if (${Me.Level}>=${Spell[Dustdevil].Level} && ${Me.Book[${Spell[Dustdevil].RankName}]}) {
		/varset Cyclonic ${Spell[Dustdevil].RankName}
	} else /if (${Me.Level}>=${Spell[Fury of Air].Level} && ${Me.Book[${Spell[Fury of Air].RankName}]}) {
		/varset Cyclonic ${Spell[Fury of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Dizzying Wind].Level} && ${Me.Book[${Spell[Dizzying Wind].RankName}]}) {
		/varset Cyclonic ${Spell[Dizzying Wind].RankName}
	} else /if (${Me.Level}>=${Spell[Whirling Wind].Level} && ${Me.Book[${Spell[Whirling Wind].RankName}]}) {
		/varset Cyclonic ${Spell[Whirling Wind].RankName}
	}


	/if (${Me.Level}>=${Spell[Remote Sunshock].Level} && ${Me.Book[${Spell[Remote Sunshock].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Sunshock].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Sunblaze].Level} && ${Me.Book[${Spell[Remote Sunblaze].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Sunblaze].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Sunflash].Level} && ${Me.Book[${Spell[Remote Sunflash].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Sunflash].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Sunfire].Level} && ${Me.Book[${Spell[Remote Sunfire].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Sunfire].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Sunburst].Level} && ${Me.Book[${Spell[Remote Sunburst].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Sunburst].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Sunflare].Level} && ${Me.Book[${Spell[Remote Sunflare].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Sunflare].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Manaflux].Level} && ${Me.Book[${Spell[Remote Manaflux].RankName}]}) {
		/varset RemoteSun ${Spell[Remote Manaflux].RankName}
	}


	/if (${Me.Level}>=${Spell[Remote Moonrake].Level} && ${Me.Book[${Spell[Remote Moonrake].RankName}]}) {
		/varset RemoteMoon ${Spell[Remote Moonrake].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Moonflash].Level} && ${Me.Book[${Spell[Remote Moonflash].RankName}]}) {
		/varset RemoteMoon ${Spell[Remote Moonflash].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Moonflame].Level} && ${Me.Book[${Spell[Remote Moonflame].RankName}]}) {
		/varset RemoteMoon ${Spell[Remote Moonflame].RankName}
	} else /if (${Me.Level}>=${Spell[Remote Moonfire].Level} && ${Me.Book[${Spell[Remote Moonfire].RankName}]}) {
		/varset RemoteMoon ${Spell[Remote Moonfire].RankName}
	}


	/if (${Me.Level}>=${Spell[Sunrake Blessing].Level} && ${Me.Book[${Spell[Sunrake Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sunrake Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Sunflash Blessing].Level} && ${Me.Book[${Spell[Sunflash Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sunflash Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Sunfire Blessing].Level} && ${Me.Book[${Spell[Sunfire Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sunfire Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Sunbeam Blessing].Level} && ${Me.Book[${Spell[Sunbeam Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sunbeam Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Sunbreeze Blessing].Level} && ${Me.Book[${Spell[Sunbreeze Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sunbreeze Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Sunrise Blessing].Level} && ${Me.Book[${Spell[Sunrise Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sunrise Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Sundew Blessing].Level} && ${Me.Book[${Spell[Sundew Blessing].RankName}]}) {
		/varset SunflashBlessing ${Spell[Sundew Blessing].RankName}
	}

	/if (${Me.Level}>=${Spell[Rejuvenescence].Level} && ${Me.Book[${Spell[Rejuvenescence].RankName}]}) {
		/varset Revitalization ${Spell[Rejuvenescence].RankName}
	} else /if (${Me.Level}>=${Spell[Revitalization].Level} && ${Me.Book[${Spell[Revitalization].RankName}]}) {
		/varset Revitalization ${Spell[Revitalization].RankName}
	} else /if (${Me.Level}>=${Spell[Resurgence].Level} && ${Me.Book[${Spell[Resurgence].RankName}]}) {
		/varset Revitalization ${Spell[Resurgence].RankName}
	} else /if (${Me.Level}>=${Spell[Vivification].Level} && ${Me.Book[${Spell[Vivification].RankName}]}) {
		/varset Revitalization ${Spell[Vivification].RankName}
	} else /if (${Me.Level}>=${Spell[Invigoration].Level} && ${Me.Book[${Spell[Invigoration].RankName}]}) {
		/varset Revitalization ${Spell[Invigoration].RankName}
	} else /if (${Me.Level}>=${Spell[Rejuvilation].Level} && ${Me.Book[${Spell[Rejuvilation].RankName}]}) {
		/varset Revitalization ${Spell[Rejuvilation].RankName}
	}


	/if (${Me.Level}>=${Spell[Viridavida].Level} && ${Me.Book[${Spell[Viridavida].RankName}]}) {
		/varset Curavida ${Spell[Viridavida].RankName}
	} else /if (${Me.Level}>=${Spell[Curavida].Level} && ${Me.Book[${Spell[Curavida].RankName}]}) {
		/varset Curavida ${Spell[Curavida].RankName}
	} else /if (${Me.Level}>=${Spell[Panavida].Level} && ${Me.Book[${Spell[Panavida].RankName}]}) {
		/varset Curavida ${Spell[Panavida].RankName}
	} else /if (${Me.Level}>=${Spell[Sterivida].Level} && ${Me.Book[${Spell[Sterivida].RankName}]}) {
		/varset Curavida ${Spell[Sterivida].RankName}
	} else /if (${Me.Level}>=${Spell[Sanavida].Level} && ${Me.Book[${Spell[Sanavida].RankName}]}) {
		/varset Curavida ${Spell[Sanavida].RankName}
	} else /if (${Me.Level}>=${Spell[Benevida].Level} && ${Me.Book[${Spell[Benevida].RankName}]}) {
		/varset Curavida ${Spell[Benevida].RankName}
	} else /if (${Me.Level}>=${Spell[Granvida].Level} && ${Me.Book[${Spell[Granvida].RankName}]}) {
		/varset Curavida ${Spell[Granvida].RankName}
	} else /if (${Me.Level}>=${Spell[Puravida].Level} && ${Me.Book[${Spell[Puravida].RankName}]}) {
		/varset Curavida ${Spell[Puravida].RankName}
	} else /if (${Me.Level}>=${Spell[Pure Life].Level} && ${Me.Book[${Spell[Pure Life].RankName}]}) {
		/varset Curavida ${Spell[Pure Life].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Chlorobon].Level} && ${Me.Book[${Spell[Ancient Chlorobon].RankName}]}) {
		/varset Curavida ${Spell[Ancient Chlorobon].RankName}
	} else /if (${Me.Level}>=${Spell[Chlorotrope].Level} && ${Me.Book[${Spell[Chlorotrope].RankName}]}) {
		/varset Curavida ${Spell[Chlorotrope].RankName}
	} else /if (${Me.Level}>=${Spell[Sylvan Infusion].Level} && ${Me.Book[${Spell[Sylvan Infusion].RankName}]}) {
		/varset Curavida ${Spell[Sylvan Infusion].RankName}
	} else /if (${Me.Level}>=${Spell[Karana's Renewal].Level} && ${Me.Book[${Spell[Karana's Renewal].RankName}]}) {
		/varset Curavida ${Spell[Karana's Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Infusion].Level} && ${Me.Book[${Spell[Nature's Infusion].RankName}]}) {
		/varset Curavida ${Spell[Nature's Infusion].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Touch].Level} && ${Me.Book[${Spell[Nature's Touch].RankName}]}) {
		/varset Curavida ${Spell[Nature's Touch].RankName}
	} else /if (${Me.Level}>=${Spell[Tunare's Renewal].Level} && ${Me.Book[${Spell[Tunare's Renewal].RankName}]}) {
		/varset Curavida ${Spell[Tunare's Renewal].RankName}
	}


	/if (${Me.Level}>=${Spell[Adrenaline Deluge].Level} && ${Me.Book[${Spell[Adrenaline Deluge].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Deluge].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Barrage].Level} && ${Me.Book[${Spell[Adrenaline Barrage].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Barrage].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Torrent].Level} && ${Me.Book[${Spell[Adrenaline Torrent].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Torrent].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Rush].Level} && ${Me.Book[${Spell[Adrenaline Rush].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Rush].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Flood].Level} && ${Me.Book[${Spell[Adrenaline Flood].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Flood].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Blast].Level} && ${Me.Book[${Spell[Adrenaline Blast].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Blast].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Burst].Level} && ${Me.Book[${Spell[Adrenaline Burst].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Burst].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Swell].Level} && ${Me.Book[${Spell[Adrenaline Swell].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Swell].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Surge].Level} && ${Me.Book[${Spell[Adrenaline Surge].RankName}]}) {
		/varset Adrenaline ${Spell[Adrenaline Surge].RankName}
	} else /if (${Me.Level}>=${Spell[Superior Healing].Level} && ${Me.Book[${Spell[Superior Healing].RankName}]}) {
		/varset Adrenaline ${Spell[Superior Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Greater Healing].Level} && ${Me.Book[${Spell[Greater Healing].RankName}]}) {
		/varset Adrenaline ${Spell[Greater Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Healing].Level} && ${Me.Book[${Spell[Healing].RankName}]}) {
		/varset Adrenaline ${Spell[Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Light Healing].Level} && ${Me.Book[${Spell[Light Healing].RankName}]}) {
		/varset Adrenaline ${Spell[Light Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Minor Healing].Level} && ${Me.Book[${Spell[Minor Healing].RankName}]}) {
		/varset Adrenaline ${Spell[Minor Healing].RankName}
	}


	

	/if (${Me.Level}>=${Spell[Promised Refreshment].Level} && ${Me.Book[${Spell[Promised Refreshment].RankName}]}) {
		/varset Promised ${Spell[Promised Refreshment].RankName}
	} else /if (${Me.Level}>=${Spell[Promised Rebirth].Level} && ${Me.Book[${Spell[Promised Rebirth].RankName}]}) {
		/varset Promised ${Spell[Promised Rebirth].RankName}
	} else /if (${Me.Level}>=${Spell[Promised Regeneration].Level} && ${Me.Book[${Spell[Promised Regeneration].RankName}]}) {
		/varset Promised ${Spell[Promised Regeneration].RankName}
	} else /if (${Me.Level}>=${Spell[Promised Recovery].Level} && ${Me.Book[${Spell[Promised Recovery].RankName}]}) {
		/varset Promised ${Spell[Promised Recovery].RankName}
	} else /if (${Me.Level}>=${Spell[Promised Revitalization].Level} && ${Me.Book[${Spell[Promised Revitalization].RankName}]}) {
		/varset Promised ${Spell[Promised Revitalization].RankName}
	} else /if (${Me.Level}>=${Spell[Promised Replenishment].Level} && ${Me.Book[${Spell[Promised Replenishment].RankName}]}) {
		/varset Promised ${Spell[Promised Replenishment].RankName}
	} else /if (${Me.Level}>=${Spell[Promised Reknit].Level} && ${Me.Book[${Spell[Promised Reknit].RankName}]}) {
		/varset Promised ${Spell[Promised Reknit].RankName}
	}


	/if (${Me.Level}>=${Spell[Lunalesce].Level} && ${Me.Book[${Spell[Lunalesce].RankName}]}) {
		/varset Lunasalve ${Spell[Lunalesce].RankName}
	} else /if (${Me.Level}>=${Spell[Lunasalve].Level} && ${Me.Book[${Spell[Lunasalve].RankName}]}) {
		/varset Lunasalve ${Spell[Lunasalve].RankName}
	} else /if (${Me.Level}>=${Spell[Lunasoothe].Level} && ${Me.Book[${Spell[Lunasoothe].RankName}]}) {
		/varset Lunasalve ${Spell[Lunasoothe].RankName}
	} else /if (${Me.Level}>=${Spell[Lunassuage].Level} && ${Me.Book[${Spell[Lunassuage].RankName}]}) {
		/varset Lunasalve ${Spell[Lunassuage].RankName}
	} else /if (${Me.Level}>=${Spell[Lunamelioration].Level} && ${Me.Book[${Spell[Lunamelioration].RankName}]}) {
		/varset Lunasalve ${Spell[Lunamelioration].RankName}
	} else /if (${Me.Level}>=${Spell[Lunulation].Level} && ${Me.Book[${Spell[Lunulation].RankName}]}) {
		/varset Lunasalve ${Spell[Lunulation].RankName}
	} else /if (${Me.Level}>=${Spell[Crescentbloom].Level} && ${Me.Book[${Spell[Crescentbloom].RankName}]}) {
		/varset Lunasalve ${Spell[Crescentbloom].RankName}
	} else /if (${Me.Level}>=${Spell[Lunarlight].Level} && ${Me.Book[${Spell[Lunarlight].RankName}]}) {
		/varset Lunasalve ${Spell[Lunarlight].RankName}
	}

	/if (${Me.Level}>=${Spell[Equinox Brand].Level} && ${Me.Book[${Spell[Equinox Brand].RankName}]}) {
		/varset NukeSpell1 ${Spell[Equinox Brand].RankName}
	} else /if (${Me.Level}>=${Spell[Equinox Burn].Level} && ${Me.Book[${Spell[Equinox Burn].RankName}]}) {
		/varset NukeSpell1 ${Spell[Equinox Burn].RankName}
	} else /if (${Me.Level}>=${Spell[Solstice Strike].Level} && ${Me.Book[${Spell[Solstice Strike].RankName}]}) {
		/varset NukeSpell1 ${Spell[Solstice Strike].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Starfire of Ro].Level} && ${Me.Book[${Spell[Ancient Starfire of Ro].RankName}]}) {
		/varset NukeSpell1 ${Spell[Ancient Starfire of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Wildfire].Level} && ${Me.Book[${Spell[Wildfire].RankName}]}) {
		/varset NukeSpell1 ${Spell[Wildfire].RankName}
	} else /if (${Me.Level}>=${Spell[Scoriae].Level} && ${Me.Book[${Spell[Scoriae].RankName}]}) {
		/varset NukeSpell1 ${Spell[Scoriae].RankName}
	} else /if (${Me.Level}>=${Spell[Starfire].Level} && ${Me.Book[${Spell[Starfire].RankName}]}) {
		/varset NukeSpell1 ${Spell[Starfire].RankName}
	} else /if (${Me.Level}>=${Spell[Firestrike].Level} && ${Me.Book[${Spell[Firestrike].RankName}]}) {
		/varset NukeSpell1 ${Spell[Firestrike].RankName}
	} else /if (${Me.Level}>=${Spell[Combust].Level} && ${Me.Book[${Spell[Combust].RankName}]}) {
		/varset NukeSpell1 ${Spell[Combust].RankName}
	} else /if (${Me.Level}>=${Spell[Immolate].Level} && ${Me.Book[${Spell[Immolate].RankName}]}) {
		/varset NukeSpell1 ${Spell[Immolate].RankName}
	} else /if (${Me.Level}>=${Spell[Ignite].Level} && ${Me.Book[${Spell[Ignite].RankName}]}) {
		/varset NukeSpell1 ${Spell[Ignite].RankName}
	} else /if (${Me.Level}>=${Spell[Burst of Fire].Level} && ${Me.Book[${Spell[Burst of Fire].RankName}]}) {
		/varset NukeSpell1 ${Spell[Burst of Fire].RankName}
	} else /if (${Me.Level}>=${Spell[Burst of Flame].Level} && ${Me.Book[${Spell[Burst of Flame].RankName}]}) {
		/varset NukeSpell1 ${Spell[Burst of Flame].RankName}
	}
	
	
	/if (${Me.Level}>=${Spell[Wasp Swarm].Level} && ${Me.Book[${Spell[Wasp Swarm].RankName}]}) {
		/varset DoTSpell1 ${Spell[Wasp Swarm].RankName}
	} else /if (${Me.Level}>=${Spell[Swarming Death].Level} && ${Me.Book[${Spell[Swarming Death].RankName}]}) {
		/varset DoTSpell1 ${Spell[Swarming Death].RankName}
	} else /if (${Me.Level}>=${Spell[Winged Death].Level} && ${Me.Book[${Spell[Winged Death].RankName}]}) {
		/varset DoTSpell1 ${Spell[Winged Death].RankName}
	} else /if (${Me.Level}>=${Spell[Drifting Death].Level} && ${Me.Book[${Spell[Drifting Death].RankName}]}) {
		/varset DoTSpell1 ${Spell[Drifting Death].RankName}
	} else /if (${Me.Level}>=${Spell[Drones of Doom].Level} && ${Me.Book[${Spell[Drones of Doom].RankName}]}) {
		/varset DoTSpell1 ${Spell[Drones of Doom].RankName}
	} else /if (${Me.Level}>=${Spell[Stinging Swarm].Level} && ${Me.Book[${Spell[Stinging Swarm].RankName}]}) {
		/varset DoTSpell1 ${Spell[Stinging Swarm].RankName}
	} else /if (${Me.Level}>=${Spell[Flame Lick].Level} && ${Me.Book[${Spell[Flame Lick].RankName}]}) {
		/varset DoTSpell1 ${Spell[Flame Lick].RankName}
	}
|**
	/if (${Me.Level}>=${Spell[Blistering Sunray].Level} && ${Me.Book[${Spell[Blistering Sunray].RankName}]}) {
		/varset FireAcDebuff ${Spell[Blistering Sunray].RankName}
	} else /if (${Me.Level}>=${Spell[Immolation of the Sun].Level} && ${Me.Book[${Spell[Immolation of the Sun].RankName}]}) {
		/varset FireAcDebuff ${Spell[Immolation of the Sun].RankName}
	} else /if (${Me.Level}>=${Spell[Sylvan Embers].Level} && ${Me.Book[${Spell[Sylvan Embers].RankName}]}) {
		/varset FireAcDebuff ${Spell[Sylvan Embers].RankName}
	} else /if (${Me.Level}>=${Spell[Immolation of Ro].Level} && ${Me.Book[${Spell[Immolation of Ro].RankName}]}) {
		/varset FireAcDebuff ${Spell[Immolation of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Vengeance of Nature].Level} && ${Me.Book[${Spell[Vengeance of Nature].RankName}]}) {
		/varset FireAcDebuff ${Spell[Vengeance of Nature].RankName}
	} else /if (${Me.Level}>=${Spell[Breath of Ro].Level} && ${Me.Book[${Spell[Breath of Ro].RankName}]}) {
		/varset FireAcDebuff ${Spell[Breath of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Vengeance of the Wild].Level} && ${Me.Book[${Spell[Vengeance of the Wild].RankName}]}) {
		/varset FireAcDebuff ${Spell[Vengeance of the Wild].RankName}
	}
**|
	
	/if (${Me.Level}>=${Spell[Bonds of Tunare].Level} && ${Me.Book[${Spell[Bonds of Tunare].RankName}]}) {
		/varset SnareSpell ${Spell[Bonds of Tunare].RankName}
	} else /if (${Me.Level}>=${Spell[Tangle].Level} && ${Me.Book[${Spell[Tangle].RankName}]}) {
		/varset SnareSpell ${Spell[Tangle].RankName}
	} else /if (${Me.Level}>=${Spell[Ensnare].Level} && ${Me.Book[${Spell[Ensnare].RankName}]}) {
		/varset SnareSpell ${Spell[Ensnare].RankName}
	} else /if (${Me.Level}>=${Spell[Snare].Level} && ${Me.Book[${Spell[Snare].RankName}]}) {
		/varset SnareSpell ${Spell[Snare].RankName}
	}

	/if (${Me.Level}>=${Spell[Opaline Blessing].Level} && ${Me.Book[${Spell[Opaline Blessing].RankName}]}) {
		/varset GroupSkin ${Spell[Opaline Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Arcronite Blessing].Level} && ${Me.Book[${Spell[Arcronite Blessing].RankName}]}) {
		/varset GroupSkin ${Spell[Arcronite Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Shieldstone Blessing].Level} && ${Me.Book[${Spell[Shieldstone Blessing].RankName}]}) {
		/varset GroupSkin ${Spell[Shieldstone Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Granitebark Blessing].Level} && ${Me.Book[${Spell[Granitebark Blessing].RankName}]}) {
		/varset GroupSkin ${Spell[Granitebark Blessing].RankName}
	} else /if (${Me.Level}>=${Spell[Blessing of the Timbercore].Level} && ${Me.Book[${Spell[Blessing of Timbercore].RankName}]}) {
		/varset GroupSkin ${Spell[Blessing of Timbercore].RankName}
	} else /if (${Me.Level}>=${Spell[Blessing of the Heartwood].Level} && ${Me.Book[${Spell[Blessing of Heartwood].RankName}]}) {
		/varset GroupSkin ${Spell[Blessing of Heartwood].RankName}
	} else /if (${Me.Level}>=${Spell[Blessing of the Ironwood].Level} && ${Me.Book[${Spell[Blessing of Ironwood].RankName}]}) {
		/varset GroupSkin ${Spell[Blessing of Ironwood].RankName}
	} else /if (${Me.Level}>=${Spell[Blessing of the Direwild].Level} && ${Me.Book[${Spell[Blessing of Direwild].RankName}]}) {
		/varset GroupSkin ${Spell[Blessing of Direwild].RankName}
	} else /if (${Me.Level}>=${Spell[Blessing of Steeloak].Level} && ${Me.Book[${Spell[Blessing of Steeloak].RankName}]}) {
		/varset GroupSkin ${Spell[Blessing of Steeloak].RankName}
	} else /if (${Me.Level}>=${Spell[Blessing of the Nine].Level} && ${Me.Book[${Spell[Blessing of the Nine].RankName}]}) {
		/varset GroupSkin ${Spell[Blessing of the Nine].RankName}
	} else /if (${Me.Level}>=${Spell[Protection of the Glades].Level} && ${Me.Book[${Spell[Protection of the Glades].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of the Glades].RankName}
	} else /if (${Me.Level}>=${Spell[Protection of Nature].Level} && ${Me.Book[${Spell[Protection of Nature].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of Nature].RankName}
	} else /if (${Me.Level}>=${Spell[Protection of Diamond].Level} && ${Me.Book[${Spell[Protection of Diamond].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of Diamond].RankName}
	} else /if (${Me.Level}>=${Spell[Protection of Steel].Level} && ${Me.Book[${Spell[Protection of Steel].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of Steel].RankName}
	} else /if (${Me.Level}>=${Spell[Protection of Rock].Level} && ${Me.Book[${Spell[Protection of Rock].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of Rock].RankName}
	} else /if (${Me.Level}>=${Spell[Protection of Wood].Level} && ${Me.Book[${Spell[Protection of Wood].RankName}]}) {
		/varset GroupSkin ${Spell[Protection of Wood].RankName}
	}

	/if (${Me.Level}>=${Spell[Skin like Wood].Level} && ${Me.Book[${Spell[Skin like Wood].RankName}]}) {
		/varset Skin ${Spell[Skin like Wood].RankName}
	}

	/if (${Me.Level}>=${Spell[Pack Shrew].Level} && ${Me.Book[${Spell[Pack Shrew].RankName}]}) {
		/varset SoW ${Spell[Pack Shrew].RankName}
	} else /if (${Me.Level}>=${Spell[Pack Spirit].Level} && ${Me.Book[${Spell[Pack Spirit].RankName}]}) {
		/varset SoW ${Spell[Pack Spirit].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of the Shrew].Level} && ${Me.Book[${Spell[Spirit of the Shrew].RankName}]}) {
		/varset SoW ${Spell[Spirit of the Shrew].RankName}
	} else /if (${Me.Level}>=${Spell[Spirit of Wolf].Level} && ${Me.Book[${Spell[Spirit of Wolf].RankName}]}) {
		/varset SoW ${Spell[Spirit of Wolf].RankName}
	}
	
	|-TwincastSpell
	/if (${Me.Level}>=85 && ${Me.Book[${Spell[Twincast].RankName}]}) {
		/varset TwincastSpell ${Spell[Twincast].RankName}
	}



	/if (${Me.Level}>=${Spell[Legacy of Icebriars].Level} && ${Me.Book[${Spell[Legacy of Icebriars].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Icebriars].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Daggerspikes].Level} && ${Me.Book[${Spell[Legacy of Daggerspikes].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Daggerspikes].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Daggerspurs].Level} && ${Me.Book[${Spell[Legacy of Daggerspurs].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Daggerspurs].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Spikethistles].Level} && ${Me.Book[${Spell[Legacy of Spikethistles].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Spikethistles].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Spineburrs].Level} && ${Me.Book[${Spell[Legacy of Spineburrs].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Spineburrs].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Bonebriar].Level} && ${Me.Book[${Spell[Legacy of Bonebriar].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Bonebriar].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Brierbloom].Level} && ${Me.Book[${Spell[Legacy of Brierbloom].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Brierbloom].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Viridithorns].Level} && ${Me.Book[${Spell[Legacy of Viridithorns].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Viridithorns].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Viridiflora].Level} && ${Me.Book[${Spell[Legacy of Viridiflora].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Viridiflora].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Nettles].Level} && ${Me.Book[${Spell[Legacy of Nettles].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Nettles].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Bracken].Level} && ${Me.Book[${Spell[Legacy of Bracken].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Bracken].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Legacy of Blades].Level} && ${Me.Book[${Spell[Ancient Legacy of Blades].RankName}]}) {
		/varset DamageShield ${Spell[Ancient Legacy of Blades].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Thorn].Level} && ${Me.Book[${Spell[Legacy of Thorn].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Thorn].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Spike].Level} && ${Me.Book[${Spell[Legacy of Spike].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Spike].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Thorns].Level} && ${Me.Book[${Spell[Shield of Thorns].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Thorns].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Spikes].Level} && ${Me.Book[${Spell[Shield of Spikes].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Spikes].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Brambles].Level} && ${Me.Book[${Spell[Shield of Brambles].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Brambles].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Barbs].Level} && ${Me.Book[${Spell[Shield of Barbs].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Barbs].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Thistles].Level} && ${Me.Book[${Spell[Shield of Thistles].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Thistles].RankName}
	}


	/if (${Me.Level}>=${Spell[Icebriar Coat].Level} && ${Me.Book[${Spell[Icebriar Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Icebriar Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Daggerspike Coat].Level} && ${Me.Book[${Spell[Daggerspike Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Daggerspike Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Daggerspur Coat].Level} && ${Me.Book[${Spell[Daggerspur Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Daggerspur Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Spikethistle Coat].Level} && ${Me.Book[${Spell[Spikethistle Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Spikethistle Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Spineburr Coat].Level} && ${Me.Book[${Spell[Spineburr Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Spineburr Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Bonebriar Coat].Level} && ${Me.Book[${Spell[Bonebriar Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Bonebriar Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Brierbloom Coat].Level} && ${Me.Book[${Spell[Brierbloom Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Brierbloom Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Viridithorn Coat].Level} && ${Me.Book[${Spell[Viridithorn Coat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Viridithorn Coat].RankName}
	} else /if (${Me.Level}>=${Spell[Viridicoat].Level} && ${Me.Book[${Spell[Viridicoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Viridicoat].RankName}
	} else /if (${Me.Level}>=${Spell[Nettlecoat].Level} && ${Me.Book[${Spell[Nettlecoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Nettlecoat].RankName}
	} else /if (${Me.Level}>=${Spell[Brackencoat].Level} && ${Me.Book[${Spell[Brackencoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Brackencoat].RankName}
	} else /if (${Me.Level}>=${Spell[Bladecoat].Level} && ${Me.Book[${Spell[Bladecoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Bladecoat].RankName}
	} else /if (${Me.Level}>=${Spell[Thorncoat].Level} && ${Me.Book[${Spell[Thorncoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Thorncoat].RankName}
	} else /if (${Me.Level}>=${Spell[Spikecoat].Level} && ${Me.Book[${Spell[Spikecoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Spikecoat].RankName}
	} else /if (${Me.Level}>=${Spell[Bramblecoat].Level} && ${Me.Book[${Spell[Bramblecoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Bramblecoat].RankName}
	} else /if (${Me.Level}>=${Spell[Barbcoat].Level} && ${Me.Book[${Spell[Barbcoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Barbcoat].RankName}
	} else /if (${Me.Level}>=${Spell[Thistlecoat].Level} && ${Me.Book[${Spell[Thistlecoat].RankName}]}) {
		/varset SelfDamageShield ${Spell[Thistlecoat].RankName}
	}

	/if (${Me.Level}>=${Spell[Wildtender's Unity].Level} && ${Me.Book[${Spell[Wildtender's Unity].RankName}]}) {
		/varset SelfUnity ${Spell[Wildtender's Unity].RankName}
	} else /if (${Me.Level}>=${Spell[Copsetender's Unity].Level} && ${Me.Book[${Spell[Copsetender's Unity].RankName}]}) {
		/varset SelfUnity ${Spell[Copsetender's Unity].RankName}
	} else /if (${Me.Level}>=${Spell[Natural Unity].Level} && ${Me.Book[${Spell[Natural Unity].RankName}]}) {
		/varset SelfUnity ${Spell[Natural Unity].RankName}
	}

	/if (${Me.Level}>=${Spell[Restless Frost].Level} && ${Me.Book[${Spell[Restless Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Restless Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Glistening Frost].Level} && ${Me.Book[${Spell[Glistening Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Glistening Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Moonbright Frost].Level} && ${Me.Book[${Spell[Moonbright Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Moonbright Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Lustrous Frost].Level} && ${Me.Book[${Spell[Lustrous Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Lustrous Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Silver Frost].Level} && ${Me.Book[${Spell[Silver Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Silver Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Argent Frost].Level} && ${Me.Book[${Spell[Argent Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Argent Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Blanched Frost].Level} && ${Me.Book[${Spell[Blanched Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Blanched Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Gelid Frost].Level} && ${Me.Book[${Spell[Gelid Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Gelid Frost].RankName}
	} else /if (${Me.Level}>=${Spell[Hoar Frost].Level} && ${Me.Book[${Spell[Hoar Frost].RankName}]}) {
		/varset SingleFrostAtkDebuff ${Spell[Hoar Frost].RankName}
	}
	
	/if (${Me.Level}>=${Spell[Crush of Ro].Level} && ${Me.Book[${Spell[Crush of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Crush of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Clasp of Ro].Level} && ${Me.Book[${Spell[Clasp of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Clasp of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Cowl of Ro].Level} && ${Me.Book[${Spell[Cowl of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Cowl of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Clutch of Ro].Level} && ${Me.Book[${Spell[Clutch of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Clutch of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Grip of Ro].Level} && ${Me.Book[${Spell[Grip of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Grip of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Grasp of Ro].Level} && ${Me.Book[${Spell[Grasp of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Grasp of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Sun's Corona].Level} && ${Me.Book[${Spell[Sun's Corona].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Sun's Corona].RankName}
	} else /if (${Me.Level}>=${Spell[Ro's Illumination].Level} && ${Me.Book[${Spell[Ro's Illumination].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Ro's Illumination].RankName}
	} else /if (${Me.Level}>=${Spell[Hand of Ro].Level} && ${Me.Book[${Spell[Hand of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Hand of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Ro's Smoldering Disjunction].Level} && ${Me.Book[${Spell[Ro's Smoldering Disjunction].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Ro's Smoldering Disjunction].RankName}
	} else /if (${Me.Level}>=${Spell[Fixation of Ro].Level} && ${Me.Book[${Spell[Fixation of Ro].RankName}]}) {
		/varset SingleFireAtkDebuff ${Spell[Fixation of Ro].RankName}
	} 

	/if (${Me.Level}>=${Spell[Gaze of Ro].Level} && ${Me.Book[${Spell[Gaze of Ro].RankName}]}) {
		/varset AEFireAtkDebuff ${Spell[Gaze of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Column of Ro].Level} && ${Me.Book[${Spell[Column of Ro].RankName}]}) {
		/varset AEFireAtkDebuff ${Spell[Column of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Pillar of Ro].Level} && ${Me.Book[${Spell[Pillar of Ro].RankName}]}) {
		/varset AEFireAtkDebuff ${Spell[Pillar of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Glare of Ro].Level} && ${Me.Book[${Spell[Glare of Ro].RankName}]}) {
		/varset AEFireAtkDebuff ${Spell[Glare of Ro].RankName}
	} 

	
	/if (${Me.Level}>=${Spell[Feral Pack].Level} && ${Me.Book[${Spell[Feral Pack].RankName}]}) {
		/varset GroupWolfAtkBuff ${Spell[Feral Pack].RankName}
	}

 

	/if (${Me.Level}>=${Spell[Survival of the Favored].Level} && ${Me.Book[${Spell[Survival of the Favored].RankName}]}) {
		/varset Survival ${Spell[Survival of the Favored].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Auspicious].Level} && ${Me.Book[${Spell[Survival of the Auspicious].RankName}]}) {
		/varset Survival ${Spell[Survival of the Auspicious].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Serendipitous].Level} && ${Me.Book[${Spell[Survival of the Serendipitous].RankName}]}) {
		/varset Survival ${Spell[Survival of the Serendipitous].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Fortuitous].Level} && ${Me.Book[${Spell[Survival of the Fortuitous].RankName}]}) {
		/varset Survival ${Spell[Survival of the Fortuitous].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Prosperous].Level} && ${Me.Book[${Spell[Survival of the Prosperous].RankName}]}) {
		/varset Survival ${Spell[Survival of the Prosperous].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Propitious].Level} && ${Me.Book[${Spell[Survival of the Propitious].RankName}]}) {
		/varset Survival ${Spell[Survival of the Propitious].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Felicitous].Level} && ${Me.Book[${Spell[Survival of the Felicitous].RankName}]}) {
		/varset Survival ${Spell[Survival of the Felicitous].RankName}
	} else /if (${Me.Level}>=${Spell[Survival of the Fittest].Level} && ${Me.Book[${Spell[Survival of the Fittest].RankName}]}) {
		/varset Survival ${Spell[Survival of the Fittest].RankName}
	}
 
	/if (${Me.Level}>=${Spell[Defense of the Reptile].Level} && ${Me.Book[${Spell[Defense of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Defense of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Guard of the Reptile].Level} && ${Me.Book[${Spell[Guard of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Guard of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Pellicle of the Reptile].Level} && ${Me.Book[${Spell[Pellicle of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Pellicle of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Husk of the Reptile].Level} && ${Me.Book[${Spell[Husk of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Husk of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Hide of the Reptile].Level} && ${Me.Book[${Spell[Hide of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Hide of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Shell of the Reptile].Level} && ${Me.Book[${Spell[Shell of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Shell of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Carapace of the Reptile].Level} && ${Me.Book[${Spell[Carapace of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Carapace of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Scales of the Reptile].Level} && ${Me.Book[${Spell[Scales of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Scales of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Skin of the Reptile].Level} && ${Me.Book[${Spell[Skin of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Skin of the Reptile].RankName}
	}

	/if (${Me.Level}>=${Spell[Nature's Fervid Wrath].Level} && ${Me.Book[${Spell[Nature's Fervid Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Fervid Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Blistering Wrath].Level} && ${Me.Book[${Spell[Nature's Blistering Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Blistering Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Fiery Wrath].Level} && ${Me.Book[${Spell[Nature's Fiery Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Fiery Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Withering Wrath].Level} && ${Me.Book[${Spell[Nature's Withering Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Withering Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Scorching Wrath].Level} && ${Me.Book[${Spell[Nature's Scorching Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Scorching Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Incinerating Wrath].Level} && ${Me.Book[${Spell[Nature's Incinerating Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Incinerating Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Searing Wrath].Level} && ${Me.Book[${Spell[Nature's Searing Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Searing Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Burning Wrath].Level} && ${Me.Book[${Spell[Nature's Burning Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Burning Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Blazing Wrath].Level} && ${Me.Book[${Spell[Nature's Blazing Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Blazing Wrath].RankName}
	}

	/if (${Me.Level}>=${Spell[Mask of the Arboreal].Level} && ${Me.Book[${Spell[Mask of the Arboreal].RankName}]}) {
		/varset Mask ${Spell[Mask of the Arboreal].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Arbor Tender].Level} && ${Me.Book[${Spell[Mask of the Arbor Tender].RankName}]}) {
		/varset Mask ${Spell[Mask of the Arbor Tender].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Wildtender].Level} && ${Me.Book[${Spell[Mask of the Wildtender].RankName}]}) {
		/varset Mask ${Spell[Mask of the Wildtender].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Copsetender].Level} && ${Me.Book[${Spell[Mask of the Copsetender].RankName}]}) {
		/varset Mask ${Spell[Mask of the Copsetender].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Bosquetender].Level} && ${Me.Book[${Spell[Mask of the Bosquetender].RankName}]}) {
		/varset Mask ${Spell[Mask of the Bosquetender].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Thicket Dweller].Level} && ${Me.Book[${Spell[Mask of the Thicket Dweller].RankName}]}) {
		/varset Mask ${Spell[Mask of the Thicket Dweller].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Arboreal].Level} && ${Me.Book[${Spell[Mask of the Arboreal].RankName}]}) {
		/varset Mask ${Spell[Mask of the Arboreal].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Raptor].Level} && ${Me.Book[${Spell[Mask of the Raptor].RankName}]}) {
		/varset Mask ${Spell[Mask of the Raptor].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Shadowcat].Level} && ${Me.Book[${Spell[Mask of the Shadowcat].RankName}]}) {
		/varset Mask ${Spell[Mask of the Shadowcat].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Wild].Level} && ${Me.Book[${Spell[Mask of the Wild].RankName}]}) {
		/varset Mask ${Spell[Mask of the Wild].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Forest].Level} && ${Me.Book[${Spell[Mask of the Forest].RankName}]}) {
		/varset Mask ${Spell[Mask of the Forest].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Stalker].Level} && ${Me.Book[${Spell[Mask of the Stalker].RankName}]}) {
		/varset Mask ${Spell[Mask of the Hunter].RankName}
	} else /if (${Me.Level}>=${Spell[Mask of the Stalker].Level} && ${Me.Book[${Spell[Mask of the Hunter].RankName}]}) {
		/varset Mask ${Spell[Mask of the Hunter].RankName}
	}

	/delay 1s
	/call dru_load_spellbar

/return
