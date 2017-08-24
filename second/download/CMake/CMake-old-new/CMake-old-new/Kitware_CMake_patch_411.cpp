@@ -499,7 +499,7 @@ bool cmComputeLinkInformation::Compute()
   if(!this->LinkLanguage)
     {
     cmSystemTools::
-      Error("CMake can not determine linker language for target:",
+      Error("CMake can not determine linker language for target: ",
             this->Target->GetName());
     return false;
     }
@@ -882,7 +882,8 @@ void cmComputeLinkInformation::ComputeItemParserInfo()
     }
 
   // Compute a regex to match link extensions.
-  std::string libext = this->CreateExtensionRegex(this->LinkExtensions);
+  std::string libext = this->CreateExtensionRegex(this->LinkExtensions,
+                                                  LinkUnknown);
 
   // Create regex to remove any library extension.
   std::string reg("(.*)");
@@ -916,7 +917,8 @@ void cmComputeLinkInformation::ComputeItemParserInfo()
   if(!this->StaticLinkExtensions.empty())
     {
     std::string reg_static = reg;
-    reg_static += this->CreateExtensionRegex(this->StaticLinkExtensions);
+    reg_static += this->CreateExtensionRegex(this->StaticLinkExtensions,
+                                             LinkStatic);
 #ifdef CM_COMPUTE_LINK_INFO_DEBUG
   fprintf(stderr, "static regex [%s]\n", reg_static.c_str());
 #endif
@@ -928,7 +930,7 @@ void cmComputeLinkInformation::ComputeItemParserInfo()
     {
     std::string reg_shared = reg;
     this->SharedRegexString =
-      this->CreateExtensionRegex(this->SharedLinkExtensions);
+      this->CreateExtensionRegex(this->SharedLinkExtensions, LinkShared);
     reg_shared += this->SharedRegexString;
 #ifdef CM_COMPUTE_LINK_INFO_DEBUG
   fprintf(stderr, "shared regex [%s]\n", reg_shared.c_str());
@@ -966,7 +968,7 @@ void cmComputeLinkInformation::AddLinkExtension(const char* e, LinkType type)
 //----------------------------------------------------------------------------
 std::string
 cmComputeLinkInformation
-::CreateExtensionRegex(std::vector<std::string> const& exts)
+::CreateExtensionRegex(std::vector<std::string> const& exts, LinkType type)
 {
   // Build a list of extension choices.
   std::string libext = "(";
@@ -995,6 +997,10 @@ ::CreateExtensionRegex(std::vector<std::string> const& exts)
     {
     libext += "(\\.[0-9]+\\.[0-9]+)?";
     }
+  else if(type == LinkShared)
+    {
+    libext += "(\\.[0-9]+)?";
+    }
 
   libext += "$";
   return libext;
@@ -1724,6 +1730,17 @@ void
 cmComputeLinkInformation::AddLibraryRuntimeInfo(std::string const& fullPath,
                                                 cmTarget* target)
 {
+  // Ignore targets on Apple where install_name is not @rpath.
+  // The dependenty library can be found with other means such as
+  // @loader_path or full paths.
+  if(this->Makefile->IsOn("CMAKE_PLATFORM_HAS_INSTALLNAME"))
+    {
+    if(!target->HasMacOSXRpath(this->Config))
+      {
+      return;
+      }
+    }
+
   // Libraries with unknown type must be handled using just the file
   // on disk.
   if(target->GetType() == cmTarget::UNKNOWN_LIBRARY)
@@ -1756,25 +1773,60 @@ void
 cmComputeLinkInformation::AddLibraryRuntimeInfo(std::string const& fullPath)
 {
   // Get the name of the library from the file name.
+  bool is_shared_library = false;
   std::string file = cmSystemTools::GetFilenameName(fullPath);
-  if(!this->ExtractSharedLibraryName.find(file.c_str()))
+
+  if(this->Makefile->IsOn("CMAKE_PLATFORM_HAS_INSTALLNAME"))
+    {
+    // Check that @rpath is part of the install name.
+    // If it isn't, return.
+    std::string soname;
+    if(!cmSystemTools::GuessLibraryInstallName(fullPath, soname))
+      {
+      return;
+      }
+
+    if(soname.find("@rpath") == std::string::npos)
+      {
+      return;
+      }
+    }
+
+  is_shared_library = this->ExtractSharedLibraryName.find(file.c_str());
+
+  if(!is_shared_library)
     {
     // On some platforms (AIX) a shared library may look static.
     if(this->ArchivesMayBeShared)
       {
-      if(!this->ExtractStaticLibraryName.find(file.c_str()))
+      if(this->ExtractStaticLibraryName.find(file.c_str()))
         {
-        // This is not the name of a shared library or archive.
-        return;
+        // This is the name of a shared library or archive.
+        is_shared_library = true;
         }
       }
-    else
+    }
+
+  // It could be an Apple framework
+  if(!is_shared_library)
+    {
+    if(fullPath.find(".framework") != std::string::npos)
       {
-      // This is not the name of a shared library.
-      return;
+      cmsys::RegularExpression splitFramework;
+      splitFramework.compile("^(.*)/(.*).framework/.*/(.*)$");
+      if(splitFramework.find(fullPath) &&
+        (splitFramework.match(2) == splitFramework.match(3)))
+        {
+        is_shared_library = true;
+        }
       }
     }
 
+  if(!is_shared_library)
+    {
+    return;
+    }
+
   // Include this library in the runtime path ordering.
   this->OrderRuntimeSearchPath->AddRuntimeLibrary(fullPath);
   if(this->LinkWithRuntimePath)
@@ -1832,6 +1884,8 @@ void cmComputeLinkInformation::GetRPath(std::vector<std::string>& runtimeDirs,
     }
   if(use_build_rpath || use_link_rpath)
     {
+    std::string rootPath = this->Makefile->GetSafeDefinition("CMAKE_SYSROOT");
+    cmSystemTools::ConvertToUnixSlashes(rootPath);
     std::vector<std::string> const& rdirs = this->GetRuntimeSearchPath();
     for(std::vector<std::string>::const_iterator ri = rdirs.begin();
         ri != rdirs.end(); ++ri)
@@ -1855,9 +1909,14 @@ void cmComputeLinkInformation::GetRPath(std::vector<std::string>& runtimeDirs,
            !cmSystemTools::IsSubDirectory(ri->c_str(), topSourceDir) &&
            !cmSystemTools::IsSubDirectory(ri->c_str(), topBinaryDir))
           {
-          if(emitted.insert(*ri).second)
+          std::string d = *ri;
+          if (d.find(rootPath) == 0)
+            {
+            d = d.substr(rootPath.size());
+            }
+          if(emitted.insert(d).second)
             {
-            runtimeDirs.push_back(*ri);
+            runtimeDirs.push_back(d);
             }
           }
         }