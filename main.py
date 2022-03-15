"""Analyze the spotify data."""

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

sns.set_theme()

csv = pd.read_csv("data.csv")
sns.lmplot(
    x="Buffer Size (kb)",
    y="Mean Latency per Read (ns)",
    data=csv,
    order=2,
    ci=None,
)

plt.savefig("bench.png")
