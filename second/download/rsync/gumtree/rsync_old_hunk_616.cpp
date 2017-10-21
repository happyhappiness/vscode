			return -1;
		}
		sanitize_paths = 1;
	}

	if (am_root) {
		if (setgid(gid)) {
			rsyserr(FERROR, errno, "setgid %d failed", (int) gid);
			io_printf(fd,"@ERROR: setgid failed\n");
			return -1;
		}

