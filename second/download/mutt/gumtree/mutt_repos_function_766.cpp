int smime_gpgme_verify_sender (HEADER *h)
{
  return verify_sender (h, GPGME_PROTOCOL_CMS);
}