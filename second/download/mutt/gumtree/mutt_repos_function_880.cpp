static const char *
status_format_str (char *buf, size_t buflen, size_t col, int cols, char op, const char *src,
		   const char *prefix, const char *ifstring,
		   const char *elsestring,
		   unsigned long data, format_flag flags)
{
  char fmt[SHORT_STRING], tmp[SHORT_STRING], *cp;
  int count, optional = (flags & MUTT_FORMAT_OPTIONAL);
  MUTTMENU *menu = (MUTTMENU *) data;

  *buf = 0;
  switch (op)
  {
    case 'b':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, mutt_buffy_check (0));
      }
      else if (!mutt_buffy_check (0))
	optional = 0;
      break;

    case 'd':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->deleted : 0);
      }
      else if (!Context || !Context->deleted)
	optional = 0;
      break;

    case 'f':
      snprintf (fmt, sizeof(fmt), "%%%ss", prefix);
      if (Context && Context->path)
      {
	strfcpy (tmp, Context->path, sizeof (tmp));
	mutt_pretty_mailbox (tmp, sizeof (tmp));
      }
      else
	strfcpy (tmp, _("(no mailbox)"), sizeof (tmp));
      snprintf (buf, buflen, fmt, tmp);
      break;

    case 'F':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->flagged : 0);
      }
      else if (!Context || !Context->flagged)
	optional = 0;
      break;

    case 'h':
      snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
      snprintf (buf, buflen, fmt, NONULL(Hostname));
      break;

    case 'l':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	mutt_pretty_size (tmp, sizeof (tmp), Context ? Context->size : 0);
	snprintf (buf, buflen, fmt, tmp);
      }
      else if (!Context || !Context->size)
	optional = 0;
      break;

    case 'L':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
	mutt_pretty_size (tmp, sizeof (tmp), Context ? Context->vsize: 0);
	snprintf (buf, buflen, fmt, tmp);
      }
      else if (!Context || !Context->pattern)
	optional = 0;
      break;

    case 'm':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->msgcount : 0);
      }
      else if (!Context || !Context->msgcount)
	optional = 0;
      break;

    case 'M':
      if (!optional)
      {
	snprintf (fmt, sizeof(fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->vcount : 0);
      }
      else if (!Context || !Context->pattern)
	optional = 0;
      break;

    case 'n':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->new : 0);
      }
      else if (!Context || !Context->new)
	optional = 0;
      break;

    case 'o':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->unread - Context->new : 0);
      }
      else if (!Context || !(Context->unread - Context->new))
	optional = 0;
      break;

    case 'p':
      count = mutt_num_postponed (0);
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, count);
      }
      else if (!count)
	optional = 0;
      break;

    case 'P':
      if (!menu)
	break;
      if (menu->top + menu->pagelen >= menu->max)
	cp = menu->top ? "end" : "all";
      else
      {
	count = (100 * (menu->top + menu->pagelen)) / menu->max;
	snprintf (tmp, sizeof (tmp), "%d%%", count);
	cp = tmp;
      }
      snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
      snprintf (buf, buflen, fmt, cp);
      break;

    case 'r':
    {
      size_t i = 0;

      if (Context)
      {
	i = option(OPTATTACHMSG) ? 3 : ((Context->readonly ||
          Context->dontwrite) ? 2 : (Context->changed ||
          /* deleted doesn't necessarily mean changed in IMAP */
          (Context->magic != MUTT_IMAP &&
           Context->deleted)) ? 1 : 0);
      }
      
      if (!StChars)
	buf[0] = 0;
      else if (i >= mutt_strlen(StChars))
	buf[0] = StChars[0];
      else
	buf[0] = StChars[i];

      buf[1] = 0;
      break;
    }
      
    case 's':
      snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
      snprintf (buf, buflen, fmt,
		get_sort_str (tmp, sizeof (tmp), Sort));
      break;

    case 'S':
      snprintf (fmt, sizeof (fmt), "%%%ss", prefix);
      snprintf (buf, buflen, fmt,
		get_sort_str (tmp, sizeof (tmp), SortAux));
      break;

    case 't':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->tagged : 0);
      }
      else if (!Context || !Context->tagged)
	optional = 0;
      break;

    case 'u':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (buf, buflen, fmt, Context ? Context->unread : 0);
      }
      else if (!Context || !Context->unread)
	optional = 0;
      break;

    case 'v':
      snprintf (fmt, sizeof (fmt), "Mutt %%s");
      snprintf (buf, buflen, fmt, MUTT_VERSION);
      break;

    case 'V':
      if (!optional)
      {
	snprintf (fmt, sizeof(fmt), "%%%ss", prefix);
	snprintf (buf, buflen, fmt, (Context && Context->pattern) ? Context->pattern : "");
      }
      else if (!Context || !Context->pattern)
	optional = 0;
      break;

    case 0:
      *buf = 0;
      return (src);

    default:
      snprintf (buf, buflen, "%%%s%c", prefix, op);
      break;
  }

  if (optional)
    _menu_status_line (buf, buflen, col, cols, menu, ifstring);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    _menu_status_line (buf, buflen, col, cols, menu, elsestring);

  return (src);
}