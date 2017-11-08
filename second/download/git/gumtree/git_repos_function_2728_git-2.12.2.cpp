char *real_pathdup(const char *path, int die_on_error)
{
	struct strbuf realpath = STRBUF_INIT;
	char *retval = NULL;

	if (strbuf_realpath(&realpath, path, die_on_error))
		retval = strbuf_detach(&realpath, NULL);

	strbuf_release(&realpath);

	return retval;
}