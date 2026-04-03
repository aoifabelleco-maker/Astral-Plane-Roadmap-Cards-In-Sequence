$ErrorActionPreference = 'Stop'
$green = Get-Content -LiteralPath 'state/green_state/green_state.json' -Raw | ConvertFrom-Json
$rp = $green.restore_point
if (-not (Test-Path -LiteralPath $rp)) {
  throw "Restore failed: restore point not found: $rp"
}
Write-Host "Restore scaffold ready. Last green restore point: $rp"
