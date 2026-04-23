#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Job {
    char id;
    int deadline;
    int profit;
};

// Max-heap comparator
struct CompareProfit {
    bool operator()(Job a, Job b) {
        return a.profit < b.profit; // Max heap based on profit
    }
};

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Job ID, Deadline and Profit for job " << i+1 << ": ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    // Find max deadline
    int maxDeadline = 0;
    for (auto job : jobs)
        if (job.deadline > maxDeadline)
            maxDeadline = job.deadline;

    // Max-heap
    priority_queue<Job, vector<Job>, CompareProfit> pq;
    for (auto job : jobs)
        pq.push(job);

    vector<char> result(maxDeadline, '-');
    int totalProfit = 0;

    while (!pq.empty()) {
        Job current = pq.top(); pq.pop();
        // Place job in latest free slot
        for (int j = min(maxDeadline, current.deadline) - 1; j >= 0; j--) {
            if (result[j] == '-') {
                result[j] = current.id;
                totalProfit += current.profit;
                break;
            }
        }
    }

    cout << "\nSelected Job Sequence: ";
    for (char c : result)
        if (c != '-') cout << c << " ";

    cout << "\nTotal Profit: " << totalProfit << endl;
    return 0;
}
