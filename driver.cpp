#include <iostream>
#include <bits/stdc++.h>

#include "SJFP.cpp"
#include "SJFNP.cpp"
#include "RR.cpp"
#include "MLFQ.cpp"
#include "FCFS.cpp"
#include "MLQ.cpp"
#include "priority_premptive.cpp"
#include "priority_non_premptive.cpp"

vector<string> process_input_file(char *file)
{
    vector<string> process_as_strings;
    FILE *fd = fopen(file, "r");
    int size = 1024, pos, c;
    char *buffer = (char *)malloc(size);
    if (fd)
    {
        do
        {
            pos = 0;
            do
            {
                c = fgetc(fd);
                if (c != EOF)
                    buffer[pos++] = (char)c;
                if (pos >= size - 1)
                {
                    size *= 2;
                    buffer = (char *)realloc(buffer, size);
                }
            } while (c != EOF && c != '\n');
            buffer[pos] = 0;
            process_as_strings.push_back(buffer);
        } while (c != EOF);
        fclose(fd);
    }
    return process_as_strings;
}

int main(int argc, char **argv)
{
    vector<string> input_from_main = process_input_file(argv[1]);
    SJFP sjfp;
    SJFNP sjfnp;
    RR rr;
    MLFQ mlfq(argv[1]);
    FCFS fcfs(input_from_main);
    MLQ mlq(input_from_main);
    Priority_non_preemptive pnp(input_from_main);
    Priority_preemptive pp(input_from_main);
    sjfp.exec(input_from_main);
    sjfnp.exec(input_from_main);
    rr.exec(input_from_main, 0, 2);
    mlfq.exec();
    fcfs.execute();
    mlq.execute();
    pnp.execute();
    pp.execute();
    system("python3 .\\plot.py");
    return 0;
}