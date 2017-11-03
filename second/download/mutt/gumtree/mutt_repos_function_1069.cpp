static void _pgp_free_key (pgp_key_t *kpp)
{
  pgp_key_t kp;

  if (!kpp || !*kpp)
    return;

  kp = *kpp;

  pgp_free_uid (&kp->address);
  FREE (&kp->keyid);
  FREE (&kp->fingerprint);
  /* mutt_crypt.h: 'typedef struct pgp_keyinfo *pgp_key_t;' */
  FREE (kpp);		/* __FREE_CHECKED__ */
}