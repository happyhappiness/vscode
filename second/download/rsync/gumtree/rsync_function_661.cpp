static void read_check(int f)
{
	int n = 8192;

	if (f == -1) return;

	if (read_buffer_len == 0) {
		read_buffer_p = read_buffer;
	}

	if (n > MAX_READ_BUFFER/4)
		n = MAX_READ_BUFFER/4;

	if (read_buffer_p != read_buffer) {
		memmove(read_buffer,read_buffer_p,read_buffer_len);
		read_buffer_p = read_buffer;
	}

	if (n > (read_buffer_size - read_buffer_len)) {
		read_buffer_size += n;
		read_buffer = (char *)Realloc(read_buffer,read_buffer_size);
		if (!read_buffer) out_of_memory("read check");      
		read_buffer_p = read_buffer;      
	}

	n = read_unbuffered(f,read_buffer+read_buffer_len,n);
	read_buffer_len += n;
}