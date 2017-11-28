comm_err_t
comm_select(int msec)
{
    int num, i;

    static struct kevent ke[KE_LENGTH];

    struct timespec poll_time;

    if (msec > max_poll_time)
        msec = max_poll_time;

    poll_time.tv_sec = msec / 1000;

    poll_time.tv_nsec = (msec % 1000) * 1000000;

    for (;;) {
        num = kevent(kq, kqlst, kqoff, ke, KE_LENGTH, &poll_time);
        ++statCounter.select_loops;
        kqoff = 0;

        if (num >= 0)
            break;

        if (ignoreErrno(errno))
            break;

        getCurrentTime();

        return COMM_ERROR;

        /* NOTREACHED */
    }

    getCurrentTime();

    if (num == 0)
        return COMM_OK;		/* No error.. */

    for (i = 0; i < num; i++) {
        int fd = (int) ke[i].ident;
        PF *hdl = NULL;
        fde *F = &fd_table[fd];

        if (ke[i].flags & EV_ERROR) {
            errno = ke[i].data;
            /* XXX error == bad! -- adrian */
            continue;        /* XXX! */
        }

        switch (ke[i].filter) {

        case EVFILT_READ:

            if ((hdl = F->read_handler) != NULL) {
                F->read_handler = NULL;
                F->flags.read_pending = 0;
                hdl(fd, F->read_data);
            }

            break;

        case EVFILT_WRITE:

            if ((hdl = F->write_handler) != NULL) {
                F->write_handler = NULL;
                hdl(fd, F->write_data);
            }

            break;

        default:
            /* Bad! -- adrian */
            debugs(5, 1, "comm_select: kevent returned " << ke[i].filter << "!");
            break;
        }
    }

    return COMM_OK;
}