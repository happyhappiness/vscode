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



void receive_file_entry_v11(struct file_struct *file,
			    unsigned char flags,int f)
{
  static mode_t last_time=0;
  static mode_t last_mode=0;
  static dev_t last_dev=0;
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
