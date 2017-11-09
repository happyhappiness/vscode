char *absolute_pathdup(const char *path)
{
	struct strbuf sb = STRBUF_INIT;
	strbuf_add_absolute_path(&sb, path);
	return strbuf_detach(&sb, NULL);
}