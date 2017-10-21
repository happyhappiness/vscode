		fnametmp,fname,strerror(errno));
      }

      cleanup_fname = NULL;

      set_perms(fname,file,NULL,0);

      if (!recv_ok) {
	if (verbose > 1)
	  fprintf(FERROR,"redoing %s(%d)\n",fname,i);
	write_int(f_gen,i);
      }
    }

  if (verbose > 2)
    fprintf(FERROR,"recv_files finished\n");
  
  return 0;
