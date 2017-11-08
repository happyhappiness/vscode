static const char *
inet_ntop4(const unsigned char *src, char *dst, apr_size_t size)
{
	const apr_size_t MIN_SIZE = 16; /* space for 255.255.255.255\0 */
	int n = 0;
	char *next = dst;

	if (size < MIN_SIZE) {
	    errno = ENOSPC;
	    return NULL;
	}
	do {
	    unsigned char u = *src++;
	    if (u > 99) {
		*next++ = '0' + u/100;
		u %= 100;
		*next++ = '0' + u/10;
		u %= 10;
	    }
	    else if (u > 9) {
		*next++ = '0' + u/10;
		u %= 10;
	    }
	    *next++ = '0' + u;
	    *next++ = '.';
	    n++;
	} while (n < 4);
	*--next = 0;
	return dst;
}