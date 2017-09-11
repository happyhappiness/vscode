@@ -97,9 +97,12 @@ void ReduceHandle::AllReduce(void *sendrecvbuf, size_t type_n4bytes, size_t coun
   utils::Assert(handle != NULL, "must intialize handle to call AllReduce");
   MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
   MPI::Datatype *dtype = reinterpret_cast<MPI::Datatype*>(htype);
-
-  if (created_type_n4bytes != type_n4bytes || htype == NULL) {
-    dtype->Free();
+  if (created_type_n4bytes != type_n4bytes || dtype == NULL) {
+    if (dtype == NULL) {
+      dtype = new MPI::Datatype();
+    } else {
+      dtype->Free();
+    }
     *dtype = MPI::INT.Create_contiguous(type_n4bytes);
     dtype->Commit();
     created_type_n4bytes = type_n4bytes;