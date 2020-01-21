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

	/declare FireAtkDebuff 		string outer NULL
	/declare FireAcDebuff		string outer NULL
	/declare ColdAtkDebuff 		string outer NULL
	
	/declare IceDebuff 			string outer NULL
	/declare GroupWolfAtkBuff 	string outer NULL

	/declare GroupSkin 			string outer NULL
	/declare Reptile 			string outer NULL
	/declare NBW				string outer NULL
	/declare Survival 			string outer NULL
	/declare Mask 				string outer NULL
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
	/call LoadSpellGem "${Survival}" 2
	/call LoadSpellGem "${Reptile}" 3

	/call LoadSpellGem "${ColdAtkDebuff}" 4
	/call LoadSpellGem "${HealSpell2}" 5
	/call LoadSpellGem "${NBW}" 6
	/call LoadSpellGem "${NukeSpell1}" 7
	/call LoadSpellGem "${GroupHealSpell1}" 8
	
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|----------------------------------------------------------------------------
|- SUB: SetupSpells
|---------------------------------------------------------------------------- 
Sub SetupSpells

	/if (${Me.Level}>=${Spell[Puravida].Level} && ${Me.Book[${Spell[Puravida].RankName}]}) {
		/varset HealSpell1 ${Spell[Puravida].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Chlorobon].Level} && ${Me.Book[${Spell[Ancient Chlorobon].RankName}]}) {
		/varset HealSpell1 ${Spell[Ancient Chlorobon].RankName}
	} else /if (${Me.Level}>=${Spell[Chlorotrope].Level} && ${Me.Book[${Spell[Chlorotrope].RankName}]}) {
		/varset HealSpell1 ${Spell[Chlorotrope].RankName}
	} else /if (${Me.Level}>=${Spell[Sylvan Infusion].Level} && ${Me.Book[${Spell[Sylvan Infusion].RankName}]}) {
		/varset HealSpell1 ${Spell[Sylvan Infusion].RankName}
	} else /if (${Me.Level}>=${Spell[Karana's Renewal].Level} && ${Me.Book[${Spell[Karana's Renewal].RankName}]}) {
		/varset HealSpell1 ${Spell[Karana's Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Infusion].Level} && ${Me.Book[${Spell[Nature's Infusion].RankName}]}) {
		/varset HealSpell1 ${Spell[Nature's Infusion].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Touch].Level} && ${Me.Book[${Spell[Nature's Touch].RankName}]}) {
		/varset HealSpell1 ${Spell[Nature's Touch].RankName}
	} else /if (${Me.Level}>=${Spell[Tunare's Renewal].Level} && ${Me.Book[${Spell[Tunare's Renewal].RankName}]}) {
		/varset HealSpell1 ${Spell[Tunare's Renewal].RankName}
	} else /if (${Me.Level}>=${Spell[Superior Healing].Level} && ${Me.Book[${Spell[Superior Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Superior Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Greater Healing].Level} && ${Me.Book[${Spell[Greater Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Greater Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Healing].Level} && ${Me.Book[${Spell[Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Light Healing].Level} && ${Me.Book[${Spell[Light Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Light Healing].RankName}
	} else /if (${Me.Level}>=${Spell[Minor Healing].Level} && ${Me.Book[${Spell[Minor Healing].RankName}]}) {
		/varset HealSpell1 ${Spell[Minor Healing].RankName}
	}

	/if (${Me.Level}>=${Spell[Adrenaline Swell].Level} && ${Me.Book[${Spell[Adrenaline Swell].RankName}]}) {
		/varset HealSpell2 ${Spell[Adrenaline Swell].RankName}
	} else /if (${Me.Level}>=${Spell[Adrenaline Surge].Level} && ${Me.Book[${Spell[Adrenaline Surge].RankName}]}) {
		/varset HealSpell2 ${Spell[Adrenaline Surge].RankName}
	}

	/if (${Me.Level}>=${Spell[Crescentbloom].Level} && ${Me.Book[${Spell[Crescentbloom].RankName}]}) {
		/varset GroupHealSpell1 ${Spell[Crescentbloom].RankName}
	}

	/if (${Me.Level}>=${Spell[Equinox Brand].Level} && ${Me.Book[${Spell[Equinox Brand].RankName}]}) {
		/varset NukeSpell1 ${Spell[Equinox Brand].RankName}
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

	
	/if (${Me.Level}>=${Spell[Bonds of Tunare].Level} && ${Me.Book[${Spell[Bonds of Tunare].RankName}]}) {
		/varset SnareSpell ${Spell[Bonds of Tunare].RankName}
	} else /if (${Me.Level}>=${Spell[Tangle].Level} && ${Me.Book[${Spell[Tangle].RankName}]}) {
		/varset SnareSpell ${Spell[Tangle].RankName}
	} else /if (${Me.Level}>=${Spell[Ensnare].Level} && ${Me.Book[${Spell[Ensnare].RankName}]}) {
		/varset SnareSpell ${Spell[Ensnare].RankName}
	} else /if (${Me.Level}>=${Spell[Snare].Level} && ${Me.Book[${Spell[Snare].RankName}]}) {
		/varset SnareSpell ${Spell[Snare].RankName}
	}

	
	
	/if (${Me.Level}>=${Spell[Blessing of the Ironwood].Level} && ${Me.Book[${Spell[Blessing of Ironwood].RankName}]}) {
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
		

	/if (${Me.Level}>=${Spell[Legacy of Viridithorns].Level} && ${Me.Book[${Spell[Legacy of Viridithorns].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Viridithorns].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Viridiflora].Level} && ${Me.Book[${Spell[Legacy of Viridiflora].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Viridiflora].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient Legacy of Blades].Level} && ${Me.Book[${Spell[Ancient Legacy of Blades].RankName}]}) {
		/varset DamageShield ${Spell[Ancient Legacy of Blades].RankName}
	} else /if (${Me.Level}>=${Spell[Legacy of Thorn].Level} && ${Me.Book[${Spell[Legacy of Thorn].RankName}]}) {
		/varset DamageShield ${Spell[Legacy of Thorn].RankName}
	} else /if (${Me.Level}>=${Spell[Shield of Blades].Level} && ${Me.Book[${Spell[Shield of Blades].RankName}]}) {
		/varset DamageShield ${Spell[Shield of Blades].RankName}
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


	
	/if (${Me.Level}>=${Spell[Torrid Sunray].Level} && ${Me.Book[${Spell[Torrid Sunray].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Torrid Sunray].RankName}
	} else /if (${Me.Level}>=${Spell[Sun's Corona].Level} && ${Me.Book[${Spell[Sun's Corona].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Sun's Corona].RankName}
	} else /if (${Me.Level}>=${Spell[Ro's Illumination].Level} && ${Me.Book[${Spell[Ro's Illumination].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Ro's Illumination].RankName}
	} else /if (${Me.Level}>=${Spell[Hand of Ro].Level} && ${Me.Book[${Spell[Hand of Ro].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Hand of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Ro's Smoldering Disjunction].Level} && ${Me.Book[${Spell[Ro's Smoldering Disjunction].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Ro's Smoldering Disjunction].RankName}
	} else /if (${Me.Level}>=${Spell[Fixation of Ro].Level} && ${Me.Book[${Spell[Fixation of Ro].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Fixation of Ro].RankName}
	} else /if (${Me.Level}>=${Spell[Ro's Fiery Sundering].Level} && ${Me.Book[${Spell[Ro's Fiery Sundering].RankName}]}) {
		/varset FireAtkDebuff ${Spell[Ro's Fiery Sundering].RankName}
	}

	/if (${Me.Level}>=${Spell[Chillvapor Breath].Level} && ${Me.Book[${Spell[Chillvapor Breath].RankName}]}) {
		/varset ColdAtkDebuff ${Spell[Chillvapor Breath].RankName}
	} else /if (${Me.Level}>=${Spell[Gelid Frost].Level} && ${Me.Book[${Spell[Gelid Frost].RankName}]}) {
		/varset ColdAtkDebuff ${Spell[Gelid Frost].RankName}
	}
	
	/if (${Me.Level}>=${Spell[Feral Pack].Level} && ${Me.Book[${Spell[Feral Pack].RankName}]}) {
		/varset GroupWolfAtkBuff ${Spell[Feral Pack].RankName}
	}

	/if (${Me.Level}>=${Spell[Survival of the Fittest].Level} && ${Me.Book[${Spell[Survival of the Fittest].RankName}]}) {
		/varset Survival ${Spell[Survival of the Fittest].RankName}
	}

	/if (${Me.Level}>=${Spell[Scales of the Reptile].Level} && ${Me.Book[${Spell[Scales of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Scales of the Reptile].RankName}
	} else /if (${Me.Level}>=${Spell[Skin of the Reptile].Level} && ${Me.Book[${Spell[Skin of the Reptile].RankName}]}) {
		/varset Reptile ${Spell[Skin of the Reptile].RankName}
	}

	/if (${Me.Level}>=${Spell[Nature's Burning Wrath].Level} && ${Me.Book[${Spell[Nature's Burning Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Burning Wrath].RankName}
	} else /if (${Me.Level}>=${Spell[Nature's Blazing Wrath].Level} && ${Me.Book[${Spell[Nature's Blazing Wrath].RankName}]}) {
		/varset NBW ${Spell[Nature's Blazing Wrath].RankName}
	}

	/if (${Me.Level}>=${Spell[Mask of the Shadowcat].Level} && ${Me.Book[${Spell[Mask of the Shadowcat].RankName}]}) {
		/varset Mask ${Spell[Mask of the Shadowcat].RankName}
	}

/return
