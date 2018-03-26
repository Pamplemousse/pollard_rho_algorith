import math

from plotly.offline import download_plotlyjs, plot, iplot
from plotly.graph_objs import Box, Figure, Layout, Scatter


with open('data.txt','r') as f:
    file_content = f.read()

lines = file_content.split('\n')
lines = [ line for line in lines if len(line) > 5 ]


# Extract values of q and "number of calls to f" from the input file
values = []
for line in lines:
    (p, q, g, h, x, nb_of_f) = line.split(' ')
    value = { 'q': int(q, 2), 'f_count': int(nb_of_f) // 3 }
    values.append(value)
values = sorted(values, key=lambda x: x['q'])

q_values = []
f_counts = []
for item in values:
    q_values.append(item['q'])
    f_counts.append(item['f_count'])

# Use sqrt(q) as a reference
sqrt_q_values = [ math.sqrt(q) for q in q_values ]


# Define traces to show on the chart
sqrt_trace = Scatter(
    x=q_values,
    y=sqrt_q_values,
    name='sqrt(q)'
)

f_calls_trace = Scatter(
    x=q_values,
    y=f_counts,
    mode='markers',
    name='calls to f'
)


data = [ sqrt_trace, f_calls_trace ]
layout = Layout(showlegend=True)
fig = Figure(data=data, layout=layout)

plot(fig)
