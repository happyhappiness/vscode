int mutt_socket_readln_d (char* buf, size_t buflen, CONNECTION* conn, int dbg)
{
  char ch;
  int i;

  for (i = 0; i < buflen-1; i++)
  {
    if (mutt_socket_readchar (conn, &ch) != 1)
    {
      buf[i] = '\0';
      return -1;
    }

    if (ch == '\n')
      break;
    buf[i] = ch;
  }

  /* strip \r from \r\n termination */
  if (i && buf[i-1] == '\r')
    buf[--i] = '\0';
  else
    buf[i] = '\0';

  dprint (dbg, (debugfile, "< %s\n", buf));
  
  /* number of bytes read, not strlen */
  return i + 1;
}