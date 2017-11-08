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