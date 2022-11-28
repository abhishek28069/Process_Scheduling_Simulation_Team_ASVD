#include <bits/stdc++.h>
using namespace std;

// PID,name,type,Priority,AT,BT

class SJFP
{
public:
    struct Process
    {
        // populating from input
        int PID;
        string name;
        bool cpu_bound;
        int priority;
        int arrival_time;
        int burst_time;
        int burst_time1;
        int burst_time2;
        int IO_time;
        // derived variables
        int start_time;       // timestamp of first-time cpu allocation
        int completion_time;  // timestamp of termination
        int waiting_time;     // turnaround time - cpu_time
        int turn_around_time; // completion time - arrival time
        int response_time;    // start time - arrival time
    };

    struct cmPtq
    {
        bool operator()(struct Process &x, struct Process &y)
        {

            return (y.burst_time < x.burst_time);
        }
    };

    struct cmpArv
    {
        bool operator()(struct Process &x, struct Process &y)
        {

            return (x.arrival_time < y.arrival_time);
        }
    };

    struct cmpId
    {
        bool operator()(struct Process &x, struct Process &y)
        {

            return (x.PID < y.PID);
        }
    };

    priority_queue<struct Process, vector<struct Process>, cmPtq> Cpt;
    priority_queue<struct Process, vector<struct Process>, cmPtq> IOpt;
    map<int, int> Arrival;
    map<int, pair<bool, int>> Vis;

    void ProcADD(int &cur_time, vector<struct Process> &CPU_Proc)
    {
        if (CPU_Proc.size() == 0)
            return;
        if (Cpt.empty() && cur_time < CPU_Proc[0].arrival_time)
            cur_time = CPU_Proc[0].arrival_time;
        int idx = 0, siz = CPU_Proc.size();

        while (idx < siz && cur_time >= CPU_Proc[idx].arrival_time)
        {
            Cpt.push(*(CPU_Proc.begin()));

            // cout<<CPU_Proc.begin()->PID<<" ";
            CPU_Proc.erase(CPU_Proc.begin());
            idx++;
        }

        return;
    }
    vector<string> split(string str, char delimiter)
    {
        int n = str.length();
        vector<string> result;
        string temp = "";
        for (int i = 0; i < n; i++)
        {
            char ch = str[i];
            if (ch != delimiter)
            {
                temp.append(1, ch);
            }
            else
            {
                result.push_back(temp);
                temp = "";
            }
        }
        if (temp != "")
        {
            result.push_back(temp);
        }
        return result;
    }

    void exec(vector<string> Vec)
    {
        string PID, Priority, AT, BT1, BT2, IOt, Type, Name;
        struct Process obj;
        vector<struct Process> INP;
        for (string proc : Vec)
        {
            vector<string> splits = split(proc, ' ');
            obj.PID = stoi(splits[0]);
            obj.name = splits[1];
            obj.priority = (stoi(splits[3]));
            obj.arrival_time = (stoi(splits[4]));
            obj.burst_time1 = (stoi(splits[5]));
            obj.burst_time = (stoi(splits[5]));
            obj.IO_time = (stoi(splits[6]));
            obj.burst_time2 = (stoi(splits[7]));
            INP.push_back(obj);
        }

        // Sorting on the basis of Arrival Time
        sort(INP.begin(), INP.end(), cmpArv());

        vector<struct Process> CPU_Proc;
        vector<struct Process> CPU_Op;
        vector<struct Process> Ans;
        int idx, cur_time = 0, entr;
        struct Process tp;
        for (idx = 0; idx < INP.size(); idx++)
        {
            CPU_Proc.push_back(INP[idx]);
            Arrival[INP[idx].arrival_time]++;
            Vis[INP[idx].PID] = make_pair(false, INP[idx].burst_time);
        }

        ProcADD(cur_time, CPU_Proc);

        while (!Cpt.empty())
        {
            tp = Cpt.top();
            Cpt.pop();
            if (Vis[tp.PID].first == false)
            {
                tp.start_time = cur_time;
                Vis[tp.PID].first = true;
            }
            entr = 1;
            while (tp.burst_time > 0 && (Arrival[cur_time] == 0) || entr)
            {
                cur_time++;
                tp.burst_time--;
                entr = 0;
            }

            if (tp.burst_time == 0)
            {
                tp.completion_time = cur_time;
                tp.burst_time = Vis[tp.PID].second;
                tp.turn_around_time = tp.completion_time - tp.arrival_time;
                tp.response_time = tp.start_time - tp.arrival_time;
                tp.waiting_time = tp.turn_around_time - tp.burst_time;
                CPU_Op.push_back(tp);
            }
            else
            {
                Cpt.push(tp);
            }

            ProcADD(cur_time, CPU_Proc);
        }
        // code for I/O Process

        for (idx = 0; idx < CPU_Op.size(); idx++)
            Ans.push_back(CPU_Op[idx]);

        sort(Ans.begin(), Ans.end(), cmpId());
        string s;
        ofstream wrt("output/SJFP_Schedule.csv");
        wrt << "id,name,priority,arrival,burst1,io,burst2,start,resp,compl,turn,wait\n";
        for (idx = 0; idx < Ans.size(); idx++)
        {
            s = (to_string(Ans[idx].PID) + "," + Ans[idx].name + "," + to_string(Ans[idx].priority) + "," + to_string(Ans[idx].arrival_time) + "," + to_string(Ans[idx].burst_time1) + "," + to_string(Ans[idx].IO_time) + "," + to_string(Ans[idx].burst_time2) +
                 "," + to_string(Ans[idx].start_time) + "," + to_string(Ans[idx].response_time) + "," + to_string(Ans[idx].completion_time) + "," + to_string(Ans[idx].turn_around_time) + "," + to_string(Ans[idx].waiting_time) + "\n");
            wrt << s;
        }
        wrt.close();
    }
};