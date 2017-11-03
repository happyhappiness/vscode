static const char *
alias_format_str (char *dest, size_t destlen, size_t col, int cols, char op, const char *src,
		  const char *fmt, const char *ifstring, const char *elsestring,
		  unsigned long data, format_flag flags)
{
  char tmp[SHORT_STRING], adr[SHORT_STRING];
  ALIAS *alias = (ALIAS *) data;

  switch (op)
  {
    case 'f':
      snprintf (tmp, sizeof (tmp), "%%%ss", fmt);
      snprintf (dest, destlen, tmp, alias->del ? "D" : " ");
      break;
    case 'a':
      mutt_format_s (dest, destlen, fmt, alias->name);
      break;
    case 'r':
      adr[0] = 0;
      rfc822_write_address (adr, sizeof (adr), alias->addr, 1);
      snprintf (tmp, sizeof (tmp), "%%%ss", fmt);
      snprintf (dest, destlen, tmp, adr);
      break;
    case 'n':
      snprintf (tmp, sizeof (tmp), "%%%sd", fmt);
      snprintf (dest, destlen, tmp, alias->num + 1);
      break;
    case 't':
      dest[0] = alias->tagged ? '*' : ' ';
      dest[1] = 0;
      break;
  }

  return (src);
}