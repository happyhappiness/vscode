{
    FILE* f = fopen(*fname, "rb");
    if (f) {
      printf("found: [%s]\n", *fname);
      fclose(f);
    } else {
      printf("error: [%s]\n", *fname);
      result = 1;
    }
  }