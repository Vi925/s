

# Process .c files in "Private-main" and copy contents to clipboard
$folderPath = "$PSScriptRoot\this"
$files = Get-ChildItem -Path $folderPath -Filter "*.c"

$clipboardContent = ""

foreach ($file in $files) {
    $filename = $file.Name
    $content = Get-Content -Path $file.FullName -Raw  # Read full file content
    $clipboardContent += "$filename`n`n$content`n`n"
}

# Copy to clipboard
Set-Clipboard -Value $clipboardContent
Write-Output "Copied all .c files to clipboard."

# Copy js to clipboard
$jsContent = @"
// Remove all inline event handlers that block copy/paste
document.onkeydown = document.oncontextmenu = document.oncopy = document.onpaste = document.oncut = document.onselectstart = null;

// Stop scripts from blocking actions dynamically
window.addEventListener = (type, listener, options) => {
    if (!['keydown', 'contextmenu', 'copy', 'paste', 'cut', 'selectstart'].includes(type)) {
        EventTarget.prototype.addEventListener.call(window, type, listener, options);
    }
};

// Remove existing event listeners from the document and all elements
document.querySelectorAll('*').forEach(el => {
    el.oncontextmenu = el.oncopy = el.onpaste = el.oncut = el.onselectstart = null;
});
"@

Set-Clipboard -Value "$(Get-Clipboard -Raw)`n$jsContent"











Write-Output "done."

