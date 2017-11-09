int mx_access (const char* path, int flags)
{
#ifdef USE_IMAP
  if (mx_is_imap (path))
    return imap_access (path);
#endif

  return access (path, flags);
}