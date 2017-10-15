     for (int i = 3, last = sysconf(_SC_OPEN_MAX); i != last; i++)
       ::close(i);
 
     int result = execvp(file, argv);
 
     _exit(result);
+  }
 
-  } else {
-    if (flags & flag_capture) {
-      m_capture = std::string();
-      ::close(pipeFd[1]);
-
-      char buffer[4096];
-      ssize_t length;
-
-      do {
-        length = read(pipeFd[0], buffer, sizeof(buffer));
-
-        if (length > 0)
-          m_capture += std::string(buffer, length);
-      } while (length > 0);
-
-      ::close(pipeFd[0]);
-
-      if (m_logFd != -1) {
-        write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
-        write(m_logFd, m_capture.data(), m_capture.length());
-      }
-    }
-
-    if (flags & flag_background) {
-      if (m_logFd != -1)
-        write(m_logFd, "\n--- Background task ---\n", sizeof("\n--- Background task ---\n"));
-        
-      return 0;
-    }
+  // We yield the global lock when waiting for the executed command to
+  // finish so that XMLRPC and other threads can continue working.
+  ThreadBase::release_global_lock();
+
+  if (flags & flag_capture) {
+    m_capture = std::string();
+    ::close(pipeFd[1]);
 
-    int status;
-    int wpid;
+    char buffer[4096];
+    ssize_t length;
 
     do {
-      wpid = waitpid(childPid, &status, 0);
-    } while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr);
+      length = read(pipeFd[0], buffer, sizeof(buffer));
+
+      if (length > 0)
+        m_capture += std::string(buffer, length);
+    } while (length > 0);
 
-    if (wpid != childPid)
-      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");
+    ::close(pipeFd[0]);
 
-    // Check return value?
     if (m_logFd != -1) {
-      if (status == 0)
-        write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
-      else
-        write(m_logFd, "\n--- Error ---\n", sizeof("\n--- Error ---\n"));
+      result = write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
+      result = write(m_logFd, m_capture.data(), m_capture.length());
     }
+  }
+
+  int status;
+  int wpid;
 
-    return status;
+  do {
+    wpid = waitpid(childPid, &status, 0);
+  } while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr);
+
+  ThreadBase::acquire_global_lock();
+
+  if (wpid != childPid)
+    throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");
+
+  // Check return value?
+  if (m_logFd != -1) {
+    if (status == 0)
+      result = write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
+    else
+      result = write(m_logFd, "\n--- Error ---\n", sizeof("\n--- Error ---\n"));
   }
+
+  return status;
 }
 
 torrent::Object
 ExecFile::execute_object(const torrent::Object& rawArgs, int flags) {
   char*  argsBuffer[max_args];
   char** argsCurrent = argsBuffer;
