@@ -630,7 +630,8 @@ bool cmake::FindPackage(const std::vector<std::string>& args)
     std::string linkLibs;
     std::string flags;
     std::string linkFlags;
-    lg->GetTargetFlags(linkLibs, flags, linkFlags, *tgt);
+    cmGeneratorTarget gtgt(tgt);
+    lg->GetTargetFlags(linkLibs, flags, linkFlags, &gtgt);
 
     printf("%s\n", linkLibs.c_str() );
 
@@ -2326,6 +2327,17 @@ int cmake::ActualConfigure()
     this->CacheManager->RemoveCacheEntry("CMAKE_GENERATOR");
     this->CacheManager->RemoveCacheEntry("CMAKE_EXTRA_GENERATOR");
     }
+
+  cmMakefile* mf=this->GlobalGenerator->GetLocalGenerators()[0]->GetMakefile();
+  if (mf->IsOn("CTEST_USE_LAUNCHERS")
+              && !this->GetProperty("RULE_LAUNCH_COMPILE", cmProperty::GLOBAL))
+    {
+    cmSystemTools::Error("CTEST_USE_LAUNCHERS is enabled, but the "
+                        "RULE_LAUNCH_COMPILE global property is not defined.\n"
+                        "Did you forget to include(CTest) in the toplevel "
+                         "CMakeLists.txt ?");
+    }
+
   // only save the cache if there were no fatal errors
   if ( this->GetWorkingMode() == NORMAL_MODE )
     {
@@ -2438,9 +2450,6 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
 
   this->PreLoadCMakeFiles();
 
-  std::string systemFile = this->GetHomeOutputDirectory();
-  systemFile += "/CMakeSystem.cmake";
-
   if ( noconfigure )
     {
     return 0;