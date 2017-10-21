	s1 += (buf[i]+CHAR_OFFSET); s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}


void get_checksum2(char *buf, int32 len, char *sum)
{
	int32 i;
	static char *buf1;
	static int32 len1;
	struct mdfour m;

	if (len > len1) {
		if (buf1)
			free(buf1);
		buf1 = new_array(char, len+4);
		len1 = len;
		if (!buf1)
			out_of_memory("get_checksum2");
	}

	mdfour_begin(&m);

	memcpy(buf1,buf,len);
	if (checksum_seed) {
