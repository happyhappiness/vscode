static ssize_t read_xattr(int attrfd, void *buf, size_t buflen)
{
	STRUCT_STAT sb;
	ssize_t ret;

	if (fstat(attrfd, &sb) < 0)
		ret = -1;
	else if (sb.st_size > SSIZE_MAX) {
		errno = ERANGE;
		ret = -1;
	} else if (buflen == 0)
		ret = sb.st_size;
	else if (sb.st_size > buflen) {
		errno = ERANGE;
		ret = -1;
	} else {
		size_t bufpos;
		for (bufpos = 0; bufpos < sb.st_size; ) {
			ssize_t cnt = read(attrfd, buf + bufpos, sb.st_size - bufpos);
			if (cnt <= 0) {
				if (cnt < 0 && errno == EINTR)
					continue;
				bufpos = -1;
				break;
			}
			bufpos += cnt;
		}
		ret = bufpos;
	}

	close(attrfd);

	return ret;
}