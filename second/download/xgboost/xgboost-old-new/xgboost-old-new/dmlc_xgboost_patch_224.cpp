@@ -352,7 +352,7 @@ class SyncManager {
       buffer_.resize(std::min(reduce_buffer_size, n));
       // make sure align to type_nbytes
       buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
-      utils::Assert(type_nbytes < buffer_size, "too large type_nbytes=%lu, buffer_size", type_nbytes, buffer_size);
+      utils::Assert(type_nbytes <= buffer_size, "too large type_nbytes=%lu, buffer_size=%lu", type_nbytes, buffer_size);
       // set buffer head
       buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
     }
@@ -487,6 +487,8 @@ void AllReduce<uint32_t>(uint32_t *sendrecvbuf, int count, ReduceOp op) {
   typedef uint32_t DType;
   switch(op) {
     case kBitwiseOR: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceBitOR<DType>); return;
+    case kSum: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceSum<DType>); return;
+    case kMax: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceMax<DType>); return;
     default: utils::Error("reduce op not supported");
   }
 }