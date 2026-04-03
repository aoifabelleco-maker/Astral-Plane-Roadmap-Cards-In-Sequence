# AP Protocol v1 (Bootstrap Truth Scaffold)

## Governance law
All development must be based on the true live repository state.
No stage skipping is allowed.
All user requirements are mandatory.

## Stage 0 bootstrap obligations
1. Protocol exists and is auditable.
2. Registry ownership exists and is auditable.
3. Green-state/restore path exists and is auditable.
4. Build/smoke/truth starter tooling exists and can emit reports.

## Required command sequence
1. `pwsh ./tools/ap_protocol_audit.ps1`
2. `pwsh ./tools/ap_registry_audit.ps1`
3. `pwsh ./tools/ap_build.ps1`
4. `pwsh ./tools/ap_smoke.ps1`
5. `pwsh ./tools/ap_truth_report.ps1`

## Truth artifacts
- Protocol: `Docs/AP_PROTOCOL.md`
- Registries: `registry/*.json`
- Green state: `state/green_state/green_state.json`
- Restore points: `state/restore_points/*.json`
- Reports: `reports/**`

## Exit criteria
- Registry audit passes.
- Smoke passes.
- Build report exists.
- Truth report exists.
- Green state points to a fresh restore point.
- Manifest is registered.
