         return DECLINED;
 
     if (strcmp(r->handler, "ldap-status")) {
         return DECLINED;
     }
 
-    r->content_type = "text/html";
+    r->content_type = "text/html; charset=ISO-8859-1";
     if (r->header_only)
         return OK;
 
     ap_rputs(DOCTYPE_HTML_3_2
              "<html><head><title>LDAP Cache Information</title></head>\n", r);
     ap_rputs("<body bgcolor='#ffffff'><h1 align=center>LDAP Cache Information"
