{
		if (read(fd, &rdat, KEYSIZE) == KEYSIZE)
			done = 1;
		(void)close(fd);
	}