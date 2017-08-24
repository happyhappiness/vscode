@@ -14,16 +14,18 @@
 #include <algorithm>
 
 //----------------------------------------------------------------------------
+cmFindCommon::PathGroup cmFindCommon::PathGroup::All("ALL");
+cmFindCommon::PathLabel cmFindCommon::PathLabel::CMake("CMAKE");
+cmFindCommon::PathLabel
+  cmFindCommon::PathLabel::CMakeEnvironment("CMAKE_ENVIRONMENT");
+cmFindCommon::PathLabel cmFindCommon::PathLabel::Hints("HINTS");
+cmFindCommon::PathLabel
+  cmFindCommon::PathLabel::SystemEnvironment("SYSTM_ENVIRONMENT");
+cmFindCommon::PathLabel cmFindCommon::PathLabel::CMakeSystem("CMAKE_SYSTEM");
+cmFindCommon::PathLabel cmFindCommon::PathLabel::Guess("GUESS");
+
+//----------------------------------------------------------------------------
 cmFindCommon::cmFindCommon()
-: CMakeVariablePaths(this, "CMAKE"),
-  CMakeEnvironmentPaths(this, "CMAKE_ENVIRONMENT"),
-  UserHintsPaths(this, "HINTS"),
-  SystemEnvironmentPaths(this, "SYSTEM_ENVIRONMENT"),
-  UserRegistryPaths(this, "USER_REGISTRY"),
-  BuildPaths(this, "BUILD"),
-  CMakeSystemVariablePaths(this, "CMAKE_SYSTEM_VARIABLE"),
-  SystemRegistryPaths(this, "SYSTEM_REGISTRY"),
-  UserGuessPaths(this, "GUESS")
 {
   this->FindRootPathMode = RootPathModeBoth;
   this->NoDefaultPath = false;
@@ -45,6 +47,8 @@ cmFindCommon::cmFindCommon()
   this->SearchFrameworkLast = false;
   this->SearchAppBundleOnly = false;
   this->SearchAppBundleLast = false;
+
+  this->InitializeSearchPathGroups();
 }
 
 //----------------------------------------------------------------------------
@@ -53,6 +57,40 @@ cmFindCommon::~cmFindCommon()
 }
 
 //----------------------------------------------------------------------------
+void cmFindCommon::InitializeSearchPathGroups()
+{
+  std::vector<PathLabel>* labels;
+
+  // Define the varoius different groups of path types
+
+  // All search paths
+  labels = &this->PathGroupLabelMap[PathGroup::All];
+  labels->push_back(PathLabel::CMake);
+  labels->push_back(PathLabel::CMakeEnvironment);
+  labels->push_back(PathLabel::Hints);
+  labels->push_back(PathLabel::SystemEnvironment);
+  labels->push_back(PathLabel::CMakeSystem);
+  labels->push_back(PathLabel::Guess);
+
+  // Define the search group order
+  this->PathGroupOrder.push_back(PathGroup::All);
+
+  // Create the idividual labeld search paths
+  this->LabeledPaths.insert(std::make_pair(PathLabel::CMake,
+    cmSearchPath(this)));
+  this->LabeledPaths.insert(std::make_pair(PathLabel::CMakeEnvironment,
+    cmSearchPath(this)));
+  this->LabeledPaths.insert(std::make_pair(PathLabel::Hints,
+    cmSearchPath(this)));
+  this->LabeledPaths.insert(std::make_pair(PathLabel::SystemEnvironment,
+    cmSearchPath(this)));
+  this->LabeledPaths.insert(std::make_pair(PathLabel::CMakeSystem,
+    cmSearchPath(this)));
+  this->LabeledPaths.insert(std::make_pair(PathLabel::Guess,
+    cmSearchPath(this)));
+}
+
+//----------------------------------------------------------------------------
 void cmFindCommon::SelectDefaultRootPathMode()
 {
   // Check the policy variable for this find command type.
@@ -140,12 +178,12 @@ void cmFindCommon::RerootPaths(std::vector<std::string>& paths)
     fprintf(stderr, "[%s]\n", i->c_str());
     }
 #endif
-
   // Short-circuit if there is nothing to do.
   if(this->FindRootPathMode == RootPathModeNever)
     {
     return;
     }
+
   const char* sysroot =
     this->Makefile->GetDefinition("CMAKE_SYSROOT");
   const char* rootPath =
@@ -293,7 +331,7 @@ bool cmFindCommon::CheckCommonArgument(std::string const& arg)
     {
     this->NoCMakeSystemPath = true;
     }
-  else if(arg == "NO_CMAKE_FIND_ROOT_PATH")
+    else if(arg == "NO_CMAKE_FIND_ROOT_PATH")
     {
     this->FindRootPathMode = RootPathModeNever;
     }
@@ -361,15 +399,13 @@ void cmFindCommon::ComputeFinalPaths()
   this->GetIgnoredPaths(ignored);
 
   // Combine the seperate path types, filtering out ignores
-  this->CMakeVariablePaths.ExtractWithout(ignored, this->SearchPaths, true);
-  this->CMakeEnvironmentPaths.ExtractWithout(ignored, this->SearchPaths);
-  this->UserHintsPaths.ExtractWithout(ignored, this->SearchPaths);
-  this->SystemEnvironmentPaths.ExtractWithout(ignored, this->SearchPaths);
-  this->UserRegistryPaths.ExtractWithout(ignored, this->SearchPaths);
-  this->BuildPaths.ExtractWithout(ignored, this->SearchPaths);
-  this->CMakeSystemVariablePaths.ExtractWithout(ignored, this->SearchPaths);
-  this->SystemRegistryPaths.ExtractWithout(ignored, this->SearchPaths);
-  this->UserGuessPaths.ExtractWithout(ignored, this->SearchPaths);
+  this->SearchPaths.clear();
+  std::vector<PathLabel>& allLabels = this->PathGroupLabelMap[PathGroup::All];
+  for(std::vector<PathLabel>::const_iterator l = allLabels.begin();
+      l != allLabels.end(); ++l)
+    {
+    this->LabeledPaths[*l].ExtractWithout(ignored, this->SearchPaths);
+    }
 
   // Expand list of paths inside all search roots.
   this->RerootPaths(this->SearchPaths);