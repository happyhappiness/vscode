(r != 0) {
		errno = r;
		goto stdout_opened;
	}