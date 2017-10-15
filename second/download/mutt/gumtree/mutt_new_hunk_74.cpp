  }
#endif
}

/* This function allows the user to specify a command to read stdout from in
   place of a normal file.  If the last character in the string is a pipe (|),
   then we assume it is a command to run instead of a normal file. */
FILE *mutt_open_read (const char *path, pid_t *thepid)
{
  FILE *f;
  struct stat s;

  int len = mutt_strlen (path);

  if (path[len - 1] == '|')
  {
    /* read from a pipe */

    char *s = safe_strdup (path);

    s[len - 1] = 0;
    mutt_endwin (NULL);
    *thepid = mutt_create_filter (s, NULL, &f, NULL);
    FREE (&s);
  }
  else
  {
    if (stat (path, &s) < 0)
      return (NULL);
    if (S_ISDIR (s.st_mode))
    {
      errno = EINVAL;
      return (NULL);
    }
    f = fopen (path, "r");
    *thepid = -1;
  }
  return (f);
}

/* returns 0 if OK to proceed, -1 to abort, 1 to retry */
int mutt_save_confirm (const char *s, struct stat *st)
{
  char tmp[_POSIX_PATH_MAX];
  int ret = 0;
  int rc;
  int magic = 0;

  magic = mx_get_magic (s);

#ifdef USE_POP
  if (magic == M_POP)
  {
    mutt_error _("Can't save message to POP mailbox.");
    return 1;
  }
#endif

  if (magic > 0 && !mx_access (s, W_OK))
  {
    if (option (OPTCONFIRMAPPEND))
    {
      snprintf (tmp, sizeof (tmp), _("Append messages to %s?"), s);
      if ((rc = mutt_yesorno (tmp, M_YES)) == M_NO)
	ret = 1;
      else if (rc == -1)
	ret = -1;
    }
  }

  if (stat (s, st) != -1)
  {
    if (magic == -1)
    {
      mutt_error (_("%s is not a mailbox!"), s);
      return 1;
    }
  }
  else if (magic != M_IMAP)
  {
    st->st_mtime = 0;
    st->st_atime = 0;

    if (errno == ENOENT)
    {
      if (option (OPTCONFIRMCREATE))
      {
	snprintf (tmp, sizeof (tmp), _("Create %s?"), s);
	if ((rc = mutt_yesorno (tmp, M_YES)) == M_NO)
	  ret = 1;
	else if (rc == -1)
	  ret = -1;
      }
    }
    else
    {
      mutt_perror (s);
      return 1;
    }
  }

  CLEARLINE (LINES-1);
  return (ret);
}

void state_prefix_putc (char c, STATE *s)
{
  if (s->flags & M_PENDINGPREFIX)
  {
    state_reset_prefix (s);
    if (s->prefix)
      state_puts (s->prefix, s);
  }

  state_putc (c, s);

  if (c == '\n')
    state_set_prefix (s);
}

int state_printf (STATE *s, const char *fmt, ...)
{
  int rv;
  va_list ap;

  va_start (ap, fmt);
  rv = vfprintf (s->fpout, fmt, ap);
  va_end (ap);
  
  return rv;
}

void state_mark_attach (STATE *s)
{
  if ((s->flags & M_DISPLAY) && !mutt_strcmp (Pager, "builtin"))
    state_puts (AttachmentMarker, s);
}

void state_attach_puts (const char *t, STATE *s)
{
  if (*t != '\n') state_mark_attach (s);
  while (*t)
  {
    state_putc (*t, s);
    if (*t++ == '\n' && *t)
      if (*t != '\n') state_mark_attach (s);
  }
}

int state_putwc (wchar_t wc, STATE *s)
{
  char mb[MB_LEN_MAX] = "";
  int rc;

  if ((rc = wcrtomb (mb, wc, NULL)) < 0)
    return rc;
  if (fputs (mb, s->fpout) == EOF)
    return -1;
  return 0;
}

int state_putws (const wchar_t *ws, STATE *s)
{
  const wchar_t *p = ws;

  while (p && *p != L'\0')
  {
    if (state_putwc (*p, s) < 0)
      return -1;
    p++;
  }
  return 0;
}

void mutt_display_sanitize (char *s)
{
  for (; *s; s++)
  {
    if (!IsPrint (*s))
      *s = '?';
