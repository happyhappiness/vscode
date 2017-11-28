 void
 WIN32_RemoveService()
 {
     SC_HANDLE schService;
     SC_HANDLE schSCManager;
 
-    if (!WIN32_Service_name)
-        WIN32_Service_name = xstrdup(_WIN_SQUID_DEFAULT_SERVICE_NAME);
+    if (service_name.isEmpty())
+        service_name = SBuf(APP_SHORTNAME);
 
-    strcat(REGKEY, WIN32_Service_name);
+    const char *service =  service_name.c_str();
+    strcat(REGKEY, service);
 
-    keys[4] = WIN32_Service_name;
+    keys[4] = const_cast<char*>(service);
 
     schSCManager = OpenSCManager(NULL,	/* machine (NULL == local)    */
-                                 NULL,			/* database (NULL == default) */
+                                 NULL,          /* database (NULL == default) */
                                  SC_MANAGER_ALL_ACCESS	/* access required            */
                                 );
 
     if (!schSCManager)
         fprintf(stderr, "OpenSCManager failed\n");
     else {
-        schService = OpenService(schSCManager, WIN32_Service_name, SERVICE_ALL_ACCESS);
+        schService = OpenService(schSCManager, service, SERVICE_ALL_ACCESS);
 
         if (schService == NULL)
             fprintf(stderr, "OpenService failed\n");
 
         /* Could not open the service */
         else {
