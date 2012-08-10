C:\_workspaces\_workspace_04_etalis\2012_08_01_etalis\_experiments\assert_vs_record>"c:\Program Files (x86)\Yap\bin\yap.exe" -g "['generator_yap.pl'], test1(100000), test2(10
0000),  test3(100000), test4(100000), halt."
% Restoring file C:\Program Files (x86)\Yap\lib\startup.yss
YAP 6.2.2 (i686-mingw32): Thu Oct 20 22:33:57 GMTDT 2011
 % consulting C:\_workspaces\_workspace_04_etalis\2012_08_01_etalis\_experiments\assert_vs_record\generator_yap.pl...
 % consulted C:\_workspaces\_workspace_04_etalis\2012_08_01_etalis\_experiments\assert_vs_record\generator_yap.pl in module user, 0 msec 8312 bytes
asserta: 0.203
recorda: 0.078
assertz: 0.374
recordz: 0.031
% YAP execution halted

C:\_workspaces\_workspace_04_etalis\2012_08_01_etalis\_experiments\assert_vs_record>swipl -g "['generator_swi.pl'], test1(100000), test2(100000),  test3(100000), test4(100000
), halt."
C:\_workspaces\_workspace_04_etalis\2012_08_01_etalis\_experiments\assert_vs_record>"c:\Program Files\pl\bin\swipl" -g "['generator_swi.pl'], test1(100000), test2(100000),  t
est3(100000), test4(100000), halt."
% generator_swi.pl compiled 0.02 sec, 14 clauses
asserta: 0.38499999046325684
recorda: 0.7980000972747803
assertz: 0.14899992942810059
recordz: 0.6489999294281006

---------------
for 1mil tuples:
Yap
assert: 2 sec
record: takes a very long time
