    "    test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);\n"
    "    if (partial_match && strstr(test_name, arg) != NULL)\n"
    "      {\n"
    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 2, av + 2);\n"
    "      }\n"
    "    else if (!partial_match && strcmp(test_name, arg) == 0)\n"
    "      {\n"
    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 1, av + 1);\n"
    "      }\n"
    "    free(test_name);\n"
    "    }\n"
    "  free(arg);\n"
    "  \n"
    "  // If the test was not found but there is only one test, then\n"
    "  // run it with the arguments\n"
    "  if (NumTests == 1)\n"
    "    {\n"
    "    return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av);\n"
    "    }\n"
    "  \n"
    "  // Nothing was run, display the test names\n"
    "  printf(\"Available tests:\\n\");\n"
    "  for (i =0; i < NumTests; ++i)\n"