static int crypt_mod_smime_verify_sender (HEADER *h)
{
  return smime_verify_sender (h);
}