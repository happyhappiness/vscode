  fout << "  int i;\n";

  fout << "  if(ac < 2)\n";

  fout << "    {\n";

  fout << "    // if there is only one test, then run it with the arguments\n";

  fout << "    if(NumTests == 1)\n";

  fout << "      { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";

  fout << "    printf(\"Available tests:\\n\");\n";

  fout << "    for(i =0; i < NumTests; ++i)\n";

  fout << "      {\n";

