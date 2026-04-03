# AP UI Contract (M-014 live shell contract)

Contract version: `ui-shell-contract-1.0.0`
Stage scope: Stage 10 recut

This contract is documentation-first and controls all near-term UI runtime implementation.

## 1) Always-visible shell truths
These truths must remain discoverable without debug knowledge:
- Top-left truth block: body + growth
- Bottom-left truth block: life anchor
- Bottom-right truth block: spirit anchor
- Always visible fields: level, cultivation stage, cultivation progress, stamina, load, burden, current mode

## 2) Action belts by mode
- Explore/Build belt
- Combat belt
- Expedition-pressure belt

Belts may swap by mode but must preserve explicit button/hotkey parity.

## 3) Radar / marker taxonomy
- Radar shell reserved lane
- Marker categories: objective, threat, extraction, home-anchor, temporal-risk
- Taxonomy must be mode-agnostic and readable from tooltips.

## 4) Key spine (frozen)
Core shell spine keys:
- `C` character
- `I` inventory
- `P` powers/progression
- `B` build
- `R` radar
- `M` map/memory
- `Esc` shell back/close

## 5) Build quick row vs drawer
- Build quick row is the high-frequency lane.
- Build drawer hosts deeper/less frequent build actions.
- Quick row entries must map to explicit drawer category and tooltip descriptor.

## 6) Tooltip law
- Tooltips must expose action intent, cost, and hotkey when available.
- Tooltip naming must match panel/button text to avoid dual terminology.

## 7) Button/hotkey parity law
Every visible button action with a hotkey must display that hotkey, and every documented hotkey must resolve to a visible button or explicit shell command.

## 8) Visuals-later rule
Layout/readability law is binding now; visual polish pass is deferred and cannot block contract alignment.
