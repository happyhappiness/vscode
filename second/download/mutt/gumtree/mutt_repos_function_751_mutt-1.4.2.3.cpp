void print_ref (FILE *out, int output_dollar, const char *ref)
{
  switch (OutputFormat)
  {
  case F_CONF:
  case F_MAN:
    if (output_dollar)
      putc ('$', out);
    fputs (ref, out);
    break;

  case F_SGML:
    fprintf (out, "<ref id=\"%s\" name=\"", ref);
    if (output_dollar)
      fputs ("&dollar;", out);
    sgml_fputs (ref, out);
    fputs ("\">", out);
    break;

  default:
    break;
  }
}