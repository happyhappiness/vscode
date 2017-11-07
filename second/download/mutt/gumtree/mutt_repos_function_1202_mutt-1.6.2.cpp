static void encode_8bit (FGETCONV *fc, FILE *fout, int istext)
{
  int ch;

  while ((ch = fgetconv (fc)) != EOF)
    fputc (ch, fout);
}