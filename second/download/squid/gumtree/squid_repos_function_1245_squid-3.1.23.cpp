int
EventScheduler::checkDelay()
{
    if (!tasks)
        return EVENT_IDLE;

    int result = (int) ((tasks->when - current_dtime) * 1000);

    if (result < 0)
        return 0;

    return result;
}