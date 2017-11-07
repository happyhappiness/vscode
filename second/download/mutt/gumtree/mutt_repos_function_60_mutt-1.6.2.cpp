static int pad (FILE *f, int col, int i)
{
  char fmt[8];

  if (col < i)
  {
    snprintf (fmt, sizeof(fmt), "%%-%ds", i - col);
    fprintf (f, fmt, "");
    return (i);
  }
  fputc (' ', f);
  return (col + 1);
}