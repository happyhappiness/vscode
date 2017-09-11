@@ -159,12 +159,17 @@ void ReduceHandle::Init(IEngine::ReduceFunction redfunc, size_t type_nbytes) {
   utils::Assert(handle_ == NULL, "cannot initialize reduce handle twice");
   if (type_nbytes != 0) {
     MPI::Datatype *dtype = new MPI::Datatype();
-    *dtype = MPI::CHAR.Create_contiguous(type_nbytes);
+    if (type_nbytes % 8 == 0) {
+      *dtype = MPI::LONG.Create_contiguous(type_nbytes / sizeof(long));
+    } else if (type_nbytes % 4 == 0) {
+      *dtype = MPI::INT.Create_contiguous(type_nbytes / sizeof(int));
+    } else {
+      *dtype = MPI::CHAR.Create_contiguous(type_nbytes);
+    }
     dtype->Commit();
     created_type_nbytes_ = type_nbytes;
     htype_ = dtype;
   }
-
   MPI::Op *op = new MPI::Op();
   MPI::User_function *pf = redfunc;
   op->Init(pf, true);
@@ -183,7 +188,13 @@ void ReduceHandle::Allreduce(void *sendrecvbuf,
     } else {
       dtype->Free();
     }
-    *dtype = MPI::CHAR.Create_contiguous(type_nbytes);
+    if (type_nbytes % 8 == 0) {
+      *dtype = MPI::LONG.Create_contiguous(type_nbytes / sizeof(long));
+    } else if (type_nbytes % 4 == 0) {
+      *dtype = MPI::INT.Create_contiguous(type_nbytes / sizeof(int));
+    } else {
+      *dtype = MPI::CHAR.Create_contiguous(type_nbytes);
+    }
     dtype->Commit();
     created_type_nbytes_ = type_nbytes;
   }