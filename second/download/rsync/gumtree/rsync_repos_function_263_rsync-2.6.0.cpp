void file_checksum(char *fname,char *sum,OFF_T size)
{
	OFF_T i;
	struct map_struct *buf;
	int fd;
	OFF_T len = size;
	char tmpchunk[CSUM_CHUNK];
	struct mdfour m;
	
	memset(sum,0,MD4_SUM_LENGTH);
	
	fd = do_open(fname, O_RDONLY, 0);
	if (fd == -1) return;
	
	buf = map_file(fd,size);
	
	mdfour_begin(&m);

	for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
		memcpy(tmpchunk, map_ptr(buf,i,CSUM_CHUNK), CSUM_CHUNK);
		mdfour_update(&m, (uchar *)tmpchunk, CSUM_CHUNK);
	}

	/*
	 * Prior to version 27 an incorrect MD4 checksum was computed
	 * by failing to call mdfour_tail() for block sizes that
	 * are multiples of 64.  This is fixed by calling mdfour_update()
	 * even when there are no more bytes.
	 */
	if (len - i > 0) {
		memcpy(tmpchunk, map_ptr(buf,i,len-i), len-i);
	}
	if (len - i > 0 || protocol_version >= 27) {
		mdfour_update(&m, (uchar *)tmpchunk, (len-i));
	}

	mdfour_result(&m, (uchar *)sum);

	close(fd);
	unmap_file(buf);
}