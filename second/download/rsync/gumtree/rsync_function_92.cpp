static void send_file_entry(struct file_struct *file,int f)
{
  if (f == -1) return;

  write_int(f,strlen(file->name));
  write_buf(f,file->name,strlen(file->name));
  write_int(f,(int)file->modtime);
  write_int(f,(int)file->length);
  write_int(f,(int)file->mode);
  if (preserve_uid)
    write_int(f,(int)file->uid);
  if (preserve_gid)
    write_int(f,(int)file->gid);
  if (preserve_devices) {
    if (verbose > 2)
      fprintf(stderr,"dev=0x%x\n",(int)file->dev);
    write_int(f,(int)file->dev);
  }

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    write_int(f,strlen(file->link));
    write_buf(f,file->link,strlen(file->link));
  }
#endif

  if (always_checksum) {
    write_buf(f,file->sum,SUM_LENGTH);
  }       
}