# AOS PROJECT: Process Scheduling Algorithms Simulation

## Requirements
- for python `pip install numpy matplotlib`

## Repo Structure
- `driver.cpp` contains the main execution code.
- Individual file for each algorithm.
- `plot.py` contains all the code required for plotting. 
- Output folder contains all the schedules in csv format after execution of driver.cpp.
- Graphs folder contains all statistics images.

## Input Format
- Input is given as text file in the form of commmand line argument to driver.cpp.
- Input contains following columns - id, name, cpu_bound, priority, arrival_time, cpu_burst1, io_burst, cpu_burst2
    ```
    sample text file
    1 P1 c 9 0 9 0 0
    2 P2 c 8 1 5 0 0
    3 P3 c 7 3 7 0 0
    4 P4 c 2 2 9 0 0
    5 P5 c 5 5 6 0 0
    ```

## Execution
- Commmand
  ```
  g++ ./driver.cpp -o driver

  ./driver ./input.txt
  ```
- Make sure `output` and `output/graphs` folders are present.

## Repo Link
[Process_Scheduling_Simulation_Team_ASVD](https://github.com/abhishek28069/Process_Scheduling_Simulation_Team_ASVD)
