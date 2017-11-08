void sum_init(void)
{
  char s[4];
  MDbegin(&sumMD);  
  sumresidue=0;
  SIVAL(s,0,checksum_seed);
  sum_update(s,4);
}