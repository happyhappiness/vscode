
  if (f != -1) {
    send_file_entry(NULL,f);
    write_flush(f);
  }

  if (verbose && recurse)
    fprintf(FINFO,"done\n");

  clean_flist(flist);

  return flist;
}


struct file_list *recv_file_list(int f)
{
  struct file_list *flist;
  unsigned char flags;

  if (verbose > 2)
    fprintf(FERROR,"recv_file_list starting\n");

  flist = (struct file_list *)malloc(sizeof(flist[0]));
  if (!flist)
    goto oom;

  flist->count=0;
