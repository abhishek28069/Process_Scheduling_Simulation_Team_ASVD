import numpy as np
import matplotlib.pyplot as plt
import csv

datalists = []


def plot_multibar(csv_filename, output_name):
    global datalists
    dataList = []

    with open(csv_filename) as f:
        reader = csv.DictReader(f)
        for row in reader:
            dataList.append(row)
    datalists.append(dataList)
    # set width of bar
    barWidth = 0.25
    fig = plt.subplots(figsize=(12, 8))

    # data for bars
    COMPLETION_TIME = [float(i["compl"]) for i in dataList]
    TURN_AROUND_TIME = [float(i["turn"]) for i in dataList]
    WAITING_TIME = [float(i["wait"]) for i in dataList]
    NAMES = [i["name"] for i in dataList]

    # Set position of bar on X axis
    br1 = np.arange(len(COMPLETION_TIME))
    br2 = [x + barWidth for x in br1]
    br3 = [x + barWidth for x in br2]

    # Make the plot
    plt.bar(br1, COMPLETION_TIME, color='r', width=barWidth,
            edgecolor='grey', label='completion time')
    plt.bar(br2, TURN_AROUND_TIME, color='g', width=barWidth,
            edgecolor='grey', label='turn around time')
    plt.bar(br3, WAITING_TIME, color='b', width=barWidth,
            edgecolor='grey', label='waiting time')

    # Adding labels and ticks
    plt.xlabel('Process', fontweight='bold', fontsize=15)
    plt.ylabel('Time', fontweight='bold', fontsize=15)
    plt.xticks([r + barWidth for r in range(len(COMPLETION_TIME))],
               NAMES)

    # TITLE
    plt.title("Multibar chart of " + output_name +
              " schedule along with their respective times", fontsize=22)

    plt.legend()
    # plt.show()
    plt.savefig("output/graphs/"+output_name, dpi=1000)


def plot_scatter(csv_filename, output_name):
    dataList = []

    with open(csv_filename) as f:
        reader = csv.DictReader(f)
        for row in reader:
            dataList.append(row)

    # set width of bar
    barWidth = 0.25
    fig = plt.subplots(figsize=(12, 8))

    # set height of bar
    COMPLETION_TIME = [float(i["compl"]) for i in dataList]
    TURN_AROUND_TIME = [float(i["turn"]) for i in dataList]
    WAITING_TIME = [float(i["wait"]) for i in dataList]
    NAMES = [i["name"] for i in dataList]

    plt.plot(NAMES, COMPLETION_TIME, label="Completion Time")
    plt.plot(NAMES, TURN_AROUND_TIME, label="Turn Around Time")
    plt.plot(NAMES, WAITING_TIME, label="Waiting Time")

#     plt.plot(NAMES, COMPLETION_TIME, '--')
#     plt.plot(NAMES, TURN_AROUND_TIME, '--')
#     plt.plot(NAMES, WAITING_TIME, '--')

    # TITLE
    plt.title("Scatter plot of " + output_name +
              " schedule along with their respective times", fontsize=22)

    plt.xlabel('Process')
    plt.ylabel('Time Taken')
    plt.legend(['Completion Time', 'Turn Around Time', 'Waiting Time'])
    plt.grid(True)
    plt.savefig("output/graphs/"+output_name+"_scatter", dpi=1000)


def plot_multibar_avg(output_name):
    global datalists

    barWidth = 0.25
    fig = plt.subplots(figsize=(12, 8))

    AVG_COMPLETION_TIMES = []
    AVG_TURN_AROUND_TIMES = []
    AVG_WAITING_TIMES = []
    for dataList in datalists:
        AVG_COMPLETION_TIMES.append(sum([float(i["compl"])
                                         for i in dataList])/len(dataList))
        AVG_TURN_AROUND_TIMES.append(sum([float(i["turn"])
                                          for i in dataList])/len(dataList))
        AVG_WAITING_TIMES.append(sum([float(i["wait"])
                                      for i in dataList])/len(dataList))

    # Set position of bar on X axis
    br1 = np.arange(len(AVG_COMPLETION_TIMES))
    br2 = [x + barWidth for x in br1]
    br3 = [x + barWidth for x in br2]

    # Make the plot
    plt.bar(br1, AVG_COMPLETION_TIMES, color='r', width=barWidth,
            edgecolor='grey', label='completion time')
    plt.bar(br2, AVG_TURN_AROUND_TIMES, color='g', width=barWidth,
            edgecolor='grey', label='turn around time')
    plt.bar(br3, AVG_WAITING_TIMES, color='b', width=barWidth,
            edgecolor='grey', label='waiting time')

    # Adding labels and ticks
    plt.xlabel('Process', fontweight='bold', fontsize=15)
    plt.ylabel('Time', fontweight='bold', fontsize=15)
    plt.xticks([r + barWidth for r in range(len(AVG_COMPLETION_TIMES))],
               ["fcfs", "priority-p", "priority-np", "mlq", "srtf", "sjf", "rr", "mlfq"])

    # TITLE
    plt.title(
        "Multibar chart of comparsion of average times of different algorithms", fontsize=22)

    plt.legend()
    # plt.show()
    plt.savefig("output/graphs/"+output_name, dpi=1000)


plot_multibar("./output/FCFS_Schedule.csv", "fcfs")
plot_multibar("./output/Priority_Non_Preemptive_Schedule.csv",
              "priority-non-preempt")
plot_multibar("./output/Priority_Preemptive_Schedule.csv", "priority-preempt")
plot_multibar("./output/MLQ_Schedule.csv", "mlq")
plot_multibar("./output/SJFP_Schedule.csv", "sjf-preempt")
plot_multibar("./output/SJFNP_Schedule.csv", "sjf-non-preempt")
plot_multibar("./output/RR_Schedule.csv", "rr")
plot_multibar("./output/MLFQ_Schedule.csv", "mlfq")

plot_scatter("./output/FCFS_Schedule.csv", "fcfs")
plot_scatter("./output/Priority_Non_Preemptive_Schedule.csv",
             "priority-non-preempt")
plot_scatter("./output/Priority_Preemptive_Schedule.csv", "priority-preempt")
plot_scatter("./output/MLQ_Schedule.csv", "mlq")
plot_scatter("./output/SJFP_Schedule.csv", "sjf-preempt")
plot_scatter("./output/SJFNP_Schedule.csv", "sjf-non-preempt")
plot_scatter("./output/RR_Schedule.csv", "rr")
plot_scatter("./output/MLFQ_Schedule.csv", "mlfq")

plot_multibar_avg("averages")
