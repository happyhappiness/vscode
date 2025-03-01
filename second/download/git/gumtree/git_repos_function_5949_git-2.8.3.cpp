struct tm *git_gmtime_r(const time_t *timep, struct tm *result)
{
	struct tm *ret;

	memset(result, 0, sizeof(*result));
	ret = gmtime_r(timep, result);

	/*
	 * Rather than NULL, FreeBSD gmtime simply leaves the "struct tm"
	 * untouched when it encounters overflow. Since "mday" cannot otherwise
	 * be zero, we can test this very quickly.
	 */
	if (ret && !ret->tm_mday) {
		ret = NULL;
		errno = EOVERFLOW;
	}

	return ret;
}