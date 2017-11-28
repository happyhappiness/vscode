void
Adaptation::Icap::History::currentTime(timeval &current) const
{
    if (concurrencyLevel > 0)
        tvSub(current, currentStart, current_time);
    else {
        current.tv_sec = 0;
        current.tv_usec = 0;
    }
}