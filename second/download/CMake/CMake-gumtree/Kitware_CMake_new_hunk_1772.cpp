    "  int i, NumTests, testNum, partial_match;\n"
    "  char *arg, *test_name;\n"
    "  \n"
    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
    "  /* Put in hook for debug library.  */\n"
    "  _CrtSetReportHook(TestDriverDebugReport);\n"
    "#endif\n"
    "  \n"
    "  NumTests = " << numTests << ";\n"
    "  \n"
    "  /* If no test name was given */\n";
  if(function.size())
    {
    fout << "  /* process command line with user function.  */\n"
         << "  " << function << "(&ac, &av);\n";
    }
  
  fout <<
    "  if (ac < 2)\n"
    "    {\n"
    "    /* Ask for a test.  */\n"
    "    printf(\"Available tests:\\n\");\n"
    "    for (i =0; i < NumTests; ++i)\n"
    "      {\n"
