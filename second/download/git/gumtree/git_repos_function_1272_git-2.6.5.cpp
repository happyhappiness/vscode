char *git_pathdup_submodule(const char *path, const char *fmt, ...)
{
	va_list args;
	struct strbuf buf = STRBUF_INIT;
	va_start(args, fmt);
	do_submodule_path(&buf, path, fmt, args);
	va_end(args);
	return strbuf_detach(&buf, NULL);
}