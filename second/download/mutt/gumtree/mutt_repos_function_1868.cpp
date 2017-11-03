static void conf_char_to_escape (unsigned int c , FILE *out)
{
  char buff[16];
  char_to_escape (buff, c);
  fputs (buff, out);
}