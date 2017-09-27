  */
 static int dav_error_response_tag(request_rec *r,
                                   dav_error *err)
 {
     r->status = err->status;
 
-    /* ### I really don't think this is needed; gotta test */
-    r->status_line = ap_get_status_line(err->status);
-
     ap_set_content_type(r, DAV_XML_CONTENT_TYPE);
 
     ap_rputs(DAV_XML_HEADER DEBUG_CR
              "<D:error xmlns:D=\"DAV:\"", r);
 
     if (err->desc != NULL) {
