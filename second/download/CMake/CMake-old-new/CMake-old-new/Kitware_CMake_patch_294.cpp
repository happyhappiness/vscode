@@ -307,13 +307,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       std::string rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";
       std::string rulesOverrideLang = rulesOverrideBase + "_" + *li;
       if(const char* rulesOverridePath =
-         this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
+         this->Makefile->GetDefinition(rulesOverrideLang))
         {
         fprintf(fout, "set(%s \"%s\")\n",
                 rulesOverrideLang.c_str(), rulesOverridePath);
         }
       else if(const char* rulesOverridePath2 =
-              this->Makefile->GetDefinition(rulesOverrideBase.c_str()))
+              this->Makefile->GetDefinition(rulesOverrideBase))
         {
         fprintf(fout, "set(%s \"%s\")\n",
                 rulesOverrideBase.c_str(), rulesOverridePath2);
@@ -325,7 +325,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
         li != testLangs.end(); ++li)
       {
       std::string langFlags = "CMAKE_" + *li + "_FLAGS";
-      const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
+      const char* flags = this->Makefile->GetDefinition(langFlags);
       fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
               lg->EscapeForCMake(flags?flags:"").c_str());
       fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
@@ -484,7 +484,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   std::string output;
   // actually do the try compile now that everything is setup
   int res = this->Makefile->TryCompile(sourceDirectory,
-                                       this->BinaryDirectory.c_str(),
+                                       this->BinaryDirectory,
                                        projectName,
                                        targetName,
                                        this->SrcFileSignature,
@@ -496,14 +496,14 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     }
 
   // set the result var to the return value to indicate success or failure
-  this->Makefile->AddCacheDefinition(argv[0].c_str(),
+  this->Makefile->AddCacheDefinition(argv[0],
                                      (res == 0 ? "TRUE" : "FALSE"),
                                      "Result of TRY_COMPILE",
                                      cmCacheManager::INTERNAL);
 
   if ( outputVariable.size() > 0 )
     {
-    this->Makefile->AddDefinition(outputVariable.c_str(), output.c_str());
+    this->Makefile->AddDefinition(outputVariable, output.c_str());
     }
 
   if (this->SrcFileSignature)
@@ -540,7 +540,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
 
     if(!copyFileError.empty())
       {
-      this->Makefile->AddDefinition(copyFileError.c_str(),
+      this->Makefile->AddDefinition(copyFileError,
                                     copyFileErrorMessage.c_str());
       }
     }