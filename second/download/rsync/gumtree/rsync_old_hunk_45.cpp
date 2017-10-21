      continue;
    }

    send_file_name(f,flist,recurse,fname);
  }

  write_int(f,0);
  write_flush(f);

  clean_flist(flist);

  return flist;
}


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
