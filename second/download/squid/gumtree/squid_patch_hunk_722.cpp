         /* walk the ip list */
 
         if (ipdata->ipaddr == ipaddr) {
             /* This ip has already been seen. */
             found = 1;
             /* update IP ttl */
-            ipdata->ip_expiretime = squid_curtime;
+            ipdata->ip_expiretime = squid_curtime + ::Config.authenticateIpTTL;
         } else if (ipdata->ip_expiretime <= squid_curtime) {
             /* This IP has expired - remove from the seen list */
             dlinkDelete(&ipdata->node, &ip_list);
-            cbdataFree(ipdata);
+            delete ipdata;
             /* catch incipient underflow */
             assert(ipcount);
             -- ipcount;
         }
 
         ipdata = tempnode;
     }
 
     if (found)
         return;
 
     /* This ip is not in the seen list */
-    ipdata = cbdataAlloc(AuthUserIP);
-
-    ipdata->ip_expiretime = squid_curtime + ::Config.authenticateIpTTL;
-
-    ipdata->ipaddr = ipaddr;
+    ipdata = new AuthUserIP(ipaddr, squid_curtime + ::Config.authenticateIpTTL);
 
     dlinkAddTail(ipdata, &ipdata->node, &ip_list);
 
     ++ipcount;
 
     debugs(29, 2, HERE << "user '" << username() << "' has been seen at a new IP address (" << ipaddr << ")");
 }
 
+SBuf
+Auth::User::BuildUserKey(const char *username, const char *realm)
+{
+    SBuf key;
+    if (realm)
+        key.Printf("%s:%s", username, realm);
+    else
+        key.append(username, strlen(username));
+    return key;
+}
+
 /**
  * Add the Auth::User structure to the username cache.
  */
 void
 Auth::User::addToNameCache()
 {
