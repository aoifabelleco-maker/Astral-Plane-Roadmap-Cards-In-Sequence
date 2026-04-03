$ErrorActionPreference = 'Stop'

$exe = './build/AstralPlane.exe'
if (-not (Test-Path -LiteralPath $exe)) {
  throw 'AstralPlane.exe not found. Run native build first.'
}

& $exe -truthreport
if ($LASTEXITCODE -ne 0) {
  throw 'Truth report command failed.'
}

$path = 'reports/truth/truth_latest.json'
if (-not (Test-Path -LiteralPath $path)) {
  throw 'Truth report file not found.'
}

$truth = Get-Content -LiteralPath $path -Raw | ConvertFrom-Json
if ($truth.status -ne 'pass') {
  throw 'Truth report status is not pass.'
}
if (-not $truth.owned_plane_summary -or -not $truth.assimilation_summary) {
  throw 'Assimilation summaries missing.'
}
if (-not $truth.building_storage_heat_summary) {
  throw 'Building storage heat summary missing.'
}
if (-not $truth.building_storage_heat_summary.build_panel_usable) {
  throw 'Build panel usability proof missing.'
}
if (-not $truth.building_storage_heat_summary.storage_query_usable) {
  throw 'Storage query proof missing.'
}
if (-not $truth.building_storage_heat_summary.ice_melted_to_water) {
  throw 'Heat/melt proof missing.'
}


if (-not $truth.ecology_event_summary) {
  throw 'Ecology event summary missing.'
}
if (-not $truth.ecology_event_summary.comet_event_occurred -or -not $truth.ecology_event_summary.meteor_event_occurred -or -not $truth.ecology_event_summary.seed_drop_occurred) {
  throw 'Meteor/comet seed event proof missing.'
}
if (-not $truth.ecology_event_summary.void_slime_consumed_matter -or -not $truth.ecology_event_summary.same_rank_slime_merged) {
  throw 'Void slime behavior proof missing.'
}
if (-not $truth.ecology_event_summary.slime_defeat_recovered_matter -or -not $truth.ecology_event_summary.plant_loop_seed_to_harvest_worked) {
  throw 'Matter recovery or plant loop proof missing.'
}
if (-not $truth.ui_anchor_summary) {
  throw 'UI anchor summary missing.'
}
if (-not $truth.ui_anchor_summary.visible_shell_shown -or -not $truth.ui_anchor_summary.wasd_movement_works -or -not $truth.ui_anchor_summary.camera_four_way_rotation_works) {
  throw 'UI anchor baseline proof missing.'
}
if (-not $truth.save_reincarnation_summary) {
  throw 'Save/reincarnation summary missing.'
}
if (-not $truth.save_reincarnation_summary.no_drift) {
  throw 'Save drift check missing.'
}
if (-not $truth.save_reincarnation_summary.death_did_not_rewind_world) {
  throw 'Death continuity proof missing.'
}
if (-not $truth.save_reincarnation_summary.schema_change_reported) {
  throw 'Schema change reporting proof missing.'
}

Write-Host 'Truth report audit passed.'
