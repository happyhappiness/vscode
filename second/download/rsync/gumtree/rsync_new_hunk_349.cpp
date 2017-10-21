
  sum_end(file_sum1);

  if (remote_version >= 14) {
    read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
    if (verbose > 2)
      fprintf(FINFO,"got file_sum\n");
    if (fd != -1 && memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0)
      return 0;
  }
  return 1;
}


static void delete_one(struct file_struct *f)
{
  if (!S_ISDIR(f->mode)) {
    if (do_unlink(f_name(f)) != 0) {
      fprintf(FERROR,"unlink %s : %s\n",f_name(f),strerror(errno));
    } else if (verbose) {
      fprintf(FINFO,"deleting %s\n",f_name(f));
    }
  } else {    
    if (do_rmdir(f_name(f)) != 0) {
      if (errno != ENOTEMPTY)
	fprintf(FERROR,"rmdir %s : %s\n",f_name(f),strerror(errno));
    } else if (verbose) {
      fprintf(FINFO,"deleting directory %s\n",f_name(f));      
    }
  }
}


/* yuck! This function wouldn't have been necessary if I had the sorting
