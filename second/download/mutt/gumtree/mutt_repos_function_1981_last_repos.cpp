static void man_print_strval (const char *v, FILE *out)
{
  for (; *v; v++)
  {
    if (*v < ' ' || *v & 0x80)
    {
      fputc ('\\', out);
      conf_char_to_escape ((unsigned int) *v, out);
      continue;
    }
    
    if (*v == '"')
      fputs ("\\(rq", out);
    else if (*v == '\\')
      fputs ("\\\\", out);
    else if (*v == '-')
      fputs ("\\-", out);
    else
      fputc (*v, out);
  }
}