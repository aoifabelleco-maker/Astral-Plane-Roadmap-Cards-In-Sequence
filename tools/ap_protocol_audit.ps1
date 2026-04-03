$ErrorActionPreference = 'Stop'
$required = @(
  'Docs/AP_PROTOCOL.md',
  'registry/ap_manifest.json',
  'registry/registry_manifest.json',
  'registry/registry_owners.json',
  'state/green_state/green_state.json'
)

$missing = @()
foreach ($path in $required) {
  if (-not (Test-Path -LiteralPath $path)) {
    $missing += $path
  }
}

if ($missing.Count -gt 0) {
  Write-Error "Protocol audit failed. Missing: $($missing -join ', ')"
}

Write-Host 'Protocol audit passed.'
