static void child_die(enum child_errcode err)
{
	struct child_err buf;

	buf.err = err;
	buf.syserr = errno;

	/* write(2) on buf smaller than PIPE_BUF (min 512) is atomic: */
	xwrite(child_notifier, &buf, sizeof(buf));
	_exit(1);
}