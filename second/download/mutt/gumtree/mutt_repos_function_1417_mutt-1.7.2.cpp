static pid_t pgp_invoke (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			 int pgpinfd, int pgpoutfd, int pgperrfd,
			 short need_passphrase,
			 const char *fname,
			 const char *sig_fname,
			 const char *signas,
			 const char *ids,
			 const char *format)
{
  struct pgp_command_context cctx;
  char cmd[HUGE_STRING];
  
  memset (&cctx, 0, sizeof (cctx));

  if (!format || !*format)
    return (pid_t) -1;
  
  cctx.need_passphrase = need_passphrase;
  cctx.fname	       = fname;
  cctx.sig_fname       = sig_fname;
  cctx.signas	       = signas;
  cctx.ids	       = ids;
  
  mutt_pgp_command (cmd, sizeof (cmd), &cctx, format);
  
  return mutt_create_filter_fd (cmd, pgpin, pgpout, pgperr,
			       pgpinfd, pgpoutfd, pgperrfd);
}