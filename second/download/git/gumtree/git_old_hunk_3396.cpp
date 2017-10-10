		close(fdi);
		return fdo;
	}
	status = copy_fd(fdi, fdo);
	switch (status) {
	case COPY_READ_ERROR:
		error("copy-fd: read returned %s", strerror(errno));
		break;
	case COPY_WRITE_ERROR:
		error("copy-fd: write returned %s", strerror(errno));
		break;
	}
	close(fdi);
	if (close(fdo) != 0)
		return error("%s: close error: %s", dst, strerror(errno));

	if (!status && adjust_shared_perm(dst))
		return -1;

	return status;
}
