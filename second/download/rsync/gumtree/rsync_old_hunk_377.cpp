
      map = map_ptr(buf,offset2,len);

      see_token(map, len);
      sum_update(map,len);

      if (fd != -1 && write_sparse(fd,map,len) != len) {
	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
	exit_cleanup(1);
      }
      offset += len;
    }
  }
