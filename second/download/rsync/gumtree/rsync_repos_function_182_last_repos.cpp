void write_sbuf(int f, const char *buf)
{
	write_buf(f, buf, strlen(buf));
}