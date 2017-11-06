static int
dotlock_try (void)
{
#ifdef USE_SETGID
  struct stat sb;
#endif

  if (access (".", W_OK) == 0)
    return DL_EX_OK;

#ifdef USE_SETGID
  if (stat (".", &sb) == 0)
  {
    if ((sb.st_mode & S_IWGRP) == S_IWGRP && sb.st_gid == MailGid)
      return DL_EX_NEED_PRIVS;
  }
#endif

  return DL_EX_IMPOSSIBLE;
}