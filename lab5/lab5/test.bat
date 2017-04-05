set PROGRAM="%~1" 
fc big.txt out.txt
if ERRORLEVEL 1 goto err
echo Program testing succeded
pause
exit 0
