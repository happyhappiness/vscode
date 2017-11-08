static void send_directory(int f,struct file_list *flist,char *dir)
{
  DIR *d;
  struct dirent *di;
  char fname[MAXPATHLEN];
  int l;
  char *p;

  d = opendir(dir);
  if (!d) {
    fprintf(stderr,"%s: %s\n",
	    dir,strerror(errno));
    return;
  }

  strcpy(fname,dir);
  l = strlen(fname);
  if (fname[l-1] != '/')
    strcat(fname,"/");
  p = fname + strlen(fname);

  if (cvs_exclude) {
    strcpy(p,".cvsignore");
    local_exclude_list = make_exclude_list(fname,NULL,0);
  }  

  for (di=readdir(d); di; di=readdir(d)) {
    if (strcmp(di->d_name,".")==0 ||
	strcmp(di->d_name,"..")==0)
      continue;
    strcpy(p,di->d_name);
    send_file_name(f,flist,1,fname);
  }

  closedir(d);
}