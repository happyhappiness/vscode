      if (unlink(fname) != 0) {
	fprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
	return;
      }
      statret = -1;
    }
    if (statret != 0 && mkdir(fname,file->mode) != 0 && errno != EEXIST)
      fprintf(FERROR,"mkdir %s : %s\n",fname,strerror(errno));
    if (set_perms(fname,file,NULL,0) && verbose) 
      fprintf(FINFO,"%s/\n",fname);
    return;
  }

#if SUPPORT_LINKS
