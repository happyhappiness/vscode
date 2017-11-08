uint32 get_checksum1(char *buf,int len)
{
    int i;
    uint32 s1, s2;

    s1 = s2 = 0;
    for (i = 0; i < (len-4); i+=4) {
	s2 += 4*(s1 + buf[i]) + 3*buf[i+1] + 2*buf[i+2] + buf[i+3];
	s1 += (buf[i+0] + buf[i+1] + buf[i+2] + buf[i+3]); 
    }
    for (; i < len; i++) {
	s1 += buf[i]; s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}