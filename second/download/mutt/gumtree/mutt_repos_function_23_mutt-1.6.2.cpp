void crypt_invoke_message (int type)
{
  if ((WithCrypto & APPLICATION_PGP) && (type & APPLICATION_PGP))
    mutt_message _("Invoking PGP...");
  else if ((WithCrypto & APPLICATION_SMIME) && (type & APPLICATION_SMIME))
    mutt_message _("Invoking S/MIME...");
}