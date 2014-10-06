#include "fvCFD.H"

int main(int argc, char *argv[]) {
#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"
#include "createFields.H"

solve ( fvm::laplacian(A)==-muMag*Je);
B = fvc::curl(A);

//#include "IeEqn.H"
    runTime++;
    Je.write();
    A.write();
    B.write();

    Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << " ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;
    return(0);
}
