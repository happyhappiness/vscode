
  if (verbose > 2)
    fprintf(FERROR,"received %d names\n",flist->count);

  clean_flist(flist);

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}
