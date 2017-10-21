  return flist;
}


struct file_list *recv_file_list(int f)
{
  int l;
  struct file_list *flist;

  if (verbose > 2)
    fprintf(stderr,"recv_file_list starting\n");

  flist = (struct file_list *)malloc(sizeof(flist[0]));
  if (!flist)
