void generate_files(int f,struct file_list *flist,char *local_name,int f_recv)
{
  int i;
  int phase=0;

  if (verbose > 2)
    fprintf(FERROR,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
    struct file_struct *file = &flist->files[i];
    mode_t saved_mode = file->mode;
    if (!file->name) continue;

    /* we need to ensure that any directories we create have writeable
       permissions initially so that we can create the files within
       them. This is then fixed after the files are transferred */
    if (!am_root && S_ISDIR(file->mode)) {
      file->mode |= S_IWUSR; /* user write */
    }

    recv_generator(local_name?local_name:file->name,
		   flist,i,f);

    file->mode = saved_mode;
  }

  phase++;
  csum_length = SUM_LENGTH;
  ignore_times=1;

  if (verbose > 2)
    fprintf(FERROR,"generate_files phase=%d\n",phase);

  write_int(f,-1);
  write_flush(f);

  if (remote_version >= 13) {
    /* in newer versions of the protocol the files can cycle through
       the system more than once to catch initial checksum errors */
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