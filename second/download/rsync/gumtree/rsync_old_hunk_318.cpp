  if (preserve_hard_links && S_ISREG(file->mode)) {
    file->dev = read_int(f);
    file->inode = read_int(f);
  }
#endif
  
  if (always_checksum)
    read_buf(f,file->sum,csum_length);
  
  last_mode = file->mode;
  last_rdev = file->rdev;
  last_uid = file->uid;
  last_gid = file->gid;
  last_time = file->modtime;

  strncpy(lastname,file->name,MAXPATHLEN-1);
  lastname[MAXPATHLEN-1] = 0;
}



static struct file_struct *make_file(char *fname)
{
  static struct file_struct file;
  struct stat st;
  char sum[SUM_LENGTH];

  bzero(sum,SUM_LENGTH);

  if (link_stat(fname,&st) != 0) {
    fprintf(FERROR,"%s: %s\n",
	    fname,strerror(errno));
    return NULL;
  }

  if (S_ISDIR(st.st_mode) && !recurse) {
    fprintf(FERROR,"skipping directory %s\n",fname);
    return NULL;
  }

  if (one_file_system && st.st_dev != filesystem_dev)
    return NULL;

  if (!match_file_name(fname,&st))
    return NULL;

  if (verbose > 2)
    fprintf(FERROR,"make_file(%s)\n",fname);

  bzero((char *)&file,sizeof(file));

  file.name = strdup(fname);
  file.modtime = st.st_mtime;
  file.length = st.st_size;
  file.mode = st.st_mode;
  file.uid = st.st_uid;
  file.gid = st.st_gid;
  file.dev = st.st_dev;
  file.inode = st.st_ino;
#ifdef HAVE_ST_RDEV
  file.rdev = st.st_rdev;
#endif

#if SUPPORT_LINKS
  if (S_ISLNK(st.st_mode)) {
    int l;
    char lnk[MAXPATHLEN];
    if ((l=readlink(fname,lnk,MAXPATHLEN-1)) == -1) {
      fprintf(FERROR,"readlink %s : %s\n",fname,strerror(errno));
      return NULL;
    }
    lnk[l] = 0;
    file.link = strdup(lnk);
  }
#endif

  if (always_checksum && S_ISREG(st.st_mode)) {
    file_checksum(fname,file.sum,st.st_size);
  }       

  if (flist_dir)
    file.dir = strdup(flist_dir);
  else
    file.dir = NULL;

  if (!S_ISDIR(st.st_mode))
    total_size += st.st_size;

  return &file;
}



static void send_file_name(int f,struct file_list *flist,char *fname)
{
  struct file_struct *file;

  file = make_file(fname);

  if (!file) return;  
  
  if (flist->count >= flist->malloced) {
	  if (flist->malloced < 100)
		  flist->malloced += 100;
	  else
		  flist->malloced *= 1.8;
	  flist->files = (struct file_struct *)realloc(flist->files,
						       sizeof(flist->files[0])*
						       flist->malloced);
	  if (!flist->files)
		  out_of_memory("send_file_name");
  }

  if (strcmp(file->name,"/")) {
    flist->files[flist->count++] = *file;    
    send_file_entry(file,f);
  }

  if (S_ISDIR(file->mode) && recurse) {
    char **last_exclude_list = local_exclude_list;
    send_directory(f,flist,file->name);
    local_exclude_list = last_exclude_list;
    return;
  }
}



static void send_directory(int f,struct file_list *flist,char *dir)
{
  DIR *d;
  struct dirent *di;
  char fname[MAXPATHLEN];
  int l;
  char *p;

  d = opendir(dir);
  if (!d) {
    fprintf(FERROR,"%s: %s\n",
	    dir,strerror(errno));
    return;
  }

  strncpy(fname,dir,MAXPATHLEN-1);
  fname[MAXPATHLEN-1]=0;
  l = strlen(fname);
  if (fname[l-1] != '/') {
        if (l == MAXPATHLEN-1) {
              fprintf(FERROR,"skipping long-named directory %s\n",fname);
              closedir(d);
              return;
        }
	  strcat(fname,"/");
	  l++;
  }
  p = fname + strlen(fname);

  if (cvs_exclude) {
    if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN-1) {
      strcpy(p,".cvsignore");
      local_exclude_list = make_exclude_list(fname,NULL,0);
    } else {
      fprintf(FERROR,"cannot cvs-exclude in long-named directory %s\n",fname);
    }
  }  

  for (di=readdir(d); di; di=readdir(d)) {
    if (strcmp(di->d_name,".")==0 ||
	strcmp(di->d_name,"..")==0)
      continue;
    strncpy(p,di->d_name,MAXPATHLEN-(l+1));
    send_file_name(f,flist,fname);
  }

  closedir(d);
}



struct file_list *send_file_list(int f,int argc,char *argv[])
{
  int i,l;
  struct stat st;
  char *p,*dir;
  char dbuf[MAXPATHLEN];
  struct file_list *flist;

  if (verbose && recurse && !am_server && f != -1) {
    fprintf(FINFO,"building file list ... ");
    fflush(FINFO);
  }

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

    strncpy(fname,argv[i],MAXPATHLEN-1);
    fname[MAXPATHLEN-1] = 0;

    l = strlen(fname);
    if (l != 1 && fname[l-1] == '/') {
      strcat(fname,".");
    }

    if (link_stat(fname,&st) != 0) {
      fprintf(FERROR,"%s : %s\n",fname,strerror(errno));
      continue;
    }

    if (S_ISDIR(st.st_mode) && !recurse) {
      fprintf(FERROR,"skipping directory %s\n",fname);
      continue;
    }

    dir = NULL;

    if (!relative_paths) {
	    p = strrchr(fname,'/');
	    if (p) {
		    *p = 0;
		    if (p == fname) 
			    dir = "/";
		    else
			    dir = fname;      
		    fname = p+1;      
	    }
    }

    if (!*fname)
      fname = ".";

    if (dir && *dir) {
      if (getcwd(dbuf,MAXPATHLEN-1) == NULL) {
	fprintf(FERROR,"getwd : %s\n",strerror(errno));
	exit_cleanup(1);
      }
      if (chdir(dir) != 0) {
	fprintf(FERROR,"chdir %s : %s\n",dir,strerror(errno));
	continue;
      }
      flist_dir = dir;
      if (one_file_system)
	set_filesystem(fname);
      send_file_name(f,flist,fname);
      flist_dir = NULL;
      if (chdir(dbuf) != 0) {
	fprintf(FERROR,"chdir %s : %s\n",dbuf,strerror(errno));
	exit_cleanup(1);
      }
      continue;
    }

    if (one_file_system)
      set_filesystem(fname);
    send_file_name(f,flist,fname);
  }

  if (f != -1) {
    send_file_entry(NULL,f);
    write_flush(f);
  }

  if (verbose && recurse && !am_server && f != -1)
    fprintf(FINFO,"done\n");

  clean_flist(flist);

  /* now send the uid/gid list. This was introduced in protocol version 15 */
  if (f != -1 && remote_version >= 15) {
	  send_uid_list(f);
  }

  return flist;
}


struct file_list *recv_file_list(int f)
{
  struct file_list *flist;
