int crypt_pgp_send_menu (HEADER *msg)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, send_menu))
    return (CRYPT_MOD_CALL (PGP, send_menu)) (msg);

  return 0;
}