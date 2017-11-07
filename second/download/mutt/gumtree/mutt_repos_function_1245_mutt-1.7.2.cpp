void mutt_write_address_list (ADDRESS *adr, FILE *fp, int linelen, int display)
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
    rfc822_write_address (buf, sizeof (buf), adr, display);
    len = mutt_strlen (buf);
    if (count && linelen + len > 74)
    {
      fputs ("\n\t", fp);
      linelen = len + 8; /* tab is usually about 8 spaces... */
    }
    else
    {
      if (count && adr->mailbox)
      {
	fputc (' ', fp);
	linelen++;
      }
      linelen += len;
    }
    fputs (buf, fp);
    adr->next = tmp;
    if (!adr->group && adr->next && adr->next->mailbox)
    {
      linelen++;
      fputc (',', fp);
    }
    adr = adr->next;
    count++;
  }
  fputc ('\n', fp);
}