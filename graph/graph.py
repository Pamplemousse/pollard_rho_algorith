#!/usr/bin/python

import math

from plotly.offline import download_plotlyjs, plot, iplot
from plotly.graph_objs import Box, Figure, Layout, Scatter


with open('data_iteration_r_adding_walks.txt','r') as f:
    file_content = f.read()

lines = file_content.split('\n')
lines = [ line for line in lines if len(line) > 5 ]


# Extract values of q and "number of calls to f" from the input file
values = []
for line in lines:
    (p, q, g, h, x, nb_of_f) = line.split(' ')
    value = { 'q': int(q, 2), 'f_count': int(nb_of_f) }
    values.append(value)
values = sorted(values, key=lambda x: x['q'])

q_values = []
f_counts = []
for item in values:
    q_values.append(item['q'])
    f_counts.append(item['f_count'])

uniq_q_values = sorted(list(set(q_values)))

# Calculate average number of calls to f per value of q
def filter_f_counts(values, q):
    return list(map(
        lambda x: x['f_count'],
        filter(
            lambda x: x['q'] == q,
            values
        ))
    )

def avg(l):
    return sum(l) / len(l)

avg_f_counts = list(map(
    lambda x: avg(filter_f_counts(values, x)),
    uniq_q_values
))

# Use sqrt(q) as a reference
sqrt_q_values = [ math.sqrt(q) for q in uniq_q_values ]


# Define traces to show on the chart
sqrt_trace = Scatter(
    x=uniq_q_values,
    y=sqrt_q_values,
    marker=dict(color='#81e506'),
    name='sqrt(q)'
)

f_calls_trace = Scatter(
    x=q_values,
    y=f_counts,
    mode='markers',
    marker=dict(size=4, opacity=0.4, symbol='x', color='#af0736'),
    name='calls to f'
)

avg_f_calls_trace = Scatter(
    x=uniq_q_values,
    y=avg_f_counts,
    mode='markers',
    marker=dict(size=7, color='#000000'),
    name='average calls to f'
)


data = [ sqrt_trace, f_calls_trace, avg_f_calls_trace ]
layout = Layout(showlegend=True)
fig = Figure(data=data, layout=layout)

plot(fig)
