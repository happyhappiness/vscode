  last_mode = file->mode;
  last_rdev = file->rdev;
  last_uid = file->uid;
  last_gid = file->gid;
  last_time = file->modtime;

  strncpy(lastname,fname,MAXPATHLEN-1);
  lastname[MAXPATHLEN-1] = 0;
}



void receive_file_entry(struct file_struct **fptr,
			unsigned char flags,int f)
{
  static time_t last_time;
  static mode_t last_mode;
  static dev_t last_rdev;
  static uid_t last_uid;
  static gid_t last_gid;
  static char lastname[MAXPATHLEN];
  char thisname[MAXPATHLEN];
  int l1=0,l2=0;
  char *p;
  struct file_struct *file;

  if (flags & SAME_NAME)
    l1 = read_byte(f);
  
  if (flags & LONG_NAME)
    l2 = read_int(f);
  else
    l2 = read_byte(f);

  file = (struct file_struct *)malloc(sizeof(*file));
  if (!file) out_of_memory("receive_file_entry");
  bzero((char *)file,sizeof(*file));
  (*fptr) = file;

  strncpy(thisname,lastname,l1);
  read_buf(f,&thisname[l1],l2);
  thisname[l1+l2] = 0;

  strncpy(lastname,thisname,MAXPATHLEN-1);
  lastname[MAXPATHLEN-1] = 0;

  clean_fname(thisname);

  if ((p = strrchr(thisname,'/'))) {
	  static char *lastdir;
	  *p = 0;
	  if (lastdir && strcmp(thisname, lastdir)==0) {
		  file->dirname = lastdir;
	  } else {
		  file->dirname = strdup(thisname);
		  lastdir = file->dirname;
	  }
	  file->basename = strdup(p+1);
  } else {
	  file->dirname = NULL;
	  file->basename = strdup(thisname);
  }

  if (!file->basename) out_of_memory("receive_file_entry 1");


  file->length = read_longint(f);
  file->modtime = (flags & SAME_TIME) ? last_time : (time_t)read_int(f);
  file->mode = (flags & SAME_MODE) ? last_mode : (mode_t)read_int(f);
  if (preserve_uid)
    file->uid = (flags & SAME_UID) ? last_uid : (uid_t)read_int(f);
  if (preserve_gid)
    file->gid = (flags & SAME_GID) ? last_gid : (gid_t)read_int(f);
