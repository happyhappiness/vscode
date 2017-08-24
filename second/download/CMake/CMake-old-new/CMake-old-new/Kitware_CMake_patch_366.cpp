@@ -294,7 +294,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
             cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());
     if(def)
       {
-      fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);
+      fprintf(fout, "set(CMAKE_MODULE_PATH %s)\n", def);
       }
 
     std::string projectLangs;
@@ -307,35 +307,35 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       if(const char* rulesOverridePath =
          this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
         {
-        fprintf(fout, "SET(%s \"%s\")\n",
+        fprintf(fout, "set(%s \"%s\")\n",
                 rulesOverrideLang.c_str(), rulesOverridePath);
         }
       else if(const char* rulesOverridePath2 =
               this->Makefile->GetDefinition(rulesOverrideBase.c_str()))
         {
-        fprintf(fout, "SET(%s \"%s\")\n",
+        fprintf(fout, "set(%s \"%s\")\n",
                 rulesOverrideBase.c_str(), rulesOverridePath2);
         }
       }
-    fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE%s)\n", projectLangs.c_str());
-    fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");
+    fprintf(fout, "project(CMAKE_TRY_COMPILE%s)\n", projectLangs.c_str());
+    fprintf(fout, "set(CMAKE_VERBOSE_MAKEFILE 1)\n");
     for(std::set<std::string>::iterator li = testLangs.begin();
         li != testLangs.end(); ++li)
       {
       std::string langFlags = "CMAKE_" + *li + "_FLAGS";
       const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
-      fprintf(fout, "SET(CMAKE_%s_FLAGS %s)\n", li->c_str(),
+      fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
               lg->EscapeForCMake(flags?flags:"").c_str());
-      fprintf(fout, "SET(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
+      fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
               " ${COMPILE_DEFINITIONS}\")\n", li->c_str(), li->c_str());
       }
-    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
-    fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");
-    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
+    fprintf(fout, "include_directories(${INCLUDE_DIRECTORIES})\n");
+    fprintf(fout, "set(CMAKE_SUPPRESS_REGENERATION 1)\n");
+    fprintf(fout, "link_directories(${LINK_DIRECTORIES})\n");
     // handle any compile flags we need to pass on
     if (compileDefs.size())
       {
-      fprintf(fout, "ADD_DEFINITIONS( ");
+      fprintf(fout, "add_definitions( ");
       for (size_t i = 0; i < compileDefs.size(); ++i)
         {
         fprintf(fout,"%s ",compileDefs[i].c_str());
@@ -406,14 +406,14 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       }
     if(this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE")!=0)
       {
-      fprintf(fout, "SET(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
+      fprintf(fout, "set(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
       }
 
     /* Put the executable at a known location (for COPY_FILE).  */
-    fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
+    fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
             this->BinaryDirectory.c_str());
     /* Create the actual executable.  */
-    fprintf(fout, "ADD_EXECUTABLE(%s", targetName);
+    fprintf(fout, "add_executable(%s", targetName);
     for(std::vector<std::string>::iterator si = sources.begin();
         si != sources.end(); ++si)
       {
@@ -429,11 +429,11 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     if (useOldLinkLibs)
       {
       fprintf(fout,
-              "TARGET_LINK_LIBRARIES(%s ${LINK_LIBRARIES})\n",targetName);
+              "target_link_libraries(%s ${LINK_LIBRARIES})\n",targetName);
       }
     else
       {
-      fprintf(fout, "TARGET_LINK_LIBRARIES(%s %s)\n",
+      fprintf(fout, "target_link_libraries(%s %s)\n",
               targetName,
               libsToLink.c_str());
       }