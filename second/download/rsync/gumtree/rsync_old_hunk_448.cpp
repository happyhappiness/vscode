	  if (buf) unmap_file(buf);
	  close(fd);
	  
	  free_sums(s);
	  
	  if (verbose > 2)
		  fprintf(FINFO,"sender finished %s\n",fname);
  }

  if (verbose > 2)
	  fprintf(FINFO,"send files finished\n");

  match_report();

  write_int(f_out,-1);
  write_flush(f_out);
}
