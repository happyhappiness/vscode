const char *real_path_if_valid(const char *path)
{
	static struct strbuf realpath = STRBUF_INIT;
	return strbuf_realpath(&realpath, path, 0);
}