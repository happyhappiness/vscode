void read_sbuf(int f,char *buf,size_t len)
{
	readfd(f, buf, len);
	buf[len] = '\0';
}