@@ -94,13 +94,13 @@ bool cmCacheManager::LoadCache(const std::string& path, bool internal,
         // If the entry is not internal to the cache being loaded
         // or if it is in the list of internal entries to be
         // imported, load it.
-        if (internal || (e.Type != cmState::INTERNAL) ||
+        if (internal || (e.Type != cmStateEnums::INTERNAL) ||
             (includes.find(entryKey) != includes.end())) {
           // If we are loading the cache from another project,
           // make all loaded entries internal so that it is
           // not visible in the gui
           if (!internal) {
-            e.Type = cmState::INTERNAL;
+            e.Type = cmStateEnums::INTERNAL;
             helpString = "DO NOT EDIT, ";
             helpString += entryKey;
             helpString += " loaded from external file.  "
@@ -142,11 +142,11 @@ bool cmCacheManager::LoadCache(const std::string& path, bool internal,
     this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", "0",
                         "Minor version of cmake used to create the "
                         "current loaded cache",
-                        cmState::INTERNAL);
+                        cmStateEnums::INTERNAL);
     this->AddCacheEntry("CMAKE_CACHE_MAJOR_VERSION", "0",
                         "Major version of cmake used to create the "
                         "current loaded cache",
-                        cmState::INTERNAL);
+                        cmStateEnums::INTERNAL);
   }
   // check to make sure the cache directory has not
   // been moved
@@ -178,7 +178,7 @@ bool cmCacheManager::ReadPropertyEntry(std::string const& entryKey,
                                        CacheEntry& e)
 {
   // All property entries are internal.
-  if (e.Type != cmState::INTERNAL) {
+  if (e.Type != cmStateEnums::INTERNAL) {
     return false;
   }
 
@@ -192,7 +192,7 @@ bool cmCacheManager::ReadPropertyEntry(std::string const& entryKey,
       if (it.IsAtEnd()) {
         // Create an entry and store the property.
         CacheEntry& ne = this->Cache[key];
-        ne.Type = cmState::UNINITIALIZED;
+        ne.Type = cmStateEnums::UNINITIALIZED;
         ne.SetProperty(*p, e.Value.c_str());
       } else {
         // Store this property on its entry.
@@ -244,17 +244,17 @@ bool cmCacheManager::SaveCache(const std::string& path)
   this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", temp,
                       "Minor version of cmake used to create the "
                       "current loaded cache",
-                      cmState::INTERNAL);
+                      cmStateEnums::INTERNAL);
   sprintf(temp, "%d", cmVersion::GetMajorVersion());
   this->AddCacheEntry("CMAKE_CACHE_MAJOR_VERSION", temp,
                       "Major version of cmake used to create the "
                       "current loaded cache",
-                      cmState::INTERNAL);
+                      cmStateEnums::INTERNAL);
   sprintf(temp, "%d", cmVersion::GetPatchVersion());
   this->AddCacheEntry("CMAKE_CACHE_PATCH_VERSION", temp,
                       "Patch version of cmake used to create the "
                       "current loaded cache",
-                      cmState::INTERNAL);
+                      cmStateEnums::INTERNAL);
 
   // Let us store the current working directory so that if somebody
   // Copies it, he will not be surprised
@@ -268,7 +268,7 @@ bool cmCacheManager::SaveCache(const std::string& path)
   this->AddCacheEntry("CMAKE_CACHEFILE_DIR", currentcwd.c_str(),
                       "This is the directory where this CMakeCache.txt"
                       " was created",
-                      cmState::INTERNAL);
+                      cmStateEnums::INTERNAL);
 
   /* clang-format off */
   fout << "# This is the CMakeCache file.\n"
@@ -301,14 +301,14 @@ bool cmCacheManager::SaveCache(const std::string& path)
          this->Cache.begin();
        i != this->Cache.end(); ++i) {
     const CacheEntry& ce = (*i).second;
-    cmState::CacheEntryType t = ce.Type;
+    cmStateEnums::CacheEntryType t = ce.Type;
     if (!ce.Initialized) {
       /*
         // This should be added in, but is not for now.
       cmSystemTools::Error("Cache entry \"", (*i).first.c_str(),
                            "\" is uninitialized");
       */
-    } else if (t != cmState::INTERNAL) {
+    } else if (t != cmStateEnums::INTERNAL) {
       // Format is key:type=value
       if (const char* help = ce.GetProperty("HELPSTRING")) {
         cmCacheManager::OutputHelpString(fout, help);
@@ -334,9 +334,9 @@ bool cmCacheManager::SaveCache(const std::string& path)
       continue;
     }
 
-    cmState::CacheEntryType t = i.GetType();
+    cmStateEnums::CacheEntryType t = i.GetType();
     this->WritePropertyEntries(fout, i);
-    if (t == cmState::INTERNAL) {
+    if (t == cmStateEnums::INTERNAL) {
       // Format is key:type=value
       if (const char* help = i.GetProperty("HELPSTRING")) {
         this->OutputHelpString(fout, help);
@@ -465,7 +465,7 @@ void cmCacheManager::PrintCache(std::ostream& out) const
   for (std::map<std::string, CacheEntry>::const_iterator i =
          this->Cache.begin();
        i != this->Cache.end(); ++i) {
-    if ((*i).second.Type != cmState::INTERNAL) {
+    if ((*i).second.Type != cmStateEnums::INTERNAL) {
       out << (*i).first << " = " << (*i).second.Value << std::endl;
     }
   }
@@ -477,7 +477,7 @@ void cmCacheManager::PrintCache(std::ostream& out) const
 
 void cmCacheManager::AddCacheEntry(const std::string& key, const char* value,
                                    const char* helpString,
-                                   cmState::CacheEntryType type)
+                                   cmStateEnums::CacheEntryType type)
 {
   CacheEntry& e = this->Cache[key];
   if (value) {
@@ -488,7 +488,7 @@ void cmCacheManager::AddCacheEntry(const std::string& key, const char* value,
   }
   e.Type = type;
   // make sure we only use unix style paths
-  if (type == cmState::FILEPATH || type == cmState::PATH) {
+  if (type == cmStateEnums::FILEPATH || type == cmStateEnums::PATH) {
     if (e.Value.find(';') != e.Value.npos) {
       std::vector<std::string> paths;
       cmSystemTools::ExpandListArgument(e.Value, paths);