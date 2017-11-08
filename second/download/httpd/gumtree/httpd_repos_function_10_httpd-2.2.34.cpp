void accept_mutex_off(void)
{
    if (flock (flock_fd, LOCK_UN) < 0)
    {
        perror ("flock(LOCK_UN)");
        exit(1);
    }
}