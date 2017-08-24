@@ -22,8 +22,8 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
 {
   if (argsIn.size() < 3)
     {
-      this->SetError("called with wrong number of arguments.");
-      return false;
+    this->SetError("called with wrong number of arguments.");
+    return false;
     }
 
   std::vector<std::string> args;
@@ -45,7 +45,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
   ++i;
 
   std::ofstream fout(driver.c_str());
-  if(!fout)
+  if (!fout)
     {
     std::string err = "Could not create file ";
     err += driver;
@@ -56,9 +56,12 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
 
   // Create the test driver file
 
-  fout << "#include <stdio.h>\n";
-  fout << "#include <string.h>\n";
-  fout << "// forward declare test functions\n";
+  fout << 
+    "#include <stdio.h>\n"
+    "#include <string.h>\n"
+    "\n"
+    "// Forward declare test functions\n"
+    "\n";
 
   std::vector<std::string>::iterator testsBegin = i;
   std::vector<std::string> tests_filename;
@@ -80,65 +83,105 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
     fout << "int " << *i << "(int, char**);\n";
     }
 
-  fout << "// Create map \n";
-  fout << "typedef int (*MainFuncPointer)(int , char**);\n";
-  fout << "struct functionMapEntry\n"
-       << "{\n"
-       << "const char* name;\n"
-       << "MainFuncPointer func;\n"
-       << "};\n\n";
-  fout << "functionMapEntry cmakeGeneratedFunctionMapEntries[] = {\n";
+  fout << 
+    "\n"
+    "// Create map\n"
+    "\n"
+    "typedef int (*MainFuncPointer)(int , char**);\n"
+    "struct functionMapEntry\n"
+    "{\n"
+    "  const char* name;\n"
+    "  MainFuncPointer func;\n"
+    "};\n"
+    "\n"
+    "functionMapEntry cmakeGeneratedFunctionMapEntries[] = {\n";
 
   int numTests = 0;
   for(i = testsBegin; i != args.end(); ++i)
     {
-    fout << "{\"" << *i << "\", " << *i << "},\n";
+    fout << 
+      "  {\n"
+      "    \"" << *i << "\",\n"
+      "    " << *i << "\n"
+      "  },\n";
     numTests++;
     }
 
-  fout << "};\n";
-  fout << "int main(int ac, char** av)\n"
-       << "{\n";
-  fout << "  int NumTests = " << numTests << ";\n";
-  fout << "  int i;\n";
-  fout << "  if(ac < 2)\n";
-  fout << "    {\n";
-  fout << "    // if there is only one test, then run it with the arguments\n";
-  fout << "    if(NumTests == 1)\n";
-  fout << "      { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";
-  fout << "    printf(\"Available tests:\\n\");\n";
-  fout << "    for(i =0; i < NumTests; ++i)\n";
-  fout << "      {\n";
-  fout << "      printf(\"%d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n";
-  fout << "      }\n";
-  fout << "    printf(\"To run a test, enter the test number: \");\n";
-  fout << "    int testNum = 0;\n";
-  fout << "    scanf(\"%d\", &testNum);\n";
-  fout << "    if(testNum >= NumTests)\n";
-  fout << "    {\n";
-  fout << "    printf(\"%d is an invalid test number.\\n\", testNum);\n";
-  fout << "    return -1;\n";
-  fout << "    }\n";
-  fout << "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n";
-  fout << "    }\n";
-  fout << "  for(i =0; i < NumTests; ++i)\n";
-  fout << "    {\n";
-  fout << "    if(strcmp(cmakeGeneratedFunctionMapEntries[i].name, av[1]) == 0)\n";
-  fout << "      {\n";
-  fout << "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac-1, av+1);\n";
-  fout << "      }\n";
-  fout << "    }\n";
-  fout << "  // if there is only one test, then run it with the arguments\n";
-  fout << "  if(NumTests == 1)\n";
-  fout << "    { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";
-  fout << "  printf(\"Available tests:\\n\");\n";
-  fout << "  for(i =0; i < NumTests; ++i)\n";
-  fout << "    {\n";
-  fout << "    printf(\"%d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n";
-  fout << "    }\n";
-  fout << "  printf(\"Failed: %s is an invalid test name.\\n\", av[1]);\n";
-  fout << "  return -1;\n";
-  fout << "}\n";
+  fout << 
+    "};\n"
+    "\n"
+    "int main(int ac, char** av)\n"
+    "{\n"
+    "  int NumTests = " << numTests << ";\n"
+    "  int i;\n"
+    "  \n"
+    "  // If no test name was given\n"
+    "  if (ac < 2)\n"
+    "    {\n"
+    "    // If there is only one test, then run it with the arguments\n"
+    "    if (NumTests == 1)\n"
+    "      {\n"
+    "      return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av);\n"
+    "      }\n"
+    "    \n"
+    "    // Ask for a test\n"
+    "    printf(\"Available tests:\\n\");\n"
+    "    for (i =0; i < NumTests; ++i)\n"
+    "      {\n"
+    "      printf(\"%d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"
+    "      }\n"
+    "    printf(\"To run a test, enter the test number: \");\n"
+    "    int testNum = 0;\n"
+    "    scanf(\"%d\", &testNum);\n"
+    "    if (testNum >= NumTests)\n"
+    "      {\n"
+    "      printf(\"%d is an invalid test number.\\n\", testNum);\n"
+    "      return -1;\n"
+    "      }\n"
+    "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n"
+    "    }\n"
+    "  \n"
+    "  // If partial match is requested\n"
+    "  int partial_match = (strcmp(av[1], \"-R\") == 0) ? 1 : 0;\n"
+    "  if (partial_match && ac < 3)\n"
+    "    {\n"
+    "    printf(\"-R needs an additional parameter.\\n\");\n"
+    "    return -1;\n"
+    "    }\n"
+    "  \n"
+    "  // A test name was given, try to find it\n"
+    "  for (i =0; i < NumTests; ++i)\n"
+    "    {\n"
+    "    if (partial_match && \n"
+    "        strstr(cmakeGeneratedFunctionMapEntries[i].name, av[2]) != NULL)\n"
+    "      {\n"
+    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac-2, av+2);\n"
+    "      }\n"
+    "    else if (!partial_match && \n"
+    "             strcmp(cmakeGeneratedFunctionMapEntries[i].name, av[1]) == 0)\n"
+    "      {\n"
+    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac-1, av+1);\n"
+    "      }\n"
+    "    }\n"
+    "  \n"
+    "  // If the test was not found but there is only one test, then\n"
+    "  // run it with the arguments\n"
+    "  if (NumTests == 1)\n"
+    "    {\n"
+    "    return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av);\n"
+    "    }\n"
+    "  \n"
+    "  // Nothing was run, display the test names\n"
+    "  printf(\"Available tests:\\n\");\n"
+    "  for (i =0; i < NumTests; ++i)\n"
+    "    {\n"
+    "    printf(\"%d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"
+    "    }\n"
+    "  printf(\"Failed: %s is an invalid test name.\\n\", av[1]);\n"
+    "  \n"
+    "  return -1;\n"
+    "}\n";
+
   fout.close();
 
   // Create the source list
@@ -151,7 +194,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
                 false);
   m_Makefile->AddSource(cfile, sourceList);
   
-  for(i = tests_filename.begin(); i != tests_filename.end(); ++i)
+  for (i = tests_filename.begin(); i != tests_filename.end(); ++i)
     {
     cmSourceFile cfile;
     cfile.SetIsAnAbstractClass(false);