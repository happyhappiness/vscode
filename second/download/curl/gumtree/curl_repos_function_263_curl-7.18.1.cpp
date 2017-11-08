static struct tftphdr *
rw_init(int x)              /* init for either read-ahead or write-behind */
{                           /* zero for write-behind, one for read-head */
  newline = 0;            /* init crlf flag */
  prevchar = -1;
  bfs[0].counter =  BF_ALLOC;     /* pass out the first buffer */
  current = 0;
  bfs[1].counter = BF_FREE;
  nextone = x;                    /* ahead or behind? */
  return (struct tftphdr *)bfs[0].buf;
}