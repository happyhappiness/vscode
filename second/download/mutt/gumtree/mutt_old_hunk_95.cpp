      putchar (*id);
    else
      printf ("\\x%02x", (*id) & 0xff);
  }
}

static void pgpring_dump_signatures (pgp_sig_t *sig)
{
  for (; sig; sig = sig->next)
  {
    if (sig->sigtype == 0x10 || sig->sigtype == 0x11 ||
	sig->sigtype == 0x12 || sig->sigtype == 0x13)
