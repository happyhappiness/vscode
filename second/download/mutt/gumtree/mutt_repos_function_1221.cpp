static void b64_putc(char c, FILE *fout)
{
  if(b64_num == 3)
    b64_flush(fout);

  b64_buffer[b64_num++] = c;
}