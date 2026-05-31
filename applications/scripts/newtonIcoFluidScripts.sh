#!/bin/bash

# On macOS, ensure OpenFOAM libraries remain discoverable for child processes.
case "$(uname -s)" in
Darwin)
    export DYLD_LIBRARY_PATH="${FOAM_LIBBIN}:${FOAM_USER_LIBBIN}${DYLD_LIBRARY_PATH:+:${DYLD_LIBRARY_PATH}}"
    ;;
esac

function newtonIcoFluid::err()
{
    echo; echo "ERROR: see error.txt"
    echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $*" >&2
    echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $*" > error.txt
    exit 1
}

function newtonIcoFluid::convertCaseFormat()
{
    if [[ $# -ne 1 ]]
    then
        newtonIcoFluid::err "convertCaseFormat: incorrect number of parameters"
    fi

    local caseDir=$1

    if [[ $WM_PROJECT = "foam" ]]
    then
        return 0
    fi

    if [[ -f "${caseDir}/system/changeDictionaryDict.openfoam" ]]
    then
        \cp -f "${caseDir}/system/changeDictionaryDict.openfoam" \
            "${caseDir}/system/changeDictionaryDict"
    fi
}

function newtonIcoFluid::caseDoesNotRunWithFoamExtend()
{
    if [[ $WM_PROJECT == "foam" ]]
    then
        echo; echo "This case currently does not run with foam-extend"; echo
        exit 0
    fi
}

function newtonIcoFluid::caseDoesNotRunWithOpenFOAMOrg()
{
    if [[ $WM_PROJECT == "OpenFOAM" ]]
    then
        if [[ $WM_PROJECT_VERSION != v* ]]
        then
            echo; echo "This case currently does not run with OpenFOAM.org"; echo
            exit 0
        fi
    fi
}

function newtonIcoFluid::regressionCaseSkipped()
{
    local logFile=$1

    if [[ ! -f "${logFile}" ]]
    then
        return 1
    fi

    if grep -Eq "This case currently does not run with foam-extend|This case currently does not run with OpenFOAM.org|Skipping this case as PETSc is not installed" "${logFile}"
    then
        return 0
    fi

    return 1
}

function newtonIcoFluid::runApplication()
{
    runApplication "$@"
}

#------------------------------------------------------------------------------
