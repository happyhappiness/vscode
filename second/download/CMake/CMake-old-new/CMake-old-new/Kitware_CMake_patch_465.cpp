@@ -405,7 +405,7 @@ bool cmQtAutomoc::RunAutomocQt4()
     const std::string &absFilename = *it;
     if (this->Verbose)
       {
-      printf("Checking -%s-\n", absFilename.c_str());
+      std::cout << "AUTOMOC: Checking " << absFilename << std::endl;
       }
     this->ParseCppFile(absFilename, includedMocs, notIncludedMocs);
     }
@@ -419,7 +419,7 @@ bool cmQtAutomoc::RunAutomocQt4()
     const std::string &absFilename = *it;
     if (this->Verbose)
       {
-      printf("Checking -%s-\n", absFilename.c_str());
+      std::cout << "AUTOMOC: Checking " << absFilename << std::endl;
       }
     if (includedMocs.find(absFilename) == includedMocs.end()
               && notIncludedMocs.find(absFilename) == notIncludedMocs.end())
@@ -527,7 +527,7 @@ void cmQtAutomoc::ParseCppFile(const std::string& absFilename,
   const std::string contentsString = this->ReadAll(absFilename);
   if (contentsString.empty())
     {
-    std::cerr << "automoc4: empty source file: " << absFilename << std::endl;
+    std::cerr << "AUTOMOC: empty source file: " << absFilename << std::endl;
     return;
     }
   const std::string absPath = cmsys::SystemTools::GetFilenamePath(
@@ -648,7 +648,7 @@ void cmQtAutomoc::ParseCppFile(const std::string& absFilename,
               }
             if (!headerFound)
               {
-              std::cerr << "automoc4: The file \"" << absFilename
+              std::cerr << "AUTOMOC: The file \"" << absFilename
                         << "\" includes the moc file \"" << currentMoc
                         << "\", but neither \"" << absPath << basename
                         << '{' << this->Join(headerExtensions, ',')
@@ -660,7 +660,7 @@ void cmQtAutomoc::ParseCppFile(const std::string& absFilename,
             }
           else
             {
-            std::cerr << "automoc4: The file \"" << absFilename
+            std::cerr << "AUTOMOC: The file \"" << absFilename
                       << "\" includes the moc file \"" << currentMoc
                       << "\", but \"" << absPath << basename << '{'
                       << this->Join(headerExtensions, ',') << '}'
@@ -728,17 +728,17 @@ bool cmQtAutomoc::GenerateMoc(const std::string& sourceFile,
       {
       for(int i=0; i<command.size(); i++)
         {
-        printf("%s ", command[i].c_str());
+        std::cout << command[i] << " ";
         }
-      printf("\n");
+      std::cout << std::endl;
       }
 
     std::string output;
     int retVal = 0;
     bool result = cmSystemTools::RunSingleCommand(command, &output, &retVal);
     if (!result || retVal)
       {
-      std::cerr << "automoc4: process for " << mocFilePath << " failed:\n"
+      std::cerr << "AUTOMOC: process for " << mocFilePath << " failed:\n"
                 << output << std::endl;
       this->RunMocFailed = true;
       cmSystemTools::RemoveFile(mocFilePath.c_str());