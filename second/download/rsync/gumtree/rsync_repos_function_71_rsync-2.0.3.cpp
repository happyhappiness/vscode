void write_sbuf(int f,char *buf)
{
	write_buf(f, buf, strlen(buf));
}