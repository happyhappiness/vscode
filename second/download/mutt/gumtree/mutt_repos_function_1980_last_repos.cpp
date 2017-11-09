static void conf_print_strval (const char *v, FILE *out)
{
  for (; *v; v++)
  {
    if (*v < ' ' || *v & 0x80)
    {
      conf_char_to_escape ((unsigned int) *v, out);
      continue;
    }

    if (*v == '"'  || *v == '\\')
      fputc ('\\', out);
    fputc (*v, out);
  }
}