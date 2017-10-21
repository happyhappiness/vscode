
    if (ret == 0) return total;

    if (ret == -1 && !(errno == EWOULDBLOCK || errno == EAGAIN)) 
      return -1;

    if (ret == -1 && got_select) {
	    /* hmmm, we got a write select on the fd and then failed to write.
	       Why doesn't that mean that the fd is dead? It doesn't on some
	       systems it seems (eg. IRIX) */
#if 0
	    fprintf(FERROR,"write exception\n");
	    exit_cleanup(1);
#endif
    }

    got_select = 0;


    if (ret == -1) {
      read_check(buffer_f_in);

      fd_count = fd+1;
      FD_ZERO(&w_fds);
      FD_ZERO(&r_fds);
      FD_SET(fd,&w_fds);
      if (buffer_f_in != -1) {
	      FD_SET(buffer_f_in,&r_fds);
	      if (buffer_f_in > fd) 
		      fd_count = buffer_f_in+1;
      }

      tv.tv_sec = BLOCKING_TIMEOUT;
      tv.tv_usec = 0;
      count = select(fd_count,buffer_f_in == -1? NULL: &r_fds,
		     &w_fds,NULL,&tv);
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
