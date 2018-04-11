#!/usr/bin/python

import math

from plotly.offline import download_plotlyjs, plot, iplot
from plotly.graph_objs import Box, Figure, Layout, Scatter

tab_data = [ 'data_iteration_de_base.txt', 'data_iteration_r_adding_walks.txt' ]
color = [ '#0c7c71', '#af0736' ]
name = [ 'basic iteration function', 'r-adding walk iteration function' ]

def extract_lines(data):
    with open(data, 'r') as f:
        file_content = f.read()
        lines = file_content.split('\n')
        lines = [ line for line in lines if len(line) > 5 ]
    return lines

tab_lines = []
for data in tab_data:
    tab_lines.append(extract_lines(data))

def extract_values(lines):
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
    uniq_q_values = sorted(list(set(q_values)))

    return (values, uniq_q_values, f_counts)

tab_values = []
tab_uniq_q_values = []
tab_f_counts = []
for lines in tab_lines:
    (values, uniq_q_values, f_counts) = extract_values(lines)
    tab_values.append(values)
    tab_uniq_q_values.append(uniq_q_values)
    tab_f_counts.append(f_counts)

for x in tab_uniq_q_values:
    for y in tab_uniq_q_values:
        if x != y:
            exit()

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

def avg_f_counts(values):
    return list(map(
        lambda x: avg(filter_f_counts(values, x)),
        uniq_q_values))

tab_avg_f_counts = []
for values in tab_values:
    tab_avg_f_counts.append(avg_f_counts(values))

# Use sqrt(q) as a reference
sqrt_q_values = [ math.sqrt(q) for q in uniq_q_values ]

# f_count = const * sqrt(q)
tab_zipped = []
for avg_f_counts in tab_avg_f_counts:
    tab_zipped.append(zip(avg_f_counts, sqrt_q_values))
tab_const = []
for zipped in tab_zipped:
    tab_const.append(list(map(
        lambda x: round(x[0] / x[1], 3), zipped)))

for a in tab_const:
    print a
    print(round(avg(a), 3))

# Define traces to show on the chart
sqrt_trace = Scatter(
    x=uniq_q_values,
    y=sqrt_q_values,
    marker=dict(color='#81e506'),
    name='sqrt(q)'
)

def avg_f_calls_trace(x, y, color, name):
    avg_f_calls_trace = Scatter(
        x=x,
        y=y,
        mode='markers',
        marker=dict(color=color),
        name=name
    )
    return avg_f_calls_trace

zipped = zip(tab_avg_f_counts, color, name)
tab_avg_f_calls_trace = list(map(
    lambda x: avg_f_calls_trace(uniq_q_values, x[0], x[1], x[2]), zipped))

data = [ sqrt_trace ]
for avg_f_calls_trace in tab_avg_f_calls_trace:
    data.append(avg_f_calls_trace)

layout = Layout(showlegend=True)
fig = Figure(data=data, layout=layout)

plot(fig)
