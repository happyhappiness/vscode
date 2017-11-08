void accept_mutex_on(void)
{
    int ret;

    while ((ret = fcntl(fcntl_fd, F_SETLKW, &lock_it)) < 0 && errno == EINTR)
        continue;

    if (ret < 0) {
        perror ("fcntl lock_it");
        exit(1);
    }
}