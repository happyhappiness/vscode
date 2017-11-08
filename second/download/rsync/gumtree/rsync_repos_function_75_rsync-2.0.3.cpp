void io_printf(int fd, const char *format, ...)
{
	va_list ap;  
	char buf[1024];
	int len;
	
	va_start(ap, format);

#if HAVE_VSNPRINTF
	len = vsnprintf(buf, sizeof(buf)-1, format, ap);
#else
	vsprintf(buf, format, ap);
	len = strlen(buf);
#endif
	va_end(ap);

	if (len < 0) exit_cleanup(1);

	write_sbuf(fd, buf);
}