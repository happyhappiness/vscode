  \param argc Ignored.
  \param argv Ignored.
  \retval ERR An error occured removing the file.
  \retval OK  The file has been removed.
  */
 int
-main(int argc, char *argv[])
+main(int, char *[])
 {
-    char buf[UNLINK_BUF_LEN];
-    char *t;
-    int x;
-    setbuf(stdin, NULL);
-    setbuf(stdout, NULL);
+    std::string sbuf;
     close(2);
     if (open(_PATH_DEVNULL, O_RDWR) < 0) {
         ; // the irony of having to close(2) earlier is that we cannot report this failure.
     }
-
-    while (fgets(buf, sizeof(buf), stdin)) {
-        if ((t = strchr(buf, '\n')))
-            *t = '\0';
-        x = unlink(buf);
-        if (x < 0)
-            printf("ERR\n");
+    while (getline(std::cin, sbuf)) {
+        // tailing newline is removed by getline
+        const int rv = remove(sbuf.c_str());
+        if (rv < 0)
+            std::cout << "ERR" << std::endl; // endl flushes
         else
-            printf("OK\n");
+            std::cout << "OK" << std::endl;
     }
 
     return 0;
 }
 
