      printf ("\\x%02x", (*id) & 0xff);
  }
}

static void print_fingerprint (pgp_key_t p) 
{
  if (!p->fingerprint)
    return;

  printf ("fpr:::::::::%s:\n", p->fingerprint);
} /* print_fingerprint() */


static void pgpring_dump_signatures (pgp_sig_t *sig)
{
  for (; sig; sig = sig->next)
