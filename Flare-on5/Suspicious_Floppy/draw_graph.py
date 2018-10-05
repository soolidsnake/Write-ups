import plotly
import plotly.plotly as py
import plotly.graph_objs as go

f = open("log_eip", "r")
values = [int(i.strip()) for i in f.readlines()]
print len(values)
plotly.offline.plot({
    "data": [go.Scatter(x=[x for x in xrange(len(values))], y=values)],
    "layout": go.Layout(title="")
}, auto_open=True)
