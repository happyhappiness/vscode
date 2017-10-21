  flist_malloced = 100;
  flist->files = (struct file_struct *)malloc(sizeof(flist->files[0])*
					      flist_malloced);
  if (!flist->files) out_of_memory("send_file_list");

  for (i=0;i<argc;i++) {
    char *fname = argv[i];

    l = strlen(fname);
    if (l != 1 && fname[l-1] == '/')
      fname[l-1] = 0;

    if (lstat(fname,&st) != 0) {
      fprintf(stderr,"%s : %s\n",fname,strerror(errno));
      continue;
    }

    if (S_ISDIR(st.st_mode) && !recurse) {
      fprintf(stderr,"skipping directory %s\n",fname);
      continue;
    }

    if (S_ISDIR(st.st_mode) && argc == 1) {
      if (chdir(fname) != 0) {
	fprintf(stderr,"chdir %s : %s\n",fname,strerror(errno));
	continue;
      }
      send_file_name(f,flist,recurse,".");
      continue;
    } 

    dir = NULL;
    p = strrchr(fname,'/');
    if (p && !p[1]) {
      *p = 0;
      p = strrchr(fname,'/');
    }
    if (p) {
      *p = 0;
      dir = fname;
      fname = p+1;      
    }

    if (dir && *dir) {
      if (getcwd(dbuf,MAXPATHLEN-1) == NULL) {
	fprintf(stderr,"getwd : %s\n",strerror(errno));
	exit(1);
      }
