@@ -491,6 +491,12 @@ void cmGlobalGenerator::ClearEnabledLanguages()
 
 void cmGlobalGenerator::Configure()
 {
+  // Setup the current output directory components for use by
+  // ConvertToRelativePath.
+  std::string outdir =
+    cmSystemTools::CollapseFullPath(m_CMakeInstance->GetHomeOutputDirectory());
+  cmSystemTools::SplitPath(outdir.c_str(), m_HomeOutputDirectoryComponents);
+
   // Delete any existing cmLocalGenerators
   unsigned int i;
   for (i = 0; i < m_LocalGenerators.size(); ++i)
@@ -522,8 +528,7 @@ void cmGlobalGenerator::Configure()
   sprintf(num,"%d",static_cast<int>(m_LocalGenerators.size()));
   this->GetCMakeInstance()->AddCacheEntry
     ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
-     "number of local generators",
-                                          cmCacheManager::INTERNAL);
+     "number of local generators", cmCacheManager::INTERNAL);
   
   std::set<cmStdString> notFoundMap;
   // after it is all done do a ConfigureFinalPass
@@ -1091,3 +1096,17 @@ void cmGlobalGenerator::SetupTests()
 }
 
 
+//----------------------------------------------------------------------------
+std::string cmGlobalGenerator::ConvertToHomeRelativePath(const char* remote)
+{
+  return (this->ConvertToRelativePath(m_HomeOutputDirectoryComponents,remote));
+}
+
+//----------------------------------------------------------------------------
+std::string
+cmGlobalGenerator::ConvertToHomeRelativeOutputPath(const char* remote)
+{
+  return cmSystemTools::ConvertToOutputPath
+    (this->ConvertToRelativePath(m_HomeOutputDirectoryComponents,remote).c_str());
+}
+