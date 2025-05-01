import random
import subprocess
import matplotlib.pyplot as plt
import pandas as pd

# Function to call the C program with a given input and get the result
def run_push_swap(input_data):
    # Convert the list to a space-separated string of numbers
    input_str = ' '.join(map(str, input_data))
    
    # Run the C program using subprocess
    # './push_swap' is the name of the compiled C program
    # input_str is passed via stdin
    result = subprocess.run(
        ['./push_swap'] + list(map(str, input_data)),  # Pass input data as command line arguments
        capture_output=True,  # Capture stdout and stderr
        text=True  # Treat output as text (string)
    )
    
    # Parse the output (assumed to be a list of moves, one per line)
    output = result.stdout.strip()
    
    # Split the output by newlines and count the number of lines (i.e., moves)
    if output:
        moves = output.splitlines()
        return len(moves)  # Return the number of moves
    else:
        return 0  # Return 0 if no moves were made

# List to store the results of move counts
results_100 = []

# Run the test 10000 times
for i in range(10):
    # Generate 500 distinct random integers between 0 and 1000
    input_data = random.sample(range(1000), 500)
    
    # Run the C program with the input data and get the number of moves
    moves = run_push_swap(input_data)
    
    # Append the result (number of moves) to the results list
    results_100.append(moves)


print(df.describe())

# Show the histogram
plt.show()
