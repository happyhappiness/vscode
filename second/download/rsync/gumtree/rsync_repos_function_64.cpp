void get_checksum2(char *buf,int len,char *sum)
{
  int i;
  MDstruct MD;

  MDbegin(&MD);

  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
    bcopy(buf+i,tmpchunk,CSUM_CHUNK);
    MDupdate(&MD, tmpchunk, CSUM_CHUNK*8);
  }

  bcopy(buf+i,tmpchunk,len-i);
  MDupdate(&MD, tmpchunk, (len-i)*8);

  sum_put(&MD,sum);
}