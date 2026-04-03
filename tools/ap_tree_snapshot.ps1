$ErrorActionPreference = 'Stop'
$timestamp = (Get-Date).ToUniversalTime().ToString('yyyy-MM-ddTHH:mm:ssZ')
$files = Get-ChildItem -Recurse -File | ForEach-Object { $_.FullName.Replace((Get-Location).Path + [IO.Path]::DirectorySeparatorChar, '') }
$output = [PSCustomObject]@{
  generated_at_utc = $timestamp
  file_count = $files.Count
  files = $files
}
$output | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath 'state/tree_snapshot/tree_snapshot_latest.json'
Write-Host 'Tree snapshot generated: state/tree_snapshot/tree_snapshot_latest.json'
