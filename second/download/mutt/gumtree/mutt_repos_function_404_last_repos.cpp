void smime_void_passphrase (void)
{
  memset (SmimePass, 0, sizeof (SmimePass));
  SmimeExptime = 0;
}