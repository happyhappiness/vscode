@@ -42,7 +42,9 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& args)
         this->SetError("incorrect arguments to EXTRA_INCLUDE");
         return false;
         }
-      extraInclude = *i;
+      extraInclude = "#include \"";
+      extraInclude += *i;
+      extraInclude += "\"\n";
       }
     else if(*i == "FUNCTION")
       {
@@ -53,6 +55,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& args)
         return false;
         }
       function = *i;
+      function += "(&ac, &av);\n";
       }
     else
       {
@@ -87,36 +90,11 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& args)
     this->SetError(err.c_str());
     return false;
     }
-
+  std::string configFile = 
+    m_Makefile->GetDefinition("CMAKE_ROOT");
+  configFile += "/Templates/TestDriver.cxx.in";
   // Create the test driver file
-
-  fout << 
-    "#include <ctype.h>\n"
-    "#include <stdio.h>\n"
-    "#include <string.h>\n"
-    "#include <stdlib.h>\n"
-    "\n";
-  fout <<
-    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
-    "/* MSVC debug hook to prevent dialogs when running from DART.  */\n"
-    "# include <crtdbg.h>\n"
-    "static int TestDriverDebugReport(int type, char* message, int* retVal)\n"
-    "{\n"
-    "  (void)type; (void)retVal;\n"
-    "  fprintf(stderr, message);\n"
-    "  exit(1);\n"
-    "}\n"
-    "#endif\n";
-  if(extraInclude.size())
-    {
-    fout << "#include \"" << extraInclude << "\"\n";
-    }
   
-  fout <<
-    "\n"
-    "/* Forward declare test functions. */\n"
-    "\n";
-
   std::vector<std::string>::const_iterator testsBegin = i;
   std::vector<std::string> tests_func_name;
 
@@ -126,7 +104,7 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& args)
   // list. 
   // For the moment:
   //   - replace spaces ' ', ':' and '/' with underscores '_'
-
+  std::string forwardDeclareCode;
   for(i = testsBegin; i != tests.end(); ++i)
     {
     if(*i == "EXTRA_INCLUDE")
@@ -148,22 +126,12 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& args)
     cmSystemTools::ReplaceString(func_name, "/", "_");
     cmSystemTools::ReplaceString(func_name, ":", "_");
     tests_func_name.push_back(func_name);
-    fout << "int " << func_name << "(int, char*[]);\n";
+    forwardDeclareCode += "int ";
+    forwardDeclareCode += func_name;
+    forwardDeclareCode += "(int, char*[]);\n";
     }
-
-  fout << 
-    "\n"
-    "/* Create map.  */\n"
-    "\n"
-    "typedef int (*MainFuncPointer)(int , char*[]);\n"
-    "typedef struct\n"
-    "{\n"
-    "  const char* name;\n"
-    "  MainFuncPointer func;\n"
-    "} functionMapEntry;\n"
-    "\n"
-    "functionMapEntry cmakeGeneratedFunctionMapEntries[] = {\n";
-
+  
+  std::string functionMapCode;
   int numTests = 0;
   std::vector<std::string>::iterator j;
   for(i = testsBegin, j = tests_func_name.begin(); i != tests.end(); ++i, ++j)
@@ -178,122 +146,27 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& args)
       {
       func_name = cmSystemTools::GetFilenameWithoutLastExtension(*i);
       }
-    fout << 
-      "  {\n"
-      "    \"" << func_name << "\",\n"
-      "    " << *j << "\n"
+    functionMapCode += "  {\n"
+      "    \"";
+    functionMapCode += func_name;
+    functionMapCode += "\",\n"
+      "    ";
+    functionMapCode +=  *j;
+    functionMapCode += "\n"
       "  },\n";
     numTests++;
     }
-  // end with an empty struct
-  fout << "  {0,0}\n";
-  
-  fout << 
-    "};\n"
-    "\n"
-    "/* Allocate and create a lowercased copy of string\n"
-    "   (note that it has to be free'd manually) */\n"
-    "\n"
-    "char* lowercase(const char *string)\n"
-    "{\n"
-    "  char *new_string, *p;\n"
-    "  new_string = (char *)malloc(sizeof(char) * (size_t)(strlen(string) + 1));\n"
-    "  if (!new_string)\n"
-    "    {\n"
-    "    return 0;\n"
-    "    }\n"
-    "  strcpy(new_string, string);\n"
-    "  p = new_string;\n"
-    "  while (*p != 0)\n"
-    "    {\n"
-    "    *p = (char)tolower(*p);\n"
-    "    ++p;\n"
-    "    }\n"
-    "  return new_string;\n"
-    "}\n"
-    "\n"
-    "int main(int ac, char *av[])\n"
-    "{\n"
-    "  int i, NumTests, testNum, partial_match;\n"
-    "  char *arg, *test_name;\n"
-    "  \n"
-    "#if defined(_MSC_VER) && defined(_DEBUG)\n"
-    "  /* If running from DART, put in debug hook.  */\n"
-    "  if(getenv(\"DART_TEST_FROM_DART\"))\n"
-    "    {\n"
-    "    _CrtSetReportHook(TestDriverDebugReport);\n"
-    "    }\n"
-    "#endif\n"
-    "  \n"
-    "  NumTests = " << numTests << ";\n"
-    "  \n"
-    "  /* If no test name was given */\n";
+  if(extraInclude.size())
+    {
+    m_Makefile->AddDefinition("CMAKE_TESTDRIVER_EXTRA_INCLUDES", extraInclude.c_str());
+    }
   if(function.size())
     {
-    fout << "  /* process command line with user function.  */\n"
-         << "  " << function << "(&ac, &av);\n";
+    m_Makefile->AddDefinition("CMAKE_TESTDRIVER_ARGVC_FUNCTION", function.c_str());
     }
-  
-  fout <<
-    "  if (ac < 2)\n"
-    "    {\n"
-    "    /* Ask for a test.  */\n"
-    "    printf(\"Available tests:\\n\");\n"
-    "    for (i =0; i < NumTests; ++i)\n"
-    "      {\n"
-    "      printf(\"%3d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"
-    "      }\n"
-    "    printf(\"To run a test, enter the test number: \");\n"
-    "    testNum = 0;\n"
-    "    scanf(\"%d\", &testNum);\n"
-    "    if (testNum >= NumTests)\n"
-    "      {\n"
-    "      printf(\"%3d is an invalid test number.\\n\", testNum);\n"
-    "      return -1;\n"
-    "      }\n"
-    "    return (*cmakeGeneratedFunctionMapEntries[testNum].func)(ac-1, av+1);\n"
-    "    }\n"
-    "  \n"
-    "  /* If partial match is requested.  */\n"
-    "  partial_match = (strcmp(av[1], \"-R\") == 0) ? 1 : 0;\n"
-    "  if (partial_match && ac < 3)\n"
-    "    {\n"
-    "    printf(\"-R needs an additional parameter.\\n\");\n"
-    "    return -1;\n"
-    "    }\n"
-    "  \n"
-    "  arg = lowercase(av[1 + partial_match]);\n"
-    "  for (i =0; i < NumTests; ++i)\n"
-    "    {\n"
-    "    test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);\n"
-    "    if (partial_match && strstr(test_name, arg) != NULL)\n"
-    "      {\n"
-    "      free(arg);\n"
-    "      free(test_name);\n"
-    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 2, av + 2);\n"
-    "      }\n"
-    "    else if (!partial_match && strcmp(test_name, arg) == 0)\n"
-    "      {\n"
-    "      free(arg);\n"
-    "      free(test_name);\n"
-    "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac - 1, av + 1);\n"
-    "      }\n"
-    "    free(test_name);\n"
-    "    }\n"
-    "  free(arg);\n"
-    "  \n"
-    "  /* Nothing was run, display the test names.  */\n"
-    "  printf(\"Available tests:\\n\");\n"
-    "  for (i =0; i < NumTests; ++i)\n"
-    "    {\n"
-    "    printf(\"%3d. %s\\n\", i, cmakeGeneratedFunctionMapEntries[i].name);\n"
-    "    }\n"
-    "  printf(\"Failed: %s is an invalid test name.\\n\", av[1]);\n"
-    "  \n"
-    "  return -1;\n"
-    "}\n";
-
-  fout.close();
+  m_Makefile->AddDefinition("CMAKE_FORWARD_DECLARE_TESTS", forwardDeclareCode.c_str());
+  m_Makefile->AddDefinition("CMAKE_FUNCTION_TABLE_ENTIRES", functionMapCode.c_str());
+  m_Makefile->ConfigureFile(configFile.c_str(), driver.c_str(), false, true, false);
 
   // Create the source list
   cmSourceFile cfile;