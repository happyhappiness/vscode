void write_sbuf(int f, const char *buf)
{
	writefd(f, buf, strlen(buf));
}