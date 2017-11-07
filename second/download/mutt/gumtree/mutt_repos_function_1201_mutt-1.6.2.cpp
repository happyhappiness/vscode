static void encode_base64 (FGETCONV * fc, FILE *fout, int istext)
{
  int ch, ch1 = EOF;

  b64_num = b64_linelen = 0;

  while ((ch = fgetconv (fc)) != EOF)
  {
    if (istext && ch == '\n' && ch1 != '\r')
      b64_putc('\r', fout);
    b64_putc(ch, fout);
    ch1 = ch;
  }
  b64_flush(fout);
  fputc('\n', fout);
}