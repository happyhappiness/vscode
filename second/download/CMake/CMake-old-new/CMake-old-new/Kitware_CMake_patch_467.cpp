@@ -7,8 +7,6 @@
 #include "cmQtAutomoc.h"
 
 
-#define TRACE_LINE() printf(" %s %d\n", __PRETTY_FUNCTION__, __LINE__)
-
 cmQtAutomoc::cmQtAutomoc()
 :Verbose(true)
 ,RunMocFailed(false)
@@ -79,7 +77,8 @@ void cmQtAutomoc::SetupAutomocTarget(cmMakefile* makefile,
     if ((skip==false) && (generated == false))
       {
       std::string ext = cmSystemTools::GetFilenameExtension(fileIt->c_str());
-      cmSystemTools::FileFormat fileType = cmSystemTools::GetFileFormat(ext.c_str());
+      cmSystemTools::FileFormat fileType = cmSystemTools::GetFileFormat(
+                                                                  ext.c_str());
       if (fileType == cmSystemTools::CXX_FILE_FORMAT)
         {
         _moc_files += sepFiles;
@@ -200,11 +199,13 @@ bool cmQtAutomoc::ReadAutomocInfoFile(cmMakefile* makefile,
   this->QtMajorVersion = makefile->GetSafeDefinition("AM_QT_VERSION_MAJOR");
   this->Sources = makefile->GetSafeDefinition("AM_SOURCES");
   this->Headers = makefile->GetSafeDefinition("AM_HEADERS");
-  this->IncludeProjectDirsBefore = makefile->IsOn("AM_CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE");
+  this->IncludeProjectDirsBefore = makefile->IsOn(
+                                "AM_CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE");
   this->Srcdir = makefile->GetSafeDefinition("AM_CMAKE_CURRENT_SOURCE_DIR");
   this->Builddir = makefile->GetSafeDefinition("AM_CMAKE_BINARY_DIR");
   this->MocExecutable = makefile->GetSafeDefinition("AM_QT_MOC_EXECUTABLE");
-  this->MocCompileDefinitionsStr = makefile->GetSafeDefinition("AM_MOC_COMPILE_DEFINITIONS");
+  this->MocCompileDefinitionsStr = makefile->GetSafeDefinition(
+                                                 "AM_MOC_COMPILE_DEFINITIONS");
   this->MocDefinitionsStr = makefile->GetSafeDefinition("AM_MOC_DEFINITIONS");
   this->MocIncludesStr = makefile->GetSafeDefinition("AM_MOC_INCLUDES");
   this->ProjectBinaryDir = makefile->GetSafeDefinition("AM_CMAKE_BINARY_DIR");
@@ -361,13 +362,18 @@ bool cmQtAutomoc::RunAutomocQt4()
     this->GenerateAll = true;
     }
 
-  // the program goes through all .cpp files to see which moc files are included. It is not really
-  // interesting how the moc file is named, but what file the moc is created from. Once a moc is
-  // included the same moc may not be included in the _automoc.cpp file anymore. OTOH if there's a
-  // header containing Q_OBJECT where no corresponding moc file is included anywhere a
-  // moc_<filename>.cpp file is created and included in the _automoc.cpp file.
-  std::map<std::string, std::string> includedMocs;    // key = moc source filepath, value = moc output filepath
-  std::map<std::string, std::string> notIncludedMocs; // key = moc source filepath, value = moc output filename
+  // the program goes through all .cpp files to see which moc files are
+  // included. It is not really interesting how the moc file is named, but
+  // what file the moc is created from. Once a moc is included the same moc
+  // may not be included in the _automoc.cpp file anymore. OTOH if there's a
+  // header containing Q_OBJECT where no corresponding moc file is included
+  // anywhere a moc_<filename>.cpp file is created and included in
+  // the _automoc.cpp file.
+
+  // key = moc source filepath, value = moc output filepath
+  std::map<std::string, std::string> includedMocs;
+  // key = moc source filepath, value = moc output filename
+  std::map<std::string, std::string> notIncludedMocs;
 
   cmsys::RegularExpression mocIncludeRegExp(
               "[\n][ \t]*#[ \t]*include[ \t]+"
@@ -422,8 +428,8 @@ bool cmQtAutomoc::RunAutomocQt4()
     int matchOffset = 0;
     if (!mocIncludeRegExp.find(contentsString.c_str()))
       {
-      // no moc #include, look whether we need to create a moc from the .h nevertheless
-      //std::cout << "no moc #include in the .cpp file";
+      // no moc #include, look whether we need to create a moc from
+      // the .h nevertheless
       const std::string basename =
             cmsys::SystemTools::GetFilenameWithoutLastExtension(absFilename);
       for(std::list<std::string>::const_iterator ext =
@@ -453,8 +459,8 @@ bool cmQtAutomoc::RunAutomocQt4()
         {
         const std::string privateHeaderName = absPath+basename+"_p"+(*ext);
         if (cmsys::SystemTools::FileExists(privateHeaderName.c_str())
-                && includedMocs.find(privateHeaderName) == includedMocs.end()
-                && notIncludedMocs.find(privateHeaderName) == notIncludedMocs.end())
+           && includedMocs.find(privateHeaderName) == includedMocs.end()
+           && notIncludedMocs.find(privateHeaderName) == notIncludedMocs.end())
           {
           const std::string currentMoc = "moc_" + basename + "_p.cpp";
           const std::string contents = this->ReadAll(privateHeaderName);
@@ -479,20 +485,19 @@ bool cmQtAutomoc::RunAutomocQt4()
                                   GetFilenameWithoutLastExtension(currentMoc);
         const bool moc_style = this->StartsWith(basename, "moc_");
 
-        // If the moc include is of the moc_foo.cpp style we expect the Q_OBJECT class
-        // declaration in a header file.
-        // If the moc include is of the foo.moc style we need to look for a Q_OBJECT
-        // macro in the current source file, if it contains the macro we generate the
-        // moc file from the source file, else from the header.
-        //
-        // TODO: currently any .moc file name will be used if the source contains
+        // If the moc include is of the moc_foo.cpp style we expect
+        // the Q_OBJECT class declaration in a header file.
+        // If the moc include is of the foo.moc style we need to look for
+        // a Q_OBJECT macro in the current source file, if it contains the
+        // macro we generate the moc file from the source file, else from the
+        // header.
         // Q_OBJECT
         if (moc_style || !qObjectRegExp.find(contentsString))
           {
           if (moc_style)
             {
-            // basename should be the part of the moc filename used for finding the
-            // correct header, so we need to remove the moc_ part
+            // basename should be the part of the moc filename used for
+            // finding the correct header, so we need to remove the moc_ part
             basename = basename.substr(4);
             }
 
@@ -513,7 +518,8 @@ bool cmQtAutomoc::RunAutomocQt4()
             }
           if (!headerFound)
             {
-            // the moc file is in a subdir => look for the header in the same subdir
+            // the moc file is in a subdir => look for the header in the
+            // same subdir
             if (currentMoc.find_first_of('/') != std::string::npos)
               {
               const std::string &filepath = absPath
@@ -536,20 +542,23 @@ bool cmQtAutomoc::RunAutomocQt4()
                 }
               if (!headerFound)
                 {
-                std::cerr << "automoc4: The file \"" << absFilename <<
-                    "\" includes the moc file \"" << currentMoc << "\", but neither \"" <<
-                    absPath + basename + '{' + this->Join(headerExtensions, ',') + "}\" nor \"" <<
-                    filepath + '{' + this->Join(headerExtensions, ',') + '}' <<
-                    "\" exist." << std::endl;
+                std::cerr << "automoc4: The file \"" << absFilename
+                          << "\" includes the moc file \"" << currentMoc
+                          << "\", but neither \"" << absPath << basename
+                          << '{' << this->Join(headerExtensions, ',')
+                          << "}\" nor \"" << filepath << '{'
+                          << this->Join(headerExtensions, ',') << '}'
+                          << "\" exist." << std::endl;
                 ::exit(EXIT_FAILURE);
                 }
               }
             else
               {
-              std::cerr << "automoc4: The file \"" << absFilename <<
-                  "\" includes the moc file \"" << currentMoc << "\", but \"" <<
-                  absPath + basename + '{' + this->Join(headerExtensions, ',') + '}' <<
-                  "\" does not exist." << std::endl;
+              std::cerr << "automoc4: The file \"" << absFilename
+                        << "\" includes the moc file \"" << currentMoc
+                        << "\", but \"" << absPath << basename << '{'
+                        << this->Join(headerExtensions, ',') << '}'
+                        << "\" does not exist." << std::endl;
               ::exit(EXIT_FAILURE);
               }
             }
@@ -578,17 +587,20 @@ bool cmQtAutomoc::RunAutomocQt4()
     if (includedMocs.find(absFilename) == includedMocs.end()
               && notIncludedMocs.find(absFilename) == notIncludedMocs.end())
       {
-      // if this header is not getting processed yet and is explicitly mentioned for the
-      // automoc the moc is run unconditionally on the header and the resulting file is
-      // included in the _automoc.cpp file (unless there's a .cpp file later on that
-      // includes the moc from this header)
-      const std::string currentMoc = "moc_" + cmsys::SystemTools::GetFilenameWithoutLastExtension(absFilename) + ".cpp";
+      // if this header is not getting processed yet and is explicitly
+      // mentioned for the automoc the moc is run unconditionally on the
+      // header and the resulting file is included in the _automoc.cpp file
+      // (unless there's a .cpp file later on that includes the moc from
+      // this header)
+      const std::string currentMoc = "moc_" + cmsys::SystemTools::
+                         GetFilenameWithoutLastExtension(absFilename) + ".cpp";
       notIncludedMocs[absFilename] = currentMoc;
       }
     }
 
   // run moc on all the moc's that are #included in source files
-  for(std::map<std::string, std::string>::const_iterator it = includedMocs.begin();
+  for(std::map<std::string, std::string>::const_iterator
+                                                     it = includedMocs.begin();
       it != includedMocs.end();
       ++it)
     {
@@ -605,8 +617,10 @@ bool cmQtAutomoc::RunAutomocQt4()
     }
   else
     {
-    // run moc on the remaining headers and include them in the _automoc.cpp file
-    for(std::map<std::string, std::string>::const_iterator it = notIncludedMocs.begin();
+    // run moc on the remaining headers and include them in
+    // the _automoc.cpp file
+    for(std::map<std::string, std::string>::const_iterator
+                                                  it = notIncludedMocs.begin();
         it != notIncludedMocs.end();
         ++it)
       {
@@ -621,8 +635,6 @@ bool cmQtAutomoc::RunAutomocQt4()
 
   if (this->RunMocFailed)
     {
-    // if any moc process failed we don't want to touch the _automoc.cpp file so that
-    // automoc4 is rerun until the issue is fixed
     std::cerr << "returning failed.."<< std::endl;
     return false;
     }
@@ -638,7 +650,6 @@ bool cmQtAutomoc::RunAutomocQt4()
       return true;
       }
     }
-  // either the contents of the _automoc.cpp file or one of the mocs included by it have changed
 
   // source file that includes all remaining moc files (_automoc.cpp file)
   std::fstream outfile;
@@ -654,7 +665,6 @@ bool cmQtAutomoc::RunAutomocQt4()
 bool cmQtAutomoc::GenerateMoc(const std::string& sourceFile,
                               const std::string& mocFileName)
 {
-    //std::cout << "AutoMoc::generateMoc" << sourceFile << mocFileName << std::endl;
   const std::string mocFilePath = this->Builddir + mocFileName;
   int sourceNewerThanMoc = 0;
   bool success = cmsys::SystemTools::FileTimeCompare(sourceFile.c_str(),
@@ -710,10 +720,11 @@ bool cmQtAutomoc::GenerateMoc(const std::string& sourceFile,
 
     std::string output;
     int retVal = 0;
-    const bool result = cmSystemTools::RunSingleCommand(command, &output, &retVal);
+    bool result = cmSystemTools::RunSingleCommand(command, &output, &retVal);
     if (!result || retVal)
       {
-      std::cerr << "automoc4: process for " << mocFilePath << " failed:\n" << output << std::endl;
+      std::cerr << "automoc4: process for " << mocFilePath << " failed:\n"
+                << output << std::endl;
       this->RunMocFailed = true;
       cmSystemTools::RemoveFile(mocFilePath.c_str());
       }