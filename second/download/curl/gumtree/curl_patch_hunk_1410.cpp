         /* we got a whole chunk of data, which can be anything from one
          * byte to a set of lines and possible just a piece of the last
          * line */
         int i;
 
         nread += gotbytes;
-        for(i=0; i< gotbytes; ptr++, i++) {
+        for(i = 0; i < gotbytes; ptr++, i++) {
           perline++;
           if(*ptr=='\n') {
             /* a newline is CRLF in ftp-talk, so the CR is ignored as
                the line isn't really terminated until the LF comes */
 
             /* output debug output if that is requested */
-            if(data->bits.verbose) {
-              fputs("< ", data->err);
-              fwrite(line_start, perline, 1, data->err);
+            if(data->set.verbose) {
+              fputs("< ", data->set.err);
+              fwrite(line_start, perline, 1, data->set.err);
               /* no need to output LF here, it is part of the data */
             }
 
+#define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
+			isdigit((int)line[2]) && (' ' == line[3]))
+
             if(perline>3 && lastline(line_start)) {
               /* This is the end of the last line, copy the last
                * line to the start of the buffer and zero terminate,
                * for old times sake (and krb4)! */
               char *meow;
               int i;
