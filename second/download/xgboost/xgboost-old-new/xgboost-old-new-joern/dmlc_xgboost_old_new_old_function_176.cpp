inline void Print(const char *fname) {
    FILE *fo;
    if (!strcmp(fname, "stdout")) {
      fo = stdout;
    } else {
      fo = utils::FopenCheck(fname, "w");
    }
    for (size_t i = 0; i < data.size(); ++i) {
      fprintf(fo, "%g", data[i]);
      if ((i+1) % ncol == 0) {
        fprintf(fo, "\n");
      } else {
        fprintf(fo, " ");
      }
    }
    // close the filed
    if (fo != stdout) fclose(fo);
  }