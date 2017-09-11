@@ -308,7 +308,7 @@ static int cliSelect() {
     return REDIS_ERR;
 }
 
-/* Connect to the client. If force is not zero the connection is performed
+/* Connect to the server. If force is not zero the connection is performed
  * even if there is already a connected socket. */
 static int cliConnect(int force) {
     if (context == NULL || force) {
@@ -976,7 +976,7 @@ static void slaveMode(void) {
     char buf[1024];
 
     fprintf(stderr,"SYNC with master, discarding %llu "
-                   "bytes of bulk tranfer...\n", payload);
+                   "bytes of bulk transfer...\n", payload);
 
     /* Discard the payload. */
     while(payload) {
@@ -1141,7 +1141,7 @@ static void pipeMode(void) {
                         int j;
 
                         eof = 1;
-                        /* Everything transfered, so we queue a special
+                        /* Everything transferred, so we queue a special
                          * ECHO command that we can match in the replies
                          * to make sure everything was read from the server. */
                         for (j = 0; j < 20; j++)