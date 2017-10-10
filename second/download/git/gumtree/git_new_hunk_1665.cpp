
const char *real_path_if_valid(const char *path)
{
	return real_path_internal(path, 0);
}

/*
 * Use this to get an absolute path from a relative one. If you want
 * to resolve links, you should use real_path.
 */
const char *absolute_path(const char *path)
{
	static struct strbuf sb = STRBUF_INIT;
	strbuf_reset(&sb);
	strbuf_add_absolute_path(&sb, path);
	return sb.buf;
}

/*
 * Unlike prefix_path, this should be used if the named file does
 * not have to interact with index entry; i.e. name of a random file
 * on the filesystem.
