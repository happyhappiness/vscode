int mx_check_empty (const char *path)
{
  switch (mx_get_magic (path))
  {
    case M_MBOX:
    case M_MMDF:
      return mbox_check_empty (path);
    case M_MH:
      return mh_check_empty (path);
    case M_MAILDIR:
      return maildir_check_empty (path);
    default:
      errno = EINVAL;
      return -1;
  }
  /* not reached */
}