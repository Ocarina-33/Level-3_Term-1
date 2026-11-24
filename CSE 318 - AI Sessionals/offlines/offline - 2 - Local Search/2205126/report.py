import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('dark_background')

col_names = [
    'Problem_Name', 
    'V', 
    'E', 
    'Simple_Randomized', 
    'Simple_Greedy', 
    'Semi_Greedy(alpha=0.5)', 
    'LS_Iterations', 
    'LS_Average_Value', 
    'GRASP_Iterations', 
    'GRASP_Best_Value', 
    'Known_Best'
]

df = pd.read_csv('2205126.csv', skiprows=3, names=col_names)

subset = df.head(10)

labels = subset['Problem_Name']
randomized = subset['Simple_Randomized']
greedy = subset['Simple_Greedy']
semi_greedy = subset['Semi_Greedy(alpha=0.5)']
local_search = subset['LS_Average_Value']
grasp = subset['GRASP_Best_Value']

x = np.arange(len(labels))
width = 0.15 

fig, ax = plt.subplots(figsize=(14, 7))

ax.set_facecolor("#2b2b2b")
fig.patch.set_facecolor('#2b2b2b')

rects1 = ax.bar(x - 2*width, randomized, width, label='Randomized', color='#3b7bb5')   
rects2 = ax.bar(x - width, greedy, width, label='Greedy', color='#d97c36')             
rects3 = ax.bar(x, semi_greedy, width, label='Semi-Greedy', color='#999999')           
rects4 = ax.bar(x + width, grasp, width, label='GRASP', color='#edc83e')               
rects5 = ax.bar(x + 2*width, local_search, width, label='Local Search', color='#539caf') 

ax.set_ylabel('Cut Weight')
ax.set_title('Max Cut (Graph 1-10)', fontsize=16, fontweight='bold', pad=15)
ax.set_xticks(x)
ax.set_xticklabels(labels)

ax.yaxis.grid(True, color='#555555', linestyle='-', linewidth=0.5, zorder=0)
ax.set_axisbelow(True)

ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=5, frameon=False)

plt.tight_layout()
plt.savefig('performance_plot.png', dpi=300, facecolor=fig.get_facecolor())
plt.show()