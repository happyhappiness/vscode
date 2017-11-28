 
 static void
 parse_wccp2_service_ports(char *options, int portlist[])
 {
     int i = 0;
     int p;
-    char *tmp, *tmp2, *port, *end;
+    char *tmp, *tmp2, *port;
 
     if (!options) {
         return;
     }
 
     tmp = xstrdup(options);
     tmp2 = tmp;
 
     port = strsep(&tmp2, ",");
 
     while (port && i < WCCP2_NUMPORTS) {
-        p = strtol(port, &end, 0);
+        p = xatoi(port);
 
         if (p < 1 || p > 65535) {
             fatalf("parse_wccp2_service_ports: port value '%s' isn't valid (1..65535)\n", port);
         }
 
         portlist[i] = p;
