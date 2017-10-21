		int fd;
		int pid = (int) getpid();
		cleanup_set_pid(pid);
		if ((fd = do_open(lp_pid_file(), O_WRONLY|O_CREAT|O_TRUNC,
					0666 & ~orig_umask)) == -1) {
		    cleanup_set_pid(0);
		    rprintf(FLOG,"failed to create pid file %s\n", pid_file);
		    exit_cleanup(RERR_FILEIO);
		}
		slprintf(pidbuf, sizeof(pidbuf), "%d\n", pid);
		write(fd, pidbuf, strlen(pidbuf));
		close(fd);
	}
