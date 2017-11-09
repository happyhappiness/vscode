int git_vsnprintf(char *str, size_t maxsize, const char *format, va_list ap)
{
	va_list cp;
	char *s;
	int ret = -1;

	if (maxsize > 0) {
		va_copy(cp, ap);
		ret = vsnprintf(str, maxsize-SNPRINTF_SIZE_CORR, format, cp);
		va_end(cp);
		if (ret == maxsize-1)
			ret = -1;
		/* Windows does not NUL-terminate if result fills buffer */
		str[maxsize-1] = 0;
	}
	if (ret != -1)
		return ret;

	s = NULL;
	if (maxsize < 128)
		maxsize = 128;

	while (ret == -1) {
		maxsize *= 4;
		str = realloc(s, maxsize);
		if (! str)
			break;
		s = str;
		va_copy(cp, ap);
		ret = vsnprintf(str, maxsize-SNPRINTF_SIZE_CORR, format, cp);
		va_end(cp);
		if (ret == maxsize-1)
			ret = -1;
	}
	free(s);
	return ret;
}