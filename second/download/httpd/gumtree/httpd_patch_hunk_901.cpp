              */
             fprintf(stderr, "Apache server shutdown initiated...\n");
             ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
             Sleep(30000);
             return TRUE;
     }
- 
+
     /* We should never get here, but this is (mostly) harmless */
     return FALSE;
 }
 
 
 static void stop_console_handler(void)
