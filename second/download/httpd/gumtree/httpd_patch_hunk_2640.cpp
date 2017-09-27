 /* calling send_http_header().  Otherwise, no header will be sent at all,   */
 /* and the output sent to the client will actually be HTTP-uncompliant.     */
 /*--------------------------------------------------------------------------*/
 /*
  * Sample content handler.  All this does is display the call list that has
  * been built up so far.
- * 
+ *
  * This routine gets called for every request, unless another handler earlier
- * in the callback chain has already handled the request. It is up to us to 
- * test the request_rec->handler field and see whether we are meant to handle 
- * this request. 
+ * in the callback chain has already handled the request. It is up to us to
+ * test the request_rec->handler field and see whether we are meant to handle
+ * this request.
  *
- * The content handler gets to write directly to the client using calls like 
+ * The content handler gets to write directly to the client using calls like
  * ap_rputs() and ap_rprintf()
  *
- * This is a RUN_FIRST hook. 
+ * This is a RUN_FIRST hook.
  */
 static int x_handler(request_rec *r)
 {
     x_cfg *dcfg;
-    char *note; 
+    char *note;
     void *conn_data;
     apr_status_t status;
 
     dcfg = our_dconfig(r);
-    /* 
-     * Add our trace to the log, and whether we get to write 
-     * content for this request. 
+    /*
+     * Add our trace to the log, and whether we get to write
+     * content for this request.
      */
-    note = apr_pstrcat(r->pool, "x_handler(), handler is \"", 
+    note = apr_pstrcat(r->pool, "x_handler(), handler is \"",
                       r->handler, "\"", NULL);
     trace_request(r, note);
 
     /* If it's not for us, get out as soon as possible. */
     if (strcmp(r->handler, "example-hooks-handler")) {
         return DECLINED;
     }
 
     /*
-     * Set the Content-type header. Note that we do not actually have to send 
-     * the headers: this is done by the http core. 
+     * Set the Content-type header. Note that we do not actually have to send
+     * the headers: this is done by the http core.
      */
     ap_set_content_type(r, "text/html");
     /*
      * If we're only supposed to send header information (HEAD request), we're
      * already there.
      */
