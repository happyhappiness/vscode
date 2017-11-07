int pop_fetch_data (POP_DATA *pop_data, char *query, progress_t *progressbar,
		    int (*funct) (char *, void *), void *data)
{
  char buf[LONG_STRING];
  char *inbuf;
  char *p;
  int ret, chunk = 0;
  long pos = 0;
  size_t lenbuf = 0;

  strfcpy (buf, query, sizeof (buf));
  ret = pop_query (pop_data, buf, sizeof (buf));
  if (ret < 0)
    return ret;

  inbuf = safe_malloc (sizeof (buf));

  FOREVER
  {
    chunk = mutt_socket_readln_d (buf, sizeof (buf), pop_data->conn, MUTT_SOCK_LOG_HDR);
    if (chunk < 0)
    {
      pop_data->status = POP_DISCONNECTED;
      ret = -1;
      break;
    }

    p = buf;
    if (!lenbuf && buf[0] == '.')
    {
      if (buf[1] != '.')
	break;
      p++;
    }

    strfcpy (inbuf + lenbuf, p, sizeof (buf));
    pos += chunk;

    /* cast is safe since we break out of the loop when chunk<=0 */
    if ((size_t)chunk >= sizeof (buf))
    {
      lenbuf += strlen (p);
    }
    else
    {
      if (progressbar)
	mutt_progress_update (progressbar, pos, -1);
      if (ret == 0 && funct (inbuf, data) < 0)
	ret = -3;
      lenbuf = 0;
    }

    safe_realloc (&inbuf, lenbuf + sizeof (buf));
  }

  FREE (&inbuf);
  return ret;
}