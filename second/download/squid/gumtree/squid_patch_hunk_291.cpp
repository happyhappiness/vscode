         str += l;
 
         switch (*str) {
 
         case '\n':
             mb->append("\\n", 2);
-            str++;
+            ++str;
             break;
 
         case '\r':
             mb->append("\\r", 2);
-            str++;
+            ++str;
             break;
 
         case '\0':
             break;
 
         default:
             mb->append("\\", 1);
             mb->append(str, 1);
-            str++;
+            ++str;
             break;
         }
     }
 
     if (quoted)
         mb->append("\"", 1);
 }
 
 void
 keepCapabilities(void)
 {
-#if HAVE_PRCTL && defined(PR_SET_KEEPCAPS) && USE_LIBCAP
+#if USE_LIBCAP && HAVE_PRCTL && defined(PR_SET_KEEPCAPS)
 
     if (prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0)) {
-        IpInterceptor.StopTransparency("capability setting has failed.");
+        Ip::Interceptor.StopTransparency("capability setting has failed.");
     }
 #endif
 }
 
 static void
 restoreCapabilities(int keep)
