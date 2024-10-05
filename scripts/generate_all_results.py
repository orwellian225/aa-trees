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

data = pl.concat([random_data, descending_data], rechunk=True).select(
    pl.col("*").exclude("tree_type", "experiment_type"),
    pl.concat_str(pl.col("tree_type"), pl.col("experiment_type"), separator="-").alias("tree_experiment_type")
)

sns.set_style("whitegrid")

_, ax = plt.subplots(ncols=1)
_ = sns.lineplot(data=data, x="n", y="height", hue="tree_experiment_type", estimator="mean", palette="Set2", ax=ax)
ax.set(yscale="log")
plt.title("Tree Height vs Number of Nodes")
plt.legend(loc="lower right")
plt.savefig("./results/tree_heights.pdf")
plt.close()

_, ax = plt.subplots(ncols=2, figsize=(10,5))
for i in range(2):
    _ = sns.lineplot(data=data, x="n", y="build_duration_seconds", hue="tree_experiment_type", estimator="mean", palette="Set2", ax=ax[i])
    # ax[i].plot(temp_x, temp_x, linestyle="--", c="b", label="$f(x) = x$", alpha=0.5, dashes=(2,5))
    # ax[i].plot(temp_x, np.log2(temp_x), linestyle="--", c="red", label="$f(x) = \log_2(x)$", alpha=0.5, dashes=(2,5))
    if i == 1:
        ax[i].set_yscale("log")
plt.suptitle("Tree building time")
plt.savefig("./results/tree_build_time.pdf")
plt.close()

_, ax = plt.subplots(ncols=2, figsize=(10,5))
for i in range(2):
    _ = sns.lineplot(data=data, x="n", y="destroy_duration_seconds", hue="tree_experiment_type", estimator="mean", palette="Set2", ax=ax[i])
    # ax[i].plot(temp_x, temp_x, linestyle="--", c="b", label="$f(x) = x$", alpha=0.5, dashes=(2,5))
    # ax[i].plot(temp_x, np.log2(temp_x), linestyle="--", c="red", label="$f(x) = \log_2(x)$", alpha=0.5, dashes=(2,5))
    if i == 1:
        ax[i].set_yscale("log")
plt.suptitle("Tree destroy time")
plt.savefig("./results/tree_destroy_time.pdf")
plt.close()
