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
#include "physicsModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "newtonIcoFoamWriteHeader.H"

    Foam::autoPtr<Foam::physicsModel> physics = Foam::physicsModel::New(runTime);

    while (runTime.run())
    {
        // Update deltaT, if desired, before moving to the next step
        physics().setDeltaT(runTime);

        runTime++;

        if (physics().printInfo())
        {
            Info<< "Time = " << runTime.timeName() << nl << endl;
        }

        // Solve the mathematical model
        physics().evolve();

        // Let the fluid model know the end of the time-step has been reached
        physics().updateTotalFields();

        if (runTime.outputTime())
        {
            physics().writeFields(runTime);
        }

        if (physics().printInfo())
        {
            Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
                << "  ClockTime = " << runTime.elapsedClockTime() << " s"
                << nl << endl;
        }
    }

    physics().end();

    Info<< nl << "End" << nl << endl;

    return(0);
}


// ************************************************************************* //
