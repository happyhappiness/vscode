static int sgml_fputc (int c, FILE *out)
{
  switch (c)
  {
    case '<': return fputs ("&lt;", out);
    case '>': return fputs ("&gt;", out);
    case '$': return fputs ("&dollar;", out);
    case '_': return fputs ("&lowbar;", out);
    case '%': return fputs ("&percnt;", out);
    case '&': return fputs ("&amp;", out);
    case '\\': return fputs ("&bsol;", out);
    case '"': return fputs ("&dquot;", out);
    case '[': return fputs ("&lsqb;", out);
    case ']': return fputs ("&rsqb;", out);
    case '~': return fputs ("&tilde;", out);
    default:  return fputc (c, out);
  }
}