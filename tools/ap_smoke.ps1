$ErrorActionPreference = 'Stop'

$exe = './build/AstralPlane.exe'
if (-not (Test-Path -LiteralPath $exe)) {
  throw 'AstralPlane.exe not found. Run native build first.'
}

& $exe -smoke
if ($LASTEXITCODE -ne 0) {
  throw 'Smoke command failed.'
}

$smokePath = 'reports/smoke/smoke_latest.json'
if (-not (Test-Path -LiteralPath $smokePath)) {
  throw 'Smoke report was not emitted.'
}

$smoke = Get-Content -LiteralPath $smokePath -Raw | ConvertFrom-Json
if ($smoke.status -ne 'pass') {
  throw 'Smoke report status is not pass.'
}
if ($smoke.note -ne 'move + mine + carry + fight + portal + assimilation + build/storage/heat + save/reincarnation + ecology valid') {
  throw 'Smoke report note mismatch for stage-7 baseline.'
}

& $exe -truthreport
if ($LASTEXITCODE -ne 0) {
  throw 'Truth report command failed during smoke verification.'
}

$truth = Get-Content -LiteralPath 'reports/truth/truth_latest.json' -Raw | ConvertFrom-Json
if (-not $truth.building_storage_heat_summary.room_closed -or -not $truth.building_storage_heat_summary.storage_query_usable -or -not $truth.building_storage_heat_summary.ice_melted_to_water) {
  throw 'Building/storage/heat proof missing in truth report.'
}



if (-not $truth.ecology_event_summary) {
  throw 'Ecology event summary missing in truth report.'
}
if (-not $truth.ecology_event_summary.comet_event_occurred -or -not $truth.ecology_event_summary.void_slime_consumed_matter -or -not $truth.ecology_event_summary.plant_loop_seed_to_harvest_worked) {
  throw 'Ecology event proof missing in truth report.'
}
if (-not $truth.ui_anchor_summary) {
  throw 'UI anchor summary missing in truth report.'
}
if (-not $truth.ui_anchor_summary.visible_shell_shown -or -not $truth.ui_anchor_summary.panel_toggles_work) {
  throw 'UI anchor baseline proof missing in truth report.'
}
if (-not $truth.save_reincarnation_summary) {
  throw 'Save/reincarnation summary missing in truth report.'
}
if (-not $truth.save_reincarnation_summary.no_drift -or -not $truth.save_reincarnation_summary.reincarnation_index) {
  throw 'Save/reincarnation proof missing in truth report.'
}

Write-Host 'Smoke audit passed.'
