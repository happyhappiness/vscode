int mx_close_message (MESSAGE **msg)
{
  int r = 0;

  if ((*msg)->magic == M_MH || (*msg)->magic == M_MAILDIR
#ifdef USE_IMAP
      || (*msg)->magic == M_IMAP
#endif
#ifdef USE_POP
      || (*msg)->magic == M_POP
#endif
      )
  {
    r = safe_fclose (&(*msg)->fp);
  }
  else
    (*msg)->fp = NULL;

  if ((*msg)->path)
  {
    dprint (1, (debugfile, "mx_close_message (): unlinking %s\n",
		(*msg)->path));
    unlink ((*msg)->path);
    FREE (&(*msg)->path);
  }

  FREE (msg);
  return (r);
}