# AP Save Schema (M-011 bootstrap)

Schema version: `1.0.0`

Purpose: persist world consequence across sessions and character death.

## Required fields
- `schema_version` (string)
- `world_seed` (int)
- `home_plane.owned_cells` (int)
- `home_plane.growth_capacity` (int)
- `ironman.enabled` (bool)
- `ironman.player_dead` (bool)
- `ironman.death_count` (int)
- `reincarnation.index` (int)
- `reincarnation.memory_fragments` (string[])
- `reincarnation.ancestral_land` (string placeholder state)
- `portal_coordinates[].plane_id` (string)
- `portal_coordinates[].x` / `y` (int)

## Bootstrap migration policy
- Any schema version bump must write `reports/audit/save_schema_change_latest.json`.
- Bootstrap audit treats missing schema-change report as failure.

## Drift law
- Serialize -> load -> serialize must be byte-identical for canonical saves.
- Death may increment `death_count` and `reincarnation.index` but must not rewind world-owned area.
