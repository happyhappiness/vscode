  if (verbose > 2)
    fprintf(FERROR,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
    struct file_struct *file = &flist->files[i];
    if (!file->name) continue;
    if (S_ISDIR(file->mode)) {
      if (dry_run) continue;
      if (mkdir(file->name,file->mode) != 0 &&
	  errno != EEXIST) {
	fprintf(FERROR,"mkdir %s : %s\n",
		file->name,strerror(errno));
      }
      continue;
    }
    recv_generator(local_name?local_name:file->name,
		   flist,i,f);
  }

  phase++;
  csum_length = SUM_LENGTH;
  ignore_times=1;

