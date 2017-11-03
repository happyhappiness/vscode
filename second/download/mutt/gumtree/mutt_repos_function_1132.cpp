int rfc3676_handler (BODY * a, STATE * s)
{
  char *buf = NULL, *t = NULL;
  unsigned int quotelevel = 0, newql = 0, sigsep = 0;
  int buf_off = 0, delsp = 0, fixed = 0;
  size_t buf_len = 0, sz = 0;
  flowed_state_t fst;

  memset (&fst, 0, sizeof (fst));

  /* respect DelSp of RfC3676 only with f=f parts */
  if ((t = (char *) mutt_get_parameter ("delsp", a->parameter)))
  {
    delsp = mutt_strlen (t) == 3 && ascii_strncasecmp (t, "yes", 3) == 0;
    t = NULL;
    fst.delsp = 1;
  }

  dprint (4, (debugfile, "f=f: DelSp: %s\n", delsp ? "yes" : "no"));

  while ((buf = mutt_read_line (buf, &sz, s->fpin, NULL, 0)))
  {
    buf_len = mutt_strlen (buf);
    newql = get_quote_level (buf);

    /* end flowed paragraph (if we're within one) if quoting level
     * changes (should not but can happen, see RFC 3676, sec. 4.5.)
     */
    if (newql != quotelevel)
      flush_par (s, &fst);

    quotelevel = newql;
    buf_off = newql;

    /* respect sender's space-stuffing by removing one leading space */
    if (buf[buf_off] == ' ')
      buf_off++;

    /* test for signature separator */
    sigsep = ascii_strcmp (buf + buf_off, "-- ") == 0;

    /* a fixed line either has no trailing space or is the
     * signature separator */
    fixed = buf_len == buf_off || buf[buf_len - 1] != ' ' || sigsep;

    /* print fixed-and-standalone, fixed-and-empty and sigsep lines as
     * fixed lines */
    if ((fixed && (!fst.width || !buf_len)) || sigsep)
    {
      /* if we're within a flowed paragraph, terminate it */
      flush_par (s, &fst);
      print_fixed_line (buf + buf_off, s, quotelevel, &fst);
      continue;
    }

    /* for DelSp=yes, we need to strip one SP prior to CRLF on flowed lines */
    if (delsp && !fixed)
      buf[--buf_len] = '\0';

    print_flowed_line (buf + buf_off, s, quotelevel, &fst, fixed);
  }

  flush_par (s, &fst);

  FREE (&buf);
  return (0);
}