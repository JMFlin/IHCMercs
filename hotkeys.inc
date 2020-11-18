Sub ClearSocials(int startPage, int endPage)
    | Clear all social pages
    /declare totalSocialPgs int local ${endPage}
    /declare socialsPerPage int local 12
    /declare i int local ${startPage}
    /declare j int local 0

    /for i ${startPage} to 10
        /notify ActionsWindow ASP_SocialPageLeftButton leftmouseup
        /if (${Int[${Window[ActionsWindow].Child[ActionsSocialsPage].Child[ASP_CurrentSocialPageLabel].Text}]} == 1) /break
        /delay 2
    /next i
    
    /for i ${startPage} to ${totalSocialPgs}
        /for j 1 to ${socialsPerPage}
            /notify ActionsWindow ASP_SocialButton${j} rightmouseup
            /notify SocialEditWnd SEW_Clear_Button leftmouseup
            /notify SocialEditWnd SEW_Accept_Button leftmouseup
        /next j
        /notify ActionsWindow ASP_SocialPageRightButton leftmouseup
        /delay 2
    /next i

    /for i ${startPage} to 10
        /notify ActionsWindow ASP_SocialPageLeftButton leftmouseup
        /if (${Int[${Window[ActionsWindow].Child[ActionsSocialsPage].Child[ASP_CurrentSocialPageLabel].Text}]} == 1) /break
        /delay 2
    /next i

    /call setup_groups
    /for i 1 to 4
        /call Page${i}
        /delay 2
    /next i

/return

Sub Page1
    |** 
        Self
        TODO:
            Invis
            Clear invis
            /say yes accept ready go etcs
    **|

    /hotbutton StartSelf 14 1:0:/addicted
    /hotbutton EndSelf 14 1:0:/endmacro

    /hotbutton RestartSelf 14 1:0:/endmacro
    /hotbutton RestartSelf 14 2:0:/pause 5
    /hotbutton RestartSelf 14 3:0:/addicted

    /hotbutton TravelSelf 14 1:0:/addict travel
    /hotbutton AfkPullSelf 14 1:0:/addict afkfight 500 20 10
    /hotbutton EventSelf 14 1:0:/addict event

    /hotbutton ScribeSelf 14 1:0:/scribelevels ${minScribeLevel} ${maxScribeLevel}
    /hotbutton RestartSelf 14 2:0:/pause 10
    /hotbutton ScribeSelf 14 2:0:/scribezone All
    /hotbutton RestartSelf 14 2:0:/pause 10
    /hotbutton ScribeSelf 14 3:0:/addict scribe

    /hotbutton NavToMeSelf 14 1:0:/dga /navto me
    /hotbutton NavToTarget 14 1:0:/dgga /navto target
    /hotbutton TravelGLSelf 14 1:0:/traveltozone "guild lobby"
    /hotbutton TravelGHSelf 14 1:0:/traveltozone "guild hall"
    /hotbutton TravelPoKSelf 14 1:0:/traveltozone "plane of knowledge"

    /hotbutton DragAll 14 1:0:/dragall
    /hotbutton DragAll 14 2:0:/varset DragAllVar TRUE
    /hotbutton DragStop 14 1:0:/varset DragAllVar FALSE

    


/return

Sub Page2
    |** 
        Group
        TODO
            invis
            clear invis
            /say yes accept ready go etc
    **|
    /hotbutton StartGroup 5 1:0:/dgga /addicted
    /hotbutton EndGroup 5 1:0:/dgga /endmacro

    /hotbutton RestartGroup 5 1:0:/dgga /endmacro
    /hotbutton RestartGroup 5 2:0:/pause 10
    /hotbutton RestartGroup 5 3:0:/dgga /addicted

    /hotbutton TravelGroup 5 1:0:/dgga /addict travel
    /hotbutton AfkPullGroup 5 1:0:/dgga /addict afkfight 300 40 65
    /hotbutton eventGroup 5 1:0:/dgga /addict event
    /hotbutton RaidGroup 5 1:0:/dgga /addict raid

    /hotbutton ScribeGroup 5 1:0:/dgga /scribezone All
    /hotbutton ScribeGroup 5 2:0:/pause 10
    /hotbutton ScribeGroup 5 3:0:/dgga /scribelevels ${minScribeLevel} ${maxScribeLevel}
    /hotbutton ScribeGroup 5 4:0:/pause 10
    /hotbutton ScribeGroup 5 5:0:/dgga /addict scribe

    /hotbutton FoScribeGroup 5 1:0:/dgga /forcescribe
    
    /hotbutton NavStopGroup 5 1:0:/dgga /nav stop

    /hotbutton PowerLevelGroup 5 1:0:/dgga /powerlevel

    /hotbutton ClickDoorGroup 5 1:0:/dgga /doortarget
    /hotbutton ClickDoorGroup 5 2:0:/pause 5
    /hotbutton ClickDoorGroup 5 3:0:/dgga /click left door

    /hotbutton NudgeFwd 5 1:0:/dgga /keypress forward hold
    /hotbutton NudgeFwd 5 2:0:/dgga /delay 10
    /hotbutton NudgeFwd 5 3:0:/dgga /keypress forward
    
    | NEAREST SPAWN NPC BIND HERE
    /hotbutton VendorGroup 5 1:0:/dgga /assist ${Me.ID}
    /hotbutton VendorGroup 5 2:0:/dgga /attack off
    /hotbutton VendorGroup 5 2:0:/dgga /click right target
    /hotbutton VendorGroup 5 3:0:/dgga /autoloot sell

    /hotbutton TravelGLGroup 5 1:0:/dgga /traveltozone "guild lobby"
    /hotbutton TravelGHGroup 5 1:0:/dgga /traveltozone "guild hall"
    /hotbutton TravelPoKGroup 5 1:0:/dgga /traveltozone "plane of knowledge"

    /hotbutton LobbyRezGroup 5 1:0:/dgga /lazylobbyrez
    /hotbutton SellMerchGroup 5 1:0:/dgga /selltomerchant

/return

Sub Page3
     |** 
        Raid
    **|

/return

Sub Page4
    |** 
        Autoloot
    **|

    | 1 
    /hotbutton AutoIKeep 1 1:0:/SetItem Keep
    
    | 2
    /hotbutton AutoIIgnore 1 1:0:/SetItem Ignore

    | 3
    /hotbutton AutoIBarter 1 1:0:/SetItem Barter ${If[${Math.Calc[${Cursor.Value}/1000].Int} < 1,1,${Math.Calc[(${Cursor.Value}/1000)+1].Int}]}

    | 4
    /hotbutton AutoISell 1 1:0:/SetItem Sell

    | 5
    /hotbutton AutoIDeposit 1 1:0:/SetItem Deposit

    | 6
    /hotbutton AutoIDestroy 1 1:0:/SetItem Destroy

    | 7
    /hotbutton !DeleteItem! 1 1:0:/destroy

    | 8
    /hotbutton AutoIQuest 1 1:0:/SetItem Quest 1

    | 9
    /hotbutton AutoIGear 1 1:0:/SetItem Gear 
    
/return

Sub Page5   
    | ### Page 5 ###

/return

Sub Page6
    /echo PAGE6 NOT YET USED
/return

Sub Page7
    /echo PAGE7 NOT YET USED
/return

Sub Page8
    /echo PAGE8 NOT YET USED
/return

Sub Page9
    /echo PAGE9 NOT YET USED
/return

Sub Page10
    /echo PAGE10 NOT YET USED
/return
