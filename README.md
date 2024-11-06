## Philosophers
### About the 42 Norm:
- Each file must contain no more than 5 functions.
- Each function must not exceed 25 lines.
- The project must be written solely in C.
- Global variables are not allowed.
- Any crash, leak, conditional jump, data race or deadlock is forbidden.
- Allowed external functions are: `memset`, `printf`, `malloc`, `free`, `write`,
                                  `usleep`, `gettimeofday`, `pthread_create`,
                                  `pthread_detach`, `pthread_join`, `pthread_mutex_init`,
                                  `pthread_mutex_destroy`, `pthread_mutex_lock`,
                                  `pthread_mutex_unlock`.

### Project Overview:
This project aims to understand **multi-threading** in C and implement the **dining philosophers problem**.

- N philosophers dine together at the same table. Each philosopher has their own plate, and there is a fork between each plate.
- In order to eat, a philosopher needs to hold two forks, which makes them unavailable for the other philosophers.
- After eating, a philosopher needs to sleep for a certain amount of time, and enters in thinking state when it is done.
- While thinking, a philosopher will either eat within a given time or die of starvation.

The problem is how to design an algorithm such that any philosopher will not starve with eating and sleeping given times, assuming that no philosopher can know when others may want to eat or think.

This project introduces the concept of **concurrency**, and makes it possible with **threads and mutexes**.

## Preview:

This shows a visualization of **20 philosophers** which need **100ms to sleep**, **100ms to eat**, and eventually **dying of starvation after 300ms**.
In this case no philosopher will die given the eat/sleep/die durations, and the simulation stops after each philosopher has eaten at least 7 times.

It is provided thanks to [nafuka11's visualizer](https://nafuka11.github.io/philosophers-visualizer/).

![image](https://github.com/user-attachments/assets/7e33f7c4-7e4a-4f9c-a7dc-d83759eb69e6)

This is what the program would normally display.

![image](https://github.com/user-attachments/assets/065bb491-3e52-41b9-a369-31b7a65ed376)

