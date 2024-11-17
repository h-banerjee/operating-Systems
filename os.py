# Banker's Algorithm in Python

def is_safe(processes, avail, max_need, alloc, need):
    # Number of processes and resources
    num_processes = len(processes)
    num_resources = len(avail)

    # Mark all processes as not finished
    finish = [False] * num_processes

    # Copy the available resources to a work array
    work = avail[:]

    # Safe sequence
    safe_seq = []

    while len(safe_seq) < num_processes:
        found = False
        for i in range(num_processes):
            if not finish[i]:
                # Check if the process can be allocated the needed resources
                if all(need[i][j] <= work[j] for j in range(num_resources)):
                    # If yes, allocate the resources and mark as finished
                    for j in range(num_resources):
                        work[j] += alloc[i][j]

                    safe_seq.append(i)
                    finish[i] = True
                    found = True
                    print(f"Process {i} has been allocated and finished.")
                    break
        
        # If no process can proceed, the system is in an unsafe state
        if not found:
            print("System is in an unsafe state!")
            return False

    # Safe sequence found
    print("System is in a safe state!")
    print("Safe Sequence:", safe_seq)
    return True

# Driver code

processes = [0, 1, 2, 3, 4]  # Process IDs
avail = [3, 3, 2]            # Available instances of resources
max_need = [[7, 5, 3],        # Maximum resources for each process
            [3, 2, 2],
            [9, 0, 2],
            [2, 2, 2],
            [4, 3, 3]]

alloc = [[0, 1, 0],           # Allocated resources for each process
         [2, 0, 0],
         [3, 0, 2],
         [2, 1, 1],
         [0, 0, 2]]

# Calculate the need matrix (Max Need - Allocated)
need = [[max_need[i][j] - alloc[i][j] for j in range(len(avail))] for i in range(len(processes))]

# Run the Banker's algorithm
is_safe(processes, avail, max_need, alloc, need)
