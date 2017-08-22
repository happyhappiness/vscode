@@ -91,6 +91,31 @@ extern char** environ;
 # endif
 #endif
 
+#if defined(CMAKE_BUILD_WITH_CMAKE)
+static std::string
+cm_archive_entry_pathname(struct archive_entry *entry)
+{
+#if cmsys_STL_HAS_WSTRING
+  return cmsys::Encoding::ToNarrow(
+    archive_entry_pathname_w(entry)).c_str();
+#else
+  return archive_entry_pathname(entry);
+#endif
+}
+
+static int cm_archive_read_open_file(struct archive* a,
+                                     const char* file,
+                                     int block_size)
+{
+#if cmsys_STL_HAS_WSTRING
+  std::wstring wfile = cmsys::Encoding::ToWide(file);
+  return archive_read_open_filename_w(a, wfile.c_str(), block_size);
+#else
+  return archive_read_open_filename(a, file, block_size);
+#endif
+}
+#endif
+
 #ifdef _WIN32
 class cmSystemToolsWindowsHandle
 {
@@ -1581,7 +1606,7 @@ namespace{
     }
   strftime(tmp, sizeof(tmp), fmt, localtime(&tim));
   fprintf(out, " %s ", tmp);
-  fprintf(out, "%s", archive_entry_pathname(entry));
+  fprintf(out, "%s", cm_archive_entry_pathname(entry).c_str());
 
   /* Extra information for links. */
   if (archive_entry_hardlink(entry)) /* Hard link */
@@ -1641,7 +1666,7 @@ bool extract_tar(const char* outFileName, bool verbose,
   archive_read_support_compression_all(a);
   archive_read_support_format_all(a);
   struct archive_entry *entry;
-  int r = archive_read_open_file(a, outFileName, 10240);
+  int r = cm_archive_read_open_file(a, outFileName, 10240);
   if(r)
     {
     cmSystemTools::Error("Problem with archive_read_open_file(): ",
@@ -1666,7 +1691,7 @@ bool extract_tar(const char* outFileName, bool verbose,
       if(extract)
         {
         cmSystemTools::Stdout("x ");
-        cmSystemTools::Stdout(archive_entry_pathname(entry));
+        cmSystemTools::Stdout(cm_archive_entry_pathname(entry).c_str());
         }
       else
         {
@@ -1676,7 +1701,7 @@ bool extract_tar(const char* outFileName, bool verbose,
       }
     else if(!extract)
       {
-      cmSystemTools::Stdout(archive_entry_pathname(entry));
+      cmSystemTools::Stdout(cm_archive_entry_pathname(entry).c_str());
       cmSystemTools::Stdout("\n");
       }
     if(extract)
@@ -1706,7 +1731,8 @@ bool extract_tar(const char* outFileName, bool verbose,
       else if(const char* linktext = archive_entry_symlink(entry))
         {
         std::cerr << "cmake -E tar: warning: skipping symbolic link \""
-                  << archive_entry_pathname(entry) << "\" -> \""
+                  << cm_archive_entry_pathname(entry)
+                  << "\" -> \""
                   << linktext << "\"." << std::endl;
         }
 #endif
@@ -1715,7 +1741,7 @@ bool extract_tar(const char* outFileName, bool verbose,
         cmSystemTools::Error("Problem with archive_write_header(): ",
                              archive_error_string(ext));
         cmSystemTools::Error("Current file: ",
-                             archive_entry_pathname(entry));
+                             cm_archive_entry_pathname(entry).c_str());
         break;
         }
       }