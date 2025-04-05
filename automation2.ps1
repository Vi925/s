

# Process .c files in "Private-main" and copy contents to clipboard
$folderPath = "$PSScriptRoot\this"
$files = Get-ChildItem -Path $folderPath -Filter "*.y"

$clipboardContent = ""

foreach ($file in $files) {
    $filename = $file.Name
    $content = Get-Content -Path $file.FullName -Raw  # Read full file content
    $clipboardContent += "$filename`n`n$content`n`n"
}

# Copy to clipboard
Set-Clipboard -Value $clipboardContent
Write-Output "Copied all .c files to clipboard."



Write-Output "done."
