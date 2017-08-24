@@ -1062,75 +1062,6 @@ ::ConvertToMakeTarget(const char* tgt)
 }
 
 //----------------------------------------------------------------------------
-std::string&
-cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
-{
-  // Look for an existing mapped name for this object file.
-  std::map<cmStdString,cmStdString>::iterator it =
-    this->UniqueObjectNamesMap.find(sin);
-
-  // If no entry exists create one.
-  if(it == this->UniqueObjectNamesMap.end())
-    {
-    // Start with the original name.
-    std::string ssin = sin;
-
-    // Avoid full paths by removing leading slashes.
-    std::string::size_type pos = 0;
-    for(;pos < ssin.size() && ssin[pos] == '/'; ++pos);
-    ssin = ssin.substr(pos);
-
-    // Avoid full paths by removing colons.
-    cmSystemTools::ReplaceString(ssin, ":", "_");
-
-    // Avoid relative paths that go up the tree.
-    cmSystemTools::ReplaceString(ssin, "../", "__/");
-
-    // Avoid spaces.
-    cmSystemTools::ReplaceString(ssin, " ", "_");
-
-    // Mangle the name if necessary.
-    if(this->Makefile->IsOn("CMAKE_MANGLE_OBJECT_FILE_NAMES"))
-      {
-      bool done;
-      int cc = 0;
-      char rpstr[100];
-      sprintf(rpstr, "_p_");
-      cmSystemTools::ReplaceString(ssin, "+", rpstr);
-      std::string sssin = sin;
-      do
-        {
-        done = true;
-        for ( it = this->UniqueObjectNamesMap.begin();
-              it != this->UniqueObjectNamesMap.end();
-              ++ it )
-          {
-          if ( it->second == ssin )
-            {
-            done = false;
-            }
-          }
-        if ( done )
-          {
-          break;
-          }
-        sssin = ssin;
-        cmSystemTools::ReplaceString(ssin, "_p_", rpstr);
-        sprintf(rpstr, "_p%d_", cc++);
-        }
-      while ( !done );
-      }
-
-    // Insert the newly mapped object file name.
-    std::map<cmStdString, cmStdString>::value_type e(sin, ssin);
-    it = this->UniqueObjectNamesMap.insert(e).first;
-    }
-
-  // Return the map entry.
-  return it->second;
-}
-
-//----------------------------------------------------------------------------
 std::string
 cmLocalUnixMakefileGenerator3
 ::CreateMakeVariable(const char* sin, const char* s2in)
@@ -1707,50 +1638,13 @@ ::GetObjectFileName(cmTarget& target,
                     const cmSourceFile& source,
                     std::string* nameWithoutTargetDir)
 {
-  // If the source file is located below the current binary directory
-  // then use that relative path for the object file name.
-  std::string objectName = this->Convert(source.GetFullPath().c_str(),
-                                         START_OUTPUT);
-  if(cmSystemTools::FileIsFullPath(objectName.c_str()) ||
-     objectName.empty() || objectName[0] == '.')
-    {
-    // If the source file is located below the current source
-    // directory then use that relative path for the object file name.
-    // Otherwise just use the relative path from the current binary
-    // directory.
-    std::string relFromSource = this->Convert(source.GetFullPath().c_str(),
-                                              START);
-    if(!cmSystemTools::FileIsFullPath(relFromSource.c_str()) &&
-       !relFromSource.empty() && relFromSource[0] != '.')
-      {
-      objectName = relFromSource;
-      }
-    }
-
-  // Replace the original source file extension with the object file
-  // extension.
-  std::string::size_type dot_pos = objectName.rfind(".");
-  if(dot_pos != std::string::npos)
-    {
-    objectName = objectName.substr(0, dot_pos);
-    }
-  if ( source.GetPropertyAsBool("KEEP_EXTENSION") )
-    {
-    if ( !source.GetSourceExtension().empty() )
-      {
-      objectName += "." + source.GetSourceExtension();
-      }
-    }
-  else
+  // Get the object file name independent of target.
+  std::string objectName = this->GetObjectFileNameWithoutTarget(source);
+  if(nameWithoutTargetDir)
     {
-    objectName +=
-      this->GlobalGenerator->GetLanguageOutputExtensionFromExtension(
-        source.GetSourceExtension().c_str());
+    *nameWithoutTargetDir = objectName;
     }
 
-  // Convert to a safe name.
-  objectName = this->CreateSafeUniqueObjectFileName(objectName.c_str());
-
   // Prepend the target directory.
   std::string obj;
   const char* fileTargetDirectory = 
@@ -1788,10 +1682,6 @@ ::GetObjectFileName(cmTarget& target,
     }
   obj += "/";
   obj += objectName;
-  if(nameWithoutTargetDir)
-    {
-    *nameWithoutTargetDir = objectName;
-    }
   return obj;
 }
 