static int sgml_fputs (const char *s, FILE *out)
{
  for (; *s; s++)
    if (sgml_fputc ((unsigned int) *s, out) == EOF)
      return EOF;

  return 0;
}