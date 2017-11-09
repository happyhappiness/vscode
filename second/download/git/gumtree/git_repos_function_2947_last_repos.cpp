const char *real_path(const char *path)
{
	static struct strbuf realpath = STRBUF_INIT;
	return strbuf_realpath(&realpath, path, 1);
}