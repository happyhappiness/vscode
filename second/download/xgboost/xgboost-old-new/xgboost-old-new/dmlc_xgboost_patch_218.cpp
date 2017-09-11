@@ -43,7 +43,7 @@ class SyncManager {
       links[i].sock.Close();
     }
     links.clear();
-    TCPSocket::Finalize();
+    utils::TCPSocket::Finalize();
   }
   /*! \brief set parameters to the sync manager */
   inline void SetParam(const char *name, const char *val) {
@@ -83,7 +83,7 @@ class SyncManager {
   }
   // initialize the manager
   inline void Init(void) {
-    TCPSocket::Startup();
+    utils::TCPSocket::Startup();
     // single node mode
     if (master_uri == "NULL") return;
     utils::Assert(links.size() == 0, "can only call Init once");