@@ -293,15 +293,15 @@ int cmCPackDebGenerator::createDeb()
 
   // debian policy enforce lower case for package name
   // mandatory entries:
-  std::string debian_pkg_name = cmsys::SystemTools::LowerCase( 
+  std::string debian_pkg_name = cmsys::SystemTools::LowerCase(
                                 this->GetOption("CPACK_DEBIAN_PACKAGE_NAME") );
-  const char* debian_pkg_version = 
+  const char* debian_pkg_version =
                                this->GetOption("CPACK_DEBIAN_PACKAGE_VERSION");
-  const char* debian_pkg_section = 
+  const char* debian_pkg_section =
                                this->GetOption("CPACK_DEBIAN_PACKAGE_SECTION");
-  const char* debian_pkg_priority = 
+  const char* debian_pkg_priority =
                               this->GetOption("CPACK_DEBIAN_PACKAGE_PRIORITY");
-  const char* debian_pkg_arch = 
+  const char* debian_pkg_arch =
                           this->GetOption("CPACK_DEBIAN_PACKAGE_ARCHITECTURE");
   const char* maintainer =  this->GetOption("CPACK_DEBIAN_PACKAGE_MAINTAINER");
   const char* desc =       this->GetOption("CPACK_DEBIAN_PACKAGE_DESCRIPTION");
@@ -719,8 +719,8 @@ static int copy_ar(CF *cfp, off_t size)
 
   FILE* from = cfp->rFile;
   FILE* to = cfp->wFile;
-  while (sz && 
-        (nr = fread(buf, 1, sz < static_cast<off_t>(sizeof(buf)) 
+  while (sz &&
+        (nr = fread(buf, 1, sz < static_cast<off_t>(sizeof(buf))
                     ? static_cast<size_t>(sz) : sizeof(buf), from ))
                > 0) {
     sz -= nr;
@@ -731,7 +731,7 @@ static int copy_ar(CF *cfp, off_t size)
   if (sz)
     return -2;
 
-  if (cfp->flags & WPAD && (size + ar_already_written) & 1 
+  if (cfp->flags & WPAD && (size + ar_already_written) & 1
       && fwrite(&pad, 1, 1, to) != 1)
     return -4;
 
@@ -767,8 +767,8 @@ static int put_arobj(CF *cfp, struct stat *sb)
                   (long long)sb->st_size + lname, ARFMAG);
     else {
       lname = 0;
-      (void)sprintf(ar_hb, HDR2, name, 
-                    (long int)sb->st_mtime, uid, gid, sb->st_mode, 
+      (void)sprintf(ar_hb, HDR2, name,
+                    (long int)sb->st_mtime, uid, gid, sb->st_mode,
                     (long long)sb->st_size, ARFMAG);
       }
     off_t size = sb->st_size;
@@ -790,7 +790,7 @@ static int put_arobj(CF *cfp, struct stat *sb)
 
 /* append --
  *      Append files to the archive - modifies original archive or creates
- *      a new archive if named archive does not exist. 
+ *      a new archive if named archive does not exist.
  */
 static int ar_append(const char* archive,const std::vector<std::string>& files)
 {