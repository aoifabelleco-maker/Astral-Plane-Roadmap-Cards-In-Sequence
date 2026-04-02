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

Write-Host 'UI smoke audit passed.'
