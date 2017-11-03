static void sum_put(MDstruct *md,char *sum)
{
  SIVAL(sum,0,md->buffer[0]);
  if (csum_length <= 4) return;
  SIVAL(sum,4,md->buffer[1]);
  if (csum_length <= 8) return;
  SIVAL(sum,8,md->buffer[2]);
  if (csum_length <= 12) return;
  SIVAL(sum,12,md->buffer[3]);
}