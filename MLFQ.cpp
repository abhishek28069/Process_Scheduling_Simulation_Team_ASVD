#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "RR_MLFQ.cpp"
#include "FCFS_MLFQ.cpp"

using namespace std;

vector<string> process_input(char *file)
{
    vector<string> process_as_strings;
    FILE *fd = fopen(file, "r");
    int size = 1024, pos, c;
    char *buffer = (char *)malloc(size);
    if (fd)
    {
        do
        { // read all lines in file
            pos = 0;
            do
            { // read one line
                c = fgetc(fd);
                if (c != EOF)
                    buffer[pos++] = (char)c;
                if (pos >= size - 1)
                { // increase buffer length - leave room for 0
                    size *= 2;
                    buffer = (char *)realloc(buffer, size);
                }
            } while (c != EOF && c != '\n');
            buffer[pos] = 0;
            // line is now in buffer
            process_as_strings.push_back(buffer);
        } while (c != EOF);
        fclose(fd);
    }
    return process_as_strings;
}

vector<vector<string>> processes_for_RR(char *file)
{
    vector<vector<string>> res(3);
    vector<string> all_processes = process_input(file);
    for (auto line : all_processes)
    {
        vector<string> tokens;
        stringstream check(line);
        string temp;
        while (getline(check, temp, ' '))
        {
            tokens.push_back(temp);
        }
        if (stoi(tokens[3]) >= 8 && stoi(tokens[3]) <= 10)
        {
            res[0].push_back(line);
        }
        else if (stoi(tokens[3]) >= 4 && stoi(tokens[3]) <= 7)
        {
            res[1].push_back(line);
        }
        else if (stoi(tokens[3]) >= 0 && stoi(tokens[3]) <= 3)
        {
            res[2].push_back(line);
        }
    }
    return res;
}

class MLFQ
{

public:
    vector<PCB_RR_MLFQ> ready_queue;
    vector<RR_MLFQ> queue_level_scheduler;
    vector<vector<string>> queue_level_processes;
    FCFS_MLFQ new_fcfs_mlfq;
    // level 0 : (priority 10 - 8)
    // level 1 : (priority 7 - 4)
    // level 2 : (priority 3 - 0)

    MLFQ() {}
    MLFQ(char *file_name)
    {
        queue_level_processes = processes_for_RR(file_name);
        int time_quanta[3];
        time_quanta[0] = 5;
        time_quanta[1] = 8;
        time_quanta[2] = 10;
        for (int i = 0; i < 2; i++)
        {
            cout << "-----" << time_quanta[i] << endl;
            RR_MLFQ new_rrmlfq(queue_level_processes[i], time_quanta[i]);
            queue_level_scheduler.push_back(new_rrmlfq);
        }
        FCFS_MLFQ temp(queue_level_processes[2]);
        new_fcfs_mlfq = temp;
        // for(vector<string> queue : queue_level_processes){
        //      cout << "--------\n";
        //      for(string proc : queue){
        //           cout << proc << endl;
        //      }
        // }
    }

    bool areAllComplete()
    {
        // return queue_level_scheduler[0].isComplete() && queue_level_scheduler[1].isComplete() && queue_level_scheduler[2].isComplete();
        return queue_level_scheduler[0].isComplete() && queue_level_scheduler[1].isComplete();
    }

    void performAgeing()
    {
    }

    void printDemotedProcs(vector<PCB_RR_MLFQ> procs, int level)
    {
        cout << level << ". Entered into print demoted procs\n";
        for (PCB_RR_MLFQ pcb : procs)
        {
            cout << pcb.name << endl;
        }
        cout << "Exited from print demoted procs\n";
    }

    void saveProps(ofstream &out_fd, vector<PCB_RR_MLFQ> completed_procs)
    {
        for (PCB_RR_MLFQ pcb : completed_procs)
        {
            string temp = "";
            temp = to_string(pcb.PID) + "," + pcb.name + "," + to_string(pcb.priority) + "," +
                   to_string(pcb.original_arrival_time / 1000) + "," + to_string(pcb.cpu_burst1 / 1000) + "," +
                   to_string(pcb.io_burst / 1000) + "," + to_string(pcb.cpu_burst2 / 1000) + "," + to_string(pcb.start_time / 1000) +
                   "," + to_string(pcb.response_time / 1000) + "," + to_string(pcb.completion_time / 1000) + "," +
                   to_string(pcb.turn_around_time / 1000) + "," + to_string(pcb.waiting_time / 1000) + "\n";
            out_fd << temp;
        }
    }

    void saveToFile()
    {
        ofstream out;
        out.open("./output/MLFQ_Schedule.csv");
        string header = "id,name,priority,arrival,burst1,io,burst2,start,resp,compl,turn,wait\n";
        out << header;
        saveProps(out, queue_level_scheduler[0].terminated);
        saveProps(out, queue_level_scheduler[1].terminated);
        while (!new_fcfs_mlfq.terminate_queue.empty())
        {
            Process proc = new_fcfs_mlfq.terminate_queue.front();
            new_fcfs_mlfq.terminate_queue.pop();
            string temp = "";
            temp = to_string(proc.PID) + "," + proc.name + "," + to_string(proc.priority) + "," +
                   to_string(proc.arrival_time) + "," + to_string(proc.cpu_burst1) + "," +
                   to_string(proc.io_burst) + "," + to_string(proc.cpu_burst2) + "," + to_string(proc.start_time) +
                   "," + to_string(proc.response_time) + "," + to_string(proc.completion_time) + "," +
                   to_string(proc.turn_around_time) + "," + to_string(proc.waiting_time) + "\n";
            out << temp;
        }
        out.close();
    }

    void exec()
    {
        int time0 = 0, time1 = 0, time2 = 0;
        while (!areAllComplete())
        {
            vector<PCB_RR_MLFQ> demoted_proc_level0, demoted_proc_level1;
            if (!queue_level_scheduler[0].isComplete())
            {
                // cout << "IN TIME0 " << endl;
                time0 = queue_level_scheduler[0].exec(0);
                // cout << "sadsadsdgdasd: " << time0 << endl;
            }
            if (!queue_level_scheduler[1].isComplete())
            {
                cout << "time0: " << time0 << endl;
                demoted_proc_level0 = queue_level_scheduler[0].demoted_processes;
                // printDemotedProcs(demoted_proc_level0,0);
                queue_level_scheduler[1].insertProcesses(demoted_proc_level0);
                // queue_level_scheduler[1].printQueue(queue_level_scheduler[1].ready_queue);
                // cout << "IN TIME1 " << endl;
                time1 = queue_level_scheduler[1].exec(time0);
            }
            demoted_proc_level1 = queue_level_scheduler[1].demoted_processes;
            // cout << demoted_proc_level1.size() << " time1: " << time1 << endl;
            new_fcfs_mlfq.schedule_processes(time1 / 1000, demoted_proc_level1);
            // new_fcfs_mlfq.print_schedule();
        }
        saveToFile();
    }
};