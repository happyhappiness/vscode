void
Comm::SetSelect(int fd, unsigned int type, PF * handler, void *client_data, time_t timeout)
{
    assert(fd >= 0);
    debugs(5, 5, HERE << "FD " << fd << ", type=" << type <<
           ", handler=" << handler << ", client_data=" << client_data <<
           ", timeout=" << timeout);

    /* POLLIN/POLLOUT are defined in <sys/poll.h> */
    fde *F = &fd_table[fd];
    if (!F->flags.open) {
        /* remove from poll set */
        comm_update_fd( fd, POLLREMOVE );
        devpoll_state[fd].state = 0;
        return;
    }

    pollfd_events_t state_old = devpoll_state[fd].state;
    pollfd_events_t state_new = 0; /* new state (derive from old state) */

    if ( type & COMM_SELECT_READ ) {
        if ( handler != NULL ) {
            // Hack to keep the events flowing if there is data immediately ready
            if (F->flags.read_pending)
                state_new |= POLLOUT;
            /* we want to POLLIN */
            state_new |= POLLIN;
        } else {
            ; /* we want to clear POLLIN because handler is NULL */
        }

        F->read_handler = handler;
        F->read_data = client_data;
    } else if ( state_old & POLLIN ) {
        /* we're not changing reading state so take from existing */
        state_new |= POLLIN;
    }

    if ( type & COMM_SELECT_WRITE ) {
        if ( handler != NULL ) {
            /* we want to POLLOUT */
            state_new |= POLLOUT;
        } else {
            ; /* we want to clear POLLOUT because handler is NULL */
        }

        F->write_handler = handler;
        F->write_data = client_data;
    } else if ( state_old & POLLOUT ) {
        /* we're not changing writing state so take from existing */
        state_new |= POLLOUT;
    }

    if ( pollfd_events_t bits_changed = (state_old ^ state_new) ) {
        /* something has changed, update /dev/poll of what to listen for */

        /* did any bits clear? (in which case a poll remove is necessary) */
        if ( bits_changed & state_old ) {
            comm_update_fd( fd, POLLREMOVE );
            /* existing state cleared, so update with all required events */
            if ( state_new )
                comm_update_fd( fd, state_new );
        } else {
            /* only update with new required event */
            if ( pollfd_events_t newly_set_only = (bits_changed & state_new) )
                comm_update_fd( fd, newly_set_only );
        }

        devpoll_state[fd].state = state_new;
    }

    if (timeout)
        F->timeout = squid_curtime + timeout;
}