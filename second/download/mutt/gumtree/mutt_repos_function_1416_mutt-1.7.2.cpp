void mutt_pgp_command (char *d, size_t dlen, struct pgp_command_context *cctx, const char *fmt)
{
  mutt_FormatString (d, dlen, 0, MuttIndexWindow->cols, NONULL (fmt), _mutt_fmt_pgp_command, (unsigned long) cctx, 0);
  dprint (2, (debugfile, "mutt_pgp_command: %s\n", d));
}