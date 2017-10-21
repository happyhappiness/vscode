		memmove(read_buffer,read_buffer_p,read_buffer_len);
		read_buffer_p = read_buffer;
	}

	if (n > (read_buffer_size - read_buffer_len)) {
		read_buffer_size += n;
		if (!read_buffer)
			read_buffer = (char *)malloc(read_buffer_size);
		else
			read_buffer = (char *)realloc(read_buffer,read_buffer_size);
		if (!read_buffer) out_of_memory("read check");      
		read_buffer_p = read_buffer;      
	}

	n = read_unbuffered(f,read_buffer+read_buffer_len,n);
	read_buffer_len += n;
