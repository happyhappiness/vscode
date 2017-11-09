static int log_ref_write_fd(int fd, const struct object_id *old_oid,
			    const struct object_id *new_oid,
			    const char *committer, const char *msg)
{
	int msglen, written;
	unsigned maxlen, len;
	char *logrec;

	msglen = msg ? strlen(msg) : 0;
	maxlen = strlen(committer) + msglen + 100;
	logrec = xmalloc(maxlen);
	len = xsnprintf(logrec, maxlen, "%s %s %s\n",
			oid_to_hex(old_oid),
			oid_to_hex(new_oid),
			committer);
	if (msglen)
		len += copy_reflog_msg(logrec + len - 1, msg) - 1;

	written = len <= maxlen ? write_in_full(fd, logrec, len) : -1;
	free(logrec);
	if (written != len)
		return -1;

	return 0;
}