static void delete_one(struct file_struct *f)
{
  if (!S_ISDIR(f->mode)) {
    if (!dry_run && unlink(f->name) != 0) {
      fprintf(stderr,"unlink %s : %s\n",f->name,strerror(errno));
    } else if (verbose) {
      fprintf(stderr,"deleting %s\n",f->name);
    }
  } else {    
    if (!dry_run && rmdir(f->name) != 0) {
      if (errno != ENOTEMPTY)
	fprintf(stderr,"rmdir %s : %s\n",f->name,strerror(errno));
    } else if (verbose) {
      fprintf(stderr,"deleting directory %s\n",f->name);      
    }
  }
}