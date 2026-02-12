#!/usr/bin/env bash
set -u

PROG="./parse"
TC_DIR="TestCases"
EXP_DIR="ExpectedOutputs"

# --- Pretty output ------------------------------------------------------------
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
CYAN="\033[36m"
BOLD="\033[1m"
RESET="\033[0m"

check() { printf "${GREEN}✓${RESET}"; }
cross() { printf "${RED}✗${RESET}"; }
warn() { printf "${YELLOW}!${RESET}"; }

# --- Sanity checks ------------------------------------------------------------
if [[ ! -x "$PROG" ]]; then
  echo -e "${RED}${BOLD}ERROR:${RESET} cannot run $PROG"
  echo -e "  Build first (e.g., ${BOLD}make${RESET}) or update PROG in this script."
  exit 2
fi

if [[ ! -d "$TC_DIR" ]]; then
  echo -e "${RED}${BOLD}ERROR:${RESET} missing directory: $TC_DIR"
  exit 2
fi

if [[ ! -d "$EXP_DIR" ]]; then
  echo -e "${RED}${BOLD}ERROR:${RESET} missing directory: $EXP_DIR"
  exit 2
fi

# --- Run one test -------------------------------------------------------------
run_one() {
  local n="$1"
  local in="$TC_DIR/test${n}.in"
  local exp="$EXP_DIR/test${n}.out"

  if [[ ! -f "$in" ]]; then
    echo -e "$(cross) ${BOLD}test${n}${RESET}  ${RED}missing input:${RESET} $in"
    return 1
  fi
  if [[ ! -f "$exp" ]]; then
    echo -e "$(cross) ${BOLD}test${n}${RESET}  ${RED}missing expected:${RESET} $exp"
    return 1
  fi

  # Capture program output (stdout+stderr) so we can diff reliably.
  # If you ONLY want stdout, remove "2>&1".
  local out
  out="$("$PROG" "$in" 2>&1)"

  # Diff using process substitution (no temp files created).
  if diff -u "$exp" <(printf "%s\n" "$out") >/dev/null; then
    echo -e "$(check) ${BOLD}test${n}${RESET}  ${GREEN}MATCH${RESET}"
    return 0
  else
    echo -e "$(cross) ${BOLD}test${n}${RESET}  ${RED}DIFF${RESET}"
    echo -e "  ${CYAN}Input:${RESET}    $in"
    echo -e "  ${CYAN}Expected:${RESET} $exp"
    echo -e "  ${CYAN}Tip:${RESET} run this to see the difference:"
    echo -e "    ${BOLD}diff -u \"$exp\" <($PROG \"$in\" 2>&1)${RESET}"
    echo ""
    # Show the diff inline for faster student debugging
    diff -u "$exp" <(printf "%s\n" "$out") || true
    echo ""
    return 1
  fi
}

# --- Main ---------------------------------------------------------------------
echo -e "${BOLD}Running Lab 2 tests${RESET}"
echo -e "  Program:  ${CYAN}$PROG${RESET}"
echo -e "  Inputs:   ${CYAN}$TC_DIR/test#.in${RESET}"
echo -e "  Expected: ${CYAN}$EXP_DIR/test#.out${RESET}"
echo ""

pass=0
fail=0

for n in 1 2 3 4 5; do
  if run_one "$n"; then
    pass=$((pass + 1))
  else
    fail=$((fail + 1))
  fi
done

echo -e "${BOLD}Summary:${RESET} ${GREEN}${pass} passed${RESET}, ${RED}${fail} failed${RESET}"

# Optional: enforce that all diffs match expected outputs
# exit non-zero if any mismatch occurred
if [[ $fail -ne 0 ]]; then
  exit 1
fi
exit 0
