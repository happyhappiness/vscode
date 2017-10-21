	  exit(1);
	}
      }

      /* move tmp file over real file */
      if (rename(fnametmp,fname) != 0) {
	fprintf(stderr,"rename %s -> %s : %s\n",
		fnametmp,fname,strerror(errno));
      }

      unmap_file(buf,st.st_size);

      set_perms(fname,&flist->files[i],NULL,0);
    }

  if (verbose > 2)
    fprintf(stderr,"recv_files finished\n");
  
  return 0;
