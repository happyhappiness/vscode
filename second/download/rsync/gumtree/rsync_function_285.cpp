struct file_list *recv_file_list(int f)
{
  struct file_list *flist;
  unsigned char flags;

  if (verbose && recurse && !am_server) {
    fprintf(FINFO,"receiving file list ... ");
    fflush(FINFO);
  }

  flist = (struct file_list *)malloc(sizeof(flist[0]));
  if (!flist)
    goto oom;

  flist->count=0;
  flist->malloced=100;
  flist->files = (struct file_struct *)malloc(sizeof(flist->files[0])*
					      flist->malloced);
  if (!flist->files)
    goto oom;


  for (flags=read_byte(f); flags; flags=read_byte(f)) {
    int i = flist->count;

    if (i >= flist->malloced) {
	  if (flist->malloced < 100)
		  flist->malloced += 100;
	  else
		  flist->malloced *= 1.8;
	  flist->files =(struct file_struct *)realloc(flist->files,
						      sizeof(flist->files[0])*
						      flist->malloced);
	  if (!flist->files)
		  goto oom;
    }

    receive_file_entry(&flist->files[i],flags,f);

    if (S_ISREG(flist->files[i].mode))
      total_size += flist->files[i].length;

    flist->count++;

    if (verbose > 2)
      fprintf(FERROR,"recv_file_name(%s)\n",flist->files[i].name);
  }


  if (verbose > 2)
    fprintf(FERROR,"received %d names\n",flist->count);

  clean_flist(flist);

  if (verbose && recurse && !am_server) {
    fprintf(FINFO,"done\n");
  }

  /* now recv the uid/gid list. This was introduced in protocol version 15 */
  if (f != -1 && remote_version >= 15) {
	  recv_uid_list(f, flist);
  }

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}