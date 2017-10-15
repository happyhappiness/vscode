	    (int) tz / 60, (int) abs (tz) % 60);
  return (s);
}

/* wrapper around mutt_write_address() so we can handle very large
   recipient lists without needing a huge temporary buffer in memory */
void mutt_write_address_list (ADDRESS *adr, FILE *fp, int linelen)
{
  ADDRESS *tmp;
  char buf[LONG_STRING];
  int count = 0;
  int len;

  while (adr)
  {
    tmp = adr->next;
    adr->next = NULL;
    buf[0] = 0;
    rfc822_write_address (buf, sizeof (buf), adr);
    len = mutt_strlen (buf);
    if (count && linelen + len > 74)
    {
      if (count)
      {
	fputs ("\n\t", fp);
	linelen = len + 8; /* tab is usually about 8 spaces... */
      }
    }
    else
    {
      if (count && adr->mailbox)
      {
	fputc (' ', fp);
