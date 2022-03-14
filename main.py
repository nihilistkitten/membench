"""Analyze the spotify data."""

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

sns.set_theme()

csv = pd.read_csv("data.csv")
sns.relplot(x=csv["Buffer Size (kb)"], y=csv["Time (ns)"])

plt.savefig("bench.png")
