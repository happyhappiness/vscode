int rsync_snprintf(char *str,size_t count,const char *fmt,...)
{
	size_t ret;
	va_list ap;
    
	va_start(ap, fmt);
	ret = vsnprintf(str, count, fmt, ap);
	va_end(ap);
	return ret;
}