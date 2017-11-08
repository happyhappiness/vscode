static void delete_one(struct file_struct *f)
{
  if (!S_ISDIR(f->mode)) {
    if (do_unlink(f_name(f)) != 0) {
      rprintf(FERROR,"unlink %s : %s\n",f_name(f),strerror(errno));
    } else if (verbose) {
      rprintf(FINFO,"deleting %s\n",f_name(f));
    }
  } else {    
    if (do_rmdir(f_name(f)) != 0) {
      if (errno != ENOTEMPTY && errno != EEXIST)
	rprintf(FERROR,"rmdir %s : %s\n",f_name(f),strerror(errno));
    } else if (verbose) {
      rprintf(FINFO,"deleting directory %s\n",f_name(f));      
    }
  }
}