void crypt_smime_invoke_import (char *infile, char *mailbox)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, smime_invoke_import))
    (CRYPT_MOD_CALL (SMIME, smime_invoke_import)) (infile, mailbox);
}