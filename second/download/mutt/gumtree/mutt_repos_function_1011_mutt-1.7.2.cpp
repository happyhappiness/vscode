static int valid_pgp_encrypted_handler (BODY *b, STATE *s)
{
  int rc;
  BODY *octetstream;

  octetstream = b->parts->next;
  rc = crypt_pgp_encrypted_handler (octetstream, s);
  b->goodsig |= octetstream->goodsig;

  return rc;
}