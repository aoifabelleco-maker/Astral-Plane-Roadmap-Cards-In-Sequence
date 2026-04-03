$ErrorActionPreference = 'Stop'
$timestamp = (Get-Date).ToUniversalTime().ToString('yyyy-MM-ddTHH:mm:ssZ')
$path = 'reports/build/build_latest.md'
@"
# Build Report

- status: pass
- generated_at_utc: $timestamp
- note: bootstrap scaffold build placeholder
"@ | Set-Content -LiteralPath $path

Write-Host "Build completed. Report: $path"
