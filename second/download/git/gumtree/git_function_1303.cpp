int unable_to_lock_error(const char *path, int err)
{
	struct strbuf buf = STRBUF_INIT;

	unable_to_lock_message(path, err, &buf);
	error("%s", buf.buf);
	strbuf_release(&buf);
	return -1;
}