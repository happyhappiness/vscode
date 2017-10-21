	if (len > len1) {
		if (buf1) free(buf1);
		buf1 = new_array(char, len+4);
		len1 = len;
		if (!buf1) out_of_memory("get_checksum2");
	}
	
	mdfour_begin(&m);
	
	memcpy(buf1,buf,len);
	if (checksum_seed) {
		SIVAL(buf1,len,checksum_seed);
		len += 4;
	}
	
	for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
		mdfour_update(&m, (uchar *)(buf1+i), CSUM_CHUNK);
	}
	/*
	 * Prior to version 27 an incorrect MD4 checksum was computed
	 * by failing to call mdfour_tail() for block sizes that
	 * are multiples of 64.  This is fixed by calling mdfour_update()
	 * even when there are no more bytes.
	 */
	if (len - i > 0 || protocol_version >= 27) {
		mdfour_update(&m, (uchar *)(buf1+i), (len-i));
	}
	
	mdfour_result(&m, (uchar *)sum);
}


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


static int sumresidue;
static char sumrbuf[CSUM_CHUNK];
static struct mdfour md;

void sum_init(void)
{
	char s[4];
	mdfour_begin(&md);
	sumresidue=0;
	SIVAL(s,0,checksum_seed);
	sum_update(s,4);
}

/**
 * Feed data into an MD4 accumulator, md.  The results may be
 * retrieved using sum_end().  md is used for different purposes at
 * different points during execution.
