@@ -375,33 +375,6 @@ bool cmQtAutomoc::RunAutomocQt4()
   // key = moc source filepath, value = moc output filename
   std::map<std::string, std::string> notIncludedMocs;
 
-  cmsys::RegularExpression mocIncludeRegExp(
-              "[\n][ \t]*#[ \t]*include[ \t]+"
-              "[\"<](([^ \">]+/)?moc_[^ \">/]+\\.cpp|[^ \">]+\\.moc)[\">]");
-  cmsys::RegularExpression qObjectRegExp("[\n][ \t]*Q_OBJECT[^a-zA-Z0-9_]");
-  std::list<std::string> headerExtensions;
-#if defined(_WIN32)
-  // not case sensitive
-  headerExtensions.push_back(".h");
-  headerExtensions.push_back(".hpp");
-  headerExtensions.push_back(".hxx");
-#elif defined(__APPLE__)
-  headerExtensions.push_back(".h");
-  headerExtensions.push_back(".hpp");
-  headerExtensions.push_back(".hxx");
-
-  // detect case-sensitive filesystem
-  long caseSensitive = pathconf(this->Srcdir.c_str(), _PC_CASE_SENSITIVE);
-  if (caseSensitive == 1)
-  {
-    headerExtensions.push_back(".H");
-  }
-#else
-  headerExtensions.push_back(".h");
-  headerExtensions.push_back(".hpp");
-  headerExtensions.push_back(".hxx");
-  headerExtensions.push_back(".H");
-#endif
 
   std::vector<std::string> sourceFiles;
   cmSystemTools::ExpandListArgument(this->Sources, sourceFiles);
@@ -415,162 +388,7 @@ bool cmQtAutomoc::RunAutomocQt4()
       {
       printf("Checking -%s-\n", absFilename.c_str());
       }
-
-    const std::string contentsString = this->ReadAll(absFilename);
-    if (contentsString.empty())
-      {
-      std::cerr << "automoc4: empty source file: " << absFilename << std::endl;
-      continue;
-      }
-    const std::string absPath = cmsys::SystemTools::GetFilenamePath(
-                cmsys::SystemTools::GetRealPath(absFilename.c_str())) + '/';
-
-    int matchOffset = 0;
-    if (!mocIncludeRegExp.find(contentsString.c_str()))
-      {
-      // no moc #include, look whether we need to create a moc from
-      // the .h nevertheless
-      const std::string basename =
-            cmsys::SystemTools::GetFilenameWithoutLastExtension(absFilename);
-      for(std::list<std::string>::const_iterator ext =
-                                                    headerExtensions.begin();
-          ext != headerExtensions.end();
-          ++ext)
-        {
-        const std::string headername = absPath + basename + (*ext);
-        if (cmsys::SystemTools::FileExists(headername.c_str())
-                && includedMocs.find(headername) == includedMocs.end()
-                && notIncludedMocs.find(headername) == notIncludedMocs.end())
-          {
-          const std::string currentMoc = "moc_" + basename + ".cpp";
-          const std::string contents = this->ReadAll(headername);
-          if (qObjectRegExp.find(contents))
-            {
-            //std::cout << "header contains Q_OBJECT macro";
-            notIncludedMocs[headername] = currentMoc;
-            }
-          break;
-          }
-        }
-      for(std::list<std::string>::const_iterator ext =
-                                                    headerExtensions.begin();
-          ext != headerExtensions.end();
-          ++ext)
-        {
-        const std::string privateHeaderName = absPath+basename+"_p"+(*ext);
-        if (cmsys::SystemTools::FileExists(privateHeaderName.c_str())
-           && includedMocs.find(privateHeaderName) == includedMocs.end()
-           && notIncludedMocs.find(privateHeaderName) == notIncludedMocs.end())
-          {
-          const std::string currentMoc = "moc_" + basename + "_p.cpp";
-          const std::string contents = this->ReadAll(privateHeaderName);
-          if (qObjectRegExp.find(contents))
-            {
-            //std::cout << "header contains Q_OBJECT macro";
-            notIncludedMocs[privateHeaderName] = currentMoc;
-            }
-          break;
-          }
-        }
-      }
-    else
-      {
-      // for every moc include in the file
-      do
-        {
-        const std::string currentMoc = mocIncludeRegExp.match(1);
-        //std::cout << "found moc include: " << currentMoc << std::endl;
-
-        std::string basename = cmsys::SystemTools::
-                                  GetFilenameWithoutLastExtension(currentMoc);
-        const bool moc_style = this->StartsWith(basename, "moc_");
-
-        // If the moc include is of the moc_foo.cpp style we expect
-        // the Q_OBJECT class declaration in a header file.
-        // If the moc include is of the foo.moc style we need to look for
-        // a Q_OBJECT macro in the current source file, if it contains the
-        // macro we generate the moc file from the source file, else from the
-        // header.
-        // Q_OBJECT
-        if (moc_style || !qObjectRegExp.find(contentsString))
-          {
-          if (moc_style)
-            {
-            // basename should be the part of the moc filename used for
-            // finding the correct header, so we need to remove the moc_ part
-            basename = basename.substr(4);
-            }
-
-          bool headerFound = false;
-          for(std::list<std::string>::const_iterator ext =
-                                                    headerExtensions.begin();
-              ext != headerExtensions.end();
-              ++ext)
-            {
-            const std::string &sourceFilePath = absPath + basename + (*ext);
-            if (cmsys::SystemTools::FileExists(sourceFilePath.c_str()))
-              {
-              headerFound = true;
-              includedMocs[sourceFilePath] = currentMoc;
-              notIncludedMocs.erase(sourceFilePath);
-              break;
-              }
-            }
-          if (!headerFound)
-            {
-            // the moc file is in a subdir => look for the header in the
-            // same subdir
-            if (currentMoc.find_first_of('/') != std::string::npos)
-              {
-              const std::string &filepath = absPath
-                      + cmsys::SystemTools::GetFilenamePath(currentMoc)
-                      + '/' + basename;
-
-              for(std::list<std::string>::const_iterator ext =
-                                                    headerExtensions.begin();
-                  ext != headerExtensions.end();
-                  ++ext)
-                {
-                const std::string &sourceFilePath = filepath + (*ext);
-                if (cmsys::SystemTools::FileExists(sourceFilePath.c_str()))
-                  {
-                  headerFound = true;
-                  includedMocs[sourceFilePath] = currentMoc;
-                  notIncludedMocs.erase(sourceFilePath);
-                  break;
-                  }
-                }
-              if (!headerFound)
-                {
-                std::cerr << "automoc4: The file \"" << absFilename
-                          << "\" includes the moc file \"" << currentMoc
-                          << "\", but neither \"" << absPath << basename
-                          << '{' << this->Join(headerExtensions, ',')
-                          << "}\" nor \"" << filepath << '{'
-                          << this->Join(headerExtensions, ',') << '}'
-                          << "\" exist." << std::endl;
-                ::exit(EXIT_FAILURE);
-                }
-              }
-            else
-              {
-              std::cerr << "automoc4: The file \"" << absFilename
-                        << "\" includes the moc file \"" << currentMoc
-                        << "\", but \"" << absPath << basename << '{'
-                        << this->Join(headerExtensions, ',') << '}'
-                        << "\" does not exist." << std::endl;
-              ::exit(EXIT_FAILURE);
-              }
-            }
-          }
-        else
-          {
-          includedMocs[absFilename] = currentMoc;
-          notIncludedMocs.erase(absFilename);
-          }
-        matchOffset += mocIncludeRegExp.end();
-        } while(mocIncludeRegExp.find(contentsString.c_str() + matchOffset));
-      }
+    this->ParseCppFile(absFilename, includedMocs, notIncludedMocs);
     }
 
   std::vector<std::string> headerFiles;
@@ -662,6 +480,187 @@ bool cmQtAutomoc::RunAutomocQt4()
 }
 
 
+void cmQtAutomoc::ParseCppFile(const std::string& absFilename,
+                           std::map<std::string, std::string>& includedMocs,
+                           std::map<std::string, std::string>& notIncludedMocs)
+{
+  cmsys::RegularExpression mocIncludeRegExp(
+              "[\n][ \t]*#[ \t]*include[ \t]+"
+              "[\"<](([^ \">]+/)?moc_[^ \">/]+\\.cpp|[^ \">]+\\.moc)[\">]");
+  cmsys::RegularExpression qObjectRegExp("[\n][ \t]*Q_OBJECT[^a-zA-Z0-9_]");
+  std::list<std::string> headerExtensions;
+  headerExtensions.push_back(".h");
+  headerExtensions.push_back(".hpp");
+  headerExtensions.push_back(".hxx");
+#if defined(_WIN32)
+  // not case sensitive, don't add ".H"
+#elif defined(__APPLE__)
+  // detect case-sensitive filesystem
+  long caseSensitive = pathconf(this->Srcdir.c_str(), _PC_CASE_SENSITIVE);
+  if (caseSensitive == 1)
+  {
+    headerExtensions.push_back(".H");
+  }
+#else
+  headerExtensions.push_back(".H");
+#endif
+
+  const std::string contentsString = this->ReadAll(absFilename);
+  if (contentsString.empty())
+    {
+    std::cerr << "automoc4: empty source file: " << absFilename << std::endl;
+    return;
+    }
+  const std::string absPath = cmsys::SystemTools::GetFilenamePath(
+                   cmsys::SystemTools::GetRealPath(absFilename.c_str())) + '/';
+
+  int matchOffset = 0;
+  if (!mocIncludeRegExp.find(contentsString.c_str()))
+    {
+    // no moc #include, look whether we need to create a moc from
+    // the .h nevertheless
+    const std::string basename =
+              cmsys::SystemTools::GetFilenameWithoutLastExtension(absFilename);
+    for(std::list<std::string>::const_iterator ext = headerExtensions.begin();
+        ext != headerExtensions.end();
+        ++ext)
+      {
+      const std::string headername = absPath + basename + (*ext);
+      if (cmsys::SystemTools::FileExists(headername.c_str())
+              && includedMocs.find(headername) == includedMocs.end()
+              && notIncludedMocs.find(headername) == notIncludedMocs.end())
+        {
+        const std::string currentMoc = "moc_" + basename + ".cpp";
+        const std::string contents = this->ReadAll(headername);
+        if (qObjectRegExp.find(contents))
+          {
+          //std::cout << "header contains Q_OBJECT macro";
+          notIncludedMocs[headername] = currentMoc;
+          }
+        break;
+        }
+      }
+    for(std::list<std::string>::const_iterator ext = headerExtensions.begin();
+        ext != headerExtensions.end();
+        ++ext)
+      {
+      const std::string privateHeaderName = absPath+basename+"_p"+(*ext);
+      if (cmsys::SystemTools::FileExists(privateHeaderName.c_str())
+          && includedMocs.find(privateHeaderName) == includedMocs.end()
+          && notIncludedMocs.find(privateHeaderName) == notIncludedMocs.end())
+        {
+        const std::string currentMoc = "moc_" + basename + "_p.cpp";
+        const std::string contents = this->ReadAll(privateHeaderName);
+        if (qObjectRegExp.find(contents))
+          {
+          //std::cout << "header contains Q_OBJECT macro";
+          notIncludedMocs[privateHeaderName] = currentMoc;
+          }
+        break;
+        }
+      }
+    }
+  else
+    {
+    // for every moc include in the file
+    do
+      {
+      const std::string currentMoc = mocIncludeRegExp.match(1);
+      //std::cout << "found moc include: " << currentMoc << std::endl;
+
+      std::string basename = cmsys::SystemTools::
+                                   GetFilenameWithoutLastExtension(currentMoc);
+      const bool moc_style = this->StartsWith(basename, "moc_");
+
+      // If the moc include is of the moc_foo.cpp style we expect
+      // the Q_OBJECT class declaration in a header file.
+      // If the moc include is of the foo.moc style we need to look for
+      // a Q_OBJECT macro in the current source file, if it contains the
+      // macro we generate the moc file from the source file, else from the
+      // header.
+      // Q_OBJECT
+      if (moc_style || !qObjectRegExp.find(contentsString))
+        {
+        if (moc_style)
+          {
+          // basename should be the part of the moc filename used for
+          // finding the correct header, so we need to remove the moc_ part
+          basename = basename.substr(4);
+          }
+
+        bool headerFound = false;
+        for(std::list<std::string>::const_iterator ext =
+                                                      headerExtensions.begin();
+            ext != headerExtensions.end();
+            ++ext)
+          {
+          const std::string &sourceFilePath = absPath + basename + (*ext);
+          if (cmsys::SystemTools::FileExists(sourceFilePath.c_str()))
+            {
+            headerFound = true;
+            includedMocs[sourceFilePath] = currentMoc;
+            notIncludedMocs.erase(sourceFilePath);
+            break;
+            }
+          }
+        if (!headerFound)
+          {
+          // the moc file is in a subdir => look for the header in the
+          // same subdir
+          if (currentMoc.find_first_of('/') != std::string::npos)
+            {
+            const std::string &filepath = absPath
+                    + cmsys::SystemTools::GetFilenamePath(currentMoc)
+                    + '/' + basename;
+
+            for(std::list<std::string>::const_iterator ext =
+                                                      headerExtensions.begin();
+                ext != headerExtensions.end();
+                ++ext)
+              {
+              const std::string &sourceFilePath = filepath + (*ext);
+              if (cmsys::SystemTools::FileExists(sourceFilePath.c_str()))
+                {
+                headerFound = true;
+                includedMocs[sourceFilePath] = currentMoc;
+                notIncludedMocs.erase(sourceFilePath);
+                break;
+                }
+              }
+            if (!headerFound)
+              {
+              std::cerr << "automoc4: The file \"" << absFilename
+                        << "\" includes the moc file \"" << currentMoc
+                        << "\", but neither \"" << absPath << basename
+                        << '{' << this->Join(headerExtensions, ',')
+                        << "}\" nor \"" << filepath << '{'
+                        << this->Join(headerExtensions, ',') << '}'
+                        << "\" exist." << std::endl;
+              ::exit(EXIT_FAILURE);
+              }
+            }
+          else
+            {
+            std::cerr << "automoc4: The file \"" << absFilename
+                      << "\" includes the moc file \"" << currentMoc
+                      << "\", but \"" << absPath << basename << '{'
+                      << this->Join(headerExtensions, ',') << '}'
+                      << "\" does not exist." << std::endl;
+            ::exit(EXIT_FAILURE);
+            }
+          }
+        }
+      else
+        {
+        includedMocs[absFilename] = currentMoc;
+        notIncludedMocs.erase(absFilename);
+        }
+      matchOffset += mocIncludeRegExp.end();
+      } while(mocIncludeRegExp.find(contentsString.c_str() + matchOffset));
+    }
+}
+
+
 bool cmQtAutomoc::GenerateMoc(const std::string& sourceFile,
                               const std::string& mocFileName)
 {