		close(fdi);
		return fdo;
	}
	status = copy_fd(fdi, fdo);
	switch (status) {
	case COPY_READ_ERROR:
		error_errno("copy-fd: read returned");
		break;
	case COPY_WRITE_ERROR:
		error_errno("copy-fd: write returned");
		break;
	}
	close(fdi);
	if (close(fdo) != 0)
		return error_errno("%s: close error", dst);

	if (!status && adjust_shared_perm(dst))
		return -1;

	return status;
}
