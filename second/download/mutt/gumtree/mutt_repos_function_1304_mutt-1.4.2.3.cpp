static void imap_set_flag (IMAP_DATA* idata, int aclbit, int flag,
  const char *str, char *flags, size_t flsize)
{
  if (mutt_bit_isset (idata->rights, aclbit))
    if (flag)
      strncat (flags, str, flsize);
}