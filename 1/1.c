import signal
import time

# Define a handler function to be called when the timer expires
def timer_handler_real(signum, frame):
    print("ITIMER_REAL timer expired")

def timer_handler_virtual(signum, frame):
    print("ITIMER_VIRTUAL timer expired")

def timer_handler_prof(signum, frame):
    print("ITIMER_PROF timer expired")

# Set the interval timer for ITIMER_REAL (10 seconds)
signal.signal(signal.ITIMER_REAL, timer_handler_real)
signal.setitimer(signal.ITIMER_REAL, 10, 0)

# Set the interval timer for ITIMER_VIRTUAL (10 seconds)
signal.signal(signal.ITIMER_VIRTUAL, timer_handler_virtual)
signal.setitimer(signal.ITIMER_VIRTUAL, 10, 0)

# Set the interval timer for ITIMER_PROF (10 microseconds)
signal.signal(signal.ITIMER_PROF, timer_handler_prof)
signal.setitimer(signal.ITIMER_PROF, 0, 10)

try:
    while True:
        pass
except KeyboardInterrupt:
    print("Exiting...")

