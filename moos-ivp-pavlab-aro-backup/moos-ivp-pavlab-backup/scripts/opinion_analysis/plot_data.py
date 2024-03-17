#!/usr/bin/env python3
print("Starting plotting")

import csv
import ternary
import matplotlib.pyplot as plt
from os import listdir
from os.path import isfile, join
from plot_data_helpers import parseOpinionLine



data_dir = "data"
files_to_process = [f for f in listdir(data_dir) if isfile(join(data_dir, f))]

attention_files = {}
opinion_files = {}

for filename in files_to_process:
    rows = []
    with open(data_dir + "/" + filename, 'r') as file:
        csvreader = csv.reader(file)
        for row in csvreader:
            rows.append(row)

    if "attention" in filename:
        attention_files[filename] = rows

    if "opinions" in filename:
        opinion_files[filename] = rows

########################################################
# Plot opinions in ternary plot
# from https://github.com/marcharper/python-ternary
agent_color = {'abe':'lightsteelblue', 'ben':'moccasin', 'cal':'limegreen', 'deb':'salmon', 'eve':'violet', 'fin':'peru', 'gil':'pink', 'hix':'yellow'}
agent_end   = {'abe':'tab:blue', 'ben':'tab:orange', 'cal':'tab:green', 'deb':'tab:red', 'eve':'tab:purple', 'fin':'tab:brown', 'gil':'deeppink', 'hix':'tab:olive'}
fontsize = 12
figure, tax = ternary.figure(scale=9.0)
axis_limits = {'b':[-8, 16],'l':[-8,16],'r':[-8,16]}
tax.set_axis_limits(axis_limits)
tax.boundary()
tax.gridlines(multiple=1, color="black")

# plot data for each record
for data_list in opinion_files.values():
    points = []
    times  = []
    for line in data_list:
         time, v_name, group, opinion_names, opinion_vals_tpl = parseOpinionLine(line)
         points.append(opinion_vals_tpl)
         times.append(time)
    
    # Plot the data
    conv_points = tax.convert_coordinates(points)
    tax.plot(conv_points, linewidth=1.0, label=v_name, color=agent_color[v_name])
    
# again plot the end points on top. 
for data_list in opinion_files.values():
    points = []
    times  = []
    for line in data_list:
         time, v_name, group, opinion_names, opinion_vals_tpl = parseOpinionLine(line)
         points.append(opinion_vals_tpl)
         times.append(time)
    
    # Plot the data
    conv_points = tax.convert_coordinates(points)
    tax.plot([conv_points[-1],conv_points[-1]], marker="o", markersize=10,  color=agent_end[v_name])
    
tax.get_ticks_from_axis_limits(1)
tax.set_custom_ticks(offset=0.017)
tax.bottom_axis_label(opinion_names[0],  fontsize=fontsize)
tax.right_axis_label(opinion_names[1],   fontsize=fontsize, offset=0.12)
tax.left_axis_label(opinion_names[2],   fontsize=fontsize, offset=0.12)
tax.get_axes().axis('off')
tax.clear_matplotlib_ticks()
tax.legend()
tax.savefig("OpinionTrajectories.pdf", dpi=1200)
print("Finished generating plot: " + "OpinionTrajectories.pdf")
tax.show()



###############################################################
# Plot attention from all agents in single plot

fig2 = plt.figure()

for filename, data_list in attention_files.items():
    name = filename[:3]
    times = []
    atten_mag = []
    for pair in data_list:
        times.append(float(pair[0]))
        atten_mag.append(float(pair[1]))
    
    plt.plot(times, atten_mag, label=name)

plt.xlabel('Time Since Mission Start', fontsize=12)
plt.ylabel('Attention (u)', fontsize=12)
plt.grid()
plt.legend()
fig2.savefig("AttentionTrajectories.pdf", dpi=1200)
print("Finished generating plot: " + "AttentionTrajectories.pdf")
plt.show()
    
    

    
    


    
