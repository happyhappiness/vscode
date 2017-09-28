 }
 
 static void slaveMode(void) {
     int fd = context->fd;
     unsigned long long payload = sendSync(fd);
     char buf[1024];
+    int original_output = config.output;
 
     fprintf(stderr,"SYNC with master, discarding %llu "
                    "bytes of bulk transfer...\n", payload);
 
     /* Discard the payload. */
     while(payload) {
