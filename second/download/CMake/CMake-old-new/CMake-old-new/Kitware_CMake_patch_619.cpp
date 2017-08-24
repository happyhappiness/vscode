@@ -1379,7 +1379,7 @@ bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdSt
       | 0) == -1)
     {
     fprintf(stderr, "tar_open(): %s\n", strerror(errno));
-    return -1;
+    return false;
     }
 
   std::vector<cmStdString>::const_iterator it;
@@ -1395,22 +1395,21 @@ bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdSt
         "tar_append_tree(\"%s\", \"%s\"): %s\n", buf,
         pathname, strerror(errno));
       tar_close(t);
-      return -1;
+      return false;
       }
     }
 
   if (tar_append_eof(t) != 0)
     {
     fprintf(stderr, "tar_append_eof(): %s\n", strerror(errno));
     tar_close(t);
-    return -1;
+    return false;
     }
 
   if (tar_close(t) != 0)
     {
     fprintf(stderr, "tar_close(): %s\n", strerror(errno));
-    return -1;
+    return false;
     }
-  std::cout << "CreateTar: " << outFileName << std::endl;
-  return false;
+  return true;
 }