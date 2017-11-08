char *alias_lookup(const char *alias)
{
	char *v = NULL;
	struct strbuf key = STRBUF_INIT;
	strbuf_addf(&key, "alias.%s", alias);
	git_config_get_string(key.buf, &v);
	strbuf_release(&key);
	return v;
}