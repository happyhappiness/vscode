    }
    child_events[0] = exit_event;
    child_events[1] = max_requests_per_child_event;

    if (parent_pid != my_pid) {
        child_events[2] = OpenProcess(SYNCHRONIZE, FALSE, parent_pid);
        num_events = 3;
    }
    else {
        /* presumably -DONE_PROCESS */
        child_events[2] = NULL;
        num_events = 2;
    }
