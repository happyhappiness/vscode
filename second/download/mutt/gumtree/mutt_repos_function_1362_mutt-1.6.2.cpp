void mutt_save_path (char *d, size_t dsize, ADDRESS *a)
{
  if (a && a->mailbox)
  {
    strfcpy (d, a->mailbox, dsize);
    if (!option (OPTSAVEADDRESS))
    {
      char *p;

      if ((p = strpbrk (d, "%@")))
	*p = 0;
    }
    mutt_strlower (d);
  }
  else
    *d = 0;
}