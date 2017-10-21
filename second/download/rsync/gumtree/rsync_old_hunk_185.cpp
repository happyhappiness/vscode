}


static off_t last_match;


static void matched(int f,struct sum_struct *s,char *buf,off_t len,
		    int offset,int i)
{
  int n = offset - last_match;
  
  if (verbose > 2)
    if (i != -1)
      fprintf(FERROR,"match at %d last_match=%d j=%d len=%d n=%d\n",
	      (int)offset,(int)last_match,i,(int)s->sums[i].len,n);

  if (n > 0) {
    int l = 0;
    write_int(f,n);
    while (l < n) {
      int n1 = MIN(CHUNK_SIZE,n-l);
      write_buf(f,map_ptr(buf,last_match+l,n1),n1);
      l += n1;
    }
    data_transfer += n;
  }
  write_int(f,-(i+1));
  if (i != -1)
    last_match = offset + s->sums[i].len;
  if (n > 0)
    write_flush(f);
}


static void hash_search(int f,struct sum_struct *s,char *buf,off_t len)
{
  int offset,j,k;
  int end;
  char sum2[SUM_LENGTH];
  uint32 s1, s2, sum; 
  char *map;

  if (verbose > 2)
    fprintf(FERROR,"hash search b=%d len=%d\n",s->n,(int)len);

  k = MIN(len, s->n);

  map = map_ptr(buf,0,k);

  sum = get_checksum1(map, k);
  s1 = sum & 0xFFFF;
  s2 = sum >> 16;
  if (verbose > 3)
    fprintf(FERROR, "sum=%.8x k=%d\n", sum, k);
