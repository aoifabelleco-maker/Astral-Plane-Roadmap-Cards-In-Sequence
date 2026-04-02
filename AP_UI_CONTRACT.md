# AP UI Contract

**Contract ID:** M-014 UI Live Shell Contract v1  
**Priority:** P1  
**Roadmap Band:** Stage 10 recut — shell contract  
**Depends on:** M-013  
**Labels:** stage-10, ui-contract, shell, docs, p1

## 1) Purpose
Lock the runtime UI shell law **before** broader runtime UI implementation. This contract is the judging baseline for future Stage 10 UI patches.

## 2) Stage Scope (M-014)
This milestone is **documentation-first** and defines immutable shell behavior for:
- always-visible shell truths,
- action belts by mode,
- radar/marker taxonomy,
- key spine (`C/I/P/B/R/M/Esc`),
- build quick row vs build drawer,
- shell differences between explore/build, combat, and expedition-pressure,
- tooltip law,
- button/hotkey parity,
- visuals-later rule.

Out of scope:
- visual polish,
- large style/animation overhauls,
- non-shell gameplay tuning.

---

## 3) Always-Visible Shell Truths
The following shell elements are always present at runtime unless an explicit blocking state is entered (e.g. loading screen, hard modal confirmation):

1. **Primary mode chip** (current mode: Explore, Build, Combat, Expedition Pressure).
2. **Resource strip** (minimum readout for critical economy + power/pressure context).
3. **Compass/radar anchor** (minimap/radar locus + marker legend affordance).
4. **Key spine hint** (`C/I/P/B/R/M/Esc`) shown as compact hints or discoverable via tooltip.
5. **Notification lane** (high-priority state changes and action confirmations).

**Rule:** If one truth must collapse at narrow aspect ratios, collapse to icon/density mode but never to absent state.

---

## 4) Action Belts by Mode
Action belts are mode-bound and must not blend inputs from another mode.

### 4.1 Explore / Build Belt
- Belt emphasizes navigation, interaction, and build entry.
- Build entry is always surfaced via **`B`** and build affordance button.
- Context-sensitive interactions appear in left-to-right priority order.

### 4.2 Combat Belt
- Belt replaces build-specific actions with combat-safe actions.
- Build drawer is inaccessible while hard combat lock is active.
- Critical defensive/offensive actions are pinned and cannot be displaced by non-critical prompts.

### 4.3 Expedition-Pressure Belt
- Belt prioritizes pressure-management and extraction/survival actions.
- Any action that increases risk must carry a warning treatment and explicit tooltip warning text.

---

## 5) Radar + Marker Taxonomy
Marker classes are fixed for Stage 10 contract:

- **Objective Marker**: main/primary progress target.
- **Secondary Marker**: optional points of interest.
- **Threat Marker**: enemy/danger source.
- **Resource Marker**: gatherable/capture point.
- **Squad Marker**: friendly/ally location.
- **Ping Marker**: transient user/system ping.

### Marker Law
- Every visible marker must map to exactly one taxonomy class.
- Color/icon can evolve later, taxonomy cannot silently drift.
- Tooltip text must name class and contextual meaning.

---

## 6) Key Spine (Global Contract)
Global shell spine hotkeys:

- `C` = Character
- `I` = Inventory
- `P` = Progress / Journal
- `B` = Build
- `R` = Radar focus/expand
- `M` = Map
- `Esc` = Back/Pause/Close topmost shell layer

### Key Spine Law
1. All keys must be bindable and visible in shell help.
2. `Esc` always resolves to close/top-layer back before opening pause, except in blocking confirmation dialogs.
3. A key action exposed in UI must have button/hotkey parity (see §9).

---

## 7) Build Quick Row vs Build Drawer
Two-tier build interaction model is mandatory:

1. **Build Quick Row**
   - Always low-latency, in-shell, one-step actions.
   - Contains most recent/favorited/high-frequency build items.
   - Must remain operable without opening full drawer.

2. **Build Drawer**
   - Full catalog, filters, and deeper build configuration.
   - Explicitly entered/exited state.
   - On close, returns focus to prior shell state without mode confusion.

**Rule:** Quick row must not become a hidden subset only reachable through the drawer.

---

## 8) Shell State Matrix

| Shell State | Always-visible truths | Belt profile | Build quick row | Build drawer |
|---|---|---|---|---|
| Explore/Build | Full | Explore/Build | Enabled | Enabled |
| Combat | Full (compressed allowed) | Combat | Disabled or read-only by lock policy | Disabled during hard combat lock |
| Expedition Pressure | Full (pressure cues elevated) | Pressure | Conditional | Conditional (policy-driven) |

**Law:** If a state blocks an element, reason must be explicit in tooltip/status text.

---

## 9) Tooltip Law
Tooltips are required for:
- marker semantics,
- disabled actions,
- risk-increasing actions,
- key spine discoverability.

Tooltip standards:
1. First line: action/object name.
2. Second line: concise effect.
3. Third line (optional): warning/restriction reason.
4. Hotkey hint appears whenever a mapped hotkey exists.

No tooltip may contradict key map or button label.

---

## 10) Button/Hotkey Parity Law
For any shell action that is clickable and hotkey-addressable:
- button label and hotkey mapping must both be present in UI model,
- disabled state reasoning must match for both entry paths,
- remapped keys update visible hints without requiring restart.

Parity failures are contract violations.

---

## 11) Visuals-Later Rule
M-014 locks interaction contract and shell semantics, **not final visual style**.
Allowed after M-014 without contract rewrite:
- spacing, typography, icon refresh, motion polish, skin/theme.

Not allowed without contract amendment:
- remapping shell truths,
- removing key spine behavior,
- changing belt/state responsibilities,
- breaking quick row vs drawer model.

---

## 12) Validation Hooks (for future patches)
Future Stage 10 runtime patches must include evidence that:
1. Shell truths remain present per state matrix.
2. Key spine mapping is intact.
3. Quick row and drawer behavior remains distinct.
4. Tooltips obey tooltip law.
5. Button/hotkey parity is maintained.

Reference tests and expectations:
- `docs/ui/panel_hotkey_map.md`
- `docs/ui/ui_smoke_expectations.md`

