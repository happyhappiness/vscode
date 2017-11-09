static FILE *
mutt_save_attachment_open (char *path, int flags)
{
  if (flags == MUTT_SAVE_APPEND)
    return fopen (path, "a");
  if (flags == MUTT_SAVE_OVERWRITE)
    return fopen (path, "w");		/* __FOPEN_CHECKED__ */
  
  return safe_fopen (path, "w");
}