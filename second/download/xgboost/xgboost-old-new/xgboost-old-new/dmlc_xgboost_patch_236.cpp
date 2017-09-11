@@ -1,6 +1,7 @@
 #include "./sync.h"
 #include "../utils/utils.h"
-#include "mpi.h"
+#include <mpi.h>
+
 // use MPI to implement sync
 namespace xgboost {
 namespace sync {
@@ -60,27 +61,50 @@ void Bcast(std::string *sendrecv_data, int root) {
 }
 
 // code for reduce handle
-ReduceHandle::ReduceHandle(void) : handle(NULL) {
+ReduceHandle::ReduceHandle(void) : handle(NULL), htype(NULL) {
 }
 ReduceHandle::~ReduceHandle(void) {
   if (handle != NULL) {
     MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
     op->Free();
     delete op;
   }
+  if (htype != NULL) {
+    MPI::Datatype *dtype = reinterpret_cast<MPI::Datatype*>(htype);
+    dtype->Free();
+    delete dtype;
+  }
 }
-void ReduceHandle::Init(ReduceFunction redfunc, bool commute) {
+int ReduceHandle::TypeSize(const MPI::Datatype &dtype) {
+  return dtype.Get_size();
+}
+void ReduceHandle::Init(ReduceFunction redfunc, size_t type_n4bytes, bool commute) {
   utils::Assert(handle == NULL, "cannot initialize reduce handle twice");
+  if (type_n4bytes != 0) {
+    MPI::Datatype *dtype = new MPI::Datatype();
+    *dtype = MPI::INT.Create_contiguous(type_n4bytes);
+    dtype->Commit();
+    created_type_n4bytes = type_n4bytes;
+    htype = dtype;
+  }
+  
   MPI::Op *op = new MPI::Op();
-  MPI::User_function *pf = reinterpret_cast<MPI::User_function*>(redfunc);
+  MPI::User_function *pf = redfunc;
   op->Init(pf, commute);
   handle = op;
 }
-void ReduceHandle::AllReduce(void *sendrecvbuf, size_t n4byte) {
-  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");  
+void ReduceHandle::AllReduce(void *sendrecvbuf, size_t type_n4bytes, size_t count) {
+  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");
   MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
-  MPI::COMM_WORLD.Allreduce(MPI_IN_PLACE, sendrecvbuf, n4byte, MPI_INT, *op);
-}
+  MPI::Datatype *dtype = reinterpret_cast<MPI::Datatype*>(htype);
 
+  if (created_type_n4bytes != type_n4bytes || htype == NULL) {
+    dtype->Free();
+    *dtype = MPI::INT.Create_contiguous(type_n4bytes);
+    dtype->Commit();
+    created_type_n4bytes = type_n4bytes;
+  }
+  MPI::COMM_WORLD.Allreduce(MPI_IN_PLACE, sendrecvbuf, count, *dtype, *op);
+}
 }  // namespace sync
 }  // namespace xgboost