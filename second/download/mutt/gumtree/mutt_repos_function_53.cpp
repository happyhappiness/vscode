int crypt_smime_send_menu (HEADER *msg, int *redraw)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, send_menu))
    return (CRYPT_MOD_CALL (SMIME, send_menu)) (msg, redraw);

  return 0;
}