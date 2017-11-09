static int read_arg_from_pipe(int fd, char *buf, int limit)
{
	char *bp = buf, *eob = buf + limit - 1;

	while (1) {
		int got = read(fd, bp, 1);
		if (got != 1) {
			if (got < 0 && errno == EINTR)
				continue;
			return -1;
		}
		if (*bp == '\0')
			break;
		if (bp < eob)
			bp++;
	}
	*bp = '\0';

	return bp - buf;
}