void become_daemon(void)
{
	if (fork())
		_exit(0);

	/* detach from the terminal */
#ifdef HAVE_SETSID
	setsid();
#else
#ifdef TIOCNOTTY
	{
		int i = open("/dev/tty", O_RDWR);
		if (i >= 0) 
			{
				ioctl(i, (int) TIOCNOTTY, (char *)0);      
				close(i);
			}
	}
#endif /* TIOCNOTTY */
#endif
	close(0);
	close(1);
	close(2);
}