void accept_mutex_child_init(void)
{
    flock_fd = open(FNAME, O_WRONLY, 0600);
    if (flock_fd == -1) {
        perror("open");
        exit(1);
    }
}