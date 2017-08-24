@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -28,7 +28,7 @@
 # include <windows.h>
 #endif // _WIN32
 
-const char* cmCacheManagerTypes[] = 
+const char* cmCacheManagerTypes[] =
 { "BOOL",
   "PATH",
   "FILEPATH",
@@ -80,14 +80,16 @@ bool cmCacheManager::LoadCache(const char* path,
   return this->LoadCache(path, internal, emptySet, emptySet);
 }
 
-bool cmCacheManager::ParseEntry(const char* entry, 
+bool cmCacheManager::ParseEntry(const char* entry,
                                 std::string& var,
                                 std::string& value)
 {
   // input line is:         key:type=value
-  static cmsys::RegularExpression reg("^([^:]*)=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
+  static cmsys::RegularExpression reg(
+    "^([^:]*)=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
   // input line is:         "key":type=value
-  static cmsys::RegularExpression regQuoted("^\"([^\"]*)\"=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
+  static cmsys::RegularExpression regQuoted(
+    "^\"([^\"]*)\"=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
   bool flag = false;
   if(regQuoted.find(entry))
     {
@@ -104,27 +106,29 @@ bool cmCacheManager::ParseEntry(const char* entry,
 
   // if value is enclosed in single quotes ('foo') then remove them
   // it is used to enclose trailing space or tab
-  if (flag && 
+  if (flag &&
       value.size() >= 2 &&
-      value[0] == '\'' && 
-      value[value.size() - 1] == '\'') 
+      value[0] == '\'' &&
+      value[value.size() - 1] == '\'')
     {
-    value = value.substr(1, 
+    value = value.substr(1,
                          value.size() - 2);
     }
 
   return flag;
 }
 
-bool cmCacheManager::ParseEntry(const char* entry, 
+bool cmCacheManager::ParseEntry(const char* entry,
                                 std::string& var,
                                 std::string& value,
                                 CacheEntryType& type)
 {
   // input line is:         key:type=value
-  static cmsys::RegularExpression reg("^([^:]*):([^=]*)=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
+  static cmsys::RegularExpression reg(
+    "^([^:]*):([^=]*)=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
   // input line is:         "key":type=value
-  static cmsys::RegularExpression regQuoted("^\"([^\"]*)\":([^=]*)=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
+  static cmsys::RegularExpression regQuoted(
+    "^\"([^\"]*)\":([^=]*)=(.*[^\r\t ]|[\r\t ]*)[\r\t ]*$");
   bool flag = false;
   if(regQuoted.find(entry))
     {
@@ -143,12 +147,12 @@ bool cmCacheManager::ParseEntry(const char* entry,
 
   // if value is enclosed in single quotes ('foo') then remove them
   // it is used to enclose trailing space or tab
-  if (flag && 
+  if (flag &&
       value.size() >= 2 &&
-      value[0] == '\'' && 
-      value[value.size() - 1] == '\'') 
+      value[0] == '\'' &&
+      value[value.size() - 1] == '\'')
     {
-    value = value.substr(1, 
+    value = value.substr(1,
                          value.size() - 2);
     }
 
@@ -186,7 +190,7 @@ bool cmCacheManager::LoadCache(const char* path,
     this->CleanCMakeFiles(path);
     return false;
     }
-  
+
   std::ifstream fin(cacheFile.c_str());
   if(!fin)
     {
@@ -232,7 +236,7 @@ bool cmCacheManager::LoadCache(const char* path,
         // If the entry is not internal to the cache being loaded
         // or if it is in the list of internal entries to be
         // imported, load it.
-        if ( internal || (e.m_Type != INTERNAL) || 
+        if ( internal || (e.m_Type != INTERNAL) ||
              (includes.find(entryKey) != includes.end()) )
           {
           // If we are loading the cache from another project,
@@ -250,12 +254,14 @@ bool cmCacheManager::LoadCache(const char* path,
             }
           if ( e.m_Type == cmCacheManager::INTERNAL &&
                (entryKey.size() > strlen("-ADVANCED")) &&
-               strcmp(entryKey.c_str() + (entryKey.size() - strlen("-ADVANCED")),
-                      "-ADVANCED") == 0 )
+               strcmp(entryKey.c_str() + (entryKey.size() -
+                   strlen("-ADVANCED")), "-ADVANCED") == 0 )
             {
             std::string value = e.m_Value;
-            std::string akey = entryKey.substr(0, (entryKey.size() - strlen("-ADVANCED")));
-            cmCacheManager::CacheIterator it = this->GetCacheIterator(akey.c_str());
+            std::string akey
+              = entryKey.substr(0, (entryKey.size() - strlen("-ADVANCED")));
+            cmCacheManager::CacheIterator it
+              = this->GetCacheIterator(akey.c_str());
             if ( it.IsAtEnd() )
               {
               e.m_Type = cmCacheManager::UNINITIALIZED;
@@ -269,12 +275,14 @@ bool cmCacheManager::LoadCache(const char* path,
             }
           else if ( e.m_Type == cmCacheManager::INTERNAL &&
                     (entryKey.size() > strlen("-MODIFIED")) &&
-                    strcmp(entryKey.c_str() + (entryKey.size() - strlen("-MODIFIED")),
-                           "-MODIFIED") == 0 )
+                    strcmp(entryKey.c_str() + (entryKey.size() -
+                        strlen("-MODIFIED")), "-MODIFIED") == 0 )
             {
             std::string value = e.m_Value;
-            std::string akey = entryKey.substr(0, (entryKey.size() - strlen("-MODIFIED")));
-            cmCacheManager::CacheIterator it = this->GetCacheIterator(akey.c_str());
+            std::string akey
+              = entryKey.substr(0, (entryKey.size() - strlen("-MODIFIED")));
+            cmCacheManager::CacheIterator it
+              = this->GetCacheIterator(akey.c_str());
             if ( it.IsAtEnd() )
               {
               e.m_Type = cmCacheManager::UNINITIALIZED;
@@ -310,7 +318,7 @@ bool cmCacheManager::LoadCache(const char* path,
     this->AddCacheEntry("CMAKE_CACHE_MAJOR_VERSION", "0",
                         "Major version of cmake used to create the "
                         "current loaded cache", cmCacheManager::INTERNAL);
-    
+
     }
   // check to make sure the cache directory has not
   // been moved
@@ -322,42 +330,42 @@ bool cmCacheManager::LoadCache(const char* path,
     currentcwd += "/CMakeCache.txt";
     oldcwd += "/CMakeCache.txt";
     if(!cmSystemTools::SameFile(oldcwd.c_str(), currentcwd.c_str()))
-      { 
-      std::string message = 
+      {
+      std::string message =
         std::string("The current CMakeCache.txt directory ") +
-        currentcwd + std::string(" is different than the directory ") + 
+        currentcwd + std::string(" is different than the directory ") +
         std::string(this->GetCacheValue("CMAKE_CACHEFILE_DIR")) +
         std::string(" where CMackeCache.txt was created. This may result "
                     "in binaries being created in the wrong place. If you "
                     "are not sure, reedit the CMakeCache.txt");
-      cmSystemTools::Error(message.c_str());   
+      cmSystemTools::Error(message.c_str());
       }
     }
   return true;
 }
 
-bool cmCacheManager::SaveCache(cmMakefile* mf) 
+bool cmCacheManager::SaveCache(cmMakefile* mf)
 {
   return this->SaveCache(mf->GetHomeOutputDirectory());
 }
 
 
-bool cmCacheManager::SaveCache(const char* path) 
+bool cmCacheManager::SaveCache(const char* path)
 {
   std::string cacheFile = path;
   cacheFile += "/CMakeCache.txt";
   std::string tempFile = cacheFile;
   tempFile += ".tmp";
   std::ofstream fout(tempFile.c_str());
   if(!fout)
-    {  
-    cmSystemTools::Error("Unable to open cache file for save. ", 
+    {
+    cmSystemTools::Error("Unable to open cache file for save. ",
                          cacheFile.c_str());
     cmSystemTools::ReportLastSystemError("");
     return false;
     }
   // before writing the cache, update the version numbers
-  // to the 
+  // to the
   char temp[1024];
   sprintf(temp, "%d", cmMakefile::GetMinorVersion());
   this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", temp,
@@ -368,7 +376,8 @@ bool cmCacheManager::SaveCache(const char* path)
                       "Major version of cmake used to create the "
                       "current loaded cache", cmCacheManager::INTERNAL);
 
-  this->AddCacheEntry("CMAKE_CACHE_RELEASE_VERSION", cmMakefile::GetReleaseVersion(),
+  this->AddCacheEntry("CMAKE_CACHE_RELEASE_VERSION",
+                      cmMakefile::GetReleaseVersion(),
                       "Major version of cmake used to create the "
                       "current loaded cache", cmCacheManager::INTERNAL);
 
@@ -387,19 +396,25 @@ bool cmCacheManager::SaveCache(const char* path)
 
   fout << "# This is the CMakeCache file.\n"
        << "# For build in directory: " << currentcwd << "\n";
-  cmCacheManager::CacheEntry* cmakeCacheEntry = this->GetCacheEntry("CMAKE_COMMAND");
+  cmCacheManager::CacheEntry* cmakeCacheEntry
+    = this->GetCacheEntry("CMAKE_COMMAND");
   if ( cmakeCacheEntry )
     {
-    fout << "# It was generated by CMake: " << cmakeCacheEntry->m_Value << std::endl;
+    fout << "# It was generated by CMake: " << cmakeCacheEntry->m_Value
+      << std::endl;
     }
 
-  fout << "# You can edit this file to change values found and used by cmake.\n"
-       << "# If you do not want to change any of the values, simply exit the editor.\n"
-       << "# If you do want to change a value, simply edit, save, and exit the editor.\n"
+  fout << "# You can edit this file to change values found and used by cmake."
+       << std::endl
+       << "# If you do not want to change any of the values, simply exit the "
+       "editor." << std::endl
+       << "# If you do want to change a value, simply edit, save, and exit "
+       "the editor." << std::endl
        << "# The syntax for the file is as follows:\n"
        << "# KEY:TYPE=VALUE\n"
        << "# KEY is the name of a variable in the cache.\n"
-       << "# TYPE is a hint to GUI's for the type of VALUE, DO NOT EDIT TYPE!.\n"
+       << "# TYPE is a hint to GUI's for the type of VALUE, DO NOT EDIT "
+       "TYPE!." << std::endl
        << "# VALUE is the current value for the KEY.\n\n";
 
   fout << "########################\n";
@@ -410,20 +425,20 @@ bool cmCacheManager::SaveCache(const char* path)
   for( std::map<cmStdString, CacheEntry>::const_iterator i = m_Cache.begin();
        i != m_Cache.end(); ++i)
     {
-    const CacheEntry& ce = (*i).second; 
+    const CacheEntry& ce = (*i).second;
     CacheEntryType t = ce.m_Type;
     if(t == cmCacheManager::UNINITIALIZED || !ce.m_Initialized)
       {
       /*
         // This should be added in, but is not for now.
-      cmSystemTools::Error("Cache entry \"", (*i).first.c_str(), 
+      cmSystemTools::Error("Cache entry \"", (*i).first.c_str(),
                            "\" is uninitialized");
       */
       }
     else if(t != INTERNAL)
       {
       // Format is key:type=value
-      std::map<cmStdString,cmStdString>::const_iterator it = 
+      std::map<cmStdString,cmStdString>::const_iterator it =
         ce.m_Properties.find("HELPSTRING");
       if ( it == ce.m_Properties.end() )
         {
@@ -434,7 +449,7 @@ bool cmCacheManager::SaveCache(const char* path)
         cmCacheManager::OutputHelpString(fout, it->second);
         }
       std::string key;
-      // support : in key name by double quoting 
+      // support : in key name by double quoting
       if((*i).first.find(':') != std::string::npos ||
         (*i).first.find("//") == 0)
         {
@@ -450,7 +465,7 @@ bool cmCacheManager::SaveCache(const char* path)
            << cmCacheManagerTypes[t] << "=";
       // if value has trailing space or tab, enclose it in single quotes
       if (ce.m_Value.size() &&
-          (ce.m_Value[ce.m_Value.size() - 1] == ' ' || 
+          (ce.m_Value[ce.m_Value.size() - 1] == ' ' ||
            ce.m_Value[ce.m_Value.size() - 1] == '\t'))
         {
         fout << '\'' << ce.m_Value << '\'';
@@ -491,7 +506,7 @@ bool cmCacheManager::SaveCache(const char* path)
       helpstring += i.GetName();
       rkey += "-ADVANCED";
       cmCacheManager::OutputHelpString(fout, helpstring.c_str());
-      // support : in key name by double quoting 
+      // support : in key name by double quoting
       if(rkey.find(':') != std::string::npos ||
          rkey.find("//") == 0)
         {
@@ -519,7 +534,7 @@ bool cmCacheManager::SaveCache(const char* path)
       helpstring += i.GetName();
       rkey += "-MODIFIED";
       cmCacheManager::OutputHelpString(fout, helpstring.c_str());
-      // support : in key name by double quoting 
+      // support : in key name by double quoting
       if(rkey.find(':') != std::string::npos ||
          rkey.find("//") == 0)
         {
@@ -550,7 +565,7 @@ bool cmCacheManager::SaveCache(const char* path)
         helpstring = "";
         }
       cmCacheManager::OutputHelpString(fout, helpstring.c_str());
-      // support : in key name by double quoting 
+      // support : in key name by double quoting
       if(rkey.find(':') != std::string::npos ||
          rkey.find("//") == 0)
         {
@@ -567,7 +582,7 @@ bool cmCacheManager::SaveCache(const char* path)
       // if value has trailing space or tab, enclose it in single quotes
       std::string value = i.GetValue();
       if (value.size() &&
-          (value[value.size() - 1] == ' ' || 
+          (value[value.size() - 1] == ' ' ||
            value[value.size() - 1] == '\t'))
         {
         fout << '\'' << value << '\'';
@@ -576,7 +591,7 @@ bool cmCacheManager::SaveCache(const char* path)
         {
         fout << value;
         }
-      fout << "\n";      
+      fout << "\n";
       }
     }
   fout << "\n";
@@ -591,15 +606,16 @@ bool cmCacheManager::SaveCache(const char* path)
   std::ofstream checkCache(checkCacheFile.c_str());
   if(!checkCache)
     {
-    cmSystemTools::Error("Unable to open check cache file for write. ", 
+    cmSystemTools::Error("Unable to open check cache file for write. ",
                          checkCacheFile.c_str());
     return false;
     }
-  checkCache << "# This file is generated by cmake for dependency checking of the CMakeCache.txt file\n";
+  checkCache << "# This file is generated by cmake for dependency checking "
+    "of the CMakeCache.txt file\n";
   return true;
 }
 
-bool cmCacheManager::DeleteCache(const char* path) 
+bool cmCacheManager::DeleteCache(const char* path)
 {
   std::string cacheFile = path;
   cmSystemTools::ConvertToUnixSlashes(cacheFile);
@@ -611,7 +627,9 @@ bool cmCacheManager::DeleteCache(const char* path)
   cmsys::Directory dir;
   cmakeFiles += "/CMakeFiles";
   dir.Load(cmakeFiles.c_str());
-  for (unsigned long fileNum = 0; fileNum <  dir.GetNumberOfFiles(); ++fileNum)
+  for (unsigned long fileNum = 0;
+    fileNum <  dir.GetNumberOfFiles();
+    ++fileNum)
     {
     if(!cmSystemTools::
        FileIsDirectory(dir.GetFile(fileNum)))
@@ -625,7 +643,7 @@ bool cmCacheManager::DeleteCache(const char* path)
   return true;
 }
 
-void cmCacheManager::OutputHelpString(std::ofstream& fout, 
+void cmCacheManager::OutputHelpString(std::ofstream& fout,
                                       const std::string& helpString)
 {
   std::string::size_type end = helpString.size();
@@ -683,7 +701,8 @@ cmCacheManager::CacheEntry *cmCacheManager::GetCacheEntry(const char* key)
   return 0;
 }
 
-cmCacheManager::CacheIterator cmCacheManager::GetCacheIterator(const char *key)
+cmCacheManager::CacheIterator cmCacheManager::GetCacheIterator(
+  const char *key)
 {
   return CacheIterator(*this, key);
 }
@@ -709,17 +728,19 @@ void cmCacheManager::PrintCache(std::ostream& out) const
     {
     if((*i).second.m_Type != INTERNAL)
       {
-      out << (*i).first.c_str() << " = " << (*i).second.m_Value.c_str() << std::endl;
+      out << (*i).first.c_str() << " = " << (*i).second.m_Value.c_str()
+        << std::endl;
       }
     }
   out << "\n\n";
-  out << "To change values in the CMakeCache, \nedit CMakeCache.txt in your output directory.\n";
+  out << "To change values in the CMakeCache, "
+    << std::endl << "edit CMakeCache.txt in your output directory.\n";
   out << "=================================================" << std::endl;
 }
 
 
-void cmCacheManager::AddCacheEntry(const char* key, 
-                                   const char* value, 
+void cmCacheManager::AddCacheEntry(const char* key,
+                                   const char* value,
                                    const char* helpString,
                                    CacheEntryType type)
 {
@@ -729,7 +750,7 @@ void cmCacheManager::AddCacheEntry(const char* key,
     e.m_Value = value;
     e.m_Initialized = true;
     }
-  else 
+  else
     {
     e.m_Value = "";
     }
@@ -743,14 +764,15 @@ void cmCacheManager::AddCacheEntry(const char* key,
     {
     e.m_Properties["HELPSTRING"] = helpString;
     }
-  else 
+  else
     {
-    e.m_Properties["HELPSTRING"] = "(This variable does not exists and should not be used)";
+    e.m_Properties["HELPSTRING"]
+      = "(This variable does not exists and should not be used)";
     }
   m_Cache[key] = e;
 }
 
-void cmCacheManager::AddCacheEntry(const char* key, bool v, 
+void cmCacheManager::AddCacheEntry(const char* key, bool v,
                                    const char* helpString)
 {
   if(v)
@@ -768,9 +790,9 @@ bool cmCacheManager::CacheIterator::IsAtEnd() const
   return m_Position == m_Container.m_Cache.end();
 }
 
-void cmCacheManager::CacheIterator::Begin() 
+void cmCacheManager::CacheIterator::Begin()
 {
-  m_Position = m_Container.m_Cache.begin(); 
+  m_Position = m_Container.m_Cache.begin();
 }
 
 bool cmCacheManager::CacheIterator::Find(const char* key)
@@ -779,11 +801,11 @@ bool cmCacheManager::CacheIterator::Find(const char* key)
   return !this->IsAtEnd();
 }
 
-void cmCacheManager::CacheIterator::Next() 
+void cmCacheManager::CacheIterator::Next()
 {
   if (!this->IsAtEnd())
     {
-    ++m_Position; 
+    ++m_Position;
     }
 }
 
@@ -805,7 +827,8 @@ void cmCacheManager::CacheIterator::SetValue(const char* value)
     }
 }
 
-const char* cmCacheManager::CacheIterator::GetProperty(const char* property) const
+const char* cmCacheManager::CacheIterator::GetProperty(
+  const char* property) const
 {
   // make sure it is not at the end
   if (this->IsAtEnd())
@@ -815,12 +838,12 @@ const char* cmCacheManager::CacheIterator::GetProperty(const char* property) con
 
   if ( !strcmp(property, "TYPE") || !strcmp(property, "VALUE") )
     {
-    cmSystemTools::Error("Property \"", property, 
+    cmSystemTools::Error("Property \"", property,
                          "\" cannot be accessed through the GetProperty()");
     return 0;
     }
   const CacheEntry* ent = &this->GetEntry();
-  std::map<cmStdString,cmStdString>::const_iterator it = 
+  std::map<cmStdString,cmStdString>::const_iterator it =
     ent->m_Properties.find(property);
   if ( it == ent->m_Properties.end() )
     {
@@ -829,7 +852,7 @@ const char* cmCacheManager::CacheIterator::GetProperty(const char* property) con
   return it->second.c_str();
 }
 
-void cmCacheManager::CacheIterator::SetProperty(const char* p, const char* v) 
+void cmCacheManager::CacheIterator::SetProperty(const char* p, const char* v)
 {
   // make sure it is not at the end
   if (this->IsAtEnd())
@@ -839,35 +862,36 @@ void cmCacheManager::CacheIterator::SetProperty(const char* p, const char* v)
 
   if ( !strcmp(p, "TYPE") || !strcmp(p, "VALUE") )
     {
-    cmSystemTools::Error("Property \"", p, 
+    cmSystemTools::Error("Property \"", p,
                          "\" cannot be accessed through the SetProperty()");
     return;
     }
   CacheEntry* ent = &this->GetEntry();
   ent->m_Properties[p] = v;
 }
 
-bool cmCacheManager::CacheIterator::GetValueAsBool() const 
-{ 
-  return cmSystemTools::IsOn(this->GetEntry().m_Value.c_str()); 
+bool cmCacheManager::CacheIterator::GetValueAsBool() const
+{
+  return cmSystemTools::IsOn(this->GetEntry().m_Value.c_str());
 }
 
-bool cmCacheManager::CacheIterator::GetPropertyAsBool(const char* property) const
+bool cmCacheManager::CacheIterator::GetPropertyAsBool(
+  const char* property) const
 {
   // make sure it is not at the end
   if (this->IsAtEnd())
     {
     return false;
     }
-  
+
   if ( !strcmp(property, "TYPE") || !strcmp(property, "VALUE") )
     {
-    cmSystemTools::Error("Property \"", property, 
-                         "\" cannot be accessed through the GetPropertyAsBool()");
+    cmSystemTools::Error("Property \"", property,
+      "\" cannot be accessed through the GetPropertyAsBool()");
     return false;
     }
   const CacheEntry* ent = &this->GetEntry();
-  std::map<cmStdString,cmStdString>::const_iterator it = 
+  std::map<cmStdString,cmStdString>::const_iterator it =
     ent->m_Properties.find(property);
   if ( it == ent->m_Properties.end() )
     {
@@ -877,7 +901,7 @@ bool cmCacheManager::CacheIterator::GetPropertyAsBool(const char* property) cons
 }
 
 
-void cmCacheManager::CacheIterator::SetProperty(const char* p, bool v) 
+void cmCacheManager::CacheIterator::SetProperty(const char* p, bool v)
 {
   // make sure it is not at the end
   if (this->IsAtEnd())
@@ -887,7 +911,7 @@ void cmCacheManager::CacheIterator::SetProperty(const char* p, bool v)
 
   if ( !strcmp(p, "TYPE") || !strcmp(p, "VALUE") )
     {
-    cmSystemTools::Error("Property \"", p, 
+    cmSystemTools::Error("Property \"", p,
                          "\" cannot be accessed through the SetProperty()");
     return;
     }
@@ -905,12 +929,12 @@ bool cmCacheManager::CacheIterator::PropertyExists(const char* property) const
 
   if ( !strcmp(property, "TYPE") || !strcmp(property, "VALUE") )
     {
-    cmSystemTools::Error("Property \"", property, 
-                         "\" cannot be accessed through the PropertyExists()");
+    cmSystemTools::Error("Property \"", property,
+      "\" cannot be accessed through the PropertyExists()");
     return false;
     }
   const CacheEntry* ent = &this->GetEntry();
-  std::map<cmStdString,cmStdString>::const_iterator it = 
+  std::map<cmStdString,cmStdString>::const_iterator it =
     ent->m_Properties.find(property);
   if ( it == ent->m_Properties.end() )
     {