{
    FILE* f = fopen(argv[1], "w");
    if (f) {
      fprintf(f, "int generated_by_testExe1() { return 0; }\n");
      fclose(f);
    } else {
      fprintf(stderr, "Error writing to %s\n", argv[1]);
      return 1;
    }
  }