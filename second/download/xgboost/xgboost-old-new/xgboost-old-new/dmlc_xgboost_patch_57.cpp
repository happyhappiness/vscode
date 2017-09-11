@@ -27,7 +27,7 @@ AllreduceRobust::AllreduceRobust(void) {
   result_buffer_round = 1;
   global_lazycheck = NULL;
   use_local_model = -1;
-  recover_counter = 0;  
+  recover_counter = 0;
   env_vars.push_back("rabit_global_replica");
   env_vars.push_back("rabit_local_replica");
 }
@@ -49,7 +49,7 @@ void AllreduceRobust::Shutdown(void) {
   AllreduceBase::Shutdown();
 }
 /*!
- * \brief set parameters to the engine 
+ * \brief set parameters to the engine
  * \param name parameter name
  * \param val parameter value
  */
@@ -61,7 +61,7 @@ void AllreduceRobust::SetParam(const char *name, const char *val) {
   }
 }
 /*!
- * \brief perform in-place allreduce, on sendrecvbuf 
+ * \brief perform in-place allreduce, on sendrecvbuf
  *        this function is NOT thread-safe
  * \param sendrecvbuf_ buffer for both sending and recving data
  * \param type_nbytes the unit number of bytes the type have
@@ -147,14 +147,14 @@ void AllreduceRobust::Broadcast(void *sendrecvbuf_, size_t total_size, int root)
  * \return the version number of check point loaded
  *     if returned version == 0, this means no model has been CheckPointed
  *     the p_model is not touched, user should do necessary initialization by themselves
- *   
+ *
  *   Common usage example:
  *      int iter = rabit::LoadCheckPoint(&model);
  *      if (iter == 0) model.InitParameters();
  *      for (i = iter; i < max_iter; ++i) {
  *        do many things, include allreduce
  *        rabit::CheckPoint(model);
- *      } 
+ *      }
  *
  * \sa CheckPoint, VersionNumber
  */
@@ -208,7 +208,7 @@ int AllreduceRobust::LoadCheckPoint(Serializable *global_model,
  * \brief internal consistency check function,
  *  use check to ensure user always call CheckPoint/LoadCheckPoint
  *  with or without local but not both, this function will set the approperiate settings
- *  in the first call of LoadCheckPoint/CheckPoint 
+ *  in the first call of LoadCheckPoint/CheckPoint
  *
  * \param with_local whether the user calls CheckPoint with local model
  */
@@ -224,14 +224,14 @@ void AllreduceRobust::LocalModelCheck(bool with_local) {
       num_local_replica = 0;
     }
   } else {
-    utils::Check(use_local_model == int(with_local),
+    utils::Check(use_local_model == static_cast<int>(with_local),
                  "Can only call Checkpoint/LoadCheckPoint always with"\
                  "or without local_model, but not mixed case");
   }
 }
 /*!
  * \brief internal implementation of checkpoint, support both lazy and normal way
- * 
+ *
  * \param global_model pointer to the globally shared model/state
  *   when calling this function, the caller need to gauranttees that global_model
  *   is the same in all nodes
@@ -423,7 +423,7 @@ AllreduceRobust::ReturnType AllreduceRobust::TryResetLinks(void) {
  *         recover links according to the error type reported
  *        if there is no error, return true
  * \param err_type the type of error happening in the system
- * \return true if err_type is kSuccess, false otherwise 
+ * \return true if err_type is kSuccess, false otherwise
  */
 bool AllreduceRobust::CheckAndRecover(ReturnType err_type) {
   if (err_type == kSuccess) return true;
@@ -488,7 +488,7 @@ ShortestDist(const std::pair<bool, size_t> &node_value,
  * \brief message passing function, used to decide the
  *    data request from each edge, whether need to request data from certain edge
  * \param node_value a pair of request_data and best_link
- *           request_data stores whether current node need to request data 
+ *           request_data stores whether current node need to request data
  *           best_link gives the best edge index to fetch the data
  * \param req_in the data request from incoming edges
  * \param out_index the edge index of output link
@@ -524,7 +524,7 @@ inline char DataRequest(const std::pair<bool, int> &node_value,
  *
  * \return this function can return kSuccess/kSockError/kGetExcept, see ReturnType for details
  * \sa ReturnType
- */  
+ */
 AllreduceRobust::ReturnType
 AllreduceRobust::TryDecideRouting(AllreduceRobust::RecoverType role,
                                   size_t *p_size,
@@ -586,7 +586,7 @@ AllreduceRobust::TryDecideRouting(AllreduceRobust::RecoverType role,
  *
  * \return this function can return kSuccess/kSockError/kGetExcept, see ReturnType for details
  * \sa ReturnType, TryDecideRouting
- */  
+ */
 AllreduceRobust::ReturnType
 AllreduceRobust::TryRecoverData(RecoverType role,
                                 void *sendrecvbuf_,
@@ -644,7 +644,7 @@ AllreduceRobust::TryRecoverData(RecoverType role,
     if (role == kRequestData) {
       const int pid = recv_link;
       if (selecter.CheckRead(links[pid].sock)) {
-        ReturnType ret = links[pid].ReadToArray(sendrecvbuf_, size);        
+        ReturnType ret = links[pid].ReadToArray(sendrecvbuf_, size);
         if (ret != kSuccess) {
           return ReportError(&links[pid], ret);
         }
@@ -691,7 +691,7 @@ AllreduceRobust::TryRecoverData(RecoverType role,
           if (len != -1) {
             links[i].size_write += len;
           } else {
-            ReturnType ret = Errno2Return(errno);
+            ReturnType ret = Errno2Return();
             if (ret != kSuccess) return ReportError(&links[i], ret);
           }
         }
@@ -823,10 +823,10 @@ AllreduceRobust::TryGetResult(void *sendrecvbuf, size_t size, int seqno, bool re
  * \param buf the buffer to store the result
  * \param size the total size of the buffer
  * \param flag flag information about the action \sa ActionSummary
- * \param seqno sequence number of the action, if it is special action with flag set, 
+ * \param seqno sequence number of the action, if it is special action with flag set,
  *              seqno needs to be set to ActionSummary::kSpecialOp
  *
- * \return if this function can return true or false 
+ * \return if this function can return true or false
  *    - true means buf already set to the
  *           result by recovering procedure, the action is complete, no further action is needed
  *    - false means this is the lastest action that has not yet been executed, need to execute the action
@@ -907,7 +907,7 @@ bool AllreduceRobust::RecoverExec(void *buf, size_t size, int flag, int seqno) {
  *        plus replication of states in previous num_local_replica hops in the ring
  *
  * The input parameters must contain the valid local states available in current nodes,
- * This function try ist best to "complete" the missing parts of local_rptr and local_chkpt 
+ * This function try ist best to "complete" the missing parts of local_rptr and local_chkpt
  * If there is sufficient information in the ring, when the function returns, local_chkpt will
  * contain num_local_replica + 1 checkpoints (including the chkpt of this node)
  * If there is no sufficient information in the ring, this function the number of checkpoints
@@ -1161,7 +1161,7 @@ AllreduceRobust::RingPassing(void *sendrecvbuf_,
       if (len != -1) {
         read_ptr += static_cast<size_t>(len);
       } else {
-        ReturnType ret = Errno2Return(errno);
+        ReturnType ret = Errno2Return();
         if (ret != kSuccess) return ReportError(&prev, ret);
       }
     }
@@ -1171,7 +1171,7 @@ AllreduceRobust::RingPassing(void *sendrecvbuf_,
       if (len != -1) {
         write_ptr += static_cast<size_t>(len);
       } else {
-        ReturnType ret = Errno2Return(errno);
+        ReturnType ret = Errno2Return();
         if (ret != kSuccess) return ReportError(&prev, ret);
       }
     }