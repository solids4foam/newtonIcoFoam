# Cylinder In Channel

This case runs the standalone `newtonIcoFoam` solver for incompressible flow
around a cylinder in a channel.

Run the default PETSc Schur field-split setup:

```bash
./Allrun
```

Run the optional SIMPLE-type physics preconditioner setup:

```bash
./Allrun newtonIcoFluidPhysicsPC
```

The case uses `constant/fluidProperties.newtonIcoFluid` and
`system/fvSolution.newtonIcoFluid`. `constant/physicsProperties` is not needed
in the standalone solver.
