static const char *
folder_format_str (char *dest, size_t destlen, size_t col, int cols, char op, const char *src,
		   const char *fmt, const char *ifstring, const char *elsestring,
		   unsigned long data, format_flag flags)
{
  char fn[SHORT_STRING], tmp[SHORT_STRING], permission[11];
  char date[SHORT_STRING], *t_fmt;
  time_t tnow;
  FOLDER *folder = (FOLDER *) data;
  struct passwd *pw;
  struct group *gr;
  int optional = (flags & MUTT_FORMAT_OPTIONAL);

  switch (op)
  {
    case 'C':
      snprintf (tmp, sizeof (tmp), "%%%sd", fmt);
      snprintf (dest, destlen, tmp, folder->num + 1);
      break;
      
    case 'd':
    case 'D':
      if (folder->ff->local)
      {
	int do_locales = TRUE;

	if (op == 'D') {
	  t_fmt = NONULL(DateFmt);
	  if (*t_fmt == '!') {
	    ++t_fmt;
	    do_locales = FALSE;
	  }
	} else {
	  tnow = time (NULL);
	  t_fmt = tnow - folder->ff->mtime < 31536000 ? "%b %d %H:%M" : "%b %d  %Y";
	}

        if (!do_locales)
          setlocale (LC_TIME, "C");
        strftime (date, sizeof (date), t_fmt, localtime (&folder->ff->mtime));
        if (!do_locales)
          setlocale (LC_TIME, "");

	mutt_format_s (dest, destlen, fmt, date);
      }
      else
	mutt_format_s (dest, destlen, fmt, "");
      break;
      
    case 'f':
    {
      char *s;
#ifdef USE_IMAP
      if (folder->ff->imap)
	s = NONULL (folder->ff->desc);
      else
#endif
	s = NONULL (folder->ff->name);

      snprintf (fn, sizeof (fn), "%s%s", s,
		folder->ff->local ? (S_ISLNK (folder->ff->mode) ? "@" :
				  (S_ISDIR (folder->ff->mode) ? "/" :
				   ((folder->ff->mode & S_IXUSR) != 0 ? "*" : ""))) : "");
      
      mutt_format_s (dest, destlen, fmt, fn);
      break;
    }
    case 'F':
      if (folder->ff->local)
      {
	snprintf (permission, sizeof (permission), "%c%c%c%c%c%c%c%c%c%c",
		  S_ISDIR(folder->ff->mode) ? 'd' : (S_ISLNK(folder->ff->mode) ? 'l' : '-'),
		  (folder->ff->mode & S_IRUSR) != 0 ? 'r': '-',
		  (folder->ff->mode & S_IWUSR) != 0 ? 'w' : '-',
		  (folder->ff->mode & S_ISUID) != 0 ? 's' : (folder->ff->mode & S_IXUSR) != 0 ? 'x': '-',
		  (folder->ff->mode & S_IRGRP) != 0 ? 'r' : '-',
		  (folder->ff->mode & S_IWGRP) != 0 ? 'w' : '-',
		  (folder->ff->mode & S_ISGID) != 0 ? 's' : (folder->ff->mode & S_IXGRP) != 0 ? 'x': '-',
		  (folder->ff->mode & S_IROTH) != 0 ? 'r' : '-',
		  (folder->ff->mode & S_IWOTH) != 0 ? 'w' : '-',
		  (folder->ff->mode & S_ISVTX) != 0 ? 't' : (folder->ff->mode & S_IXOTH) != 0 ? 'x': '-');
	mutt_format_s (dest, destlen, fmt, permission);
      }
#ifdef USE_IMAP
      else if (folder->ff->imap)
      {
	/* mark folders with subfolders AND mail */
	snprintf (permission, sizeof (permission), "IMAP %c",
		  (folder->ff->inferiors && folder->ff->selectable) ? '+' : ' ');
	mutt_format_s (dest, destlen, fmt, permission);
      }                                        
#endif
      else
	mutt_format_s (dest, destlen, fmt, "");
      break;
      
    case 'g':
      if (folder->ff->local)
      {
	if ((gr = getgrgid (folder->ff->gid)))
	  mutt_format_s (dest, destlen, fmt, gr->gr_name);
	else
	{
	  snprintf (tmp, sizeof (tmp), "%%%sld", fmt);
	  snprintf (dest, destlen, tmp, folder->ff->gid);
	}
      }
      else
	mutt_format_s (dest, destlen, fmt, "");
      break;
      
    case 'l':
      if (folder->ff->local)
      {
	snprintf (tmp, sizeof (tmp), "%%%sd", fmt);
	snprintf (dest, destlen, tmp, folder->ff->nlink);
      }
      else
	mutt_format_s (dest, destlen, fmt, "");
      break;

    case 'm':
      if (!optional)
      {
        if (folder->ff->has_buffy)
        {
          snprintf (tmp, sizeof (tmp), "%%%sd", fmt);
          snprintf (dest, destlen, tmp, folder->ff->msg_count);
        }
        else
          mutt_format_s (dest, destlen, fmt, "");
      }
      else if (!folder->ff->msg_count)
        optional = 0;
      break;

    case 'N':
      snprintf (tmp, sizeof (tmp), "%%%sc", fmt);
      snprintf (dest, destlen, tmp, folder->ff->new ? 'N' : ' ');
      break;

    case 'n':
      if (!optional)
      {
        if (folder->ff->has_buffy)
        {
          snprintf (tmp, sizeof (tmp), "%%%sd", fmt);
          snprintf (dest, destlen, tmp, folder->ff->msg_unread);
        }
        else
          mutt_format_s (dest, destlen, fmt, "");
      }
      else if (!folder->ff->msg_unread)
        optional = 0;
      break;

    case 's':
      if (folder->ff->local)
      {
	mutt_pretty_size(fn, sizeof(fn), folder->ff->size);
	snprintf (tmp, sizeof (tmp), "%%%ss", fmt);
	snprintf (dest, destlen, tmp, fn);
      }
      else
	mutt_format_s (dest, destlen, fmt, "");
      break;

    case 't':
      snprintf (tmp, sizeof (tmp), "%%%sc", fmt);
      snprintf (dest, destlen, tmp, folder->ff->tagged ? '*' : ' ');
      break;

    case 'u':
      if (folder->ff->local)
      {
	if ((pw = getpwuid (folder->ff->uid)))
	  mutt_format_s (dest, destlen, fmt, pw->pw_name);
	else
	{
	  snprintf (tmp, sizeof (tmp), "%%%sld", fmt);
	  snprintf (dest, destlen, tmp, folder->ff->uid);
	}
      }
      else
	mutt_format_s (dest, destlen, fmt, "");
      break;

    default:
      snprintf (tmp, sizeof (tmp), "%%%sc", fmt);
      snprintf (dest, destlen, tmp, op);
      break;
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, cols, ifstring, folder_format_str, data, 0);
  else if (flags & MUTT_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, cols, elsestring, folder_format_str, data, 0);

  return (src);
}