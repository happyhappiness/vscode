			exit_cleanup(RERR_STREAMIO);
		}

		read_loop(fd, line, remaining);
		line[remaining] = 0;

		rprintf(tag,"%s", line);
		remaining = 0;
	}

	return ret;
}



/* This function was added to overcome a deadlock problem when using
 * ssh.  It looks like we can't allow our receive queue to get full or
 * ssh will clag up. Uggh.  */
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


/* do a buffered read from fd. don't return until all N bytes
   have been read. If all N can't be read then exit with an error */
static void readfd(int fd,char *buffer,size_t N)
{
	int  ret;
	int total=0;  
	
	if ((read_buffer_len < N) && (N < 1024)) {
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

		no_flush_read++;
		io_flush();
		no_flush_read--;

		ret = read_unbuffered(fd,buffer + total,N-total);
		total += ret;
	}

	stats.total_read += total;
