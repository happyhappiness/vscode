    file->uid = (flags & SAME_UID) ? last_uid : (uid_t)read_int(f);
  if (preserve_gid)
    file->gid = (flags & SAME_GID) ? last_gid : (gid_t)read_int(f);
  if (preserve_devices && IS_DEVICE(file->mode))
    file->rdev = (flags & SAME_RDEV) ? last_rdev : (dev_t)read_int(f);

  if (preserve_links && S_ISLNK(file->mode)) {
    int l = read_int(f);
    file->link = (char *)malloc(l+1);
    if (!file->link) out_of_memory("receive_file_entry 2");
    read_buf(f,file->link,l);
    file->link[l] = 0;
  }

#if SUPPORT_HARD_LINKS
  if (preserve_hard_links && S_ISREG(file->mode)) {
    file->dev = read_int(f);
    file->inode = read_int(f);
  }
