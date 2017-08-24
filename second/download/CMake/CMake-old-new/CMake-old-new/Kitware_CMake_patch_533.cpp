@@ -919,13 +919,22 @@ ::ConvertToMakeTarget(const char* tgt)
 std::string&
 cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
 {
-  if ( m_Makefile->IsOn("CMAKE_MANGLE_OBJECT_FILE_NAMES") )
+  // Look for an existing mapped name for this object file.
+  std::map<cmStdString,cmStdString>::iterator it =
+    m_UniqueObjectNamesMap.find(sin);
+
+  // If no entry exists create one.
+  if(it == m_UniqueObjectNamesMap.end())
     {
-    std::map<cmStdString,cmStdString>::iterator it = 
-      m_UniqueObjectNamesMap.find(sin);
-    if ( it == m_UniqueObjectNamesMap.end() )
+    // Start with the original name.
+    std::string ssin = sin;
+
+    // Avoid relative paths that go up the tree.
+    cmSystemTools::ReplaceString(ssin, "../", "__/");
+
+    // Mangle the name if necessary.
+    if(m_Makefile->IsOn("CMAKE_MANGLE_OBJECT_FILE_NAMES"))
       {
-      std::string ssin = sin;
       bool done;
       int cc = 0;
       char rpstr[100];
@@ -936,8 +945,8 @@ cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
         {
         done = true;
         for ( it = m_UniqueObjectNamesMap.begin();
-          it != m_UniqueObjectNamesMap.end();
-          ++ it )
+              it != m_UniqueObjectNamesMap.end();
+              ++ it )
           {
           if ( it->second == ssin )
             {
@@ -953,14 +962,15 @@ cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
         sprintf(rpstr, "_p%d_", cc++);
         }
       while ( !done );
-      m_UniqueObjectNamesMap[sin] = ssin;
       }
+
+    // Insert the newly mapped object file name.
+    std::map<cmStdString, cmStdString>::value_type e(sin, ssin);
+    it = m_UniqueObjectNamesMap.insert(e).first;
     }
-  else
-    {
-    m_UniqueObjectNamesMap[sin] = sin;
-    }
-  return m_UniqueObjectNamesMap[sin];
+
+  // Return the map entry.
+  return it->second;
 }
 
 //----------------------------------------------------------------------------
@@ -1486,32 +1496,40 @@ ::GetObjectFileName(cmTarget& target,
                     const cmSourceFile& source,
                     std::string* nameWithoutTargetDir)
 {
-  // If the full path to the source file includes this directory,
-  // we want to use the relative path for the filename of the
-  // object file.  Otherwise, we will use just the filename
-  // portion.
-  std::string objectName;
-  if((cmSystemTools::GetFilenamePath(
-        source.GetFullPath()).find(
-          m_Makefile->GetCurrentDirectory()) == 0)
-     || (cmSystemTools::GetFilenamePath(
-           source.GetFullPath()).find(
-             m_Makefile->GetStartOutputDirectory()) == 0))
-    {
-    objectName = source.GetSourceName();
+  // If the source file is located below the current binary directory
+  // then use that relative path for the object file name.
+  std::string objectName =
+    cmSystemTools::RelativePath(m_Makefile->GetCurrentOutputDirectory(),
+                                source.GetFullPath().c_str());
+  if(objectName.empty() || objectName[0] == '.')
+    {
+    // If the source file is located below the current source
+    // directory then use that relative path for the object file name.
+    // Otherwise just use the relative path from the current binary
+    // directory.
+    std::string relFromSource =
+      cmSystemTools::RelativePath(m_Makefile->GetCurrentDirectory(),
+                                  source.GetFullPath().c_str());
+    if(!relFromSource.empty() && relFromSource[0] != '.')
+      {
+      objectName = relFromSource;
+      }
     }
-  else
+
+  // Replace the original source file extension with the object file
+  // extension.
+  std::string::size_type dot_pos = objectName.rfind(".");
+  if(dot_pos != std::string::npos)
     {
-    objectName = cmSystemTools::GetFilenameName(source.GetSourceName());
+    objectName = objectName.substr(0, dot_pos);
     }
-
-  // Append the object file extension.
   objectName +=
     m_GlobalGenerator->GetLanguageOutputExtensionFromExtension(
       source.GetSourceExtension().c_str());
 
   // Convert to a safe name.
   objectName = this->CreateSafeUniqueObjectFileName(objectName.c_str());
+
   // Prepend the target directory.
   std::string obj = this->GetTargetDirectory(target);
   obj += "/";