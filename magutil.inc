|- ihcwizutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|- Thanks to Saar for additions and bug fixes
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub mag_setup
|-Declare AA and Spell variables
  |-Buffs
	/declare SelfHPBuff				string	outer	NULL
	/declare SelfRune1				string	outer	NULL
  |-Debuff
	/declare StripBuffSpell			string	outer	NULL
  |-DPS
  	/declare Aura1					string  outer   NULL
	/declare Aura2					string  outer   NULL
	
    /declare AllianceSpell			string	outer	NULL
	/declare DichoSpell				string 	outer	NULL
	/declare ServantSpell			string 	outer	NULL
	/declare ManySpell	    		string 	outer	NULL
	/declare ChaoticSpell			string 	outer	NULL
	/declare SpearSpell1     		string 	outer	NULL
    /declare SpearSpell2     		string 	outer	NULL
    /declare Malo                   string  outer   NULL
    /declare SummonOrbSpell         string  outer   NULL
	
    /declare ModRodSpell			string 	outer	NULL
	
	
    /declare TwincastSpell			string 	outer	NULL
    /declare DamageShieldSpell		string 	outer	NULL
  |-Pet
	/declare PetSpell				string	outer	NULL
    /declare PetBuff        		string 	outer	NULL
    /declare PetToysPlate			string 	outer	NULL
    /declare PetToysJewlry			string 	outer	NULL
    /declare PetToysWeps			string 	outer	NULL

/return
|* ------------------------------------------------------------------------------------------
| SUB: load_spellbar
|------------------------------------------------------------------------------------------ *|
Sub mag_load_spellbar
	
	/if (${Me.Standing}) /sit
	/delay 10 ${Me.Sitting}
	/echo \aw Loading Spell Bar
	/call LoadSpellGem "${SpearSpell1}" 1
	/call LoadSpellGem "${SpearSpell2}" 2
	/call LoadSpellGem "${ChaoticSpell}" 3
    /call LoadSpellGem "${ManySpell}" 4
	/call LoadSpellGem "${ServantSpell}" 5
	/call LoadSpellGem "${Malo}" 6
    /call LoadSpellGem "${TwincastSpell}" 7
	/call LoadSpellGem "${}" 8
	
    |**
	/if (${Me.Book[${TwincastSpell}]}) {
		/call LoadSpellGem "${TwincastSpell}" 4
	} else {
		/call LoadSpellGem "${WildNuke}" 4
	}


	/if (${Me.Book[${SelfRune1}]}) {
		/call LoadSpellGem "${SelfRune1}" 5
	} else /if (${Me.Book[${RootSpell}]}) {
		/call LoadSpellGem "${RootSpell}" 5
	}
	/call LoadSpellGem "${FireEtherealNuke}" 6
	/call LoadSpellGem "${ColdEtherealNuke}" 7

	/if (${GambitSpell.NotEqual[NULL]} && ${Me.Book[${GambitSpell}]}) {
		/call LoadSpellGem "${GambitSpell}" 8
	} else {
		/call LoadSpellGem "${HarvestSpell1}" 8
	}
    **|


	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) {
		
	} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==4) {
		
	
	} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==3) {
		/call LoadSpellGem "${}" 5
		/call LoadSpellGem "${}" 6
		/call LoadSpellGem "${}" 7
		/call LoadSpellGem "${}" 8
		/call LoadSpellGem "${}" 9
		/call LoadSpellGem "${}" 10

	} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==2) {
		/call LoadSpellGem "${}" 5
		/call LoadSpellGem "${}" 6
		/call LoadSpellGem "${}" 7
		/call LoadSpellGem "${}" 8
		/call LoadSpellGem "${}" 9

	} else /if (${Me.AltAbility[Mnemonic Retention].Rank}==1) {
		/call LoadSpellGem "${}" 5
		|-6
		|-7
		/call LoadSpellGem "${}" 8
	} else {
		|-6
		
	}
	
	/delay 2s
	/if (${Me.Sitting}) /stand
	/delay 10 ${Me.Standing}
/return 
|* ------------------------------------------------------------------------------------------
| SUB: SetWizSpells
|------------------------------------------------------------------------------------------ *|
Sub mag_abilities

    
    /if (${Me.Level}>=${Spell[Summon Firebound Orb].Level} && ${Me.Book[${Spell[Summon Firebound Orb].RankName}]}) {
		/varset SummonOrbSpell ${Spell[Summon Firebound Orb].RankName}
	} else /if (${Me.Level}>=${Spell[Summon Blazing Orb].Level} && ${Me.Book[${Spell[Summon Blazing Orb].RankName}]}) {
		/varset SummonOrbSpell ${Spell[Summon Blazing Orb].RankName}
	}

| Burnout V

    /if (${Me.Level}>=${Spell[Manifestation of Air].Level} && ${Me.Book[${Spell[Manifestation of Air].RankName}]}) {
		/varset PetSpell ${Spell[Manifestation of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Embodiment of Air].Level} && ${Me.Book[${Spell[Embodiment of Air].RankName}]}) {
		/varset PetSpell ${Spell[Embodiment of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Convocation of Air].Level} && ${Me.Book[${Spell[Convocation of Air].RankName}]}) {
		/varset PetSpell ${Spell[Convocation of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Shard of Air].Level} && ${Me.Book[${Spell[Shard of Air].RankName}]}) {
		/varset PetSpell ${Spell[Shard of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Facet of Air].Level} && ${Me.Book[${Spell[Facet of Air].RankName}]}) {
		/varset PetSpell ${Spell[Facet of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Construct of Air].Level} && ${Me.Book[${Spell[Construct of Air].RankName}]}) {
		/varset PetSpell ${Spell[Construct of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Aspect of Air].Level} && ${Me.Book[${Spell[Aspect of Air].RankName}]}) {
		/varset PetSpell ${Spell[Aspect of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Core of Air].Level} && ${Me.Book[${Spell[Core of Air].RankName}]}) {
		/varset PetSpell ${Spell[Core of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Essence of Air].Level} && ${Me.Book[${Spell[Essence of Air].RankName}]}) {
		/varset PetSpell ${Spell[Essence of Air].RankName}
	} else /if (${Me.Level}>=${Spell[Child of Wind].Level} && ${Me.Book[${Spell[Child of Wind].RankName}]}) {
		/varset PetSpell ${Spell[Child of Wind].RankName}
	} else /if (${Me.Level}>=${Spell[Ward of Xegony].Level} && ${Me.Book[${Spell[Ward of Xegony].RankName}]}) {
		/varset PetSpell ${Spell[Ward of Xegony].RankName}
	} else /if (${Me.Level}>=${Spell[Greater Vocaration: Air].Level} && ${Me.Book[${Spell[Greater Vocaration: Air].RankName}]}) {
		/varset PetSpell ${Spell[Greater Vocaration: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Greater Conjuration: Air].Level} && ${Me.Book[${Spell[Greater Conjuration: Air].RankName}]}) {
		/varset PetSpell ${Spell[Greater Conjuration: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Conjuration: Air].Level} && ${Me.Book[${Spell[Conjuration: Air].RankName}]}) {
		/varset PetSpell ${Spell[Conjuration: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Lesser Conjuration: Air].Level} && ${Me.Book[${Spell[Lesser Conjuration: Air].RankName}]}) {
		/varset PetSpell ${Spell[Lesser Conjuration: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Minor Conjuration: Air].Level} && ${Me.Book[${Spell[Minor Conjuration: Air].RankName}]}) {
		/varset PetSpell ${Spell[Minor Conjuration: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Summoning: Air].Level} && ${Me.Book[${Spell[Summoning: Air].RankName}]}) {
		/varset PetSpell ${Spell[Summoning: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Lesser Summoning: Air].Level} && ${Me.Book[${Spell[Lesser Summoning: Air].RankName}]}) {
		/varset PetSpell ${Spell[Lesser Summoning: Air Shielding].RankName}
	} else /if (${Me.Level}>=${Spell[Elemental: Air].Level} && ${Me.Book[${Spell[Elemental: Air].RankName}]}) {
		/varset PetSpell ${Spell[Elemental: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Elementaling: Air].Level} && ${Me.Book[${Spell[Elementaling: Air].RankName}]}) {
		/varset PetSpell ${Spell[Elementaling: Air].RankName}
	} else /if (${Me.Level}>=${Spell[Elementalkin: Air].Level} && ${Me.Book[${Spell[Elementalkin: Air].RankName}]}) {
		/varset PetSpell ${Spell[Elementalkin: Air].RankName}
	}


    
    /if (${Me.Level}>=${Spell[Grant Ocoenydd's Plate].Level} && ${Me.Book[${Spell[Grant Ocoenydd's Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Grant Ocoenydd's Plate].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Wirn's Plate].Level} && ${Me.Book[${Spell[Grant Wirn's Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Grant Wirn's Plate].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Thassis' Plate].Level} && ${Me.Book[${Spell[Grant Thassis' Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Grant Thassis' Plate].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Frightforged Plate].Level} && ${Me.Book[${Spell[Grant Frightforged Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Grant Frightforged Plate].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Manaforged Plate].Level} && ${Me.Book[${Spell[Grant Manaforged Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Grant Manaforged Plate].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Spectral Plate].Level} && ${Me.Book[${Spell[Grant Spectral Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Grant Spectral Plate].RankName}
	} else /if (${Me.Level}>=${Spell[Summon Plate of the Prime].Level} && ${Me.Book[${Spell[Summon Plate of the Prime].RankName}]}) {
		/varset PetToysPlate ${Spell[Summon Plate of the Prime].RankName}
	} else /if (${Me.Level}>=${Spell[Summon Plate of the Elements].Level} && ${Me.Book[${Spell[Summon Plate of the Elements].RankName}]}) {
		/varset PetToysPlate ${Spell[Summon Plate of the Elements].RankName}
	} else /if (${Me.Level}>=${Spell[Summon Phantom Plate].Level} && ${Me.Book[${Spell[Summon Phantom Plate].RankName}]}) {
		/varset PetToysPlate ${Spell[Summon Phantom Plate].RankName}
	}
    

    /if (${Me.Level}>=${Spell[Grant Crystasia's Heirlooms].Level} && ${Me.Book[${Spell[Grant Crystasia's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Crystasia's Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Ioulin's Heirlooms].Level} && ${Me.Book[${Spell[Grant Ioulin's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Ioulin's Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Calix's Heirlooms].Level} && ${Me.Book[${Spell[Grant Calix's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Calix's Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Nint's Heirlooms].Level} && ${Me.Book[${Spell[Grant Nint's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Nint's Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Atleris' Heirlooms].Level} && ${Me.Book[${Spell[Grant Atleris' Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Atleris' Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Enibik's Heirlooms].Level} && ${Me.Book[${Spell[Grant Enibik's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Enibik's Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Summon Zabella's Heirlooms].Level} && ${Me.Book[${Spell[Summon Zabella's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Summon Zabella's Heirlooms].RankName}
	} else /if (${Me.Level}>=${Spell[Summon Nastel's Heirlooms].Level} && ${Me.Book[${Spell[Summon Nastel's Heirlooms].RankName}]}) {
		/varset PetToysJewlry ${Spell[Summon Nastel's Heirlooms].RankName}
	}

   
	/if (${Me.Level}>=${Spell[Grant Yalrek's Armaments].Level} && ${Me.Book[${Spell[Grant Yalrek's Armaments].RankName}]}) {
		/varset PetToysWeps ${Spell[Grant Yalrek's Armaments].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Wirn's Armaments].Level} && ${Me.Book[${Spell[Grant Wirn's Armaments].RankName}]}) {
		/varset PetToysWeps ${Spell[Grant Wirn's Armaments].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Thassis' Armaments].Level} && ${Me.Book[${Spell[Grant Thassis' Armaments].RankName}]}) {
		/varset PetToysWeps ${Spell[Grant Thassis' Armaments].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Frightforged Armaments].Level} && ${Me.Book[${Spell[Grant Frightforged Armaments].RankName}]}) {
		/varset PetToysWeps ${Spell[Grant Frightforged Armaments].RankName}
    } else /if (${Me.Level}>=${Spell[Grant Manaforged Armaments].Level} && ${Me.Book[${Spell[Grant Manaforged Armaments].RankName}]}) {
		/varset PetToysJewlry ${Spell[Grant Manaforged Armaments].RankName}
	} else /if (${Me.Level}>=${Spell[Grant Spectral Armaments].Level} && ${Me.Book[${Spell[Grant Spectral Armaments].RankName}]}) {
		/varset PetToysWeps ${Spell[Grant Spectral Armaments].RankName}
	}


    /if (${Me.Level}>=${Spell[Burnout XIV].Level} && ${Me.Book[${Spell[Burnout XIV].RankName}]}) {
		/varset PetBuff ${Spell[Burnout XIV].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout XIII].Level} && ${Me.Book[${Spell[Burnout XIII].RankName}]}) {
		/varset PetBuff ${Spell[Burnout XIII].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout XII].Level} && ${Me.Book[${Spell[Burnout XII].RankName}]}) {
		/varset PetBuff ${Spell[Burnout XII].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout XI].Level} && ${Me.Book[${Spell[Burnout XI].RankName}]}) {
		/varset PetBuff ${Spell[Burnout XI].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout X].Level} && ${Me.Book[${Spell[Burnout X].RankName}]}) {
		/varset PetBuff ${Spell[Burnout X].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout IX].Level} && ${Me.Book[${Spell[Burnout IX].RankName}]}) {
		/varset PetBuff ${Spell[Burnout IX].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout VIII].Level} && ${Me.Book[${Spell[Burnout VIII].RankName}]}) {
		/varset PetBuff ${Spell[Burnout VIII].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout VII].Level} && ${Me.Book[${Spell[Burnout VII].RankName}]}) {
		/varset PetBuff ${Spell[Burnout VII].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout VI].Level} && ${Me.Book[${Spell[Burnout VI].RankName}]}) {
		/varset PetBuff ${Spell[Burnout VI].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout V].Level} && ${Me.Book[${Spell[Burnout V].RankName}]}) {
		/varset PetBuff ${Spell[Burnout V].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient: Burnout Blaze].Level} && ${Me.Book[${Spell[Ancient: Burnout Blaze].RankName}]}) {
		/varset PetBuff ${Spell[Ancient: Burnout Blaze].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout IV].Level} && ${Me.Book[${Spell[Burnout IV].RankName}]}) {
		/varset PetBuff ${Spell[Burnout IV].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout III].Level} && ${Me.Book[${Spell[Burnout III].RankName}]}) {
		/varset PetBuff ${Spell[Burnout III].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout II].Level} && ${Me.Book[${Spell[Burnout II].RankName}]}) {
		/varset PetBuff ${Spell[Burnout II].RankName}
	} else /if (${Me.Level}>=${Spell[Burnout].Level} && ${Me.Book[${Spell[Burnout].RankName}]}) {
		/varset PetBuff ${Spell[Burnout].RankName}
	}



    /if (${Me.Level}>=${Spell[Chaotic Pyroclasm].Level} && ${Me.Book[${Spell[Chaotic Pyroclasm].RankName}]}) {
		/varset ChaoticSpell ${Spell[Chaotic Pyroclasm].RankName}
	} else /if (${Me.Level}>=${Spell[Chaotic Inferno].Level} && ${Me.Book[${Spell[Chaotic Inferno].RankName}]}) {
		/varset ChaoticSpell ${Spell[Chaotic Inferno].RankName}
	} else /if (${Me.Level}>=${Spell[Chaotic Fire].Level} && ${Me.Book[${Spell[Chaotic Fire].RankName}]}) {
		/varset ChaoticSpell ${Spell[Chaotic Fire].RankName}
	}


    /if (${Me.Level}>=${Spell[Riotous Servant].Level} && ${Me.Book[${Spell[Riotous Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Riotous Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Reckless Servant].Level} && ${Me.Book[${Spell[Reckless Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Reckless Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Relentless Servant].Level} && ${Me.Book[${Spell[Relentless Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Relentless Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Ruthless Servant].Level} && ${Me.Book[${Spell[Ruthless Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Ruthless Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Ruinous Servant].Level} && ${Me.Book[${Spell[Ruinous Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Ruinous Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Rumbling Servant].Level} && ${Me.Book[${Spell[Rumbling Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Rumbling Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Rancorous Servant].Level} && ${Me.Book[${Spell[Rancorous Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Rancorous Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Rampaging Servant].Level} && ${Me.Book[${Spell[Rampaging Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Rampaging Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Raging Servant].Level} && ${Me.Book[${Spell[Raging Servant].RankName}]}) {
		/varset ServantSpell ${Spell[Raging Servant].RankName}
	}

    /if (${Me.Level}>=${Spell[Malosenia].Level} && ${Me.Book[${Spell[Malosenia].RankName}]}) {
		/varset Malo ${Spell[Malosenia].RankName}
	} else /if (${Me.Level}>=${Spell[Malosinara].Level} && ${Me.Book[${Spell[Malosinara].RankName}]}) {
		/varset Malo ${Spell[Malosinara].RankName}
	} else /if (${Me.Level}>=${Spell[Malosinata].Level} && ${Me.Book[${Spell[Malosinata].RankName}]}) {
		/varset Malo ${Spell[Malosinata].RankName}
	} else /if (${Me.Level}>=${Spell[Malosenete].Level} && ${Me.Book[${Spell[Malosenete].RankName}]}) {
		/varset Malo ${Spell[Malosenete].RankName}
	} else /if (${Me.Level}>=${Spell[Maloseneta].Level} && ${Me.Book[${Spell[Maloseneta].RankName}]}) {
		/varset Malo ${Spell[Maloseneta].RankName}
	} else /if (${Me.Level}>=${Spell[Malosene].Level} && ${Me.Book[${Spell[Malosene].RankName}]}) {
		/varset Malo ${Spell[Malosene].RankName}
	} else /if (${Me.Level}>=${Spell[Malosenea].Level} && ${Me.Book[${Spell[Malosenea].RankName}]}) {
		/varset Malo ${Spell[Malosenea].RankName}
	} else /if (${Me.Level}>=${Spell[Malosinatia].Level} && ${Me.Book[${Spell[Malosinatia].RankName}]}) {
		/varset Malo ${Spell[Malosinatia].RankName}
	} else /if (${Me.Level}>=${Spell[Malosinise].Level} && ${Me.Book[${Spell[Malosinise].RankName}]}) {
		/varset Malo ${Spell[Malosinise].RankName}
	} else /if (${Me.Level}>=${Spell[Malosinia].Level} && ${Me.Book[${Spell[Malosinia].RankName}]}) {
		/varset Malo ${Spell[Malosinia].RankName}
	} else /if (${Me.Level}>=${Spell[Malosini].Level} && ${Me.Book[${Spell[Malosini].RankName}]}) {
		/varset Malo ${Spell[Malosini].RankName}
	} else /if (${Me.Level}>=${Spell[Malosi].Level} && ${Me.Book[${Spell[Malosi].RankName}]}) {
		/varset Malo ${Spell[Malosi].RankName}
	}


    /if (${Me.Level}>=${Spell[Remorseless Servant].Level} && ${Me.Book[${Spell[Remorseless Servant].RankName}]}) {
		/varset ManySpell ${Spell[Remorseless Servant].RankName}
	} else /if (${Me.Level}>=${Spell[Volley of Many].Level} && ${Me.Book[${Spell[Volley of Many].RankName}]}) {
		/varset ManySpell ${Spell[Volley of Many].RankName}
	} else /if (${Me.Level}>=${Spell[Storm of Many].Level} && ${Me.Book[${Spell[Storm of Many].RankName}]}) {
		/varset ManySpell ${Spell[Storm of Many].RankName}
	} else /if (${Me.Level}>=${Spell[Salvo of Many].Level} && ${Me.Book[${Spell[Salvo of Many].RankName}]}) {
		/varset ManySpell ${Spell[Salvo of Many].RankName}
	} else /if (${Me.Level}>=${Spell[Strike of Many].Level} && ${Me.Book[${Spell[Strike of Many].RankName}]}) {
		/varset ManySpell ${Spell[Strike of Many].RankName}
	} else /if (${Me.Level}>=${Spell[Clash of Many].Level} && ${Me.Book[${Spell[Clash of Many].RankName}]}) {
		/varset ManySpell ${Spell[Clash of Many].RankName}
	} else /if (${Me.Level}>=${Spell[Jolt of Many].Level} && ${Me.Book[${Spell[Jolt of Many].RankName}]}) {
		/varset ManySpell ${Spell[Jolt of Many].RankName}
	} else /if (${Me.Level}>=${Spell[Shock of Many].Level} && ${Me.Book[${Spell[Shock of Many].RankName}]}) {
		/varset ManySpell ${Spell[Shock of Many].RankName}
	}

    /if (${Me.Level}>=${Spell[Spear of Molten Komatiite].Level} && ${Me.Book[${Spell[Spear of Molten Komatiite].RankName}]}) {
		/varset SpearSpell1 ${Spell[Spear of Molten Komatiite].RankName}
        /varset SpearSpell2 ${Spell[Spear of Molten Arcronite].RankName}

	} else /if (${Me.Level}>=${Spell[Spear of Molten Arcronite].Level} && ${Me.Book[${Spell[Spear of Molten Arcronite].RankName}]}) {
		/varset SpearSpell1 ${Spell[Spear of Molten Arcronite].RankName}
        /varset SpearSpell2 ${Spell[Spear of Molten Shieldstone].RankName}

	} else /if (${Me.Level}>=${Spell[Spear of Molten Shieldstone].Level} && ${Me.Book[${Spell[Spear of Molten Shieldstone].RankName}]}) {
		/varset SpearSpell1 ${Spell[Spear of Molten Shieldstone].RankName}
        /varset SpearSpell2 ${Spell[Spear of Blistersteel].RankName}

	} else /if (${Me.Level}>=${Spell[Spear of Blistersteel].Level} && ${Me.Book[${Spell[Spear of Blistersteel].RankName}]}) {
		/varset SpearSpell1 ${Spell[Spear of Blistersteel].RankName}
        /varset SpearSpell2 ${Spell[Spear of Molten Steel].RankName}

	} else /if (${Me.Level}>=${Spell[Spear of Molten Steel].Level} && ${Me.Book[${Spell[Spear of Molten Steel].RankName}]}) {
		/varset SpearSpell1 ${Spell[Spear of Molten Steel].RankName}
        /varset SpearSpell2 ${Spell[Spear of Magma].RankName}

	} else /if (${Me.Level}>=${Spell[Spear of Magma].Level} && ${Me.Book[${Spell[Spear of Magma].RankName}]}) {
		/varset SpearSpell1 ${Spell[Spear of Magma].RankName}
        /varset SpearSpell2 ${Spell[Bolt of Molten Steel].RankName}

	} else /if (${Me.Level}>=${Spell[Bolt of Rhyolite].Level} && ${Me.Book[${Spell[Bolt of Rhyolite].RankName}]}) {
		/varset SpearSpell1 ${Spell[Bolt of Rhyolite].RankName}
        /varset SpearSpell2 ${Spell[Bolt of Scoria].RankName}
	} else /if (${Me.Level}>=${Spell[Bolt of Molten Scoria].Level} && ${Me.Book[${Spell[Bolt of Molten Scoria].RankName}]}) {
		/varset SpearSpell1 ${Spell[Bolt of Molten Scoria].RankName}
        /varset SpearSpell2 ${Spell[Bolt of Molten Dross].RankName}
	} else /if (${Me.Level}>=${Spell[Bolt of Molten Dross].Level} && ${Me.Book[${Spell[Bolt of Molten Dross].RankName}]}) {
		/varset SpearSpell1 ${Spell[Bolt of Molten Dross].RankName}
        /varset SpearSpell2 ${Spell[Bolt of Molten Slag].RankName}
	} else /if (${Me.Level}>=${Spell[Bolt of Molten Slag].Level} && ${Me.Book[${Spell[Bolt of Molten Slag].RankName}]}) {
		/varset SpearSpell1 ${Spell[Bolt of Molten Slag].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient: Nova Strike].Level} && ${Me.Book[${Spell[Ancient: Nova Strike].RankName}]}) {
		/varset SpearSpell1 ${Spell[Ancient: Nova Strike].RankName}
	} else /if (${Me.Level}>=${Spell[Bolt of Jerikor].Level} && ${Me.Book[${Spell[Bolt of Jerikor].RankName}]}) {
		/varset SpearSpell1 ${Spell[Bolt of Jerikor].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient: Chaos Vortex].Level} && ${Me.Book[${Spell[Ancient: Chaos Vortex].RankName}]}) {
		/varset SpearSpell1 ${Spell[Ancient: Chaos Vortex].RankName}
	} else /if (${Me.Level}>=${Spell[Firebolt of Tallon].Level} && ${Me.Book[${Spell[Firebolt of Tallon].RankName}]}) {
		/varset SpearSpell1 ${Spell[Firebolt of Tallon].RankName}
	} else /if (${Me.Level}>=${Spell[Ancient: Shock of Sun].Level} && ${Me.Book[${Spell[Ancient: Shock of Sun].RankName}]}) {
		/varset SpearSpell1 ${Spell[Ancient: Shock of Sun].RankName}
	} else /if (${Me.Level}>=${Spell[Shock of Fiery Blades].Level} && ${Me.Book[${Spell[Shock of Fiery Blades].RankName}]}) {
		/varset SpearSpell1 ${Spell[Shock of Fiery Blades].RankName}
	} else /if (${Me.Level}>=${Spell[Seeking Flame of Seukor].Level} && ${Me.Book[${Spell[Seeking Flame of Seukor].RankName}]}) {
		/varset SpearSpell1 ${Spell[Seeking Flame of Seukor].RankName}
	} else /if (${Me.Level}>=${Spell[Scars of Sigil].Level} && ${Me.Book[${Spell[Scars of Sigil].RankName}]}) {
		/varset SpearSpell1 ${Spell[Scars of Sigil].RankName}
	} else /if (${Me.Level}>=${Spell[Char].Level} && ${Me.Book[${Spell[Char].RankName}]}) {
		/varset SpearSpell1 ${Spell[Char].RankName}
	} else /if (${Me.Level}>=${Spell[Lava Bolt].Level} && ${Me.Book[${Spell[Lava Bolt].RankName}]}) {
		/varset SpearSpell1 ${Spell[Lava Bolt].RankName}
	} else /if (${Me.Level}>=${Spell[Cinder Bolt].Level} && ${Me.Book[${Spell[Cinder Bolt].RankName}]}) {
		/varset SpearSpell1 ${Spell[Cinder Bolt].RankName}
	} else /if (${Me.Level}>=${Spell[Blaze].Level} && ${Me.Book[${Spell[Blaze].RankName}]}) {
		/varset SpearSpell1 ${Spell[Blaze].RankName}
	} else /if (${Me.Level}>=${Spell[Bolt of Flame].Level} && ${Me.Book[${Spell[Bolt of Flame].RankName}]}) {
		/varset SpearSpell1 ${Spell[Bolt of Flame].RankName}
	} else /if (${Me.Level}>=${Spell[Shock of Flame].Level} && ${Me.Book[${Spell[Shock of Flame].RankName}]}) {
		/varset SpearSpell1 ${Spell[Shock of Flame].RankName}
	} else /if (${Me.Level}>=${Spell[Flame Bolt].Level} && ${Me.Book[${Spell[Flame Bolt].RankName}]}) {
		/varset SpearSpell1 ${Spell[Flame Bolt].RankName}
	} else /if (${Me.Level}>=${Spell[Burn].Level} && ${Me.Book[${Spell[Burn].RankName}]}) {
		/varset SpearSpell1 ${Spell[Burn].RankName}
	} else /if (${Me.Level}>=${Spell[Burst of Flame].Level} && ${Me.Book[${Spell[Burst of Flame].RankName}]}) {
		/varset SpearSpell1 ${Spell[Burst of Flame].RankName}
	}


|-Self HP Buff * Var Name: SelfHPBuff string outer
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Shield of Scales].RankName}]}) {
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
	} else /if (${Me.Level}>=102 && ${Me.Book[${Spell[Frostbound Alliance].RankName}]}) {
		/varset AllianceSpell ${Spell[Frostbound Alliance].RankName}
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
|-JoltSpell
	/if (${Me.Level}>=106 && ${Me.Book[${Spell[Concussive Volley].RankName}]}) {
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


	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9
	
	/if (${Me.AltAbility[25].Name.Find[disabled]} && ${Me.AltAbilityReady[25]}) {
		/alt act 25
		/delay 5
	}
	
	/call mag_load_spellbar

/return 
