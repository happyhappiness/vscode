			exit_cleanup(RERR_STREAMIO);
		}

		read_loop(fd, line, remaining);
		line[remaining] = 0;

		rprintf((enum logcode)tag,"%s", line);
		remaining = 0;
	}

	return ret;
}


/* do a buffered read from fd. don't return until all N bytes
   have been read. If all N can't be read then exit with an error */
static void readfd(int fd,char *buffer,int N)
{
	int  ret;
	int total=0;  
	
	while (total < N) {
		io_flush();

		ret = read_unbuffered(fd,buffer + total,N-total);
		total += ret;
	}

	stats.total_read += total;
