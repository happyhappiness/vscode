static int writeit(struct testcase *test, struct tftphdr **dpp,
                   int ct, int convert)
{
  bfs[current].counter = ct;      /* set size of data to write */
  current = !current;             /* switch to other buffer */
  if (bfs[current].counter != BF_FREE)     /* if not free */
    write_behind(test, convert);     /* flush it */
  bfs[current].counter = BF_ALLOC;        /* mark as alloc'd */
  *dpp =  (struct tftphdr *)bfs[current].buf;
  return ct;                      /* this is a lie of course */
}