import matplotlib.pyplot as plt
import seaborn as sns
import polars as pl
import numpy as np

random_data = pl.read_csv("./data/random_construction_data.csv").with_columns(
    pl.col("n"),
    pl.col("tree_type"),
    pl.col("height"),
    pl.col("build_duration_seconds"),
    pl.col("destroy_duration_seconds"),
    pl.lit("random").alias("experiment_type")
)
descending_data = pl.read_csv("./data/descending_construction_data.csv").with_columns(
    pl.col("n"),
    pl.col("tree_type"),
    pl.col("height"),
    pl.col("build_duration_seconds"),
    pl.col("destroy_duration_seconds"),
    pl.lit("descending").alias("experiment_type")
)

data = pl.concat([random_data, descending_data], rechunk=True)

sns.set_style("whitegrid")

_, ax = plt.subplots(ncols=1)
_ = sns.lineplot(data=data.filter(pl.col("tree_type") == "OST"), x="n", y="height", hue="experiment_type", estimator="mean", palette="Set2", ax=ax)
ax.set(yscale="log")
plt.title("OST Tree Height vs Number of Nodes")
plt.legend(loc="lower right")
plt.savefig("./results/ost_construction_heights.pdf")
plt.close()

_, ax = plt.subplots(ncols=2, figsize=(10,5))
for i in range(2):
    _ = sns.lineplot(data=data.filter(pl.col("tree_type") == "OST"), x="n", y="build_duration_seconds", hue="experiment_type", estimator="mean", palette="Set2", ax=ax[i])
    # ax[i].plot(temp_x, temp_x, linestyle="--", c="b", label="$f(x) = x$", alpha=0.5, dashes=(2,5))
    # ax[i].plot(temp_x, np.log2(temp_x), linestyle="--", c="red", label="$f(x) = \log_2(x)$", alpha=0.5, dashes=(2,5))
    if i == 1:
        ax[i].set_yscale("log")
plt.suptitle("OST Tree building time")
plt.legend(loc="lower right")
plt.savefig("./results/ost_construction_build_time.pdf")
plt.close()

_, ax = plt.subplots(ncols=2, figsize=(10,5))
for i in range(2):
    _ = sns.lineplot(data=data.filter(pl.col("tree_type") == "OST"), x="n", y="destroy_duration_seconds", hue="experiment_type", estimator="mean", palette="Set2", ax=ax[i])
    # ax[i].plot(temp_x, temp_x, linestyle="--", c="b", label="$f(x) = x$", alpha=0.5, dashes=(2,5))
    # ax[i].plot(temp_x, np.log2(temp_x), linestyle="--", c="red", label="$f(x) = \log_2(x)$", alpha=0.5, dashes=(2,5))
    if i == 1:
        ax[i].set_yscale("log")
plt.suptitle("OST Tree destroy time")
plt.legend(loc="lower right")
plt.savefig("./results/ost_construction_destroy_time.pdf")
plt.close()
