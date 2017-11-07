static void print_fingerprint (pgp_key_t p) 
{
  if (!p->fingerprint)
    return;

  printf ("fpr:::::::::%s:\n", p->fingerprint);
}