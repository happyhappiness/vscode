static const char * query_format_str (char *dest, size_t destlen, size_t col, int cols,
				      char op, const char *src,
				      const char *fmt, const char *ifstring,
				      const char *elsestring,
				      unsigned long data, format_flag flags)
{
  ENTRY *entry = (ENTRY *)data;
  QUERY *query = entry->data;
  char tmp[SHORT_STRING];
  char buf2[STRING] = "";
  int optional = (flags & MUTT_FORMAT_OPTIONAL);

  switch (op)
  {
  case 'a':
    rfc822_write_address (buf2, sizeof (buf2), query->addr, 1);
    snprintf (tmp, sizeof (tmp), "%%%ss", fmt);
    snprintf (dest, destlen, tmp, buf2);
    break;
  case 'c':
    snprintf (tmp, sizeof (tmp), "%%%sd", fmt);
    snprintf (dest, destlen, tmp, query->num + 1);
    break;
  case 'e':
    if (!optional)
    {
      snprintf (tmp, sizeof (tmp), "%%%ss", fmt);
      snprintf (dest, destlen, tmp, NONULL (query->other));
    }
    else if (!query->other || !*query->other)
      optional = 0;
    break;
  case 'n':
    snprintf (tmp, sizeof (tmp), "%%%ss", fmt);
    snprintf (dest, destlen, tmp, NONULL (query->name));
    break;
  case 't':
    snprintf (tmp, sizeof (tmp), "%%%sc", fmt);
    snprintf (dest, destlen, tmp, entry->tagged ? '*' : ' ');
    break;
  default:
    snprintf (tmp, sizeof (tmp), "%%%sc", fmt);
    snprintf (dest, destlen, tmp, op);
    break;
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, cols, ifstring, query_format_str, data, 0);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, cols, elsestring, query_format_str, data, 0);

  return src;
}