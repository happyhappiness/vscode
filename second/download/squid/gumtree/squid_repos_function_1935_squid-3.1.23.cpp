static void
comm_update_fd(int fd, int events)
{
    debugs(
        5,
        DEBUG_DEVPOLL ? 0 : 8,
        HERE << "FD " << fd << ", events=" << events
    );

    /* Is the array already full and in need of flushing? */
    if (devpoll_update.cur != -1 && (devpoll_update.cur == devpoll_update.size))
        comm_flush_updates();

    /* Push new event onto array */
    devpoll_update.cur++;
    devpoll_update.pfds[devpoll_update.cur].fd = fd;
    devpoll_update.pfds[devpoll_update.cur].events = events;
    devpoll_update.pfds[devpoll_update.cur].revents = 0;
}