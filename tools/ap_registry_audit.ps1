$ErrorActionPreference = 'Stop'

function Read-Json([string]$Path) {
  if (-not (Test-Path -LiteralPath $Path)) {
    throw "Missing required JSON file: $Path"
  }
  return Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json
}

$manifestRegistry = Read-Json 'registry/registry_manifest.json'
$ownersRegistry = Read-Json 'registry/registry_owners.json'
$manifest = Read-Json 'registry/ap_manifest.json'

$manifestEntry = $manifestRegistry.entries | Where-Object { $_.path -eq 'registry/ap_manifest.json' }
if (-not $manifestEntry) {
  throw 'Manifest is not registered in registry/registry_manifest.json'
}

if (-not $ownersRegistry.entries) {
  throw 'Owners registry has no entries.'
}

if (-not $manifest.manifest_id) {
  throw 'Manifest missing manifest_id.'
}

Write-Host 'Registry audit passed.'
