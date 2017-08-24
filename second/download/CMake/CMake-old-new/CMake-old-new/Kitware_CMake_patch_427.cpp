@@ -196,18 +196,16 @@ inline int Rmdir(const char* dir)
 }
 inline const char* Getcwd(char* buf, unsigned int len)
 {
-  const char* ret = _getcwd(buf, len);
-  if(!ret)
+  if(const char* ret = _getcwd(buf, len))
     {
-    fprintf(stderr, "No current working directory.\n");
-    abort();
-    }
-  // make sure the drive letter is capital
-  if(strlen(buf) > 1 && buf[1] == ':')
-    {
-    buf[0] = toupper(buf[0]);
+    // make sure the drive letter is capital
+    if(strlen(buf) > 1 && buf[1] == ':')
+      {
+      buf[0] = toupper(buf[0]);
+      }
+    return ret;
     }
-  return ret;
+  return 0;
 }
 inline int Chdir(const char* dir)
 {
@@ -245,13 +243,7 @@ inline int Rmdir(const char* dir)
 }
 inline const char* Getcwd(char* buf, unsigned int len)
 {
-  const char* ret = getcwd(buf, len);
-  if(!ret)
-    {
-    fprintf(stderr, "No current working directory\n");
-    abort();
-    }
-  return ret;
+  return getcwd(buf, len);
 }
 
 inline int Chdir(const char* dir)
@@ -3089,7 +3081,7 @@ kwsys_stl::string SystemTools::CollapseFullPath(const char* in_path,
         }
       else
         {
-        // ??
+        base_components.push_back("");
         }
       }
 