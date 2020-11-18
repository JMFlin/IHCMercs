|- ihcberutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub ber_setup
|-Declare AA's and Discs
	/declare endregen				string outer NULL
	/declare Aura1					string outer NULL
	/declare Aura2					string outer NULL
	/declare DichoDisc				string outer NULL
	/declare Dfrenzy				string outer NULL
	/declare Dvolley				string outer NULL
	/declare Daxethrow				string outer NULL
	/declare Daxeof					string outer NULL
	/declare Phantom				string outer NULL
	/declare AllianceDisc			string outer NULL
	/declare PreCombatDisc			string outer NULL
	/declare AESlice				string outer NULL
	/declare AEVicious				string outer NULL
	/declare FrenzyBoost			string outer NULL
	/declare FrenzyBoostBuff		string outer NULL
	/declare RageStrike				string outer NULL
	/declare SharedBuff				string outer NULL
	/declare SharedBuffName			string outer NULL
	/declare BrutalDisc				string outer NULL
	/declare BrutalDiscID			int outer 0
	/declare CleavingDisc			string outer NULL
	/declare CleavingDiscID			int outer 0
	/declare FlurryDisc				string outer NULL
	/declare FlurryDiscID			int outer 0
	/declare DisconDisc				string outer NULL
	/declare DisconDiscID			int outer 0
	/declare ResolveDisc			string outer NULL
	/declare ResolveDiscID			int outer 0
	/declare HHEBuff				string outer NULL
	/declare CryHavoc 				string outer NULL
	/declare Snare 					string outer NULL
	/declare Stun 					string outer NULL
	/declare JoltDisc 				string outer NULL
	/declare BloodDisc 				string outer NULL
	/declare SappingStrike 			string outer NULL
	/declare VolleyAxeName 			string outer NULL
	/declare SnareAxeName 			string outer NULL
	/declare ThrowAxeName 			string outer NULL
	/declare VolleyAxeComponent		string outer NULL
	/declare SnareAxeComponent		string outer NULL
	/declare ThrowAxeComponent		string outer NULL
	/declare JoltAxeComponent		string outer NULL
	/declare JoltAxeName			string outer NULL
	/declare StunAxeName			string outer NULL
	/declare StunAxeComponent		string outer NULL
	/declare DichoAxeComponent	 	string outer NULL
	/declare DichoAxeName 			string outer NULL
	/declare RitualScarification 	string outer NULL
	
	/declare ChestItemName			string outer "${Me.Inventory[17].Name}"
	/declare ZerkerCount			int outer 1
	/declare epicaxe				string outer NULL
	/declare UseEpic				int outer 0
	/declare CastResult             string outer
	/declare PosseSpell				string 	outer 	Origin
|- Check for epic
	/if (${FindItem[Raging Taelosian Alloy Axe].ID}) {
		/varset epicaxe		Raging Taelosian Alloy Axe
		/varset UseEpic 1
	} else /if (${FindItem[Vengeful Taelosian Blood Axe].ID}) {
		/varset epicaxe		Vengeful Taelosian Blood Axe
		/varset UseEpic 1
	}
	/if (${Me.AltAbility[962].Name.Find[disabled]} && ${Me.AltAbilityReady[962]}) {
		/alt act 962
		/delay 5
	}
/return 
|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|----------------------------------------------------------------------------
Sub ber_abilities

|-	Axe Components
|-	Balanced Axe Components
|-	Basic Axe Components
|-	Crafted Axe Components
|-	Masterwork Axe Components

|---One off abilities
	/if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Phantom Assailant].RankName}]}) /varset Phantom ${Spell[Phantom Assailant].RankName}
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Mangler's Alliance].RankName}]}) {
		/varset AllianceDisc ${Spell[Mangler's Covenant].RankName}
		/varset AllianceSpellRankCheck ${Spell[Mangler's Covenant]}
	} else /if (${Me.Level}>=105 && ${Me.CombatAbility[${Spell[Demolisher's Alliance].RankName}]}) {
		/varset AllianceDisc ${Spell[Demolisher's Alliance].RankName}
		/varset AllianceSpellRankCheck ${Spell[Demolisher's Alliance]}
	}
|---Cry Havoc - Crit Buff
	/if (${Me.Level}>=98 && ${Me.CombatAbility[Cry Carnage]}) {
		/varset CryHavoc Cry Carnage
	} else /if (${Me.Level}>=68 && ${Me.CombatAbility[Cry Havoc]}) {
		/varset CryHavoc Cry Havoc
	}
|---Stun
	/if (${Me.Level}>=113 && ${Me.CombatAbility[Temple Crack]}) {
		/varset Stun Temple Crack
		/varset StunAxeName Axe of the Vindicator
		/varset StunAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=108 && ${Me.CombatAbility[Temple Slam]}) {
		/varset Stun Temple Slam
		/varset StunAxeName Axe of the Mangler
		/varset StunAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[Temple Demolish]}) {
		/varset Stun Temple Demolish
		/varset StunAxeName Axe of the Demolisher
		/varset StunAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=98 && ${Me.CombatAbility[Temple Crush]}) {
		/varset Stun Temple Crush
		/varset StunAxeName Axe of the Brute
		/varset StunAxeComponent Crafted Axe Component
	} else /if (${Me.Level}>=93 && ${Me.CombatAbility[Temple Smash]}) {
		/varset Stun Temple Smash
		/varset StunAxeName Axe of the Sunderer
		/varset StunAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=88 && ${Me.CombatAbility[Temple Chop]}) {
		/varset Stun Temple Chop
		/varset StunAxeName Axe of the Savage
		/varset StunAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=83 && ${Me.CombatAbility[Temple Bash]}) {
		/varset Stun Temple Bash
		/varset StunAxeName Axe of the Eradicator
		/varset StunAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=78 && ${Me.CombatAbility[Temple Strike]}) {
		/varset Stun Temple Strike
		/varset StunAxeName Axe of the Decimitor
		/varset StunAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=73 && ${Me.CombatAbility[Temple Blow]}) {
		/varset Stun Temple Blow
		/varset StunAxeName Axe of the Annihilator
		/varset StunAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=68 && ${Me.CombatAbility[Mind Strike]}) {
		/varset Stun Mind Strike
		/varset StunAxeName Axe of the Destroyer
		/varset StunAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=60 && ${Me.CombatAbility[Head Crush]}) {
		/varset Stun Head Crush
		/varset StunAxeName Rage Axe
		/varset StunAxeComponent Basic Axe Component
	} else /if (${Me.Level}>=40 && ${Me.CombatAbility[Head Pummel]}) {
		/varset Stun Head Pummel
		/varset StunAxeName Bonesplicer Axe
		/varset StunAxeComponent Basic Axe Component
	} else /if (${Me.Level}>=16 && ${Me.CombatAbility[Head Strike]}) {
		/varset Stun Head Strike
		/varset StunAxeName Blunt Axe
		/varset StunAxeComponent Basic Axe Component
	}
	
|---Snare
	/if (${Me.Level}>=106 && ${Me.CombatAbility[Tendon Rip]}) {
		/varset Snare Tendon Rip
		/varset SnareAxeName Axe of the Vindicator
		/varset SnareAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=106 && ${Me.CombatAbility[Tendon Rupture]}) {
		/varset Snare Tendon Rupture
		/varset SnareAxeName Axe of the Mangler
		/varset SnareAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=101 && ${Me.CombatAbility[Tendon Tear]}) {
		/varset Snare Tendon Tear
		/varset SnareAxeName Axe of the Demolisher
		/varset SnareAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=96 && ${Me.CombatAbility[Tendon Gash]}) {
		/varset Snare Tendon Gash
		/varset SnareAxeName Axe of the Brute
		/varset SnareAxeComponent Crafted Axe Component
	} else /if (${Me.Level}>=91 && ${Me.CombatAbility[Tendon Slash]}) {
		/varset Snare Tendon Slash
		/varset SnareAxeName Axe of the Sunderer
		/varset SnareAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=86 && ${Me.CombatAbility[Tendon Lacerate]}) {
		/varset Snare Tendon Lacerate
		/varset SnareAxeName Axe of the Savage
		/varset SnareAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=81 && ${Me.CombatAbility[Tendon Shear]}) {
		/varset Snare Tendon Shear
		/varset SnareAxeName Axe of the Eradicator
		/varset SnareAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=76 && ${Me.CombatAbility[Tendor Sever]}) {
		/varset Snare Tendor Sever
		/varset SnareAxeName Axe of the Decimitor
		/varset SnareAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=71 && ${Me.CombatAbility[Tendor Cleave]}) {
		/varset Snare Tendor Cleave
		/varset SnareAxeName Axe of the Annihilator
		/varset SnareAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=67 && ${Me.CombatAbility[Crippling Strike]}) {
		/varset Snare Crippling Strike
		/varset SnareAxeName Axe of the Destroyer
		/varset SnareAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=54 && ${Me.CombatAbility[Leg Slice]}) {
		/varset Snare Leg Slice
		/varset SnareAxeName Rage Axe
		/varset SnareAxeComponent Axe Component
	} else /if (${Me.Level}>=32 && ${Me.CombatAbility[Leg Cut]}) {
		/varset Snare Leg Cut
		/varset SnareAxeName Bonesplicer Axe
		/varset SnareAxeComponent Axe Component
	} else /if (${Me.Level}>=8 && ${Me.CombatAbility[Leg Strike]}) {
		/varset Snare Leg Strike
		/varset SnareAxeName Blunt Axe
		/varset SnareAxeComponent Axe Component
	}

	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Jarring Jolt].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Jolt].RankName}
		/varset JoltAxeName Axe of the Mangler
		/varset JoltAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Jarring Smite].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Smite].RankName}
		/varset JoltAxeName Axe of the Demolisher
		/varset JoltAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Jarring Crush].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Crush].RankName}
		/varset JoltAxeName Axe of the Brute
		/varset JoltAxeComponent Crafted Axe Component
	} else /if (${Me.Level}>=94 && ${Me.CombatAbility[${Spell[Jarring Blow].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Blow].RankName}
		/varset JoltAxeName Axe of the Sunderer
		/varset JoltAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=89 && ${Me.CombatAbility[${Spell[Jarring Slam].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Slam].RankName}
		/varset JoltAxeName Axe of the Savage
		/varset JoltAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=84 && ${Me.CombatAbility[${Spell[Jarring Clash].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Clash].RankName}
	} else /if (${Me.Level}>=79 && ${Me.CombatAbility[${Spell[Jarring Smash].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Smash].RankName}
	} else /if (${Me.Level}>=74 && ${Me.CombatAbility[${Spell[Jarring Strike].RankName}]}) {
		/varset JoltDisc ${Spell[Jarring Strike].RankName}
	} else /if (${Me.Level}>=69 && ${Me.CombatAbility[${Spell[Baffeling Strike].RankName}]}) {
		/varset JoltDisc ${Spell[Baffeling Strike].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Confusing Strike].RankName}]}) {
		/varset JoltDisc ${Spell[Confusing Strike].RankName}
	} else /if (${Me.Level}>=48 && ${Me.CombatAbility[${Spell[Distracting Strike].RankName}]}) {
		/varset JoltDisc ${Spell[Distracting Strike].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Divertive Strike].RankName}]}) {
		/varset JoltDisc ${Spell[Divertive Strike].RankName}
	} else /if (${Me.Level}>=24 && ${Me.CombatAbility[${Spell[Distracting Strike].RankName}]}) {
		/varset JoltDisc ${Spell[Distracting Strike].RankName}
	} 


	/if (${Me.CombatAbility[${BrutalDisc}]}) /varset BrutalDiscID ${Spell[${BrutalDisc}].ID}

|---Cleaving Disc
	/if (${Me.Level}>=86 && ${Me.CombatAbility[${Spell[Cleaving Acrimony Discipline].RankName}]}) {
		/varset CleavingDisc ${Spell[Cleaving Acrimony Discipline].RankName}
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[${Spell[Cleaving Anger Discipline].RankName}]}) {
		/varset CleavingDisc ${Spell[Cleaving Anger Discipline].RankName}
	}
	/if (${Me.CombatAbility[${CleavingDisc}]}) /varset CleavingDiscID ${Spell[${CleavingDisc}].ID}
|---Flurry Disc
	/if (${Me.Level}>=89 && ${Me.CombatAbility[${Spell[Avenging Flurry Discipline].RankName}]}) {
		/varset FlurryDisc ${Spell[Avenging Flurry Discipline].RankName}
	} else /if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Vengeful Flurry Discipline].RankName}]}) {
		/varset FlurryDisc ${Spell[Vengeful Flurry Discipline].RankName}
	}
	/if (${Me.CombatAbility[${FlurryDisc}]}) /varset FlurryDiscID ${Spell[${FlurryDisc}].ID}
|---Disconcerting
	/if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Disconcerting Discipline].RankName}]}) {
		/varset DisconDisc ${Spell[Disconcerting Discipline].RankName}
		/varset DisconDiscID ${Spell[DisconDisc].ID}
	}
|---Resolve Disc
	/if (${Me.Level}>=94 && ${Me.CombatAbility[${Spell[Frenzied Resolve Discipline].RankName}]}) {
		/varset ResolveDisc ${Spell[Frenzied Resolve Discipline].RankName}
		/varset ResolveDiscID ${Spell[ResolveDisc].ID}
	}
	
	/if (${Me.Level}>=${Spell[Ritual Scarification].Level} && ${Me.CombatAbility[${Spell[Ritual Scarification].RankName}]}) {
		/varset RitualScarification ${Spell[Ritual Scarification].RankName}
	}
	

|---Frenzy Boost - Updated for RoS and Expanded for lower level
|- STORMWILD FRENZY?
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Torrid Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Torrid Frenzy].RankName}
		/varset FrenzyBoostBuff Torrid Frenzy
	} else /if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Bolstered Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Bolstered Frenzy].RankName}
		/varset FrenzyBoostBuff Bolstered Frenzy Effect
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Amplified Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Amplified Frenzy].RankName}
		/varset FrenzyBoostBuff Amplified Frenzy Effect
	} else /if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Augmented Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Augmented Frenzy].RankName}
		/varset FrenzyBoostBuff Augmented Frenzy Effect
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Steel Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Steel Frenzy].RankName}
		/varset FrenzyBoostBuff Steel Frenzy Effect
	} else /if (${Me.Level}>=90 && ${Me.CombatAbility[${Spell[Fighting Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Fighting Frenzy].RankName}
		/varset FrenzyBoostBuff Fighting Frenzy Effect
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Combat Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Combat Frenzy].RankName}
		/varset FrenzyBoostBuff Combat Frenzy Effect
	} else /if (${Me.Level}>=80 && ${Me.CombatAbility[${Spell[Battle Frenzy].RankName}]}) {
		/varset FrenzyBoost ${Spell[Battle Frenzy].RankName}
		/varset FrenzyBoostBuff Battle Frenzy Effect
	}
|---SharedBuff - Updated for RoS and Expanded for lower level
	/if (${Me.Level}>=110 && ${Me.CombatAbility[${Spell[Shared Ruthlessness].RankName}]}) {
		/varset SharedBuff ${Spell[Shared Ruthlessness].RankName}
		/varset SharedBuffName Shared Ruthlessness
	} else /if (${Me.Level}>=105 && ${Me.CombatAbility[${Spell[Shared Cruelty].RankName}]}) {
		/varset SharedBuff ${Spell[Shared Cruelty].RankName}
		/varset SharedBuffName Shared Cruelty
	} else /if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Shared Viciousness].RankName}]}) {
		/varset SharedBuff ${Spell[Shared Viciousness].RankName}
		/varset SharedBuffName Shared Viciousness
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Shared Savagery].RankName}]}) {
		/varset SharedBuff ${Spell[Shared Savagery].RankName}
		/varset SharedBuffName Shared Savagery
	} else /if (${Me.Level}>=90 && ${Me.CombatAbility[${Spell[Shared Brutality].RankName}]}) {
		/varset SharedBuff ${Spell[Shared Brutality].RankName}
		/varset SharedBuffName Shared Brutality
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Shared Bloodlust].RankName}]}) {
		/varset SharedBuff ${Spell[Shared Bloodlust].RankName}
		/varset SharedBuffName Shared Bloodlust
	}
|---RageStrike - Updated for RoS and Expanded for lower level
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Smoldering Rage].RankName}]}) {
		/varset RageStrike ${Spell[Smoldering Rage].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Bubbling Rage].RankName}]}) {
		/varset RageStrike ${Spell[Bubbling Rage].RankName}
	} else /if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Festering Rage].RankName}]}) {
		/varset RageStrike ${Spell[Festering Rage].RankName}
	}
|---PreCombatDisc ability EX: Kick in the shins - Updated for RoS
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Sucker Punch].RankName}]}) {
		/varset PreCombatDisc ${Spell[Sucker Punch].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Kick in the Shins].RankName}]}) {
		/varset PreCombatDisc ${Spell[Kick in the Shins].RankName}
	} else /if (${Me.Level}>=97 && ${Me.CombatAbility[${Spell[Punch in the Throat].RankName}]}) {
		/varset PreCombatDisc ${Spell[Punch in the Throat].RankName}
	} else /if (${Me.Level}>=92 && ${Me.CombatAbility[${Spell[Kick in the Teeth].RankName}]}) {
		/varset PreCombatDisc ${Spell[Kick in the Teeth].RankName}
	} else /if (${Me.Level}>=87 && ${Me.CombatAbility[${Spell[Slap in the Face].RankName}]}) {
		/varset PreCombatDisc ${Spell[Slap in the Face].RankName}
	} else /if (${Me.Level}>=5 && ${Me.CombatAbility[${Spell[Elbow Strike].RankName}]}) {
		/varset PreCombatDisc ${Spell[Elbow Strike].RankName}
	} else /if (${Me.Level}>=1 && ${Me.CombatAbility[${Spell[Throw Stone].RankName}]}) {
		/varset PreCombatDisc ${Spell[Throw Stone].RankName}
	}
|-Dicho Spell*
	/if (${Me.Level}>=${Spell[Dissident Rage].Level} && ${Me.CombatAbility[${Spell[Dissident Rage].RankName}]}) {
		/varset DichoDisc ${Spell[Dissident Rage].RankName}
		/varset DichoAxeName NULL
		/varset DichoAxeComponent NULL
	} else /if (${Me.Level}>=${Spell[Dichotomic Rage].Level} && ${Me.CombatAbility[${Spell[Dichotomic Rage].RankName}]}) {
		/varset DichoDisc ${Spell[Dichotomic Rage].RankName}
		/varset DichoAxeName Axe of the Demolisher
		/varset DichoAxeComponent Masterwork Axe Components
	}
	
|---Frenzy Combat Ability not normal Frenzy - Updated for RoS
	/if (${Me.Level}>=111 && ${Me.CombatAbility[${Spell[Vindicating Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Vindicating Frenzy].RankName}
	} else /if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Mangling Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Mangling Frenzy].RankName}
	} else /if (${Me.Level}>=101 && ${Me.CombatAbility[${Spell[Demolishing Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Demolishing Frenzy].RankName}
	} else /if (${Me.Level}>=96 && ${Me.CombatAbility[${Spell[Vanquishing Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Vanquishing Frenzy].RankName}
	} else /if (${Me.Level}>=91 && ${Me.CombatAbility[${Spell[Conquering Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Conquering Frenzy].RankName}
	} else /if (${Me.Level}>=86 && ${Me.CombatAbility[${Spell[Overwhelming Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Overwhelming Frenzy].RankName}
	} else /if (${Me.Level}>=81 && ${Me.CombatAbility[${Spell[Overpowering Frenzy].RankName}]}) {
		/varset Dfrenzy ${Spell[Overpowering Frenzy].RankName}
	}

	|- Blood Axe TIMER 1
|- NEED BUFF EFFECT NAME ON MOB TO CHECK IN COMBATDPS
	/if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Blood Brand].RankName}]}) {
		/varset BloodDisc ${Spell[Blood Brand].RankName}
	} else /if (${Me.Level}>=93 && ${Me.CombatAbility[${Spell[Blood Blade].RankName}]}) {
		/varset BloodDisc ${Spell[Blood Blade].RankName}
	} else /if (${Me.Level}>=88 && ${Me.CombatAbility[${Spell[Blood Axe].RankName}]}) {
		/varset BloodDisc ${Spell[Blood Axe].RankName}
	} else /if (${Me.Level}>=83 && ${Me.CombatAbility[${Spell[Blood Hatchet].RankName}]}) {
		/varset BloodDisc ${Spell[Blood Hatchet].RankName}
	} 

|---Battle Cry - HHE Buff
	/if (${Me.Level}>=65 && ${Me.CombatAbility[Ancient: Cry of Chaos]}) {
		/varset HHEBuff Ancient: Cry of Chaos
	} else /if (${Me.Level}>=65 && ${Me.CombatAbility[Battle Cry of the Mastruq]}) {
		/varset HHEBuff Battle Cry of the Mastruq
	} else /if (${Me.Level}>=64 && ${Me.CombatAbility[War Cry of Dravel]}) {
		/varset HHEBuff War Cry of Dravel
	} else /if (${Me.Level}>=57 && ${Me.CombatAbility[Battle Cry of Dravel]}) {
		/varset HHEBuff Battle Cry of Dravel
	} else /if (${Me.Level}>=50 && ${Me.CombatAbility[War Cry]}) {
		/varset HHEBuff War Cry
	} else /if (${Me.Level}>=30 && ${Me.CombatAbility[Battle Cry]}) {
		/varset HHEBuff Battle Cry
	}
|---Primary Burn Disc Setup - Expanded for lower level use
|- TIMER 4
	/if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Brutal Discipline].RankName}]}) {
		/varset BrutalDisc ${Spell[Brutal Discipline].RankName}
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Sundering Discipline].RankName}]}) {
		/varset BrutalDisc ${Spell[Sundering Discipline].RankName}
	} else /if (${Me.Level}>=75 && ${Me.CombatAbility[${Spell[Berserking Discipline].RankName}]}) {
		/varset BrutalDisc ${Spell[Berserking Discipline].RankName}
	} else /if (${Me.Level}>=60 && ${Me.CombatAbility[${Spell[Burning Rage Discipline].RankName}]}) {
		/varset BrutalDisc ${Spell[Burning Rage Discipline].RankName}
	} else /if (${Me.Level}>=58 && ${Me.CombatAbility[${Spell[Blind Rage Discipline].RankName}]}) {
		/varset BrutalDisc ${Spell[Blind Rage Discipline].RankName}
	} else /if (${Me.Level}>=54 && ${Me.CombatAbility[${Spell[Cleaving Rage Discipline].RankName}]}) {
		/varset BrutalDisc ${Spell[Cleaving Rage Discipline].RankName}
	} 
|---Volley - Updated for RoS
	/if (${Me.Level}>=114 && ${Me.CombatAbility[${Spell[Vindicating Volley].RankName}]}) {
		/varset Dvolley ${Spell[Vindicating Volley].RankName}
		|/varset VolleyAxeName Axe of the Vindicator
	} else /if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Mangling Volley].RankName}]}) {
		/varset Dvolley ${Spell[Mangling Volley].RankName}
		|/varset VolleyAxeName Axe of the Mangler
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Demolishing Volley].RankName}]}) {
		/varset Dvolley ${Spell[Demolishing Volley].RankName}
		|/varset VolleyAxeName Axe of the Demolisher
	} else /if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Brutal Volley].RankName}]}) {
		/varset Dvolley ${Spell[Brutal Volley].RankName}
		|/varset VolleyAxeName Axe of the Brute
	} else /if (${Me.Level}>=94 && ${Me.CombatAbility[${Spell[Sundering Volley].RankName}]}) {
		/varset Dvolley ${Spell[Sundering Volley].RankName}
		|/varset VolleyAxeName Axe of the Sunderer
	} else /if (${Me.Level}>=89 && ${Me.CombatAbility[${Spell[Savage Volley].RankName}]}) {
		/varset Dvolley ${Spell[Savage Volley].RankName}
		|/varset VolleyAxeName Axe of the Savage
	} else /if (${Me.Level}>=84 && ${Me.CombatAbility[${Spell[Eradicator's Volley].RankName}]}) {
		/varset Dvolley ${Spell[Eradicator's Volley].RankName}
		|/varset VolleyAxeName Axe of the Eradicator
	} else /if (${Me.Level}>=79 && ${Me.CombatAbility[${Spell[Decimator's Volley].RankName}]}) {
		/varset Dvolley ${Spell[Decimator's Volley].RankName}
		|/varset VolleyAxeName Axe of the Decimator
		|/varset VolleyAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=74 && ${Me.CombatAbility[${Spell[Annihilator's Volley].RankName}]}) {
		/varset Dvolley ${Spell[Annihilator's Volley].RankName}
		|/varset VolleyAxeName Axe of the Annihilator
		|/varset VolleyAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=69 && ${Me.CombatAbility[${Spell[Destroyer's Volley].RankName}]}) {
		/varset Dvolley ${Spell[Destroyer's Volley].RankName}
		|/varset VolleyAxeName Axe of the Destroyer
		|/varset VolleyAxeComponent Balanced Axe Components
	} else /if (${Me.Level}>=61 && ${Me.CombatAbility[${Spell[Rage Volley].RankName}]}) {
		/varset Dvolley ${Spell[Rage Volley].RankName}
		|/varset VolleyAxeName Rage Axe
		|/varset VolleyAxeComponent Axe Components
	}
|---Axe Throw - Updated for RoS
	/if (${Me.Level}>=108 && ${Me.CombatAbility[${Spell[Mangling Axe Throw].RankName}]}) {
		/varset Daxethrow ${Spell[Mangling Axe Throw].RankName}
		|/varset ThrowAxeName Axe of the Mangler
		|/varset ThrowAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Demolishing Axe Throw].RankName}]}) {
		/varset Daxethrow ${Spell[Demolishing Axe Throw].RankName}
		|/varset ThrowAxeName Axe of the Demolisher
		|/varset ThrowAxeComponent Masterwork Axe Components
	} else /if (${Me.Level}>=98 && ${Me.CombatAbility[${Spell[Brutal Axe Throw].RankName}]}) {
		/varset Daxethrow ${Spell[Brutal Axe Throw].RankName}
		|/varset ThrowAxeName Axe of the Brute
		|/varset ThrowAxeComponent NULL
	} else /if (${Me.Level}>=93 && ${Me.CombatAbility[${Spell[Spirited Axe Throw].RankName}]}) {
		/varset Daxethrow ${Spell[Spirited Axe Throw].RankName}
		|/varset ThrowAxeName Axe of the Sunderer
		|/varset ThrowAxeComponent NULL
	} else /if (${Me.Level}>=88 && ${Me.CombatAbility[${Spell[Energetic Axe Throw].RankName}]}) {
		/varset Daxethrow ${Spell[Energetic Axe Throw].RankName}
		|/varset ThrowAxeName Axe of the Savage
		|/varset ThrowAxeComponent NULL
	} else /if (${Me.Level}>=83 && ${Me.CombatAbility[${Spell[Vigorous Axe Throw].RankName}]}) {
		/varset Daxethrow ${Spell[Vigorous Axe Throw].RankName}
		|/varset ThrowAxeName Axe of the Eradicator
		|/varset ThrowAxeComponent Balanced Axe Components
	}
|- Sapping strike
	/if (${Me.Level}>=103 && ${Me.CombatAbility[${Spell[Sapping Strikes].RankName}]}) {
		/varset SappingStrike ${Spell[Sapping Strikes].RankName}
	}
|---Axe of - No Update
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Axe of Empyr].RankName}]}) {
		/varset Daxeof ${Spell[Axe of Empyr].RankName}
	} else /if (${Me.Level}>=106 && ${Me.CombatAbility[${Spell[Axe of the Mangler].RankName}]}) {
		/varset Daxeof ${Spell[Axe of Numicia].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Axe of the Aeons].RankName}]}) {
		/varset Daxeof ${Spell[Axe of the Aeons].RankName}
	} else /if (${Me.Level}>=100 && ${Me.CombatAbility[${Spell[Axe of Zurel].RankName}]}) {
		/varset Daxeof ${Spell[Axe of Zurel].RankName}
	} else /if (${Me.Level}>=95 && ${Me.CombatAbility[${Spell[Axe of Illdaera].RankName}]}) {
		/varset Daxeof ${Spell[Axe of Illdaera].RankName}
	} else /if (${Me.Level}>=90 && ${Me.CombatAbility[${Spell[Axe of Graster].RankName}]}) {
		/varset Daxeof ${Spell[Axe of Graster].RankName}
	} else /if (${Me.Level}>=85 && ${Me.CombatAbility[${Spell[Axe of Rallos].RankName}]}) {
		/varset Daxeof ${Spell[Axe of Rallos].RankName}
	}
|---AE Slice Attack - 4 targets or less DIRECTIONAL Range 40
	/if (${Me.Level}>=109 && ${Me.CombatAbility[${Spell[Arcsteel].RankName}]}) {
		/varset AESlice ${Spell[Arcsteel].RankName}
	} else /if (${Me.Level}>=104 && ${Me.CombatAbility[${Spell[Arcslice].RankName}]}) {
		/varset AESlice ${Spell[Arcslice].RankName}
	} else /if (${Me.Level}>=99 && ${Me.CombatAbility[${Spell[Arcblade].RankName}]}) {
		/varset AESlice ${Spell[Arcblade].RankName}
	}
|---AE Viscious Attack - Up to 12 targets Range 25
	/if (${Me.Level}>=107 && ${Me.CombatAbility[${Spell[Vicious Cycle].RankName}]}) {
		/varset AEVicious ${Spell[Vicious Cycle].RankName}
	} else /if (${Me.Level}>=102 && ${Me.CombatAbility[${Spell[Vicious Cyclone].RankName}]}) {
		/varset AEVicious ${Spell[Vicious Cyclone].RankName}
	} else /if (${Me.Level}>=97 && ${Me.CombatAbility[${Spell[Vicious Spiral].RankName}]}) {
		/varset AEVicious ${Spell[Vicious Spiral].RankName}
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
	/if (${Me.Level}>=70 && ${Me.CombatAbility[${Spell[Bloodlust Aura].RankName}]}) {
		/varset Aura1 ${Spell[Bloodlust Aura].RankName}
	} else /if (${Me.Level}>=55 && ${Me.CombatAbility[${Spell[Aura of Rage].RankName}]}) {
		/varset Aura1 ${Spell[Aura of Rage].RankName}
	}
	
/return
|----------------------------------------------------------------------------
|-SUB: Bind Change Var Int resets various interger settings from ini file
|----------------------------------------------------------------------------
Sub Bind_SetVarInt(string ISection, string IName, int IVar)
    /docommand /varset changetoini 1
 |-Toggles
	/if (${ISection.Equal[Toggle]}) {
  |--Pet
		/if (${IName.Equal[UsePet]}) {
			/if (!${UsePet}) {
				/echo \aw Setting UsePet to \ag ON
				/varset UsePet 1
			} else {
				/echo \aw Resetting UsePet to \ar OFF
				/varset UsePet 0
			}
  |--Alliance
		} else /if (${IName.Equal[useAlliance]}) {
			/if (!${useAlliance}) {
				/echo \aw Setting useAlliance to \ag ON
				/varset useAlliance 1
				/call AllianceCheck
			} else {
				/echo \aw Resetting useAlliance to \ar OFF
				/varset useAlliance 0
			}
  |--Opener
		} else /if (${IName.Equal[UseOpener]}) {
			/if (!${UseOpener}) {
				/echo \aw Setting UseOpener to \ag ON
				/varset UseOpener 1
			} else {
				/echo \aw Resetting UseOpener to \ar OFF
				/varset UseOpener 0
			}
  |--LootOn
		} else /if (${IName.Equal[LootOn]}) {
			/if (!${LootOn}) {
				/echo \aw Setting LootOn to \ag ON
				/varset LootOn 1
			} else {
				/echo \aw Resetting LootOn to \ar OFF
				/varset LootOn 0
			}
  |--Intimidate
		} else /if (${IName.Equal[UseIntimidate]}) {
			/if (!${UseIntimidate}) {
				/echo \aw Setting UseIntimidate to \ag ON
				/varset UseIntimidate 1
			} else {
				/echo \aw Resetting UseIntimidate to \ar OFF
				/varset UseIntimidate 0
			}
  |--Allow MezBreak
		} else /if (${IName.Equal[AllowMezBreak]}) {
			/if (!${AllowMezBreak}) {
				/echo \aw Setting AllowMezBreak to \ag ON
				/varset AllowMezBreak 1
			} else {
				/echo \aw Resetting AllowMezBreak to \ar OFF
				/varset AllowMezBreak 0
			}
  |--Force Alliance
		} else /if (${IName.Equal[ForceAlliance]}) {
			/if (!${ForceAlliance}) {
				/echo \aw Setting ForceAlliance to \ag ON
				/varset ForceAlliance 1
			} else {
				/echo \aw Resetting ForceAlliance to \ar OFF
				/varset ForceAlliance 0
			}
  |--UseAoE
		} else /if (${IName.Equal[UseAoE]}) {
			/if (!${UseAoE}) {
				/echo \aw Setting UseAoE to \ag ON
				/varset UseAoE 1
			} else {
				/echo \aw Resetting UseAoE to \ar OFF
				/varset UseAoE 0
			}
  |--AutoAxe
		} else /if (${IName.Equal[AutoAxe]}) {
			/if (!${AutoAxe}) {
				/echo \aw Setting AutoAxe to \ag ON
				/varset AutoAxe 1
			} else {
				/echo \aw Resetting AutoAxe to \ar OFF
				/varset AutoAxe 0
			}
  |--Chest Combat Cast
		} else /if (${IName.Equal[ChestCombatCast]}) {
			/if (!${ChestCombatCast}) {
				/echo \aw Setting ChestCombatCast to \ag ON
				/varset ChestCombatCast 1
			} else {
				/echo \aw Resetting ChestCombatCast to \ar OFF
				/varset ChestCombatCast 0
			}
  |--Use Poisons
		} else /if (${IName.Equal[UsePoisons]}) {
			/if (!${UsePoisons}) {
				/echo \aw Setting UsePoisons to \ag ON
				/varset UsePoisons 1
			} else {
				/echo \aw Resetting UsePoisons to \ar OFF
				/varset UsePoisons 0
			}
		}
	}
/return
