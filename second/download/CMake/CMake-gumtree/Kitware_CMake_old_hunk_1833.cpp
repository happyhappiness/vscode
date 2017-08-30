  fout << "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac-1, av+1);\n";
  fout << "      }\n";
  fout << "    }\n";
  fout << "  printf(\"Available tests:\\n\");\n";
  fout << "  for(i =0; i < NumTests; ++i)\n";
  fout << "    {\n";