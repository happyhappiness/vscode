     BOOL Done = FALSE;
 
 try_again:
     if (fgets(buf, HELPER_INPUT_BUFFER, stdin))
         return 0;
 
-    c = memchr(buf, '\n', HELPER_INPUT_BUFFER);		/* safer against overrun than strchr */
+    c = static_cast<char*>(memchr(buf, '\n', HELPER_INPUT_BUFFER));
     if (c) {
         if (oversized) {
             SEND("BH illegal request received");
             fprintf(stderr, "ERROR: Illegal request received: '%s'\n", buf);
             return 1;
         }
