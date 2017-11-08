void get_checksum2(char *buf,int len,char *sum)
{
  char buf2[64];
  int i;
  MDstruct MD;

  MDbegin(&MD);
  for(i = 0; i + 64 <= len; i += 64) {
    bcopy(buf+i,buf2,64);
    MDupdate(&MD, buf2, 512);
  }
  bcopy(buf+i,buf2,len-i);
  MDupdate(&MD, buf2, (len-i)*8);
  SIVAL(sum,0,MD.buffer[0]);
  SIVAL(sum,4,MD.buffer[1]);
  SIVAL(sum,8,MD.buffer[2]);
  SIVAL(sum,12,MD.buffer[3]);
}