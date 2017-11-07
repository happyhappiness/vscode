static void pgpring_dump_signatures (pgp_sig_t *sig)
{
  for (; sig; sig = sig->next)
  {
    if (sig->sigtype == 0x10 || sig->sigtype == 0x11 ||
	sig->sigtype == 0x12 || sig->sigtype == 0x13)
      printf ("sig::::%08lX%08lX::::::%X:\n",
	      sig->sid1, sig->sid2, sig->sigtype);
    else if (sig->sigtype == 0x20)
      printf ("rev::::%08lX%08lX::::::%X:\n",
	      sig->sid1, sig->sid2, sig->sigtype);
  }
}