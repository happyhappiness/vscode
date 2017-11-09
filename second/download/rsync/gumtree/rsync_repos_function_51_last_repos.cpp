static int write_sparse(int f, char *buf, int len)
{
	int l1 = 0, l2 = 0;
	int ret;

	for (l1 = 0; l1 < len && buf[l1] == 0; l1++) {}
	for (l2 = 0; l2 < len-l1 && buf[len-(l2+1)] == 0; l2++) {}

	sparse_seek += l1;

	if (l1 == len)
		return len;

	if (sparse_seek)
		do_lseek(f, sparse_seek, SEEK_CUR);
	sparse_seek = l2;

	while ((ret = write(f, buf + l1, len - (l1+l2))) <= 0) {
		if (ret < 0 && errno == EINTR)
			continue;
		sparse_seek = 0;
		return ret;
	}

	if (ret != (int)(len - (l1+l2))) {
		sparse_seek = 0;
		return l1+ret;
	}

	return len;
}