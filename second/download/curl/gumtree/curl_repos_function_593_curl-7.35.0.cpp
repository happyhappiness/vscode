static struct tftphdr *rw_init(int x)
{
  newline = 0;                    /* init crlf flag */
  prevchar = -1;
  bfs[0].counter =  BF_ALLOC;     /* pass out the first buffer */
  current = 0;
  bfs[1].counter = BF_FREE;
  nextone = x;                    /* ahead or behind? */
  return &bfs[0].buf.hdr;
}