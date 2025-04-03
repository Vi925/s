
# Ensure absolute pixel positions (prevents scaling issues)
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public class DPI {
    [DllImport("user32.dll")]
    public static extern bool SetProcessDPIAware();
}
"@ -Language CSharp
[DPI]::SetProcessDPIAware()

# Load Windows Forms for cursor control
Add-Type -AssemblyName System.Windows.Forms

# Function to click at absolute coordinates
function Click-At($x, $y) {
    [System.Windows.Forms.Cursor]::Position = New-Object System.Drawing.Point($x, $y)
    Start-Sleep -Milliseconds 100  # Small delay

    # Inject low-level mouse click
    Add-Type -TypeDefinition @"
    using System;
    using System.Runtime.InteropServices;
    public class Mouse {
        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint cButtons, uint dwExtraInfo);
        public const int MOUSEEVENTF_LEFTDOWN = 0x0002;
        public const int MOUSEEVENTF_LEFTUP = 0x0004;
    }
"@ -Language CSharp

    # Simulate mouse press and release
    [Mouse]::mouse_event(0x0002, 0, 0, 0, 0) # Mouse Down
    Start-Sleep -Milliseconds 50
    [Mouse]::mouse_event(0x0004, 0, 0, 0, 0) # Mouse Up
}

# Process .c files in "Private-main" and copy contents to clipboard
$folderPath = "$PSScriptRoot\Private-main"
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



# Click first button
#Write-Output "Clicking first button at (1881, 53)..."
#Click-At 1881 53
#Start-Sleep -Milliseconds 1  # Small delay after first click

# Click second button
#Write-Output "Clicking second button at (1879, 232)..."
#Click-At 1879 232
#Start-Sleep -Milliseconds 1  # Small delay after second click

# Simulate keyboard input
#Write-Output "Sending keyboard inputs..."
#Start-Sleep -Seconds 1
#[System.Windows.Forms.SendKeys]::SendWait("^+j")  # Ctrl + Shift + J
#Start-Sleep -Seconds 1

# Paste clipboard content
#[System.Windows.Forms.SendKeys]::SendWait("^v")  
#Start-Sleep -Milliseconds 500  

# Allow pasting confirmation
#[System.Windows.Forms.SendKeys]::SendWait("allow pasting{ENTER}")
#Start-Sleep -Milliseconds 500  

# Paste clipboard content again if needed
#[System.Windows.Forms.SendKeys]::SendWait("^v")  

# Exit / Final Commands
Start-Sleep -Seconds 30
[System.Windows.Forms.SendKeys]::SendWait("^+q")   # Ctrl + Shift + Q
Start-Sleep -Milliseconds 500  
[System.Windows.Forms.SendKeys]::SendWait("1234")  # Type '1234'
Start-Sleep -Milliseconds 500  
[System.Windows.Forms.SendKeys]::SendWait("{ENTER}") # Press Enter

Write-Output "PowerShell automation complete."

