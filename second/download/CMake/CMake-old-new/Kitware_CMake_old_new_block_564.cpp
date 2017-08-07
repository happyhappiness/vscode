#if 0
      DumpExeFile( dosHeader );
#else
      fprintf(stderr, "File is an executable.  I don't dump those.\n");
      return;