(FILE* fout = fopen(argv[1], "w")) {
    fprintf(fout, "static const char* %s_string = \"%s\";\n", argv[2], foo());
    fclose(fout);
  } else {
    fprintf(stderr, "Could not open output file \"%s\"", argv[1]);
    return 1;
  }