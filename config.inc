Sub setup_plugins
	/declare _count int local 0
	/echo -----${MacroName} LOADING------
	|/if (${Me.XTarget[1].TargetType.NotEqual[Auto Hater]}) {
	|	/echo Extended Target 1 HAS TO BE SET TO Auto Hater
	|	/xtarget set 1 Autohater
	|	/echo Set Extended Target 1 to Auto
	|  }
	|-Check for loaded plugins
	/call CheckPlugin MQ2Rez
	/call CheckPlugin MQ2AdvPath
	/call CheckPlugin MQ2MoveUtils
	/call CheckPlugin MQ2DanNet
	/call CheckPlugin MQ2Nav
	/call CheckPlugin MQ2Autoloot
	/call CheckPlugin MQ2AAspend
	/call CheckPlugin MQ2AutoAccept
	/call CheckPlugin MQ2Hud
	/call CheckPlugin MQ2EasyFind
	/call CheckPlugin MQ2SpawnSort
	|/call CheckPlugin MQ2Worsthurt
	/call CheckPlugin MQ2Yes
	/call CheckPlugin MQ2sqlite
	/call CheckPlugin MQ2Collections
	/call CheckPlugin MQ2Chatwnd
	/call CheckPlugin MQ2AutoClaim
	|/call CheckPlugin MQ2IniX
	/call CheckPlugin MQ2Posse
	/call UnCheckPlugin MQ2Twist
	/call UnCheckPlugin MQ2Cast
	/call UnCheckPlugin MQ2Exchange
	/call UnCheckPlugin MQ2AutoGroup
	|/call UnCheckPlugin MQ2DamageParser
	|/call UnCheckPlugin MQ2Relocate
	/squelch /rez accept on
    /squelch /rez loot off
	/squelch /rez pct 20
	/posse on
	/aaspend order 3521
	/aaspend brute on
	/aaspend bonus on
	/docommand /roleplay off
	/docommand /anon on
	|/mqchat reset
	|- Set the order of the tabs to be spent when brute force is on. 1=general,2=archetype,3=class,4=special,5=focus
	|- /aaspend order 32541 - Brute force mode would buy all AAs in this order Class, Archetype, Focus, Special, General
	|-Disable mq2melee if its running
	/if (${Plugin[MQ2Melee].Name.Length}) {
		/if (${Melee.Enable}) {
			/melee off
		}
	}
	|- Load DanNet to communicate with other box chars in the same group. 
	/if (${Plugin[MQ2DanNet].Name.Length}) {
		/if (${DanNet.CommandEcho}) /squelch /dnet commandecho off
	}
	/autoaccept trade on
	/autoaccept group on
	/autoaccept raid on
	/autoaccept translocate on
|	/autoaccept anchor on
	/autoaccept add Panasonic
	/autoaccept add Exide
	/autoaccept add Aceleron
	/autoaccept add Makkara
	/autoaccept add Aerocell
	/autoaccept add Polaroid
	/autoaccept add Rayovac
	/autoaccept add Yuasa
	/autoaccept add Duplex
	/autoaccept add Aannaydar
	/autoaccept add Teudayael
	/autoaccept add Kaeluuen
	/autoaccept add Fiamm
	/autoaccept add Tramral
	/autoaccept add Tragzab
	/autoaccept add Raukan
	/autoaccept add Ainlawen
	/autoaccept add Optima
	/autoaccept add Sinnayven
	/autoaccept add Breunayen
	/autoaccept add Silaelin
	/autoaccept add Keuaelan
	/autoaccept add Sinuuil
	/autoaccept add Saladyan
	/autoaccept add Keudayyan
	/autoaccept add Keunayin
	/autoaccept add Taeldayr
	/autoaccept add Neunayin
	/autoaccept add Uilaelr
	/autoaccept add Utenaelr
	/autoaccept add Zailus
	/autoaccept add Golien
	/autoaccept add Aanaelen
	/autoaccept add Xailus
	/autoaccept add Aaldiven
	/autoaccept add Brald
	/autoaccept save

	/loadhud Player
	/loadhud Posse
	/loadhud Target
	/loadhud Nearest
	/loadhud XTarget
	/loadhud General

/return