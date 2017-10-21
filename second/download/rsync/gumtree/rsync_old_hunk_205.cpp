      if (read_buffer_len > 0) {
	ret = MIN(read_buffer_len,N-total);
	memcpy(buffer+total,read_buffer_p,ret);
	read_buffer_p += ret;
	read_buffer_len -= ret;
      } else {
	ret = read(fd,buffer + total,N - total);
      }

      if (ret <= 0)
	return total;
      total += ret;
    }
  return total;
}


int read_int(int f)
{
  char b[4];
  if (readfd(f,b,4) != 4) {
    if (verbose > 1) 
      fprintf(stderr,"Error reading %d bytes : %s\n",4,strerror(errno));
    exit(1);
  }
  total_read += 4;
  return IVAL(b,0);
}

void read_buf(int f,char *buf,int len)
{
  if (readfd(f,buf,len) != len) {
    if (verbose > 1) 
      fprintf(stderr,"Error reading %d bytes : %s\n",len,strerror(errno));
    exit(1);
  }
  total_read += len;
}

unsigned char read_byte(int f)
