void get_checksum2(char *buf,int len,char *sum)
{
  int i;
  MDstruct MD;
  static char *buf1 = NULL;
  static int len1 = 0;

  if (len > len1) {
    if (buf1) free(buf1);
    buf1 = (char *)malloc(len+4);
    len1 = len;
    if (!buf1) out_of_memory("get_checksum2");
  }

  MDbegin(&MD);

  bcopy(buf,buf1,len);
  if (checksum_seed) {
    SIVAL(buf1,len,checksum_seed);
    len += 4;
  }

  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
    MDupdate(&MD, buf1+i, CSUM_CHUNK*8);
  }
  MDupdate(&MD, buf1+i, (len-i)*8);

  sum_put(&MD,sum);
}