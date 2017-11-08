void get_checksum2(char *buf,int len,char *sum)
{
	int i;
	static char *buf1;
	static int len1;
	struct mdfour m;

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