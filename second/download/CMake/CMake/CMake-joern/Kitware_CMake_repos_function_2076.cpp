void cmDumpInformationPrintFile(const char* name, FILE* fout)
{
  fprintf(fout, "Avoid ctest truncation of output: CTEST_FULL_OUTPUT\n");
  fprintf(
    fout,
    "================================================================\n");
  struct stat fs;
  if (stat(name, &fs) != 0) {
    fprintf(fout, "The file \"%s\" does not exist.\n", name);
    fflush(fout);
    return;
  }

  FILE* fin = fopen(name, "r");
  if (fin) {
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
  } else {
    fprintf(fout, "Error opening \"%s\" for reading.\n", name);
    fflush(fout);
  }
}