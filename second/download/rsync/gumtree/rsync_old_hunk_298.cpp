
  if (f != -1) {
    send_file_entry(NULL,f);
    write_flush(f);
  }

  if (verbose && recurse && !am_server)
    fprintf(FINFO,"done\n");

  clean_flist(flist);

  return flist;
}


struct file_list *recv_file_list(int f)
{
