         return DECLINED;
 
     r->allowed |= (AP_METHOD_BIT << M_GET);
     if (r->method_number != M_GET)
         return DECLINED;
 
-    ap_set_content_type(r, "text/html");
+    ap_set_content_type(r, "text/html; charset=ISO-8859-1");
 
     ap_rputs(DOCTYPE_XHTML_1_0T
              "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
              "<head>\n"
              "  <title>Server Information</title>\n" "</head>\n", r);
     ap_rputs("<body><h1 style=\"text-align: center\">"
