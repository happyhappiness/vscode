
  if (verbose > 2)
    fprintf(stderr,"hash search b=%d len=%d\n",s->n,(int)len);

  k = MIN(len, s->n);
  sum = get_checksum1(buf, k);
  s1 = sum;
  s2 = sum >> 16;
  if (verbose > 3)
    fprintf(stderr, "sum=%.8x k=%d\n", sum, k);

  offset = 0;

