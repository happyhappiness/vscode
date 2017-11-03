void send_file_entry_v10(struct file_struct *file,int f)
{
  unsigned char flags;
  static mode_t last_mode=0;
  static dev_t last_dev=0;
  static uid_t last_uid=0;
  static gid_t last_gid=0;
  static char lastdir[MAXPATHLEN]="";
  char *p=NULL;

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
    
  if (strncmp(file->name,lastdir,strlen(lastdir)) == 0) {
    flags |= SAME_DIR;
    p = file->name + strlen(lastdir);
  } else {
    p = file->name;
  }

  write_byte(f,flags);
  if (flags & SAME_DIR)
    write_byte(f,strlen(p));
  else
    write_int(f,strlen(p));
  write_buf(f,p,strlen(p));
  write_int(f,(int)file->modtime);
  write_int(f,(int)file->length);
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
  p = strrchr(file->name,'/');
  if (p) {
    int l = (int)(p - file->name) + 1;
    strncpy(lastdir,file->name,l);
    lastdir[l] = 0;
  } else {
    strcpy(lastdir,"");
  }
}