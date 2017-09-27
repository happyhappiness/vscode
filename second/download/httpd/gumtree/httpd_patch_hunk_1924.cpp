 {
     while (*pic) {
         ipaddr_chain *ic = *pic;
 
         if (ic->server == NULL) {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, main_s,
-                         "NameVirtualHost %s:%u has no VirtualHosts",
+                         "Either NameVirtualHost %s:%u has no VirtualHosts,"
+                         " or there is more than one identical NameVirtualHost line,"
+                         " or your VirtualHost declarations do not match the NameVirtualHost line",
                          ic->sar->virthost, ic->sar->host_port);
             *pic = ic->next;
         }
         else {
             pic = &ic->next;
         }
