    "    test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);\n"

    "    if (partial_match && strstr(test_name, arg) != NULL)\n"

    "      {\n"

    "      free(test_name);\n"

    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 2, av + 2);\n"

    "      }\n"

    "    else if (!partial_match && strcmp(test_name, arg) == 0)\n"

    "      {\n"

    "      free(test_name);\n"

    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 1, av + 1);\n"

    "      }\n"

    "    free(test_name);\n"

    "    }\n"

    "  free(arg);\n"

    "  \n"

    "  // Nothing was run, display the test names\n"

    "  printf(\"Available tests:\\n\");\n"

    "  for (i =0; i < NumTests; ++i)\n"
