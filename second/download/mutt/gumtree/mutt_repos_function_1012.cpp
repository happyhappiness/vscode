static int malformed_pgp_encrypted_handler (BODY *b, STATE *s)
{
  int rc;
  BODY *octetstream;

  octetstream = b->parts->next->next;
  /* exchange encodes the octet-stream, so re-run it through the decoder */
  rc = run_decode_and_handler (octetstream, s, crypt_pgp_encrypted_handler, 0);
  b->goodsig |= octetstream->goodsig;

  return rc;
}