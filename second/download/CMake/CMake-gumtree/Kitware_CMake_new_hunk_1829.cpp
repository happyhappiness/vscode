    "    printf(\"Available tests:\\n\");\n"

    "    for (i =0; i < NumTests; ++i)\n"

    "      {\n"

    "      printf(\"%3d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"

    "      }\n"

    "    printf(\"To run a test, enter the test number: \");\n"

    "    int testNum = 0;\n"

    "    scanf(\"%d\", &testNum);\n"

    "    if (testNum >= NumTests)\n"

    "      {\n"

    "      printf(\"%3d is an invalid test number.\\n\", testNum);\n"

    "      return -1;\n"

    "      }\n"

    "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n"

