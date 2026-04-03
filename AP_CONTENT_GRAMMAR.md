# AP Content Grammar v1 (Bootstrap)

## File model
- Content is loaded from module files listed in `content/ap_module_load_order.txt`.
- Each module file is tokenized as line-based `key=value` pairs.
- Records are enclosed by `BEGIN` and `END`.
- `#` starts a comment.

## Required record fields
- `kind`: one of `material`, `terrain`, `stat`, `core`, `plane`, `graphics_map`, `lua_placeholder`.
- `id`: globally unique content identifier.

## Optional fields
- `name`: display label.
- `material_id`: required on `terrain`.
- `terrain_id`, `core_id`, `stat_id`: required on `plane`.
- `logical_id`, `asset`: required on `graphics_map`.
- `script`: optional for `lua_placeholder` (placeholder integration only).

## Validation laws
1. Duplicate `id` values fail loud.
2. Missing required fields fail loud.
3. Cross-reference IDs must resolve.
4. Graphics mappings must resolve logical IDs to existing content IDs.

## Bootstrap scope
- Init + vanilla content only.
- Placeholder Lua integration only.

## Matter denomination law references
- `measure` is the smallest economic unit.
- `microblock` equals one `measure`.
- `block` is a structural denomination of 27 measures.
- Equal measure counts do not imply equal lawful use.
- Forms `walkable_floor`, `structural_block`, `loose_matter`, and `contained_matter` are distinct in reporting and audits.
