char *rep_inet_ntoa(struct in_addr ip)
{
	unsigned char *p = (unsigned char *)&ip.s_addr;
	static char buf[18];
#ifdef WORDS_BIGENDIAN
	snprintf(buf, 18, "%d.%d.%d.%d", 
		 (int)p[0], (int)p[1], (int)p[2], (int)p[3]);
#else
	snprintf(buf, 18, "%d.%d.%d.%d", 
		 (int)p[3], (int)p[2], (int)p[1], (int)p[0]);
#endif
	return buf;
}