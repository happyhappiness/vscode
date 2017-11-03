void mutt_debug (FILE *fp, const char *fmt, ...)
{
  va_list ap;
  time_t now = time (NULL);
  static char buf[23] = "";
  static time_t last = 0;

  if (now > last)
  {
    strftime (buf, sizeof (buf), "%Y-%m-%d %H:%M:%S", localtime (&now));
    last = now;
  }
  fprintf (fp, "[%s] ", buf);
  va_start (ap, fmt);
  vfprintf (fp, fmt, ap);
  va_end (ap);
}