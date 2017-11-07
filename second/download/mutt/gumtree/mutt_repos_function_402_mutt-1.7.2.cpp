static void mutt_smime_command (char *d, size_t dlen,
				struct smime_command_context *cctx, const char *fmt)
{
  mutt_FormatString (d, dlen, 0, MuttIndexWindow->cols, NONULL(fmt), _mutt_fmt_smime_command,
		    (unsigned long) cctx, 0);
  dprint (2,(debugfile, "mutt_smime_command: %s\n", d));
}