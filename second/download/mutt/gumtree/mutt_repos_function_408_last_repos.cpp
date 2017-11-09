static pid_t smime_invoke (FILE **smimein, FILE **smimeout, FILE **smimeerr,
			   int smimeinfd, int smimeoutfd, int smimeerrfd,
			   const char *fname,
			   const char *sig_fname,
			   const char *cryptalg,
			   const char *digestalg,
			   const char *key,
			   const char *certificates,
			   const char *intermediates,
			   const char *format)
{
  struct smime_command_context cctx;
  char cmd[HUGE_STRING];
  
  memset (&cctx, 0, sizeof (cctx));

  if (!format || !*format)
    return (pid_t) -1;
  
  cctx.fname	       = fname;
  cctx.sig_fname       = sig_fname;
  cctx.key	       = key;
  cctx.cryptalg	       = cryptalg;
  cctx.digestalg       = digestalg;
  cctx.certificates    = certificates;
  cctx.intermediates   = intermediates;
  
  mutt_smime_command (cmd, sizeof (cmd), &cctx, format);

  return mutt_create_filter_fd (cmd, smimein, smimeout, smimeerr,
				smimeinfd, smimeoutfd, smimeerrfd);
}