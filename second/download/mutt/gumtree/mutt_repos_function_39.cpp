void crypt_pgp_extract_keys_from_attachment_list (FILE *fp, int tag, BODY *top)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_extract_keys_from_attachment_list))
    (CRYPT_MOD_CALL (PGP, pgp_extract_keys_from_attachment_list)) (fp, tag, top);
}