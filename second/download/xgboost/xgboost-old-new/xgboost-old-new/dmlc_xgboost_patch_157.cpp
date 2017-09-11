@@ -26,14 +26,18 @@ AllreduceBase::AllreduceBase(void) {
   world_size = -1;
   hadoop_mode = 0;
   version_number = 0;
+  // 32 K items
+  reduce_ring_mincount = 32 << 10;
+  // tracker URL
   task_id = "NULL";
   err_link = NULL;
   this->SetParam("rabit_reduce_buffer", "256MB");
   // setup possible enviroment variable of intrest
   env_vars.push_back("rabit_task_id");
   env_vars.push_back("rabit_num_trial");
   env_vars.push_back("rabit_reduce_buffer");
-  env_vars.push_back("rabit_tracker_uri");  
+  env_vars.push_back("rabit_reduce_ring_mincount");
+  env_vars.push_back("rabit_tracker_uri");
   env_vars.push_back("rabit_tracker_port");
 }
 
@@ -116,6 +120,27 @@ void AllreduceBase::TrackerPrint(const std::string &msg) {
   tracker.SendStr(msg);
   tracker.Close();
 }
+// util to parse data with unit suffix
+inline size_t ParseUnit(const char *name, const char *val) {
+  char unit;
+  uint64_t amount;
+  int n = sscanf(val, "%lu%c", &amount, &unit);
+  if (n == 2) {
+    switch (unit) {
+      case 'B': return amount;
+      case 'K': return amount << 10UL;
+      case 'M': return amount << 20UL;
+      case 'G': return amount << 30UL;
+      default: utils::Error("invalid format for %s", name); return 0;
+    }
+  } else if (n == 1) {
+    return amount;
+  } else {
+    utils::Error("invalid format for %s,"                               \
+                 "shhould be {integer}{unit}, unit can be {B, KB, MB, GB}", name);
+    return 0;
+  }
+}
 /*!
  * \brief set parameters to the engine 
  * \param name parameter name
@@ -127,21 +152,11 @@ void AllreduceBase::SetParam(const char *name, const char *val) {
   if (!strcmp(name, "rabit_task_id")) task_id = val;
   if (!strcmp(name, "rabit_world_size")) world_size = atoi(val);
   if (!strcmp(name, "rabit_hadoop_mode")) hadoop_mode = atoi(val);
+  if (!strcmp(name, "rabit_reduce_ring_mincount")) {
+    reduce_ring_mincount = ParseUnit(name, val);
+  }
   if (!strcmp(name, "rabit_reduce_buffer")) {
-    char unit;
-    uint64_t amount;
-    if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
-      switch (unit) {
-        case 'B': reduce_buffer_size = (amount + 7)/ 8; break;
-        case 'K': reduce_buffer_size = amount << 7UL; break;
-        case 'M': reduce_buffer_size = amount << 17UL; break;
-        case 'G': reduce_buffer_size = amount << 27UL; break;
-        default: utils::Error("invalid format for reduce buffer");
-      }
-    } else {
-      utils::Error("invalid format for reduce_buffer,"\
-                   "shhould be {integer}{unit}, unit can be {B, KB, MB, GB}");
-    }
+    reduce_buffer_size = (ParseUnit(name, val) + 7) >> 3;
   }
 }
 /*!
@@ -341,6 +356,28 @@ AllreduceBase::TryAllreduce(void *sendrecvbuf_,
                             size_t type_nbytes,
                             size_t count,
                             ReduceFunction reducer) {
+  if (count > reduce_ring_mincount) {
+    return this->TryAllreduceRing(sendrecvbuf_, type_nbytes, count, reducer);
+  } else {
+    return this->TryAllreduceTree(sendrecvbuf_, type_nbytes, count, reducer);
+  }
+}
+/*!
+ * \brief perform in-place allreduce, on sendrecvbuf,
+ * this function implements tree-shape reduction
+ *
+ * \param sendrecvbuf_ buffer for both sending and recving data
+ * \param type_nbytes the unit number of bytes the type have
+ * \param count number of elements to be reduced
+ * \param reducer reduce function
+ * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+ * \sa ReturnType
+ */
+AllreduceBase::ReturnType
+AllreduceBase::TryAllreduceTree(void *sendrecvbuf_,
+                                size_t type_nbytes,
+                                size_t count,
+                                ReduceFunction reducer) {
   RefLinkVector &links = tree_links;
   if (links.size() == 0 || count == 0) return kSuccess;
   // total size of message
@@ -411,7 +448,7 @@ AllreduceBase::TryAllreduce(void *sendrecvbuf_,
     // read data from childs
     for (int i = 0; i < nlink; ++i) {
       if (i != parent_index && selecter.CheckRead(links[i].sock)) {
-        ReturnType ret = links[i].ReadToRingBuffer(size_up_out);
+        ReturnType ret = links[i].ReadToRingBuffer(size_up_out, total_size);
         if (ret != kSuccess) {
           return ReportError(&links[i], ret);
         }
@@ -599,5 +636,217 @@ AllreduceBase::TryBroadcast(void *sendrecvbuf_, size_t total_size, int root) {
   }
   return kSuccess;
 }
+/*!
+ * \brief internal Allgather function, each node have a segment of data in the ring of sendrecvbuf,
+ *  the data provided by current node k is [slice_begin, slice_end),
+ *  the next node's segment must start with slice_end
+ *  after the call of Allgather, sendrecvbuf_ contains all the contents including all segments
+ *  use a ring based algorithm
+ *
+ * \param sendrecvbuf_ buffer for both sending and receiving data, it is a ring conceptually
+ * \param total_size total size of data to be gathered
+ * \param slice_begin beginning of the current slice
+ * \param slice_end end of the current slice
+ * \param size_prev_slice size of the previous slice i.e. slice of node (rank - 1) % world_size
+ */
+AllreduceBase::ReturnType
+AllreduceBase::TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
+                                size_t slice_begin,
+                                size_t slice_end,
+                                size_t size_prev_slice) {
+  // read from next link and send to prev one 
+  LinkRecord &prev = *ring_prev, &next = *ring_next;
+  // need to reply on special rank structure
+  utils::Assert(next.rank == (rank + 1) % world_size &&
+                rank == (prev.rank + 1) % world_size,
+                "need to assume rank structure");
+  // send recv buffer
+  char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
+  const size_t stop_read = total_size + slice_begin; 
+  const size_t stop_write = total_size + slice_begin - size_prev_slice; 
+  size_t write_ptr = slice_begin;
+  size_t read_ptr = slice_end;
+  
+  while (true) {
+    // select helper
+    bool finished = true;
+    utils::SelectHelper selecter;
+    if (read_ptr != stop_read) {
+      selecter.WatchRead(next.sock);
+      finished = false;
+    }
+    if (write_ptr != stop_write) {
+      if (write_ptr < read_ptr) {
+        selecter.WatchWrite(prev.sock);
+      }
+      finished  = false;
+    }
+    if (finished) break;
+    selecter.Select();
+    if (read_ptr != stop_read && selecter.CheckRead(next.sock)) {
+      size_t size = stop_read - read_ptr;
+      size_t start = read_ptr % total_size;
+      if (start + size > total_size) {
+        size = total_size - start;
+      }
+      ssize_t len = next.sock.Recv(sendrecvbuf + start, size);
+      if (len != -1) {
+        read_ptr += static_cast<size_t>(len);
+      } else {
+        ReturnType ret = Errno2Return(errno);
+        if (ret != kSuccess) return ReportError(&next, ret);
+      }
+    }
+    if (write_ptr < read_ptr && write_ptr != stop_write) {
+      size_t size = std::min(read_ptr, stop_write) - write_ptr;
+      size_t start = write_ptr % total_size;
+      if (start + size > total_size) {
+        size = total_size - start;
+      }
+      ssize_t len = prev.sock.Send(sendrecvbuf + start, size);
+      if (len != -1) {
+        write_ptr += static_cast<size_t>(len);
+      } else {
+        ReturnType ret = Errno2Return(errno);
+        if (ret != kSuccess) return ReportError(&prev, ret);
+      }
+    }
+  }
+  return kSuccess;
+}
+/*!
+ * \brief perform in-place allreduce, on sendrecvbuf, this function can fail,
+ *  and will return the cause of failure
+ * 
+ *  Ring-based algorithm
+ *
+ * \param sendrecvbuf_ buffer for both sending and recving data
+ * \param type_nbytes the unit number of bytes the type have
+ * \param count number of elements to be reduced
+ * \param reducer reduce function
+ * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+ * \sa ReturnType, TryAllreduce
+ */
+AllreduceBase::ReturnType
+AllreduceBase::TryReduceScatterRing(void *sendrecvbuf_,
+                                    size_t type_nbytes,
+                                    size_t count,
+                                    ReduceFunction reducer) {
+  // read from next link and send to prev one 
+  LinkRecord &prev = *ring_prev, &next = *ring_next;
+  // need to reply on special rank structure
+  utils::Assert(next.rank == (rank + 1) % world_size &&
+                rank == (prev.rank + 1) % world_size,
+                "need to assume rank structure");
+  // total size of message
+  const size_t total_size = type_nbytes * count;
+  size_t n = static_cast<size_t>(world_size);
+  size_t step = (count + n - 1) / n;  
+  size_t r = static_cast<size_t>(next.rank);
+  size_t write_ptr = std::min(r * step, count) * type_nbytes;
+  size_t read_ptr = std::min((r + 1) * step, count) * type_nbytes;
+  size_t reduce_ptr = read_ptr;
+  // send recv buffer
+  char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
+  // position to stop reading
+  const size_t stop_read = total_size + write_ptr;
+  // position to stop writing
+  size_t stop_write = total_size + std::min(rank * step, count) * type_nbytes;
+  if (stop_write > stop_read) {
+    stop_write -= total_size;
+    utils::Assert(write_ptr <= stop_write, "write ptr boundary check");
+  }
+  // use ring buffer in next position
+  next.InitBuffer(type_nbytes, step, reduce_buffer_size);
+  // set size_read to read pointer for ring buffer to work properly
+  next.size_read = read_ptr;
+
+  while (true) {
+    // select helper
+    bool finished = true;
+    utils::SelectHelper selecter;
+    if (read_ptr != stop_read) {
+      selecter.WatchRead(next.sock);
+      finished = false;
+    }
+    if (write_ptr != stop_write) {
+      if (write_ptr < reduce_ptr) {
+        selecter.WatchWrite(prev.sock);
+      }
+      finished = false;
+    }
+    if (finished) break;
+    selecter.Select();
+    if (read_ptr != stop_read && selecter.CheckRead(next.sock)) {
+      ReturnType ret = next.ReadToRingBuffer(reduce_ptr, stop_read);
+      if (ret != kSuccess) {
+        return ReportError(&next, ret);
+      }
+      // sync the rate
+      read_ptr = next.size_read;
+      utils::Assert(read_ptr <= stop_read, "[%d] read_ptr boundary check", rank);
+      const size_t buffer_size = next.buffer_size;
+      size_t max_reduce = (read_ptr  / type_nbytes) * type_nbytes;
+      while (reduce_ptr < max_reduce) {
+        size_t bstart = reduce_ptr % buffer_size;
+        size_t nread = std::min(buffer_size - bstart,
+                                max_reduce - reduce_ptr);
+        size_t rstart = reduce_ptr % total_size;
+        nread = std::min(nread, total_size - rstart);
+        reducer(next.buffer_head + bstart,
+                sendrecvbuf + rstart,
+                static_cast<int>(nread / type_nbytes),
+                MPI::Datatype(type_nbytes));
+        reduce_ptr += nread;
+      }
+    }
+    if (write_ptr < reduce_ptr && write_ptr != stop_write) {
+      size_t size = std::min(reduce_ptr, stop_write) - write_ptr;
+      size_t start = write_ptr % total_size;
+      if (start + size > total_size) {
+        size = total_size - start;
+      }
+      ssize_t len = prev.sock.Send(sendrecvbuf + start, size);
+      if (len != -1) {
+        write_ptr += static_cast<size_t>(len);
+      } else {
+        ReturnType ret = Errno2Return(errno);
+        if (ret != kSuccess) return ReportError(&prev, ret);
+      }
+    }
+  }  
+  return kSuccess;
+}
+/*!
+ * \brief perform in-place allreduce, on sendrecvbuf
+ *  use a ring based algorithm
+ *
+ * \param sendrecvbuf_ buffer for both sending and recving data
+ * \param type_nbytes the unit number of bytes the type have
+ * \param count number of elements to be reduced
+ * \param reducer reduce function
+ * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+ * \sa ReturnType
+ */
+AllreduceBase::ReturnType
+AllreduceBase::TryAllreduceRing(void *sendrecvbuf_,
+                                size_t type_nbytes,
+                                size_t count,
+                                ReduceFunction reducer) {
+  ReturnType ret = TryReduceScatterRing(sendrecvbuf_, type_nbytes, count, reducer);
+  if (ret != kSuccess) return ret;
+  size_t n = static_cast<size_t>(world_size);
+  size_t step = (count + n - 1) / n;
+  size_t begin = std::min(rank * step, count) * type_nbytes;
+  size_t end = std::min((rank + 1) * step, count) * type_nbytes;
+  // previous rank
+  int prank = ring_prev->rank;
+  // get rank of previous 
+  return TryAllgatherRing
+      (sendrecvbuf_, type_nbytes * count,
+       begin, end,
+       (std::min((prank + 1) * step, count) -
+        std::min(prank * step, count)) * type_nbytes);
+}
 }  // namespace engine
 }  // namespace rabit