void read_sbuf(int f, char *buf, size_t len)
{
	read_buf(f, buf, len);
	buf[len] = '\0';
}