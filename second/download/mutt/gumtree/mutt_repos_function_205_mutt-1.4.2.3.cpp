int pgp_valid_passphrase (void)
{
  time_t now = time (NULL);

# if defined(HAVE_SETRLIMIT) && (!defined(DEBUG))
  disable_coredumps ();
# endif

  if (now < PgpExptime) return 1; /* just use the cached copy. */
  pgp_void_passphrase ();

  if (mutt_get_password (_("Enter PGP passphrase:"), PgpPass, sizeof (PgpPass)) == 0)
  {
    PgpExptime = time (NULL) + PgpTimeout;
    return (1);
  }
  else
  {
    PgpExptime = 0;
    return (0);
  }
  /* not reached */
}