static void sgml_print_strval (const char *v, FILE *out)
{
  char buff[16];
  for (; *v; v++)
  {
    if (*v <  ' ' || *v & 0x80)
    {
      char_to_escape (buff, (unsigned int) *v);
      sgml_fputs (buff, out);
      continue;
    }
    sgml_fputc ((unsigned int) *v, out);
  }
}