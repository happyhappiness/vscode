void generate_files(int f,struct file_list *flist,char *local_name,int f_recv)
{
  int i;
  int phase=0;

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

  if (verbose > 2)
    fprintf(FERROR,"generate_files phase=%d\n",phase);

  write_int(f,-1);
  write_flush(f);

  if (remote_version >= 13) {
    for (i=read_int(f_recv); i != -1; i=read_int(f_recv)) {
      struct file_struct *file = &flist->files[i];
      recv_generator(local_name?local_name:file->name,
		     flist,i,f);    
    }

    phase++;
    if (verbose > 2)
      fprintf(FERROR,"generate_files phase=%d\n",phase);

    write_int(f,-1);
    write_flush(f);
  }


  if (verbose > 2)
    fprintf(FERROR,"generator wrote %d\n",write_total());
}