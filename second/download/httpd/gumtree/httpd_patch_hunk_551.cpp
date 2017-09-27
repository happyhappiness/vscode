         return DECLINED;
 
     r->allowed |= (AP_METHOD_BIT << M_GET);
     if (r->method_number != M_GET)
 	return DECLINED;
 
-    ap_set_content_type(r, "text/html");
+    ap_set_content_type(r, "text/html; charset=ISO-8859-1");
 
     ap_rputs(DOCTYPE_HTML_3_2
 	     "<html><head><title>Server Information</title></head>\n", r);
     ap_rputs("<body><h1 align=\"center\">Apache Server Information</h1>\n", r);
     if (!r->args || strcasecmp(r->args, "list")) {
         if (!r->args) {
