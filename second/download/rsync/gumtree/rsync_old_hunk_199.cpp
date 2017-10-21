

off_t send_files(struct file_list *flist,int f_out,int f_in)
{ 
  int fd;
  struct sum_struct *s;
  char *buf;
  struct stat st;
  char fname[MAXPATHLEN];  
  off_t total=0;
  int i;
  struct file_struct *file;

  if (verbose > 2)
    fprintf(FERROR,"send_files starting\n");

  setup_nonblocking(f_in,f_out);

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) break;

      file = &flist->files[i];

      fname[0] = 0;
      if (file->dir) {
	strcpy(fname,file->dir);
