     cap_t caps;
     if (keep)
         caps = cap_get_proc();
     else
         caps = cap_init();
     if (!caps) {
-        IpInterceptor.StopTransparency("Can't get current capabilities");
+        Ip::Interceptor.StopTransparency("Can't get current capabilities");
     } else {
         int ncaps = 0;
         int rc = 0;
         cap_value_t cap_list[10];
-        cap_list[ncaps++] = CAP_NET_BIND_SERVICE;
-
-        if (IpInterceptor.TransparentActive()) {
-            cap_list[ncaps++] = CAP_NET_ADMIN;
-#if LINUX_TPROXY2
-            cap_list[ncaps++] = CAP_NET_BROADCAST;
-#endif
+        cap_list[ncaps] = CAP_NET_BIND_SERVICE;
+        ++ncaps;
+        if (Ip::Interceptor.TransparentActive() || Ip::Qos::TheConfig.isHitNfmarkActive() || Ip::Qos::TheConfig.isAclNfmarkActive()) {
+            cap_list[ncaps] = CAP_NET_ADMIN;
+            ++ncaps;
         }
 
         cap_clear_flag(caps, CAP_EFFECTIVE);
         rc |= cap_set_flag(caps, CAP_EFFECTIVE, ncaps, cap_list, CAP_SET);
         rc |= cap_set_flag(caps, CAP_PERMITTED, ncaps, cap_list, CAP_SET);
 
         if (rc || cap_set_proc(caps) != 0) {
-            IpInterceptor.StopTransparency("Error enabling needed capabilities.");
+            Ip::Interceptor.StopTransparency("Error enabling needed capabilities.");
         }
         cap_free(caps);
     }
-#elif defined(_SQUID_LINUX_)
-    IpInterceptor.StopTransparency("Missing needed capability support.");
+#elif _SQUID_LINUX_
+    Ip::Interceptor.StopTransparency("Missing needed capability support.");
 #endif /* HAVE_SYS_CAPABILITY_H */
 }
-
-void *
-xmemset(void *dst, int val, size_t sz)
-{
-    // do debugs output
-    debugs(63, 9, "memset: dst=" << dst << ", val=" << val << ", bytes=" << sz);
-
-    // call the system one to do the actual work ~safely.
-    return memset(dst, val, sz);
-}
