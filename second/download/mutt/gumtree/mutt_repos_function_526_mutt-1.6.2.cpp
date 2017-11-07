int mx_close_message (MESSAGE **msg)
{
  int r = 0;

  if ((*msg)->magic == M_MH || (*msg)->magic == M_MAILDIR
      || (*msg)->magic == M_IMAP || (*msg)->magic == M_POP)
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

  FREE (msg);		/* __FREE_CHECKED__ */
  return (r);
}