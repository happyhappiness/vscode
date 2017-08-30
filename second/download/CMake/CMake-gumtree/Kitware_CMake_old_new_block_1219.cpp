{
  register int q;      /* Doesn't need to be long */

  if(num > 214748L)
    {    /* 2147483647/10000 */
    q = num / (den / 10000L);
    }
  else
    {
    q = 10000L * num / den;    /* Long calculations, though */
    }
  if (q < 0)
    {
    putc('-', stream);
    q = -q;
    }
  fprintf(stream, "%d.%02d%%", q / 100, q % 100);
}