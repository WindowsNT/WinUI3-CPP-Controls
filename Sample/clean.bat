@echo off
del /q /s *.ncb *.sdf *.obj *.iobj *.map *.res *.dsw *.ils *.ilc *.ild *.ilf *.ilk *.tds *.upx *.tmp *.idb *.pdb *.pch *.ipch *.ipdb *.aqt *.000 *.aps Browse.VC.db 
del "Generated Files"\* /s /q 
del packages\* /s /q
del x64\* /s /q
del Sample\x64\* /s /q
del .vs\Sample\CopilotIndices\* /s /q
msbuild Sample.sln -target:Clean
