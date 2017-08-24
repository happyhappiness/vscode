@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -23,8 +23,9 @@ cmakewizard::cmakewizard()
   m_ShowAdvanced = false;
 }
 
-  
-void cmakewizard::AskUser(const char* key, cmCacheManager::CacheIterator& iter)
+
+void cmakewizard::AskUser(const char* key,
+  cmCacheManager::CacheIterator& iter)
 {
   printf("Variable Name: %s\n", key);
   const char* helpstring = iter.GetProperty("HELPSTRING");
@@ -34,7 +35,7 @@ void cmakewizard::AskUser(const char* key, cmCacheManager::CacheIterator& iter)
   char buffer[4096];
   buffer[0] = 0;
   fgets(buffer, sizeof(buffer)-1, stdin);
-          
+
   if(strlen(buffer) > 0)
     {
     std::string sbuffer = buffer;
@@ -44,7 +45,7 @@ void cmakewizard::AskUser(const char* key, cmCacheManager::CacheIterator& iter)
       {
       value = sbuffer.substr(0, pos+1);
       }
-    
+
     if ( value.size() > 0 )
       {
       if(iter.GetType() == cmCacheManager::PATH ||
@@ -67,7 +68,7 @@ void cmakewizard::AskUser(const char* key, cmCacheManager::CacheIterator& iter)
 
 bool cmakewizard::AskAdvanced()
 {
-  printf("Would you like to see advanced options? [No]:");  
+  printf("Would you like to see advanced options? [No]:");
   char buffer[4096];
   buffer[0] = 0;
   fgets(buffer, sizeof(buffer)-1, stdin);
@@ -105,7 +106,8 @@ int cmakewizard::RunWizard(std::vector<std::string> const& args)
     {
     asked = false;
     // run cmake
-    this->ShowMessage("Please wait while cmake processes CMakeLists.txt files....\n");
+    this->ShowMessage(
+      "Please wait while cmake processes CMakeLists.txt files....\n");
 
     make.Configure();
     this->ShowMessage("\n");
@@ -115,9 +117,9 @@ int cmakewizard::RunWizard(std::vector<std::string> const& args)
     cmCacheManager::CacheIterator i = cachem->NewIterator();
     // iterate over all entries in the cache
     for(;!i.IsAtEnd(); i.Next())
-      { 
+      {
       std::string key = i.GetName();
-      if( i.GetType() == cmCacheManager::INTERNAL || 
+      if( i.GetType() == cmCacheManager::INTERNAL ||
           i.GetType() == cmCacheManager::STATIC ||
           i.GetType() == cmCacheManager::UNINITIALIZED )
         {
@@ -136,7 +138,7 @@ int cmakewizard::RunWizard(std::vector<std::string> const& args)
           }
         }
       else
-        {    
+        {
         if(m_ShowAdvanced || !i.GetPropertyAsBool("ADVANCED"))
           {
           this->AskUser(key.c_str(), i);