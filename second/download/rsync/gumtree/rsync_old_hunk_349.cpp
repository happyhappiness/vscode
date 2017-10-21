
  sum_end(file_sum1);

  if (remote_version >= 14) {
    read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
    if (verbose > 2)
      fprintf(FERROR,"got file_sum\n");
    if (fd != -1 && memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0)
      return 0;
  }
  return 1;
}


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


/* yuck! This function wouldn't have been necessary if I had the sorting
