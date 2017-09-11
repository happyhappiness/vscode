@@ -222,20 +222,15 @@ class WQuantileSketch {
   };
   /*! 
    * \brief intialize the quantile sketch, given the performance specification
-   * \param maxn maximum number of data points can be encountered
+   * \param maxn maximum number of data points can be feed into sketch
    * \param eps accuracy level of summary
    */
-  inline void Init(RType maxn, double eps) {
-    nlevel = 0;
-    size_t b = std::max(floor(log2(eps * maxn) / eps), 8.0);
-    // check for small n case
-    while (b < maxn) {
-      nlevel = ceil(log2(maxn / b)) + 1;
-      if (nlevel < eps * b) break;
-      ++b;
-    }
-    nlevel += 1;
-    limit_size = (b + 1) / 2 + 1;
+  inline void Init(size_t maxn, double eps) {
+    nlevel = std::max(ceil(maxn * eps), 1.0);
+    limit_size = ceil(nlevel / eps);
+    // check invariant
+    utils::Assert((1 << nlevel)  * limit_size > maxn, "invalid init parameter");
+    utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
     // lazy reserve the space, if there is only one value, no need to allocate space
     inqueue.resize(1);
     qtail = 0;
@@ -281,7 +276,7 @@ class WQuantileSketch {
     } else {
       inqueue[qtail - 1].weight += w;
     }
-  } 
+  }
   /*! \brief get the summary after finalize */
   inline void GetSummary(SummaryContainer *out) {
     if (level.size() != 0) {