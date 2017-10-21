
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


int file_compare(struct file_struct *f1,struct file_struct *f2)
{
  if (!f1->name && !f2->name) return 0;
  if (!f1->name) return -1;
  if (!f2->name) return 1;
  return strcmp(f1->name,f2->name);
}


int flist_find(struct file_list *flist,struct file_struct *f)
{
	int low=0,high=flist->count-1;

	if (flist->count <= 0) return -1;

	while (low != high) {
		int mid = (low+high)/2;
		int ret = file_compare(&flist->files[flist_up(flist, mid)],f);
		if (ret == 0) return flist_up(flist, mid);
		if (ret > 0) {
			high=mid;
		} else {
			low=mid+1;
		}
	}

	if (file_compare(&flist->files[flist_up(flist,low)],f) == 0)
		return flist_up(flist,low);
	return -1;
}


static void clean_fname(char *name)
{
  char *p;
  int l;
  int modified = 1;

  if (!name) return;

  while (modified) {
    modified = 0;

    if ((p=strstr(name,"/./"))) {
      modified = 1;
      while (*p) {
	p[0] = p[2];
	p++;
      }
    }

    if ((p=strstr(name,"//"))) {
      modified = 1;
      while (*p) {
	p[0] = p[1];
	p++;
      }
    }

    if (strncmp(p=name,"./",2) == 0) {      
      modified = 1;
      do {
	p[0] = p[2];
      } while (*p++);
    }

    l = strlen(p=name);
    if (l > 1 && p[l-1] == '/') {
      modified = 1;
      p[l-1] = 0;
    }
  }
}


/*
 * This routine ensures we don't have any duplicate names in our file list.
 * duplicate names can cause corruption because of the pipelining 
 */
void clean_flist(struct file_list *flist)
{
  int i;

  if (!flist || flist->count == 0) 
    return;
  
  for (i=0;i<flist->count;i++) {
    clean_fname(flist->files[i].name);
  }
      
  qsort(flist->files,flist->count,
	sizeof(flist->files[0]),
	(int (*)())file_compare);

  for (i=1;i<flist->count;i++) {
    if (flist->files[i].name &&
	strcmp(flist->files[i].name,flist->files[i-1].name) == 0) {
      if (verbose > 1 && !am_server)
	fprintf(FERROR,"removing duplicate name %s from file list %d\n",
		flist->files[i-1].name,i-1);
      free(flist->files[i-1].name);
      bzero((char *)&flist->files[i-1],sizeof(flist->files[i-1]));
    } 
  }
}

