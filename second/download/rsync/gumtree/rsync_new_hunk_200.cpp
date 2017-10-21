      if (!am_server && verbose)
	printf("%s\n",fname);
      
      match_sums(f_out,s,buf,st.st_size);
      write_flush(f_out);
      
      if (buf) unmap_file(buf);
      close(fd);

      free_sums(s);

      if (verbose > 2)
	fprintf(FERROR,"sender finished %s\n",fname);
