static char *smime_key_flags (int flags)
{
  static char buff[3];

  if (!(flags & KEYFLAG_CANENCRYPT))
    buff[0] = '-';
  else
    buff[0] = 'e';

  if (!(flags & KEYFLAG_CANSIGN))
    buff[1] = '-';
  else
    buff[1] = 's';

  buff[2] = '\0';

  return buff;
}