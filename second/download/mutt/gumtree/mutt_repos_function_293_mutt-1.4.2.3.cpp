void mutt_perror (const char *s)
{
  char *p = strerror (errno);

  dprint (1, (debugfile, "%s: %s (errno = %d)\n", s, 
      p ? p : "unknown error", errno));
  mutt_error ("%s: %s (errno = %d)", s, p ? p : _("unknown error"), errno);
}