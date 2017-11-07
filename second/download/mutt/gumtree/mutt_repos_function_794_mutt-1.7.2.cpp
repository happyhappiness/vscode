static const char *
compose_format_str (char *buf, size_t buflen, size_t col, int cols, char op, const char *src,
		   const char *prefix, const char *ifstring,
		   const char *elsestring,
		   unsigned long data, format_flag flags)
{
  char fmt[SHORT_STRING], tmp[SHORT_STRING];
  int optional = (flags & MUTT_FORMAT_OPTIONAL);
  MUTTMENU *menu = (MUTTMENU *) data;

  *buf = 0;
  switch (op)
  {
    case 'a': /* total number of attachments */
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, menu->max);
      break;

    case 'h':  /* hostname */
      snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
      snprintf (buf, buflen, fmt, NONULL(Hostname));
      break;

    case 'l': /* approx length of current message in bytes */
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	mutt_pretty_size (tmp, sizeof (tmp), menu ? cum_attachs_size(menu) : 0);
	snprintf (buf, buflen, fmt, tmp);
      break;

    case 'v':
      snprintf (fmt, sizeof (fmt), "Mutt %%s");
      snprintf (buf, buflen, fmt, MUTT_VERSION);
      break;

    case 0:
      *buf = 0;
      return (src);

    default:
      snprintf (buf, buflen, "%%%s%c", prefix, op);
      break;
  }

  if (optional)
    compose_status_line (buf, buflen, col, cols, menu, ifstring);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    compose_status_line (buf, buflen, col, cols, menu, elsestring);

  return (src);
}