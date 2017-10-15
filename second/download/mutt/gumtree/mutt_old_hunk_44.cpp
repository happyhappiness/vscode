    rename (buf, buf2);
  }
  if ((debugfile = safe_fopen(buf, "w")) != NULL)
  {
    t = time (0);
    setbuf (debugfile, NULL); /* don't buffer the debugging output! */
    fprintf (debugfile, "Mutt %s started at %s.\nDebugging at level %d.\n\n",
	     MUTT_VERSION, asctime (localtime (&t)), debuglevel);
  }
}
#endif

static int mutt_execute_commands (LIST *p)
{
  BUFFER err, token;
  char errstr[SHORT_STRING];

  memset (&err, 0, sizeof (err));
  err.data = errstr;
  err.dsize = sizeof (errstr);
  memset (&token, 0, sizeof (token));
  for (; p; p = p->next)
  {
    if (mutt_parse_rc_line (p->data, &token, &err) != 0)
    {
      fprintf (stderr, _("Error in command line: %s\n"), err.data);
      FREE (&token.data);
      return (-1);
    }
  }
  FREE (&token.data);
  return 0;
}

void mutt_init (int skip_sys_rc, LIST *commands)
{
  struct passwd *pw;
  struct utsname utsname;
  char *p, buffer[STRING], error[STRING];
  int i, default_rc = 0, need_pause = 0;
  BUFFER err;

  memset (&err, 0, sizeof (err));
  err.data = error;
  err.dsize = sizeof (error);

  /* 
   * XXX - use something even more difficult to predict?
   */
  snprintf (AttachmentMarker, sizeof (AttachmentMarker),
	    "\033]9;%ld\a", (long) time (NULL));
