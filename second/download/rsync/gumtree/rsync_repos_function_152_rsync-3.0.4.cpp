void write_buf(int f, const char *buf, size_t len)
{
	writefd(f,buf,len);
}