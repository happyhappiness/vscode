static void start_debug (void)
{
  int i;
  char buf[_POSIX_PATH_MAX];
  char buf2[_POSIX_PATH_MAX];

  /* rotate the old debug logs */
  for (i=3; i>=0; i--)
  {
    snprintf (buf, sizeof(buf), "%s/.muttdebug%d", NONULL(Homedir), i);
    snprintf (buf2, sizeof(buf2), "%s/.muttdebug%d", NONULL(Homedir), i+1);
    rename (buf, buf2);
  }
  if ((debugfile = safe_fopen(buf, "w")) != NULL)
  {
    setbuf (debugfile, NULL); /* don't buffer the debugging output! */
    dprint(1,(debugfile,"Mutt/%s (%s) debugging at level %d\n",
	      MUTT_VERSION, ReleaseDate, debuglevel));
  }
}