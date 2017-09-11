@@ -3,7 +3,7 @@
  * \file engine_mpi.cc
  * \brief this file gives an implementation of engine interface using MPI,
  *   this will allow rabit program to run with MPI, but do not comes with fault tolerant
- *   
+ *
  * \author Tianqi Chen
  */
 #define _CRT_SECURE_NO_WARNINGS
@@ -110,6 +110,8 @@ inline MPI::Datatype GetType(mpi::DataType dtype) {
     case kULong: return MPI::UNSIGNED_LONG;
     case kFloat: return MPI::FLOAT;
     case kDouble: return MPI::DOUBLE;
+    case kLongLong: return MPI::LONG_LONG;
+    case kULongLong: return MPI::UNSIGNED_LONG_LONG;
   }
   utils::Error("unknown mpi::DataType");
   return MPI::CHAR;
@@ -141,7 +143,7 @@ void Allreduce_(void *sendrecvbuf,
 }
 
 // code for reduce handle
-ReduceHandle::ReduceHandle(void) 
+ReduceHandle::ReduceHandle(void)
     : handle_(NULL), redfunc_(NULL), htype_(NULL) {
 }
 ReduceHandle::~ReduceHandle(void) {
@@ -164,7 +166,7 @@ void ReduceHandle::Init(IEngine::ReduceFunction redfunc, size_t type_nbytes) {
   if (type_nbytes != 0) {
     MPI::Datatype *dtype = new MPI::Datatype();
     if (type_nbytes % 8 == 0) {
-      *dtype = MPI::LONG.Create_contiguous(type_nbytes / sizeof(long));
+      *dtype = MPI::LONG.Create_contiguous(type_nbytes / sizeof(long));  // NOLINT(*)
     } else if (type_nbytes % 4 == 0) {
       *dtype = MPI::INT.Create_contiguous(type_nbytes / sizeof(int));
     } else {
@@ -193,7 +195,7 @@ void ReduceHandle::Allreduce(void *sendrecvbuf,
       dtype->Free();
     }
     if (type_nbytes % 8 == 0) {
-      *dtype = MPI::LONG.Create_contiguous(type_nbytes / sizeof(long));
+      *dtype = MPI::LONG.Create_contiguous(type_nbytes / sizeof(long));  // NOLINT(*)
     } else if (type_nbytes % 4 == 0) {
       *dtype = MPI::INT.Create_contiguous(type_nbytes / sizeof(int));
     } else {