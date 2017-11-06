static int
dotlock_check_stats (struct stat *fsb, struct stat *lsb)
{
  /* S_ISLNK (fsb->st_mode) should actually be impossible,
   * but we may have mixed up the parameters somewhere.
   * play safe.
   */

  if (S_ISLNK (lsb->st_mode) || S_ISLNK (fsb->st_mode))
    return -1;
  
  if ((lsb->st_dev != fsb->st_dev) ||
     (lsb->st_ino != fsb->st_ino) ||
     (lsb->st_mode != fsb->st_mode) ||
     (lsb->st_nlink != fsb->st_nlink) ||
     (lsb->st_uid != fsb->st_uid) ||
     (lsb->st_gid != fsb->st_gid) ||
     (lsb->st_rdev != fsb->st_rdev) ||
     (lsb->st_size != fsb->st_size))
  {
    /* something's fishy */
    return -1;
  }
  
  return 0;
}