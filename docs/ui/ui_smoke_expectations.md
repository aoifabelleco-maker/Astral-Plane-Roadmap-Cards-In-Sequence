# UI Smoke Expectations (M-014)

These expectations define pass/fail criteria for shell-level smoke checks tied to:
- `AstralPlane.exe -uismoke`
- `ap_ui_smoke.ps1`

## Required Assertions

### 1) Shell Truth Presence
- In Explore/Build, Combat, and Expedition Pressure shells, core truths are present:
  - mode chip,
  - resource strip,
  - radar anchor,
  - key spine discoverability,
  - notification lane.

### 2) Key Spine Integrity
- `C/I/P/B/R/M/Esc` bindings resolve to the mapped panel/action.
- `Esc` close-first behavior is honored before pause fallback.

### 3) Build Partitioning
- Quick row can execute at least one build action without opening drawer.
- Drawer exposes full build catalog and returns focus cleanly on close.

### 4) Mode Belt Correctness
- Combat belt excludes build-only actions while lock is active.
- Expedition-pressure belt surfaces warning treatment for risk-increasing actions.

### 5) Marker Taxonomy + Tooltips
- Every sampled marker is typed as objective/secondary/threat/resource/squad/ping.
- Tooltip content includes action/object name and effect; warning/restriction line appears when applicable.

### 6) Button/Hotkey Parity
- At least one sampled action per key spine entry validates parity:
  - same availability state,
  - same disabled reason,
  - visible hotkey hint.

## Suggested Smoke Output Sections

1. Environment + build hash
2. Shell state matrix checks
3. Key spine checks
4. Build quick row vs drawer checks
5. Tooltip + marker checks
6. Parity checks
7. Contract verdict (PASS/FAIL)

## Contract Verdict Rule
- PASS only if all six required assertion groups pass.
- Any mismatch against `AP_UI_CONTRACT.md` is a FAIL and must name violated section.

