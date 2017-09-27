        return 1;
   }
#endif

    if (accf > 0) /* 'data' or 'connect' */
    {
        /* first, high priority event is an already accepted connection */
        events[1] = exit_event;
        events[2] = max_requests_per_child_event;
    }
    else /* accf == 0, 'none' */
    {
