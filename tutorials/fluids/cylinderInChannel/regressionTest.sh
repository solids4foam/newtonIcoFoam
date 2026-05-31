#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG_FILE="${SCRIPT_DIR}/log.regressionTest"

(
    cd "${SCRIPT_DIR}"
    ./Allclean
    ./Allrun
) > "${LOG_FILE}" 2>&1

if grep -q "ERROR" "${SCRIPT_DIR}/log.newtonIcoFoam"
then
    echo "FAIL: newtonIcoFoam reported an error"
    exit 1
fi

echo "PASS: cylinderInChannel completed"
