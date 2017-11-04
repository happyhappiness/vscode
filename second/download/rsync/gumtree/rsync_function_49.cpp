struct file_list *send_file_list(int f,int recurse,int argc,char *argv[])
{
  int i,l;
  struct stat st;
  char *p,*dir;
  char dbuf[MAXPATHLEN];
  struct file_list *flist;

  if (verbose && recurse)
    fprintf(am_server?stderr:stdout,"building file list ... ");

  flist = (struct file_list *)malloc(sizeof(flist[0]));
  if (!flist) out_of_memory("send_file_list");

  flist->count=0;
  flist->malloced = 100;
  flist->files = (struct file_struct *)malloc(sizeof(flist->files[0])*
					      flist->malloced);
  if (!flist->files) out_of_memory("send_file_list");

  for (i=0;i<argc;i++) {
    char fname2[MAXPATHLEN];
    char *fname = fname2;

    strcpy(fname,argv[i]);

    l = strlen(fname);
    if (l != 1 && fname[l-1] == '/') {
      strcat(fname,".");
    }

    if (lstat(fname,&st) != 0) {
      fprintf(stderr,"%s : %s\n",fname,strerror(errno));
      continue;
    }

    if (S_ISDIR(st.st_mode) && !recurse) {
      fprintf(stderr,"skipping directory %s\n",fname);
      continue;
    }

    dir = NULL;
    p = strrchr(fname,'/');
    if (p) {
      *p = 0;
      dir = fname;
      fname = p+1;      
    }
    if (!*fname)
      fname = ".";

    if (dir && *dir) {
      if (getcwd(dbuf,MAXPATHLEN-1) == NULL) {
	fprintf(stderr,"getwd : %s\n",strerror(errno));
	exit(1);
      }
      if (chdir(dir) != 0) {
	fprintf(stderr,"chdir %s : %s\n",dir,strerror(errno));
	continue;
      }
      flist_dir = dir;
      send_file_name(f,flist,recurse,fname);
      flist_dir = NULL;
      if (chdir(dbuf) != 0) {
	fprintf(stderr,"chdir %s : %s\n",dbuf,strerror(errno));
	exit(1);
      }
      continue;
    }

    send_file_name(f,flist,recurse,fname);
  }

  if (f != -1) {
    write_int(f,0);
    write_flush(f);
  }

  clean_flist(flist);

  if (verbose && recurse)
    fprintf(am_server?stderr:stdout,"done\n");

  return flist;
}