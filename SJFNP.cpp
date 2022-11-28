#include <bits/stdc++.h>
using namespace std;

// PID,name,type,Priority,AT,BT

class SJFNP
{
public:
    struct Process
    {
        int PID;
        string name;
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

            return (y.arrival_time < x.arrival_time);
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
    priority_queue<struct Process, vector<struct Process>, cmpArv> INP;
    map<int, pair<bool, int>> Vis;

    void ProcADD(int &cur_time)
    {
        if (INP.empty())
            return;
        struct Process tp;
        tp = INP.top();
        if (Cpt.empty() && (cur_time < tp.arrival_time))
            cur_time = tp.arrival_time;

        while (!INP.empty() && cur_time >= tp.arrival_time)
        {
            Cpt.push(tp);
            INP.pop();
            if (!INP.empty())
                tp = INP.top();
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
        string PID, Priority, AT, BT1, BT2, IOt, Name;
        cout << "hii" << endl;
        struct Process obj;
        int idx, i, ct = 0;
        string temp;
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
            Vis[obj.PID] = make_pair(false, obj.arrival_time);
            INP.push(obj);
        }

        vector<struct Process> Ans;
        int cur_time = 0;
        struct Process tp;

        ProcADD(cur_time);
        while (!Cpt.empty())
        {
            tp = Cpt.top();
            Cpt.pop();
            if (Vis[tp.PID].first == false)
            {
                tp.start_time = cur_time;
                cout << tp.PID << " " << cur_time << endl;
                cur_time += tp.burst_time;
                tp.arrival_time = (cur_time + tp.IO_time);
                tp.burst_time = tp.burst_time2;
                Vis[tp.PID].first = true;
                INP.push(tp);
                ProcADD(cur_time);
            }
            else
            {
                cout << tp.PID << " " << cur_time << endl;
                tp.arrival_time = Vis[tp.PID].second;
                cur_time += tp.burst_time;
                tp.completion_time = cur_time;
                tp.turn_around_time = tp.completion_time - tp.arrival_time;
                tp.response_time = tp.start_time - tp.arrival_time;
                tp.waiting_time = tp.turn_around_time - (tp.burst_time1 + tp.burst_time2);
                Ans.push_back(tp);
            }
        }

        sort(Ans.begin(), Ans.end(), cmpId());
        cout << "siz" << Ans.size() << endl;
        string s;
        ofstream wrt("output/SJFNP_Schedule.csv");
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
