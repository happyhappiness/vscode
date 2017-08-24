(ret == 0 || (events[0].flags & EV_ERROR) == 0 || events[0].data != EINVAL)
    return 0;