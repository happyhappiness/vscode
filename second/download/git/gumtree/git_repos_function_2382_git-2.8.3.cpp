int unlink_or_msg(const char *file, struct strbuf *err)
{
	int rc = unlink(file);

	assert(err);

	if (!rc || errno == ENOENT)
		return 0;

	strbuf_addf(err, "unable to unlink %s: %s",
		    file, strerror(errno));
	return -1;
}