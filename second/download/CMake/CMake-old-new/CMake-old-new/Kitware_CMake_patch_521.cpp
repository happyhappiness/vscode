@@ -67,8 +67,13 @@ cmFindPackageCommand::cmFindPackageCommand()
   this->VersionMinor = 0;
   this->VersionPatch = 0;
   this->VersionCount = 0;
+  this->VersionExact = false;
+  this->VersionFoundMajor = 0;
+  this->VersionFoundMinor = 0;
+  this->VersionFoundPatch = 0;
+  this->VersionFoundCount = 0;
   this->CommandDocumentation =
-    "  find_package(<package> [major[.minor[.patch]]] [QUIET]\n"
+    "  find_package(<package> [major[.minor[.patch]]] [EXACT] [QUIET]\n"
     "               [[REQUIRED|COMPONENTS] [components...]])\n"
     "Finds and loads settings from an external project.  "
     "<package>_FOUND will be set to indicate whether the package was found.  "
@@ -82,8 +87,9 @@ cmFindPackageCommand::cmFindPackageCommand()
     "option is given.  "
     "The \"[major[.minor[.patch]]]\" version argument specifies a desired "
     "version with which the package found should be compatible.  "
+    "The EXACT option requests that the version be matched exactly.  "
     "Version support is currently provided only on a package-by-package "
-    "basis and is not enforced by the command.\n"
+    "basis (details below).\n"
     "User code should generally look for packages using the above simple "
     "signature.  The remainder of this command documentation specifies the "
     "full command signature and details of the search process.  Project "
@@ -96,12 +102,14 @@ cmFindPackageCommand::cmFindPackageCommand()
     "CMake searches for a file called \"Find<package>.cmake\" in "
     "the CMAKE_MODULE_PATH followed by the CMake installation.  "
     "If the file is found, it is read and processed by CMake.  "
-    "It is responsible for finding the package or producing an error message "
-    "if package content cannot be found.  "
-    "Otherwise the command proceeds to Config mode.\n"
+    "It is responsible for finding the package, checking the version, "
+    "and producing any needed messages.  "
+    "Many find-modules provide limited or no support for versioning; "
+    "check the module documentation.  "
+    "If no module is found the command proceeds to Config mode.\n"
     "The complete Config mode command signature is:\n"
-    "  find_package(<package> [major[.minor[.patch]]] [QUIET] [NO_MODULE]\n"
-    "               [[REQUIRED|COMPONENTS] [components...]]\n"
+    "  find_package(<package> [major[.minor[.patch]]] [EXACT] [QUIET]\n"
+    "               [[REQUIRED|COMPONENTS] [components...]] [NO_MODULE]\n"
     "               [NAMES name1 [name2 ...]]\n"
     "               [CONFIGS config1 [config2 ...]]\n"
     "               [PATHS path1 [path2 ... ]]\n"
@@ -122,7 +130,6 @@ cmFindPackageCommand::cmFindPackageCommand()
     "Config mode attempts to locate a configuration file provided by the "
     "package to be found.  A cache entry called <package>_DIR is created to "
     "hold the directory containing the file.  "
-    "Currently versioning is not implemented by Config mode.  "
     "By default the command searches for a package with the name <package>.  "
     "If the NAMES option is given the names following it are used instead "
     "of <package>.  "
@@ -144,11 +151,49 @@ cmFindPackageCommand::cmFindPackageCommand()
     "a configuration file a fatal error is always generated because user "
     "intervention is required."
     "\n"
+    "When the \"[major[.minor[.patch]]]\" version argument is specified "
+    "Config mode will only find a version of the package that claims "
+    "compatibility with the requested version.  "
+    "If the EXACT option is given only a version of the package claiming "
+    "an exact match of the requested version may be found.  "
+    "CMake does not establish any convention for the meaning of version "
+    "numbers.  "
+    "Package version numbers are checked by \"version\" files provided by "
+    "the packages themselves.  "
+    "For a candidate package confguration file \"<config-file>.cmake\" the "
+    "corresponding version file is located next to it and named either "
+    "\"<config-file>-version.cmake\" or \"<config-file>Version.cmake\".  "
+    "If no such version file is available then the configuration file "
+    "is assumed to not be compatible with any requested version.  "
+    "When a version file is found it is loaded to check the requested "
+    "version number.  "
+    "The version file is loaded in a nested scope in which the following "
+    "variables have been defined:\n"
+    "  PACKAGE_FIND_NAME          = the <package> name\n"
+    "  PACKAGE_FIND_VERSION       = full requested version string\n"
+    "  PACKAGE_FIND_VERSION_MAJOR = requested major version, if any\n"
+    "  PACKAGE_FIND_VERSION_MINOR = requested minor version, if any\n"
+    "  PACKAGE_FIND_VERSION_PATCH = requested patch version, if any\n"
+    "The version file checks whether it satisfies the requested version "
+    "and sets these variables:\n"
+    "  PACKAGE_VERSION            = package version (major[.minor[.patch]])\n"
+    "  PACKAGE_VERSION_EXACT      = true if version is exact match\n"
+    "  PACKAGE_VERSION_COMPATIBLE = true if version is compatible\n"
+    "These variables are checked by the find_package command to determine "
+    "whether the configuration file provides an acceptable version.  "
+    "They are not available after the find_package call returns.  "
+    "If the version is acceptable the following variables are set:\n"
+    "  <package>_VERSION       = package version (major[.minor[.patch]])\n"
+    "  <package>_VERSION_MAJOR = major from major[.minor[.patch]], if any\n"
+    "  <package>_VERSION_MINOR = minor from major[.minor[.patch]], if any\n"
+    "  <package>_VERSION_PATCH = patch from major[.minor[.patch]], if any\n"
+    "and the corresponding package configuration file is loaded."
+    "\n"
     "Config mode provides an elaborate interface and search procedure.  "
     "Much of the interface is provided for completeness and for use "
     "internally by find-modules loaded by Module mode.  "
     "Most user code should simply call\n"
-    "  find_package(<package> [REQUIRED|QUIET])\n"
+    "  find_package(<package> [major[.minor]] [EXACT] [REQUIRED|QUIET])\n"
     "in order to find a package.  Package maintainers providing CMake "
     "package configuration files are encouraged to name and install "
     "them such that the procedure outlined below will find them "
@@ -275,6 +320,12 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
       this->Quiet = true;
       doing = DoingNone;
       }
+    else if(args[i] == "EXACT")
+      {
+      this->VersionExact = true;
+      this->Compatibility_1_6 = false;
+      doing = DoingNone;
+      }
     else if(args[i] == "NO_MODULE")
       {
       this->NoModule = true;
@@ -353,6 +404,15 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
       }
     else if(doing == DoingConfigs)
       {
+      if(args[i].find_first_of(":/\\") != args[i].npos ||
+         cmSystemTools::GetFilenameLastExtension(args[i]) != ".cmake")
+        {
+        cmOStringStream e;
+        e << "given CONFIGS option followed by invalid file name \""
+          << args[i] << "\".  The names given must be file names without "
+          << "a path and with a \".cmake\" extension.";
+        return false;
+        }
       this->Configs.push_back(args[i]);
       }
     else if(!haveVersion && version.find(args[i].c_str()))
@@ -494,6 +554,12 @@ bool cmFindPackageCommand::FindModule(bool& found)
           } // no break
         default: break;
         }
+
+      // Tell the module whether an exact version has been requested.
+      std::string exact = this->Name;
+      exact += "_FIND_VERSION_EXACT";
+      this->Makefile->AddDefinition(exact.c_str(),
+                                    this->VersionExact? "1":"0");
       }
 
     // Load the module we found.
@@ -555,8 +621,12 @@ bool cmFindPackageCommand::HandlePackageMode()
       }
 
     // Find the configuration file.
-    if(this->FindConfigFile(dir, file))
+    if(this->FindConfigFileToLoad(dir, file))
       {
+      // Set the version variables before loading the config file.
+      // It may override them.
+      this->StoreVersionFound();
+
       // Parse the configuration file.
       if(this->ReadListFile(file.c_str()))
         {
@@ -576,7 +646,7 @@ bool cmFindPackageCommand::HandlePackageMode()
       e << "cannot find package " << this->Name << " because "
         << this->Variable << " is set to \"" << def << "\" "
         << "which is not a directory containing a package configuration "
-        << "file.  "
+        << "file (or it is not for the requested version).  "
         << "Please set the cache entry " << this->Variable << " "
         << "to the correct directory, or delete it to ask CMake "
         << "to search.";
@@ -1009,6 +1079,8 @@ bool cmFindPackageCommand::CheckDirectory(std::string const& dir)
   std::string d = dir.substr(0, dir.size()-1);
   if(this->FindConfigFile(d, this->FileFound))
     {
+    // Remove duplicate slashes.
+    cmSystemTools::ConvertToUnixSlashes(this->FileFound);
     return true;
     }
   return false;
@@ -1028,7 +1100,8 @@ bool cmFindPackageCommand::FindConfigFile(std::string const& dir,
       {
       fprintf(stderr, "Checking file [%s]\n", file.c_str());
       }
-    if(cmSystemTools::FileExists(file.c_str(), true))
+    if(cmSystemTools::FileExists(file.c_str(), true) &&
+       this->CheckVersion(file))
       {
       return true;
       }
@@ -1037,6 +1110,182 @@ bool cmFindPackageCommand::FindConfigFile(std::string const& dir,
 }
 
 //----------------------------------------------------------------------------
+bool cmFindPackageCommand::FindConfigFileToLoad(std::string const& dir,
+                                                std::string& file)
+{
+  if(this->FileFound.empty())
+    {
+    // The file location was cached.  Look for the correct file.
+    return this->FindConfigFile(dir, file);
+    }
+  else
+    {
+    // The file location was just found during this call.
+    // Use the file found without searching again.
+    file = this->FileFound;
+    return true;
+    }
+}
+
+//----------------------------------------------------------------------------
+bool cmFindPackageCommand::CheckVersion(std::string const& config_file)
+{
+  // Get the filename without the .cmake extension.
+  std::string::size_type pos = config_file.rfind('.');
+  std::string version_file_base = config_file.substr(0, pos);
+
+  // Look for foo-config-version.cmake
+  std::string version_file = version_file_base;
+  version_file += "-version.cmake";
+  if(cmSystemTools::FileExists(version_file.c_str(), true))
+    {
+    return this->CheckVersionFile(version_file);
+    }
+
+  // Look for fooConfigVersion.cmake
+  version_file = version_file_base;
+  version_file += "Version.cmake";
+  if(cmSystemTools::FileExists(version_file.c_str(), true))
+    {
+    return this->CheckVersionFile(version_file);
+    }
+
+  // If no version was requested a versionless package is acceptable.
+  if(this->Version.empty())
+    {
+    return true;
+    }
+
+  // No version file found.  Assume the version is incompatible.
+  return false;
+}
+
+//----------------------------------------------------------------------------
+bool cmFindPackageCommand::CheckVersionFile(std::string const& version_file)
+{
+  // The version file will be loaded in an isolated scope.
+  this->Makefile->PushScope();
+
+  // Clear the output variables.
+  this->Makefile->RemoveDefinition("PACKAGE_VERSION");
+  this->Makefile->RemoveDefinition("PACKAGE_VERSION_COMPATIBLE");
+  this->Makefile->RemoveDefinition("PACKAGE_VERSION_EXACT");
+
+  // Set the input variables.
+  this->Makefile->AddDefinition("PACKAGE_FIND_NAME", this->Name.c_str());
+  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION",
+                                this->Version.c_str());
+  if(this->VersionCount >= 3)
+    {
+    char buf[64];
+    sprintf(buf, "%u", this->VersionPatch);
+    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
+    }
+  else
+    {
+    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_PATCH");
+    }
+  if(this->VersionCount >= 2)
+    {
+    char buf[64];
+    sprintf(buf, "%u", this->VersionMinor);
+    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
+    }
+  else
+    {
+    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MINOR");
+    }
+  if(this->VersionCount >= 1)
+    {
+    char buf[64];
+    sprintf(buf, "%u", this->VersionMajor);
+    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
+    }
+  else
+    {
+    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MAJOR");
+    }
+
+  // Load the version check file.
+  bool found = false;
+  if(this->ReadListFile(version_file.c_str()))
+    {
+    // Check the output variables.
+    found = this->Makefile->IsOn("PACKAGE_VERSION_EXACT");
+    if(!found && !this->VersionExact)
+      {
+      found = this->Makefile->IsOn("PACKAGE_VERSION_COMPATIBLE");
+      }
+    if(found || this->Version.empty())
+      {
+      // Get the version found.
+      this->VersionFound =
+        this->Makefile->GetSafeDefinition("PACKAGE_VERSION");
+
+      // Try to parse the version number and store the results that were
+      // successfully parsed.
+      unsigned int parsed_major;
+      unsigned int parsed_minor;
+      unsigned int parsed_patch;
+      this->VersionFoundCount =
+        sscanf(this->VersionFound.c_str(), "%u.%u.%u",
+               &parsed_major, &parsed_minor, &parsed_patch);
+      switch(this->VersionFoundCount)
+        {
+        case 3: this->VersionFoundPatch = parsed_patch; // no break!
+        case 2: this->VersionFoundMinor = parsed_minor; // no break!
+        case 1: this->VersionFoundMajor = parsed_major; // no break!
+        default: break;
+        }
+      }
+    }
+
+  // Restore the original scope.
+  this->Makefile->PopScope();
+
+  // Succeed if the version was found or no version was requested.
+  return found || this->Version.empty();
+}
+
+//----------------------------------------------------------------------------
+void cmFindPackageCommand::StoreVersionFound()
+{
+  // Store the whole version string.
+  std::string ver = this->Name;
+  ver += "_VERSION";
+  if(this->VersionFound.empty())
+    {
+    this->Makefile->RemoveDefinition(ver.c_str());
+    }
+  else
+    {
+    this->Makefile->AddDefinition(ver.c_str(), this->VersionFound.c_str());
+    }
+
+  // Store the portions that could be parsed.
+  char buf[64];
+  switch(this->VersionFoundCount)
+    {
+    case 3:
+      {
+      sprintf(buf, "%u", this->VersionFoundPatch);
+      this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
+      } // no break
+    case 2:
+      {
+      sprintf(buf, "%u", this->VersionFoundMinor);
+      this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
+      } // no break
+    case 1:
+      {
+      sprintf(buf, "%u", this->VersionFoundMajor);
+      this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
+      } // no break
+    default: break;
+    }
+}
+
+//----------------------------------------------------------------------------
 #include <cmsys/Directory.hxx>
 #include <cmsys/Glob.hxx>
 #include <cmsys/String.h>