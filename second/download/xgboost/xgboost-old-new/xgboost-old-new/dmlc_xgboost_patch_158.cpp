@@ -278,15 +278,19 @@ class AllreduceBase : public IEngine {
      * \brief read data into ring-buffer, with care not to existing useful override data
      *  position after protect_start
      * \param protect_start all data start from protect_start is still needed in buffer
-     *                      read shall not override this 
+     *                      read shall not override this
+     * \param max_size_read maximum logical amount we can read, size_read cannot exceed this value
      * \return the type of reading
      */
-    inline ReturnType ReadToRingBuffer(size_t protect_start) {
+    inline ReturnType ReadToRingBuffer(size_t protect_start, size_t max_size_read) {
       utils::Assert(buffer_head != NULL, "ReadToRingBuffer: buffer not allocated");
+      utils::Assert(size_read <= max_size_read, "ReadToRingBuffer: max_size_read check");
       size_t ngap = size_read - protect_start;
       utils::Assert(ngap <= buffer_size, "Allreduce: boundary check");
       size_t offset = size_read % buffer_size;
-      size_t nmax = std::min(buffer_size - ngap, buffer_size - offset);
+      size_t nmax = max_size_read - size_read;
+      nmax = std::min(nmax, buffer_size - ngap);
+      nmax = std::min(nmax, buffer_size - offset);
       if (nmax == 0) return kSuccess;
       ssize_t len = sock.Recv(buffer_head + offset, nmax);
       // length equals 0, remote disconnected
@@ -380,13 +384,79 @@ class AllreduceBase : public IEngine {
                           ReduceFunction reducer);
   /*!
    * \brief broadcast data from root to all nodes, this function can fail,and will return the cause of failure
-   * \param sendrecvbuf_ buffer for both sending and recving data
+   * \param sendrecvbuf_ buffer for both sending and receiving data
    * \param size the size of the data to be broadcasted
    * \param root the root worker id to broadcast the data
    * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
    * \sa ReturnType
    */
-  ReturnType TryBroadcast(void *sendrecvbuf_, size_t size, int root);
+  ReturnType TryBroadcast(void *sendrecvbuf_, size_t size, int root);   
+  /*!
+   * \brief perform in-place allreduce, on sendrecvbuf,
+   * this function implements tree-shape reduction
+   *
+   * \param sendrecvbuf_ buffer for both sending and recving data
+   * \param type_nbytes the unit number of bytes the type have
+   * \param count number of elements to be reduced
+   * \param reducer reduce function
+   * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+   * \sa ReturnType
+   */
+  ReturnType TryAllreduceTree(void *sendrecvbuf_,
+                              size_t type_nbytes,
+                              size_t count,
+                              ReduceFunction reducer);
+  /*!
+   * \brief internal Allgather function, each node have a segment of data in the ring of sendrecvbuf,
+   *  the data provided by current node k is [slice_begin, slice_end),
+   *  the next node's segment must start with slice_end
+   *  after the call of Allgather, sendrecvbuf_ contains all the contents including all segments
+   *  use a ring based algorithm
+   *
+   * \param sendrecvbuf_ buffer for both sending and receiving data, it is a ring conceptually
+   * \param total_size total size of data to be gathered
+   * \param slice_begin beginning of the current slice
+   * \param slice_end end of the current slice
+   * \param size_prev_slice size of the previous slice i.e. slice of node (rank - 1) % world_size
+   * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+   * \sa ReturnType
+   */
+  ReturnType TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
+                              size_t slice_begin, size_t slice_end,
+                              size_t size_prev_slice);
+  /*!
+   * \brief perform in-place allreduce, reduce on the sendrecvbuf,
+   * 
+   *  after the function, node k get k-th segment of the reduction result
+   *  the k-th segment is defined by [k * step, min((k + 1) * step,count) )
+   *  where step = ceil(count / world_size)
+   *
+   * \param sendrecvbuf_ buffer for both sending and recving data
+   * \param type_nbytes the unit number of bytes the type have
+   * \param count number of elements to be reduced   
+   * \param reducer reduce function
+   * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+   * \sa ReturnType, TryAllreduce
+   */
+  ReturnType TryReduceScatterRing(void *sendrecvbuf_,
+                                  size_t type_nbytes,
+                                  size_t count,
+                                  ReduceFunction reducer);
+  /*!
+   * \brief perform in-place allreduce, on sendrecvbuf
+   *  use a ring based algorithm, reduce-scatter + allgather
+   *
+   * \param sendrecvbuf_ buffer for both sending and recving data
+   * \param type_nbytes the unit number of bytes the type have
+   * \param count number of elements to be reduced
+   * \param reducer reduce function
+   * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
+   * \sa ReturnType
+   */
+  ReturnType TryAllreduceRing(void *sendrecvbuf_,
+                              size_t type_nbytes,
+                              size_t count,
+                              ReduceFunction reducer);
   /*!
    * \brief function used to report error when a link goes wrong 
    * \param link the pointer to the link who causes the error
@@ -432,6 +502,10 @@ class AllreduceBase : public IEngine {
   int slave_port, nport_trial;
   // reduce buffer size
   size_t reduce_buffer_size;
+  // reduction method
+  int reduce_method;
+  // mininum count of cells to use ring based method
+  size_t reduce_ring_mincount;
   // current rank
   int rank;
   // world size