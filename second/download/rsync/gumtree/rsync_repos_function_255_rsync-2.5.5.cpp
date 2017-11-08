void checksum_init(void)
{
  if (remote_version >= 14)
    csum_length = 2; /* adaptive */
  else
    csum_length = SUM_LENGTH;
}