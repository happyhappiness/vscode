	if (ifd == -1) {
		fprintf(FERROR,"open %s: %s\n",
			source,strerror(errno));
		return -1;
	}

	if (do_unlink(dest) && errno != ENOENT) {
		fprintf(FERROR,"unlink %s: %s\n",
			dest,strerror(errno));
		return -1;
	}

	ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode);
	if (ofd < 0) {
		fprintf(FERROR,"open %s: %s\n",
			dest,strerror(errno));
		close(ifd);
		return -1;
	}
