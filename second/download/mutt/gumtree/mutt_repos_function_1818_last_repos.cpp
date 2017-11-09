static const char *cb_format_str(char *dest, size_t destlen, size_t col, int cols, char op,
                                 const char *src, const char *prefix, const char *ifstring,
                                 const char *elsestring, unsigned long data, format_flag flags)
{
  SBENTRY *sbe = (SBENTRY *) data;
  unsigned int optional;
  char fmt[STRING];

  if (!sbe || !dest)
    return src;

  dest[0] = 0;	/* Just in case there's nothing to do */

  BUFFY *b = sbe->buffy;
  if (!b)
    return src;

  int c = Context && (mutt_strcmp (Context->realpath, b->realpath) == 0);

  optional = flags & MUTT_FORMAT_OPTIONAL;

  switch (op)
  {
    case 'B':
      mutt_format_s (dest, destlen, prefix, sbe->box);
      break;

    case 'd':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, c ? Context->deleted : 0);
      }
      else if ((c && Context->deleted == 0) || !c)
        optional = 0;
      break;

    case 'F':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, b->msg_flagged);
      }
      else if (b->msg_flagged == 0)
        optional = 0;
      break;

    case 'L':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, c ? Context->vcount : b->msg_count);
      }
      else if ((c && Context->vcount == b->msg_count) || !c)
        optional = 0;
      break;

    case 'N':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, b->msg_unread);
      }
      else if (b->msg_unread == 0)
        optional = 0;
      break;

    case 'n':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
        snprintf (dest, destlen, fmt, b->new ? 'N' : ' ');
      }
      else if (b->new == 0)
        optional = 0;
      break;

    case 'S':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, b->msg_count);
      }
      else if (b->msg_count == 0)
        optional = 0;
      break;

    case 't':
      if (!optional)
      {
        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, c ? Context->tagged : 0);
      }
      else if ((c && Context->tagged == 0) || !c)
        optional = 0;
      break;

    case '!':
      if (b->msg_flagged == 0)
        mutt_format_s (dest, destlen, prefix, "");
      else if (b->msg_flagged == 1)
        mutt_format_s (dest, destlen, prefix, "!");
      else if (b->msg_flagged == 2)
        mutt_format_s (dest, destlen, prefix, "!!");
      else
      {
        snprintf (fmt, sizeof (fmt), "%d!", b->msg_flagged);
        mutt_format_s (dest, destlen, prefix, fmt);
      }
      break;
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, SidebarWidth, ifstring,   cb_format_str, (unsigned long) sbe, flags);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, SidebarWidth, elsestring, cb_format_str, (unsigned long) sbe, flags);

  /* We return the format string, unchanged */
  return src;
}