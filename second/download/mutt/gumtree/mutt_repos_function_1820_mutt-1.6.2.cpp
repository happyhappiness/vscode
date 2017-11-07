static int sgml_id_fputs (const char *s, FILE* out)
{
  char id;

  if (*s == '<')
    s++;

  for (; *s; s++)
  {
    if (*s == '_')
      id = '-';
    else
      id = *s;
    if (*s == '>' && !*(s+1))
      break;

    if (fputc ((unsigned int) id, out) == EOF)
      return EOF;
  }

  return 0;
}