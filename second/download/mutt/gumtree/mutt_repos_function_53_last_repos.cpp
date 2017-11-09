int crypt_smime_send_menu (HEADER *msg)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, send_menu))
    return (CRYPT_MOD_CALL (SMIME, send_menu)) (msg);

  return 0;
}