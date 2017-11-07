int mutt_get_password (char *msg, char *buf, size_t buflen)
{
  int rc;
  
  CLEARLINE (LINES-1);
  addstr (msg);
  rc = mutt_enter_string (buf, buflen, LINES - 1, mutt_strlen (msg), M_PASS);
  CLEARLINE (LINES-1);
  return (rc);
}