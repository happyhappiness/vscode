@@ -4,6 +4,7 @@
  *   with use async socket and tree-shape reduction
  * \author Tianqi Chen
  */
+#include <vector>
 #include "./sync.h"
 #include "../utils/socket.h"
 
@@ -23,8 +24,8 @@ class SyncManager {
   }
   /*!
    * \brief perform in-place allreduce, on sendrecvbuf 
-   *        this function is not thread-safe
-   * \param sendrecvbuf buffer for both sending and recving data
+   *        this function is NOT thread-safe
+   * \param sendrecvbuf_ buffer for both sending and recving data
    * \param type_n4bytes the unit number of bytes the type have
    * \param count number of elements to be reduced
    * \param reducer reduce function
@@ -33,79 +34,83 @@ class SyncManager {
                         size_t type_nbytes,
                         size_t count,
                         ReduceHandle::ReduceFunction reducer) {
-    if (parent.size() == 0 && childs.size() == 0) return;
-    char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
+    if (links.size() == 0) return;
     // total size of message
     const size_t total_size = type_nbytes * count;
+    // number of links
+    const int nlink = static_cast<int>(links.size());
+    // send recv buffer
+    char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
     // size of space that we already performs reduce in up pass
     size_t size_up_reduce = 0;
     // size of space that we have already passed to parent
     size_t size_up_out = 0;
     // size of message we received, and send in the down pass
-    size_t size_down_in = 0;
-    // initialize the send buffer
-    for (size_t i = 0; i < childs.size(); ++i) {
-      childs[i].Init(type_nbytes, count);
+    size_t size_down_in = 0;    
+
+    // initialize the link ring-buffer and pointer
+    for (int i = 0; i < nlink; ++i) {
+      if (i != parent_index) links[i].InitBuffer(type_nbytes, count);
+      links[i].ResetSize();
     }
     // if no childs, no need to reduce
-    if (childs.size() == 0) size_up_reduce = total_size;    
+    if (nlink == static_cast<int>(parent_index != -1)) {
+      size_up_reduce = total_size;
+    }
+    
     // while we have not passed the messages out
     while(true) {
       selecter.Select();
       // read data from childs
-      for (size_t i = 0; i < childs.size(); ++i) {
-        if (selecter.CheckRead(childs[i].sock)) {
-          childs[i].Read(size_up_out);
+      for (int i = 0; i < nlink; ++i) {
+        if (i != parent_index && selecter.CheckRead(links[i].sock)) {
+          links[i].ReadToRingBuffer(size_up_out);
         }
       }
-      // peform reduce
-      if (childs.size() != 0) {
-        const size_t buffer_size = childs[0].buffer_size;
+      // this node have childs, peform reduce
+      if (nlink > static_cast<int>(parent_index != -1)) {
+        size_t buffer_size = 0;
         // do upstream reduce
-        size_t min_read = childs[0].size_read;
-        for (size_t i = 1; i < childs.size(); ++i) {
-          min_read = std::min(min_read, childs[i].size_read);
-        }
-        // align to type_nbytes
-        min_read = (min_read / type_nbytes * type_nbytes);
-        // start position
-        size_t start = size_up_reduce % buffer_size;
-        // peform read till end of buffer
-        if (start + min_read - size_up_reduce > buffer_size) {
-          const size_t nread = buffer_size - start;
-          utils::Assert(nread % type_nbytes == 0, "AllReduce: size check");
-          for (size_t i = 0; i < childs.size(); ++i) {
-            reducer(childs[i].buffer_head + start,
-                    sendrecvbuf + size_up_reduce,
-                    nread / type_nbytes,
-                    MPI::Datatype(type_nbytes));
+        size_t max_reduce = total_size;
+        for (int i = 0; i < nlink; ++i) {
+          if (i != parent_index) {
+            max_reduce= std::min(max_reduce, links[i].size_read);
+            utils::Assert(buffer_size == 0 || buffer_size == links[i].buffer_size,
+                          "buffer size inconsistent");
+            buffer_size = links[i].buffer_size;
           }
-          size_up_reduce += nread;
-          start = 0;
         }
-        // peform second phase of reduce
-        const size_t nread = min_read - size_up_reduce;
-        if (nread != 0) {
+        utils::Assert(buffer_size != 0, "must assign buffer_size");
+        // round to type_n4bytes
+        max_reduce = (max_reduce / type_nbytes * type_nbytes);
+        // peform reduce, can be at most two rounds
+        while (size_up_reduce < max_reduce) {
+          // start position
+          size_t start = size_up_reduce % buffer_size;
+          // peform read till end of buffer
+          size_t nread = std::min(buffer_size - start, max_reduce - size_up_reduce);          
           utils::Assert(nread % type_nbytes == 0, "AllReduce: size check");
-          for (size_t i = 0; i < childs.size(); ++i) {
-            reducer(childs[i].buffer_head + start,
-                    sendrecvbuf + size_up_reduce,
-                    nread / type_nbytes,
-                    MPI::Datatype(type_nbytes));
+          for (int i = 0; i < nlink; ++i) {
+            if (i != parent_index) {
+              reducer(links[i].buffer_head + start,
+                      sendrecvbuf + size_up_reduce,
+                      nread / type_nbytes,
+                      MPI::Datatype(type_nbytes));
+            }
           }
+          size_up_reduce += nread;
         }
-        size_up_reduce += nread;
       }
-      if (parent.size() != 0) {
-        // can pass message up to parent
-        if (selecter.CheckWrite(parent[0])) {
-          size_up_out += parent[0]
-              .Send(sendrecvbuf + size_up_out, size_up_reduce - size_up_out);
+      if (parent_index != -1) {
+        // pass message up to parent, can pass data that are already been reduced
+        if (selecter.CheckWrite(links[parent_index].sock)) {
+          size_up_out += links[parent_index].sock.
+              Send(sendrecvbuf + size_up_out, size_up_reduce - size_up_out);
         }
         // read data from parent
-        if (selecter.CheckRead(parent[0])) {
-          size_down_in +=  parent[0]
-              .Recv(sendrecvbuf + size_down_in, total_size - size_down_in);
+        if (selecter.CheckRead(links[parent_index].sock)) {
+          size_down_in +=  links[parent_index].sock.
+              Recv(sendrecvbuf + size_down_in, total_size - size_down_in);
           utils::Assert(size_down_in <= size_up_out, "AllReduce: boundary error");
         }
       } else {
@@ -115,150 +120,138 @@ class SyncManager {
       // check if we finished the job of message passing
       size_t nfinished = size_down_in;
       // can pass message down to childs
-      for (size_t i = 0; i < childs.size(); ++i) {
-        if (selecter.CheckWrite(childs[i].sock)) {
-          childs[i].size_write += childs[i].sock
-              .Send(sendrecvbuf + childs[i].size_write, size_down_in - childs[i].size_write);
+      for (int i = 0; i < nlink; ++i) {
+        if (i != parent_index && selecter.CheckWrite(links[i].sock)) {
+          links[i].WriteFromArray(sendrecvbuf, size_down_in);
+          nfinished = std::min(links[i].size_write, nfinished);
         }
-        nfinished = std::min(childs[i].size_write, nfinished);
       }
       // check boundary condition
-      if (nfinished >= total_size) {
-        utils::Assert(nfinished == total_size, "AllReduce: nfinished check");
-        break;
-      }
+      if (nfinished >= total_size) break;
     }
   }
-  inline void Bcast(std::string *sendrecv_data, int root) {
-    if (parent.size() == 0 && childs.size() == 0) return;
-    // message send to parent
-    size_t size_up_out = 0;
-    // all messages received
+  /*!
+   * \brief broadcast data from root to all nodes
+   * \param sendrecvbuf_ buffer for both sending and recving data
+   * \param type_n4bytes the unit number of bytes the type have
+   * \param count number of elements to be reduced
+   * \param reducer reduce function
+   */  
+  inline void Bcast(void *sendrecvbuf_,
+                    size_t total_size,
+                    int root) {
+    if (links.size() == 0) return;
+    // number of links
+    const int nlink = static_cast<int>(links.size());
+    // size of space already read from data
     size_t size_in = 0;
-    // all headers received so far
-    size_t header_in = 0;
-    // total size of data
-    size_t total_size;
-    // input channel, -1 means parent, -2 means unknown yet
-    // otherwise its child index
-    int in_channel = -2;
-    // root already reads all data in
-    if (root == rank) {
-      in_channel = -3;
-      total_size = size_in = sendrecv_data->length();
-      header_in = sizeof(total_size);
+    // input link, -2 means unknown yet, -1 means this is root
+    int in_link = -2;
+
+    // initialize the link statistics
+    for (int i = 0; i < nlink; ++i) {
+      links[i].ResetSize();
     }
-    // initialize write position
-    for (size_t i = 0; i < childs.size(); ++i) {
-      childs[i].size_write = 0;
+    // root have all the data
+    if (this->rank == root) {
+      size_in = total_size;
+      in_link = -1;
     }
-    const int nchilds = static_cast<int>(childs.size());
-
-    while (true) {
+    
+    // while we have not passed the messages out
+    while(true) {
       selecter.Select();
-      if (selecter.CheckRead(parent[0])) {
-        utils::Assert(in_channel == -2 || in_channel == -1, "invalid in channel");
-        this->BcastRecvData(parent[0], sendrecv_data,
-                            header_in, size_in, total_size);
-        if (header_in != 0) in_channel = -1;
-      }
-      for (int i = 0; i < nchilds; ++i) {
-        if (selecter.CheckRead(childs[i].sock)) {
-          utils::Assert(in_channel == -2 || in_channel == i, "invalid in channel");
-          this->BcastRecvData(parent[0], sendrecv_data,
-                              header_in, size_in, total_size);
-          if (header_in != 0) in_channel = i;
-        }
-      }
-      if (in_channel == -2) continue;
-      if (in_channel != -1) {
-        if (selecter.CheckWrite(parent[0])) {
-          size_t nsend = size_in - size_up_out;
-          if (nsend != 0) {
-            size_up_out += parent[0].Send(&(*sendrecv_data)[0] + size_up_out, nsend);
+      if (in_link == -2) {
+        // probe in-link
+        for (int i = 0; i < nlink; ++i) {
+          if (selecter.CheckRead(links[i].sock)) {
+            links[i].ReadToArray(sendrecvbuf_, total_size);
+            size_in = links[i].size_read;
+            if (size_in != 0) {
+              in_link = i; break;
+            }
           }
         }
       } else {
-        size_up_out = size_in;
+        // read from in link
+        if (in_link >= 0 && selecter.CheckRead(links[in_link].sock)) {
+          links[in_link].ReadToArray(sendrecvbuf_, total_size);
+          size_in = links[in_link].size_read;
+        }
       }
-      size_t nfinished = size_up_out;
-      for (int i = 0; i < nchilds; ++i) {
-        if (in_channel != i) {
-          if (selecter.CheckWrite(childs[i].sock)) {
-            size_t nsend = size_in - childs[i].size_write;
-            if (nsend != 0) {
-              childs[i].size_write += childs[i].sock
-                  .Send(&(*sendrecv_data)[0] + childs[i].size_write, nsend);
-            }
-          }
-          nfinished = std::min(nfinished, childs[i].size_write);
+      size_t nfinished = total_size;
+      // send data to all out-link
+      for (int i = 0; i < nlink; ++i) {
+        if (i != in_link && selecter.CheckWrite(links[i].sock)) {
+          links[i].WriteFromArray(sendrecvbuf_, size_in);
+          nfinished = std::min(nfinished, links[i].size_write);
         }
       }
       // check boundary condition
-      if (nfinished >= total_size) {
-        utils::Assert(nfinished == total_size, "Bcast: nfinished check");
-        break;
-      }
+      if (nfinished >= total_size) break;
     }
   }
-
- private:
-  inline void BcastRecvData(utils::TCPSocket &sock,
-                            std::string *sendrecv_data,   
-                            size_t &header_in,
-                            size_t &size_in,
-                            size_t &total_size) {
-    if (header_in < sizeof(total_size)) {
-      char *p = reinterpret_cast<char*>(&total_size);
-      header_in += sock.Recv(p + size_in, sizeof(total_size) - header_in);
-      if (header_in == sizeof(total_size)) {
-        sendrecv_data->resize(total_size);
-      }
-    } else {
-      size_t nread  = total_size - size_in;
-      if (nread != 0) {
-        size_in += sock
-            .Recv(&(*sendrecv_data)[0] + size_in, nread);
-      }
-    }
-  }
-  
+ private:  
   // 128 MB
   const static size_t kBufferSize = 128;
   // an independent child record
-  struct ChildRecord {
+  struct LinkRecord {
    public:
-    // socket to get data from child
+    // socket to get data from/to link
     utils::TCPSocket sock;
-    // size of data readed from child
+    // size of data readed from link
     size_t size_read;
-    // size of data write into child
+    // size of data sent to the link
     size_t size_write;
     // pointer to buffer head
     char *buffer_head;
     // buffer size, in bytes
     size_t buffer_size;
     // initialize buffer
-    inline void Init(size_t type_nbytes, size_t count) {
+    inline void InitBuffer(size_t type_nbytes, size_t count) {
       utils::Assert(type_nbytes < kBufferSize, "too large type_nbytes");
       size_t n = (type_nbytes * count + 7)/ 8;
       buffer_.resize(std::min(kBufferSize, n));
       // make sure align to type_nbytes
       buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
       // set buffer head
       buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
-      // set write head
+    }
+    // reset the recv and sent size
+    inline void ResetSize(void) {
       size_write = size_read = 0;
     }
-    // maximum number of bytes we are able to read
-    // currently without corrupt the data
-    inline void Read(size_t size_up_out) {
-      size_t ngap = size_read - size_up_out;
+    /*! 
+     * \brief read data into ring-buffer, with care not to existing useful override data
+     *  position after protect_start
+     * \param protect_start all data start from protect_start is still needed in buffer
+     *                      read shall not override this 
+     */
+    inline void ReadToRingBuffer(size_t protect_start) {
+      size_t ngap = size_read - protect_start;
       utils::Assert(ngap <= buffer_size, "AllReduce: boundary check");
-      size_t offset = size_read % buffer_size;      
-      size_t nmax = std::min(ngap, buffer_size - offset);
-      size_t len = sock.Recv(buffer_head + offset, nmax);
-      size_read += len;
+      size_t offset = size_read % buffer_size;
+      size_t nmax = std::min(buffer_size - ngap, buffer_size - offset);
+      size_read += sock.Recv(buffer_head + offset, nmax);
+    }
+    /*!
+     * \brief read data into array,
+     * this function can not be used together with ReadToRingBuffer
+     * a link can either read into the ring buffer, or existing array
+     * \param max_size maximum size of array
+     */
+    inline void ReadToArray(void *recvbuf_, size_t max_size) {
+      char *p = static_cast<char*>(recvbuf_);
+      size_read += sock.Recv(p + size_read, max_size - size_read);
+    }
+    /*!
+     * \brief write data in array to sock
+     * \param sendbuf_ head of array
+     * \param max_size maximum size of array
+     */
+    inline void WriteFromArray(const void *sendbuf_, size_t max_size) {
+      const char *p = static_cast<const char*>(sendbuf_);
+      size_write += sock.Send(p + size_write, max_size - size_write);
     }
 
    private:
@@ -267,11 +260,11 @@ class SyncManager {
     std::vector<uint64_t> buffer_;
   };
   // current rank
-  int rank;                  
-  // parent socket, can be of size 0 or 1
-  std::vector<utils::TCPSocket> parent;
-  // sockets of all childs, can be of size 0, 1, 2 or more
-  std::vector<ChildRecord> childs;
+  int rank;
+  // index of parent link, can be -1, meaning this is root of the tree
+  int parent_index;
+  // sockets of all links
+  std::vector<LinkRecord> links;
   // select helper
   utils::SelectHelper selecter;
 };