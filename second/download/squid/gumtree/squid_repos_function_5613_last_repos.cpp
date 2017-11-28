static void
comm_flush_updates(void)
{
    int i;
    if (devpoll_update.cur == -1)
        return; /* array of changes to make is empty */

    debugs(
        5,
        DEBUG_DEVPOLL ? 0 : 8,
        HERE << (devpoll_update.cur + 1) << " fds queued"
    );

    i = write(
            devpoll_fd, /* open handle to /dev/poll */
            devpoll_update.pfds, /* pointer to array of struct pollfd */
            (devpoll_update.cur + 1) * sizeof(struct pollfd) /* bytes to process */
        );
    assert(i > 0);
    assert(static_cast<size_t>(i) == (sizeof(struct pollfd) * (devpoll_update.cur + 1)));
    devpoll_update.cur = -1; /* reset size of array, no elements remain */
}