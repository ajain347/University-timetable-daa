
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct BenchmarkRecord
{
    string scenario;
    string algorithm;
    double time;
    long long checks;
    int scheduled;
    int valid;
};

struct Summary
{
    string scenario;
    string algorithm;
    int runs = 0;
    double totalTime = 0;
    double minTime = -1;
    double maxTime = 0;
    long long totalChecks = 0;
    int validRuns = 0;
    int totalScheduled = 0;
};

int main()
{
    ifstream file("benchmarks/final_results.csv");

    if (!file)
    {
        cerr << "Cannot open benchmark results.\n";
        return 1;
    }

    string line;
    getline(file, line); // Skip CSV header

    vector<Summary> summaries;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string fields[11];

        for (int i = 0; i < 11; i++)
        {
            if (!getline(ss, fields[i], ','))
            {
                cerr << "Invalid benchmark row.\n";
                return 1;
            }
        }

        string scenario = fields[0];
        string algorithm = fields[1];

        int scheduled = stoi(fields[4]);
        int valid = stoi(fields[6]);
        long long checks = stoll(fields[7]);
        double time = stod(fields[9]);

        int index = -1;

        for (int i = 0; i < (int)summaries.size(); i++)
        {
            if (summaries[i].scenario == scenario &&
                summaries[i].algorithm == algorithm)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            Summary s;
            s.scenario = scenario;
            s.algorithm = algorithm;

            summaries.push_back(s);
            index = (int)summaries.size() - 1;
        }

        Summary& s = summaries[index];

        s.runs++;
        s.totalTime += time;
        s.totalChecks += checks;
        s.totalScheduled += scheduled;

        if (valid == 1)
            s.validRuns++;

        if (s.minTime < 0 || time < s.minTime)
            s.minTime = time;

        if (time > s.maxTime)
            s.maxTime = time;
    }

    ofstream output("benchmarks/summary.csv");

    if (!output)
    {
        cerr << "Cannot create summary.csv\n";
        return 1;
    }

    output << "Scenario,Algorithm,Runs,AverageMs,"
           << "MinimumMs,MaximumMs,AverageChecks,"
           << "AverageScheduled,ValidRuns\n";

    cout << fixed << setprecision(6);
    output << fixed << setprecision(6);

    for (const Summary& s : summaries)
    {
        if (s.runs == 0)
            continue;

        double avgTime = s.totalTime / s.runs;
        double avgChecks =
            (double)s.totalChecks / s.runs;
        double avgScheduled =
            (double)s.totalScheduled / s.runs;

        cout << "\n" << s.scenario
             << " | " << s.algorithm << "\n";

        cout << "Runs: " << s.runs << "\n";
        cout << "Average time: " << avgTime << " ms\n";
        cout << "Min/Max: " << s.minTime
             << " / " << s.maxTime << " ms\n";
        cout << "Average checks: " << avgChecks << "\n";
        cout << "Valid runs: " << s.validRuns << "\n";

        output << s.scenario << ","
               << s.algorithm << ","
               << s.runs << ","
               << avgTime << ","
               << s.minTime << ","
               << s.maxTime << ","
               << avgChecks << ","
               << avgScheduled << ","
               << s.validRuns << "\n";
    }

    cout << "\nSummary saved to benchmarks/summary.csv\n";

    return 0;
}
