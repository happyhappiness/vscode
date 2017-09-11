@@ -24,6 +24,7 @@ AllreduceBase::AllreduceBase(void) {
   nport_trial = 1000;
   rank = 0;
   world_size = -1;
+  connect_retry = 5;
   hadoop_mode = 0;
   version_number = 0;
   // 32 K items
@@ -46,6 +47,7 @@ AllreduceBase::AllreduceBase(void) {
   env_vars.push_back("DMLC_NUM_ATTEMPT");
   env_vars.push_back("DMLC_TRACKER_URI");
   env_vars.push_back("DMLC_TRACKER_PORT");
+  env_vars.push_back("DMLC_WORKER_CONNECT_RETRY");
 }
 
 // initialization function
@@ -94,7 +96,8 @@ void AllreduceBase::Init(void) {
     }
   }
   if (dmlc_role != "worker") {
-    fprintf(stderr, "Rabit Module currently only work with dmlc worker, quit this program by exit 0\n");
+    fprintf(stderr, "Rabit Module currently only work with dmlc worker"\
+            ", quit this program by exit 0\n");
     exit(0);
   }
   // clear the setting before start reconnection
@@ -134,7 +137,7 @@ void AllreduceBase::TrackerPrint(const std::string &msg) {
 // util to parse data with unit suffix
 inline size_t ParseUnit(const char *name, const char *val) {
   char unit;
-  unsigned long amt;
+  unsigned long amt;  // NOLINT(*)
   int n = sscanf(val, "%lu%c", &amt, &unit);
   size_t amount = amt;
   if (n == 2) {
@@ -154,7 +157,7 @@ inline size_t ParseUnit(const char *name, const char *val) {
   }
 }
 /*!
- * \brief set parameters to the engine 
+ * \brief set parameters to the engine
  * \param name parameter name
  * \param val parameter value
  */
@@ -174,6 +177,9 @@ void AllreduceBase::SetParam(const char *name, const char *val) {
   if (!strcmp(name, "rabit_reduce_buffer")) {
     reduce_buffer_size = (ParseUnit(name, val) + 7) >> 3;
   }
+  if (!strcmp(name, "DMLC_WORKER_CONNECT_RETRY")) {
+    connect_retry = atoi(val);
+  }
 }
 /*!
  * \brief initialize connection to the tracker
@@ -184,9 +190,27 @@ utils::TCPSocket AllreduceBase::ConnectTracker(void) const {
   // get information from tracker
   utils::TCPSocket tracker;
   tracker.Create();
-  if (!tracker.Connect(utils::SockAddr(tracker_uri.c_str(), tracker_port))) {
-    utils::Socket::Error("Connect");
-  }
+
+  int retry = 0;
+  do {
+    fprintf(stderr, "connect to ip: [%s]\n", tracker_uri.c_str());
+    if (!tracker.Connect(utils::SockAddr(tracker_uri.c_str(), tracker_port))) {
+      if (++retry >= connect_retry) {
+        fprintf(stderr, "connect to (failed): [%s]\n", tracker_uri.c_str());
+        utils::Socket::Error("Connect");
+      } else {
+        fprintf(stderr, "retry connect to ip(retry time %d): [%s]\n", retry, tracker_uri.c_str());
+        #ifdef _MSC_VER
+        Sleep(1);
+        #else
+        sleep(1);
+        #endif
+        continue;
+      }
+    }
+    break;
+  } while (1);
+
   using utils::Assert;
   Assert(tracker.SendAll(&magic, sizeof(magic)) == sizeof(magic),
          "ReConnectLink failure 1");
@@ -258,7 +282,7 @@ void AllreduceBase::ReConnectLinks(const char *cmd) {
       } else {
         if (!all_links[i].sock.IsClosed()) all_links[i].sock.Close();
       }
-    }    
+    }
     int ngood = static_cast<int>(good_link.size());
     Assert(tracker.SendAll(&ngood, sizeof(ngood)) == sizeof(ngood),
            "ReConnectLink failure 5");
@@ -359,7 +383,7 @@ void AllreduceBase::ReConnectLinks(const char *cmd) {
  *    The kSuccess TryAllreduce does NOT mean every node have successfully finishes TryAllreduce.
  *    It only means the current node get the correct result of Allreduce.
  *    However, it means every node finishes LAST call(instead of this one) of Allreduce/Bcast
- * 
+ *
  * \param sendrecvbuf_ buffer for both sending and recving data
  * \param type_nbytes the unit number of bytes the type have
  * \param count number of elements to be reduced
@@ -440,7 +464,7 @@ AllreduceBase::TryAllreduceTree(void *sendrecvbuf_,
           selecter.WatchRead(links[i].sock);
         }
         // size_write <= size_read
-        if (links[i].size_write != total_size){
+        if (links[i].size_write != total_size) {
           if (links[i].size_write < size_down_in) {
             selecter.WatchWrite(links[i].sock);
           }
@@ -477,7 +501,7 @@ AllreduceBase::TryAllreduceTree(void *sendrecvbuf_,
       size_t max_reduce = total_size;
       for (int i = 0; i < nlink; ++i) {
         if (i != parent_index) {
-          max_reduce= std::min(max_reduce, links[i].size_read);
+          max_reduce = std::min(max_reduce, links[i].size_read);
           utils::Assert(buffer_size == 0 || buffer_size == links[i].buffer_size,
                         "buffer size inconsistent");
           buffer_size = links[i].buffer_size;
@@ -513,7 +537,7 @@ AllreduceBase::TryAllreduceTree(void *sendrecvbuf_,
         if (len != -1) {
           size_up_out += static_cast<size_t>(len);
         } else {
-          ReturnType ret = Errno2Return(errno);
+          ReturnType ret = Errno2Return();
           if (ret != kSuccess) {
             return ReportError(&links[parent_index], ret);
           }
@@ -525,15 +549,15 @@ AllreduceBase::TryAllreduceTree(void *sendrecvbuf_,
         ssize_t len = links[parent_index].sock.
             Recv(sendrecvbuf + size_down_in, total_size - size_down_in);
         if (len == 0) {
-          links[parent_index].sock.Close(); 
+          links[parent_index].sock.Close();
           return ReportError(&links[parent_index], kRecvZeroLen);
         }
         if (len != -1) {
           size_down_in += static_cast<size_t>(len);
           utils::Assert(size_down_in <= size_up_out,
                         "Allreduce: boundary error");
         } else {
-          ReturnType ret = Errno2Return(errno);
+          ReturnType ret = Errno2Return();
           if (ret != kSuccess) {
             return ReportError(&links[parent_index], ret);
           }
@@ -670,19 +694,19 @@ AllreduceBase::TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
                                 size_t slice_begin,
                                 size_t slice_end,
                                 size_t size_prev_slice) {
-  // read from next link and send to prev one 
+  // read from next link and send to prev one
   LinkRecord &prev = *ring_prev, &next = *ring_next;
   // need to reply on special rank structure
   utils::Assert(next.rank == (rank + 1) % world_size &&
                 rank == (prev.rank + 1) % world_size,
                 "need to assume rank structure");
   // send recv buffer
   char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
-  const size_t stop_read = total_size + slice_begin; 
-  const size_t stop_write = total_size + slice_begin - size_prev_slice; 
+  const size_t stop_read = total_size + slice_begin;
+  const size_t stop_write = total_size + slice_begin - size_prev_slice;
   size_t write_ptr = slice_begin;
   size_t read_ptr = slice_end;
-  
+
   while (true) {
     // select helper
     bool finished = true;
@@ -709,7 +733,7 @@ AllreduceBase::TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
       if (len != -1) {
         read_ptr += static_cast<size_t>(len);
       } else {
-        ReturnType ret = Errno2Return(errno);
+        ReturnType ret = Errno2Return();
         if (ret != kSuccess) return ReportError(&next, ret);
       }
     }
@@ -723,7 +747,7 @@ AllreduceBase::TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
       if (len != -1) {
         write_ptr += static_cast<size_t>(len);
       } else {
-        ReturnType ret = Errno2Return(errno);
+        ReturnType ret = Errno2Return();
         if (ret != kSuccess) return ReportError(&prev, ret);
       }
     }
@@ -733,7 +757,7 @@ AllreduceBase::TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
 /*!
  * \brief perform in-place allreduce, on sendrecvbuf, this function can fail,
  *  and will return the cause of failure
- * 
+ *
  *  Ring-based algorithm
  *
  * \param sendrecvbuf_ buffer for both sending and recving data
@@ -748,7 +772,7 @@ AllreduceBase::TryReduceScatterRing(void *sendrecvbuf_,
                                     size_t type_nbytes,
                                     size_t count,
                                     ReduceFunction reducer) {
-  // read from next link and send to prev one 
+  // read from next link and send to prev one
   LinkRecord &prev = *ring_prev, &next = *ring_next;
   // need to reply on special rank structure
   utils::Assert(next.rank == (rank + 1) % world_size &&
@@ -757,7 +781,7 @@ AllreduceBase::TryReduceScatterRing(void *sendrecvbuf_,
   // total size of message
   const size_t total_size = type_nbytes * count;
   size_t n = static_cast<size_t>(world_size);
-  size_t step = (count + n - 1) / n;  
+  size_t step = (count + n - 1) / n;
   size_t r = static_cast<size_t>(next.rank);
   size_t write_ptr = std::min(r * step, count) * type_nbytes;
   size_t read_ptr = std::min((r + 1) * step, count) * type_nbytes;
@@ -826,11 +850,11 @@ AllreduceBase::TryReduceScatterRing(void *sendrecvbuf_,
       if (len != -1) {
         write_ptr += static_cast<size_t>(len);
       } else {
-        ReturnType ret = Errno2Return(errno);
+        ReturnType ret = Errno2Return();
         if (ret != kSuccess) return ReportError(&prev, ret);
       }
     }
-  }  
+  }
   return kSuccess;
 }
 /*!
@@ -857,7 +881,7 @@ AllreduceBase::TryAllreduceRing(void *sendrecvbuf_,
   size_t end = std::min((rank + 1) * step, count) * type_nbytes;
   // previous rank
   int prank = ring_prev->rank;
-  // get rank of previous 
+  // get rank of previous
   return TryAllgatherRing
       (sendrecvbuf_, type_nbytes * count,
        begin, end,