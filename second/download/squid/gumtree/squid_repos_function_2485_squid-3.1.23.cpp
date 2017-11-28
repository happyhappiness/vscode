void
kq_update_events(int fd, short filter, PF * handler)
{
    PF *cur_handler;
    int kep_flags;

    switch (filter) {

    case EVFILT_READ:
        cur_handler = fd_table[fd].read_handler;
        break;

    case EVFILT_WRITE:
        cur_handler = fd_table[fd].write_handler;
        break;

    default:
        /* XXX bad! -- adrian */
        return;
        break;
    }

    if ((cur_handler == NULL && handler != NULL)
            || (cur_handler != NULL && handler == NULL)) {

        struct kevent *kep;

        kep = kqlst + kqoff;

        if (handler != NULL) {
            kep_flags = (EV_ADD | EV_ONESHOT);
        } else {
            kep_flags = EV_DELETE;
        }

        EV_SET(kep, (uintptr_t) fd, filter, kep_flags, 0, 0, 0);

        /* Check if we've used the last one. If we have then submit them all */
        if (kqoff == kqmax - 1) {
            int ret;

            ret = kevent(kq, kqlst, kqmax, NULL, 0, &zero_timespec);
            /* jdc -- someone needs to do error checking... */

            if (ret == -1) {
                perror("kq_update_events(): kevent()");
                return;
            }

            kqoff = 0;
        } else {
            kqoff++;
        }
    }
}