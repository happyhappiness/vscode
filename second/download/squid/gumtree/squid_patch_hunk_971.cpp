         fp = popen(file_name + 1, "r");
         is_pipe = 1;
     } else {
         fp = fopen(file_name, "r");
     }
 
-    if (fp == NULL)
-        fatalf("Unable to open configuration file: %s: %s", file_name, xstrerror());
+    if (!fp) {
+        int xerrno = errno;
+        fatalf("Unable to open configuration file: %s: %s", file_name, xstrerr(xerrno));
+    }
 
 #if _SQUID_WINDOWS_
     setmode(fileno(fp), O_TEXT);
 #endif
 
     SetConfigFilename(file_name, bool(is_pipe));
