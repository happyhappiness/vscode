             exit(1);
         }
     }
 
     while(payload) {
         ssize_t nread, nwritten;
-        
+
         nread = read(s,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
         if (nread <= 0) {
             fprintf(stderr,"I/O Error reading RDB payload from socket\n");
             exit(1);
         }
         nwritten = write(fd, buf, nread);
