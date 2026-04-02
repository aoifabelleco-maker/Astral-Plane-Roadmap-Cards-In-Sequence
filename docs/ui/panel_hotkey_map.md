# Panel + Hotkey Map (M-014 Contract Baseline)

This map is normative for Stage 10 shell contract checks.

## Global Spine Map

| Key | Panel/Action | Scope | Notes |
|---|---|---|---|
| `C` | Character panel | Global shell | Toggle/open depending on shell depth |
| `I` | Inventory panel | Global shell | Must expose same disable reason as button |
| `P` | Progress/Journal panel | Global shell | Mission/log progression surface |
| `B` | Build mode entry / build panel | Explore/Build preferred | In combat may be blocked with reason |
| `R` | Radar focus/expand | Global shell | Can expand or focus radar context |
| `M` | World/sector map | Global shell | Returns to prior focus when closed |
| `Esc` | Back / close top shell layer / pause fallback | Global shell | Close-first behavior before pause fallback |

## Mode Notes

### Explore/Build
- `B` must open build affordance.
- Quick row can be used with or without drawer open.

### Combat
- `B` can be blocked by combat lock policy.
- `Esc` closes top overlays before any pause action.

### Expedition Pressure
- High-risk actions must include warning tooltip copy.
- `R` and `M` remain available unless explicit pressure event lock is active.

## Parity Checklist

For each mapped action above:
1. A visible button or menu affordance exists.
2. The hotkey hint is visible in tooltip/help surface.
3. Disabled reason text matches between button and key path.
4. Remapping updates shown hint text.

