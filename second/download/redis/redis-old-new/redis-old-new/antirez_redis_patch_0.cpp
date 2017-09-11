@@ -1807,6 +1807,7 @@ static void getRDB(void) {
     }
     close(s); /* Close the file descriptor ASAP as fsync() may take time. */
     fsync(fd);
+    close(fd);
     fprintf(stderr,"Transfer finished with success.\n");
     exit(0);
 }