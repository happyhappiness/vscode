@@ -235,7 +235,7 @@ class SyncManager {
             if (i != parent_index) {
               reducer(links[i].buffer_head + start,
                       sendrecvbuf + size_up_reduce,
-                      nread / type_nbytes,
+                      static_cast<int>(nread / type_nbytes),
                       MPI::Datatype(type_nbytes));
             }
           }
@@ -522,7 +522,7 @@ ReduceHandle::ReduceHandle(void) : handle(NULL), htype(NULL) {
 ReduceHandle::~ReduceHandle(void) {}
 
 int ReduceHandle::TypeSize(const MPI::Datatype &dtype) {
-  return dtype.type_size;
+  return static_cast<int>(dtype.type_size);
 }
 void ReduceHandle::Init(ReduceFunction redfunc, size_t type_n4bytes, bool commute) {
   utils::Assert(handle == NULL, "cannot initialize reduce handle twice");