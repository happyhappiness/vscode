    "#include <ctype.h>\n"
    "#include <stdio.h>\n"
    "#include <string.h>\n"
    "#include <stdlib.h>\n"
    "\n";
  fout <<
    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
    "/* MSVC debug hook to prevent dialogs when running from DART.  */\n"
    "# include <crtdbg.h>\n"
    "static int TestDriverDebugReport(int type, char* message, int* retVal)\n"
    "{\n"
    "  (void)type; (void)retVal;\n"
    "  fprintf(stderr, message);\n"
    "  exit(1);\n"
    "  return 0;\n"
    "}\n"
    "#endif\n";
