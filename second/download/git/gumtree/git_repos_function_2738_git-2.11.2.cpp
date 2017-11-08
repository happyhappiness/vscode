static char **read_author_script(void)
{
	struct strbuf script = STRBUF_INIT;
	int i, count = 0;
	char *p, *p2, **env;
	size_t env_size;

	if (strbuf_read_file(&script, rebase_path_author_script(), 256) <= 0)
		return NULL;

	for (p = script.buf; *p; p++)
		if (skip_prefix(p, "'\\\\''", (const char **)&p2))
			strbuf_splice(&script, p - script.buf, p2 - p, "'", 1);
		else if (*p == '\'')
			strbuf_splice(&script, p-- - script.buf, 1, "", 0);
		else if (*p == '\n') {
			*p = '\0';
			count++;
		}

	env_size = (count + 1) * sizeof(*env);
	strbuf_grow(&script, env_size);
	memmove(script.buf + env_size, script.buf, script.len);
	p = script.buf + env_size;
	env = (char **)strbuf_detach(&script, NULL);

	for (i = 0; i < count; i++) {
		env[i] = p;
		p += strlen(p) + 1;
	}
	env[count] = NULL;

	return env;
}