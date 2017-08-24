@@ -17,6 +17,7 @@
 #include "ctest.h"
 #include "cmRegularExpression.h"
 #include "cmSystemTools.h"
+#include "cmListFileCache.h"
 
 #include <stdio.h>
 #include <time.h>
@@ -1111,17 +1112,19 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
   bool parseError;
   while ( fin )
     {
-    if(cmSystemTools::ParseFunction(fin, name, args, "DartTestfile.txt",
-                                    parseError))
+    cmListFileFunction lff;
+    if(cmListFileCache::ParseFunction(fin, lff, "DartTestfile.txt", parseError))
       {
+      const std::string& name = lff.m_Name;
+      const std::vector<cmListFileArgument>& args = lff.m_Arguments;
       if (name == "SUBDIRS")
         {
         std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-        for(std::vector<std::string>::iterator j = args.begin();
+        for(std::vector<cmListFileArgument>::const_iterator j = args.begin();
             j != args.end(); ++j)
           {   
           std::string nwd = cwd + "/";
-          nwd += *j;
+          nwd += j->Value;
           if (cmSystemTools::FileIsDirectory(nwd.c_str()))
             {
             cmSystemTools::ChangeDirectory(nwd.c_str());
@@ -1136,17 +1139,17 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
         {
         if (this->m_UseExcludeRegExp && 
             this->m_UseExcludeRegExpFirst && 
-            ereg.find(args[0].c_str()))
+            ereg.find(args[0].Value.c_str()))
           {
           continue;
           }
-        if (this->m_UseIncludeRegExp && !ireg.find(args[0].c_str()))
+        if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))
           {
           continue;
           }
         if (this->m_UseExcludeRegExp && 
             !this->m_UseExcludeRegExpFirst && 
-            ereg.find(args[0].c_str()))
+            ereg.find(args[0].Value.c_str()))
           {
           continue;
           }
@@ -1159,30 +1162,30 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
           std::cerr << "Changing directory into " << nwd.c_str() << "\n";
           firstTest = 0;
           }
-        cres.m_Name = args[0];
-        fprintf(stderr,"Testing %-30s ",args[0].c_str());
+        cres.m_Name = args[0].Value;
+        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
         fflush(stderr);
         //std::cerr << "Testing " << args[0] << " ... ";
         // find the test executable
-        std::string testCommand = this->FindExecutable(args[1].c_str());
+        std::string testCommand = this->FindExecutable(args[1].Value.c_str());
         testCommand = cmSystemTools::ConvertToOutputPath(testCommand.c_str());
 
         // continue if we did not find the executable
         if (testCommand == "")
           {
           std::cerr << "Unable to find executable: " << 
-            args[1].c_str() << "\n";
+            args[1].Value.c_str() << "\n";
           continue;
           }
         
         // add the arguments
-        std::vector<std::string>::iterator j = args.begin();
+        std::vector<cmListFileArgument>::const_iterator j = args.begin();
         ++j;
         ++j;
         for(;j != args.end(); ++j)
           {   
           testCommand += " ";
-          testCommand += cmSystemTools::EscapeSpaces(j->c_str());
+          testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
           }
         /**
          * Run an executable command and put the stdout in output.
@@ -1219,7 +1222,7 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
               std::cerr << output.c_str() << "\n";
               }
             }
-          failed.push_back(args[0]); 
+          failed.push_back(args[0].Value); 
           }
         else
           {
@@ -1236,7 +1239,7 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
               std::cerr << output.c_str() << "\n";
               }
             }
-          passed.push_back(args[0]); 
+          passed.push_back(args[0].Value); 
           }
         cres.m_Output = output;
         cres.m_ReturnValue = retVal;