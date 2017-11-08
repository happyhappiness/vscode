int sparse_end(int f)
{
	int ret;

	if (!sparse_seek)
		return 0;

	do_lseek(f, sparse_seek-1, SEEK_CUR);
	sparse_seek = 0;

	do {
		ret = write(f, "", 1);
	} while (ret < 0 && errno == EINTR);

	return ret <= 0 ? -1 : 0;
}