import math

from plotly.offline import download_plotlyjs, plot, iplot
from plotly.graph_objs import Box, Figure, Layout, Scatter


with open('c/test/fixtures/inputs.txt','r') as f:
    file_content = f.read()

lines = file_content.split('\n')
lines = [ line for line in lines if len(line) > 5 ]


# Extract values of q from the input file
q_values = set()
for line in lines:
    (p, q, g, h, x) = line.split(' ')
    q_values.add(int(q))
q_values = sorted(list(q_values), key=float)

sqrt_q_values = [ math.sqrt(q) for q in q_values ]


# Define traces to show on the chart
sqrt_trace = Scatter(
    x=q_values,
    y=sqrt_q_values,
    name='sqrt(q)'
)

data = [ sqrt_trace ]
layout = Layout(showlegend=True)
fig = Figure(data=data, layout=layout)

plot(fig)
