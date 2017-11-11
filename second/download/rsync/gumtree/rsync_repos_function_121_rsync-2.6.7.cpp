void write_sbuf(int f, char *buf)
{
	writefd(f, buf, strlen(buf));
}