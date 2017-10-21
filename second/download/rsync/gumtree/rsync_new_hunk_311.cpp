

void get_checksum2(char *buf,int len,char *sum)
{
  int i;
  MDstruct MD;
  static char *buf1;
  static int len1;

  if (len > len1) {
    if (buf1) free(buf1);
    buf1 = (char *)malloc(len+4);
    len1 = len;
    if (!buf1) out_of_memory("get_checksum2");
