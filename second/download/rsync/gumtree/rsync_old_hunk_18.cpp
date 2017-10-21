}



void do_server_recv(int argc,char *argv[])
{
  int pid,i,status;
  char *dir = NULL;
  struct file_list *flist;
  char *fname=NULL;
  struct stat st;
  
  if (verbose > 2)
    fprintf(stderr,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());

  if (argc > 0) {
    dir = argv[0];
    argc--;
    argv++;
  }

  if (argc > 0) {
    fname = argv[0];
    dir = NULL;

    if (stat(fname,&st) != 0) {
      if (!recurse || mkdir(fname,0777) != 0) {
	fprintf(stderr,"stat %s : %s\n",fname,strerror(errno));
	exit(1);
      }
      stat(fname,&st);
    }

    if (S_ISDIR(st.st_mode)) {
      dir = fname;
      fname = NULL;
    }
  }

  if (dir) {
    if (chdir(dir) != 0) {
      fprintf(stderr,"chdir %s : %s\n",dir,strerror(errno));
      exit(1);
    } else {
      if (verbose > 2) {
	fprintf(stderr,"server changed to directory %s\n",dir);
      }
    }
  }

  flist = recv_file_list(STDIN_FILENO);
  if (!flist) {
    fprintf(stderr,"nothing to do\n");
    exit(1);
  }

  if ((pid=fork()) == 0) {
    recv_files(STDIN_FILENO,flist,fname);
    if (verbose > 1)
      fprintf(stderr,"receiver read %d\n",read_total());
    exit(0);
  }

  if (verbose > 2)
    fprintf(stderr,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
    if (S_ISDIR(flist->files[i].mode)) {
      if (dry_run) continue;
      if (mkdir(flist->files[i].name,flist->files[i].mode) != 0 && 
	  errno != EEXIST) {	 
	fprintf(stderr,"mkdir %s: %s\n",
		flist->files[i].name,strerror(errno));
	exit(1);
      }
      continue;
    }
    fname = flist->files[i].name;
    if (flist->count == 1 &&
	argc > 0)
      fname = argv[0];
    recv_generator(fname,flist,i,STDOUT_FILENO);
  }
  write_int(STDOUT_FILENO,-1);
  write_flush(STDOUT_FILENO);
  if (verbose > 1)
    fprintf(stderr,"generator wrote %d\n",write_total());

  waitpid(pid, &status, 0);
  exit(status);
}


