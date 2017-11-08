void become_daemon(void)
{
	int i;

	if (fork()) {
		_exit(0);
	}

	/* detach from the terminal */
#ifdef HAVE_SETSID
	setsid();
#else
#ifdef TIOCNOTTY
	i = open("/dev/tty", O_RDWR);
	if (i >= 0) {
		ioctl(i, (int) TIOCNOTTY, (char *)0);      
		close(i);
	}
#endif /* TIOCNOTTY */
#endif
	/* make sure that stdin, stdout an stderr don't stuff things
           up (library functions, for example) */
	for (i=0;i<3;i++) {
		close(i); 
		open("/dev/null", O_RDWR);
	}
}