static void make_sidebar_entry (char *buf, unsigned int buflen, int width, char *box,
                                SBENTRY *sbe)
{
  if (!buf || !box || !sbe)
    return;

  strfcpy (sbe->box, box, sizeof (sbe->box));

  mutt_FormatString (buf, buflen, 0, width, NONULL(SidebarFormat), cb_format_str, (unsigned long) sbe, 0);

  /* Force string to be exactly the right width */
  int w = mutt_strwidth (buf);
  int s = mutt_strlen (buf);
  width = MIN(buflen, width);
  if (w < width)
  {
    /* Pad with spaces */
    memset (buf + s, ' ', width - w);
    buf[s + width - w] = 0;
  }
  else if (w > width)
  {
    /* Truncate to fit */
    int len = mutt_wstr_trunc (buf, buflen, width, NULL);
    buf[len] = 0;
  }
}