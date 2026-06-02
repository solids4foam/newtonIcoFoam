/*---------------------------------------------------------------------------*\
License
    This file is part of newtonIcoFluid.

    newtonIcoFluid is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    newtonIcoFluid is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with newtonIcoFluid.  If not, see <http://www.gnu.org/licenses/>.

Application
    newtonIcoFoam

Description
    Standalone solver for the newtonIcoFluid incompressible Newtonian fluid
    model.

Author
    Philip Cardiff, UCD.
    Zeljko Tukovic, FSB Zagreb.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "newtonIcoFluid.H"

#include <cstdlib>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "newtonIcoFoamWriteHeader.H"

    Foam::autoPtr<Foam::fluidModels::newtonIcoFluid> fluidPtr
    (
        new Foam::fluidModels::newtonIcoFluid(runTime)
    );
    Foam::fluidModels::newtonIcoFluid& fluid = fluidPtr();

    while (runTime.run())
    {
        // Update deltaT, if desired, before moving to the next step
        fluid.setDeltaT(runTime);

        runTime++;

        if (fluid.printInfo())
        {
            Info<< "Time = " << runTime.timeName() << nl << endl;
        }

        // Solve the mathematical model
        fluid.evolve();

        // Let the fluid model know the end of the time-step has been reached
        fluid.updateTotalFields();

        if (runTime.outputTime())
        {
            fluid.writeFields(runTime);
        }

        if (fluid.printInfo())
        {
            Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
                << "  ClockTime = " << runTime.elapsedClockTime() << " s"
                << nl << endl;
        }
    }

    fluid.end();

    Info<< nl << "End" << nl << endl;

    // Avoid OpenFOAM/PETSc teardown aborts in the standalone v2512 PETSc build.
    std::exit(0);

    return(0);
}


// ************************************************************************* //
