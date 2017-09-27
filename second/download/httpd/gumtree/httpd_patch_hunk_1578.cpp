         if ((val = apr_table_get(params, "dw"))) {
             if (!strcasecmp(val, "Disable"))
                 wsel->s->status |= PROXY_WORKER_DISABLED;
             else if (!strcasecmp(val, "Enable"))
                 wsel->s->status &= ~PROXY_WORKER_DISABLED;
         }
+        if ((val = apr_table_get(params, "ls"))) {
+            int ival = atoi(val);
+            if (ival >= 0 && ival <= 99) {
+                wsel->s->lbset = ival;
+             }
+        }
 
     }
     if (apr_table_get(params, "xml")) {
         ap_set_content_type(r, "text/xml");
         ap_rputs("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n", r);
         ap_rputs("<httpd:manager xmlns:httpd=\"http://httpd.apache.org\">\n", r);
