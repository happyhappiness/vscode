@@ -255,10 +255,8 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
          * have a connected socket. Let's return to the caller. */
         goto end;
     }
-    if (p == NULL) {
+    if (p == NULL)
         anetSetError(err, "creating socket: %s", strerror(errno));
-        goto error;
-    }
 
 error:
     if (s != ANET_ERR) {