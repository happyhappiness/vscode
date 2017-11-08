struct file_list *recv_file_list(int f)
{
  int l;
  struct file_list *flist;
  int malloc_count=0;

  if (verbose > 2)
    fprintf(stderr,"recv_file_list starting\n");

  flist = (struct file_list *)malloc(sizeof(flist[0]));
  if (!flist)
    goto oom;

  malloc_count=100;
  flist->files = (struct file_struct *)malloc(sizeof(flist->files[0])*
					      malloc_count);
  if (!flist->files)
    goto oom;

  flist->count=0;

  for (l=read_int(f); l; l=read_int(f)) {
    int i = flist->count;

    if (i >= malloc_count) {
      malloc_count += 100;
      flist->files =(struct file_struct *)realloc(flist->files,
						  sizeof(flist->files[0])*
						  malloc_count);
      if (!flist->files)
	goto oom;
    }

    flist->files[i].name = (char *)malloc(l+1);
    if (!flist->files[i].name) 
      goto oom;

    read_buf(f,flist->files[i].name,l);
    flist->files[i].name[l] = 0;
    flist->files[i].modtime = (time_t)read_int(f);
    flist->files[i].length = (off_t)read_int(f);
    flist->files[i].mode = (mode_t)read_int(f);
    if (preserve_uid)
      flist->files[i].uid = (uid_t)read_int(f);
    if (preserve_gid)
      flist->files[i].gid = (gid_t)read_int(f);
    if (preserve_devices)
      flist->files[i].dev = (dev_t)read_int(f);

#if SUPPORT_LINKS
    if (preserve_links && S_ISLNK(flist->files[i].mode)) {
      int l = read_int(f);
      flist->files[i].link = (char *)malloc(l+1);
      read_buf(f,flist->files[i].link,l);
      flist->files[i].link[l] = 0;
    }
#endif

    if (always_checksum)
      read_buf(f,flist->files[i].sum,SUM_LENGTH);

    if (S_ISREG(flist->files[i].mode))
      total_size += flist->files[i].length;

    flist->count++;

    if (verbose > 2)
      fprintf(stderr,"recv_file_name(%s)\n",flist->files[i].name);
  }


  if (verbose > 2)
    fprintf(stderr,"received %d names\n",flist->count);

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}