{
    fprintf(
      fout,
      "Contents of \"%s\":\n"
      "----------------------------------------------------------------\n",
      name);
    const int bufferSize = 4096;
    char buffer[bufferSize];
    int n;
    while ((n = fread(buffer, 1, bufferSize, fin)) > 0) {
      for (char* c = buffer; c < buffer + n; ++c) {
        switch (*c) {
          case '<':
            fprintf(fout, "&lt;");
            break;
          case '>':
            fprintf(fout, "&gt;");
            break;
          case '&':
            fprintf(fout, "&amp;");
            break;
          default:
            putc(*c, fout);
            break;
        }
      }
      fflush(fout);
    }
    fclose(fin);
  }