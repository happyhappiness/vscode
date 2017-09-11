@@ -1009,7 +1009,7 @@ static void pipeMode(void) {
             /* Read from socket and feed the hiredis reader. */
             do {
                 nread = read(fd,ibuf,sizeof(ibuf));
-                if (nread == -1 && errno != EAGAIN) {
+                if (nread == -1 && errno != EAGAIN && errno != EINTR) {
                     fprintf(stderr, "Error reading from the server: %s\n",
                         strerror(errno));
                     exit(1);
@@ -1052,7 +1052,7 @@ static void pipeMode(void) {
                     ssize_t nwritten = write(fd,obuf+obuf_pos,obuf_len);
                     
                     if (nwritten == -1) {
-                        if (errno != EAGAIN) {
+                        if (errno != EAGAIN && errno != EINTR) {
                             fprintf(stderr, "Error writing to the server: %s\n",
                                 strerror(errno));
                             exit(1);