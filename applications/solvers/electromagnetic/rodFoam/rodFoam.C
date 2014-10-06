/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) Original authors
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    rodFoam

Description
    Solver for steady-state Maxwell equations:
         Vm is the electric potential scalar field
         A is the magnetic vector potencial
         mu is the constant magnetic permeability
         sigma is the electric conductivity
         (sigma is piecewise constant in rodFoamCase) 

Authors
    Margarita Sass-Tisovskaya
    Isabelle Choquet
    Håkan Nilsson
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"
#   include "createFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
 
    // Solve equation for electric potential  ElPot
    solve ( fvm::laplacian(sigma, ElPot) );
  
    // Solve equation for magnetic potential vector A
    solve ( fvm::laplacian(A)==sigma*muMag*(fvc::grad(ElPot)) );
    // Check that all components are still converged
    solve ( fvm::laplacian(A)==sigma*muMag*(fvc::grad(ElPot)) );
       
    // Calculate magnetic field          
    B= fvc::curl(A); 

    // Calculate current density
    Je=-sigma*(fvc::grad(ElPot));

    // Calculate the current in the cross section
#   include "IeEqn.H"

    runTime++;
    sigma.write();
    ElPot.write();
    A.write();
    B.write();
    Je.write();

    Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;

    return(0);
}

// ************************************************************************* //
