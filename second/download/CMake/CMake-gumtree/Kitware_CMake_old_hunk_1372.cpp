  fprintf(ofp, "#include \"kwsysPrivate.h\"\n");

  fprintf(ofp, "#include KWSYS_HEADER(Configure.h)\n\n");

  fprintf(ofp, "#include <stdio.h>\n\n");

  

  /* Split file up in 1024-byte chunks.  */

  while((n = (int)fread(buffer, 1, 1024, ifp)) > 0)

