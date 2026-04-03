$ErrorActionPreference = 'Stop'

$exe = './build/AstralPlane.exe'
if (-not (Test-Path -LiteralPath $exe)) {
  throw 'AstralPlane.exe not found. Run native build first.'
}

& $exe -truthreport
if ($LASTEXITCODE -ne 0) {
  throw 'Truth report command failed.'
}

$truthPath = 'reports/truth/truth_latest.json'
if (-not (Test-Path -LiteralPath $truthPath)) {
  throw 'Truth report missing.'
}

$truth = Get-Content -LiteralPath $truthPath -Raw | ConvertFrom-Json
if (-not $truth.save_reincarnation_summary) {
  throw 'Save/reincarnation summary missing.'
}
if (-not $truth.save_reincarnation_summary.no_drift) {
  throw 'Save round-trip drift detected.'
}
if (-not $truth.save_reincarnation_summary.death_did_not_rewind_world) {
  throw 'Death rewind law violated.'
}
if (-not $truth.save_reincarnation_summary.schema_change_reported) {
  throw 'Schema change reporting missing.'
}

$schemaPath = 'reports/audit/save_schema_change_latest.json'
if (-not (Test-Path -LiteralPath $schemaPath)) {
  throw 'Schema change report file missing.'
}

$schema = Get-Content -LiteralPath $schemaPath -Raw | ConvertFrom-Json
if ($schema.status -ne 'pass' -or $schema.schema_version -ne '1.0.0') {
  throw 'Schema change report invalid.'
}

Write-Host 'Save schema audit passed.'
