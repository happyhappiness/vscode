       else if (values[i] == ',')
         values[i] = ':';
     }
 
     fprintf(use_stdio == 1 ? stdout : stderr, "PUTVAL %s interval=%.3f %s\n",
             filename, CDTIME_T_TO_DOUBLE(vl->interval), values);
-    return (0);
+    return 0;
   }
 
   if (stat(filename, &statbuf) == -1) {
     if (errno == ENOENT) {
       if (csv_create_file(filename, ds))
-        return (-1);
+        return -1;
     } else {
       char errbuf[1024];
       ERROR("stat(%s) failed: %s", filename,
             sstrerror(errno, errbuf, sizeof(errbuf)));
-      return (-1);
+      return -1;
     }
   } else if (!S_ISREG(statbuf.st_mode)) {
     ERROR("stat(%s): Not a regular file!", filename);
-    return (-1);
+    return -1;
   }
 
   csv = fopen(filename, "a");
   if (csv == NULL) {
     char errbuf[1024];
     ERROR("csv plugin: fopen (%s) failed: %s", filename,
           sstrerror(errno, errbuf, sizeof(errbuf)));
-    return (-1);
+    return -1;
   }
   csv_fd = fileno(csv);
 
   fl.l_pid = getpid();
   fl.l_type = F_WRLCK;
   fl.l_whence = SEEK_SET;
