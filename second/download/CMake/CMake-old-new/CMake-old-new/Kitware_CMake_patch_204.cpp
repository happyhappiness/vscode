@@ -145,9 +145,9 @@ cmake::cmake()
   }
 #endif
 
-  this->GlobalGenerator = 0;
-  this->ProgressCallback = 0;
-  this->ProgressCallbackClientData = 0;
+  this->GlobalGenerator = CM_NULLPTR;
+  this->ProgressCallback = CM_NULLPTR;
+  this->ProgressCallbackClientData = CM_NULLPTR;
   this->CurrentWorkingMode = NORMAL_MODE;
 
 #ifdef CMAKE_BUILD_WITH_CMAKE
@@ -191,7 +191,7 @@ cmake::~cmake()
   delete this->State;
   if (this->GlobalGenerator) {
     delete this->GlobalGenerator;
-    this->GlobalGenerator = 0;
+    this->GlobalGenerator = CM_NULLPTR;
   }
   cmDeleteAll(this->Generators);
 #ifdef CMAKE_BUILD_WITH_CMAKE
@@ -463,7 +463,8 @@ bool cmake::FindPackage(const std::vector<std::string>& args)
 
     gg->CreateGenerationObjects();
     cmLocalGenerator* lg = gg->LocalGenerators[0];
-    std::string includeFlags = lg->GetIncludeFlags(includeDirs, 0, language);
+    std::string includeFlags =
+      lg->GetIncludeFlags(includeDirs, CM_NULLPTR, language);
 
     std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");
     printf("%s %s\n", includeFlags.c_str(), definitions.c_str());
@@ -870,7 +871,7 @@ void cmake::GetRegisteredGenerators(std::vector<GeneratorInfo>& generators)
 
 cmGlobalGenerator* cmake::CreateGlobalGenerator(const std::string& gname)
 {
-  cmExternalMakefileProjectGenerator* extraGenerator = 0;
+  cmExternalMakefileProjectGenerator* extraGenerator = CM_NULLPTR;
   std::string name = gname;
   RegisteredExtraGeneratorsMap::const_iterator extraGenIt =
     this->ExtraGenerators.find(name);
@@ -879,7 +880,7 @@ cmGlobalGenerator* cmake::CreateGlobalGenerator(const std::string& gname)
     name = extraGenerator->GetGlobalGeneratorName(name);
   }
 
-  cmGlobalGenerator* generator = 0;
+  cmGlobalGenerator* generator = CM_NULLPTR;
   for (RegisteredGeneratorsVector::const_iterator i = this->Generators.begin();
        i != this->Generators.end(); ++i) {
     generator = (*i)->CreateGlobalGenerator(name, this);
@@ -1707,8 +1708,8 @@ int cmake::CheckBuildSystem()
   // the make system's VERBOSE environment variable to enable verbose
   // output. This can be skipped by setting CMAKE_NO_VERBOSE (which is set
   // by the Eclipse and KDevelop generators).
-  bool verbose = ((cmSystemTools::GetEnv("VERBOSE") != 0) &&
-                  (cmSystemTools::GetEnv("CMAKE_NO_VERBOSE") == 0));
+  bool verbose = ((cmSystemTools::GetEnv("VERBOSE") != CM_NULLPTR) &&
+                  (cmSystemTools::GetEnv("CMAKE_NO_VERBOSE") == CM_NULLPTR));
 
   // This method will check the integrity of the build system if the
   // option was given on the command line.  It reads the given file to
@@ -1973,7 +1974,7 @@ cmInstalledFile const* cmake::GetInstalledFile(const std::string& name) const
     cmInstalledFile const& file = i->second;
     return &file;
   } else {
-    return 0;
+    return CM_NULLPTR;
   }
 }
 