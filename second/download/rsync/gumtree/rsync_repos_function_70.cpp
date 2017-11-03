void send_file_entry_v11(struct file_struct *file,int f)
{
  unsigned char flags;
  static time_t last_time=0;
  static mode_t last_mode=0;
  static dev_t last_dev=0;
  static uid_t last_uid=0;
  static gid_t last_gid=0;
  static char lastname[MAXPATHLEN]="";
  int l1,l2;

  if (f == -1) return;

  if (!file) {
    write_byte(f,0);
    return;
  }

  flags = FILE_VALID;

  if (file->mode == last_mode) flags |= SAME_MODE;
  if (file->dev == last_dev) flags |= SAME_DEV;
  if (file->uid == last_uid) flags |= SAME_UID;
  if (file->gid == last_gid) flags |= SAME_GID;
  if (file->modtime == last_time) flags |= SAME_TIME;

  for (l1=0;lastname[l1] && file->name[l1] == lastname[l1];l1++) ;
  l2 = strlen(file->name) - l1;

  if (l1 > 0) flags |= SAME_NAME;
  if (l2 > 255) flags |= LONG_NAME;
    
  write_byte(f,flags);  
  if (flags & SAME_NAME)
    write_byte(f,l1);
  if (flags & LONG_NAME)
    write_int(f,l2);
  else
    write_byte(f,l2);
  write_buf(f,file->name+l1,l2);

  write_int(f,(int)file->length);
  if (!(flags & SAME_TIME))
    write_int(f,(int)file->modtime);
  if (!(flags & SAME_MODE))
    write_int(f,(int)file->mode);
  if (preserve_uid && !(flags & SAME_UID))
    write_int(f,(int)file->uid);
  if (preserve_gid && !(flags & SAME_GID))
    write_int(f,(int)file->gid);
  if (preserve_devices && IS_DEVICE(file->mode) && !(flags & SAME_DEV))
    write_int(f,(int)file->dev);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    write_int(f,strlen(file->link));
    write_buf(f,file->link,strlen(file->link));
  }
#endif

  if (always_checksum) {
    write_buf(f,file->sum,csum_length);
  }       

  last_mode = file->mode;
  last_dev = file->dev;
  last_uid = file->uid;
  last_gid = file->gid;
  last_time = file->modtime;

  strcpy(lastname,file->name);
  lastname[255] = 0;
}