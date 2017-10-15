{
  int c, linelen = 0;
  char line[77], savechar;

  while ((c = fgetconv (fc)) != EOF)
  {
    /* Wrap the line if needed. */
    if (linelen == 76 && ((istext && c != '\n') || !istext))
    {
      /* If the last character is "quoted", then be sure to move all three
       * characters to the next line.  Otherwise, just move the last
       * character...
       */
      if (line[linelen-3] == '=')
      {
        line[linelen-3] = 0;
        fputs (line, fout);
        fputs ("=\n", fout);
        line[linelen] = 0;
        line[0] = '=';
        line[1] = line[linelen-2];
        line[2] = line[linelen-1];
        linelen = 3;
