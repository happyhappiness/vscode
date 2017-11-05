void strbuf_git_path_submodule(struct strbuf *buf, const char *path,
			       const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	do_submodule_path(buf, path, fmt, args);
	va_end(args);
}