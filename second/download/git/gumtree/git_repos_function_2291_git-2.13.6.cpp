int daemonize(void)
{
#ifdef NO_POSIX_GOODIES
	errno = ENOSYS;
	return -1;
#else
	switch (fork()) {
		case 0:
			break;
		case -1:
			die_errno("fork failed");
		default:
			exit(0);
	}
	if (setsid() == -1)
		die_errno("setsid failed");
	close(0);
	close(1);
	close(2);
	sanitize_stdfds();
	return 0;
#endif
}