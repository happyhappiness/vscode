static int warn_if_unremovable(const char *op, const char *file, int rc)
{
	if (rc < 0) {
		int err = errno;
		if (ENOENT != err) {
			warning("unable to %s %s: %s",
				op, file, strerror(errno));
			errno = err;
		}
	}
	return rc;
}