@@ -20,7 +20,7 @@
 // cmCreateTestSourceList
 bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
 {
-  if (argsIn.size() < 5)
+  if (argsIn.size() < 3)
     {
       this->SetError("called with wrong number of arguments.");
       return false;
@@ -75,6 +75,9 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
   fout << "  int i;\n";
   fout << "  if(ac < 2)\n";
   fout << "    {\n";
+  fout << "    // if there is only one test, then run it with the arguments\n";
+  fout << "    if(NumTests == 1)\n";
+  fout << "      { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";
   fout << "    printf(\"Available tests:\\n\");\n";
   fout << "    for(i =0; i < NumTests; ++i)\n";
   fout << "      {\n";
@@ -97,6 +100,9 @@ bool cmCreateTestSourceList::InitialPass(std::vector<std::string> const& argsIn)
   fout << "      return (*cmakeGeneratedFunctionMapEntries[i].func)(ac-1, av+1);\n";
   fout << "      }\n";
   fout << "    }\n";
+  fout << "  // if there is only one test, then run it with the arguments\n";
+  fout << "  if(NumTests == 1)\n";
+  fout << "    { return (*cmakeGeneratedFunctionMapEntries[0].func)(ac, av); }\n";
   fout << "  printf(\"Available tests:\\n\");\n";
   fout << "  for(i =0; i < NumTests; ++i)\n";
   fout << "    {\n";