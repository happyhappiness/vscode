int vasprintf(char **ptr, const char *format, va_list ap)
{
	int ret;
	va_list ap2;

	VA_COPY(ap2, ap);
	ret = vsnprintf(NULL, 0, format, ap2);
	va_end(ap2);
	if (ret < 0) return ret;

	(*ptr) = (char *)malloc(ret+1);
	if (!*ptr) return -1;

	VA_COPY(ap2, ap);
	ret = vsnprintf(*ptr, ret+1, format, ap2);
	va_end(ap2);

	return ret;
}