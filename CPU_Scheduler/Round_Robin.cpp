#include <iostream>
#include <queue>
#include <vector>

struct Process {
    int pid;       // Process ID
    int burstTime; // Burst time of the process
    int remainingTime; // Remaining time for the process to complete
};

int main() {
    int n, quantum;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;
    std::cout << "Enter the time quantum: ";
    std::cin >> quantum;

    std::vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        std::cout << "Enter burst time for process " << i + 1 << ": ";
        std::cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    std::queue<Process*> readyQueue;
    for (int i = 0; i < n; ++i) {
        readyQueue.push(&processes[i]);
    }

    int currentTime = 0;
    while (!readyQueue.empty()) {
        Process* currentProcess = readyQueue.front();
        readyQueue.pop();

        if (currentProcess->remainingTime > quantum) {
            currentProcess->remainingTime -= quantum;
            currentTime += quantum;
            std::cout << "Process " << currentProcess->pid << " executed for " << quantum << " units.\n";
            readyQueue.push(currentProcess);
        } else {
            currentTime += currentProcess->remainingTime;
            std::cout << "Process " << currentProcess->pid << " executed for " << currentProcess->remainingTime << " units and completed.\n";
            currentProcess->remainingTime = 0;
        }
    }

    std::cout << "All processes completed by time " << currentTime << ".\n";

    return 0;
}
