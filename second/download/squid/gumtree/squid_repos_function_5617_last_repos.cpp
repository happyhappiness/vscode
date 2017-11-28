void
Comm::SelectLoopInit(void)
{
    /* allocate memory first before attempting to open poll device */
    /* This tracks the FD devpoll offset+state */
    devpoll_state = (struct _devpoll_state *)xcalloc(
                        SQUID_MAXFD, sizeof(struct _devpoll_state)
                    );

    /* And this is the stuff we use to read events */
    do_poll.dp_fds = (struct pollfd *)xcalloc(
                         DEVPOLL_QUERYSIZE, sizeof(struct pollfd)
                     );
    dpoll_nfds = DEVPOLL_QUERYSIZE;

    devpoll_update.pfds = (struct pollfd *)xcalloc(
                              DEVPOLL_UPDATESIZE, sizeof(struct pollfd)
                          );
    devpoll_update.cur = -1;
    devpoll_update.size = DEVPOLL_UPDATESIZE;

    /* attempt to open /dev/poll device */
    devpoll_fd = open("/dev/poll", O_RDWR);
    if (devpoll_fd < 0) {
        int xerrno = errno;
        fatalf("comm_select_init: can't open /dev/poll: %s\n", xstrerr(xerrno));
    }

    fd_open(devpoll_fd, FD_UNKNOWN, "devpoll ctl");

    commDevPollRegisterWithCacheManager();
}