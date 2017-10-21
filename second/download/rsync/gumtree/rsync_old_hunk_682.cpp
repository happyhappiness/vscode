
void io_printf(int fd, const char *format, ...)
{
	va_list ap;  
	char buf[1024];
	int len;
	
	va_start(ap, format);
	len = vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);

	if (len < 0) exit_cleanup(RERR_STREAMIO);

	write_sbuf(fd, buf);
}
