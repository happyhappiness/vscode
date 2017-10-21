
static void hash_search(int f,struct sum_struct *s,char *buf,off_t len)
{
  int offset,j,k;
  int end;
  char sum2[SUM_LENGTH];
  uint32 s1, s2, sum; 
  char *map;

  if (verbose > 2)
    fprintf(stderr,"hash search b=%d len=%d\n",s->n,(int)len);

  k = MIN(len, s->n);

  map = map_ptr(buf,0,k);

  sum = get_checksum1(map, k);
  s1 = sum & 0xFFFF;
  s2 = sum >> 16;
  if (verbose > 3)
    fprintf(stderr, "sum=%.8x k=%d\n", sum, k);

  offset = 0;
