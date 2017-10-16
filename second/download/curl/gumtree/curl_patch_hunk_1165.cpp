         config->test_event_based = toggle;
 #else
         warnf(global, "--test-event is ignored unless a debug build!\n");
 #endif
         break;
       case 'M': /* --unix-socket */
+        config->abstract_unix_socket = FALSE;
         GetStr(&config->unix_socket_path, nextarg);
         break;
       case 'N': /* --path-as-is */
         config->path_as_is = toggle;
         break;
       case 'O': /* --proxy-service-name */
