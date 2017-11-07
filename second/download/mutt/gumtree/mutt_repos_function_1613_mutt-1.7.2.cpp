static int
smtp_data (CONNECTION * conn, const char *msgfile)
{
  char buf[1024];
  FILE *fp = 0;
  progress_t progress;
  struct stat st;
  int r, term = 0;
  size_t buflen = 0;

  fp = fopen (msgfile, "r");
  if (!fp)
  {
    mutt_error (_("SMTP session failed: unable to open %s"), msgfile);
    return -1;
  }
  stat (msgfile, &st);
  unlink (msgfile);
  mutt_progress_init (&progress, _("Sending message..."), MUTT_PROGRESS_SIZE,
                      NetInc, st.st_size);

  snprintf (buf, sizeof (buf), "DATA\r\n");
  if (mutt_socket_write (conn, buf) == -1)
  {
    safe_fclose (&fp);
    return smtp_err_write;
  }
  if ((r = smtp_get_resp (conn)))
  {
    safe_fclose (&fp);
    return r;
  }

  while (fgets (buf, sizeof (buf) - 1, fp))
  {
    buflen = mutt_strlen (buf);
    term = buflen && buf[buflen-1] == '\n';
    if (term && (buflen == 1 || buf[buflen - 2] != '\r'))
      snprintf (buf + buflen - 1, sizeof (buf) - buflen + 1, "\r\n");
    if (buf[0] == '.')
    {
      if (mutt_socket_write_d (conn, ".", -1, MUTT_SOCK_LOG_FULL) == -1)
      {
        safe_fclose (&fp);
        return smtp_err_write;
      }
    }
    if (mutt_socket_write_d (conn, buf, -1, MUTT_SOCK_LOG_FULL) == -1)
    {
      safe_fclose (&fp);
      return smtp_err_write;
    }
    mutt_progress_update (&progress, ftell (fp), -1);
  }
  if (!term && buflen &&
      mutt_socket_write_d (conn, "\r\n", -1, MUTT_SOCK_LOG_FULL) == -1)
  {
    safe_fclose (&fp);
    return smtp_err_write;
  }
  safe_fclose (&fp);

  /* terminate the message body */
  if (mutt_socket_write (conn, ".\r\n") == -1)
    return smtp_err_write;

  if ((r = smtp_get_resp (conn)))
    return r;

  return 0;
}