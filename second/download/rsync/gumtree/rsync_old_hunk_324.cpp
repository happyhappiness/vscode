      if (count == -1 && errno != EINTR) {
	      if (verbose > 1) 
		      fprintf(FERROR,"select error: %s\n", strerror(errno));
	      exit_cleanup(1);
      }

      if (count == 0) continue;
      
      if (FD_ISSET(fd, &w_fds)) {
	      got_select = 1;
      }
    } else {
      total += ret;
    }
  }

  return total;
}



void write_int(int f,int x)
