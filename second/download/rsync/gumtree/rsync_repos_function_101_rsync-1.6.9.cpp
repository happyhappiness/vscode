void sum_update(char *p,int len)
{
  int i;
  if (len + sumresidue < CSUM_CHUNK) {
    bcopy(p,sumrbuf+sumresidue,len);
    sumresidue += len;
    return;
  }

  if (sumresidue) {
    i = MIN(CSUM_CHUNK-sumresidue,len);
    bcopy(p,sumrbuf+sumresidue,i);
    MDupdate(&sumMD, sumrbuf, (i+sumresidue)*8);
    len -= i;
    p += i;
  }

  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
    bcopy(p+i,sumrbuf,CSUM_CHUNK);
    MDupdate(&sumMD, sumrbuf, CSUM_CHUNK*8);
  }

  if (len - i > 0) {
    sumresidue = len-i;
    bcopy(p+i,sumrbuf,sumresidue);
  } else {
    sumresidue = 0;    
  }
}