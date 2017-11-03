int safe_asprintf (char **strp, const char *fmt, ...)
{
  va_list ap;
  int n;

  va_start (ap, fmt);
  n = vasprintf (strp, fmt, ap);
  va_end (ap);

  /* GNU libc man page for vasprintf(3) states that the value of *strp
   * is undefined when the return code is -1.
   */
  if (n < 0)
  {
    mutt_error _("Out of memory!");
    sleep (1);
    mutt_exit (1);
  }

  if (n == 0)
  {
    /* Mutt convention is to use NULL for 0-length strings */
    FREE (strp); /* __FREE_CHECKED__ */
  }

  return n;
}