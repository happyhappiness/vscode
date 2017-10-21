
  if (verbose > 2)
    fprintf(FERROR,"hash search b=%d len=%d\n",s->n,(int)len);

  k = MIN(len, s->n);

  map = map_ptr(buf,0,k);

  sum = get_checksum1(map, k);
  s1 = sum & 0xFFFF;
  s2 = sum >> 16;
  if (verbose > 3)
    fprintf(FERROR, "sum=%.8x k=%d\n", sum, k);
