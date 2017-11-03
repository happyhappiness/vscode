int pgp_valid_passphrase (void)
{
  time_t now = time (NULL);

  if (pgp_use_gpg_agent())
    {
      *PgpPass = 0;
      return 1; /* handled by gpg-agent */
    }

  if (now < PgpExptime)
    /* Use cached copy.  */
    return 1;
  
  pgp_void_passphrase ();

  if (mutt_get_password (_("Enter PGP passphrase:"), PgpPass, sizeof (PgpPass)) == 0)
    {
      PgpExptime = time (NULL) + PgpTimeout;
      return (1);
    }
  else
    PgpExptime = 0;

  return 0;
}