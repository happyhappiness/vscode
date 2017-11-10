void accept_mutex_init(void)
{
    pthread_mutexattr_t mattr;
    int fd;

    fd = open ("/dev/zero", O_RDWR);
    if (fd == -1) {
	perror ("open(/dev/zero)");
	exit (1);
    }
    mutex = (pthread_mutex_t *)mmap ((caddr_t)0, sizeof (*mutex),
		    PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mutex == (void *)(caddr_t)-1) {
	perror ("mmap");
	exit (1);
    }
    close (fd);
    if (pthread_mutexattr_init(&mattr)) {
	perror ("pthread_mutexattr_init");
	exit (1);
    }
    if (pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED)) {
	perror ("pthread_mutexattr_setpshared");
	exit (1);
    }
    if (pthread_mutex_init(mutex, &mattr)) {
	perror ("pthread_mutex_init");
	exit (1);
    }
    sigfillset(&accept_block_mask);
    sigdelset(&accept_block_mask, SIGHUP);
    sigdelset(&accept_block_mask, SIGTERM);
    sigdelset(&accept_block_mask, SIGUSR1);
}