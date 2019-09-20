<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting keepoldvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="mm" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="mm"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="common">
<packages>
<package name="HLK5M05">
<pad name="1" x="2.2" y="3" drill="1" diameter="1.5" thermals="no"/>
<pad name="2" x="2.2" y="-3" drill="1" diameter="1.5" thermals="no"/>
<pad name="3" x="35.8" y="10.25" drill="1" diameter="1.5" thermals="no"/>
<pad name="4" x="35.8" y="-10.25" drill="1" diameter="1.5" thermals="no"/>
<wire x1="0" y1="11.5" x2="38" y2="11.5" width="0.2" layer="51"/>
<wire x1="38" y1="11.5" x2="38" y2="-11.5" width="0.2" layer="51"/>
<wire x1="38" y1="-11.5" x2="0" y2="-11.5" width="0.2" layer="51"/>
<wire x1="0" y1="-11.5" x2="0" y2="11.5" width="0.2" layer="51"/>
<wire x1="0" y1="11.5" x2="38" y2="11.5" width="0.1" layer="21"/>
<wire x1="38" y1="11.5" x2="38" y2="-11.5" width="0.1" layer="21"/>
<wire x1="38" y1="-11.5" x2="0" y2="-11.5" width="0.1" layer="21"/>
<wire x1="0" y1="-11.5" x2="0" y2="11.5" width="0.1" layer="21"/>
<wire x1="-1.6" y1="12.5" x2="39" y2="12.5" width="0.1" layer="51"/>
<wire x1="39" y1="12.5" x2="39" y2="-12.5" width="0.1" layer="51"/>
<wire x1="39" y1="-12.5" x2="-1.6" y2="-12.5" width="0.1" layer="51"/>
<wire x1="-1.6" y1="-12.5" x2="-1.6" y2="12.5" width="0.1" layer="51"/>
<wire x1="-0.5" y1="3.1" x2="-0.5" y2="3.1" width="0.2" layer="21"/>
<wire x1="-0.5" y1="2.9" x2="-0.5" y2="3.1" width="0.2" layer="21" curve="180"/>
<wire x1="-0.5" y1="2.9" x2="-0.5" y2="2.9" width="0.2" layer="21"/>
<wire x1="-0.5" y1="3.1" x2="-0.5" y2="2.9" width="0.2" layer="21" curve="180"/>
</package>
<package name="DIP-4/400MIL">
<pad name="1" x="-5.08" y="1.27" drill="0.9" diameter="1.5" shape="square" thermals="no"/>
<pad name="2" x="-5.08" y="-1.27" drill="0.9" diameter="1.5" thermals="no"/>
<pad name="3" x="5.08" y="-1.27" drill="0.9" diameter="1.5" thermals="no"/>
<pad name="4" x="5.08" y="1.27" drill="0.9" diameter="1.5" thermals="no"/>
<wire x1="-3.3" y1="2.6" x2="-3.3" y2="-2.6" width="0.25" layer="21"/>
<wire x1="-3.3" y1="-2.6" x2="3.3" y2="-2.6" width="0.25" layer="21"/>
<wire x1="3.3" y1="-2.6" x2="3.3" y2="2.6" width="0.25" layer="21"/>
<wire x1="3.3" y1="2.6" x2="0.6" y2="2.6" width="0.25" layer="21"/>
<wire x1="-0.6" y1="2.6" x2="-3.3" y2="2.6" width="0.25" layer="21"/>
<wire x1="-0.6" y1="2.6" x2="0.6" y2="2.6" width="0.25" layer="21" curve="179.92358"/>
</package>
<package name="D1-MINI">
<pad name="1" x="-11.43" y="8.89" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="2" x="-11.43" y="6.35" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="3" x="-11.43" y="3.81" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="4" x="-11.43" y="1.27" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="5" x="-11.43" y="-1.27" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="6" x="-11.43" y="-3.81" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="7" x="-11.43" y="-6.35" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="8" x="-11.43" y="-8.89" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="9" x="11.43" y="-8.89" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="10" x="11.43" y="-6.35" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="11" x="11.43" y="-3.81" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="12" x="11.43" y="-1.27" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="13" x="11.43" y="1.27" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="14" x="11.43" y="3.81" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="15" x="11.43" y="6.35" drill="1.11" diameter="1.61" thermals="no"/>
<pad name="16" x="11.43" y="8.89" drill="1.11" diameter="1.61" thermals="no"/>
<wire x1="-12.8" y1="17.1" x2="12.8" y2="17.1" width="0.2" layer="51"/>
<wire x1="12.8" y1="17.1" x2="12.8" y2="-17.1" width="0.2" layer="51"/>
<wire x1="12.8" y1="-17.1" x2="-12.8" y2="-17.1" width="0.2" layer="51"/>
<wire x1="-12.8" y1="-17.1" x2="-12.8" y2="17.1" width="0.2" layer="51"/>
<wire x1="-12.8" y1="-17.1" x2="-12.8" y2="17.1" width="0.2" layer="21"/>
<wire x1="-12.8" y1="17.1" x2="12.8" y2="17.1" width="0.2" layer="21"/>
<wire x1="12.8" y1="17.1" x2="12.8" y2="-17.1" width="0.2" layer="21"/>
<wire x1="12.8" y1="-17.1" x2="-12.8" y2="-17.1" width="0.2" layer="21"/>
<circle x="-14.225" y="9.713" radius="0.174" width="0.2" layer="21"/>
</package>
<package name="LED100">
<pad name="2" x="1.27" y="0" drill="0.711" diameter="1.27" thermals="no"/>
<pad name="1" x="-1.27" y="0" drill="0.711" diameter="1.27" shape="square" rot="R90" thermals="no"/>
<wire x1="-2.54" y1="-1.903" x2="-2.54" y2="1.903" width="0.25" layer="21"/>
<wire x1="-2.534" y1="-1.911" x2="-2.534" y2="1.911" width="0.25" layer="21" curve="285.973302"/>
</package>
<package name="RES-7.62/4X1.5">
<pad name="2" x="3.81" y="0" drill="0.559" diameter="1.27" thermals="no"/>
<pad name="1" x="-3.81" y="0" drill="0.559" diameter="1.27" thermals="no"/>
<wire x1="2.036" y1="-0.762" x2="2.036" y2="0.762" width="0.25" layer="21"/>
<wire x1="-2.036" y1="-0.762" x2="2.036" y2="-0.762" width="0.25" layer="21"/>
<wire x1="-2.036" y1="-0.762" x2="-2.036" y2="0.762" width="0.25" layer="21"/>
<wire x1="-2.036" y1="0.762" x2="2.036" y2="0.762" width="0.25" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="HLK-5M05">
<wire x1="-8.89" y1="3.81" x2="8.89" y2="3.81" width="0.254" layer="94"/>
<wire x1="8.89" y1="-3.81" x2="8.89" y2="3.81" width="0.254" layer="94"/>
<wire x1="8.89" y1="-3.81" x2="-8.89" y2="-3.81" width="0.254" layer="94"/>
<wire x1="-8.89" y1="3.81" x2="-8.89" y2="-3.81" width="0.254" layer="94"/>
<pin name="AC_1" x="-13.97" y="1.27" length="middle"/>
<pin name="AC_2" x="-13.97" y="-1.27" length="middle"/>
<pin name="-VO" x="13.97" y="1.27" length="middle" rot="R180"/>
<pin name="+VO" x="13.97" y="-1.27" length="middle" rot="R180"/>
</symbol>
<symbol name="LTV-817M">
<wire x1="-3.175" y1="2.54" x2="-5.08" y2="2.54" width="0.25" layer="94"/>
<wire x1="-3.175" y1="0.635" x2="-3.175" y2="2.54" width="0.25" layer="94"/>
<wire x1="-3.175" y1="-2.54" x2="-3.175" y2="-0.635" width="0.25" layer="94"/>
<wire x1="-5.08" y1="3.81" x2="5.08" y2="3.81" width="0.25" layer="94"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="-3.81" width="0.25" layer="94"/>
<wire x1="5.08" y1="-3.81" x2="-5.08" y2="-3.81" width="0.25" layer="94"/>
<wire x1="-5.08" y1="-3.81" x2="-5.08" y2="3.81" width="0.25" layer="94"/>
<wire x1="-3.81" y1="-0.635" x2="-2.54" y2="-0.635" width="0.25" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-3.175" y2="-2.54" width="0.25" layer="94"/>
<wire x1="3.81" y1="2.54" x2="5.08" y2="2.54" width="0.25" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="5.08" y2="-2.54" width="0.25" layer="94"/>
<wire x1="-3.81" y1="0.635" x2="-2.54" y2="0.635" width="0.25" layer="94"/>
<wire x1="-2.54" y1="0.635" x2="-3.175" y2="-0.635" width="0.25" layer="94"/>
<wire x1="-3.175" y1="-0.635" x2="-3.81" y2="0.635" width="0.25" layer="94"/>
<wire x1="1.422" y1="1.905" x2="1.422" y2="-1.905" width="0.25" layer="94"/>
<wire x1="3.81" y1="2.54" x2="1.429" y2="1.111" width="0.25" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="1.429" y2="-0.952" width="0.25" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="2.222" y2="-2.064" width="0.25" layer="94"/>
<wire x1="2.222" y1="-2.064" x2="2.699" y2="-1.27" width="0.25" layer="94"/>
<wire x1="2.699" y1="-1.27" x2="3.81" y2="-2.54" width="0.25" layer="94"/>
<pin name="ANODE" x="-7.62" y="2.54" visible="pad" length="short" direction="pas"/>
<pin name="CATHODE" x="-7.62" y="-2.54" visible="pad" length="short" direction="pas"/>
<pin name="EMITTER" x="7.62" y="-2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="COLLECTOR" x="7.62" y="2.54" visible="pad" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="D1_MINI">
<wire x1="-7.62" y1="11.43" x2="7.62" y2="11.43" width="0.254" layer="94"/>
<wire x1="7.62" y1="-11.43" x2="7.62" y2="11.43" width="0.254" layer="94"/>
<wire x1="7.62" y1="-11.43" x2="-7.62" y2="-11.43" width="0.254" layer="94"/>
<wire x1="-7.62" y1="11.43" x2="-7.62" y2="-11.43" width="0.254" layer="94"/>
<pin name="RST" x="-12.7" y="8.89" visible="pad" length="middle"/>
<pin name="A0" x="-12.7" y="6.35" visible="pad" length="middle"/>
<pin name="D0" x="-12.7" y="3.81" visible="pad" length="middle"/>
<pin name="D5" x="-12.7" y="1.27" visible="pad" length="middle"/>
<pin name="D6" x="-12.7" y="-1.27" visible="pad" length="middle"/>
<pin name="D7" x="-12.7" y="-3.81" visible="pad" length="middle"/>
<pin name="D8" x="-12.7" y="-6.35" visible="pad" length="middle"/>
<pin name="3V3" x="-12.7" y="-8.89" visible="pad" length="middle"/>
<pin name="5V" x="12.7" y="-8.89" visible="pad" length="middle" rot="R180"/>
<pin name="GND" x="12.7" y="-6.35" visible="pad" length="middle" rot="R180"/>
<pin name="D4" x="12.7" y="-3.81" visible="pad" length="middle" rot="R180"/>
<pin name="D3" x="12.7" y="-1.27" visible="pad" length="middle" rot="R180"/>
<pin name="D2" x="12.7" y="1.27" visible="pad" length="middle" rot="R180"/>
<pin name="D1" x="12.7" y="3.81" visible="pad" length="middle" rot="R180"/>
<pin name="RX" x="12.7" y="6.35" visible="pad" length="middle" rot="R180"/>
<pin name="TX" x="12.7" y="8.89" visible="pad" length="middle" rot="R180"/>
</symbol>
<symbol name="+5V">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.25" layer="94"/>
<pin name="+5V" x="0" y="-2.54" visible="pad" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="RELAY_STATIC">
<wire x1="-2.521" y1="8.37" x2="2.559" y2="8.37" width="0.25" layer="94"/>
<wire x1="2.559" y1="8.37" x2="2.559" y2="-1.79" width="0.25" layer="94"/>
<wire x1="2.559" y1="-1.79" x2="-2.521" y2="-1.79" width="0.25" layer="94"/>
<wire x1="-2.521" y1="-1.79" x2="-2.521" y2="8.37" width="0.25" layer="94"/>
<wire x1="-3.791" y1="-5.37" x2="-3.791" y2="-8.37" width="0.25" layer="94"/>
<wire x1="0.019" y1="-1.79" x2="0.019" y2="-2.425" width="0.25" layer="94"/>
<wire x1="0.019" y1="-3.06" x2="0.019" y2="-3.695" width="0.25" layer="94"/>
<wire x1="0.006" y1="-4.34" x2="0.006" y2="-5.292" width="0.25" layer="94"/>
<wire x1="-3.816" y1="-6.89" x2="5.709" y2="-2.911" width="0.25" layer="94"/>
<wire x1="-6.356" y1="-6.87" x2="-3.816" y2="-6.87" width="0.25" layer="94"/>
<wire x1="4.439" y1="-6.87" x2="6.344" y2="-6.87" width="0.25" layer="94"/>
<pin name="1" x="5.086" y="3.29" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="2" x="-5.074" y="3.29" visible="pad" length="short" direction="pas"/>
<pin name="4" x="8.896" y="-6.87" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="3" x="-8.884" y="-6.87" visible="pad" length="short" direction="pas"/>
</symbol>
<symbol name="LED">
<circle x="-0.787" y="-0.787" radius="3.175" width="0.254" layer="94"/>
<wire x1="0.787" y1="-2.692" x2="0.787" y2="1.118" width="0.25" layer="94"/>
<wire x1="2.388" y1="1.422" x2="3.962" y2="3.023" width="0.25" layer="94"/>
<wire x1="1.422" y1="2.388" x2="3.023" y2="3.962" width="0.25" layer="94"/>
<wire x1="0.787" y1="-0.787" x2="1.753" y2="-0.787" width="0.25" layer="94"/>
<wire x1="-3.327" y1="-0.787" x2="-2.388" y2="-0.787" width="0.25" layer="94"/>
<wire x1="3.327" y1="2.692" x2="3.658" y2="2.388" width="0.25" layer="94"/>
<wire x1="3.658" y1="2.388" x2="3.962" y2="3.023" width="0.25" layer="94"/>
<wire x1="3.962" y1="3.023" x2="3.327" y2="2.692" width="0.25" layer="94"/>
<wire x1="2.388" y1="3.658" x2="2.692" y2="3.327" width="0.25" layer="94"/>
<wire x1="2.692" y1="3.327" x2="3.023" y2="3.962" width="0.25" layer="94"/>
<wire x1="3.023" y1="3.962" x2="2.388" y2="3.658" width="0.25" layer="94"/>
<wire x1="0.787" y1="-0.787" x2="-2.388" y2="1.118" width="0.25" layer="94"/>
<wire x1="-2.388" y1="1.118" x2="-2.388" y2="-2.692" width="0.25" layer="94"/>
<wire x1="-2.388" y1="-2.692" x2="0.787" y2="-0.787" width="0.25" layer="94"/>
<pin name="K" x="4.293" y="-0.787" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="A" x="-5.867" y="-0.787" visible="pad" length="short" direction="pas"/>
</symbol>
<symbol name="RES">
<wire x1="3.175" y1="-1.27" x2="3.81" y2="0" width="0.25" layer="94"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="-1.27" width="0.25" layer="94"/>
<wire x1="0.635" y1="-1.27" x2="1.905" y2="1.27" width="0.25" layer="94"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="-1.27" width="0.25" layer="94"/>
<wire x1="-1.905" y1="-1.27" x2="-0.635" y2="1.27" width="0.25" layer="94"/>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="-1.27" width="0.25" layer="94"/>
<wire x1="-3.81" y1="0" x2="-3.175" y2="1.27" width="0.25" layer="94"/>
<pin name="B" x="6.35" y="0" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="A" x="-6.35" y="0" visible="pad" length="short" direction="pas"/>
</symbol>
<symbol name="PUSHBUTTON_NO">
<wire x1="2.56" y1="2.919" x2="-2.559" y2="2.919" width="0.254" layer="94" curve="44.012965"/>
<circle x="4.445" y="-2.781" radius="0.635" width="0.254" layer="94"/>
<circle x="-4.445" y="-2.781" radius="0.635" width="0.254" layer="94"/>
<wire x1="0" y1="-0.241" x2="0" y2="3.315" width="0.25" layer="94"/>
<wire x1="-4.445" y1="-0.241" x2="4.445" y2="-0.241" width="0.25" layer="94"/>
<pin name="C2" x="7.62" y="-2.781" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="C1" x="-7.62" y="-2.781" visible="pad" length="short" direction="pas"/>
</symbol>
<symbol name="NPN">
<circle x="0" y="0" radius="3.81" width="0.254" layer="94"/>
<wire x1="-2.845" y1="0" x2="-1.575" y2="0" width="0.25" layer="94"/>
<wire x1="2.235" y1="2.21" x2="2.235" y2="2.54" width="0.25" layer="94"/>
<wire x1="2.235" y1="-2.54" x2="2.235" y2="-2.21" width="0.25" layer="94"/>
<wire x1="-1.575" y1="-0.94" x2="2.235" y2="-2.21" width="0.25" layer="94"/>
<wire x1="-1.575" y1="0.94" x2="2.235" y2="2.21" width="0.25" layer="94"/>
<wire x1="-1.575" y1="-2.21" x2="-1.575" y2="2.21" width="0.25" layer="94"/>
<wire x1="1.27" y1="-1.905" x2="-0.305" y2="-1.905" width="0.25" layer="94"/>
<wire x1="-0.305" y1="-1.905" x2="0" y2="-0.94" width="0.25" layer="94"/>
<wire x1="0" y1="-0.94" x2="1.27" y2="-1.905" width="0.25" layer="94"/>
<pin name="B" x="-5.385" y="0" visible="pad" length="short" direction="pas"/>
<pin name="E" x="2.235" y="-5.08" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="C" x="2.235" y="5.08" visible="pad" length="short" direction="pas" rot="R270"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="1.016" x2="1.905" y2="1.016" width="0.25" layer="94"/>
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.25" layer="94"/>
<wire x1="-0.508" y1="-1.016" x2="0.508" y2="-1.016" width="0.25" layer="94"/>
<pin name="GND" x="0" y="3.556" visible="pad" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="HLK-5M05" prefix="PS">
<gates>
<gate name="PART_1" symbol="HLK-5M05" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HLK5M05">
<connects>
<connect gate="PART_1" pin="+VO" pad="4"/>
<connect gate="PART_1" pin="-VO" pad="3"/>
<connect gate="PART_1" pin="AC_1" pad="1"/>
<connect gate="PART_1" pin="AC_2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="5W ultra-compact power module HLK-5M05"/>
<attribute name="HEIGHT" value="18mm"/>
<attribute name="MANUFACTURER_NAME" value="Hi-Link"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="HLK-5M05"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LTV-817M" prefix="VO">
<gates>
<gate name="PART_1" symbol="LTV-817M" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP-4/400MIL">
<connects>
<connect gate="PART_1" pin="ANODE" pad="1"/>
<connect gate="PART_1" pin="CATHODE" pad="2"/>
<connect gate="PART_1" pin="COLLECTOR" pad="4"/>
<connect gate="PART_1" pin="EMITTER" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="DATASHEET" value="http://datasheets.diptrace.com/optoisolators/LTV-817_827_847.pdf"/>
<attribute name="MANUFACTURER" value="Lite-On"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="D1_MINI" prefix="U">
<gates>
<gate name="PART_1" symbol="D1_MINI" x="0" y="0"/>
</gates>
<devices>
<device name="" package="D1-MINI">
<connects>
<connect gate="PART_1" pin="3V3" pad="8"/>
<connect gate="PART_1" pin="5V" pad="9"/>
<connect gate="PART_1" pin="A0" pad="2"/>
<connect gate="PART_1" pin="D0" pad="3"/>
<connect gate="PART_1" pin="D1" pad="14"/>
<connect gate="PART_1" pin="D2" pad="13"/>
<connect gate="PART_1" pin="D3" pad="12"/>
<connect gate="PART_1" pin="D4" pad="11"/>
<connect gate="PART_1" pin="D5" pad="4"/>
<connect gate="PART_1" pin="D6" pad="5"/>
<connect gate="PART_1" pin="D7" pad="6"/>
<connect gate="PART_1" pin="D8" pad="7"/>
<connect gate="PART_1" pin="GND" pad="10"/>
<connect gate="PART_1" pin="RST" pad="1"/>
<connect gate="PART_1" pin="RX" pad="15"/>
<connect gate="PART_1" pin="TX" pad="16"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="wifi board based on ESP-8266EX."/>
<attribute name="HEIGHT" value="mm"/>
<attribute name="MANUFACTURER_NAME" value="Wemos"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="D1 Mini"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="NETPORT">
<gates>
<gate name="PART_1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RELAY_STATIC" prefix="K">
<gates>
<gate name="PART_1" symbol="RELAY_STATIC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="ATTR_1" value="Semiconductor Make Contact"/>
<attribute name="DESCRIPTION" value="Static Relay"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LED" prefix="D">
<gates>
<gate name="PART_1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LED100">
<connects>
<connect gate="PART_1" pin="A" pad="2"/>
<connect gate="PART_1" pin="K" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RES" prefix="R">
<gates>
<gate name="PART_1" symbol="RES" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RES-7.62/4X1.5">
<connects>
<connect gate="PART_1" pin="A" pad="1"/>
<connect gate="PART_1" pin="B" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="200"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PUSHBUTTON_NO" prefix="S">
<gates>
<gate name="PART_1" symbol="PUSHBUTTON_NO" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="ATTR_1" value="Normally Open"/>
<attribute name="DESCRIPTION" value="Pushbutton"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NPN" prefix="Q">
<gates>
<gate name="PART_1" symbol="NPN" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="Bipolar NPN"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="NETPORT">
<gates>
<gate name="PART_1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U1" library="common" deviceset="D1_MINI" device=""/>
<part name="R7" library="common" deviceset="RES" device="" value="200"/>
<part name="R1" library="common" deviceset="RES" device=""/>
<part name="R2" library="common" deviceset="RES" device=""/>
<part name="R3" library="common" deviceset="RES" device=""/>
<part name="R4" library="common" deviceset="RES" device=""/>
<part name="R5" library="common" deviceset="RES" device=""/>
<part name="R6" library="common" deviceset="RES" device=""/>
<part name="D1" library="common" deviceset="LED" device=""/>
<part name="NETPORT1" library="common" deviceset="+5V" device=""/>
<part name="NETPORT2" library="common" deviceset="GND" device=""/>
<part name="VO1" library="common" deviceset="LTV-817M" device=""/>
<part name="NETPORT3" library="common" deviceset="GND" device=""/>
<part name="S1" library="common" deviceset="PUSHBUTTON_NO" device=""/>
<part name="K1" library="common" deviceset="RELAY_STATIC" device=""/>
<part name="Q1" library="common" deviceset="NPN" device=""/>
<part name="PS1" library="common" deviceset="HLK-5M05" device=""/>
<part name="NETPORT4" library="common" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="PART_1" x="-81.28" y="36.83" smashed="yes" rot="R180"/>
<instance part="R7" gate="PART_1" x="-109.22" y="-15.24" smashed="yes" rot="R270"/>
<instance part="R1" gate="PART_1" x="-44.45" y="35.56" smashed="yes" rot="R180"/>
<instance part="R2" gate="PART_1" x="-29.21" y="35.56" smashed="yes" rot="R180"/>
<instance part="R3" gate="PART_1" x="-17.78" y="30.48" smashed="yes"/>
<instance part="R4" gate="PART_1" x="-17.78" y="20.32" smashed="yes"/>
<instance part="R5" gate="PART_1" x="-17.78" y="12.7" smashed="yes"/>
<instance part="R6" gate="PART_1" x="-17.78" y="2.54" smashed="yes"/>
<instance part="D1" gate="PART_1" x="-108.433" y="-2.057" smashed="yes" rot="R270"/>
<instance part="NETPORT1" gate="PART_1" x="-116.84" y="49.53" smashed="yes"/>
<instance part="NETPORT2" gate="PART_1" x="-116.84" y="10.414" smashed="yes"/>
<instance part="VO1" gate="PART_1" x="-8.89" y="-12.7" smashed="yes"/>
<instance part="NETPORT3" gate="PART_1" x="-109.22" y="-35.306" smashed="yes"/>
<instance part="S1" gate="PART_1" x="-96.279" y="-11.43" smashed="yes" rot="R270"/>
<instance part="K1" gate="PART_1" x="-46.996" y="-13.45" smashed="yes"/>
<instance part="Q1" gate="PART_1" x="-35.56" y="25.095" smashed="yes" rot="R270"/>
<instance part="PS1" gate="PART_1" x="-72.39" y="-1.27" smashed="yes"/>
<instance part="NETPORT4" gate="PART_1" x="10.16" y="19.304" smashed="yes"/>
</instances>
<busses>
</busses>
<nets>
<net name="NET_0" class="0">
<segment>
<wire x1="-93.98" y1="45.72" x2="-116.84" y2="45.72" width="0.25" layer="91"/>
<wire x1="-116.84" y1="45.72" x2="-116.84" y2="46.99" width="0.25" layer="91"/>
<pinref part="U1" gate="PART_1" pin="5V"/>
<pinref part="NETPORT1" gate="PART_1" pin="+5V"/>
</segment>
</net>
<net name="NET_1" class="0">
<segment>
<wire x1="-109.22" y1="-21.59" x2="-109.22" y2="-25.4" width="0.25" layer="91"/>
<wire x1="-109.22" y1="-25.4" x2="-109.22" y2="-31.75" width="0.25" layer="91"/>
<pinref part="R7" gate="PART_1" pin="B"/>
<pinref part="NETPORT3" gate="PART_1" pin="GND"/>
<wire x1="-99.06" y1="-19.05" x2="-99.06" y2="-25.4" width="0.25" layer="91"/>
<wire x1="-99.06" y1="-25.4" x2="-109.22" y2="-25.4" width="0.25" layer="91"/>
<pinref part="S1" gate="PART_1" pin="C2"/>
<junction x="-109.22" y="-25.4"/>
</segment>
<segment>
<wire x1="-93.98" y1="43.18" x2="-116.84" y2="43.18" width="0.25" layer="91"/>
<wire x1="-116.84" y1="43.18" x2="-116.84" y2="13.97" width="0.25" layer="91"/>
<pinref part="U1" gate="PART_1" pin="GND"/>
<pinref part="NETPORT2" gate="PART_1" pin="GND"/>
</segment>
<segment>
<wire x1="-22.86" y1="35.56" x2="10.16" y2="35.56" width="0.25" layer="91"/>
<wire x1="10.16" y1="35.56" x2="10.16" y2="22.86" width="0.25" layer="91"/>
<pinref part="R2" gate="PART_1" pin="A"/>
<pinref part="NETPORT4" gate="PART_1" pin="GND"/>
</segment>
</net>
<net name="NET_2" class="0">
<segment>
<wire x1="-93.98" y1="40.64" x2="-109.22" y2="40.64" width="0.25" layer="91"/>
<wire x1="-109.22" y1="40.64" x2="-109.22" y2="3.81" width="0.25" layer="91"/>
<pinref part="U1" gate="PART_1" pin="D4"/>
<pinref part="D1" gate="PART_1" pin="A"/>
</segment>
</net>
<net name="NET_3" class="0">
<segment>
<wire x1="-109.22" y1="-6.35" x2="-109.22" y2="-8.89" width="0.25" layer="91"/>
<pinref part="D1" gate="PART_1" pin="K"/>
<pinref part="R7" gate="PART_1" pin="A"/>
</segment>
</net>
<net name="NET_4" class="0">
<segment>
<wire x1="-93.98" y1="35.56" x2="-99.06" y2="35.56" width="0.25" layer="91"/>
<wire x1="-99.06" y1="35.56" x2="-99.06" y2="-3.81" width="0.25" layer="91"/>
<pinref part="U1" gate="PART_1" pin="D2"/>
<pinref part="S1" gate="PART_1" pin="C1"/>
</segment>
</net>
<net name="NET_5" class="0">
<segment>
<wire x1="-38.1" y1="35.56" x2="-35.56" y2="35.56" width="0.25" layer="91"/>
<pinref part="R1" gate="PART_1" pin="A"/>
<pinref part="R2" gate="PART_1" pin="B"/>
<wire x1="-35.56" y1="35.56" x2="-35.56" y2="30.48" width="0.25" layer="91"/>
<pinref part="Q1" gate="PART_1" pin="B"/>
<junction x="-35.56" y="35.56"/>
</segment>
</net>
<net name="NET_6" class="0">
<segment>
<wire x1="-68.58" y1="35.56" x2="-50.8" y2="35.56" width="0.25" layer="91"/>
<pinref part="U1" gate="PART_1" pin="D5"/>
<pinref part="R1" gate="PART_1" pin="B"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
