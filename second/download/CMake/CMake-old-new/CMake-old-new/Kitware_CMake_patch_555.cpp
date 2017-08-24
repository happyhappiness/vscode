@@ -267,19 +267,17 @@ void cmOrderLinkDirectories::PrepareLinkTargets()
   for(std::vector<cmStdString>::iterator i = originalLinkItems.begin();
       i != originalLinkItems.end(); ++i)
     {
-    // separate the library name from libfoo.a or foo.a
-    if(this->ExtractStaticLibraryName.find(*i))
-      {
-#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
-      fprintf(stderr, "static regex matched [%s] [%s] [%s]\n",
-              this->ExtractStaticLibraryName.match(1).c_str(),
-              this->ExtractStaticLibraryName.match(2).c_str(),
-              this->ExtractStaticLibraryName.match(3).c_str());
-#endif
-      this->SetCurrentLinkType(LinkStatic);
-      this->LinkItems.push_back(this->ExtractStaticLibraryName.match(2));
-      }
-    else if(this->ExtractSharedLibraryName.find(*i))
+    // Parse out the prefix, base, and suffix components of the
+    // library name.  If the name matches that of a shared or static
+    // library then set the link type accordingly.
+    //
+    // Search for shared library names first because some platforms
+    // have shared libraries with names that match the static library
+    // pattern.  For example cygwin and msys use the convention
+    // libfoo.dll.a for import libraries and libfoo.a for static
+    // libraries.  On AIX a library with the name libfoo.a can be
+    // shared!
+    if(this->ExtractSharedLibraryName.find(*i))
       {
 #ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
       fprintf(stderr, "shared regex matched [%s] [%s] [%s]\n",
@@ -290,6 +288,17 @@ void cmOrderLinkDirectories::PrepareLinkTargets()
       this->SetCurrentLinkType(LinkShared);
       this->LinkItems.push_back(this->ExtractSharedLibraryName.match(2));
       }
+    else if(this->ExtractStaticLibraryName.find(*i))
+      {
+#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
+      fprintf(stderr, "static regex matched [%s] [%s] [%s]\n",
+              this->ExtractStaticLibraryName.match(1).c_str(),
+              this->ExtractStaticLibraryName.match(2).c_str(),
+              this->ExtractStaticLibraryName.match(3).c_str());
+#endif
+      this->SetCurrentLinkType(LinkStatic);
+      this->LinkItems.push_back(this->ExtractStaticLibraryName.match(2));
+      }
     else if(this->ExtractAnyLibraryName.find(*i))
       {
 #ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG