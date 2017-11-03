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
    fputs ("<link linkend=\"", out);
    sgml_id_fputs (ref, out);
    fputs ("\">", out);
    if (output_dollar)
      fputc ('$', out);
    sgml_fputs (ref, out);
    fputs ("</link>", out);
    break;

  default:
    break;
  }
}