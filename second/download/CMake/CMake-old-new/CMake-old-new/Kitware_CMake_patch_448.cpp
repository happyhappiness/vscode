@@ -602,14 +602,10 @@ bool cmake::FindPackage(const std::vector<std::string>& args)
     std::string includes = mf->GetSafeDefinition("PACKAGE_INCLUDE_DIRS");
     std::vector<std::string> includeDirs;
     cmSystemTools::ExpandListArgument(includes, includeDirs);
-    for(std::vector<std::string>::const_iterator dirIt=includeDirs.begin();
-            dirIt != includeDirs.end();
-            ++dirIt)
-      {
-      mf->AddIncludeDirectory(dirIt->c_str(), false);
-      }
 
-    std::string includeFlags = lg->GetIncludeFlags(language.c_str(), false);
+    std::string includeFlags = lg->GetIncludeFlags(includeDirs,
+                                                   language.c_str(), false);
+
     std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");
     printf("%s %s\n", includeFlags.c_str(), definitions.c_str());
     }
@@ -2130,32 +2126,8 @@ int cmake::Configure()
 
 }
 
-bool cmake::RejectUnsupportedPaths(const char* desc, std::string const& path)
-{
-  // Some characters are not well-supported by native build systems.
-  std::string::size_type pos = path.find_first_of("=");
-  if(pos == std::string::npos)
-    {
-    return false;
-    }
-  cmOStringStream e;
-  e << "The path to the " << desc << " directory:\n"
-    << "  " << path << "\n"
-    << "contains unsupported character '" << path[pos] << "'.\n"
-    << "Please use a different " << desc << " directory name.";
-  cmListFileBacktrace bt;
-  this->IssueMessage(cmake::FATAL_ERROR, e.str(), bt);
-  return true;
-}
-
 int cmake::ActualConfigure()
 {
-  if(this->RejectUnsupportedPaths("source", this->cmHomeDirectory) ||
-     this->RejectUnsupportedPaths("binary", this->HomeOutputDirectory))
-    {
-    return 1;
-    }
-
   // Construct right now our path conversion table before it's too late:
   this->UpdateConversionPathTable();
   this->CleanupCommandsAndMacros();
@@ -2208,8 +2180,11 @@ int cmake::ActualConfigure()
       std::string installedCompiler;
       // Try to find the newest VS installed on the computer and
       // use that as a default if -G is not specified
-      std::string vsregBase =
-        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\";
+      const std::string vsregBase =
+        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\";
+      std::vector<std::string> vsVerions;
+      vsVerions.push_back("VisualStudio\\");
+      vsVerions.push_back("VCExpress\\");
       struct VSRegistryEntryName
       {
         const char* MSVersion;
@@ -2223,14 +2198,18 @@ int cmake::ActualConfigure()
         {"9.0", "Visual Studio 9 2008"},
         {"10.0", "Visual Studio 10"},
         {0, 0}};
-      for(int i =0; version[i].MSVersion != 0; i++)
+      for(size_t b=0; b < vsVerions.size() && installedCompiler.empty(); b++)
         {
-        std::string reg = vsregBase + version[i].MSVersion;
-        reg += ";InstallDir]";
-        cmSystemTools::ExpandRegistryValues(reg);
-        if (!(reg == "/registry"))
+        for(int i =0; version[i].MSVersion != 0; i++)
           {
-          installedCompiler = version[i].GeneratorName;
+          std::string reg = vsregBase + vsVerions[b] + version[i].MSVersion;
+          reg += ";InstallDir]";
+          cmSystemTools::ExpandRegistryValues(reg,
+                                              cmSystemTools::KeyWOW64_32);
+          if (!(reg == "/registry"))
+            {
+            installedCompiler = version[i].GeneratorName;
+            }
           }
         }
       cmGlobalGenerator* gen
@@ -2685,7 +2664,9 @@ void cmake::GetCommandDocumentation(std::vector<cmDocumentationEntry>& v,
       j != this->Commands.end(); ++j)
     {
     if (((  withCompatCommands == false) && ( (*j).second->IsDiscouraged()))
-        || ((withCurrentCommands == false) && (!(*j).second->IsDiscouraged())))
+        || ((withCurrentCommands == false) && (!(*j).second->IsDiscouraged()))
+        || (!((*j).second->ShouldAppearInDocumentation()))
+        )
       {
       continue;
       }