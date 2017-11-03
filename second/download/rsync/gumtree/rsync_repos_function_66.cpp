void checksum_init(void)
{
  tmpchunk = (char *)malloc(CSUM_CHUNK);
  if (!tmpchunk) out_of_memory("checksum_init");
}