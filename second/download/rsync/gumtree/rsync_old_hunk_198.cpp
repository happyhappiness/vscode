		fnametmp,fname,strerror(errno));
      }

      cleanup_fname = NULL;

      set_perms(fname,file,NULL,0);
    }

  if (verbose > 2)
    fprintf(FERROR,"recv_files finished\n");
  
  return 0;
