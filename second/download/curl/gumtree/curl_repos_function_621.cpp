static void read_ahead(struct testcase *test,
                       int convert /* if true, convert to ascii */)
{
  int i;
  char *p;
  int c;
  struct bf *b;
  struct tftphdr *dp;

  b = &bfs[nextone];              /* look at "next" buffer */
  if (b->counter != BF_FREE)      /* nop if not free */
    return;
  nextone = !nextone;             /* "incr" next buffer ptr */

  dp = &b->buf.hdr;

  if (convert == 0) {
    /* The former file reading code did this:
       b->counter = read(fileno(file), dp->th_data, SEGSIZE); */
    size_t copy_n = MIN(SEGSIZE, test->rcount);
    memcpy(dp->th_data, test->rptr, copy_n);

    /* decrease amount, advance pointer */
    test->rcount -= copy_n;
    test->rptr += copy_n;
    b->counter = (int)copy_n;
    return;
  }

  p = dp->th_data;
  for (i = 0 ; i < SEGSIZE; i++) {
    if (newline) {
      if (prevchar == '\n')
        c = '\n';       /* lf to cr,lf */
      else
        c = '\0';       /* cr to cr,nul */
      newline = 0;
    }
    else {
      if(test->rcount) {
        c=test->rptr[0];
        test->rptr++;
        test->rcount--;
      }
      else
        break;
      if (c == '\n' || c == '\r') {
        prevchar = c;
        c = '\r';
        newline = 1;
      }
    }
    *p++ = (char)c;
  }
  b->counter = (int)(p - dp->th_data);
}