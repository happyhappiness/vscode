	  return;
	}
      }
    }
    delete_file(fname);
    if (do_symlink(file->link,fname) != 0) {
      rprintf(FERROR,"link %s -> %s : %s\n",
	      fname,file->link,strerror(errno));
    } else {
      set_perms(fname,file,NULL,0);
      if (verbose) 
	rprintf(FINFO,"%s -> %s\n",
		fname,file->link);
    }
#endif
    return;
  }

