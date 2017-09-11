@@ -4,6 +4,9 @@
  *   with use non-block socket and tree-shape reduction
  * \author Tianqi Chen
  */
+#define _CRT_SECURE_NO_WARNINGS
+#define _CRT_SECURE_NO_DEPRECATE
+#define NOMINMAX
 #include <vector>
 #include <string>
 #include <cstring>
@@ -34,13 +37,13 @@ class SyncManager {
     this->SetParam("reduce_buffer", "256MB");
   }
   ~SyncManager(void) {
-    this->Shutdown();
   }
   inline void Shutdown(void) {
     for (size_t i = 0; i < links.size(); ++i) {
       links[i].sock.Close();
     }
     links.clear();
+    TCPSocket::Finalize();
   }
   /*! \brief set parameters to the sync manager */
   inline void SetParam(const char *name, const char *val) {
@@ -80,6 +83,7 @@ class SyncManager {
   }
   // initialize the manager
   inline void Init(void) {
+    TCPSocket::Startup();
     // single node mode
     if (master_uri == "NULL") return;
     utils::Assert(links.size() == 0, "can only call Init once");