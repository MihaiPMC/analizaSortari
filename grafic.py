import glob
import os
import pandas as pd
import matplotlib.pyplot as plt

def plot_csv(csv_file):
    # Read CSV file
    df = pd.read_csv(csv_file)
    # Check if this is an individual test CSV or the consolidated CSV
    if 'Time (seconds)' in df.columns:
        algorithms = df['Algorithm']
        x = range(len(algorithms))

        # Create a figure with three subplots (Time, Operations, Comparisons)
        fig, axs = plt.subplots(3, 1, figsize=(10, 15))

        axs[0].bar(x, df['Time (seconds)'], color='skyblue')
        axs[0].set_title("Time (seconds)")
        axs[0].set_xticks(x)
        axs[0].set_xticklabels(algorithms, rotation=45, ha='right')

        axs[1].bar(x, df['Operations'], color='lightgreen')
        axs[1].set_title("Operations")
        axs[1].set_xticks(x)
        axs[1].set_xticklabels(algorithms, rotation=45, ha='right')

        axs[2].bar(x, df['Comparisons'], color='salmon')
        axs[2].set_title("Comparisons")
        axs[2].set_xticks(x)
        axs[2].set_xticklabels(algorithms, rotation=45, ha='right')

        plt.tight_layout()
        out_filename = os.path.splitext(csv_file)[0] + ".png"
        plt.savefig(out_filename)
        plt.close()
        print(f"Graph saved as {out_filename}")
    elif any(col.startswith("Test") for col in df.columns if col != 'Algorithm'):
        # If CSV contains consolidated results with test columns like "Test 1 Time", "Test 2 Time", etc.
        tests = [col for col in df.columns if col.startswith("Test")]
        x = range(1, len(tests) + 1)
        fig, ax = plt.subplots(figsize=(10, 6))
        for idx, row in df.iterrows():
            ax.plot(x, row[tests].values, marker='o', label=row['Algorithm'])
        ax.set_title("Consolidated Test Times")
        ax.set_xlabel("Test Number")
        ax.set_ylabel("Time (seconds)")
        ax.legend()
        plt.tight_layout()
        out_filename = os.path.splitext(csv_file)[0] + ".png"
        plt.savefig(out_filename)
        plt.close()
        print(f"Graph saved as {out_filename}")
    else:
        print(f"Skipping {csv_file}: unknown format")

def main():
    # Process all CSV files in current directory
    csv_files = glob.glob("*.csv")
    for csv_file in csv_files:
        plot_csv(csv_file)

if __name__ == "__main__":
    main()
