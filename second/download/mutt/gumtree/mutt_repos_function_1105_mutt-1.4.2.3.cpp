static FILE *
mutt_save_attachment_open (char *path, int flags)
{
  if (flags == M_SAVE_APPEND)
    return fopen (path, "a");
  if (flags == M_SAVE_OVERWRITE)
    return fopen (path, "w");		/* __FOPEN_CHECKED__ */
  
  return safe_fopen (path, "w");
}