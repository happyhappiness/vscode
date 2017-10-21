  if (io_timeout)
	  last_io = time(NULL);

  return total;
}

static char *io_buffer;
static int io_buffer_count;

void io_start_buffering(int fd)
{
	io_buffer = (char *)malloc(IO_BUFFER_SIZE);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;
}

void io_end_buffering(int fd)
{
	if (io_buffer_count) {
		if (writefd_unbuffered(fd, io_buffer, 
				       io_buffer_count) != 
		    io_buffer_count) {
			rprintf(FERROR,"write failed\n");
			exit_cleanup(1);
		}
		io_buffer_count = 0;
	}
	free(io_buffer);
	io_buffer = NULL;
}

static int writefd(int fd,char *buf,int len1)
{
	int len = len1;

	if (!io_buffer) return writefd_unbuffered(fd, buf, len);

	while (len) {
		int n = MIN(len, IO_BUFFER_SIZE-io_buffer_count);
		if (n > 0) {
			memcpy(io_buffer+io_buffer_count, buf, n);
			buf += n;
			len -= n;
			io_buffer_count += n;
		}
		
		if (io_buffer_count == IO_BUFFER_SIZE) {
			if (writefd_unbuffered(fd, io_buffer, 
					       io_buffer_count) != 
			    io_buffer_count) {
				return -1;
			}
			io_buffer_count = 0;
		}
	}

	return len1;
}


void write_int(int f,int32 x)
{
  int ret;
  char b[4];
