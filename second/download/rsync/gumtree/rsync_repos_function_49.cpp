static void send_sums(struct sum_struct *s,int f_out)
{
  int i;

  /* tell the other guy how many we are going to be doing and how many
     bytes there are in the last chunk */
  write_int(f_out,s?s->count:0);
  write_int(f_out,s?s->n:block_size);
  write_int(f_out,s?s->remainder:0);
  if (s)
    for (i=0;i<s->count;i++) {
      write_int(f_out,s->sums[i].sum1);
      write_buf(f_out,s->sums[i].sum2,csum_length);
    }
  write_flush(f_out);
}