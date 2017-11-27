     fprintf (stderr, "lcc_network_create failed.\n");
     exit (EXIT_FAILURE);
   }
   else
   {
     lcc_server_t *srv;
-    
+
     srv = lcc_server_create (net, conf_destination, conf_service);
     if (srv == NULL)
     {
       fprintf (stderr, "lcc_server_create failed.\n");
       exit (EXIT_FAILURE);
     }
