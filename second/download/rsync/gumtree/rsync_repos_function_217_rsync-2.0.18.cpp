struct file_list *recv_file_list(int f)
{
  struct file_list *flist;
  unsigned char flags;
  int64 start_read;

  if (verbose && recurse && !am_server) {
    rprintf(FINFO,"receiving file list ... ");
    rflush(FINFO);
  }

  start_read = stats.total_read;

  flist = (struct file_list *)malloc(sizeof(flist[0]));
  if (!flist)
    goto oom;

  flist->count=0;
  flist->malloced=1000;
  flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
					       flist->malloced);
  if (!flist->files)
    goto oom;


  for (flags=read_byte(f); flags; flags=read_byte(f)) {
    int i = flist->count;

    if (i >= flist->malloced) {
	  if (flist->malloced < 1000)
		  flist->malloced += 1000;
	  else
		  flist->malloced *= 2;
	  flist->files =(struct file_struct **)realloc(flist->files,
						       sizeof(flist->files[0])*
						       flist->malloced);
	  if (!flist->files)
		  goto oom;
    }

    receive_file_entry(&flist->files[i],flags,f);

    if (S_ISREG(flist->files[i]->mode))
	    stats.total_size += flist->files[i]->length;

    flist->count++;

    if (verbose > 2)
      rprintf(FINFO,"recv_file_name(%s)\n",f_name(flist->files[i]));
  }


  if (verbose > 2)
    rprintf(FINFO,"received %d names\n",flist->count);

  clean_flist(flist);

  if (verbose && recurse && !am_server) {
    rprintf(FINFO,"done\n");
  }

  /* now recv the uid/gid list. This was introduced in protocol version 15 */
  if (f != -1 && remote_version >= 15) {
	  recv_uid_list(f, flist);
  }

  /* if protocol version is >= 17 then recv the io_error flag */
  if (f != -1 && remote_version >= 17) {
	  io_error |= read_int(f);
  }

  if (verbose > 2)
    rprintf(FINFO,"recv_file_list done\n");

  stats.flist_size = stats.total_read - start_read;
  stats.num_files = flist->count;

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}