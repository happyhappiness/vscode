@@ -1487,8 +1487,8 @@ int cmake::Configure()
   if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
     {
     char ver[256];
-    sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
-            cmMakefile::GetMinorVersion());
+    sprintf(ver,"%i.%i",cmVersion::GetMajorVersion(),
+            cmVersion::GetMinorVersion());
     this->CacheManager->AddCacheEntry
       ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
        "For backwards compatibility, what version of CMake commands and "
@@ -1680,10 +1680,10 @@ bool cmake::CacheVersionMatches()
     this->CacheManager->GetCacheValue("CMAKE_CACHE_RELEASE_VERSION");
   bool cacheSameCMake = false;
   if(majv &&
-     atoi(majv) == static_cast<int>(cmMakefile::GetMajorVersion())
+     atoi(majv) == static_cast<int>(cmVersion::GetMajorVersion())
      && minv &&
-     atoi(minv) == static_cast<int>(cmMakefile::GetMinorVersion())
-     && relv && (strcmp(relv, cmMakefile::GetReleaseVersion()) == 0))
+     atoi(minv) == static_cast<int>(cmVersion::GetMinorVersion())
+     && relv && (strcmp(relv, cmVersion::GetReleaseVersion().c_str()) == 0))
     {
     cacheSameCMake = true;
     }
@@ -1815,21 +1815,6 @@ int cmake::Generate()
   return 0;
 }
 
-unsigned int cmake::GetMajorVersion()
-{
-  return cmMakefile::GetMajorVersion();
-}
-
-unsigned int cmake::GetMinorVersion()
-{
-  return cmMakefile::GetMinorVersion();
-}
-
-const char *cmake::GetReleaseVersion()
-{
-  return cmMakefile::GetReleaseVersion();
-}
-
 void cmake::AddCacheEntry(const char* key, const char* value,
                           const char* helpString,
                           int type)
@@ -1852,8 +1837,9 @@ int cmake::DumpDocumentationToFile(std::ostream& f)
   const char *terse;
   const char *full;
   char tmp[1024];
-  sprintf(tmp,"Version %d.%d (%s)", cmake::GetMajorVersion(),
-          cmake::GetMinorVersion(), cmVersion::GetReleaseVersion().c_str());
+  sprintf(tmp,"Version %d.%d (%s)", cmVersion::GetMajorVersion(),
+          cmVersion::GetMinorVersion(),
+          cmVersion::GetReleaseVersion().c_str());
   f << "<html>\n";
   f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";
   f << "<ul>\n";
@@ -1959,8 +1945,8 @@ int cmake::LoadCache()
   if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
     {
     char ver[256];
-    sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
-            cmMakefile::GetMinorVersion());
+    sprintf(ver,"%i.%i",cmVersion::GetMajorVersion(),
+            cmVersion::GetMinorVersion());
     this->CacheManager->AddCacheEntry
       ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
        "For backwards compatibility, what version of CMake commands and "