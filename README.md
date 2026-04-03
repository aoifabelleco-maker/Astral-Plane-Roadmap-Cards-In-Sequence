# Astral-Plane-Roadmap-Cards-In-Sequence

Governed milestone scaffolding for Astral Plane.

## Native executable bootstrap (M-001)

### Build
- Linux/macOS shell: `./scripts/build_native.sh`
- PowerShell: `pwsh ./tools/ap_build_native.ps1`

### Run
- Launch only: `./build/AstralPlane.exe`
- Truth report: `./build/AstralPlane.exe -truthreport`
- Smoke report: `./build/AstralPlane.exe -smoke`
- UI smoke report: `./build/AstralPlane.exe -uismoke`
- Worldgen probe: `./build/AstralPlane.exe -genworld`
- Full gate chain + green restore capture: `./build/AstralPlane.exe -fullgate`
- Save/reincarnation probe: `./build/AstralPlane.exe -saveprobe`

## Content grammar bootstrap (M-002)

- Grammar doc: `AP_CONTENT_GRAMMAR.md`
- Module order: `content/ap_module_load_order.txt`
- PowerShell content audit: `pwsh ./tools/ap_content_audit.ps1`
- Truth report includes `loaded_modules` and `content_audit_checksum` from content loading.

## Start plane layout bootstrap (M-003)

- Layout data: `data/plane_layout/home_plane_layout.json`
- World generator guarantees a 3x3 home plane on layer 0 with a center core marker.
- Truth report now includes `world_summary` with layer and block counts.
- Audit commands:
  - `pwsh ./tools/ap_truth_report.ps1`
  - `pwsh ./tools/ap_smoke.ps1`

## Terrain block model bootstrap (M-004)

- Terrain law docs:
  - `terrain_cells.txt`
  - `terrain_blocks.txt`
  - `terrain_microblocks.txt`
  - `terrain_verticality.txt`
  - `terrain_occupation_rules.txt`
- Start terrain model now includes full blocks, loose matter, assimilated matter, 27-unit decomposition rules, occupied/free logic, and baseline temperature placeholders.
- Truth/smoke audits remain:
  - `pwsh ./tools/ap_truth_report.ps1`
  - `pwsh ./tools/ap_smoke.ps1`

## M-004 support: block measure and form law

- Denomination law: `1 block = 27 measures`.
- Reporting law distinguishes place truth (cells/layers) from quantity truth (measures) and form truth (structural/loose/contained).
- Material terms are frozen in terrain law text surfaces and reflected in `reports/truth/truth_latest.json`.

## Body stats and action law bootstrap (M-005)

- Law text surfaces:
  - `body_human_mortal.txt`
  - `stats_primary.txt`
  - `stats_secondary.txt`
  - `stats_formulas.txt`
- Truth report now includes `body_law_summary` and `character_panel` blocks proving STR carry impact, PER sight impact, stamina drain, overload visibility, and primary/derived stat display.

## First harsh verbs bootstrap (M-006)

- Placeholder surfaces:
  - `data/items/item_tools.txt`
  - `data/items/simple_weapon_placeholder.txt`
  - `data/creatures/hostile_placeholder.txt`
- Truth report now includes `harsh_verb_summary` proving movement, mining, carry limit enforcement, pickup/drop/transfer, melee fight, and death/corpse handling scaffold behavior.
- `ap_smoke.ps1` validates move/mine/carry/fight evidence from smoke + truth reports.

## M-006 support: loose matter stack split/merge truth

- Law file: `loose_matter_stack_law.txt`.
- Harsh verb scenario now includes mined loose-stack creation, split inheritance, legal merge with strongest warning union, and blocked merge with readable reason.
- Truth report surfaces these via `harsh_verb_summary` (`merge_blocked_reason`, `merged_warning_chip`, `inspect_text`).

## Portal rift bootstrap (M-007)

- Law text surfaces:
  - `portal_rifts.txt`
  - `portal_timers.txt`
  - `portal_extension_costs.txt`
  - `portal_coordinate_tools.txt`
- Smoke/genworld/truth now include portal-rift proofs for enter, return, visible timer, extension cost, coordinate recording, and stranded-timeout hard failure.

## Assimilation home growth bootstrap (M-008)

- Law text surfaces:
  - `core_assimilation.txt`
  - `plane_surface_growth.txt`
  - `core_merge_ancestral.txt`
- Support law text:
  - `assimilated_reserved_feed_state_law.txt`
- Truth report now includes `owned_plane_summary` and `assimilation_summary` with reserved/feed/assimilated state counts, core capture, and growth metrics.

## Build, storage, and heat bootstrap (M-009)

- Law text surfaces:
  - `building_walls_doors_roofs.txt`
  - `building_storage.txt`
  - `building_beds.txt`
  - `building_heat_sources.txt`
- Support law text:
  - `material_storage_container_transport_truth.txt`
- Truth report now includes `building_storage_heat_summary` with enclosure, storage state/query, and local heat/ice-melt proof fields.
- New UI obligation script: `pwsh ./tools/ap_ui_smoke.ps1`.


## Save/load + death continuity bootstrap (M-011)

- Save schema law: `AP_SAVE_SCHEMA.md`
- Legacy surfaces:
  - `legacy_death_rules.txt`
  - `legacy_reincarnation.txt`
  - `legacy_memory_fragments.txt`
- Truth report now includes `save_reincarnation_summary` proving save/write-load drift checks, world seed persistence, death continuity, reincarnation index carryover, memory fragment count, and schema-change reporting.
- New audit command: `pwsh ./tools/ap_save_schema_audit.ps1`


## UI/input/camera floor bootstrap (M-012)

- Launching `./build/AstralPlane.exe` now presents a visible native shell (main menu floor).
- `Enter/New Game` runtime entry is represented in the UI smoke scenario state machine.
- Runtime controls covered in smoke: `WASD` move, `Q/E` four-way camera rotation, left-click inspect, right-click interact, `Esc` return, and first panel toggles.
- Validation commands:
  - `./build/AstralPlane.exe -uismoke`
  - `pwsh ./tools/ap_ui_smoke.ps1`


## UI rebase anchor freeze (M-013)

- Frozen contract seed: `Docs/AP_UI_CONTRACT_SEED.md` (`ui-anchor-1.0.0`).
- UI smoke now writes a trusted restore anchor: `state/restore_points/restore_point_m013_ui_anchor.json`.
- Truth report now includes `ui_anchor_summary` so truth/smoke chain guards the Stage-10 UI floor while later UI cards branch.
