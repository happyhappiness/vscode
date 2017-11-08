int Curl_HMAC_update(HMAC_context * ctxt,
                     const unsigned char * data,
                     unsigned int len)
{
  /* Update first hash calculation. */
  (*ctxt->hmac_hash->hmac_hupdate)(ctxt->hmac_hashctxt1, data, len);
  return 0;
}