static void delete_one(struct file_struct *f)
{
  if (!S_ISDIR(f->mode)) {
    if (!dry_run && unlink(f->name) != 0) {
      fprintf(FERROR,"unlink %s : %s\n",f->name,strerror(errno));
    } else if (verbose) {
      fprintf(FERROR,"deleting %s\n",f->name);
    }
  } else {    
    if (!dry_run && rmdir(f->name) != 0) {
      if (errno != ENOTEMPTY)
	fprintf(FERROR,"rmdir %s : %s\n",f->name,strerror(errno));
    } else if (verbose) {
      fprintf(FERROR,"deleting directory %s\n",f->name);      
    }
  }
}