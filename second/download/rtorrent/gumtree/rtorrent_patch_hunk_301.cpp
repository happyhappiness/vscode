       if (m_logFd != -1) {
         write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
         write(m_logFd, m_capture.data(), m_capture.length());
       }
     }
 
+    if (flags & flag_background) {
+      if (m_logFd != -1)
+        write(m_logFd, "\n--- Background task ---\n", sizeof("\n--- Background task ---\n"));
+        
+      return 0;
+    }
+
     int status;
-    int wpid = waitpid(childPid, &status, 0);
+    int wpid;
 
-    while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr)
+    do {
       wpid = waitpid(childPid, &status, 0);
+    } while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr);
 
     if (wpid != childPid)
       throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");
 
     // Check return value?
     if (m_logFd != -1) {
