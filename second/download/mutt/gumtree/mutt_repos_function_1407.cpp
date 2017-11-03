const char *mutt_make_version (void)
{
  static char vstring[STRING];
  snprintf (vstring, sizeof (vstring), "Mutt %s (%s)",
	    MUTT_VERSION, ReleaseDate);
  return vstring;
}