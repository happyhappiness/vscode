void pgp_void_passphrase (void)
{
  memset (PgpPass, 0, sizeof (PgpPass));
  PgpExptime = 0;
}