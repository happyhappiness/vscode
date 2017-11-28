 #if USE_WIN32_SERVICE
 
         if (opt_signal_service) {
             WIN32_sendSignal(opt_send_signal);
             exit(0);
         } else
-#ifdef _SQUID_MSWIN_
+#if _SQUID_MSWIN_
         {
             fprintf(stderr, "%s: ERROR: Could not send ", APP_SHORTNAME);
             fprintf(stderr, "signal to Squid Service:\n");
             fprintf(stderr, "missing -n command line switch.\n");
             exit(1);
         }
