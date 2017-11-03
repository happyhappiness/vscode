void pgp_forget_passphrase (void)
{
  pgp_void_passphrase ();
  mutt_message _("PGP passphrase forgotten.");
}