	  if (do_lchown(fname,
			(am_root&&preserve_uid)?file->uid:-1,
			preserve_gid?file->gid:-1) != 0) {
		  if (preserve_uid && st->st_uid != file->uid)
			  updated = 1;
		  if (verbose>1 || preserve_uid)
			  rprintf(FERROR,"chown %s : %s\n",
				  fname,strerror(errno));
		  return updated;
	  }
	  updated = 1;
  }
    
  if (verbose > 1 && report) {
	  if (updated)
		  rprintf(FINFO,"%s\n",fname);
	  else
		  rprintf(FINFO,"%s is uptodate\n",fname);
  }
  return updated;
}


/* choose whether to skip a particular file */
static int skip_file(char *fname,
		     struct file_struct *file, STRUCT_STAT *st)
{
	if (st->st_size != file->length) {
		return 0;
	}
	
	/* if always checksum is set then we use the checksum instead 
