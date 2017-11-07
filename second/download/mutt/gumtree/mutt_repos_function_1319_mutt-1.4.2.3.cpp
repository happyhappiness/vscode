int imap_expand_path (char* path, size_t len)
{
  IMAP_MBOX mx;
  ciss_url_t url;
  int rc;

  if (imap_parse_path (path, &mx) < 0)
    return -1;

  mutt_account_tourl (&mx.account, &url);
  url.path = mx.mbox;

  rc = url_ciss_tostring (&url, path, len, U_DECODE_PASSWD);
  FREE (&mx.mbox);

  return rc;
}