@@ -67,14 +67,16 @@ cmFindPackageCommand::cmFindPackageCommand()
   this->VersionMajor = 0;
   this->VersionMinor = 0;
   this->VersionPatch = 0;
+  this->VersionTweak = 0;
   this->VersionCount = 0;
   this->VersionExact = false;
   this->VersionFoundMajor = 0;
   this->VersionFoundMinor = 0;
   this->VersionFoundPatch = 0;
+  this->VersionFoundTweak = 0;
   this->VersionFoundCount = 0;
   this->CommandDocumentation =
-    "  find_package(<package> [major[.minor[.patch]]] [EXACT] [QUIET]\n"
+    "  find_package(<package> [version] [EXACT] [QUIET]\n"
     "               [[REQUIRED|COMPONENTS] [components...]])\n"
     "Finds and loads settings from an external project.  "
     "<package>_FOUND will be set to indicate whether the package was found.  "
@@ -86,8 +88,8 @@ cmFindPackageCommand::cmFindPackageCommand()
     "A package-specific list of components may be listed after the "
     "REQUIRED option or after the COMPONENTS option if no REQUIRED "
     "option is given.  "
-    "The \"[major[.minor[.patch]]]\" version argument specifies a desired "
-    "version with which the package found should be compatible.  "
+    "The [version] argument requests a version with which the package found "
+    "should be compatible (format is major[.minor[.patch[.tweak]]]).  "
     "The EXACT option requests that the version be matched exactly.  "
     "Version support is currently provided only on a package-by-package "
     "basis (details below).\n"
@@ -109,7 +111,7 @@ cmFindPackageCommand::cmFindPackageCommand()
     "check the module documentation.  "
     "If no module is found the command proceeds to Config mode.\n"
     "The complete Config mode command signature is:\n"
-    "  find_package(<package> [major[.minor[.patch]]] [EXACT] [QUIET]\n"
+    "  find_package(<package> [version] [EXACT] [QUIET]\n"
     "               [[REQUIRED|COMPONENTS] [components...]] [NO_MODULE]\n"
     "               [NAMES name1 [name2 ...]]\n"
     "               [CONFIGS config1 [config2 ...]]\n"
@@ -153,9 +155,9 @@ cmFindPackageCommand::cmFindPackageCommand()
     "a configuration file a fatal error is always generated because user "
     "intervention is required."
     "\n"
-    "When the \"[major[.minor[.patch]]]\" version argument is specified "
-    "Config mode will only find a version of the package that claims "
-    "compatibility with the requested version.  "
+    "When the [version] argument is given Config mode will only find a "
+    "version of the package that claims compatibility with the requested "
+    "version (format is major[.minor[.patch[.tweak]]]).  "
     "If the EXACT option is given only a version of the package claiming "
     "an exact match of the requested version may be found.  "
     "CMake does not establish any convention for the meaning of version "
@@ -173,22 +175,26 @@ cmFindPackageCommand::cmFindPackageCommand()
     "variables have been defined:\n"
     "  PACKAGE_FIND_NAME          = the <package> name\n"
     "  PACKAGE_FIND_VERSION       = full requested version string\n"
-    "  PACKAGE_FIND_VERSION_MAJOR = requested major version, if any\n"
-    "  PACKAGE_FIND_VERSION_MINOR = requested minor version, if any\n"
-    "  PACKAGE_FIND_VERSION_PATCH = requested patch version, if any\n"
+    "  PACKAGE_FIND_VERSION_MAJOR = major version if requested, else 0\n"
+    "  PACKAGE_FIND_VERSION_MINOR = minor version if requested, else 0\n"
+    "  PACKAGE_FIND_VERSION_PATCH = patch version if requested, else 0\n"
+    "  PACKAGE_FIND_VERSION_TWEAK = tweak version if requested, else 0\n"
+    "  PACKAGE_FIND_VERSION_COUNT = number of version components, 0 to 4\n"
     "The version file checks whether it satisfies the requested version "
     "and sets these variables:\n"
-    "  PACKAGE_VERSION            = package version (major[.minor[.patch]])\n"
+    "  PACKAGE_VERSION            = full provided version string\n"
     "  PACKAGE_VERSION_EXACT      = true if version is exact match\n"
     "  PACKAGE_VERSION_COMPATIBLE = true if version is compatible\n"
     "These variables are checked by the find_package command to determine "
     "whether the configuration file provides an acceptable version.  "
     "They are not available after the find_package call returns.  "
     "If the version is acceptable the following variables are set:\n"
-    "  <package>_VERSION       = package version (major[.minor[.patch]])\n"
-    "  <package>_VERSION_MAJOR = major from major[.minor[.patch]], if any\n"
-    "  <package>_VERSION_MINOR = minor from major[.minor[.patch]], if any\n"
-    "  <package>_VERSION_PATCH = patch from major[.minor[.patch]], if any\n"
+    "  <package>_VERSION       = full provided version string\n"
+    "  <package>_VERSION_MAJOR = major version if provided, else 0\n"
+    "  <package>_VERSION_MINOR = minor version if provided, else 0\n"
+    "  <package>_VERSION_PATCH = patch version if provided, else 0\n"
+    "  <package>_VERSION_TWEAK = tweak version if provided, else 0\n"
+    "  <package>_VERSION_COUNT = number of version components, 0 to 4\n"
     "and the corresponding package configuration file is loaded.  "
     "When multiple package configuration files are available whose version "
     "files claim compatibility with the version requested it is unspecified "
@@ -469,10 +475,13 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
     unsigned int parsed_major;
     unsigned int parsed_minor;
     unsigned int parsed_patch;
-    this->VersionCount = sscanf(this->Version.c_str(), "%u.%u.%u",
-                                &parsed_major, &parsed_minor, &parsed_patch);
+    unsigned int parsed_tweak;
+    this->VersionCount = sscanf(this->Version.c_str(), "%u.%u.%u.%u",
+                                &parsed_major, &parsed_minor,
+                                &parsed_patch, &parsed_tweak);
     switch(this->VersionCount)
       {
+      case 4: this->VersionTweak = parsed_tweak; // no break!
       case 3: this->VersionPatch = parsed_patch; // no break!
       case 2: this->VersionMinor = parsed_minor; // no break!
       case 1: this->VersionMajor = parsed_major; // no break!
@@ -565,25 +574,16 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
     ver += "_FIND_VERSION";
     this->Makefile->AddDefinition(ver.c_str(), this->Version.c_str());
     char buf[64];
-    switch(this->VersionCount)
-      {
-      case 3:
-        {
-        sprintf(buf, "%u", this->VersionPatch);
-        this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
-        } // no break
-      case 2:
-        {
-        sprintf(buf, "%u", this->VersionMinor);
-        this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
-        } // no break
-      case 1:
-        {
-        sprintf(buf, "%u", this->VersionMajor);
-        this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
-        } // no break
-      default: break;
-      }
+    sprintf(buf, "%u", this->VersionMajor);
+    this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
+    sprintf(buf, "%u", this->VersionMinor);
+    this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
+    sprintf(buf, "%u", this->VersionPatch);
+    this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
+    sprintf(buf, "%u", this->VersionTweak);
+    this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);
+    sprintf(buf, "%u", this->VersionCount);
+    this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);
 
     // Tell the module whether an exact version has been requested.
     std::string exact = this->Name;
@@ -1234,36 +1234,17 @@ bool cmFindPackageCommand::CheckVersionFile(std::string const& version_file)
   this->Makefile->AddDefinition("PACKAGE_FIND_NAME", this->Name.c_str());
   this->Makefile->AddDefinition("PACKAGE_FIND_VERSION",
                                 this->Version.c_str());
-  if(this->VersionCount >= 3)
-    {
-    char buf[64];
-    sprintf(buf, "%u", this->VersionPatch);
-    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
-    }
-  else
-    {
-    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_PATCH");
-    }
-  if(this->VersionCount >= 2)
-    {
-    char buf[64];
-    sprintf(buf, "%u", this->VersionMinor);
-    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
-    }
-  else
-    {
-    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MINOR");
-    }
-  if(this->VersionCount >= 1)
-    {
-    char buf[64];
-    sprintf(buf, "%u", this->VersionMajor);
-    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
-    }
-  else
-    {
-    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MAJOR");
-    }
+  char buf[64];
+  sprintf(buf, "%u", this->VersionMajor);
+  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
+  sprintf(buf, "%u", this->VersionMinor);
+  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
+  sprintf(buf, "%u", this->VersionPatch);
+  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
+  sprintf(buf, "%u", this->VersionTweak);
+  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_TWEAK", buf);
+  sprintf(buf, "%u", this->VersionCount);
+  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_COUNT", buf);
 
   // Load the version check file.
   bool found = false;
@@ -1286,11 +1267,14 @@ bool cmFindPackageCommand::CheckVersionFile(std::string const& version_file)
       unsigned int parsed_major;
       unsigned int parsed_minor;
       unsigned int parsed_patch;
+      unsigned int parsed_tweak;
       this->VersionFoundCount =
-        sscanf(this->VersionFound.c_str(), "%u.%u.%u",
-               &parsed_major, &parsed_minor, &parsed_patch);
+        sscanf(this->VersionFound.c_str(), "%u.%u.%u.%u",
+               &parsed_major, &parsed_minor,
+               &parsed_patch, &parsed_tweak);
       switch(this->VersionFoundCount)
         {
+        case 4: this->VersionFoundTweak = parsed_tweak; // no break!
         case 3: this->VersionFoundPatch = parsed_patch; // no break!
         case 2: this->VersionFoundMinor = parsed_minor; // no break!
         case 1: this->VersionFoundMajor = parsed_major; // no break!
@@ -1321,27 +1305,18 @@ void cmFindPackageCommand::StoreVersionFound()
     this->Makefile->AddDefinition(ver.c_str(), this->VersionFound.c_str());
     }
 
-  // Store the portions that could be parsed.
+  // Store the version components.
   char buf[64];
-  switch(this->VersionFoundCount)
-    {
-    case 3:
-      {
-      sprintf(buf, "%u", this->VersionFoundPatch);
-      this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
-      } // no break
-    case 2:
-      {
-      sprintf(buf, "%u", this->VersionFoundMinor);
-      this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
-      } // no break
-    case 1:
-      {
-      sprintf(buf, "%u", this->VersionFoundMajor);
-      this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
-      } // no break
-    default: break;
-    }
+  sprintf(buf, "%u", this->VersionFoundMajor);
+  this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
+  sprintf(buf, "%u", this->VersionFoundMinor);
+  this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
+  sprintf(buf, "%u", this->VersionFoundPatch);
+  this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
+  sprintf(buf, "%u", this->VersionFoundTweak);
+  this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);
+  sprintf(buf, "%u", this->VersionFoundCount);
+  this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);
 }
 
 //----------------------------------------------------------------------------