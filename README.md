# Philosophers (Dining Philosophers Problem)

This project implements the classic **Dining Philosophers Problem** using two different approaches: threads with mutexes and processes with semaphores.

## Problem Description

The Dining Philosophers Problem is a classic synchronization problem in computer science. Five philosophers sit around a circular table with five forks between them. Each philosopher alternates between thinking and eating. To eat, a philosopher needs both forks adjacent to them. The challenge is to design a solution that prevents deadlock and starvation.

## Project Structure

```
philos/
├── philo/          # Thread-based implementation
└── philo_bonus/    # Process-based implementation
```

## Common Rules

Both implementations follow these rules:
- Each philosopher is numbered from 1 to `number_of_philosophers`
- Philosopher 1 sits next to philosopher `number_of_philosophers`
- Any state change must be formatted as: `timestamp_in_ms X message`
- Messages include: "has taken a fork", "is eating", "is sleeping", "is thinking", "died"
- The simulation stops when a philosopher dies
- Philosophers should avoid dying!

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't eaten
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) Number of times each philosopher must eat before simulation ends

### Examples

```bash
# Basic test - philosophers should not die
./philo 4 410 200 200

# Philosophers must eat 5 times each
./philo 5 800 200 200 5

# Edge case - one philosopher
./philo 1 800 200 200

# Tight timing test
./philo 4 310 200 100
```

## Implementation Details

### Regular Version (`philo/`)

**Approach**: Uses threads and mutexes
- Each philosopher is a separate thread
- Each fork is protected by a mutex
- One watchdog thread monitors all philosophers for death
- Shared memory between threads

**Key Features**:
- Thread-safe access to shared data using mutexes
- Deadlock prevention through ordered fork acquisition
- Starvation prevention with staggered philosopher starts
- Race condition prevention with proper mutex locking

### Bonus Version (`philo_bonus/`)

**Approach**: Uses processes and semaphores
- Each philosopher is a separate process
- Forks are managed by a semaphore with count = number_of_philosophers
- Each philosopher process has its own watchdog thread
- Inter-process communication through semaphores

**Key Features**:
- Process isolation - each philosopher runs independently
- Semaphore-based fork management
- Individual process monitoring for death detection
- Process cleanup using SIGKILL

**Memory Management Note**: The bonus version may show "still reachable" memory in Valgrind due to pthread library internals when processes exit abruptly. This is expected behavior. If signal handling (SIGKILL with signal() or sigaction()) were allowed by the subject, these could be eliminated, but these functions are forbidden in the project requirements.

## Compilation

Both versions include Makefiles with standard targets:

```bash
# Compile
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re

# Compile and clean objects (bonus Makefile)
make e
```

**Compiler Flags**: `-Wall -Wextra -Werror`

## Key Algorithms

### Deadlock Prevention
- Odd philosophers pick up right fork first, then left fork
- Even philosophers pick up left fork first, then right fork
- This breaks the circular wait condition that causes deadlock

### Starvation Prevention
- Even-numbered philosophers have a small initial delay (200μs in bonus, 200μs in mandatory part)
- Minimum thinking time ensures philosophers don't immediately compete again
- Fair access patterns prevent any philosopher from being permanently blocked

### Death Detection
- **Regular**: Centralized watchdog thread checks all philosophers
- **Bonus**: Each process has its own watchdog thread monitoring itself
- Precise timing calculations account for meals eaten vs. time since start

## Testing

### Recommended Test Cases

```bash
# Should not die
./philo 1 800 200 200
./philo 5 800 200 200
./philo 4 410 200 200
./philo 4 800 200 200

# Should not die, simulation should stop when everyone has eaten enough
./philo 5 800 200 200 7
./philo 4 410 200 200 10

# Should die
./philo 4 310 200 100
./philo 1 200 100 100

# Performance tests
./philo 200 800 200 200    # Many philosophers
./philo 4 410 200 200      # Tight timing
```

### Expected Behavior
- No philosopher should die in "should not die" tests
- Simulation should end when all philosophers have eaten the required number of times
- Death should be detected within 10ms of occurrence
- No data races (check with `valgrind --tool=helgrind`)

## Design Decisions

### Timing Precision
- All times stored in microseconds internally for precision
- Output converted to milliseconds for display
- `precise_usleep()` function provides accurate delays

### Fork Management
- **Regular**: Each fork is a separate mutex, philosophers acquire both
- **Bonus**: Single semaphore with count = number of forks, philosophers acquire 2

## Known Limitations

1. **Bonus Memory Reports**: Valgrind may report "still reachable" memory from pthread internals when processes exit via `exit()`. This is normal and expected.

2. **Minimum Timing**: Very small time values (< 60ms) may not work reliably due to system scheduler limitations.

3. **Large Philosopher Counts**: Performance may degrade with very large numbers of philosophers (> 200) due to context switching overhead.

## Author

This implementation follows the 42 School Philosophers project requirements and demonstrates understanding of:
- Concurrent programming concepts
- Thread vs. process-based solutions
- Synchronization primitives (mutexes, semaphores)
- Race condition and deadlock prevention
- Resource management and cleanup 