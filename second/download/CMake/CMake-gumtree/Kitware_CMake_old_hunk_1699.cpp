  fclose(ifp);

  

  /* Provide a function to write the data to a file.  */

  fprintf(ofp, "extern int %sEncodedWriteArray%s(const char* fname)\n",

          argv[3], argv[4]);

  fprintf(ofp, "{\n");

  fprintf(ofp, "  FILE* ofp = fopen(fname, \"wb\");\n");

  fprintf(ofp, "  if(!ofp) { return 0; }\n");
