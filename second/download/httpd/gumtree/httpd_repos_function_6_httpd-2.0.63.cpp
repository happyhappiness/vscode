void accept_mutex_init(void)
{

    printf("opening " FNAME " in current directory\n");
    flock_fd = open(FNAME, O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (flock_fd == -1)
    {
	perror ("open");
	fprintf (stderr, "Cannot open lock file: %s\n", "test-lock-thing");
	exit (1);
    }
}