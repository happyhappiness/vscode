void accept_mutex_off(void)
{
    if (fcntl (fcntl_fd, F_SETLKW, &unlock_it) < 0)
    {
        perror ("fcntl unlock_it");
        exit(1);
    }
}