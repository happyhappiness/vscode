@@ -42,7 +42,7 @@ class AllreduceBase : public IEngine {
   // shutdown the engine
   virtual void Shutdown(void);
   /*!
-   * \brief set parameters to the engine 
+   * \brief set parameters to the engine
    * \param name parameter name
    * \param val parameter value
    */
@@ -72,7 +72,7 @@ class AllreduceBase : public IEngine {
     return host_uri;
   }
   /*!
-   * \brief perform in-place allreduce, on sendrecvbuf 
+   * \brief perform in-place allreduce, on sendrecvbuf
    *        this function is NOT thread-safe
    * \param sendrecvbuf_ buffer for both sending and recving data
    * \param type_nbytes the unit number of bytes the type have
@@ -82,14 +82,15 @@ class AllreduceBase : public IEngine {
    *                     will be called by the function before performing Allreduce, to intialize the data in sendrecvbuf_.
    *                     If the result of Allreduce can be recovered directly, then prepare_func will NOT be called
    * \param prepare_arg argument used to passed into the lazy preprocessing function
-   */  
+   */
   virtual void Allreduce(void *sendrecvbuf_,
                          size_t type_nbytes,
                          size_t count,
                          ReduceFunction reducer,
                          PreprocFunction prepare_fun = NULL,
                          void *prepare_arg = NULL) {
     if (prepare_fun != NULL) prepare_fun(prepare_arg);
+    if (world_size == 1) return;
     utils::Assert(TryAllreduce(sendrecvbuf_,
                                type_nbytes, count, reducer) == kSuccess,
                   "Allreduce failed");
@@ -101,6 +102,7 @@ class AllreduceBase : public IEngine {
    * \param root the root worker id to broadcast the data
    */
   virtual void Broadcast(void *sendrecvbuf_, size_t total_size, int root) {
+    if (world_size == 1) return;
     utils::Assert(TryBroadcast(sendrecvbuf_, total_size, root) == kSuccess,
                   "Broadcast failed");
   }
@@ -115,14 +117,14 @@ class AllreduceBase : public IEngine {
    * \return the version number of check point loaded
    *     if returned version == 0, this means no model has been CheckPointed
    *     the p_model is not touched, user should do necessary initialization by themselves
-   *   
+   *
    *   Common usage example:
    *      int iter = rabit::LoadCheckPoint(&model);
    *      if (iter == 0) model.InitParameters();
    *      for (i = iter; i < max_iter; ++i) {
    *        do many things, include allreduce
    *        rabit::CheckPoint(model);
-   *      } 
+   *      }
    *
    * \sa CheckPoint, VersionNumber
    */
@@ -133,7 +135,7 @@ class AllreduceBase : public IEngine {
   /*!
    * \brief checkpoint the model, meaning we finished a stage of execution
    *  every time we call check point, there is a version number which will increase by one
-   * 
+   *
    * \param global_model pointer to the globally shared model/state
    *   when calling this function, the caller need to gauranttees that global_model
    *   is the same in all nodes
@@ -153,16 +155,16 @@ class AllreduceBase : public IEngine {
   /*!
    * \brief This function can be used to replace CheckPoint for global_model only,
    *   when certain condition is met(see detailed expplaination).
-   * 
+   *
    *   This is a "lazy" checkpoint such that only the pointer to global_model is
    *   remembered and no memory copy is taken. To use this function, the user MUST ensure that:
    *   The global_model must remain unchanged util last call of Allreduce/Broadcast in current version finishs.
-   *   In another words, global_model model can be changed only between last call of 
+   *   In another words, global_model model can be changed only between last call of
    *   Allreduce/Broadcast and LazyCheckPoint in current version
-   *   
+   *
    *   For example, suppose the calling sequence is:
    *   LazyCheckPoint, code1, Allreduce, code2, Broadcast, code3, LazyCheckPoint
-   *   
+   *
    *   If user can only changes global_model in code3, then LazyCheckPoint can be used to
    *   improve efficiency of the program.
    * \param global_model pointer to the globally shared model/state
@@ -189,8 +191,8 @@ class AllreduceBase : public IEngine {
   virtual void InitAfterException(void) {
     utils::Error("InitAfterException: not implemented");
   }
-  /*! 
-   * \brief report current status to the job tracker 
+  /*!
+   * \brief report current status to the job tracker
    * depending on the job tracker we are in
    */
   inline void ReportStatus(void) const {
@@ -211,7 +213,7 @@ class AllreduceBase : public IEngine {
     kRecvZeroLen,
     /*! \brief a neighbor node go down, the connection is dropped */
     kSockError,
-    /*! 
+    /*!
      * \brief another node which is not my neighbor go down,
      *   get Out-of-Band exception notification from my neighbor
      */
@@ -223,7 +225,7 @@ class AllreduceBase : public IEngine {
     ReturnTypeEnum value;
     // constructor
     ReturnType() {}
-    ReturnType(ReturnTypeEnum value) : value(value){}
+    ReturnType(ReturnTypeEnum value) : value(value) {}  // NOLINT(*)
     inline bool operator==(const ReturnTypeEnum &v) const {
       return value == v;
     }
@@ -232,8 +234,13 @@ class AllreduceBase : public IEngine {
     }
   };
   /*! \brief translate errno to return type */
-  inline static ReturnType Errno2Return(int errsv) {
-    if (errsv == EAGAIN || errsv == EWOULDBLOCK) return kSuccess;
+  inline static ReturnType Errno2Return() {
+    int errsv = utils::Socket::GetLastError();
+    if (errsv == EAGAIN || errsv == EWOULDBLOCK || errsv == 0) return kSuccess;
+#ifdef _WIN32
+    if (errsv == WSAEWOULDBLOCK) return kSuccess;
+    if (errsv == WSAECONNRESET) return kConnReset;
+#endif
     if (errsv == ECONNRESET) return kConnReset;
     return kSockError;
   }
@@ -253,7 +260,7 @@ class AllreduceBase : public IEngine {
     // buffer size, in bytes
     size_t buffer_size;
     // constructor
-    LinkRecord(void) 
+    LinkRecord(void)
         : buffer_head(NULL), buffer_size(0) {
     }
     // initialize buffer
@@ -297,7 +304,7 @@ class AllreduceBase : public IEngine {
       if (len == 0) {
         sock.Close(); return kRecvZeroLen;
       }
-      if (len == -1) return Errno2Return(errno);
+      if (len == -1) return Errno2Return();
       size_read += static_cast<size_t>(len);
       return kSuccess;
     }
@@ -316,7 +323,7 @@ class AllreduceBase : public IEngine {
       if (len == 0) {
         sock.Close(); return kRecvZeroLen;
       }
-      if (len == -1) return Errno2Return(errno);
+      if (len == -1) return Errno2Return();
       size_read += static_cast<size_t>(len);
       return kSuccess;
     }
@@ -329,7 +336,7 @@ class AllreduceBase : public IEngine {
     inline ReturnType WriteFromArray(const void *sendbuf_, size_t max_size) {
       const char *p = static_cast<const char*>(sendbuf_);
       ssize_t len = sock.Send(p + size_write, max_size - size_write);
-      if (len == -1) return Errno2Return(errno);
+      if (len == -1) return Errno2Return();
       size_write += static_cast<size_t>(len);
       return kSuccess;
     }
@@ -370,7 +377,7 @@ class AllreduceBase : public IEngine {
    *    The kSuccess TryAllreduce does NOT mean every node have successfully finishes TryAllreduce.
    *    It only means the current node get the correct result of Allreduce.
    *    However, it means every node finishes LAST call(instead of this one) of Allreduce/Bcast
-   * 
+   *
    * \param sendrecvbuf_ buffer for both sending and recving data
    * \param type_nbytes the unit number of bytes the type have
    * \param count number of elements to be reduced
@@ -390,7 +397,7 @@ class AllreduceBase : public IEngine {
    * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
    * \sa ReturnType
    */
-  ReturnType TryBroadcast(void *sendrecvbuf_, size_t size, int root);   
+  ReturnType TryBroadcast(void *sendrecvbuf_, size_t size, int root);
   /*!
    * \brief perform in-place allreduce, on sendrecvbuf,
    * this function implements tree-shape reduction
@@ -426,14 +433,14 @@ class AllreduceBase : public IEngine {
                               size_t size_prev_slice);
   /*!
    * \brief perform in-place allreduce, reduce on the sendrecvbuf,
-   * 
+   *
    *  after the function, node k get k-th segment of the reduction result
    *  the k-th segment is defined by [k * step, min((k + 1) * step,count) )
    *  where step = ceil(count / world_size)
    *
    * \param sendrecvbuf_ buffer for both sending and recving data
    * \param type_nbytes the unit number of bytes the type have
-   * \param count number of elements to be reduced   
+   * \param count number of elements to be reduced
    * \param reducer reduce function
    * \return this function can return kSuccess, kSockError, kGetExcept, see ReturnType for details
    * \sa ReturnType, TryAllreduce
@@ -458,7 +465,7 @@ class AllreduceBase : public IEngine {
                               size_t count,
                               ReduceFunction reducer);
   /*!
-   * \brief function used to report error when a link goes wrong 
+   * \brief function used to report error when a link goes wrong
    * \param link the pointer to the link who causes the error
    * \param err the error type
    */
@@ -512,7 +519,9 @@ class AllreduceBase : public IEngine {
   int rank;
   // world size
   int world_size;
+  // connect retry time
+  int connect_retry;
 };
 }  // namespace engine
 }  // namespace rabit
-#endif  // RABIT_ALLREDUCE_BASE_H
+#endif  // RABIT_ALLREDUCE_BASE_H_