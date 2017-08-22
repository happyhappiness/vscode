@@ -22,59 +22,13 @@
 #include <cmsys/FStream.hxx>
 #include <cmsys/RegularExpression.hxx>
 
-const char* cmCacheManagerTypes[] =
-{ "BOOL",
-  "PATH",
-  "FILEPATH",
-  "STRING",
-  "INTERNAL",
-  "STATIC",
-  "UNINITIALIZED",
-  0
-};
-
 cmCacheManager::cmCacheManager(cmake* cm)
 {
   this->CacheMajorVersion = 0;
   this->CacheMinorVersion = 0;
   this->CMakeInstance = cm;
 }
 
-const char* cmCacheManager::TypeToString(cmCacheManager::CacheEntryType type)
-{
-  if ( type > 6 )
-    {
-    return cmCacheManagerTypes[6];
-    }
-  return cmCacheManagerTypes[type];
-}
-
-cmCacheManager::CacheEntryType cmCacheManager::StringToType(const char* s)
-{
-  int i = 0;
-  while(cmCacheManagerTypes[i])
-    {
-    if(strcmp(s, cmCacheManagerTypes[i]) == 0)
-      {
-      return static_cast<CacheEntryType>(i);
-      }
-    ++i;
-    }
-  return STRING;
-}
-
-bool cmCacheManager::IsType(const char* s)
-{
-  for(int i=0; cmCacheManagerTypes[i]; ++i)
-    {
-    if(strcmp(s, cmCacheManagerTypes[i]) == 0)
-      {
-      return true;
-      }
-    }
-  return false;
-}
-
 bool cmCacheManager::LoadCache(const std::string& path)
 {
   std::set<std::string> emptySet;
@@ -122,7 +76,7 @@ static bool ParseEntryWithoutType(const std::string& entry,
 bool cmCacheManager::ParseEntry(const std::string& entry,
                                 std::string& var,
                                 std::string& value,
-                                CacheEntryType& type)
+                                cmState::CacheEntryType& type)
 {
   // input line is:         key:type=value
   static cmsys::RegularExpression reg(
@@ -134,14 +88,14 @@ bool cmCacheManager::ParseEntry(const std::string& entry,
   if(regQuoted.find(entry))
     {
     var = regQuoted.match(1);
-    type = cmCacheManager::StringToType(regQuoted.match(2).c_str());
+    type = cmState::StringToCacheEntryType(regQuoted.match(2).c_str());
     value = regQuoted.match(3);
     flag = true;
     }
   else if (reg.find(entry))
     {
     var = reg.match(1);
-    type = cmCacheManager::StringToType(reg.match(2).c_str());
+    type = cmState::StringToCacheEntryType(reg.match(2).c_str());
     value = reg.match(3);
     flag = true;
     }
@@ -250,15 +204,15 @@ bool cmCacheManager::LoadCache(const std::string& path,
         // If the entry is not internal to the cache being loaded
         // or if it is in the list of internal entries to be
         // imported, load it.
-        if ( internal || (e.Type != INTERNAL) ||
+        if ( internal || (e.Type != cmState::INTERNAL) ||
              (includes.find(entryKey) != includes.end()) )
           {
           // If we are loading the cache from another project,
           // make all loaded entries internal so that it is
           // not visible in the gui
           if (!internal)
             {
-            e.Type = INTERNAL;
+            e.Type = cmState::INTERNAL;
             helpString = "DO NOT EDIT, ";
             helpString += entryKey;
             helpString += " loaded from external file.  "
@@ -306,10 +260,10 @@ bool cmCacheManager::LoadCache(const std::string& path,
     // Set as version 0.0
     this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", "0",
                         "Minor version of cmake used to create the "
-                        "current loaded cache", cmCacheManager::INTERNAL);
+                        "current loaded cache", cmState::INTERNAL);
     this->AddCacheEntry("CMAKE_CACHE_MAJOR_VERSION", "0",
                         "Major version of cmake used to create the "
-                        "current loaded cache", cmCacheManager::INTERNAL);
+                        "current loaded cache", cmState::INTERNAL);
 
     }
   // check to make sure the cache directory has not
@@ -351,7 +305,7 @@ bool cmCacheManager::ReadPropertyEntry(std::string const& entryKey,
                                        CacheEntry& e)
 {
   // All property entries are internal.
-  if(e.Type != cmCacheManager::INTERNAL)
+  if(e.Type != cmState::INTERNAL)
     {
     return false;
     }
@@ -370,7 +324,7 @@ bool cmCacheManager::ReadPropertyEntry(std::string const& entryKey,
         // Create an entry and store the property.
         CacheEntry& ne = this->Cache[key];
         ne.Properties.SetCMakeInstance(this->CMakeInstance);
-        ne.Type = cmCacheManager::UNINITIALIZED;
+        ne.Type = cmState::UNINITIALIZED;
         ne.SetProperty(*p, e.Value.c_str());
         }
       else
@@ -427,15 +381,15 @@ bool cmCacheManager::SaveCache(const std::string& path)
   sprintf(temp, "%d", cmVersion::GetMinorVersion());
   this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", temp,
                       "Minor version of cmake used to create the "
-                      "current loaded cache", cmCacheManager::INTERNAL);
+                      "current loaded cache", cmState::INTERNAL);
   sprintf(temp, "%d", cmVersion::GetMajorVersion());
   this->AddCacheEntry("CMAKE_CACHE_MAJOR_VERSION", temp,
                       "Major version of cmake used to create the "
-                      "current loaded cache", cmCacheManager::INTERNAL);
+                      "current loaded cache", cmState::INTERNAL);
   sprintf(temp, "%d", cmVersion::GetPatchVersion());
   this->AddCacheEntry("CMAKE_CACHE_PATCH_VERSION", temp,
                       "Patch version of cmake used to create the "
-                      "current loaded cache", cmCacheManager::INTERNAL);
+                      "current loaded cache", cmState::INTERNAL);
 
   // Let us store the current working directory so that if somebody
   // Copies it, he will not be surprised
@@ -450,7 +404,7 @@ bool cmCacheManager::SaveCache(const std::string& path)
   cmSystemTools::ConvertToUnixSlashes(currentcwd);
   this->AddCacheEntry("CMAKE_CACHEFILE_DIR", currentcwd.c_str(),
                       "This is the directory where this CMakeCache.txt"
-                      " was created", cmCacheManager::INTERNAL);
+                      " was created", cmState::INTERNAL);
 
   fout << "# This is the CMakeCache file.\n"
        << "# For build in directory: " << currentcwd << "\n";
@@ -484,7 +438,7 @@ bool cmCacheManager::SaveCache(const std::string& path)
          this->Cache.begin(); i != this->Cache.end(); ++i)
     {
     const CacheEntry& ce = (*i).second;
-    CacheEntryType t = ce.Type;
+    cmState::CacheEntryType t = ce.Type;
     if(!ce.Initialized)
       {
       /*
@@ -493,7 +447,7 @@ bool cmCacheManager::SaveCache(const std::string& path)
                            "\" is uninitialized");
       */
       }
-    else if(t != INTERNAL)
+    else if(t != cmState::INTERNAL)
       {
       // Format is key:type=value
       if(const char* help = ce.GetProperty("HELPSTRING"))
@@ -505,7 +459,7 @@ bool cmCacheManager::SaveCache(const std::string& path)
         cmCacheManager::OutputHelpString(fout, "Missing description");
         }
       this->OutputKey(fout, i->first);
-      fout << ":" << cmCacheManagerTypes[t] << "=";
+      fout << ":" << cmState::CacheEntryTypeToString(t) << "=";
       this->OutputValue(fout, ce.Value);
       fout << "\n\n";
       }
@@ -525,17 +479,17 @@ bool cmCacheManager::SaveCache(const std::string& path)
       continue;
       }
 
-    CacheEntryType t = i.GetType();
+    cmState::CacheEntryType t = i.GetType();
     this->WritePropertyEntries(fout, i);
-    if(t == cmCacheManager::INTERNAL)
+    if(t == cmState::INTERNAL)
       {
       // Format is key:type=value
       if(const char* help = i.GetProperty("HELPSTRING"))
         {
         this->OutputHelpString(fout, help);
         }
       this->OutputKey(fout, i.GetName());
-      fout << ":" << cmCacheManagerTypes[t] << "=";
+      fout << ":" << cmState::CacheEntryTypeToString(t) << "=";
       this->OutputValue(fout, i.GetValue());
       fout << "\n";
       }
@@ -677,7 +631,7 @@ void cmCacheManager::PrintCache(std::ostream& out) const
   for(std::map<std::string, CacheEntry>::const_iterator i =
         this->Cache.begin(); i != this->Cache.end(); ++i)
     {
-    if((*i).second.Type != INTERNAL)
+    if((*i).second.Type != cmState::INTERNAL)
       {
       out << (*i).first << " = " << (*i).second.Value
           << std::endl;
@@ -693,7 +647,7 @@ void cmCacheManager::PrintCache(std::ostream& out) const
 void cmCacheManager::AddCacheEntry(const std::string& key,
                                    const char* value,
                                    const char* helpString,
-                                   CacheEntryType type)
+                                   cmState::CacheEntryType type)
 {
   CacheEntry& e = this->Cache[key];
   e.Properties.SetCMakeInstance(this->CMakeInstance);
@@ -708,7 +662,7 @@ void cmCacheManager::AddCacheEntry(const std::string& key,
     }
   e.Type = type;
   // make sure we only use unix style paths
-  if(type == FILEPATH || type == PATH)
+  if(type == cmState::FILEPATH || type == cmState::PATH)
     {
     if(e.Value.find(';') != e.Value.npos)
       {
@@ -789,7 +743,7 @@ cmCacheManager::CacheEntry::GetProperty(const std::string& prop) const
 {
   if(prop == "TYPE")
     {
-    return cmCacheManagerTypes[this->Type];
+    return cmState::CacheEntryTypeToString(this->Type);
     }
   else if(prop == "VALUE")
     {
@@ -806,7 +760,7 @@ void cmCacheManager::CacheEntry::SetProperty(const std::string& prop,
 {
   if(prop == "TYPE")
     {
-    this->Type = cmCacheManager::StringToType(value? value : "STRING");
+    this->Type = cmState::StringToCacheEntryType(value? value : "STRING");
     }
   else if(prop == "VALUE")
     {
@@ -825,7 +779,7 @@ void cmCacheManager::CacheEntry::AppendProperty(const std::string& prop,
 {
   if(prop == "TYPE")
     {
-    this->Type = cmCacheManager::StringToType(value? value : "STRING");
+    this->Type = cmState::StringToCacheEntryType(value? value : "STRING");
     }
   else if(prop == "VALUE")
     {