  file->mode = (flags & SAME_MODE) ? last_mode : (mode_t)read_int(f);
  if (preserve_uid)
    file->uid = (flags & SAME_UID) ? last_uid : (uid_t)read_int(f);
  if (preserve_gid)
    file->gid = (flags & SAME_GID) ? last_gid : (gid_t)read_int(f);
  if (preserve_devices && IS_DEVICE(file->mode))
    file->dev = (flags & SAME_DEV) ? last_dev : (dev_t)read_int(f);

#if SUPPORT_LINKS
  if (preserve_links && S_ISLNK(file->mode)) {
    int l = read_int(f);
    file->link = (char *)malloc(l+1);
    if (!file->link) out_of_memory("receive_file_entry");
