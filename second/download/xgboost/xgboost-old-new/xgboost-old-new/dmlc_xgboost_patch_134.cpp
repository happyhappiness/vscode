@@ -296,7 +296,17 @@ struct WXQSummary : public WQSummary<DType, RType> {
     }
     RType begin = src.data[0].rmax;
     size_t n = maxsize - 1, nbig = 0;
-    const RType range = src.data[src.size - 1].rmin - begin;
+    RType range = src.data[src.size - 1].rmin - begin;
+    // prune off zero weights 
+    if (range == 0.0f) {
+      // special case, contain only two effective data pts
+      this->data[0] = src.data[0];
+      this->data[1] = src.data[src.size - 1];
+      this->size = 2;
+      return;
+    } else {
+      range = std::max(range, static_cast<RType>(1e-3f));
+    }
     const RType chunk = 2 * range / n;
     // minimized range
     RType mrange = 0;
@@ -316,7 +326,19 @@ struct WXQSummary : public WQSummary<DType, RType> {
         mrange += src.data[src.size-1].rmax_prev() - src.data[bid].rmin_next();
       }
     }
-    utils::Assert(nbig < n - 1, "too many large chunk");
+    if (nbig >= n - 1) {
+      // see what was the case
+      fprintf(stderr, "LOG: check quantile stats, nbig=%lu, n=%lu\n", nbig, n);
+      fprintf(stderr, "LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
+              src.size, maxsize, static_cast<double>(range),
+              static_cast<double>(chunk));      
+      for (size_t i = 0; i < src.size; ++i) {
+        printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g, isbig=%d\n", i,
+               src.data[i].rmin, src.data[i].rmax,  src.data[i].wmin,
+               src.data[i].value, CheckLarge(src.data[i], chunk));
+      }
+      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
+    }
     this->data[0] = src.data[0];
     this->size = 1;
     // use smaller size
@@ -619,6 +641,7 @@ class QuantileSketchTemplate {
    * \param x the elemented added to the sketch
    */
   inline void Push(DType x, RType w = 1) {
+    if (w == static_cast<RType>(0)) return;
     if (inqueue.qtail == inqueue.queue.size()) {
       // jump from lazy one value to limit_size * 2
       if (inqueue.queue.size() == 1) {