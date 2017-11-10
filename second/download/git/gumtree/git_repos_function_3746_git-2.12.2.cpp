static void env_append(struct argv_array *env, const char *key, const char *val)
{
	struct strbuf quoted = STRBUF_INIT;
	const char *old;

	/*
	 * Avoid quoting if it's not necessary, for maximum compatibility
	 * with older parsers which don't understand the quoting.
	 */
	if (*val == '"' || strchr(val, PATH_SEP)) {
		strbuf_addch(&quoted, '"');
		quote_c_style(val, &quoted, NULL, 1);
		strbuf_addch(&quoted, '"');
		val = quoted.buf;
	}

	old = getenv(key);
	if (!old)
		argv_array_pushf(env, "%s=%s", key, val);
	else
		argv_array_pushf(env, "%s=%s%c%s", key, old, PATH_SEP, val);

	strbuf_release(&quoted);
}