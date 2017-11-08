int sparse_end(int f, OFF_T size)
{
	int ret;

	if (!sparse_seek)
		return 0;

#ifdef HAVE_FTRUNCATE
	ret = do_ftruncate(f, size);
#else
	if (do_lseek(f, sparse_seek-1, SEEK_CUR) != size-1)
		ret = -1;
	else {
		do {
			ret = write(f, "", 1);
		} while (ret < 0 && errno == EINTR);

		ret = ret <= 0 ? -1 : 0;
	}
#endif

	sparse_seek = 0;

	return ret;
}