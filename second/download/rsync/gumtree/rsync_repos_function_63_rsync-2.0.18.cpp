static void readfd(int fd,char *buffer,int N)
{
	int  ret;
	int total=0;  
	
	if (read_buffer_len < N && N < 1024) {
		read_check(buffer_f_in);
	}
	
	while (total < N) {
		if (read_buffer_len > 0 && buffer_f_in == fd) {
			ret = MIN(read_buffer_len,N-total);
			memcpy(buffer+total,read_buffer_p,ret);
			read_buffer_p += ret;
			read_buffer_len -= ret;
			total += ret;
			continue;
		} 

		io_flush();

		ret = read_unbuffered(fd,buffer + total,N-total);
		total += ret;
	}
}