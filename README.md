# Bankers-Algo-Implementation

Implement Banker’s Resource Request algorithm for
deadlock ​ ​avoidance.
A process may or may not request all resource at same time. Banker’s safety algorithm should
be executed before allocating resources to the process. If the request is denied the process
goes into waiting queue till the request is not satisfied. Print “Deny” when this scenario occurs.
Print “Grant” when the request is granted. At the end of the execution print the safe sequence
in which the resources were allocated to processes. ​Print the safe sequence in terms of
<process_id>.
Write ​ ​a ​ ​C/C++ ​ ​program ​ ​which ​ ​takes ​ ​following ​ ​inputs ​ ​:
● N ​ ​R ​ ​Q ​ ​(number ​ ​of ​ ​processes, ​ ​resources, ​ ​queries ​ ​respectively)
● Process ​ ​ids
● Respective ​ ​arrival ​ ​times
● Available ​ ​instances ​ ​of ​ ​resources
● Maximum ​ ​R ​ ​that ​ ​can ​ ​be ​ ​allocated ​ ​to ​ ​a ​ ​process
● Resources ​ ​allocated ​ ​to ​ ​processes
● ‘q’ lines containing q queries. Each query will be a request from process <pid> for given
resources
E.g: ​ ​Assuming ​ ​there ​ ​are ​ ​3 ​ ​resources ​ ​in ​ ​the ​ ​system
0 ​ ​1 ​ ​1 ​ ​1 (i.e. ​ ​P0 ​ ​is ​ ​requesting ​ ​1 ​ ​instance ​ ​of ​ ​each ​ ​available ​ ​resource)
1 ​ ​1 ​ ​0 ​ ​1 (i.e. ​ ​P1 ​ ​is ​ ​requesting ​ ​1 ​ ​instance ​ ​of ​ ​1st ​ ​and ​ ​3rd ​ ​resource)
Note: ​ ​request ​ ​from ​ ​a ​ ​process ​ ​will ​ ​never ​ ​exceed ​ ​the ​ ​total ​ ​requirement ​ ​for ​ ​the ​ ​same ​ ​process.
