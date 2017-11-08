void sum_end(char *sum)
{
  if (sumresidue)
    MDupdate(&sumMD, sumrbuf, sumresidue*8);

  SIVAL(sum,0,sumMD.buffer[0]);
  SIVAL(sum,4,sumMD.buffer[1]);
  SIVAL(sum,8,sumMD.buffer[2]);
  SIVAL(sum,12,sumMD.buffer[3]);  
}