      putchar (*id);
    else
      printf ("\\x%02x", (*id) & 0xff);
  }
}

static void print_fingerprint (pgp_key_t p) 
{
  int i = 0;

  printf ("fpr:::::::::");
  for (i = 0; i < p->fp_len; i++)
    printf ("%02X", p->fingerprint[i]);
  printf (":\n");

} /* print_fingerprint() */


static void pgpring_dump_signatures (pgp_sig_t *sig)
{
  for (; sig; sig = sig->next)
  {
    if (sig->sigtype == 0x10 || sig->sigtype == 0x11 ||
	sig->sigtype == 0x12 || sig->sigtype == 0x13)
