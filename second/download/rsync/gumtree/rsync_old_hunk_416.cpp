
	write_int(f, -1);
	SIVAL(b,0,(x&0xFFFFFFFF));
	SIVAL(b,4,((x>>32)&0xFFFFFFFF));

	if ((ret=writefd(f,b,8)) != 8) {
		fprintf(FERROR,"write_longint failed : %s\n",
			ret==-1?strerror(errno):"EOF");
		exit_cleanup(1);
	}
	total_written += 8;
}

void write_buf(int f,char *buf,int len)
{
  int ret;
  if ((ret=writefd(f,buf,len)) != len) {
    fprintf(FERROR,"write_buf failed : %s\n",
	    ret==-1?strerror(errno):"EOF");
    exit_cleanup(1);
  }
  total_written += len;
}


void write_byte(int f,unsigned char c)
{
  write_buf(f,(char *)&c,1);
}

void write_flush(int f)
{
}


