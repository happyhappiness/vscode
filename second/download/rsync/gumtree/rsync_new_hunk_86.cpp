      if (verbose > 2)
	fprintf(stderr,"calling match_sums %s\n",fname);

      if (!am_server && verbose)
	printf("%s\n",fname);
      
      match_sums(f_out,s,buf,st.st_size);
      write_flush(f_out);
      
      unmap_file(buf,st.st_size);
      close(fd);

      free_sums(s);
