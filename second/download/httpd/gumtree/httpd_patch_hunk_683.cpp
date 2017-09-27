 {
     r->status = status;
 
     /* ### I really don't think this is needed; gotta test */
     r->status_line = ap_get_status_line(status);
 
-    ap_set_content_type(r, "text/html; charset=ISO-8859-1");
+    ap_set_content_type(r, "text/html");
 
     /* begin the response now... */
     ap_rvputs(r,
               DAV_RESPONSE_BODY_1,
               r->status_line,
               DAV_RESPONSE_BODY_2,
