static int show_all_config(const char *key_, const char *value_, void *cb)
{
	if (show_origin) {
		struct strbuf buf = STRBUF_INIT;
		show_config_origin(&buf);
		/* Use fwrite as "buf" can contain \0's if "end_null" is set. */
		fwrite(buf.buf, 1, buf.len, stdout);
		strbuf_release(&buf);
	}
	if (!omit_values && value_)
		printf("%s%c%s%c", key_, delim, value_, term);
	else
		printf("%s%c", key_, term);
	return 0;
}