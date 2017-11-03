static int
imap_complete_hosts (char *dest, size_t len)
{
  BUFFY* mailbox;
  CONNECTION* conn;
  int rc = -1;
  int matchlen;

  matchlen = mutt_strlen (dest);
  for (mailbox = Incoming; mailbox; mailbox = mailbox->next)
  {
    if (!mutt_strncmp (dest, mailbox->path, matchlen))
    {
      if (rc)
      {
        strfcpy (dest, mailbox->path, len);
        rc = 0;
      }
      else
        longest_common_prefix (dest, mailbox->path, matchlen, len);
    }
  }

  for (conn = mutt_socket_head (); conn; conn = conn->next)
  {
    ciss_url_t url;
    char urlstr[LONG_STRING];

    if (conn->account.type != MUTT_ACCT_TYPE_IMAP)
      continue;

    mutt_account_tourl (&conn->account, &url);
    /* FIXME: how to handle multiple users on the same host? */
    url.user = NULL;
    url.path = NULL;
    url_ciss_tostring (&url, urlstr, sizeof (urlstr), 0);
    if (!mutt_strncmp (dest, urlstr, matchlen))
    {
      if (rc)
      {
        strfcpy (dest, urlstr, len);
        rc = 0;
      }
      else
        longest_common_prefix (dest, urlstr, matchlen, len);
    }
  }

  return rc;
}