# CPU Scheduler

This project is a web-based CPU Scheduler that allows users to input processes and select a scheduling algorithm to visualize the results. The supported algorithms include FCFS, SJF, Priority Scheduling, and Round Robin.

## Features

- Algorithm Selection: FCFS, SJF, Priority Scheduling, Round Robin
- Process Input: Enter processes in `pid,burst_time,priority` format
- Dynamic Results: View waiting time and turnaround time for each process
- Responsive Design

## Getting Started

### Prerequisites

- Git
- C++ Compiler
- Crow (C++ microframework)

### Installing

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/Harshtiw108/CPU_Scheduler.git
    cd CPU_Scheduler
    ```

2. **Setup Backend**:
    - Ensure you have a C++ compiler installed.
    - Install Crow:
        ```sh
        sudo apt-get install libcrow-dev
        ```
    - Compile the backend:
        ```sh
        cd backend
        mkdir build
        cd build
        cmake ..
        make
        ./cpu_scheduler
        ```

3. **Serve Frontend**:
    - Open `index.html
