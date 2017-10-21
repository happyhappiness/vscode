		else
			read_buffer = (char *)realloc(read_buffer,read_buffer_size);
		if (!read_buffer) out_of_memory("read check");      
		read_buffer_p = read_buffer;      
	}

	n = read_unbuffered(f,read_buffer+read_buffer_len,n);
	if (n > 0) {
		read_buffer_len += n;
	}
}

static int readfd(int fd,char *buffer,int N)
{
	int  ret;
	int total=0;  
	struct timeval tv;
	
