 
     default:
         fatalf("fd_open(): unknown FD type - FD#: %i, type: %u, desc %s\n", fd, type, desc);
     }
 
 #else
-    F->read_method = &default_read_method;
+    switch (type) {
+
+    case FD_MSGHDR:
+        F->read_method = &msghdr_read_method;
+        F->write_method = &msghdr_write_method;
+        break;
 
-    F->write_method = &default_write_method;
+    default:
+        F->read_method = &default_read_method;
+        F->write_method = &default_write_method;
+        break;
+    }
 
 #endif
 
     fdUpdateBiggest(fd, 1);
 
     if (desc)
         xstrncpy(F->desc, desc, FD_DESC_SZ);
 
-    Number_FD++;
+    ++Number_FD;
 }
 
 void
 fd_note(int fd, const char *s)
 {
     fde *F = &fd_table[fd];
