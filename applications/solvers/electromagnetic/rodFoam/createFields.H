    Info<< "Reading transportProperties\n" << endl;
    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );
    dimensionedScalar muMag
    (
        transportProperties.lookup("muMag")
    );

    Info<< "Reading field sigma\n" << endl;
    volScalarField sigma
    (
        IOobject
        (
            "sigma",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field ElPot\n" << endl;
    volScalarField ElPot
    (
        IOobject
        (
            "ElPot",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field A\n" << endl;
    volVectorField A
    (
        IOobject
        (
            "A",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

 
    Info << "Calculating magnetic field B \n" << endl;
    volVectorField B
    (
        IOobject
        (
            "B",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        fvc::curl(A) 
    );

    Info << "Calculate electrical current density Je \n" << endl;
    volVectorField  Je
    (
        IOobject
        (
            "Je",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        -sigma*(fvc::grad(ElPot)) 
    );

