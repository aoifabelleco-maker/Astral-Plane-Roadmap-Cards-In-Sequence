$ErrorActionPreference = 'Stop'

$exe = './build/AstralPlane.exe'
if (-not (Test-Path -LiteralPath $exe)) {
  throw 'AstralPlane.exe not found. Run native build first.'
}

& $exe -uismoke
if ($LASTEXITCODE -ne 0) {
  throw 'UI smoke command failed.'
}

$path = 'reports/smoke/ui_smoke_latest.json'
if (-not (Test-Path -LiteralPath $path)) {
  throw 'UI smoke report was not emitted.'
}

$ui = Get-Content -LiteralPath $path -Raw | ConvertFrom-Json
if ($ui.status -ne 'pass') {
  throw 'UI smoke report status is not pass.'
}
if (-not $ui.visible_shell_shown) {
  throw 'Visible shell proof missing.'
}
if (-not $ui.enter_new_game_works) {
  throw 'Enter/New Game proof missing.'
}
if (-not $ui.wasd_movement_works) {
  throw 'WASD movement proof missing.'
}
if (-not $ui.camera_four_way_rotation_works) {
  throw 'Camera Q/E four-way proof missing.'
}
if (-not $ui.left_click_inspect_works -or -not $ui.right_click_interact_works) {
  throw 'Mouse inspect/interact proof missing.'
}
if (-not $ui.esc_return_works) {
  throw 'Esc return proof missing.'
}
if (-not $ui.panel_toggles_work) {
  throw 'Panel toggles proof missing.'
}
if (-not $ui.ui_anchor_written) {
  throw 'UI anchor write proof missing.'
}

if ($ui.ui_contract_version -ne 'ui-shell-contract-1.0.0') {
  throw 'UI contract version mismatch.'
}
if (-not $ui.always_visible_truths_declared) {
  throw 'Always-visible truths declaration missing.'
}
if (-not $ui.mode_action_belts_declared) {
  throw 'Mode action belts declaration missing.'
}
if (-not $ui.key_spine_declared) {
  throw 'Key spine declaration missing.'
}

if (-not $ui.action_belt_visible) {
  throw 'Action belt visibility proof missing.'
}
if (-not $ui.current_verb_readable) {
  throw 'Current verb readability proof missing.'
}
if (-not $ui.hover_truth_visible) {
  throw 'Hover truth visibility proof missing.'
}
if (-not $ui.build_quick_row_visible) {
  throw 'Build quick row visibility proof missing.'
}
if (-not $ui.build_access_key_button_parity) {
  throw 'Build key/button parity proof missing.'
}

if (-not $ui.radar_visible) {
  throw 'Radar/minimap visibility proof missing.'
}
if (-not $ui.marker_taxonomy_present) {
  throw 'Marker taxonomy proof missing.'
}
if (-not $ui.marker_distances_readable) {
  throw 'Marker distance readout proof missing.'
}
if (-not $ui.expedition_overlay_readable) {
  throw 'Expedition overlay readability proof missing.'
}
if (-not $ui.marker_camera_behavior_four_way) {
  throw 'Four-way camera marker behavior proof missing.'
}
if (-not (Test-Path -LiteralPath 'state/restore_points/restore_point_m013_ui_anchor.json')) {
  throw 'M-013 UI restore anchor file missing.'
}

Write-Host 'UI smoke audit passed.'
