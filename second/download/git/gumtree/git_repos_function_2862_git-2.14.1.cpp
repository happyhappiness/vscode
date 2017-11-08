void write_file(const char *path, const char *fmt, ...)
{
	va_list params;
	struct strbuf sb = STRBUF_INIT;

	va_start(params, fmt);
	strbuf_vaddf(&sb, fmt, params);
	va_end(params);

	strbuf_complete_line(&sb);

	write_file_buf(path, sb.buf, sb.len);
	strbuf_release(&sb);
}