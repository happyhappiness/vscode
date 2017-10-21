 extern int do_compression;
 
 
 /* non-compressing recv token */
 static int simple_recv_token(int f,char **data)
 {
-  static int residue = 0;
-  static char *buf = NULL;
+  static int residue;
+  static char *buf;
   int n;
 
   if (!buf) {
     buf = (char *)malloc(CHUNK_SIZE);
     if (!buf) out_of_memory("simple_recv_token");
   }
