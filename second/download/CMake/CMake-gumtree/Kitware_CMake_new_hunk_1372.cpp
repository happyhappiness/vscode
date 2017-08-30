  fprintf(ofp, "#include \"kwsysPrivate.h\"\n");

  fprintf(ofp, "#include KWSYS_HEADER(Configure.h)\n\n");

  fprintf(ofp, "#include <stdio.h>\n\n");

  fprintf(ofp, "#if defined(_WIN32)\n");

  fprintf(ofp, "# include <io.h>\n");

  fprintf(ofp, "#else\n");

  fprintf(ofp, "# include <unistd.h>\n");

  fprintf(ofp, "#endif\n");

  fprintf(ofp, "\n");

  fprintf(ofp, "static void kwsys_unlink(const char* fname)\n");

  fprintf(ofp, "{\n");

  fprintf(ofp, "#if defined(__WATCOMC__)\n");

  fprintf(ofp, "  unlink(fname);\n");

  fprintf(ofp, "#else\n");

  fprintf(ofp, "  _unlink(fname);\n");

  fprintf(ofp, "#endif\n");

  fprintf(ofp, "}\n");

  fprintf(ofp, "\n");

  

  /* Split file up in 1024-byte chunks.  */

  while((n = (int)fread(buffer, 1, 1024, ifp)) > 0)

