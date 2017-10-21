	s1 += (buf[i]+CHAR_OFFSET); s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}


void get_checksum2(char *buf,int len,char *sum)
{
	int i;
	static char *buf1;
	static int len1;
	struct mdfour m;

	if (len > len1) {
		if (buf1) free(buf1);
		buf1 = (char *)malloc(len+4);
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
	if (len - i > 0) {
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
	
	memset(sum,0,csum_length);
	
	fd = open(fname,O_RDONLY);
	if (fd == -1) return;
	
	buf = map_file(fd,size);
	
	mdfour_begin(&m);

	for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
		memcpy(tmpchunk, map_ptr(buf,i,CSUM_CHUNK), CSUM_CHUNK);
		mdfour_update(&m, (uchar *)tmpchunk, CSUM_CHUNK);
	}

	if (len - i > 0) {
		memcpy(tmpchunk, map_ptr(buf,i,len-i), len-i);
		mdfour_update(&m, (uchar *)tmpchunk, (len-i));
	}

	mdfour_result(&m, (uchar *)sum);

	close(fd);
	unmap_file(buf);
}


void checksum_init(void)
{
  if (remote_version >= 14)
