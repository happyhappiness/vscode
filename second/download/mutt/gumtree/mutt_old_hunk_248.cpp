  /* (postponment) save the Fcc: using a special X-Mutt- header so that
   * it can be picked up when the message is recalled
   */
  if (post && fcc)
    fprintf (msg->fp, "X-Mutt-Fcc: %s\n", fcc);

  if (f.magic == M_MMDF || f.magic == M_MBOX)
    fprintf (msg->fp, "Status: RO\n");

  /* mutt_write_rfc822_header() only writes out a Date: header with
   * mode == 0, i.e. _not_ postponment; so write out one ourself */
  if (post)
    fprintf (msg->fp, "%s", mutt_make_date (buf, sizeof (buf)));
