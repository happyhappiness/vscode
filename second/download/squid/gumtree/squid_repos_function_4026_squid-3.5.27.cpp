int
Adaptation::Ecap::Engine::checkEvents(int)
{
    // Start with the default I/O loop timeout, convert from milliseconds.
    static const struct timeval maxTimeout = {
        EVENT_LOOP_TIMEOUT/1000, // seconds
        (EVENT_LOOP_TIMEOUT % 1000)*1000
    }; // microseconds
    struct timeval timeout = maxTimeout;

    kickAsyncServices(timeout);
    if (timeout.tv_sec == maxTimeout.tv_sec && timeout.tv_usec == maxTimeout.tv_usec)
        return EVENT_IDLE;

    debugs(93, 7, "timeout: " << timeout.tv_sec << "s+" << timeout.tv_usec << "us");

    // convert back to milliseconds, avoiding int overflows
    if (timeout.tv_sec >= std::numeric_limits<int>::max()/1000 - 1000)
        return std::numeric_limits<int>::max();
    else
        return timeout.tv_sec*1000 + timeout.tv_usec/1000;
}