void receive_file_entry_v11(struct file_struct *file,
			    unsigned char flags,int f)
{
  static time_t last_time=0;
  static mode_t last_mode=0;
  static dev_t last_rdev=0;
  static uid_t last_uid=0;
  static gid_t last_gid=0;
  static char lastname[MAXPATHLEN]="";
  int l1=0,l2=0;

  if (flags & SAME_NAME)
    l1 = read_byte(f);
  
  if (flags & LONG_NAME)
    l2 = read_int(f);
  else
    l2 = read_byte(f);

  bzero((char *)file,sizeof(*file));

  file->name = (char *)malloc(l1+l2+1);
  if (!file->name) out_of_memory("receive_file_entry");

  strncpy(file->name,lastname,l1);
  read_buf(f,file->name+l1,l2);
  file->name[l1+l2] = 0;

  file->length = (off_t)read_int(f);
  file->modtime = (flags & SAME_TIME) ? last_time : (time_t)read_int(f);
  file->mode = (flags & SAME_MODE) ? last_mode : (mode_t)read_int(f);
  if (preserve_uid)
    file->uid = (flags & SAME_UID) ? last_uid : (uid_t)read_int(f);
  if (preserve_gid)
    file->gid = (flags & SAME_GID) ? last_gid : (gid_t)read_int(f);
  if (preserve_devices && IS_DEVICE(file->mode))
    file->rdev = (flags & SAME_RDEV) ? last_rdev : (dev_t)read_int(f);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    int l = read_int(f);
    file->link = (char *)malloc(l+1);
    if (!file->link) out_of_memory("receive_file_entry");
    read_buf(f,file->link,l);
    file->link[l] = 0;
  }
#endif

#if SUPPORT_HARD_LINKS
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