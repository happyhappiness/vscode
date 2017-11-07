int utf8_fprintf(FILE *stream, const char *format, ...)
{
	struct strbuf buf = STRBUF_INIT;
	va_list arg;
	int columns;

	va_start(arg, format);
	strbuf_vaddf(&buf, format, arg);
	va_end(arg);

	columns = fputs(buf.buf, stream);
	if (0 <= columns) /* keep the error from the I/O */
		columns = utf8_strwidth(buf.buf);
	strbuf_release(&buf);
	return columns;
}