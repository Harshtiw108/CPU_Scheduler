#define CROW_MAIN
#include "crow.h"
#include <vector>
#include <algorithm>
#include <sstream>

struct Process {
    int pid;
    int burstTime;
    int priority;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
};

std::string fcfs(std::vector<Process>& processes) {
    int currentTime = 0;
    std::ostringstream result;
    result << "[";
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].waitingTime = currentTime;
        currentTime += processes[i].burstTime;
        processes[i].turnAroundTime = currentTime;
        result << "{ \"pid\": " << processes[i].pid
               << ", \"burstTime\": " << processes[i].burstTime
               << ", \"priority\": " << processes[i].priority
               << ", \"waitingTime\": " << processes[i].waitingTime
               << ", \"turnAroundTime\": " << processes[i].turnAroundTime
               << "}";
        if (i < processes.size() - 1) result << ",";
    }
    result << "]";
    return result.str();
}

std::string sjf(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burstTime < b.burstTime;
    });
    return fcfs(processes);
}

std::string priorityScheduling(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.priority > b.priority;
    });
    return fcfs(processes);
}

std::string roundRobin(std::vector<Process>& processes, int quantum) {
    std::ostringstream result;
    result << "[";
    int currentTime = 0;
    std::vector<Process> queue = processes;

    while (!queue.empty()) {
        std::vector<Process> tempQueue;
        for (auto &process : queue) {
            if (process.remainingTime > quantum) {
                process.remainingTime -= quantum;
                currentTime += quantum;
                tempQueue.push_back(process);
            } else {
                currentTime += process.remainingTime;
                process.remainingTime = 0;
                process.turnAroundTime = currentTime;
                process.waitingTime = process.turnAroundTime - process.burstTime;
                result << "{ \"pid\": " << process.pid
                       << ", \"burstTime\": " << process.burstTime
                       << ", \"priority\": " << process.priority
                       << ", \"waitingTime\": " << process.waitingTime
                       << ", \"turnAroundTime\": " << process.turnAroundTime
                       << "},";
            }
        }
        queue = tempQueue;
    }
    std::string output = result.str();
    if (output.back() == ',') output.pop_back();
    output += "]";
    return output;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/schedule")([](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::vector<Process> processes;
        for (const auto& process : x["processes"]) {
            processes.push_back({
                process["pid"].i(),
                process["burstTime"].i(),
                process["priority"].i(),
                process["burstTime"].i(), 0, 0
            });
        }
        std::string algorithm = x["algorithm"].s();
        std::string result;

        if (algorithm == "fcfs") {
            result = fcfs(processes);
        } else if (algorithm == "Shortest_Job_First") {
            result = sjf(processes);
        } else if (algorithm == "priority") {
            result = priorityScheduling(processes);
        } else if (algorithm == "Round-Robin") {
            int quantum = x["quantum"].i();
            result = roundRobin(processes, quantum);
        } else {
            return crow::response(400, "Unknown algorithm");
        }

        return crow::response(result);
    });

    app.port(18080).multithreaded().run();
}
