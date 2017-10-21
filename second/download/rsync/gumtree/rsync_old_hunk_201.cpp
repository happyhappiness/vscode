
  return total;
}



void generate_files(int f,struct file_list *flist,char *local_name)
{
  int i;

  if (verbose > 2)
    fprintf(FERROR,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
