void pgp_invoke_getkeys (ADDRESS *addr)
{
  char buff[LONG_STRING];
  char tmp[LONG_STRING];
  char cmd[HUGE_STRING];
  int devnull;

  char *personal;
  
  struct pgp_command_context cctx;

  if (!PgpGetkeysCommand) return;
  
  memset (&cctx, 0, sizeof (cctx));

  personal = addr->personal;
  addr->personal = NULL;
  
  *tmp = '\0';
  mutt_addrlist_to_local (addr);
  rfc822_write_address_single (tmp, sizeof (tmp), addr, 0);
  mutt_quote_filename (buff, sizeof (buff), tmp);

  addr->personal = personal;
  
  cctx.ids = buff;
  
  mutt_pgp_command (cmd, sizeof (cmd), &cctx, PgpGetkeysCommand);

  devnull = open ("/dev/null", O_RDWR);

  if (!isendwin ()) mutt_message  _("Fetching PGP key...");

  mutt_system (cmd);

  if (!isendwin ()) mutt_clear_error ();

  close (devnull);
}