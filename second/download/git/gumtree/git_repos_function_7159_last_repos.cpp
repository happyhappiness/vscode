static char *get_stdin(void)
{
	struct strbuf buf = STRBUF_INIT;
	if (strbuf_read(&buf, 0, 1024) < 0) {
		die_errno("error reading standard input");
	}
	return strbuf_detach(&buf, NULL);
}