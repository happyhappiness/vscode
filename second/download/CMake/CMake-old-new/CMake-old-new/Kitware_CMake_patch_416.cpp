@@ -38,10 +38,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   char targetNameBuf[64];
   bool didOutputVariable = false;
   bool didCopyFile = false;
+  bool useSources = argv[2] == "SOURCES";
+  std::vector<std::string> sources;
 
   enum Doing { DoingNone, DoingCMakeFlags, DoingCompileDefinitions,
-               DoingLinkLibraries, DoingOutputVariable, DoingCopyFile };
-  Doing doing = DoingNone;
+               DoingLinkLibraries, DoingOutputVariable, DoingCopyFile,
+               DoingSources };
+  Doing doing = useSources? DoingSources : DoingNone;
   for(size_t i=3; i < argv.size(); ++i)
     {
     if(argv[i] == "CMAKE_FLAGS")
@@ -118,6 +121,10 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       copyFile = argv[i].c_str();
       doing = DoingNone;
       }
+    else if(doing == DoingSources)
+      {
+      sources.push_back(argv[i]);
+      }
     else if(i == 3)
       {
       this->SrcFileSignature = false;
@@ -149,6 +156,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     return -1;
     }
 
+  if(useSources && sources.empty())
+    {
+    this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+      "SOURCES must be followed by at least one source file");
+    return -1;
+    }
+
   // compute the binary dir when TRY_COMPILE is called with a src file
   // signature
   if (this->SrcFileSignature)
@@ -193,6 +207,44 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     std::string ccFile = this->BinaryDirectory + "/CMakeCache.txt";
     cmSystemTools::RemoveFile(ccFile.c_str());
 
+    // Choose sources.
+    if(!useSources)
+      {
+      sources.push_back(argv[2]);
+      }
+
+    // Detect languages to enable.
+    cmGlobalGenerator* gg =
+      this->Makefile->GetCMakeInstance()->GetGlobalGenerator();
+    std::set<std::string> testLangs;
+    for(std::vector<std::string>::iterator si = sources.begin();
+        si != sources.end(); ++si)
+      {
+      std::string ext = cmSystemTools::GetFilenameLastExtension(*si);
+      if(const char* lang = gg->GetLanguageFromExtension(ext.c_str()))
+        {
+        testLangs.insert(lang);
+        }
+      else
+        {
+        cmOStringStream err;
+        err << "Unknown extension \"" << ext << "\" for file\n"
+            << "  " << *si << "\n"
+            << "try_compile() works only for enabled languages.  "
+            << "Currently these are:\n ";
+        std::vector<std::string> langs;
+        gg->GetEnabledLanguages(langs);
+        for(std::vector<std::string>::iterator l = langs.begin();
+            l != langs.end(); ++l)
+          {
+          err << " " << *l;
+          }
+        err << "\nSee project() command to enable other languages.";
+        this->Makefile->IssueMessage(cmake::FATAL_ERROR, err.str());
+        return -1;
+        }
+      }
+
     // we need to create a directory and CMakeLists file etc...
     // first create the directories
     sourceDirectory = this->BinaryDirectory.c_str();
@@ -209,10 +261,6 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       return -1;
       }
 
-    std::string source = argv[2];
-    std::string ext = cmSystemTools::GetFilenameLastExtension(source);
-    const char* lang =(this->Makefile->GetCMakeInstance()->GetGlobalGenerator()
-                        ->GetLanguageFromExtension(ext.c_str()));
     const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");
     fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",
             cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),
@@ -222,57 +270,39 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);
       }
 
-    const char* rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";
-    std::string rulesOverrideLang =
-      rulesOverrideBase + (lang ? std::string("_") + lang : std::string(""));
-    if(const char* rulesOverridePath =
-       this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
+    std::string projectLangs;
+    for(std::set<std::string>::iterator li = testLangs.begin();
+        li != testLangs.end(); ++li)
       {
-      fprintf(fout, "SET(%s \"%s\")\n",
-              rulesOverrideLang.c_str(), rulesOverridePath);
-      }
-    else if(const char* rulesOverridePath2 =
-            this->Makefile->GetDefinition(rulesOverrideBase))
-      {
-      fprintf(fout, "SET(%s \"%s\")\n",
-              rulesOverrideBase, rulesOverridePath2);
-      }
-
-    if(lang)
-      {
-      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE %s)\n", lang);
-      }
-    else
-      {
-      fclose(fout);
-      cmOStringStream err;
-      err << "Unknown extension \"" << ext << "\" for file\n"
-          << "  " << source << "\n"
-          << "try_compile() works only for enabled languages.  "
-          << "Currently these are:\n ";
-      std::vector<std::string> langs;
-      this->Makefile->GetCMakeInstance()->GetGlobalGenerator()->
-        GetEnabledLanguages(langs);
-      for(std::vector<std::string>::iterator l = langs.begin();
-          l != langs.end(); ++l)
+      projectLangs += " " + *li;
+      std::string rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";
+      std::string rulesOverrideLang = rulesOverrideBase + "_" + *li;
+      if(const char* rulesOverridePath =
+         this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
         {
-        err << " " << *l;
+        fprintf(fout, "SET(%s \"%s\")\n",
+                rulesOverrideLang.c_str(), rulesOverridePath);
+        }
+      else if(const char* rulesOverridePath2 =
+              this->Makefile->GetDefinition(rulesOverrideBase.c_str()))
+        {
+        fprintf(fout, "SET(%s \"%s\")\n",
+                rulesOverrideBase.c_str(), rulesOverridePath2);
         }
-      err << "\nSee project() command to enable other languages.";
-      this->Makefile->IssueMessage(cmake::FATAL_ERROR, err.str());
-      return -1;
       }
-    std::string langFlags = "CMAKE_";
-    langFlags +=  lang;
-    langFlags += "_FLAGS";
+    fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE%s)\n", projectLangs.c_str());
     fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");
-    fprintf(fout, "SET(CMAKE_%s_FLAGS \"", lang);
-    const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
-    if(flags)
+    for(std::set<std::string>::iterator li = testLangs.begin();
+        li != testLangs.end(); ++li)
       {
-      fprintf(fout, " %s ", flags);
+      fprintf(fout, "SET(CMAKE_%s_FLAGS \"", li->c_str());
+      std::string langFlags = "CMAKE_" + *li + "_FLAGS";
+      if(const char* flags = this->Makefile->GetDefinition(langFlags.c_str()))
+        {
+        fprintf(fout, " %s ", flags);
+        }
+      fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
       }
-    fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
     fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
     fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");
     fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
@@ -357,7 +387,19 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
             this->BinaryDirectory.c_str());
     /* Create the actual executable.  */
-    fprintf(fout, "ADD_EXECUTABLE(%s \"%s\")\n", targetName, source.c_str());
+    fprintf(fout, "ADD_EXECUTABLE(%s", targetName);
+    for(std::vector<std::string>::iterator si = sources.begin();
+        si != sources.end(); ++si)
+      {
+      fprintf(fout, " \"%s\"", si->c_str());
+
+      // Add dependencies on any non-temporary sources.
+      if(si->find("CMakeTmp") == si->npos)
+        {
+        this->Makefile->AddCMakeDependFile(si->c_str());
+        }
+      }
+    fprintf(fout, ")\n");
     if (useOldLinkLibs)
       {
       fprintf(fout,
@@ -371,12 +413,6 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       }
     fclose(fout);
     projectName = "CMAKE_TRY_COMPILE";
-    // if the source is not in CMakeTmp
-    if(source.find("CMakeTmp") == source.npos)
-      {
-      this->Makefile->AddCMakeDependFile(source.c_str());
-      }
-
     }
 
   bool erroroc = cmSystemTools::GetErrorOccuredFlag();