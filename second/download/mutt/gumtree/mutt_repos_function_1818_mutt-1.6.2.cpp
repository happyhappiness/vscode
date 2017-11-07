static int sgml_fputc (int c, FILE *out)
{
  switch (c)
  {
    /* the bare minimum for escaping */
    case '<': return fputs ("&lt;", out);
    case '>': return fputs ("&gt;", out);
    case '&': return fputs ("&amp;", out);
    default:  return fputc (c, out);
  }
}