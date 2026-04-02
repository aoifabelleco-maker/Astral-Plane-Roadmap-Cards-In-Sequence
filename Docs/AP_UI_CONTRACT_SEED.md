# AP UI Contract Seed (M-013 rebase anchor)

Contract version: `ui-anchor-1.0.0`

This document freezes the first trusted Stage-10 UI baseline so later UI cards can branch without reopening Stage 0-9 law.

## Frozen baseline
- Launch shell surface: visible native main menu shell.
- Runtime entry: `Enter/New Game` transitions from menu to runtime state.
- Input floor:
  - `WASD` movement routing
  - `Q/E` four-way camera rotation
  - left-click inspect
  - right-click interact
  - `Esc` return to menu
- First panel toggles: inventory/map placeholder toggles.

## Anchor law
- UI smoke must pass against this contract.
- Truth/smoke chain must remain green while this contract is frozen.
- Stage-10 descendants may extend visuals, drawers, radar, action belt, and mode shells without redefining this floor.
