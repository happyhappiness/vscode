static void b64_flush(FILE *fout)
{
  short i;

  if(!b64_num)
    return;

  if(b64_linelen >= 72)
  {
    fputc('\n', fout);
    b64_linelen = 0;
  }

  for(i = b64_num; i < 3; i++)
    b64_buffer[i] = '\0';

  fputc(B64Chars[(b64_buffer[0] >> 2) & 0x3f], fout);
  b64_linelen++;
  fputc(B64Chars[((b64_buffer[0] & 0x3) << 4) | ((b64_buffer[1] >> 4) & 0xf) ], fout);
  b64_linelen++;

  if(b64_num > 1)
  {
    fputc(B64Chars[((b64_buffer[1] & 0xf) << 2) | ((b64_buffer[2] >> 6) & 0x3) ], fout);
    b64_linelen++;
    if(b64_num > 2)
    {
      fputc(B64Chars[b64_buffer[2] & 0x3f], fout);
      b64_linelen++;
    }
  }

  while(b64_linelen % 4)
  {
    fputc('=', fout);
    b64_linelen++;
  }

  b64_num = 0;
}