static char *read_shell_var(FILE *fp, const char *key)
{
	struct strbuf sb = STRBUF_INIT;
	const char *str;

	if (strbuf_getline(&sb, fp, '\n'))
		goto fail;

	if (!skip_prefix(sb.buf, key, &str))
		goto fail;

	if (!skip_prefix(str, "=", &str))
		goto fail;

	strbuf_remove(&sb, 0, str - sb.buf);

	str = sq_dequote(sb.buf);
	if (!str)
		goto fail;

	return strbuf_detach(&sb, NULL);

fail:
	strbuf_release(&sb);
	return NULL;
}