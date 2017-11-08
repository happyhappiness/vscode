void accept_mutex_on(void)
{
    int ret;

    while ((ret = flock(flock_fd, LOCK_EX)) < 0 && errno == EINTR)
        continue;

    if (ret < 0) {
        perror ("flock(LOCK_EX)");
        exit(1);
    }
}