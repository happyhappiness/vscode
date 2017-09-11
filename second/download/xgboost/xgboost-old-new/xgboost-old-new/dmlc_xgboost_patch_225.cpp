@@ -1,7 +1,7 @@
 /*!
  * \file sync_tcp.cpp
  * \brief implementation of sync AllReduce using TCP sockets
- *   with use async socket and tree-shape reduction
+ *   with use non-block socket and tree-shape reduction
  * \author Tianqi Chen
  */
 #include <vector>
@@ -11,7 +11,8 @@
 #include "../utils/socket.h"
 
 namespace MPI {
-struct Datatype {
+class Datatype {
+ public:
   size_t type_size;
   Datatype(size_t type_size) : type_size(type_size) {}
 };
@@ -30,7 +31,7 @@ class SyncManager {
     nport_trial = 1000;
     rank = 0;
     world_size = 1;
-    reduce_buffer_size = 128; 
+    this->SetParam("reduce_buffer", "256MB");
   }
   ~SyncManager(void) {
     this->Shutdown();
@@ -50,10 +51,10 @@ class SyncManager {
       unsigned long amount;
       if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
         switch (unit) {
-          case 'B': reduce_buffer_size = amount; break;
-          case 'K': reduce_buffer_size = amount << 10UL; break;
-          case 'M': reduce_buffer_size = amount << 20UL; break;
-          case 'G': reduce_buffer_size = amount << 30UL; break;
+          case 'B': reduce_buffer_size = (amount + 7)/ 8; break;
+          case 'K': reduce_buffer_size = amount << 7UL; break;
+          case 'M': reduce_buffer_size = amount << 17UL; break;
+          case 'G': reduce_buffer_size = amount << 27UL; break;
           default: utils::Error("invalid format for reduce buffer");
         }
       } else {
@@ -117,27 +118,27 @@ class SyncManager {
       utils::Assert(master.RecvAll(&hname[0], len) == static_cast<size_t>(len), "sync::Init failure 10");
       utils::Assert(master.RecvAll(&hport, sizeof(hport)) == sizeof(hport), "sync::Init failure 11");
       links[0].sock.Create();
-      links[0].sock.Connect(utils::SockAddr(hname.c_str(), hport));
-      utils::Assert(links[0].sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure");
-      utils::Assert(links[0].sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure");
+      links[0].sock.Connect(utils::SockAddr(hname.c_str(), hport));      
+      utils::Assert(links[0].sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 12");
+      utils::Assert(links[0].sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 13");
       utils::Check(magic == kMagic, "sync::Init failure, parent magic number mismatch");
       parent_index = 0;
     } else {
       parent_index = -1;
     }
     // send back socket listening port to master
-    utils::Assert(master.SendAll(&port, sizeof(port)) == sizeof(port), "sync::Init failure 12");
+    utils::Assert(master.SendAll(&port, sizeof(port)) == sizeof(port), "sync::Init failure 14");
     // close connection to master
     master.Close();
     // accept links from childs
     for (int i = 0; i < nchild; ++i) {
       LinkRecord r; 
       while (true) {
         r.sock = sock_listen.Accept();
-        if (links[0].sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic) && magic == kMagic) {
-          utils::Assert(r.sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure");
+        if (r.sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic) && magic == kMagic) {
+          utils::Assert(r.sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 15");
           break;
-        } else {
+        } else {         
           // not a valid child
           r.sock.Close();
         }
@@ -150,7 +151,7 @@ class SyncManager {
     selecter.Clear();
     for (size_t i = 0; i < links.size(); ++i) {
       // set the socket to non-blocking mode
-      links[i].sock.SetNonBlock();
+      links[i].sock.SetNonBlock(true);
       selecter.WatchRead(links[i].sock);
       selecter.WatchWrite(links[i].sock);
     }
@@ -343,11 +344,11 @@ class SyncManager {
     size_t buffer_size;
     // initialize buffer
     inline void InitBuffer(size_t type_nbytes, size_t count, size_t reduce_buffer_size) {
-      utils::Assert(type_nbytes < reduce_buffer_size, "too large type_nbytes");
       size_t n = (type_nbytes * count + 7)/ 8;
       buffer_.resize(std::min(reduce_buffer_size, n));
       // make sure align to type_nbytes
       buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
+      utils::Assert(type_nbytes < buffer_size, "too large type_nbytes=%lu, buffer_size", type_nbytes, buffer_size);
       // set buffer head
       buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
     }