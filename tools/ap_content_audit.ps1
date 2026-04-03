$ErrorActionPreference = 'Stop'

$exe = './build/AstralPlane.exe'
if (-not (Test-Path -LiteralPath $exe)) {
  throw 'AstralPlane.exe not found. Run build first.'
}

& $exe -truthreport
if ($LASTEXITCODE -ne 0) {
  throw 'Truth report command failed (content audit failed loud).'
}

$truthPath = 'reports/truth/truth_latest.json'
if (-not (Test-Path -LiteralPath $truthPath)) {
  throw 'Truth report was not emitted.'
}

$truth = Get-Content -LiteralPath $truthPath -Raw | ConvertFrom-Json
if (-not $truth.content_audit_checksum) {
  throw 'Truth report missing content_audit_checksum.'
}
if (-not $truth.loaded_modules -or $truth.loaded_modules.Count -eq 0) {
  throw 'Truth report missing loaded_modules.'
}

Write-Host 'Content audit passed.'
