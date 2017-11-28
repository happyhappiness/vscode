void
comm_lingering_close(int fd)
{
#if USE_SSL

    if (fd_table[fd].ssl)
        ssl_shutdown_method(fd);

#endif

    if (shutdown(fd, 1) < 0) {
        comm_close(fd);
        return;
    }

    fd_note(fd, "lingering close");
    commSetTimeout(fd, 10, commLingerTimeout, NULL);
    commSetSelect(fd, COMM_SELECT_READ, commLingerClose, NULL, 0);
}