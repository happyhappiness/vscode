void file_checksum(const char *fname, const STRUCT_STAT *st_p, char *sum)
{
	struct map_struct *buf;
	OFF_T i, len = st_p->st_size;
	md_context m;
	int32 remainder;
	int fd;

	memset(sum, 0, MAX_DIGEST_LEN);

	fd = do_open(fname, O_RDONLY, 0);
	if (fd == -1)
		return;

	buf = map_file(fd, len, MAX_MAP_SIZE, CSUM_CHUNK);

	if (protocol_version >= 30) {
		md5_begin(&m);

		for (i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
			md5_update(&m, (uchar *)map_ptr(buf, i, CSUM_CHUNK),
				   CSUM_CHUNK);
		}

		remainder = (int32)(len - i);
		if (remainder > 0)
			md5_update(&m, (uchar *)map_ptr(buf, i, remainder), remainder);

		md5_result(&m, (uchar *)sum);
	} else {
		mdfour_begin(&m);

		for (i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
			mdfour_update(&m, (uchar *)map_ptr(buf, i, CSUM_CHUNK),
				      CSUM_CHUNK);
		}

		/* Prior to version 27 an incorrect MD4 checksum was computed
		 * by failing to call mdfour_tail() for block sizes that
		 * are multiples of 64.  This is fixed by calling mdfour_update()
		 * even when there are no more bytes. */
		remainder = (int32)(len - i);
		if (remainder > 0 || protocol_version >= 27)
			mdfour_update(&m, (uchar *)map_ptr(buf, i, remainder), remainder);

		mdfour_result(&m, (uchar *)sum);
	}

	close(fd);
	unmap_file(buf);
}