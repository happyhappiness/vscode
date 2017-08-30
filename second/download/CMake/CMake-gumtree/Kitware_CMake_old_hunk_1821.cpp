  fout <<

    "  if (ac < 2)\n"

    "    {\n"

    "    // If there is only one test, then run it with the arguments\n"

    "    if (NumTests == 1)\n"

    "      {\n"

    "      return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av);\n"

    "      }\n"

    "    \n"

    "    // Ask for a test\n"

    "    printf(\"Available tests:\\n\");\n"

    "    for (i =0; i < NumTests; ++i)\n"

