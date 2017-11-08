static int read_env_script(struct argv_array *env)
{
	struct strbuf script = STRBUF_INIT;
	int i, count = 0;
	char *p, *p2;

	if (strbuf_read_file(&script, rebase_path_author_script(), 256) <= 0)
		return -1;

	for (p = script.buf; *p; p++)
		if (skip_prefix(p, "'\\\\''", (const char **)&p2))
			strbuf_splice(&script, p - script.buf, p2 - p, "'", 1);
		else if (*p == '\'')
			strbuf_splice(&script, p-- - script.buf, 1, "", 0);
		else if (*p == '\n') {
			*p = '\0';
			count++;
		}

	for (i = 0, p = script.buf; i < count; i++) {
		argv_array_push(env, p);
		p += strlen(p) + 1;
	}

	return 0;
}