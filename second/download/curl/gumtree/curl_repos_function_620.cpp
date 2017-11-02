static int readit(struct testcase *test, struct tftphdr **dpp,
                  int convert /* if true, convert to ascii */)
{
  struct bf *b;

  bfs[current].counter = BF_FREE; /* free old one */
  current = !current;             /* "incr" current */

  b = &bfs[current];              /* look at new buffer */
  if (b->counter == BF_FREE)      /* if it's empty */
    read_ahead(test, convert);    /* fill it */

  *dpp = &b->buf.hdr;             /* set caller's ptr */
  return b->counter;
}