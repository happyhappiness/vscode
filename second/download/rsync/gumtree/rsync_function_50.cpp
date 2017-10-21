void clean_flist(struct file_list *flist)
{
  int i,l;
  char *p;

  if (!flist || flist->count == 0) 
    return;
  
  for (i=0;i<flist->count;i++) {
    if (!flist->files[i].name) continue;
    if ((p=strstr(flist->files[i].name,"/./"))) {
      while (*p) {
	p[0] = p[2];
	p++;
      }
    }
    if ((p=strstr(flist->files[i].name,"//"))) {
      while (*p) {
	p[0] = p[1];
	p++;
      }
    }
    if (strncmp(p=flist->files[i].name,"./",2) == 0) {      
      while (*p) {
	p[0] = p[2];
	p++;
      }
    }
    l = strlen(p=flist->files[i].name);
    if (l > 1 && p[l-1] == '/')
      p[l-1] = 0;
  }
  
    
  qsort(flist->files,flist->count,
	sizeof(flist->files[0]),
	(int (*)())flist_compare);

  for (i=1;i<flist->count;i++) {
    if (flist->files[i].name &&
	strcmp(flist->files[i].name,flist->files[i-1].name) == 0) {
      if (verbose > 1 && !am_server)
	fprintf(stderr,"removing duplicate name %s from file list\n",
		flist->files[i].name);
      free(flist->files[i-1].name);
      flist->files[i-1].name = NULL;
    }
  }
}