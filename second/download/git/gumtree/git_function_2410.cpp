static int warn_if_unremovable(const char *op, const char *file, int rc)
{
	int err;
	if (!rc || errno == ENOENT)
		return 0;
	err = errno;
	warning("unable to %s %s: %s", op, file, strerror(errno));
	errno = err;
	return rc;
}