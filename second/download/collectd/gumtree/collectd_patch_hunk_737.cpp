 
     if (memcmp("[TS]\r\n", buffer, 6) != 0) {
       ERROR("teamspeak2 plugin: Unexpected response when connecting "
             "to server. Expected ``[TS]'', got ``%s''.",
             buffer);
       tss2_close_socket();
-      return (-1);
+      return -1;
     }
     DEBUG("teamspeak2 plugin: Server send correct banner, connected!");
   }
 
   /* Copy the new filehandles to the given pointers */
   if (ret_read_fh != NULL)
     *ret_read_fh = global_read_fh;
   if (ret_write_fh != NULL)
     *ret_write_fh = global_write_fh;
-  return (0);
+  return 0;
 } /* int tss2_get_socket */
 
 static int tss2_send_request(FILE *fh, const char *request) {
   /*
    * This function puts a request to the server socket
    */
   int status;
 
   status = fputs(request, fh);
   if (status < 0) {
     ERROR("teamspeak2 plugin: fputs failed.");
     tss2_close_socket();
-    return (-1);
+    return -1;
   }
   fflush(fh);
 
-  return (0);
+  return 0;
 } /* int tss2_send_request */
 
 static int tss2_receive_line(FILE *fh, char *buffer, int buffer_size) {
   /*
    * Receive a single line from the given file object
    */
