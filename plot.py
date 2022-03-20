"""Analyze the spotify data."""

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

sns.set_theme()

csv = pd.read_csv("data.csv")
splot = sns.relplot(x=csv["Buffer Size (kb)"], y=csv["Mean Latency per Read (ns)"])

# plt.axvline(512, 0, 100)

plt.savefig("bench.png")
