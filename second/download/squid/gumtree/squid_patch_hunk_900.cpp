             }
 
             /* now remove the service */
             if (DeleteService(schService) == 0)
                 fprintf(stderr, "DeleteService failed.\n");
             else
-                printf("Service %s deleted successfully.\n",
-                       WIN32_Service_name);
+                printf("Service " SQUIDSBUFPH " deleted successfully.\n", SQUIDSBUFPRINT(service_name));
 
             CloseServiceHandle(schService);
         }
 
         CloseServiceHandle(schSCManager);
     }
 }
 
 void
 WIN32_SetServiceCommandLine()
 {
-    if (!WIN32_Service_name)
-        WIN32_Service_name = xstrdup(_WIN_SQUID_DEFAULT_SERVICE_NAME);
+    if (service_name.isEmpty())
+        service_name = SBuf(APP_SHORTNAME);
 
-    strcat(REGKEY, WIN32_Service_name);
+    const char *service = service_name.c_str();
+    strcat(REGKEY, service);
 
-    keys[4] = WIN32_Service_name;
+    keys[4] = const_cast<char*>(service);
 
     /* Now store the Service Command Line in the registry */
     WIN32_StoreKey(COMMANDLINE, REG_SZ, (unsigned char *) WIN32_Command_Line, strlen(WIN32_Command_Line) + 1);
 }
 
 void
