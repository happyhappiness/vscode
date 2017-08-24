@@ -154,6 +154,11 @@ inline const char* Getcwd(char* buf, unsigned int len)
     fprintf(stderr, "No current working directory.\n");
     abort();
     }
+  // make sure the drive letter is capital
+  if(strlen(buf) > 1 && buf[1] == ':')
+    {
+    buf[0] = toupper(buf[0]);
+    }
   return ret;
 }
 inline int Chdir(const char* dir)
@@ -2875,6 +2880,11 @@ kwsys_stl::string SystemTools::GetActualCaseForPath(const char* p)
     {
     return p;
     }
+  // make sure drive letter is always upper case
+  if(longPath.size() > 1 && longPath[1] == ':')
+    {
+    longPath[0] = toupper(longPath[0]);
+    }
   return longPath;
 #endif  
 }