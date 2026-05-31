# newtonIcoFluid

`newtonIcoFluid` is a standalone OpenFOAM solver extracted from solids4foam.
It provides `newtonIcoFoam`, an incompressible Newtonian laminar fluid solver
using the `newtonIcoFluid` PETSc SNES implementation.

## Build

Source a supported OpenFOAM environment, then build:

```bash
source ~/bin/load-openfoam v2512
./Allwmake
```

PETSc is required for the coupled Newton solve path. The build scripts detect
`PETSC_DIR` and add the required PETSc include and link flags.

## Tutorials

The retained tutorials are in `tutorials/fluids`:

```bash
cd tutorials/fluids/cylinderInChannel
./Allrun

cd ../decayingTaylorGreenVortex
./Allrun
```

Cases run `newtonIcoFoam` directly and do not require
`constant/physicsProperties`.

## Provenance

The solver and support classes are extracted from solids4foam while preserving
the original source layout where practical, so updates to the upstream
`newtonIcoFluid` class can be ported with small diffs.
