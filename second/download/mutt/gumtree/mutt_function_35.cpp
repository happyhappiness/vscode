static void start_debug (void)
{
  time_t t;
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
    t = time (0);
    setbuf (debugfile, NULL); /* don't buffer the debugging output! */
    fprintf (debugfile, "Mutt %s started at %s.\nDebugging at level %d.\n\n",
	     MUTT_VERSION, asctime (localtime (&t)), debuglevel);
  }
}