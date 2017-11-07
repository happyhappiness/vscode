void pgp_invoke_import (const char *fname)
{
  char _fname[_POSIX_PATH_MAX + SHORT_STRING];
  char cmd[HUGE_STRING];
  struct pgp_command_context cctx;
  
  memset (&cctx, 0, sizeof (cctx));
  
  mutt_quote_filename (_fname, sizeof (_fname), fname);
  cctx.fname = _fname;
  cctx.signas = PgpSignAs;
  
  mutt_pgp_command (cmd, sizeof (cmd), &cctx, PgpImportCommand);
  mutt_system (cmd);
}