    fout << "int " << *i << "(int, char**);\n";
    }

  fout << "// Create map \n";
  fout << "typedef int (*MainFuncPointer)(int , char**);\n";
  fout << "struct functionMapEntry\n"
       << "{\n"
       << "const char* name;\n"
       << "MainFuncPointer func;\n"
       << "};\n\n";
  fout << "functionMapEntry cmakeGeneratedFunctionMapEntries[] = {\n";

  int numTests = 0;
  for(i = testsBegin; i != args.end(); ++i)
    {
    fout << "{\"" << *i << "\", " << *i << "},\n";
    numTests++;
    }

  fout << "};\n";
  fout << "int main(int ac, char** av)\n"
       << "{\n";
  fout << "  int NumTests = " << numTests << ";\n";
  fout << "  int i;\n";
  fout << "  if(ac < 2)\n";
  fout << "    {\n";
  fout << "    // if there is only one test, then run it with the arguments\n";
  fout << "    if(NumTests == 1)\n";
  fout << "      { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";
  fout << "    printf(\"Available tests:\\n\");\n";
  fout << "    for(i =0; i < NumTests; ++i)\n";
  fout << "      {\n";
  fout << "      printf(\"%d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n";
  fout << "      }\n";
  fout << "    printf(\"To run a test, enter the test number: \");\n";
  fout << "    int testNum = 0;\n";
  fout << "    scanf(\"%d\", &testNum);\n";
  fout << "    if(testNum >= NumTests)\n";
  fout << "    {\n";
  fout << "    printf(\"%d is an invalid test number.\\n\", testNum);\n";
  fout << "    return -1;\n";
  fout << "    }\n";
  fout << "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n";
  fout << "    }\n";
  fout << "  for(i =0; i < NumTests; ++i)\n";
  fout << "    {\n";
  fout << "    if(strcmp(cmakeGeneratedFunctionMapEntries[i].name, av[1]) == 0)\n";
  fout << "      {\n";
  fout << "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac-1, av+1);\n";
  fout << "      }\n";
  fout << "    }\n";
  fout << "  // if there is only one test, then run it with the arguments\n";
  fout << "  if(NumTests == 1)\n";
  fout << "    { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";
  fout << "  printf(\"Available tests:\\n\");\n";
  fout << "  for(i =0; i < NumTests; ++i)\n";
  fout << "    {\n";
  fout << "    printf(\"%d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n";
  fout << "    }\n";
  fout << "  printf(\"Failed: %s is an invalid test name.\\n\", av[1]);\n";
  fout << "  return -1;\n";
  fout << "}\n";
  fout.close();

  // Create the source list
