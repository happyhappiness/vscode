static void _pgp_free_key (pgp_key_t ** kpp)
{
  pgp_key_t *kp;

  if (!kpp || !*kpp)
    return;

  kp = *kpp;

  pgp_free_uid (&kp->address);
  safe_free ((void **) &kp->keyid);
  safe_free ((void **) kpp);
}