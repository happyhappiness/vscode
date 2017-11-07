void mutt_mktemp (char *s)
{
  snprintf (s, _POSIX_PATH_MAX, "%s/mutt-%s-%d-%d", NONULL (Tempdir), NONULL(Hostname), (int) getpid (), Counter++);
  unlink (s);
}