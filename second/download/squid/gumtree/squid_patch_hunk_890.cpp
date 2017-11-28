         Ip::Interceptor.StopTransparency("capability setting has failed.");
     }
 #endif
 }
 
 static void
-restoreCapabilities(int keep)
+restoreCapabilities(bool keep)
 {
     /* NP: keep these two if-endif separate. Non-Linux work perfectly well without Linux syscap support. */
 #if USE_LIBCAP
     cap_t caps;
     if (keep)
         caps = cap_get_proc();
