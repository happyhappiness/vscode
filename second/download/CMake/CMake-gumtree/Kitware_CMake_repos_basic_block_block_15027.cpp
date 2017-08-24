{
		myfd = open(name, O_RDONLY | O_NONBLOCK | O_BINARY | O_CLOEXEC);
		__archive_ensure_cloexec_flag(myfd);
	}