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
