const char *absolute_path(const char *path)
{
	static struct strbuf sb = STRBUF_INIT;
	strbuf_reset(&sb);
	strbuf_add_absolute_path(&sb, path);
	return sb.buf;
}