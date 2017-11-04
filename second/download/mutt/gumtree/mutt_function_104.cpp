static void print_fingerprint (pgp_key_t p) 
{
  int i = 0;

  printf ("fpr:::::::::");
  for (i = 0; i < p->fp_len; i++)
    printf ("%02X", p->fingerprint[i]);
  printf (":\n");

}