@echo off
set MATLAB=S:\Matlab R2019a

call  "\\Laksie\S$\Matlab R2019a\bin\win64\checkMATLABRootForDriveMap.exe" "\\Laksie\S$\Matlab R2019a"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
"%MATLAB%\bin\win64\gmake" -f PV_fed_VCIMD_updated.mk MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN% 
