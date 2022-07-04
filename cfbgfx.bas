' FBGFX Wrapper
'
extern "C"

Function cScreenRes(dx As long, dy As long, depth As long, pages As long, flags As long) As long Export
    Return ScreenRes(dx,dy,depth,pages,flags,0)
End Function

Function cWindowTitle(text as zstring ptr) As long Export
    WindowTitle *text
    Return 0
End Function

Function cImageCreate(dx As long, dy As long, colors As ulong,depth As long) As ulong Ptr Export
    Return ImageCreate(dx,dy,colors)
End Function
Function cImageDestroy(img As ulong ptr) As long Export
    ImageDestroy(img)
    Return 0
End Function

Function cPset(target As ulong Ptr,x As long, y As long, colors As ulong) As long Export
    PSet target,(x,y),colors
    Return 1
End Function

Function cPoint(target As ulong Ptr,x As long, y As long) As ulong Export
    Return Point(x,y,target)
End Function

Function cSleep(num As long) As long Export
    If num=0 Then Sleep Else Sleep num
    Return 1
End Function

Function cRGB(r As long, g As long, b As long) As ulong Export
    Return RGB(r,g,b)
End Function

Function cRGBA(r As long, g As long, b As long, a As long) As ulong Export
    Return RGBA(r,g,b,a)
End Function

Function cMultikey(key As long) As long Export

    Return MultiKey(key)
End Function

Function cCircle(target As ulong Ptr,x As long,y As long,size As long,colors As ulong,fill As long) As long Export
    If fill=0 Then Circle target,(x,y),size,colors
    If fill=1 Then Circle target,(x,y),size,colors,,,,f
    Return 0
End Function

Function cLine(target As ulong Ptr,x As long,y As long,x2 As long,y2 As long,colors As ulong,box as long, style As long) As long Export  
    select case box
    case 0
        Line target,(x, y)-(x2, y2),colors,,style
    case 1
        Line target,(x, y)-(x2, y2),colors,b,style
    case 2
        Line target,(x, y)-(x2, y2),colors,bf,style
    end select
    Return 0
End Function
Function cBox(target As ulong Ptr,x As long,y As long,x2 As long,y2 As long,colors As ulong,fill As long,style As long) As long Export
    If fill=0 Then Line target,(x, y)-(x2, y2),colors,b,style
    If fill=1 Then Line target,(x, y)-(x2, y2),colors,bf,style
    Return 0
End Function

Function cPaint(target As ulong Ptr,x As long,y As long,colors As ulong,border As ulong) As long Export
    Paint target,(x, y),colors,border
    Return 0
End Function

Function cScreenlock As long Export
    ScreenLock
    Return 1
End Function

Function cScreenunlock As long Export
    ScreenUnLock
    Return 1
End Function

Function cBload(file As zString ptr,target As ulong Ptr) As long Export
    BLoad *file,target
    Return 0
End Function

Function cPrint(text As zString ptr,mode As long) As long Export
    If mode=0 Then print *text
    If mode=1 Then print *text;
    Return 0
End Function

Function cPrintInt(value As long,mode As long) As long Export
    If mode=0 Then print value
    If mode=1 Then print value;
    Return 0
End Function

Function cLocate(row As long,column As long) As long Export
    locate row,column
    Return 0
End Function

Function cColor(fore As ulong,back As ulong) As long Export
    Color fore,back
    Return 0
End Function

Function cCls As long Export
    Cls
    Return 1
End Function

Function cSetmouse(x as long=-1,y as long=-1,v as long=-1,c as long=-1) As long Export
    if x=-1 then
        setmouse ,,v,c
    else
        SetMouse x,y,v,c
    end if
    return 1
End Function

Function cGetmouse(byref mx as long,byref my as long,byref mw as long,byref mb as long) As long Export
    GetMouse mx,my,mw,mb
    return 1
End Function

Function cTimer As double Export
    Return timer
End Function
#define getR( c ) ( CUInt( c ) Shr 16 And 255 )
#define getG( c ) ( CUInt( c ) Shr  8 And 255 )
#define getB( c ) ( CUInt( c )        And 255 )
#define getA( c ) ( CUInt( c ) Shr 24         )

Function darken ( ByVal source_pixel As Ulong, ByVal destination_pixel As Ulong, ByVal parameter As Any Ptr ) As Ulong
    If source_pixel<>rgb(255,0,255) Then
        Return rgba(getR(source_pixel)/1.2,getG(source_pixel)/1.2,getB(source_pixel)/1.2,getA(source_pixel))
    Else
        Return destination_pixel
    End If
End Function

Function cPut(dst As ulong Ptr, x As long, y As long, himage As ulong Ptr, mode As long) As long Export
    Select Case mode
        Case 0
            Put dst,(x,y),himage,PSet
        Case 1
            Put dst,(x,y),himage,PReset
        Case 2
            Put dst,(x,y),himage,Trans
        Case 3
            Put dst,(x,y),himage,And
        Case 4
            Put dst,(x,y),himage,Or
        Case 5
            Put dst,(x,y),himage,Xor
        Case 6
            Put dst,(x,y),himage,Alpha
        Case 7
            Put dst,(x,y),himage,custom,@darken
    End Select
    Return 0
End Function

Function cDrawString(dst As ulong Ptr, x As long, y As long, text As zstring Ptr,col as ulong) As long Export
    draw string dst,(x,y),*text,col
    return 1
End Function

Function cScreenControl(what as long, param1 as long = &h80000000, param2 as long = &h80000000, param3 as long = &h80000000, param4 as long = &h80000000) as long Export
    ScreenControl ( what, param1, param2, param3, param4)
    return 1
End Function

Function cFlip as long Export
    flip
    return 1
End Function

function cImagePitch ( byval image as ulong ptr) as long Export
    dim as any ptr pixdata
    dim as long w,h,bypp,pitch
    ImageInfo ( image, w, h, bypp, pitch, pixdata)
    return pitch
end function

function cImageBypp ( byval image as ulong ptr) as long Export
    dim as any ptr pixdata
    dim as long w,h,bypp,pitch
    ImageInfo ( image, w, h, bypp, pitch, pixdata)
    return bypp
end function

function cImageWidth ( byval image as ulong ptr) as long Export
    dim as any ptr pixdata
    dim as long w,h,bypp,pitch
    ImageInfo ( image, w, h, bypp, pitch, pixdata)
    return w
end function

function cImageHeight ( byval image as ulong ptr) as long Export
    dim as any ptr pixdata
    dim as long w,h,bypp,pitch
    ImageInfo ( image, w, h, bypp, pitch, pixdata)
    return h
end function

function cImagePixels ( byval image as ulong ptr) as any ptr Export
    dim as any ptr pixdata
    dim as long w,h,bypp,pitch
    ImageInfo ( image, w, h, bypp, pitch, pixdata)
    return pixdata
end function


Function cInkey(j as zstring ptr) as long Export
    *j=inkey
    return 1
End Function
'declare sub ScreenControl ( byval what as const long, byref param1 as longint, byref param2 as longint = &h80000000, byref param3 as longint = &h80000000, byref param4 as longint = &h80000000 )
'declare sub ScreenControl ( byval what as const long, byref param as string)



function cMid ( strv as zstring ptr, dest as zstring ptr, start as integer, n as integer = 0 ) as long export
    if n=0 then
        *dest = Mid( *strv, start)
    else
        *dest = Mid( *strv, start, n )
    end if
    return 1
end function

function cInstr ( start as long = 1, strval as zstring ptr, substring as zstring ptr ) as long export
    return instr(start,*strval,*substring)

end function

function convertInt ( value as zstring ptr ) as long export
    return cint(*value)
end function

function convertStr ( value as long, dest as zstring ptr) as long export
    *dest = str(value)
    return 1
end function


function cLen ( value as zstring ptr ) as long export
    return len(*value)
end function

' Multiput by D.J.Peters (Joshy)
' MultiPut [destination],[xmidpos],[ymidpos], source,[xScale],[yScale],[Trans]
type FP16 ' fixed point 16:16
  union
  type
    as ushort l
    as  short h
  end type
  as long v
  end union
end type

#define _ADD_ 0 ' increment a value
#define _CMP_ 1 ' compare values
#define _SET_ 2 ' set a value

#define _XScreen_  0
#define _YScreen_  1
#define _UTexture_ 2
#define _VTexture_ 3

#define _LeftIndex_    0
#define _RightIndex_   1

#define _CurrentIndex_ 0
#define _NextIndex_    1

#define _EdgeXStart_ 0
#define _EdgeUStart_ 1
#define _EdgeVStart_ 2
#define _EdgeXStep_  3
#define _EdgeUStep_  4
#define _EdgeVStep_  5

'#define UseRad 'if not then Rotate are in degrees

Function cMultiPut(Byval pTarget As ulong Ptr= 0, _
             Byval xMidPos As long= 0, _
             Byval yMidPos As long= 0, _
             Byval pSource As ulong Ptr   , _
             Byval xScale  As Double = 1, _
             Byval yScale  As Double = 1, _
             Byval Rotate  As Double = 0, _
             Byval Transparent As boolean = false) as long Export
  Dim As long SourceWidth=any,SourceHeight=any,SourceBytes=any,SourcePitch=any
  Dim as long TargetWidth=any,TargetHeight=any,TargetBytes=any,TargetPitch=any
  Dim As long i=any,yStart=any,yEnd=any,xStart=any,xEnd=any
  Dim As long CNS(1,1)=any 'Counters
  Dim As long ACS(1,2)=any '_ADD_ compare and _SET_
  Dim As Single fPoints(3,3)=any,fEdges(2,6)=any,fLength=any,fUSlope=any,fVSlope=any
  Dim As FP16 U=any,V=any,US=any,VS=any
  Dim As boolean MustRotate = iif(Rotate<>0,true,false)

  If (ScreenPtr()=0) Or (pSource=0) Then return 1

  If xScale < 0.001 Then xScale=0.001
  If yScale < 0.001 Then yScale=0.001
 
  If pTarget=0 Then
    ScreenInfo     _
    TargetWidth  , _
    TargetHeight,, _
    TargetBytes  , _
    TargetPitch
    pTarget=ScreenPtr()
  Else
    ImageInfo     _
    pTarget     , _
    TargetWidth , _
    TargetHeight, _
    TargetBytes , _
    TargetPitch , _
    pTarget
  End If
  If (TargetWidth<4) Or (TargetHeight<4) Then return 1

  ImageInfo     _
  pSource     , _
  SourceWidth , _
  SourceHeight, _
  SourceBytes , _
  SourcePitch , _
  pSource

  Select Case as const TargetBytes
  case 1    ' TargetPitch shr=0 : SourcePitch shr=0
  case 2    : TargetPitch shr=1 : SourcePitch shr=1
  case 4    : TargetPitch shr=2 : SourcePitch shr=2
  case else : return 1
  end select

  fPoints(0,_XScreen_)=-SourceWidth/2 * xScale
  fPoints(1,_XScreen_)= SourceWidth/2 * xScale
  fPoints(2,_XScreen_)= fPoints(1,_XScreen_)
  fPoints(3,_XScreen_)= fPoints(0,_XScreen_)

  fPoints(0,_YScreen_)=-SourceHeight/2 * yScale
  fPoints(1,_YScreen_)= fPoints(0,_YScreen_)
  fPoints(2,_YScreen_)= SourceHeight/2 * yScale
  fPoints(3,_YScreen_)= fPoints(2,_YScreen_)

  fPoints(0,_UTexture_)=0
  fPoints(1,_UTexture_)= SourceWidth
  fPoints(2,_UTexture_)= fPoints(1,_UTexture_)
  fPoints(3,_UTexture_)=0
 
  fPoints(0,_VTexture_)=0
  fPoints(1,_VTexture_)=0
  fPoints(2,_VTexture_)= SourceHeight
  fPoints(3,_VTexture_)= fPoints(2,_VTexture_)

  If MustRotate=true Then
    #ifndef UseRad
    Rotate*=0.017453292 'deg 2 rad
    #endif
    var co = cos(rotate)
    var si = sin(rotate)
    For i=0 To 3
      var x = fPoints(i,_XScreen_)*co - fPoints(i,_YScreen_)*si
      var y = fPoints(i,_XScreen_)*si + fPoints(i,_YScreen_)*co
      fPoints(i,_XScreen_) = x
      fPoints(i,_YScreen_) = y
    Next
  End If
  yStart=30^2:yEnd=-yStart:xStart=yStart:xEnd=yEnd
 
  ' get min max
  For i=0 To 3
    fPoints(i,_XScreen_)=Int(fPoints(i,_XScreen_)+xMidPos)
    fPoints(i,_YScreen_)=Int(fPoints(i,_YScreen_)+yMidPos)
    If fPoints(i,_YScreen_)<yStart Then yStart=fPoints(i,_YScreen_):CNS(_LeftIndex_,_CurrentIndex_)=i
    If fPoints(i,_YScreen_)>yEnd   Then yEnd  =fPoints(i,_YScreen_)
    If fPoints(i,_XScreen_)<xStart Then xStart=fPoints(i,_XScreen_)
    If fPoints(i,_XScreen_)>xEnd   Then xEnd  =fPoints(i,_XScreen_)
  Next

  If yStart = yEnd        Then return 1
  If xStart = xEnd        Then return 1
  If yEnd   < 0           Then return 1
  If xEnd   < 0           Then return 1
  If yStart>=TargetHeight Then return 1
  If xStart>=TargetWidth  Then return 1
 
 
  ACS(_LeftIndex_ ,_ADD_)=-1:ACS(_LeftIndex_ ,_CMP_)=-1:ACS(_LeftIndex_ ,_SET_)=3
  ACS(_RightIndex_,_ADD_)= 1:ACS(_RightIndex_,_CMP_)= 4:ACS(_RightIndex_,_SET_)=0

  ' share the same highest point
  CNS(_RightIndex_,_CurrentIndex_)=CNS(_LeftIndex_,_CurrentIndex_)
 
  ' loop from Top to Bottom
  While yStart<yEnd
    'Scan Left and Right edges together
    For i=_LeftIndex_ To _RightIndex_
      ' bad to read but fast and short ;-)
      If yStart=fPoints(CNS(i,_CurrentIndex_),_YScreen_) Then
        CNS(i,_NextIndex_)=CNS(i,_CurrentIndex_)+ACS(i,_ADD_)
        If CNS(i,_NextIndex_)=ACS(i,_CMP_) Then CNS(i,_NextIndex_)=ACS(i,_SET_)
        While fPoints(CNS(i,_CurrentIndex_),_YScreen_) = fPoints(CNS(i,_NextIndex_),_YScreen_)
          CNS(i,_CurrentIndex_)=CNS(i,_NextIndex_)
          CNS(i,_NextIndex_   )=CNS(i,_CurrentIndex_)+ACS(i,_ADD_)
          If CNS(i,_NextIndex_)=ACS(i,_CMP_) Then CNS(i,_NextIndex_)=ACS(i,_SET_)
        Wend
        fEdges(i,_EdgeXStart_) = fPoints(CNS(i,_CurrentIndex_),_XScreen_)
        fEdges(i,_EdgeUStart_) = fPoints(CNS(i,_CurrentIndex_),_UTexture_)
        fEdges(i,_EdgeVStart_) = fPoints(CNS(i,_CurrentIndex_),_VTexture_)
        fLength  = fPoints(CNS(i,_NextIndex_),_YScreen_) - fPoints(CNS(i,_CurrentIndex_),_YScreen_)
        If fLength <> 0.0 Then
          fLength=1/fLength
          fEdges(i,_EdgeXStep_) = fPoints(CNS(i,_NextIndex_),_XScreen_ )-fEdges(i,_EdgeXStart_):fEdges(i,_EdgeXStep_)*=fLength
          fEdges(i,_EdgeUStep_) = fPoints(CNS(i,_NextIndex_),_UTexture_)-fEdges(i,_EdgeUStart_):fEdges(i,_EdgeUStep_)*=fLength
          fEdges(i,_EdgeVStep_) = fPoints(CNS(i,_NextIndex_),_VTexture_)-fEdges(i,_EdgeVStart_):fEdges(i,_EdgeVStep_)*=fLength
        End If
        CNS(i,_CurrentIndex_)=CNS(i,_NextIndex_)
      End If
    Next

    If (yStart<0)                                                   Then Goto NextScanLine
    xStart=fEdges(_LeftIndex_ ,_EdgeXStart_):If xStart>=TargetWidth Then Goto NextScanLine
    xEnd  =fEdges(_RightIndex_,_EdgeXStart_):If xEnd  < 0           Then Goto NextScanLine
    If (xStart=xEnd)                                                Then Goto NextScanLine
    if xEnd  <xStart                                                Then goto NextScanLine

    fLength=1/(xEnd-xStart)
    fUSlope=fEdges(_RightIndex_,_EdgeUStart_)-fEdges(_LeftIndex_,_EdgeUStart_):fUSlope*=fLength
    fVSlope=fEdges(_RightIndex_,_EdgeVStart_)-fEdges(_LeftIndex_,_EdgeVStart_):fVSlope*=fLength
    If xStart<0 Then
      fLength=-xStart
      U.v=(fEdges(_LeftIndex_,_EdgeUStart_)+fUSlope*fLength)*&HFFFF
      V.v=(fEdges(_LeftIndex_,_EdgeVStart_)+fVSlope*fLength)*&HFFFF
      xStart = 0
    Else
      U.v=fEdges(_LeftIndex_,_EdgeUStart_)*&HFFFF
      V.v=fEdges(_LeftIndex_,_EdgeVStart_)*&HFFFF
    End If
    If u.v<0 Then u.v=0
    If v.v<0 Then v.v=0
    US.v=fUSlope*&HFFFF
    VS.v=fVSlope*&HFFFF

    If xEnd>=TargetWidth Then xEnd=TargetWidth-1

    Select Case as const TargetBytes
    Case 1
      var s=cptr(ubyte ptr,pSource)
      var t=cptr(ubyte ptr,pTarget)+yStart*TargetPitch+xStart
      var e=t+(xEnd-xStart)
      If Transparent=false Then
        While t<e
          *t=*(s+V.h*SourcePitch+U.h)
          V.v+=VS.v : U.v+=US.v : t+=1
        Wend
      Else
        While t<e
          dim as ubyte c=*(s+V.h*SourcePitch+U.h)
          If c Then *t=c
          V.v+=VS.v : U.v+=US.v : t+=1
        Wend
      End If
    Case 2
      var s=cptr(ushort ptr,pSource)
      var t=cptr(ushort ptr,pTarget)+yStart*TargetPitch+xStart
      var e=t+(xEnd-xStart)
      If Transparent=false Then
        While t<e
          *t=*(s+V.h*SourcePitch+U.h)
          V.v+=VS.v : U.v+=US.v : t+=1
        Wend
      Else
        While t<e
          dim as ushort c=*(s+V.h*SourcePitch+U.h)
          If c<>&HF81F Then *t=c
          V.v+=VS.v : U.v+=US.v : t+=1
        Wend
      End If
    Case 4
      var s=cptr(ulong ptr,pSource)
      var t=cptr(ulong ptr,pTarget)+yStart*TargetPitch+xStart
      var e=t+(xEnd-xStart)
      If Transparent=false Then
        While t<e
          *t=*(s+V.h*SourcePitch+U.h)
          V.v+=VS.v : U.v+=US.v : t+=1
        Wend
      Else
        While t<e
          dim as ulong c=*(s+V.h*SourcePitch+U.h)
          If c<>&HFFFF00FF Then *t=c
          V.v+=VS.v : U.v+=US.v : t+=1
        Wend
      End If
    End Select

  NextScanLine:
    yStart+=1 : If yStart=TargetHeight Then exit while
    fEdges(_LeftIndex_ ,_EdgeXStart_)+=fEdges(_LeftIndex_ ,_EdgeXStep_)
    fEdges(_LeftIndex_ ,_EdgeUStart_)+=fEdges(_LeftIndex_ ,_EdgeUStep_)
    fEdges(_LeftIndex_ ,_EdgeVStart_)+=fEdges(_LeftIndex_ ,_EdgeVStep_)
    fEdges(_RightIndex_,_EdgeXStart_)+=fEdges(_RightIndex_,_EdgeXStep_)
    fEdges(_RightIndex_,_EdgeUStart_)+=fEdges(_RightIndex_,_EdgeUStep_)
    fEdges(_RightIndex_,_EdgeVStart_)+=fEdges(_RightIndex_,_EdgeVStep_)
  Wend
End Function




End extern
