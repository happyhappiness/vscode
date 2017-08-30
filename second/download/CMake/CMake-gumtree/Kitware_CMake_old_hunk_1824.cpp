    "    }\n"

    "  \n"

    "  // If partial match is requested\n"

    "  int partial_match = (strcmp(av[1], \"-R\") == 0) ? 1 : 0;\n"

    "  if (partial_match && ac < 3)\n"

    "    {\n"

    "    printf(\"-R needs an additional parameter.\\n\");\n"

    "    return -1;\n"

    "    }\n"

    "  \n"

    "  char *arg = lowercase(av[1 + partial_match]);\n"

    "  for (i =0; i < NumTests; ++i)\n"

    "    {\n"

    "    char *test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);\n"

    "    if (partial_match && strstr(test_name, arg) != NULL)\n"

    "      {\n"

    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 2, av + 2);\n"
