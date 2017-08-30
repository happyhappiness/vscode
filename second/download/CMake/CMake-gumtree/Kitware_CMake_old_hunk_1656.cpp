      {
      func_name = cmSystemTools::GetFilenameWithoutLastExtension(*i);
      }
    fout << 
      "  {\n"
      "    \"" << func_name << "\",\n"
      "    " << *j << "\n"
      "  },\n";
    numTests++;
    }
  // end with an empty struct
  fout << "  {0,0}\n";
  
  fout << 
    "};\n"
    "\n"
    "/* Allocate and create a lowercased copy of string\n"
    "   (note that it has to be free'd manually) */\n"
    "\n"
    "char* lowercase(const char *string)\n"
    "{\n"
    "  char *new_string, *p;\n"
    "  new_string = (char *)malloc(sizeof(char) * (size_t)(strlen(string) + 1));\n"
    "  if (!new_string)\n"
    "    {\n"
    "    return 0;\n"
    "    }\n"
    "  strcpy(new_string, string);\n"
    "  p = new_string;\n"
    "  while (*p != 0)\n"
    "    {\n"
    "    *p = (char)tolower(*p);\n"
    "    ++p;\n"
    "    }\n"
    "  return new_string;\n"
    "}\n"
    "\n"
    "int main(int ac, char *av[])\n"
    "{\n"
    "  int i, NumTests, testNum, partial_match;\n"
    "  char *arg, *test_name;\n"
    "  \n"
    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
    "  /* If running from DART, put in debug hook.  */\n"
    "  if(getenv(\"DART_TEST_FROM_DART\"))\n"
    "    {\n"
    "    _CrtSetReportHook(TestDriverDebugReport);\n"
    "    }\n"
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
    "      printf(\"%3d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"
    "      }\n"
    "    printf(\"To run a test, enter the test number: \");\n"
    "    testNum = 0;\n"
    "    scanf(\"%d\", &testNum);\n"
    "    if (testNum >= NumTests)\n"
    "      {\n"
    "      printf(\"%3d is an invalid test number.\\n\", testNum);\n"
    "      return -1;\n"
    "      }\n"
    "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n"
    "    }\n"
    "  \n"
    "  /* If partial match is requested.  */\n"
    "  partial_match = (strcmp(av[1], \"-R\") == 0) ? 1 : 0;\n"
    "  if (partial_match && ac < 3)\n"
    "    {\n"
    "    printf(\"-R needs an additional parameter.\\n\");\n"
    "    return -1;\n"
    "    }\n"
    "  \n"
    "  arg = lowercase(av[1 + partial_match]);\n"
    "  for (i =0; i < NumTests; ++i)\n"
    "    {\n"
    "    test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);\n"
    "    if (partial_match && strstr(test_name, arg) != NULL)\n"
    "      {\n"
    "      free(arg);\n"
    "      free(test_name);\n"
    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 2, av + 2);\n"
    "      }\n"
    "    else if (!partial_match && strcmp(test_name, arg) == 0)\n"
    "      {\n"
    "      free(arg);\n"
    "      free(test_name);\n"
    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 1, av + 1);\n"
    "      }\n"
    "    free(test_name);\n"
    "    }\n"
    "  free(arg);\n"
    "  \n"
    "  /* Nothing was run, display the test names.  */\n"
    "  printf(\"Available tests:\\n\");\n"
    "  for (i =0; i < NumTests; ++i)\n"
    "    {\n"
    "    printf(\"%3d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"
    "    }\n"
    "  printf(\"Failed: %s is an invalid test name.\\n\", av[1]);\n"
    "  \n"
    "  return -1;\n"
    "}\n";

  fout.close();

  // Create the source list
  cmSourceFile cfile;