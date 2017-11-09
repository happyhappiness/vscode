void fsync_or_die(int fd, const char *msg)
{
	if (fsync(fd) < 0) {
		die_errno("fsync error on '%s'", msg);
	}
}