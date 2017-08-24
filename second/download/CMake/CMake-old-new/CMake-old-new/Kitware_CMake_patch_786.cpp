@@ -1,5 +1,6 @@
 #include <stdio.h>
 #include "ctest.h"
+#include "cmRegularExpression.h"
 
 bool TryExecutable(const char *dir, const char *file,
                    std::string *fullPath, const char *subdir)
@@ -103,6 +104,8 @@ void ctest::ProcessDirectory(int &passed, int &failed)
 
   std::string name;
   std::vector<std::string> args;
+  cmRegularExpression var(this->m_RegExp.c_str());
+
   while ( fin )
     {
     if(cmSystemTools::ParseFunction(fin, name, args))
@@ -125,9 +128,13 @@ void ctest::ProcessDirectory(int &passed, int &failed)
         // return to the original directory
         cmSystemTools::ChangeDirectory(cwd.c_str());
         }
-
+      
       if (name == "ADD_TEST")
         {
+        if (this->m_UseRegExp && !var.find(args[0].c_str()))
+          {
+          continue;
+          }
         fprintf(stderr,"Testing %-30s ",args[0].c_str());
         //std::cerr << "Testing " << args[0] << " ... ";
         // find the test executable
@@ -150,7 +157,7 @@ void ctest::ProcessDirectory(int &passed, int &failed)
         if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                        retVal, false) || retVal != 0)
           {
-          std::cerr << " Failed\n";
+          fprintf(stderr,"***Failed\n");
           if (output != "")
             {
             std::cerr << output.c_str() << "\n";
@@ -159,7 +166,7 @@ void ctest::ProcessDirectory(int &passed, int &failed)
           }
         else
           {
-          std::cerr << " Passed\n";
+          fprintf(stderr,"   Passed\n");
           if (output != "")
             {
             std::cerr << output.c_str() << "\n";
@@ -182,6 +189,23 @@ int main (int argc, char *argv[])
   
   ctest inst;
   
+  // look at the args
+  std::vector<std::string> args;
+  for(int i =0; i < argc; ++i)
+    {
+    args.push_back(argv[i]);
+    }
+  
+  for(unsigned int i=1; i < args.size(); ++i)
+    {
+    std::string arg = args[i];
+    if(arg.find("-R",0) == 0 && i < args.size() - 1)
+      {
+      inst.m_UseRegExp = true;
+      inst.m_RegExp  = args[i+1];
+      }
+    }
+
   // call process directory
   inst.ProcessDirectory(passed, failed);
   total = passed + failed;