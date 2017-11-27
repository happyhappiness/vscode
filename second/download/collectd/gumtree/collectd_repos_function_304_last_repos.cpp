static int df_read(void) {
#if HAVE_STATVFS
  struct statvfs statbuf;
#elif HAVE_STATFS
  struct statfs statbuf;
#endif
  /* struct STATANYFS statbuf; */
  cu_mount_t *mnt_list;

  mnt_list = NULL;
  if (cu_mount_getlist(&mnt_list) == NULL) {
    ERROR("df plugin: cu_mount_getlist failed.");
    return -1;
  }

  for (cu_mount_t *mnt_ptr = mnt_list; mnt_ptr != NULL;
       mnt_ptr = mnt_ptr->next) {
    unsigned long long blocksize;
    char disk_name[256];
    cu_mount_t *dup_ptr;
    uint64_t blk_free;
    uint64_t blk_reserved;
    uint64_t blk_used;

    char const *dev =
        (mnt_ptr->spec_device != NULL) ? mnt_ptr->spec_device : mnt_ptr->device;

    if (ignorelist_match(il_device, dev))
      continue;
    if (ignorelist_match(il_mountpoint, mnt_ptr->dir))
      continue;
    if (ignorelist_match(il_fstype, mnt_ptr->type))
      continue;

    /* search for duplicates *in front of* the current mnt_ptr. */
    for (dup_ptr = mnt_list; dup_ptr != NULL; dup_ptr = dup_ptr->next) {
      /* No duplicate found: mnt_ptr is the first of its kind. */
      if (dup_ptr == mnt_ptr) {
        dup_ptr = NULL;
        break;
      }

      /* Duplicate found: leave non-NULL dup_ptr. */
      if (by_device && (mnt_ptr->spec_device != NULL) &&
          (dup_ptr->spec_device != NULL) &&
          (strcmp(mnt_ptr->spec_device, dup_ptr->spec_device) == 0))
        break;
      else if (!by_device && (strcmp(mnt_ptr->dir, dup_ptr->dir) == 0))
        break;
    }

    /* ignore duplicates */
    if (dup_ptr != NULL)
      continue;

    if (STATANYFS(mnt_ptr->dir, &statbuf) < 0) {
      char errbuf[1024];
      ERROR(STATANYFS_STR "(%s) failed: %s", mnt_ptr->dir,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    if (!statbuf.f_blocks)
      continue;

    if (by_device) {
      /* eg, /dev/hda1  -- strip off the "/dev/" */
      if (strncmp(dev, "/dev/", strlen("/dev/")) == 0)
        sstrncpy(disk_name, dev + strlen("/dev/"), sizeof(disk_name));
      else
        sstrncpy(disk_name, dev, sizeof(disk_name));

      if (strlen(disk_name) < 1) {
        DEBUG("df: no device name for mountpoint %s, skipping", mnt_ptr->dir);
        continue;
      }
    } else {
      if (strcmp(mnt_ptr->dir, "/") == 0)
        sstrncpy(disk_name, "root", sizeof(disk_name));
      else {
        int len;

        sstrncpy(disk_name, mnt_ptr->dir + 1, sizeof(disk_name));
        len = strlen(disk_name);

        for (int i = 0; i < len; i++)
          if (disk_name[i] == '/')
            disk_name[i] = '-';
      }
    }

    blocksize = BLOCKSIZE(statbuf);

/*
 * Sanity-check for the values in the struct
 */
/* Check for negative "available" byes. For example UFS can
 * report negative free space for user. Notice. blk_reserved
 * will start to diminish after this. */
#if HAVE_STATVFS
    /* Cast and temporary variable are needed to avoid
     * compiler warnings.
     * ((struct statvfs).f_bavail is unsigned (POSIX)) */
    int64_t signed_bavail = (int64_t)statbuf.f_bavail;
    if (signed_bavail < 0)
      statbuf.f_bavail = 0;
#elif HAVE_STATFS
    if (statbuf.f_bavail < 0)
      statbuf.f_bavail = 0;
#endif
    /* Make sure that f_blocks >= f_bfree >= f_bavail */
    if (statbuf.f_bfree < statbuf.f_bavail)
      statbuf.f_bfree = statbuf.f_bavail;
    if (statbuf.f_blocks < statbuf.f_bfree)
      statbuf.f_blocks = statbuf.f_bfree;

    blk_free = (uint64_t)statbuf.f_bavail;
    blk_reserved = (uint64_t)(statbuf.f_bfree - statbuf.f_bavail);
    blk_used = (uint64_t)(statbuf.f_blocks - statbuf.f_bfree);

    if (values_absolute) {
      df_submit_one(disk_name, "df_complex", "free",
                    (gauge_t)(blk_free * blocksize));
      df_submit_one(disk_name, "df_complex", "reserved",
                    (gauge_t)(blk_reserved * blocksize));
      df_submit_one(disk_name, "df_complex", "used",
                    (gauge_t)(blk_used * blocksize));
    }

    if (values_percentage) {
      if (statbuf.f_blocks > 0) {
        df_submit_one(disk_name, "percent_bytes", "free",
                      (gauge_t)((float_t)(blk_free) / statbuf.f_blocks * 100));
        df_submit_one(
            disk_name, "percent_bytes", "reserved",
            (gauge_t)((float_t)(blk_reserved) / statbuf.f_blocks * 100));
        df_submit_one(disk_name, "percent_bytes", "used",
                      (gauge_t)((float_t)(blk_used) / statbuf.f_blocks * 100));
      } else
        return -1;
    }

    /* inode handling */
    if (report_inodes && statbuf.f_files != 0 && statbuf.f_ffree != 0) {
      uint64_t inode_free;
      uint64_t inode_reserved;
      uint64_t inode_used;

      /* Sanity-check for the values in the struct */
      if (statbuf.f_ffree < statbuf.f_favail)
        statbuf.f_ffree = statbuf.f_favail;
      if (statbuf.f_files < statbuf.f_ffree)
        statbuf.f_files = statbuf.f_ffree;

      inode_free = (uint64_t)statbuf.f_favail;
      inode_reserved = (uint64_t)(statbuf.f_ffree - statbuf.f_favail);
      inode_used = (uint64_t)(statbuf.f_files - statbuf.f_ffree);

      if (values_percentage) {
        if (statbuf.f_files > 0) {
          df_submit_one(
              disk_name, "percent_inodes", "free",
              (gauge_t)((float_t)(inode_free) / statbuf.f_files * 100));
          df_submit_one(
              disk_name, "percent_inodes", "reserved",
              (gauge_t)((float_t)(inode_reserved) / statbuf.f_files * 100));
          df_submit_one(
              disk_name, "percent_inodes", "used",
              (gauge_t)((float_t)(inode_used) / statbuf.f_files * 100));
        } else
          return -1;
      }
      if (values_absolute) {
        df_submit_one(disk_name, "df_inodes", "free", (gauge_t)inode_free);
        df_submit_one(disk_name, "df_inodes", "reserved",
                      (gauge_t)inode_reserved);
        df_submit_one(disk_name, "df_inodes", "used", (gauge_t)inode_used);
      }
    }
  }

  cu_mount_freelist(mnt_list);

  return 0;
}