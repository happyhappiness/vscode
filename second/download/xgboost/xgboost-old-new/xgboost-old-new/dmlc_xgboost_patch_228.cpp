@@ -23,16 +23,64 @@ class SyncManager {
  public:
   const static int kMagic = 0xff99;
   SyncManager(void) {
-    master_uri = "localhost";
+    master_uri = "NULL";
     master_port = 9000;
+    host_uri = "";
     slave_port = 9010;
     nport_trial = 1000;
+    rank = 0;
+    world_size = 1;
+    reduce_buffer_size = 128; 
   }
   ~SyncManager(void) {
     this->Shutdown();
   }
+  inline void Shutdown(void) {
+    for (size_t i = 0; i < links.size(); ++i) {
+      links[i].sock.Close();
+    }
+    links.clear();
+  }
+  /*! \brief set parameters to the sync manager */
+  inline void SetParam(const char *name, const char *val) {
+    if (!strcmp(name, "master_uri")) master_uri = val;
+    if (!strcmp(name, "master_port")) master_port = atoi(val);
+    if (!strcmp(name, "reduce_buffer")) {
+      char unit;
+      unsigned long amount;
+      if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
+        switch (unit) {
+          case 'B': reduce_buffer_size = amount; break;
+          case 'K': reduce_buffer_size = amount << 10UL; break;
+          case 'M': reduce_buffer_size = amount << 20UL; break;
+          case 'G': reduce_buffer_size = amount << 30UL; break;
+          default: utils::Error("invalid format for reduce buffer");
+        }
+      } else {
+        utils::Error("invalid format for reduce_buffer, shhould be {integer}{unit}, unit can be {B, KB, MB, GB}");
+      }
+    }
+  }
+  /*! \brief get rank */
+  inline int GetRank(void) const {
+    return rank;
+  }
+  /*! \brief check whether its distributed mode */
+  inline bool IsDistributed(void) const {
+    return links.size() != 0;
+  }
+  /*! \brief get rank */
+  inline int GetWorldSize(void) const {
+    return world_size;
+  }
+  /*! \brief get rank */
+  inline std::string GetHost(void) const {
+    return host_uri;
+  }
   // initialize the manager
   inline void Init(void) {
+    // single node mode
+    if (master_uri == "NULL") return;
     utils::Assert(links.size() == 0, "can only call Init once");
     int magic = kMagic;
     int nchild = 0, nparent = 0;
@@ -108,29 +156,6 @@ class SyncManager {
     }
     // done
   }
-  inline void Shutdown(void) {
-    for (size_t i = 0; i < links.size(); ++i) {
-      links[i].sock.Close();
-    }
-    links.clear();
-  }
-  /*! \brief set parameters to the sync manager */
-  inline void SetParam(const char *name, const char *val) {
-    if (!strcmp(name, "master_uri")) master_uri = val;
-    if (!strcmp(name, "master_port")) master_port = atoi(val);
-  }
-  /*! \brief get rank */
-  inline int GetRank(void) const {
-    return rank;
-  }  
-  /*! \brief get rank */
-  inline int GetWorldSize(void) const {
-    return world_size;
-  }
-  /*! \brief get rank */
-  inline std::string GetHost(void) const {
-    return host_uri;
-  }
   /*!
    * \brief perform in-place allreduce, on sendrecvbuf 
    *        this function is NOT thread-safe
@@ -159,7 +184,9 @@ class SyncManager {
 
     // initialize the link ring-buffer and pointer
     for (int i = 0; i < nlink; ++i) {
-      if (i != parent_index) links[i].InitBuffer(type_nbytes, count);
+      if (i != parent_index) {
+        links[i].InitBuffer(type_nbytes, count, reduce_buffer_size);
+      }
       links[i].ResetSize();
     }
     // if no childs, no need to reduce
@@ -301,8 +328,6 @@ class SyncManager {
     }
   }
  private:  
-  // 128 MB
-  const static size_t kBufferSize = 128;
   // an independent child record
   struct LinkRecord {
    public:
@@ -317,10 +342,10 @@ class SyncManager {
     // buffer size, in bytes
     size_t buffer_size;
     // initialize buffer
-    inline void InitBuffer(size_t type_nbytes, size_t count) {
-      utils::Assert(type_nbytes < kBufferSize, "too large type_nbytes");
+    inline void InitBuffer(size_t type_nbytes, size_t count, size_t reduce_buffer_size) {
+      utils::Assert(type_nbytes < reduce_buffer_size, "too large type_nbytes");
       size_t n = (type_nbytes * count + 7)/ 8;
-      buffer_.resize(std::min(kBufferSize, n));
+      buffer_.resize(std::min(reduce_buffer_size, n));
       // make sure align to type_nbytes
       buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
       // set buffer head
@@ -377,6 +402,8 @@ class SyncManager {
   int master_port;
   // port of slave process
   int slave_port, nport_trial;
+  // reduce buffer size
+  size_t reduce_buffer_size;
   // current rank
   int rank;
   // world size
@@ -405,9 +432,8 @@ int GetWorldSize(void) {
 std::string GetProcessorName(void) {
   return manager.GetHost();
 }
-
 bool IsDistributed(void) {
-  return true;
+  return manager.IsDistributed();
 }
 /*! \brief intiialize the synchronization module */
 void Init(int argc, char *argv[]) {