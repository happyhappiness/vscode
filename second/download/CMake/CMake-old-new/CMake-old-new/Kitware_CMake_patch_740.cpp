@@ -97,14 +97,29 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
     "#include <stdio.h>\n"
     "#include <string.h>\n"
     "#include <stdlib.h>\n";
+  fout <<
+    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
+    "/* MSVC debug hook to prevent dialogs when running from DART.  */\n"
+    "# include <crtdbg.h>\n"
+    "static int TestDriverDebugReport(int type, char* message, int* retVal)\n"
+    "{\n"
+    "  (void)type; (void)retVal;\n"
+    "  if(getenv(\"DART_TEST_FROM_DART\"))\n"
+    "    {\n"
+    "    fprintf(stderr, message);\n"
+    "    exit(1);\n"
+    "    }\n"
+    "  return 0;\n"
+    "}\n"
+    "#endif\n";
   if(extraInclude.size())
     {
     fout << "#include \"" << extraInclude << "\"\n";
     }
   
   fout <<
     "\n"
-    "// Forward declare test functions\n"
+    "/* Forward declare test functions. */\n"
     "\n";
 
   std::vector<std::string>::iterator testsBegin = i;
@@ -143,7 +158,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
 
   fout << 
     "\n"
-    "// Create map\n"
+    "/* Create map.  */\n"
     "\n"
     "typedef int (*MainFuncPointer)(int , char*[]);\n"
     "typedef struct\n"
@@ -179,8 +194,8 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
   fout << 
     "};\n"
     "\n"
-    "// Allocate and create a lowercased copy of string\n"
-    "// (note that it has to be free'd manually)\n"
+    "/* Allocate and create a lowercased copy of string\n"
+    "   (note that it has to be free'd manually) */\n"
     "\n"
     "char* lowercase(const char *string)\n"
     "{\n"
@@ -205,19 +220,24 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
     "  int i, NumTests, testNum, partial_match;\n"
     "  char *arg, *test_name;\n"
     "  \n"
+    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
+    "  /* Put in hook for debug library.  */\n"
+    "  _CrtSetReportHook(TestDriverDebugReport);\n"
+    "#endif\n"
+    "  \n"
     "  NumTests = " << numTests << ";\n"
     "  \n"
-    "  // If no test name was given\n";
+    "  /* If no test name was given */\n";
   if(function.size())
     {
-    fout << "  // process command line with user function\n"
+    fout << "  /* process command line with user function.  */\n"
          << "  " << function << "(&ac, &av);\n";
     }
   
   fout <<
     "  if (ac < 2)\n"
     "    {\n"
-    "    // Ask for a test\n"
+    "    /* Ask for a test.  */\n"
     "    printf(\"Available tests:\\n\");\n"
     "    for (i =0; i < NumTests; ++i)\n"
     "      {\n"
@@ -234,7 +254,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
     "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n"
     "    }\n"
     "  \n"
-    "  // If partial match is requested\n"
+    "  /* If partial match is requested.  */\n"
     "  partial_match = (strcmp(av[1], \"-R\") == 0) ? 1 : 0;\n"
     "  if (partial_match && ac < 3)\n"
     "    {\n"
@@ -262,7 +282,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
     "    }\n"
     "  free(arg);\n"
     "  \n"
-    "  // Nothing was run, display the test names\n"
+    "  /* Nothing was run, display the test names.  */\n"
     "  printf(\"Available tests:\\n\");\n"
     "  for (i =0; i < NumTests; ++i)\n"
     "    {\n"