int
EventScheduler::timeRemaining() const
{
    if (!tasks)
        return EVENT_IDLE;

    if (tasks->when <= current_dtime) // we are on time or late
        return 0; // fire the event ASAP

    const double diff = tasks->when - current_dtime; // microseconds
    // Round UP: If we come back a nanosecond earlier, we will wait again!
    const int timeLeft = static_cast<int>(ceil(1000*diff)); // milliseconds
    // Avoid hot idle: A series of rapid select() calls with zero timeout.
    const int minDelay = 1; // millisecond
    return max(minDelay, timeLeft);
}