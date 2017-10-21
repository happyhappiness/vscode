	int fd, len;

	if (!pid_file || !*pid_file)
		return;

	cleanup_set_pid(pid);
	if ((fd = do_open(pid_file, O_WRONLY|O_CREAT|O_EXCL, 0666)) == -1) {
	  failure:
		cleanup_set_pid(0);
		fprintf(stderr, "failed to create pid file %s: %s\n", pid_file, strerror(errno));
		rsyserr(FLOG, errno, "failed to create pid file %s", pid_file);
		exit_cleanup(RERR_FILEIO);
	}
	snprintf(pidbuf, sizeof pidbuf, "%d\n", (int)pid);
	len = strlen(pidbuf);
	if (write(fd, pidbuf, len) != len)
		goto failure;
	close(fd);
}

