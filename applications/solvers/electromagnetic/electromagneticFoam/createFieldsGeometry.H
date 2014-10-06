IOdictionary geometryProperties
    (
        IOobject
        (
            "geometryProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );
  

scalar x(readScalar(geometryProperties.lookup("x"))); 
scalar dx(readScalar(geometryProperties.lookup("dx"))); 
