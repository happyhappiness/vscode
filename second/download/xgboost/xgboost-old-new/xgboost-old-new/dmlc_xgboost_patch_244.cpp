@@ -1,7 +1,7 @@
 #ifndef XGBOOST_UTILS_QUANTILE_H_
 #define XGBOOST_UTILS_QUANTILE_H_
 /*!
- * \file quantile
+ * \file quantile.h
  * \brief util to compute quantiles 
  * \author Tianqi Chen
  */
@@ -14,7 +14,6 @@
 
 namespace xgboost {
 namespace utils {
-
 /*!
  * \brief experimental wsummary
  * \tparam DType type of data content
@@ -172,7 +171,7 @@ struct WQSummary {
     this->size = 1;
     // lastidx is used to avoid duplicated records
     size_t i = 1, lastidx = 0;
-    for (RType k = 1; k < n; ++k) {
+    for (size_t k = 1; k < n; ++k) {
       RType dx2 =  2 * ((k * range) / n + begin);
       // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2 
       while (i < src.size - 1 &&
@@ -246,7 +245,84 @@ struct WQSummary {
     utils::Assert(size <= sa.size + sb.size, "bug in combine");
   }
 };
-
+/*! \brief try to do efficient prunning */
+template<typename DType, typename RType>
+struct WXQSummary : public WQSummary<DType, RType> {
+  // redefine entry type
+  typedef typename WQSummary<DType, RType>::Entry Entry;
+  // constructor
+  WXQSummary(Entry *data, size_t size)
+      : WQSummary<DType, RType>(data, size) {}
+  // check if the block is large chunk
+  inline static bool CheckLarge(const Entry &e, RType chunk) {
+    return  e.rmin_next() > e.rmax_prev() + chunk;
+  }
+  // set prune
+  inline void SetPrune(const WXQSummary &src, RType maxsize) {
+    if (src.size <= maxsize) {
+      this->CopyFrom(src); return;
+    }
+    RType begin = src.data[0].rmax;
+    size_t n = maxsize - 1, nbig = 0;
+    const RType range = src.data[src.size - 1].rmin - begin;
+    const RType chunk = 2 * range / n;
+    // minimized range
+    RType mrange = 0;
+    {
+      // first scan, grab all the big chunk
+      // moviing block index
+      size_t bid = 0;
+      for (size_t i = 1; i < src.size; ++i) {
+        if (CheckLarge(src.data[i], chunk)) {
+          if (bid != i - 1) {
+            mrange += src.data[i].rmax_prev() - src.data[bid].rmin_next();
+          }
+          bid = i; ++nbig;
+        }
+      }
+      if (bid != src.size - 2) {
+        mrange += src.data[src.size-1].rmax_prev() - src.data[bid].rmin_next();
+      }
+    }
+    utils::Assert(nbig < n - 1, "too many large chunk");
+    this->data[0] = src.data[0];
+    this->size = 1;
+    // use smaller size
+    n = n - nbig;
+    // find the rest of point
+    size_t bid = 0, k = 1, lastidx = 0;
+    for (size_t end = 1; end < src.size; ++end) {
+      if (end == src.size - 1 || CheckLarge(src.data[end], chunk)) {
+        if (bid != end - 1) {
+          size_t i = bid;
+          RType maxdx2 = src.data[end].rmax_prev() * 2;
+          for (; k < n; ++k) {
+            RType dx2 =  2 * ((k * mrange) / n + begin);
+            if (dx2 >= maxdx2) break; 
+            while (i < end &&
+                   dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
+            if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
+              if (i != lastidx) {
+                this->data[this->size++] = src.data[i]; lastidx = i;
+              }
+            } else {
+              if (i + 1 != lastidx) {
+                this->data[this->size++] = src.data[i + 1]; lastidx = i + 1;
+              }
+            }
+          }
+        }
+        if (lastidx != end) {
+          this->data[this->size++] = src.data[end];
+          lastidx = end;
+        }
+        bid = end;
+        // shift base by the gap 
+        begin += src.data[bid].rmin_next() - src.data[bid].rmax_prev();
+      }
+    }
+  }
+};
 /*! 
  * \brief traditional GK summary
  */
@@ -564,6 +640,16 @@ template<typename DType, typename RType=unsigned>
 class WQuantileSketch : 
       public QuantileSketchTemplate<DType, RType, WQSummary<DType, RType> >{
 };
+
+/*!
+ * \brief Quantile sketch use WXQSummary
+ * \tparam DType type of data content
+ * \tparam RType type of rank
+ */
+template<typename DType, typename RType=unsigned>
+class WXQuantileSketch : 
+      public QuantileSketchTemplate<DType, RType, WXQSummary<DType, RType> >{
+};
 /*!
  * \brief Quantile sketch use WQSummary
  * \tparam DType type of data content