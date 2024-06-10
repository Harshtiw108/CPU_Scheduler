#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;          // Process ID
    int burstTime;    // Burst time of the process
    int priority;     // Priority of the process
    int waitingTime;  // Waiting time for the process
    int turnAroundTime; // Turnaround time for the process
};

bool comparePriority(Process a, Process b) {
    return a.priority > b.priority; // Higher priority first
}

void findWaitingTime(std::vector<Process>& processes) {
    processes[0].waitingTime = 0; // First process has no waiting time

    for (int i = 1; i < processes.size(); i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void findTurnAroundTime(std::vector<Process>& processes) {
    for (int i = 0; i < processes.size(); i++) {
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void findAverageTimes(std::vector<Process>& processes) {
    findWaitingTime(processes);
    findTurnAroundTime(processes);

    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    for (int i = 0; i < processes.size(); i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        std::cout << "Process " << processes[i].pid << ": Waiting Time = " << processes[i].waitingTime 
                  << ", Turnaround Time = " << processes[i].turnAroundTime << "\n";
    }

    std::cout << "\nAverage Waiting Time = " << (float)totalWaitingTime / processes.size();
    std::cout << "\nAverage Turnaround Time = " << (float)totalTurnAroundTime / processes.size() << "\n";
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        std::cout << "Enter burst time for process " << i + 1 << ": ";
        std::cin >> processes[i].burstTime;
        std::cout << "Enter priority for process " << i + 1 << ": ";
        std::cin >> processes[i].priority;
    }

    std::sort(processes.begin(), processes.end(), comparePriority);

    findAverageTimes(processes);

    return 0;
}
