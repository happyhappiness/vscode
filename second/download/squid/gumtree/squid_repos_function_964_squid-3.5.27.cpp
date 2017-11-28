int
CommSelectEngine::checkEvents(int timeout)
{
    static time_t last_timeout = 0;

    /* No, this shouldn't be here. But it shouldn't be in each comm handler. -adrian */
    if (squid_curtime > last_timeout) {
        last_timeout = squid_curtime;
        checkTimeouts();
    }

    switch (Comm::DoSelect(timeout)) {

    case Comm::OK:

    case Comm::TIMEOUT:
        return 0;

    case Comm::IDLE:

    case Comm::SHUTDOWN:
        return EVENT_IDLE;

    case Comm::COMM_ERROR:
        return EVENT_ERROR;

    default:
        fatal_dump("comm.cc: Internal error -- this should never happen.");
        return EVENT_ERROR;
    };
}