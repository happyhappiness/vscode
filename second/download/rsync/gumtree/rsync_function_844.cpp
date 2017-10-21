static void create_pid_file(void)
{
	char *pid_file = lp_pid_file();
	char pidbuf[16];
	pid_t pid = getpid();
	int fd;

	if (!pid_file || !*pid_file)
		return;

	cleanup_set_pid(pid);
	if ((fd = do_open(pid_file, O_WRONLY|O_CREAT|O_EXCL, 0666 & ~orig_umask)) == -1) {
		cleanup_set_pid(0);
		fprintf(stderr, "failed to create pid file %s: %s\n", pid_file, strerror(errno));
		rsyserr(FLOG, errno, "failed to create pid file %s", pid_file);
		exit_cleanup(RERR_FILEIO);
	}
	snprintf(pidbuf, sizeof pidbuf, "%ld\n", (long)pid);
	write(fd, pidbuf, strlen(pidbuf));
	close(fd);
}