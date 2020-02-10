# ACADOtoolkit-Adaptive-Reference-Trajectory-V1.0
A add-on for the ACADO toolkit that enables adaptive reference trajectory functionality

Installation Instructions: \\
Merge the "controller" and "reference trajectory" folders with their counterparts in the ACADO toolkit installation folder and resolve all conflicts. 

Use: \\
Simply replace the "StaticReferenceTrajectory" call by "AdaptiveReferenceTrajectory" when defining your reference.

IMPORTANT NOTES:
1.) Only functions for the C++ version of ACADO, MATLAB interface is not supported.
2.) Only checks the accuracy(95%) of the first 3 differential states for 5 consequetive steps
3.) The same requirements for a reference variablesgrid apply as for the Static Reference trajectory. The first collumn(time) must be present but will be ignored.
