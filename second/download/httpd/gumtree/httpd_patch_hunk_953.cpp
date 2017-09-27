     return (DefWindowProc(hWnd, msg, wParam, lParam));
 }
 
 static DWORD WINAPI monitor_service_9x_thread(void *service_name)
 {
     /* When running as a service under Windows 9x, there is no console
-     * window present, and no ConsoleCtrlHandler to call when the system 
+     * window present, and no ConsoleCtrlHandler to call when the system
      * is shutdown.  If the WatchWindow thread is created with a NULL
      * service_name argument, then the ...SystemMonitor window class is
      * used to create the "Apache" window to watch for logoff and shutdown.
      * If the service_name is provided, the ...ServiceMonitor window class
      * is used to create the window named by the service_name argument,
      * and the logoff message is ignored.
      */
     WNDCLASS wc;
     HWND hwndMain;
     MSG msg;
-    
+
     wc.style         = CS_GLOBALCLASS;
-    wc.lpfnWndProc   = monitor_service_9x_proc; 
+    wc.lpfnWndProc   = monitor_service_9x_proc;
     wc.cbClsExtra    = 0;
-    wc.cbWndExtra    = 0; 
+    wc.cbWndExtra    = 0;
     wc.hInstance     = NULL;
     wc.hIcon         = NULL;
     wc.hCursor       = NULL;
     wc.hbrBackground = NULL;
     wc.lpszMenuName  = NULL;
     if (service_name)
 	wc.lpszClassName = "ApacheWin95ServiceMonitor";
     else
 	wc.lpszClassName = "ApacheWin95SystemMonitor";
- 
+
     die_on_logoff = service_name ? FALSE : TRUE;
 
-    if (!RegisterClass(&wc)) 
+    if (!RegisterClass(&wc))
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), 
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                      NULL, "Could not register window class for WatchWindow");
         globdat.service_thread_id = 0;
         return 0;
     }
-    
+
     /* Create an invisible window */
-    hwndMain = CreateWindow(wc.lpszClassName, 
+    hwndMain = CreateWindow(wc.lpszClassName,
                             service_name ? (char *) service_name : "Apache",
- 	                    WS_OVERLAPPEDWINDOW & ~WS_VISIBLE, 
-                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
+                            WS_OVERLAPPEDWINDOW & ~WS_VISIBLE,
+                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                             CW_USEDEFAULT, NULL, NULL, NULL, NULL);
-                            
+
     if (!hwndMain)
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), 
+        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                      NULL, "Could not create WatchWindow");
         globdat.service_thread_id = 0;
         return 0;
     }
 
     /* If we succeed, eliminate the console window.
      * Signal the parent we are all set up, and
      * watch the message queue while the window lives.
      */
     FreeConsole();
     SetEvent(globdat.service_init);
 
-    while (GetMessage(&msg, NULL, 0, 0)) 
+    while (GetMessage(&msg, NULL, 0, 0))
     {
         if (msg.message == WM_CLOSE)
-            DestroyWindow(hwndMain); 
+            DestroyWindow(hwndMain);
         else {
 	    TranslateMessage(&msg);
 	    DispatchMessage(&msg);
         }
     }
     globdat.service_thread_id = 0;
