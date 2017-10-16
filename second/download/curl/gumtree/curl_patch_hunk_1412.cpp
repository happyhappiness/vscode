 
 /*
  * Read everything until a newline.
  */
 
 static
-int GetLine(int sockfd, char *buf, struct connectdata *conn)
+int GetLine(int sockfd, char *ptr, struct connectdata *conn)
 {
   ssize_t nread;
-  int read_rc=1;
-  char *ptr;
-  struct UrlData *data=conn->data;
-
-  ptr=buf;
 
   /* get us a full line, terminated with a newline */
-  for(nread=0;
-      (nread<BUFSIZE) && read_rc;
-      nread++, ptr++) {
+  for(nread=0; (nread<BUFSIZE); nread++, ptr++) {
     if((CURLE_OK != Curl_read(conn, sockfd, ptr, 1, &nread)) ||
-       (nread <= 0) ||
-       (*ptr == '\n'))
+       (nread <= 0) || (*ptr == '\n'))
       break;
   }
   *ptr=0; /* zero terminate */
   
-  if(data->bits.verbose) {
-    fputs("< ", data->err);
-    fwrite(buf, 1, nread, data->err);
-    fputs("\n", data->err);
-  }
   return nread>0?nread:0;
 }
 
 
 
 /*
  * This function checks the linked list of custom HTTP headers for a particular
  * header (prefix).
  */
-static bool checkheaders(struct UrlData *data, const char *thisheader)
+static bool checkheaders(struct SessionHandle *data, const char *thisheader)
 {
   struct curl_slist *head;
   size_t thislen = strlen(thisheader);
 
-  for(head = data->headers; head; head=head->next) {
+  for(head = data->set.headers; head; head=head->next) {
     if(strnequal(head->data, thisheader, thislen)) {
       return TRUE;
     }
   }
   return FALSE;
 }
