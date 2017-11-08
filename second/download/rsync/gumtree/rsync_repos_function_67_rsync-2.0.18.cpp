void read_sbuf(int f,char *buf,int len)
{
	read_buf(f,buf,len);
	buf[len] = 0;
}