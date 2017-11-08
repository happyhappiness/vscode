char *mkpathdup(const char *fmt, ...)
{
	char *path;
	struct strbuf sb = STRBUF_INIT;
	va_list args;

	va_start(args, fmt);
	strbuf_vaddf(&sb, fmt, args);
	va_end(args);
	path = xstrdup(cleanup_path(sb.buf));

	strbuf_release(&sb);
	return path;
}