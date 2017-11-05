void
accept_mutex_init(void)
{

    lock_it.l_whence = SEEK_SET;   /* from current point */
    lock_it.l_start  = 0;          /* -"- */
    lock_it.l_len    = 0;          /* until end of file */
    lock_it.l_type   = F_WRLCK;    /* set exclusive/write lock */
    lock_it.l_pid    = 0;          /* pid not actually interesting */
    unlock_it.l_whence = SEEK_SET; /* from current point */
    unlock_it.l_start  = 0;        /* -"- */
    unlock_it.l_len    = 0;        /* until end of file */
    unlock_it.l_type   = F_UNLCK;  /* set exclusive/write lock */
    unlock_it.l_pid    = 0;        /* pid not actually interesting */

    printf("opening test-lock-thing in current directory\n");
    fcntl_fd = open("test-lock-thing", O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (fcntl_fd == -1)
    {
        perror ("open");
        fprintf (stderr, "Cannot open lock file: %s\n", "test-lock-thing");
        exit (1);
    }
    unlink("test-lock-thing");
}