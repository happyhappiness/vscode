void _mutt_mktemp (char *s, size_t slen, const char *prefix, const char *suffix,
                   const char *src, int line)
{
  size_t n = snprintf (s, slen, "%s/%s-%s-%d-%d-%ld%ld%s%s",
      NONULL (Tempdir), NONULL (prefix), NONULL (Hostname),
      (int) getuid (), (int) getpid (), random (), random (),
      suffix ? "." : "", NONULL (suffix));
  if (n >= slen)
    dprint (1, (debugfile, "%s:%d: ERROR: insufficient buffer space to hold temporary filename! slen=%zu but need %zu\n",
	    src, line, slen, n));
  dprint (3, (debugfile, "%s:%d: mutt_mktemp returns \"%s\".\n", src, line, s));
  if (unlink (s) && errno != ENOENT)
    dprint (1, (debugfile, "%s:%d: ERROR: unlink(\"%s\"): %s (errno %d)\n", src, line, s, strerror (errno), errno));
}