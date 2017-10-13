static void bug_die(int err, const char *msg)
{
	if (err) {
		errno = err;
		die_errno("BUG: %s", msg);
	}
}