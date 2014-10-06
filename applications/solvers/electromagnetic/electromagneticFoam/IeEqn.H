// Check that the current is conserved at a cross-section
//--------------------------------------------------------------------//
//--------------- NOTE: this is valid for uniform mesh ---------------//
//--------------------------------------------------------------------//

#   include "createFieldsGeometry.H"

volVectorField C = mesh.C();        //- center of the volume
volScalarField Cx = C.component(0); //- x coordinate of the center of the volume
vector Ie(0, 0, 0);               //- current

scalar Srod = 0;

//--- loop for calculating current in the cross section
forAll(mesh.C(), celli)
{
    if( mag( Cx[celli] - x ) <= ( dx / 2 )) 
    {
        Ie = Ie + Je[celli] * (mesh.V()[celli] / dx);  
        Srod = Srod + mesh.V()[celli] / dx;
    }
}

Info<<"Srod="<<Srod<<"; electrical current Ie="<<Ie<<endl;
