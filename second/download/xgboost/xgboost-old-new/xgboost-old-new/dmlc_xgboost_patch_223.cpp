@@ -186,7 +186,7 @@ struct WQSummary {
    * \param maxsize size we can afford in the pruned sketch
    */
 
-  inline void SetPrune(const WQSummary &src, RType maxsize) {
+  inline void SetPrune(const WQSummary &src, size_t maxsize) {
     if (src.size <= maxsize) {
       this->CopyFrom(src); return;
     }
@@ -290,7 +290,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
     return  e.rmin_next() > e.rmax_prev() + chunk;
   }
   // set prune
-  inline void SetPrune(const WQSummary<DType, RType> &src, RType maxsize) {
+  inline void SetPrune(const WQSummary<DType, RType> &src, size_t maxsize) {
     if (src.size <= maxsize) {
       this->CopyFrom(src); return;
     }
@@ -435,7 +435,7 @@ struct GKSummary {
    * \param src source summary
    * \param maxsize size we can afford in the pruned sketch
    */
-  inline void SetPrune(const GKSummary &src, RType maxsize) {
+  inline void SetPrune(const GKSummary &src, size_t maxsize) {
     if (src.size <= maxsize) {
       this->CopyFrom(src); return;
     }
@@ -597,12 +597,14 @@ class QuantileSketchTemplate {
   inline void Init(size_t maxn, double eps) {
     nlevel = 1;
     while (true) {
-      limit_size = ceil(nlevel / eps) + 1;
-      if ((1 << nlevel)  * limit_size >= maxn) break;
+      limit_size = static_cast<size_t>(ceil(nlevel / eps)) + 1;
+	  size_t n = (1UL << nlevel);
+      if (n * limit_size >= maxn) break;
       ++nlevel;
     }
     // check invariant
-    utils::Assert((1 << nlevel) * limit_size >= maxn, "invalid init parameter");
+	size_t n = (1UL << nlevel);
+    utils::Assert(n * limit_size >= maxn, "invalid init parameter");
     utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
     // lazy reserve the space, if there is only one value, no need to allocate space
     inqueue.queue.resize(1);