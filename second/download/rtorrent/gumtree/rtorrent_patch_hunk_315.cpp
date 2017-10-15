 
   char buf[256];
   int pos = ::gethostname(buf, 255);
 
   if (pos == 0) {
     ::snprintf(buf + std::strlen(buf), 255, ":+%i\n", ::getpid());
-    ::write(fd, buf, std::strlen(buf));
+    int __UNUSED result = ::write(fd, buf, std::strlen(buf));
   }
 
   ::close(fd);
 
   m_locked = true;
   return true;
