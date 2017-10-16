         nread += gotbytes;
         for(i = 0; i < gotbytes; ptr++, i++) {
           perline++;
           if(*ptr=='\n') {
             /* a newline is CRLF in ftp-talk, so the CR is ignored as
                the line isn't really terminated until the LF comes */
+            CURLcode result;
 
             /* output debug output if that is requested */
-            if(data->set.verbose) {
-              fputs("< ", data->set.err);
-              fwrite(line_start, perline, 1, data->set.err);
-              /* no need to output LF here, it is part of the data */
-            }
+            if(data->set.verbose)
+              Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline);
 
+            /*
+             * We pass all response-lines to the callback function registered
+             * for "headers". The response lines can be seen as a kind of
+             * headers.
+             */
+            result = Curl_client_write(data, CLIENTWRITE_HEADER,
+                                       line_start, perline);
+            if(result)
+              return -SELECT_CALLBACK;
+                                       
 #define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
 			isdigit((int)line[2]) && (' ' == line[3]))
 
             if(perline>3 && lastline(line_start)) {
               /* This is the end of the last line, copy the last
                * line to the start of the buffer and zero terminate,
                * for old times sake (and krb4)! */
               char *meow;
-              int i;
-              for(meow=line_start, i=0; meow<ptr; meow++, i++)
-                buf[i] = *meow;
-              meow[i]=0; /* zero terminate */
+              int n;
+              for(meow=line_start, n=0; meow<ptr; meow++, n++)
+                buf[n] = *meow;
+              *meow=0; /* zero terminate */
               keepon=FALSE;
+              line_start = ptr+1; /* advance pointer */
+              i++; /* skip this before getting out */
               break;
             }
             perline=0; /* line starts over here */
             line_start = ptr+1;
           }
         }
-      }
-      break;
-    } /* switch */
+        if(!keepon && (i != gotbytes)) {
+          /* We found the end of the response lines, but we didn't parse the
+             full chunk of data we have read from the server. We therefore
+             need to store the rest of the data to be checked on the next
+             invoke as it may actually contain another end of response
+             already!  Cleverly figured out by Eric Lavigne in December
+             2001. */
+          ftp->cache_size = gotbytes - i;
+          ftp->cache = (char *)malloc(ftp->cache_size);
+          if(ftp->cache)
+            memcpy(ftp->cache, line_start, ftp->cache_size);
+          else
+            return -SELECT_MEMORY; /**BANG**/
+        }
+      } /* there was data */
+    } /* if(no error) */
   } /* while there's buffer left and loop is requested */
 
   if(!error)
     code = atoi(buf);
 
-#if KRB4
+#ifdef KRB4
   /* handle the security-oriented responses 6xx ***/
   /* FIXME: some errorchecking perhaps... ***/
   switch(code) {
   case 631:
     Curl_sec_read_msg(conn, buf, prot_safe);
     break;
