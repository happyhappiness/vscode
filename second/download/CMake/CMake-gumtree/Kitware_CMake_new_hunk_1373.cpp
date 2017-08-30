  fprintf(ofp, "extern %s_EXPORT int %sEncodedWriteArray%s(const char* fname)\n",
          argv[3], argv[3], argv[4]);
  fprintf(ofp, "{\n");
  fprintf(ofp, "  FILE* ofp = fopen(fname, \"wb\");\n");
  fprintf(ofp, "  if(!ofp) { return 0; }\n");
  for(i=0; i < count; ++i)
