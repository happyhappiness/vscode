@@ -5,29 +5,6 @@
 namespace xgboost {
 namespace sync {
 
-// code for reduce handle
-ReduceHandle::ReduceHandle(void) : handle(NULL) {
-}
-ReduceHandle::~ReduceHandle(void) {
-  if (handle != NULL) {
-    MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
-    op->Free();
-    delete op;
-  }
-}
-void ReduceHandle::Init(ReduceFunction redfunc, bool commute) {
-  utils::Assert(handle == NULL, "cannot initialize reduce handle twice");
-  MPI::Op *op = new MPI::Op();
-  MPI::User_function *pf = reinterpret_cast<MPI::User_function*>(redfunc);
-  op->Init(pf, commute);
-  handle = op;
-}
-void ReduceHandle::AllReduce(void *sendrecvbuf, size_t n4byte) {
-  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");  
-  MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
-  MPI::COMM_WORLD.Allreduce(MPI_IN_PLACE, sendrecvbuf, n4byte, MPI_INT, *op);
-}
-
 int GetRank(void) {
   return MPI::COMM_WORLD.Get_rank();
 }
@@ -57,5 +34,37 @@ void AllReduce<float>(float *sendrecvbuf, int count, ReduceOp op) {
   AllReduce_(sendrecvbuf, count, MPI::FLOAT, op);
 }
 
+void Bcast(std::string *sendrecv_data, int root) {
+  unsigned len = static_cast<unsigned>(sendrecv_data->length());
+  MPI::COMM_WORLD.Bcast(&len, 1, MPI::UNSIGNED, root);
+  sendrecv_data->resize(len);
+  if (len != 0) {
+    MPI::COMM_WORLD.Bcast(&(*sendrecv_data)[0], len, MPI::CHAR, root);  
+  }
+}
+
+// code for reduce handle
+ReduceHandle::ReduceHandle(void) : handle(NULL) {
+}
+ReduceHandle::~ReduceHandle(void) {
+  if (handle != NULL) {
+    MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
+    op->Free();
+    delete op;
+  }
+}
+void ReduceHandle::Init(ReduceFunction redfunc, bool commute) {
+  utils::Assert(handle == NULL, "cannot initialize reduce handle twice");
+  MPI::Op *op = new MPI::Op();
+  MPI::User_function *pf = reinterpret_cast<MPI::User_function*>(redfunc);
+  op->Init(pf, commute);
+  handle = op;
+}
+void ReduceHandle::AllReduce(void *sendrecvbuf, size_t n4byte) {
+  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");  
+  MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
+  MPI::COMM_WORLD.Allreduce(MPI_IN_PLACE, sendrecvbuf, n4byte, MPI_INT, *op);
+}
+
 }  // namespace sync
 }  // namespace xgboost