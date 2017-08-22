@@ -23,6 +23,7 @@
 
 #include <cmsys/Directory.hxx>
 #include <cmsys/Process.h>
+#include <cmsys/FStream.hxx>
 
 #if defined(CMAKE_HAVE_VS_GENERATORS)
 #include "cmCallVisualStudioMacro.h"
@@ -376,7 +377,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
       cmSystemTools::RemoveADirectory(dirName.c_str());
 
       // is the last argument a filename that exists?
-      FILE *countFile = fopen(args[3].c_str(),"r");
+      FILE *countFile = cmsys::SystemTools::Fopen(args[3].c_str(),"r");
       int count;
       if (countFile)
         {
@@ -396,7 +397,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
         // write the count into the directory
         std::string fName = dirName;
         fName += "/count.txt";
-        FILE *progFile = fopen(fName.c_str(),"w");
+        FILE *progFile = cmsys::SystemTools::Fopen(fName.c_str(),"w");
         if (progFile)
           {
           fprintf(progFile,"%i\n",count);
@@ -417,7 +418,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
       // read the count
       fName = dirName;
       fName += "/count.txt";
-      progFile = fopen(fName.c_str(),"r");
+      progFile = cmsys::SystemTools::Fopen(fName.c_str(),"r");
       int count = 0;
       if (!progFile)
         {
@@ -437,7 +438,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
         fName = dirName;
         fName += "/";
         fName += args[i];
-        progFile = fopen(fName.c_str(),"w");
+        progFile = cmsys::SystemTools::Fopen(fName.c_str(),"w");
         if (progFile)
           {
           fprintf(progFile,"empty");
@@ -946,7 +947,7 @@ int cmcmd::ExecuteLinkScript(std::vector<std::string>& args)
   cmsysProcess_SetOption(cp, cmsysProcess_Option_Verbatim, 1);
 
   // Read command lines from the script.
-  std::ifstream fin(args[2].c_str());
+  cmsys::ifstream fin(args[2].c_str());
   if(!fin)
     {
     std::cerr << "Error opening link script \""
@@ -1057,7 +1058,7 @@ int cmcmd::VisualStudioLink(std::vector<std::string>& args, int type)
     // check for nmake temporary files
     if((*i)[0] == '@' && i->find("@CMakeFiles") != 0 )
       {
-      std::ifstream fin(i->substr(1).c_str());
+      cmsys::ifstream fin(i->substr(1).c_str());
       std::string line;
       while(cmSystemTools::GetLineFromStream(fin,
                                              line))
@@ -1229,7 +1230,7 @@ int cmcmd::VisualStudioLinkIncremental(std::vector<std::string>& args,
     std::cout << "Create " << resourceInputFile.c_str() << "\n";
     }
   // Create input file for rc command
-  std::ofstream fout(resourceInputFile.c_str());
+  cmsys::ofstream fout(resourceInputFile.c_str());
   if(!fout)
     {
     return -1;
@@ -1252,7 +1253,7 @@ int cmcmd::VisualStudioLinkIncremental(std::vector<std::string>& args,
       {
       std::cout << "Create empty: " << manifestFile.c_str() << "\n";
       }
-    std::ofstream foutTmp(manifestFile.c_str());
+    cmsys::ofstream foutTmp(manifestFile.c_str());
     }
   std::string resourceFile = manifestFile;
   resourceFile += ".res";