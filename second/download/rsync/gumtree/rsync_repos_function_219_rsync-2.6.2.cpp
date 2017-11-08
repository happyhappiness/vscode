size_t stringjoin(char *dest, size_t destsize, ...)
{
	va_list ap;
	size_t len, ret = 0;
	const char *src;

	va_start(ap, destsize);
	while (1) {
		if (!(src = va_arg(ap, const char *)))
			break;
		len = strlen(src);
		ret += len;
		if (destsize > 1) {
			if (len >= destsize)
				len = destsize - 1;
			memcpy(dest, src, len);
			destsize -= len;
			dest += len;
		}
	}
	*dest = '\0';
	va_end(ap);

	return ret;
}