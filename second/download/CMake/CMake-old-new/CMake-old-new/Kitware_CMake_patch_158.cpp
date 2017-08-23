@@ -30,7 +30,8 @@
 // a GNU ar.
 // See http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=161593 for more info
 // Therefore we provide our own implementation of a BSD-ar:
-static int ar_append(const char*archive,const std::vector<std::string>& files);
+static int ar_append(const char* archive,
+                     const std::vector<std::string>& files);
 
 cmCPackDebGenerator::cmCPackDebGenerator()
 {
@@ -43,70 +44,63 @@ cmCPackDebGenerator::~cmCPackDebGenerator()
 int cmCPackDebGenerator::InitializeInternal()
 {
   this->SetOptionIfNotSet("CPACK_PACKAGING_INSTALL_PREFIX", "/usr");
-  if (cmSystemTools::IsOff(this->GetOption("CPACK_SET_DESTDIR")))
-    {
+  if (cmSystemTools::IsOff(this->GetOption("CPACK_SET_DESTDIR"))) {
     this->SetOption("CPACK_SET_DESTDIR", "I_ON");
-    }
+  }
   return this->Superclass::InitializeInternal();
 }
 
 int cmCPackDebGenerator::PackageOnePack(std::string initialTopLevel,
                                         std::string packageName)
-  {
+{
   int retval = 1;
   // Begin the archive for this pack
   std::string localToplevel(initialTopLevel);
-  std::string packageFileName(
-      cmSystemTools::GetParentDirectory(toplevel)
-  );
-  std::string outputFileName(
-          cmsys::SystemTools::LowerCase(
-              std::string(this->GetOption("CPACK_PACKAGE_FILE_NAME")))
-          +"-"+packageName + this->GetOutputExtension()
-      );
-
-  localToplevel += "/"+ packageName;
+  std::string packageFileName(cmSystemTools::GetParentDirectory(toplevel));
+  std::string outputFileName(cmsys::SystemTools::LowerCase(std::string(
+                               this->GetOption("CPACK_PACKAGE_FILE_NAME"))) +
+                             "-" + packageName + this->GetOutputExtension());
+
+  localToplevel += "/" + packageName;
   /* replace the TEMP DIRECTORY with the component one */
-  this->SetOption("CPACK_TEMPORARY_DIRECTORY",localToplevel.c_str());
-  packageFileName += "/"+ outputFileName;
+  this->SetOption("CPACK_TEMPORARY_DIRECTORY", localToplevel.c_str());
+  packageFileName += "/" + outputFileName;
   /* replace proposed CPACK_OUTPUT_FILE_NAME */
-  this->SetOption("CPACK_OUTPUT_FILE_NAME",outputFileName.c_str());
+  this->SetOption("CPACK_OUTPUT_FILE_NAME", outputFileName.c_str());
   /* replace the TEMPORARY package file name */
   this->SetOption("CPACK_TEMPORARY_PACKAGE_FILE_NAME",
-      packageFileName.c_str());
+                  packageFileName.c_str());
   // Tell CPackDeb.cmake the name of the component GROUP.
-  this->SetOption("CPACK_DEB_PACKAGE_COMPONENT",packageName.c_str());
+  this->SetOption("CPACK_DEB_PACKAGE_COMPONENT", packageName.c_str());
   // Tell CPackDeb.cmake the path where the component is.
   std::string component_path = "/";
   component_path += packageName;
   this->SetOption("CPACK_DEB_PACKAGE_COMPONENT_PART_PATH",
                   component_path.c_str());
-  if (!this->ReadListFile("CPackDeb.cmake"))
-    {
-    cmCPackLogger(cmCPackLog::LOG_ERROR,
-        "Error while execution CPackDeb.cmake" << std::endl);
+  if (!this->ReadListFile("CPackDeb.cmake")) {
+    cmCPackLogger(cmCPackLog::LOG_ERROR, "Error while execution CPackDeb.cmake"
+                    << std::endl);
     retval = 0;
     return retval;
-    }
+  }
 
   cmsys::Glob gl;
   std::string findExpr(this->GetOption("GEN_WDIR"));
   findExpr += "/*";
   gl.RecurseOn();
   gl.SetRecurseListDirs(true);
-  if ( !gl.FindFiles(findExpr) )
-    {
+  if (!gl.FindFiles(findExpr)) {
     cmCPackLogger(cmCPackLog::LOG_ERROR,
-        "Cannot find any files in the installed directory" << std::endl);
+                  "Cannot find any files in the installed directory"
+                    << std::endl);
     return 0;
-    }
+  }
   packageFiles = gl.GetFiles();
 
   int res = createDeb();
-  if (res != 1)
-    {
+  if (res != 1) {
     retval = 0;
-    }
+  }
   // add the generated package to package file names list
   packageFileName = this->GetOption("CPACK_TOPLEVEL_DIRECTORY");
   packageFileName += "/";
@@ -125,53 +119,46 @@ int cmCPackDebGenerator::PackageComponents(bool ignoreGroup)
 
   // The default behavior is to have one package by component group
   // unless CPACK_COMPONENTS_IGNORE_GROUP is specified.
-  if (!ignoreGroup)
-    {
+  if (!ignoreGroup) {
     std::map<std::string, cmCPackComponentGroup>::iterator compGIt;
-    for (compGIt=this->ComponentGroups.begin();
-        compGIt!=this->ComponentGroups.end(); ++compGIt)
-      {
+    for (compGIt = this->ComponentGroups.begin();
+         compGIt != this->ComponentGroups.end(); ++compGIt) {
       cmCPackLogger(cmCPackLog::LOG_VERBOSE, "Packaging component group: "
-          << compGIt->first
-          << std::endl);
+                      << compGIt->first << std::endl);
       // Begin the archive for this group
-      retval &= PackageOnePack(initialTopLevel,compGIt->first);
-      }
+      retval &= PackageOnePack(initialTopLevel, compGIt->first);
+    }
     // Handle Orphan components (components not belonging to any groups)
     std::map<std::string, cmCPackComponent>::iterator compIt;
-    for (compIt=this->Components.begin();
-        compIt!=this->Components.end(); ++compIt )
-      {
+    for (compIt = this->Components.begin(); compIt != this->Components.end();
+         ++compIt) {
       // Does the component belong to a group?
-      if (compIt->second.Group==NULL)
-        {
-        cmCPackLogger(cmCPackLog::LOG_VERBOSE,
-            "Component <"
+      if (compIt->second.Group == NULL) {
+        cmCPackLogger(
+          cmCPackLog::LOG_VERBOSE, "Component <"
             << compIt->second.Name
             << "> does not belong to any group, package it separately."
             << std::endl);
         // Begin the archive for this orphan component
-        retval &= PackageOnePack(initialTopLevel,compIt->first);
-        }
+        retval &= PackageOnePack(initialTopLevel, compIt->first);
       }
     }
+  }
   // CPACK_COMPONENTS_IGNORE_GROUPS is set
   // We build 1 package per component
-  else
-    {
+  else {
     std::map<std::string, cmCPackComponent>::iterator compIt;
-    for (compIt=this->Components.begin();
-         compIt!=this->Components.end(); ++compIt )
-      {
-      retval &= PackageOnePack(initialTopLevel,compIt->first);
-      }
+    for (compIt = this->Components.begin(); compIt != this->Components.end();
+         ++compIt) {
+      retval &= PackageOnePack(initialTopLevel, compIt->first);
     }
+  }
   return retval;
 }
 
 //----------------------------------------------------------------------
 int cmCPackDebGenerator::PackageComponentsAllInOne(
-    const std::string& compInstDirName)
+  const std::string& compInstDirName)
 {
   int retval = 1;
   /* Reset package file name list it will be populated during the
@@ -182,65 +169,57 @@ int cmCPackDebGenerator::PackageComponentsAllInOne(
   cmCPackLogger(cmCPackLog::LOG_VERBOSE,
                 "Packaging all groups in one package..."
                 "(CPACK_COMPONENTS_ALL_[GROUPS_]IN_ONE_PACKAGE is set)"
-      << std::endl);
+                  << std::endl);
 
   // The ALL GROUPS in ONE package case
   std::string localToplevel(initialTopLevel);
-  std::string packageFileName(
-      cmSystemTools::GetParentDirectory(toplevel)
-                             );
-  std::string outputFileName(
-            cmsys::SystemTools::LowerCase(
-                std::string(this->GetOption("CPACK_PACKAGE_FILE_NAME")))
-            + this->GetOutputExtension()
-                            );
+  std::string packageFileName(cmSystemTools::GetParentDirectory(toplevel));
+  std::string outputFileName(cmsys::SystemTools::LowerCase(std::string(
+                               this->GetOption("CPACK_PACKAGE_FILE_NAME"))) +
+                             this->GetOutputExtension());
   // all GROUP in one vs all COMPONENT in one
-  localToplevel += "/"+compInstDirName;
+  localToplevel += "/" + compInstDirName;
 
   /* replace the TEMP DIRECTORY with the component one */
-  this->SetOption("CPACK_TEMPORARY_DIRECTORY",localToplevel.c_str());
-  packageFileName += "/"+ outputFileName;
+  this->SetOption("CPACK_TEMPORARY_DIRECTORY", localToplevel.c_str());
+  packageFileName += "/" + outputFileName;
   /* replace proposed CPACK_OUTPUT_FILE_NAME */
-  this->SetOption("CPACK_OUTPUT_FILE_NAME",outputFileName.c_str());
+  this->SetOption("CPACK_OUTPUT_FILE_NAME", outputFileName.c_str());
   /* replace the TEMPORARY package file name */
   this->SetOption("CPACK_TEMPORARY_PACKAGE_FILE_NAME",
-      packageFileName.c_str());
+                  packageFileName.c_str());
 
-  if(!compInstDirName.empty())
-    {
+  if (!compInstDirName.empty()) {
     // Tell CPackDeb.cmake the path where the component is.
     std::string component_path = "/";
     component_path += compInstDirName;
     this->SetOption("CPACK_DEB_PACKAGE_COMPONENT_PART_PATH",
                     component_path.c_str());
-    }
-  if (!this->ReadListFile("CPackDeb.cmake"))
-    {
-    cmCPackLogger(cmCPackLog::LOG_ERROR,
-        "Error while execution CPackDeb.cmake" << std::endl);
+  }
+  if (!this->ReadListFile("CPackDeb.cmake")) {
+    cmCPackLogger(cmCPackLog::LOG_ERROR, "Error while execution CPackDeb.cmake"
+                    << std::endl);
     retval = 0;
     return retval;
-    }
+  }
 
   cmsys::Glob gl;
   std::string findExpr(this->GetOption("GEN_WDIR"));
   findExpr += "/*";
   gl.RecurseOn();
   gl.SetRecurseListDirs(true);
-  if ( !gl.FindFiles(findExpr) )
-    {
+  if (!gl.FindFiles(findExpr)) {
     cmCPackLogger(cmCPackLog::LOG_ERROR,
-    "Cannot find any files in the installed directory" << std::endl);
+                  "Cannot find any files in the installed directory"
+                    << std::endl);
     return 0;
-    }
+  }
   packageFiles = gl.GetFiles();
 
-
   int res = createDeb();
-  if (res != 1)
-    {
+  if (res != 1) {
     retval = 0;
-    }
+  }
   // add the generated package to package file names list
   packageFileName = this->GetOption("CPACK_TOPLEVEL_DIRECTORY");
   packageFileName += "/";
@@ -256,232 +235,206 @@ int cmCPackDebGenerator::PackageFiles()
     // CASE 1 : COMPONENT ALL-IN-ONE package
     // If ALL GROUPS or ALL COMPONENTS in ONE package has been requested
     // then the package file is unique and should be open here.
-    if (componentPackageMethod == ONE_PACKAGE)
-      {
+    if (componentPackageMethod == ONE_PACKAGE) {
       return PackageComponentsAllInOne("ALL_COMPONENTS_IN_ONE");
-      }
+    }
     // CASE 2 : COMPONENT CLASSICAL package(s) (i.e. not all-in-one)
     // There will be 1 package for each component group
     // however one may require to ignore component group and
     // in this case you'll get 1 package for each component.
-    else
-      {
+    else {
       return PackageComponents(componentPackageMethod ==
                                ONE_PACKAGE_PER_COMPONENT);
-      }
+    }
   }
   // CASE 3 : NON COMPONENT package.
-  else
-    {
+  else {
     return PackageComponentsAllInOne("");
-    }
+  }
 }
 
 int cmCPackDebGenerator::createDeb()
 {
   // debian-binary file
   const std::string strGenWDIR(this->GetOption("GEN_WDIR"));
   const std::string dbfilename = strGenWDIR + "/debian-binary";
-    { // the scope is needed for cmGeneratedFileStream
+  { // the scope is needed for cmGeneratedFileStream
     cmGeneratedFileStream out(dbfilename.c_str());
     out << "2.0";
     out << std::endl; // required for valid debian package
-    }
+  }
 
   // control file
   std::string ctlfilename = strGenWDIR + "/control";
 
   // debian policy enforce lower case for package name
   // mandatory entries:
   std::string debian_pkg_name = cmsys::SystemTools::LowerCase(
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_NAME") );
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_NAME"));
   const char* debian_pkg_version =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_VERSION");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_VERSION");
   const char* debian_pkg_section =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SECTION");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SECTION");
   const char* debian_pkg_priority =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_PRIORITY");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_PRIORITY");
   const char* debian_pkg_arch =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_ARCHITECTURE");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_ARCHITECTURE");
   const char* maintainer =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_MAINTAINER");
-  const char* desc =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_DESCRIPTION");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_MAINTAINER");
+  const char* desc = this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_DESCRIPTION");
 
   // optional entries
   const char* debian_pkg_dep =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_DEPENDS");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_DEPENDS");
   const char* debian_pkg_rec =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_RECOMMENDS");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_RECOMMENDS");
   const char* debian_pkg_sug =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SUGGESTS");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SUGGESTS");
   const char* debian_pkg_url =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_HOMEPAGE");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_HOMEPAGE");
   const char* debian_pkg_predep =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_PREDEPENDS");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_PREDEPENDS");
   const char* debian_pkg_enhances =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_ENHANCES");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_ENHANCES");
   const char* debian_pkg_breaks =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_BREAKS");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_BREAKS");
   const char* debian_pkg_conflicts =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_CONFLICTS");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_CONFLICTS");
   const char* debian_pkg_provides =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_PROVIDES");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_PROVIDES");
   const char* debian_pkg_replaces =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_REPLACES");
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_REPLACES");
   const char* debian_pkg_source =
-      this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SOURCE");
-
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SOURCE");
 
-    { // the scope is needed for cmGeneratedFileStream
+  { // the scope is needed for cmGeneratedFileStream
     cmGeneratedFileStream out(ctlfilename.c_str());
     out << "Package: " << debian_pkg_name << "\n";
     out << "Version: " << debian_pkg_version << "\n";
     out << "Section: " << debian_pkg_section << "\n";
     out << "Priority: " << debian_pkg_priority << "\n";
     out << "Architecture: " << debian_pkg_arch << "\n";
-    if(debian_pkg_source && *debian_pkg_source)
-      {
+    if (debian_pkg_source && *debian_pkg_source) {
       out << "Source: " << debian_pkg_source << "\n";
-      }
-    if(debian_pkg_dep && *debian_pkg_dep)
-      {
+    }
+    if (debian_pkg_dep && *debian_pkg_dep) {
       out << "Depends: " << debian_pkg_dep << "\n";
-      }
-    if(debian_pkg_rec && *debian_pkg_rec)
-      {
+    }
+    if (debian_pkg_rec && *debian_pkg_rec) {
       out << "Recommends: " << debian_pkg_rec << "\n";
-      }
-    if(debian_pkg_sug && *debian_pkg_sug)
-      {
+    }
+    if (debian_pkg_sug && *debian_pkg_sug) {
       out << "Suggests: " << debian_pkg_sug << "\n";
-      }
-    if(debian_pkg_url && *debian_pkg_url)
-      {
+    }
+    if (debian_pkg_url && *debian_pkg_url) {
       out << "Homepage: " << debian_pkg_url << "\n";
-      }
-    if (debian_pkg_predep && *debian_pkg_predep)
-      {
+    }
+    if (debian_pkg_predep && *debian_pkg_predep) {
       out << "Pre-Depends: " << debian_pkg_predep << "\n";
-      }
-    if (debian_pkg_enhances && *debian_pkg_enhances)
-      {
+    }
+    if (debian_pkg_enhances && *debian_pkg_enhances) {
       out << "Enhances: " << debian_pkg_enhances << "\n";
-      }
-    if (debian_pkg_breaks && *debian_pkg_breaks)
-      {
+    }
+    if (debian_pkg_breaks && *debian_pkg_breaks) {
       out << "Breaks: " << debian_pkg_breaks << "\n";
-      }
-    if (debian_pkg_conflicts && *debian_pkg_conflicts)
-      {
+    }
+    if (debian_pkg_conflicts && *debian_pkg_conflicts) {
       out << "Conflicts: " << debian_pkg_conflicts << "\n";
-      }
-    if (debian_pkg_provides && *debian_pkg_provides)
-      {
+    }
+    if (debian_pkg_provides && *debian_pkg_provides) {
       out << "Provides: " << debian_pkg_provides << "\n";
-      }
-    if (debian_pkg_replaces && *debian_pkg_replaces)
-      {
+    }
+    if (debian_pkg_replaces && *debian_pkg_replaces) {
       out << "Replaces: " << debian_pkg_replaces << "\n";
-      }
+    }
     unsigned long totalSize = 0;
     {
       std::string dirName = this->GetOption("CPACK_TEMPORARY_DIRECTORY");
       dirName += '/';
       for (std::vector<std::string>::const_iterator fileIt =
-           packageFiles.begin();
-           fileIt != packageFiles.end(); ++ fileIt )
-        {
+             packageFiles.begin();
+           fileIt != packageFiles.end(); ++fileIt) {
         totalSize += cmSystemTools::FileLength(*fileIt);
-        }
+      }
     }
     out << "Installed-Size: " << (totalSize + 1023) / 1024 << "\n";
     out << "Maintainer: " << maintainer << "\n";
     out << "Description: " << desc << "\n";
     out << std::endl;
-    }
+  }
 
   const std::string shlibsfilename = strGenWDIR + "/shlibs";
 
-  const char* debian_pkg_shlibs = this->GetOption(
-      "GEN_CPACK_DEBIAN_PACKAGE_SHLIBS");
-  const bool gen_shibs = this->IsOn("CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS")
-      && debian_pkg_shlibs && *debian_pkg_shlibs;
-  if( gen_shibs )
-    {
+  const char* debian_pkg_shlibs =
+    this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_SHLIBS");
+  const bool gen_shibs = this->IsOn("CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS") &&
+    debian_pkg_shlibs && *debian_pkg_shlibs;
+  if (gen_shibs) {
     cmGeneratedFileStream out(shlibsfilename.c_str());
     out << debian_pkg_shlibs;
     out << std::endl;
-    }
+  }
 
   const std::string postinst = strGenWDIR + "/postinst";
   const std::string postrm = strGenWDIR + "/postrm";
-  if(this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTINST"))
-    {
+  if (this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTINST")) {
     cmGeneratedFileStream out(postinst.c_str());
-     out <<
-       "#!/bin/sh\n\n"
-       "set -e\n\n"
-       "if [ \"$1\" = \"configure\" ]; then\n"
-       "\tldconfig\n"
-       "fi\n";
-    }
-  if(this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTRM"))
-    {
+    out << "#!/bin/sh\n\n"
+           "set -e\n\n"
+           "if [ \"$1\" = \"configure\" ]; then\n"
+           "\tldconfig\n"
+           "fi\n";
+  }
+  if (this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTRM")) {
     cmGeneratedFileStream out(postrm.c_str());
-    out <<
-      "#!/bin/sh\n\n"
-      "set -e\n\n"
-      "if [ \"$1\" = \"remove\" ]; then\n"
-      "\tldconfig\n"
-      "fi\n";
-    }
+    out << "#!/bin/sh\n\n"
+           "set -e\n\n"
+           "if [ \"$1\" = \"remove\" ]; then\n"
+           "\tldconfig\n"
+           "fi\n";
+  }
 
   cmArchiveWrite::Compress tar_compression_type = cmArchiveWrite::CompressGZip;
   const char* debian_compression_type =
-      this->GetOption("GEN_CPACK_DEBIAN_COMPRESSION_TYPE");
-  if(!debian_compression_type)
-    {
+    this->GetOption("GEN_CPACK_DEBIAN_COMPRESSION_TYPE");
+  if (!debian_compression_type) {
     debian_compression_type = "gzip";
-    }
+  }
 
   std::string compression_suffix;
-  if(!strcmp(debian_compression_type, "lzma")) {
-      compression_suffix = ".lzma";
-      tar_compression_type = cmArchiveWrite::CompressLZMA;
-  } else if(!strcmp(debian_compression_type, "xz")) {
-      compression_suffix = ".xz";
-      tar_compression_type = cmArchiveWrite::CompressXZ;
-  } else if(!strcmp(debian_compression_type, "bzip2")) {
-      compression_suffix = ".bz2";
-      tar_compression_type = cmArchiveWrite::CompressBZip2;
-  } else if(!strcmp(debian_compression_type, "gzip")) {
-      compression_suffix = ".gz";
-      tar_compression_type = cmArchiveWrite::CompressGZip;
-  } else if(!strcmp(debian_compression_type, "none")) {
-      compression_suffix = "";
-      tar_compression_type = cmArchiveWrite::CompressNone;
+  if (!strcmp(debian_compression_type, "lzma")) {
+    compression_suffix = ".lzma";
+    tar_compression_type = cmArchiveWrite::CompressLZMA;
+  } else if (!strcmp(debian_compression_type, "xz")) {
+    compression_suffix = ".xz";
+    tar_compression_type = cmArchiveWrite::CompressXZ;
+  } else if (!strcmp(debian_compression_type, "bzip2")) {
+    compression_suffix = ".bz2";
+    tar_compression_type = cmArchiveWrite::CompressBZip2;
+  } else if (!strcmp(debian_compression_type, "gzip")) {
+    compression_suffix = ".gz";
+    tar_compression_type = cmArchiveWrite::CompressGZip;
+  } else if (!strcmp(debian_compression_type, "none")) {
+    compression_suffix = "";
+    tar_compression_type = cmArchiveWrite::CompressNone;
   } else {
-      cmCPackLogger(cmCPackLog::LOG_ERROR,
-                    "Error unrecognized compression type: "
+    cmCPackLogger(cmCPackLog::LOG_ERROR,
+                  "Error unrecognized compression type: "
                     << debian_compression_type << std::endl);
   }
 
-
-  std::string filename_data_tar = strGenWDIR
-      + "/data.tar" + compression_suffix;
+  std::string filename_data_tar =
+    strGenWDIR + "/data.tar" + compression_suffix;
 
   // atomic file generation for data.tar
   {
     cmGeneratedFileStream fileStream_data_tar;
     fileStream_data_tar.Open(filename_data_tar.c_str(), false, true);
-    if(!fileStream_data_tar)
-      {
-      cmCPackLogger(cmCPackLog::LOG_ERROR,
-          "Error opening the file \"" << filename_data_tar << "\" for writing"
-          << std::endl);
+    if (!fileStream_data_tar) {
+      cmCPackLogger(cmCPackLog::LOG_ERROR, "Error opening the file \""
+                      << filename_data_tar << "\" for writing" << std::endl);
       return 0;
-      }
+    }
     cmArchiveWrite data_tar(fileStream_data_tar, tar_compression_type, "paxr");
 
     // uid/gid should be the one of the root user, and this root user has
@@ -495,81 +448,69 @@ int cmCPackDebGenerator::createDeb()
     // give /usr and /opt
     size_t topLevelLength = strGenWDIR.length();
     cmCPackLogger(cmCPackLog::LOG_DEBUG, "WDIR: \""
-            << strGenWDIR
-            << "\", length = " << topLevelLength
-            << std::endl);
+                    << strGenWDIR << "\", length = " << topLevelLength
+                    << std::endl);
     std::set<std::string> orderedFiles;
 
     // we have to reconstruct the parent folders as well
 
     for (std::vector<std::string>::const_iterator fileIt =
-         packageFiles.begin();
-         fileIt != packageFiles.end(); ++ fileIt )
-      {
+           packageFiles.begin();
+         fileIt != packageFiles.end(); ++fileIt) {
       std::string currentPath = *fileIt;
-      while(currentPath != strGenWDIR)
-        {
+      while (currentPath != strGenWDIR) {
         // the last one IS strGenWDIR, but we do not want this one:
         // XXX/application/usr/bin/myprogram with GEN_WDIR=XXX/application
         // should not add XXX/application
         orderedFiles.insert(currentPath);
         currentPath = cmSystemTools::CollapseCombinedPath(currentPath, "..");
-        }
       }
+    }
 
-
-    for (std::set<std::string>::const_iterator fileIt =
-         orderedFiles.begin();
-         fileIt != orderedFiles.end(); ++ fileIt )
-      {
+    for (std::set<std::string>::const_iterator fileIt = orderedFiles.begin();
+         fileIt != orderedFiles.end(); ++fileIt) {
       cmCPackLogger(cmCPackLog::LOG_DEBUG, "FILEIT: \"" << *fileIt << "\""
-                    << std::endl);
-      std::string::size_type slashPos = fileIt->find('/', topLevelLength+1);
-      std::string relativeDir = fileIt->substr(topLevelLength,
-                                               slashPos - topLevelLength);
-      cmCPackLogger(cmCPackLog::LOG_DEBUG, "RELATIVEDIR: \"" << relativeDir
-                    << "\"" << std::endl);
+                                                        << std::endl);
+      std::string::size_type slashPos = fileIt->find('/', topLevelLength + 1);
+      std::string relativeDir =
+        fileIt->substr(topLevelLength, slashPos - topLevelLength);
+      cmCPackLogger(cmCPackLog::LOG_DEBUG, "RELATIVEDIR: \""
+                      << relativeDir << "\"" << std::endl);
 
       // do not recurse because the loop will do it
-      if(!data_tar.Add(*fileIt, topLevelLength, ".", false))
-        {
-        cmCPackLogger(cmCPackLog::LOG_ERROR,
-                      "Problem adding file to tar:" << std::endl
-                      << "#top level directory: "
-                      << strGenWDIR << std::endl
-                      << "#file: " << *fileIt << std::endl
-                      << "#error:" << data_tar.GetError() << std::endl);
+      if (!data_tar.Add(*fileIt, topLevelLength, ".", false)) {
+        cmCPackLogger(cmCPackLog::LOG_ERROR, "Problem adding file to tar:"
+                        << std::endl
+                        << "#top level directory: " << strGenWDIR << std::endl
+                        << "#file: " << *fileIt << std::endl
+                        << "#error:" << data_tar.GetError() << std::endl);
         return 0;
-        }
       }
+    }
   } // scope for file generation
 
-
   std::string md5filename = strGenWDIR + "/md5sums";
   {
     // the scope is needed for cmGeneratedFileStream
     cmGeneratedFileStream out(md5filename.c_str());
 
     std::string topLevelWithTrailingSlash =
-        this->GetOption("CPACK_TEMPORARY_DIRECTORY");
+      this->GetOption("CPACK_TEMPORARY_DIRECTORY");
     topLevelWithTrailingSlash += '/';
     for (std::vector<std::string>::const_iterator fileIt =
            packageFiles.begin();
-         fileIt != packageFiles.end(); ++ fileIt )
-      {
+         fileIt != packageFiles.end(); ++fileIt) {
       // hash only regular files
-      if(   cmSystemTools::FileIsDirectory(*fileIt)
-         || cmSystemTools::FileIsSymlink(*fileIt))
-        {
+      if (cmSystemTools::FileIsDirectory(*fileIt) ||
+          cmSystemTools::FileIsSymlink(*fileIt)) {
         continue;
-        }
+      }
 
       char md5sum[33];
-      if(!cmSystemTools::ComputeFileMD5(*fileIt, md5sum))
-        {
+      if (!cmSystemTools::ComputeFileMD5(*fileIt, md5sum)) {
         cmCPackLogger(cmCPackLog::LOG_ERROR, "Problem computing the md5 of "
-                      << *fileIt << std::endl);
-        }
+                        << *fileIt << std::endl);
+      }
 
       md5sum[32] = 0;
 
@@ -578,31 +519,27 @@ int cmCPackDebGenerator::createDeb()
       // debian md5sums entries are like this:
       // 014f3604694729f3bf19263bac599765  usr/bin/ccmake
       // thus strip the full path (with the trailing slash)
-      cmSystemTools::ReplaceString(output,
-                                   topLevelWithTrailingSlash.c_str(), "");
+      cmSystemTools::ReplaceString(output, topLevelWithTrailingSlash.c_str(),
+                                   "");
       out << output;
-      }
+    }
     // each line contains a eol.
     // Do not end the md5sum file with yet another (invalid)
   }
 
-
-
   std::string filename_control_tar = strGenWDIR + "/control.tar.gz";
   // atomic file generation for control.tar
   {
     cmGeneratedFileStream fileStream_control_tar;
     fileStream_control_tar.Open(filename_control_tar.c_str(), false, true);
-    if(!fileStream_control_tar)
-      {
-      cmCPackLogger(cmCPackLog::LOG_ERROR,
-          "Error opening the file \"" << filename_control_tar
-          << "\" for writing" << std::endl);
+    if (!fileStream_control_tar) {
+      cmCPackLogger(cmCPackLog::LOG_ERROR, "Error opening the file \""
+                      << filename_control_tar << "\" for writing"
+                      << std::endl);
       return 0;
-      }
+    }
     cmArchiveWrite control_tar(fileStream_control_tar,
-                               cmArchiveWrite::CompressGZip,
-                               "paxr");
+                               cmArchiveWrite::CompressGZip, "paxr");
 
     // sets permissions and uid/gid for the files
     control_tar.SetUIDAndGID(0u, 0u);
@@ -623,113 +560,96 @@ int cmCPackDebGenerator::createDeb()
     control_tar.SetPermissions(permission644);
 
     // adds control and md5sums
-    if(   !control_tar.Add(md5filename, strGenWDIR.length(), ".")
-       || !control_tar.Add(strGenWDIR + "/control", strGenWDIR.length(), "."))
-      {
-        cmCPackLogger(cmCPackLog::LOG_ERROR,
-            "Error adding file to tar:" << std::endl
-            << "#top level directory: "
-               << strGenWDIR << std::endl
-            << "#file: \"control\" or \"md5sums\"" << std::endl
-            << "#error:" << control_tar.GetError() << std::endl);
-        return 0;
-      }
+    if (!control_tar.Add(md5filename, strGenWDIR.length(), ".") ||
+        !control_tar.Add(strGenWDIR + "/control", strGenWDIR.length(), ".")) {
+      cmCPackLogger(cmCPackLog::LOG_ERROR, "Error adding file to tar:"
+                      << std::endl
+                      << "#top level directory: " << strGenWDIR << std::endl
+                      << "#file: \"control\" or \"md5sums\"" << std::endl
+                      << "#error:" << control_tar.GetError() << std::endl);
+      return 0;
+    }
 
     // adds generated shlibs file
-    if( gen_shibs )
-      {
-      if( !control_tar.Add(shlibsfilename, strGenWDIR.length(), ".") )
-        {
-          cmCPackLogger(cmCPackLog::LOG_ERROR,
-              "Error adding file to tar:" << std::endl
-              << "#top level directory: "
-                 << strGenWDIR << std::endl
-              << "#file: \"shlibs\"" << std::endl
-              << "#error:" << control_tar.GetError() << std::endl);
-          return 0;
-        }
+    if (gen_shibs) {
+      if (!control_tar.Add(shlibsfilename, strGenWDIR.length(), ".")) {
+        cmCPackLogger(cmCPackLog::LOG_ERROR, "Error adding file to tar:"
+                        << std::endl
+                        << "#top level directory: " << strGenWDIR << std::endl
+                        << "#file: \"shlibs\"" << std::endl
+                        << "#error:" << control_tar.GetError() << std::endl);
+        return 0;
       }
+    }
 
     // adds LDCONFIG related files
-    if(this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTINST"))
-      {
+    if (this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTINST")) {
       control_tar.SetPermissions(permission755);
-      if(!control_tar.Add(postinst, strGenWDIR.length(), "."))
-        {
-          cmCPackLogger(cmCPackLog::LOG_ERROR,
-              "Error adding file to tar:" << std::endl
-              << "#top level directory: "
-                 << strGenWDIR << std::endl
-              << "#file: \"postinst\"" << std::endl
-              << "#error:" << control_tar.GetError() << std::endl);
-          return 0;
-        }
-      control_tar.SetPermissions(permission644);
+      if (!control_tar.Add(postinst, strGenWDIR.length(), ".")) {
+        cmCPackLogger(cmCPackLog::LOG_ERROR, "Error adding file to tar:"
+                        << std::endl
+                        << "#top level directory: " << strGenWDIR << std::endl
+                        << "#file: \"postinst\"" << std::endl
+                        << "#error:" << control_tar.GetError() << std::endl);
+        return 0;
       }
+      control_tar.SetPermissions(permission644);
+    }
 
-    if(this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTRM"))
-      {
+    if (this->IsOn("GEN_CPACK_DEBIAN_GENERATE_POSTRM")) {
       control_tar.SetPermissions(permission755);
-      if(!control_tar.Add(postrm, strGenWDIR.length(), "."))
-        {
-          cmCPackLogger(cmCPackLog::LOG_ERROR,
-              "Error adding file to tar:" << std::endl
-              << "#top level directory: "
-                 << strGenWDIR << std::endl
-              << "#file: \"postinst\"" << std::endl
-              << "#error:" << control_tar.GetError() << std::endl);
-          return 0;
-        }
-      control_tar.SetPermissions(permission644);
+      if (!control_tar.Add(postrm, strGenWDIR.length(), ".")) {
+        cmCPackLogger(cmCPackLog::LOG_ERROR, "Error adding file to tar:"
+                        << std::endl
+                        << "#top level directory: " << strGenWDIR << std::endl
+                        << "#file: \"postinst\"" << std::endl
+                        << "#error:" << control_tar.GetError() << std::endl);
+        return 0;
       }
+      control_tar.SetPermissions(permission644);
+    }
 
     // for the other files, we use
     // -either the original permission on the files
     // -either a permission strictly defined by the Debian policies
     const char* controlExtra =
       this->GetOption("GEN_CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA");
-    if( controlExtra )
-      {
+    if (controlExtra) {
       // permissions are now controlled by the original file permissions
 
       const bool permissionStrictPolicy =
         this->IsSet("GEN_CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION");
 
-      static const char* strictFiles[] = {
-        "config", "postinst", "postrm", "preinst", "prerm"
-        };
+      static const char* strictFiles[] = { "config", "postinst", "postrm",
+                                           "preinst", "prerm" };
       std::set<std::string> setStrictFiles(
         strictFiles,
-        strictFiles + sizeof(strictFiles)/sizeof(strictFiles[0]));
+        strictFiles + sizeof(strictFiles) / sizeof(strictFiles[0]));
 
       // default
       control_tar.ClearPermissions();
 
       std::vector<std::string> controlExtraList;
       cmSystemTools::ExpandListArgument(controlExtra, controlExtraList);
-      for(std::vector<std::string>::iterator i = controlExtraList.begin();
-          i != controlExtraList.end(); ++i)
-        {
-        std::string filenamename =
-          cmsys::SystemTools::GetFilenameName(*i);
+      for (std::vector<std::string>::iterator i = controlExtraList.begin();
+           i != controlExtraList.end(); ++i) {
+        std::string filenamename = cmsys::SystemTools::GetFilenameName(*i);
         std::string localcopy = strGenWDIR + "/" + filenamename;
 
-        if(permissionStrictPolicy)
-          {
-          control_tar.SetPermissions(setStrictFiles.count(filenamename) ?
-            permission755 : permission644);
-          }
+        if (permissionStrictPolicy) {
+          control_tar.SetPermissions(setStrictFiles.count(filenamename)
+                                       ? permission755
+                                       : permission644);
+        }
 
         // if we can copy the file, it means it does exist, let's add it:
-        if( cmsys::SystemTools::CopyFileIfDifferent(*i, localcopy) )
-          {
+        if (cmsys::SystemTools::CopyFileIfDifferent(*i, localcopy)) {
           control_tar.Add(localcopy, strGenWDIR.length(), ".");
-          }
         }
       }
+    }
   }
 
-
   // ar -r your-package-name.deb debian-binary control.tar.* data.tar.*
   // since debian packages require BSD ar (most Linux distros and even
   // FreeBSD and NetBSD ship GNU ar) we use a copy of OpenBSD ar here.
@@ -742,33 +662,29 @@ int cmCPackDebGenerator::createDeb()
   outputFileName += "/";
   outputFileName += this->GetOption("GEN_CPACK_OUTPUT_FILE_NAME");
   int res = ar_append(outputFileName.c_str(), arFiles);
-  if ( res!=0 )
-    {
-    std::string tmpFile = this->GetOption(
-        "GEN_CPACK_TEMPORARY_PACKAGE_FILE_NAME");
+  if (res != 0) {
+    std::string tmpFile =
+      this->GetOption("GEN_CPACK_TEMPORARY_PACKAGE_FILE_NAME");
     tmpFile += "/Deb.log";
     cmGeneratedFileStream ofs(tmpFile.c_str());
     ofs << "# Problem creating archive using: " << res << std::endl;
     return 0;
-    }
+  }
   return 1;
 }
 
 bool cmCPackDebGenerator::SupportsComponentInstallation() const
-  {
-  if (IsOn("CPACK_DEB_COMPONENT_INSTALL"))
-    {
-      return true;
-    }
-  else
-    {
-      return false;
-    }
+{
+  if (IsOn("CPACK_DEB_COMPONENT_INSTALL")) {
+    return true;
+  } else {
+    return false;
   }
+}
 
 std::string cmCPackDebGenerator::GetComponentInstallDirNameSuffix(
-    const std::string& componentName)
-  {
+  const std::string& componentName)
+{
   if (componentPackageMethod == ONE_PACKAGE_PER_COMPONENT) {
     return componentName;
   }
@@ -778,18 +694,14 @@ std::string cmCPackDebGenerator::GetComponentInstallDirNameSuffix(
   }
   // We have to find the name of the COMPONENT GROUP
   // the current COMPONENT belongs to.
-  std::string groupVar = "CPACK_COMPONENT_" +
-        cmSystemTools::UpperCase(componentName) + "_GROUP";
-    if (NULL != GetOption(groupVar))
-      {
-      return std::string(GetOption(groupVar));
-      }
-    else
-      {
-      return componentName;
-      }
+  std::string groupVar =
+    "CPACK_COMPONENT_" + cmSystemTools::UpperCase(componentName) + "_GROUP";
+  if (NULL != GetOption(groupVar)) {
+    return std::string(GetOption(groupVar));
+  } else {
+    return componentName;
   }
-
+}
 
 // The following code is taken from OpenBSD ar:
 // http://www.openbsd.org/cgi-bin/cvsweb/src/usr.bin/ar/
@@ -840,58 +752,61 @@ std::string cmCPackDebGenerator::GetComponentInstallDirNameSuffix(
 #include <stdlib.h>
 #include <string.h>
 
-#define ARMAG           "!<arch>\n"        /* ar "magic number" */
-#define SARMAG          8                  /* strlen(ARMAG); */
+#define ARMAG "!<arch>\n" /* ar "magic number" */
+#define SARMAG 8          /* strlen(ARMAG); */
 
-#define AR_EFMT1        "#1/"              /* extended format #1 */
-#define ARFMAG          "`\n"
+#define AR_EFMT1 "#1/" /* extended format #1 */
+#define ARFMAG "`\n"
 
 /* Header format strings. */
-#define HDR1            "%s%-13d%-12ld%-6u%-6u%-8o%-10lld%2s"
-#define HDR2             "%-16.16s%-12ld%-6u%-6u%-8o%-10lld%2s"
-
-struct ar_hdr {
-  char ar_name[16];                        /* name */
-  char ar_date[12];                        /* modification time */
-  char ar_uid[6];                          /* user id */
-  char ar_gid[6];                          /* group id */
-  char ar_mode[8];                         /* octal file permissions */
-  char ar_size[10];                        /* size in bytes */
-  char ar_fmag[2];                         /* consistency check */
+#define HDR1 "%s%-13d%-12ld%-6u%-6u%-8o%-10lld%2s"
+#define HDR2 "%-16.16s%-12ld%-6u%-6u%-8o%-10lld%2s"
+
+struct ar_hdr
+{
+  char ar_name[16]; /* name */
+  char ar_date[12]; /* modification time */
+  char ar_uid[6];   /* user id */
+  char ar_gid[6];   /* group id */
+  char ar_mode[8];  /* octal file permissions */
+  char ar_size[10]; /* size in bytes */
+  char ar_fmag[2];  /* consistency check */
 };
 
 /* Set up file copy. */
-#define SETCF(from, fromname, to, toname, pad) { \
-        cf.rFile = from; \
-        cf.rname = fromname; \
-        cf.wFile = to; \
-        cf.wname = toname; \
-        cf.flags = pad; \
-}
+#define SETCF(from, fromname, to, toname, pad)                                \
+  {                                                                           \
+    cf.rFile = from;                                                          \
+    cf.rname = fromname;                                                      \
+    cf.wFile = to;                                                            \
+    cf.wname = toname;                                                        \
+    cf.flags = pad;                                                           \
+  }
 
 /* File copy structure. */
-typedef struct {
-        FILE* rFile;                       /* read file descriptor */
-        const char *rname;                 /* read name */
-        FILE* wFile;                       /* write file descriptor */
-        const char *wname;                 /* write name */
-#define NOPAD        0x00                  /* don't pad */
-#define WPAD        0x02                   /* pad on writes */
-        unsigned int flags;                       /* pad flags */
+typedef struct
+{
+  FILE* rFile;        /* read file descriptor */
+  const char* rname;  /* read name */
+  FILE* wFile;        /* write file descriptor */
+  const char* wname;  /* write name */
+#define NOPAD 0x00    /* don't pad */
+#define WPAD 0x02     /* pad on writes */
+  unsigned int flags; /* pad flags */
 } CF;
 
 /* misc.c */
 
-static const char * ar_rname(const char *path)
+static const char* ar_rname(const char* path)
 {
-  const char *ind = strrchr(path, '/');
-  return (ind ) ? ind + 1 : path;
+  const char* ind = strrchr(path, '/');
+  return (ind) ? ind + 1 : path;
 }
 
 /* archive.c */
 
 typedef struct ar_hdr HDR;
-static char ar_hb[sizeof(HDR) + 1];        /* real header */
+static char ar_hb[sizeof(HDR) + 1]; /* real header */
 
 static size_t ar_already_written;
 
@@ -908,73 +823,72 @@ static size_t ar_already_written;
  *      because 16-bit word addressed copies were faster?)  Anyhow, it should
  *      have been ripped out long ago.
  */
-static int copy_ar(CF *cfp, off_t size)
+static int copy_ar(CF* cfp, off_t size)
 {
   static char pad = '\n';
   off_t sz = size;
   size_t nr, nw;
-  char buf[8*1024];
+  char buf[8 * 1024];
 
   if (sz == 0)
     return 0;
 
   FILE* from = cfp->rFile;
   FILE* to = cfp->wFile;
   while (sz &&
-        (nr = fread(buf, 1, sz < static_cast<off_t>(sizeof(buf))
-                    ? static_cast<size_t>(sz) : sizeof(buf), from ))
-               > 0) {
+         (nr = fread(buf, 1, sz < static_cast<off_t>(sizeof(buf))
+                       ? static_cast<size_t>(sz)
+                       : sizeof(buf),
+                     from)) > 0) {
     sz -= nr;
     for (size_t off = 0; off < nr; nr -= off, off += nw)
       if ((nw = fwrite(buf + off, 1, nr, to)) < nr)
         return -1;
-    }
+  }
   if (sz)
     return -2;
 
-  if (cfp->flags & WPAD && (size + ar_already_written) & 1
-      && fwrite(&pad, 1, 1, to) != 1)
+  if (cfp->flags & WPAD && (size + ar_already_written) & 1 &&
+      fwrite(&pad, 1, 1, to) != 1)
     return -4;
 
   return 0;
 }
 
 /* put_arobj --  Write an archive member to a file. */
-static int put_arobj(CF *cfp, struct stat *sb)
+static int put_arobj(CF* cfp, struct stat* sb)
 {
   int result = 0;
-  struct ar_hdr *hdr;
+  struct ar_hdr* hdr;
 
- /* If passed an sb structure, reading a file from disk.  Get stat(2)
-  * information, build a name and construct a header.  (Files are named
-  * by their last component in the archive.) */
+  /* If passed an sb structure, reading a file from disk.  Get stat(2)
+   * information, build a name and construct a header.  (Files are named
+   * by their last component in the archive.) */
   const char* name = ar_rname(cfp->rname);
   (void)stat(cfp->rname, sb);
 
- /* If not truncating names and the name is too long or contains
-  * a space, use extended format 1.   */
+  /* If not truncating names and the name is too long or contains
+   * a space, use extended format 1.   */
   size_t lname = strlen(name);
   uid_t uid = sb->st_uid;
   gid_t gid = sb->st_gid;
   if (uid > USHRT_MAX) {
     uid = USHRT_MAX;
-    }
+  }
   if (gid > USHRT_MAX) {
     gid = USHRT_MAX;
-    }
+  }
   if (lname > sizeof(hdr->ar_name) || strchr(name, ' '))
-    (void)sprintf(ar_hb, HDR1, AR_EFMT1, (int)lname,
-                  (long int)sb->st_mtime, (unsigned)uid, (unsigned)gid,
-                  (unsigned)sb->st_mode, (long long)sb->st_size + lname,
+    (void)sprintf(ar_hb, HDR1, AR_EFMT1, (int)lname, (long int)sb->st_mtime,
+                  (unsigned)uid, (unsigned)gid, (unsigned)sb->st_mode,
+                  (long long)sb->st_size + lname, ARFMAG);
+  else {
+    lname = 0;
+    (void)sprintf(ar_hb, HDR2, name, (long int)sb->st_mtime, (unsigned)uid,
+                  (unsigned)gid, (unsigned)sb->st_mode, (long long)sb->st_size,
                   ARFMAG);
-    else {
-      lname = 0;
-      (void)sprintf(ar_hb, HDR2, name,
-                    (long int)sb->st_mtime, (unsigned)uid, (unsigned)gid,
-                    (unsigned)sb->st_mode, (long long)sb->st_size,
-                    ARFMAG);
-      }
-    off_t size = sb->st_size;
+  }
+  off_t size = sb->st_size;
 
   if (fwrite(ar_hb, 1, sizeof(HDR), cfp->wFile) != sizeof(HDR))
     return -1;
@@ -983,7 +897,7 @@ static int put_arobj(CF *cfp, struct stat *sb)
     if (fwrite(name, 1, lname, cfp->wFile) != lname)
       return -2;
     ar_already_written = lname;
-    }
+  }
   result = copy_ar(cfp, size);
   ar_already_written = 0;
   return result;
@@ -995,42 +909,41 @@ static int put_arobj(CF *cfp, struct stat *sb)
  *      Append files to the archive - modifies original archive or creates
  *      a new archive if named archive does not exist.
  */
-static int ar_append(const char* archive,const std::vector<std::string>& files)
+static int ar_append(const char* archive,
+                     const std::vector<std::string>& files)
 {
   int eval = 0;
   FILE* aFile = cmSystemTools::Fopen(archive, "wb+");
-  if (aFile!=NULL) {
+  if (aFile != NULL) {
     fwrite(ARMAG, SARMAG, 1, aFile);
     if (fseek(aFile, 0, SEEK_END) != -1) {
       CF cf;
       struct stat sb;
       /* Read from disk, write to an archive; pad on write. */
       SETCF(NULL, 0, aFile, archive, WPAD);
-      for(std::vector<std::string>::const_iterator fileIt = files.begin();
-          fileIt!=files.end(); ++fileIt) {
+      for (std::vector<std::string>::const_iterator fileIt = files.begin();
+           fileIt != files.end(); ++fileIt) {
         const char* filename = fileIt->c_str();
         FILE* file = cmSystemTools::Fopen(filename, "rb");
         if (file == NULL) {
           eval = -1;
           continue;
-          }
+        }
         cf.rFile = file;
         cf.rname = filename;
         int result = put_arobj(&cf, &sb);
         (void)fclose(file);
-        if (result!=0) {
+        if (result != 0) {
           eval = -2;
           break;
-          }
         }
       }
-      else {
-        eval = -3;
-      }
-    fclose(aFile);
+    } else {
+      eval = -3;
     }
-  else {
+    fclose(aFile);
+  } else {
     eval = -4;
-    }
+  }
   return eval;
 }