@@ -1704,7 +1704,7 @@ bool cmSystemTools::IsPathToFramework(const char* path)
 
 bool cmSystemTools::CreateTar(const char* outFileName, 
                               const std::vector<cmStdString>& files,
-                              bool gzip, bool verbose)
+                              bool gzip, bool bzip2, bool verbose)
 {
 #if defined(CMAKE_BUILD_WITH_CMAKE)  
   std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
@@ -1755,6 +1755,14 @@ bool cmSystemTools::CreateTar(const char* outFileName,
       cmSystemTools::Error("Unable to use gzip in libarchive");
       }
     } 
+  if(bzip2)
+    {
+    res = archive_write_set_compression_bzip2(a); 
+    if(res != ARCHIVE_OK)
+      {
+      cmSystemTools::Error("Unable to use bzip2 in libarchive");
+      }
+    } 
   res = archive_write_set_format_ustar(a);
   if(res != ARCHIVE_OK)
     {
@@ -1822,7 +1830,7 @@ namespace{
 #define BSDTAR_FILESIZE_PRINTF  "%lu"
 #define BSDTAR_FILESIZE_TYPE    unsigned long
   void
-list_item_verbose(FILE *out, struct archive_entry *entry)
+    list_item_verbose(FILE *out, struct archive_entry *entry)
 {
   char                   tmp[100];
   size_t                         w;
@@ -1862,7 +1870,6 @@ list_item_verbose(FILE *out, struct archive_entry *entry)
     u_width = w;
     }
   fprintf(out, "%-*s ", (int)u_width, p);
-  
   /* Use gname if it's present, else gid. */
   p = archive_entry_gname(entry);
   if (p != NULL && p[0] != '\0')
@@ -1905,7 +1912,7 @@ list_item_verbose(FILE *out, struct archive_entry *entry)
     gs_width = w+strlen(tmp)+1;
     }
   fprintf(out, "%*s", (int)(gs_width - w), tmp);
-  
+
   /* Format the time using 'ls -l' conventions. */
   tim = archive_entry_mtime(entry);
 #define HALF_YEAR (time_t)365 * 86400 / 2
@@ -1926,7 +1933,7 @@ list_item_verbose(FILE *out, struct archive_entry *entry)
   strftime(tmp, sizeof(tmp), fmt, localtime(&tim));
   fprintf(out, " %s ", tmp);
   fprintf(out, "%s", archive_entry_pathname(entry));
-  
+
   /* Extra information for links. */
   if (archive_entry_hardlink(entry)) /* Hard link */
     {
@@ -1967,7 +1974,8 @@ int copy_data(struct archive *ar, struct archive *aw)
     }
 }
 
-bool extract_tar(const char* outFileName, bool verbose, bool extract)
+bool extract_tar(const char* outFileName, bool verbose, 
+                 bool extract)
 {
   struct archive* a = archive_read_new();
   struct archive *ext = archive_write_disk_new();
@@ -2038,10 +2046,8 @@ bool extract_tar(const char* outFileName, bool verbose, bool extract)
 #endif 
 
 bool cmSystemTools::ExtractTar(const char* outFileName, 
-                               const std::vector<cmStdString>& files, 
                                bool , bool verbose)
 {
-  (void)files;
 #if defined(CMAKE_BUILD_WITH_CMAKE)
   return extract_tar(outFileName, verbose, true);
 #else
@@ -2052,11 +2058,10 @@ bool cmSystemTools::ExtractTar(const char* outFileName,
 }
 
 bool cmSystemTools::ListTar(const char* outFileName, 
-                            std::vector<cmStdString>& files, bool ,
+                            bool ,
                             bool verbose)
 {
 #if defined(CMAKE_BUILD_WITH_CMAKE)
-  (void)files;
   return extract_tar(outFileName, verbose, false);
 #else
   (void)outFileName;