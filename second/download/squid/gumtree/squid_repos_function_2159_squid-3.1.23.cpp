void
commSetSelect(int fd, unsigned int type, PF * handler,
              void *client_data, time_t timeout)
{
    fde *F = &fd_table[fd];
    int epoll_ctl_type = 0;

    struct epoll_event ev;
    assert(fd >= 0);
    debugs(5, DEBUG_EPOLL ? 0 : 8, "commSetSelect(FD " << fd << ",type=" << type <<
           ",handler=" << handler << ",client_data=" << client_data <<
           ",timeout=" << timeout << ")");

    if (RUNNING_ON_VALGRIND) {
        /* Keep valgrind happy.. complains about uninitialized bytes otherwise */
        memset(&ev, 0, sizeof(ev));
    }
    ev.events = 0;
    ev.data.fd = fd;

    if (!F->flags.open) {
        epoll_ctl(kdpfd, EPOLL_CTL_DEL, fd, &ev);
        return;
    }

    // If read is an interest

    if (type & COMM_SELECT_READ) {
        if (handler) {
            // Hack to keep the events flowing if there is data immediately ready
            if (F->flags.read_pending)
                ev.events |= EPOLLOUT;
            ev.events |= EPOLLIN;
        }

        F->read_handler = handler;

        F->read_data = client_data;

        // Otherwise, use previously stored value
    } else if (F->epoll_state & EPOLLIN) {
        ev.events |= EPOLLIN;
    }

    // If write is an interest
    if (type & COMM_SELECT_WRITE) {
        if (handler)
            ev.events |= EPOLLOUT;

        F->write_handler = handler;

        F->write_data = client_data;

        // Otherwise, use previously stored value
    } else if (F->epoll_state & EPOLLOUT) {
        ev.events |= EPOLLOUT;
    }

    if (ev.events)
        ev.events |= EPOLLHUP | EPOLLERR;

    if (ev.events != F->epoll_state) {
        if (F->epoll_state) // already monitoring something.
            epoll_ctl_type = ev.events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        else
            epoll_ctl_type = EPOLL_CTL_ADD;

        F->epoll_state = ev.events;

        if (epoll_ctl(kdpfd, epoll_ctl_type, fd, &ev) < 0) {
            debugs(5, DEBUG_EPOLL ? 0 : 8, "commSetSelect: epoll_ctl(," << epolltype_atoi(epoll_ctl_type) <<
                   ",,): failed on FD " << fd << ": " << xstrerror());
        }
    }

    if (timeout)
        F->timeout = squid_curtime + timeout;
}