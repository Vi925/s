

# Copy js to clipboard
$jsContent = @"
yacc -d yourfile.y   
lex yourfile.l       
gcc lex.yy.c y.tab.c -o your_program -ly
"@

Set-Clipboard -Value $jsContent











Write-Output "done."
