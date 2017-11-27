   int status;
   os_handler_t *os_handler = NULL;
 
   status = thread_init (&os_handler);
   if (status != 0)
   {
-    fprintf (stderr, "ipmi plugin: thread_init failed.\n");
+    ERROR ("ipmi plugin: thread_init failed.\n");
     return ((void *) -1);
   }
 
   while (c_ipmi_active != 0)
   {
     struct timeval tv = { 1, 0 };
