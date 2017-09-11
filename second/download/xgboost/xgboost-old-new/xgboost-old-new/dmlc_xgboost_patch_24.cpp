@@ -4,19 +4,19 @@
  * \brief util to compute quantiles
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_UTILS_QUANTILE_H_
-#define XGBOOST_UTILS_QUANTILE_H_
+#ifndef XGBOOST_COMMON_QUANTILE_H_
+#define XGBOOST_COMMON_QUANTILE_H_
 
+#include <dmlc/base.h>
+#include <dmlc/logging.h>
 #include <cmath>
 #include <vector>
 #include <cstring>
 #include <algorithm>
 #include <iostream>
-#include "./io.h"
-#include "./utils.h"
 
 namespace xgboost {
-namespace utils {
+namespace common {
 /*!
  * \brief experimental wsummary
  * \tparam DType type of data content
@@ -35,7 +35,7 @@ struct WQSummary {
     /*! \brief the value of data */
     DType value;
     // constructor
-    Entry(void) {}
+    Entry() {}
     // constructor
     Entry(RType rmin, RType rmax, RType wmin, DType value)
         : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {}
@@ -44,15 +44,15 @@ struct WQSummary {
      * \param eps the tolerate level for violating the relation
      */
     inline void CheckValid(RType eps = 0) const {
-      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
-      utils::Assert(rmax- rmin - wmin > -eps, "relation constraint: min/max");
+      CHECK(rmin >= 0 && rmax >= 0 && wmin >= 0) << "nonneg constraint";
+      CHECK(rmax- rmin - wmin > -eps) <<  "relation constraint: min/max";
     }
     /*! \return rmin estimation for v strictly bigger than value */
-    inline RType rmin_next(void) const {
+    inline RType rmin_next() const {
       return rmin + wmin;
     }
     /*! \return rmax estimation for v strictly smaller than value */
-    inline RType rmax_prev(void) const {
+    inline RType rmax_prev() const {
       return rmax - wmin;
     }
   };
@@ -65,7 +65,7 @@ struct WQSummary {
       // weight of instance
       RType weight;
       // default constructor
-      QEntry(void) {}
+      QEntry() {}
       // constructor
       QEntry(DType value, RType weight)
           : value(value), weight(weight) {}
@@ -113,7 +113,7 @@ struct WQSummary {
   /*!
    * \return the maximum error of the Summary
    */
-  inline RType MaxError(void) const {
+  inline RType MaxError() const {
     RType res = data[0].rmax - data[0].rmin - data[0].wmin;
     for (size_t i = 1; i < size; ++i) {
       res = std::max(data[i].rmax_prev() - data[i - 1].rmin_next(), res);
@@ -147,7 +147,7 @@ struct WQSummary {
     }
   }
   /*! \return maximum rank in the summary */
-  inline RType MaxRank(void) const {
+  inline RType MaxRank() const {
     return data[size - 1].rmax;
   }
   /*!
@@ -168,8 +168,8 @@ struct WQSummary {
     for (size_t i = 0; i < size; ++i) {
       data[i].CheckValid(eps);
       if (i != 0) {
-        utils::Assert(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin, "rmin range constraint");
-        utils::Assert(data[i].rmax >= data[i - 1].rmax + data[i].wmin, "rmax range constraint");
+        CHECK(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin) << "rmin range constraint";
+        CHECK(data[i].rmax >= data[i - 1].rmax + data[i].wmin) << "rmax range constraint";
       }
     }
   }
@@ -196,7 +196,7 @@ struct WQSummary {
       // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2
       while (i < src.size - 1
              && dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
-      utils::Assert(i != src.size - 1, "this cannot happen");
+      CHECK(i != src.size - 1);
       if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
         if (i != lastidx) {
           data[size++] = src.data[i]; lastidx = i;
@@ -224,7 +224,7 @@ struct WQSummary {
     if (sb.size == 0) {
       this->CopyFrom(sa); return;
     }
-    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge");
+    CHECK(sa.size > 0 && sb.size > 0);
     const Entry *a = sa.data, *a_end = sa.data + sa.size;
     const Entry *b = sb.data, *b_end = sb.data + sb.size;
     // extended rmin value
@@ -272,18 +272,19 @@ struct WQSummary {
     RType err_mingap, err_maxgap, err_wgap;
     this->FixError(&err_mingap, &err_maxgap, &err_wgap);
     if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
-      utils::Printf("INFO: mingap=%g, maxgap=%g, wgap=%g\n",
-                    err_mingap, err_maxgap, err_wgap);
+      LOG(INFO) << "mingap=" << err_mingap
+                << ", maxgap=" << err_maxgap
+                << ", wgap=" << err_wgap;
     }
-
-    utils::Assert(size <= sa.size + sb.size, "bug in combine");
+    CHECK(size <= sa.size + sb.size) << "bug in combine";
   }
   // helper function to print the current content of sketch
   inline void Print() const {
     for (size_t i = 0; i < this->size; ++i) {
-      utils::Printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g\n",
-                    i, data[i].rmin, data[i].rmax,
-                    data[i].wmin, data[i].value);
+      LOG(INFO) << "[" << i << "] rmin=" << data[i].rmin
+                << ", rmax=" << data[i].rmax
+                << ", wmin=" << data[i].wmin
+                << ", v=" << data[i].value;
     }
   }
   // try to fix rounding error
@@ -320,7 +321,7 @@ struct WQSummary {
     for (size_t i = 0; i < this->size; ++i) {
       if (data[i].rmin + data[i].wmin > data[i].rmax + tol ||
           data[i].rmin < -1e-6f || data[i].rmax < -1e-6f) {
-        utils::Printf("----%s: Check not Pass------\n", msg);
+        LOG(INFO) << "----------check not pass----------";
         this->Print();
         return false;
       }
@@ -380,12 +381,11 @@ struct WXQSummary : public WQSummary<DType, RType> {
     }
     if (nbig >= n - 1) {
       // see what was the case
-      utils::Printf("LOG: check quantile stats, nbig=%lu, n=%lu\n", nbig, n);
-      utils::Printf("LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
-                    src.size, maxsize, static_cast<double>(range),
-                    static_cast<double>(chunk));
+      LOG(INFO) << " check quantile stats, nbig=" << nbig << ", n=" << n;
+      LOG(INFO) << " srcsize=" << src.size << ", maxsize=" << maxsize
+                << ", range=" << range << ", chunk=" << chunk;
       src.Print();
-      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
+      CHECK(nbig < n - 1) << "quantile: too many large chunk";
     }
     this->data[0] = src.data[0];
     this->size = 1;
@@ -440,7 +440,7 @@ struct GKSummary {
     /*! \brief the value of data */
     DType value;
     // constructor
-    Entry(void) {}
+    Entry() {}
     // constructor
     Entry(RType rmin, RType rmax, DType value)
         : rmin(rmin), rmax(rmax), value(value) {}
@@ -470,15 +470,15 @@ struct GKSummary {
   GKSummary(Entry *data, size_t size)
       : data(data), size(size) {}
   /*! \brief the maximum error of the summary */
-  inline RType MaxError(void) const {
+  inline RType MaxError() const {
     RType res = 0;
     for (size_t i = 1; i < size; ++i) {
       res = std::max(data[i].rmax - data[i-1].rmin, res);
     }
     return res;
   }
   /*! \return maximum rank in the summary */
-  inline RType MaxRank(void) const {
+  inline RType MaxRank() const {
     return data[size - 1].rmax;
   }
   /*!
@@ -493,7 +493,7 @@ struct GKSummary {
     // assume always valid
   }
   /*! \brief used for debug purpose, print the summary */
-  inline void Print(void) const {
+  inline void Print() const {
     for (size_t i = 0; i < size; ++i) {
       std::cout << "x=" << data[i].value << "\t"
                 << "[" << data[i].rmin << "," << data[i].rmax << "]"
@@ -536,7 +536,7 @@ struct GKSummary {
     if (sb.size == 0) {
       this->CopyFrom(sa); return;
     }
-    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge");
+    CHECK(sa.size > 0 && sb.size > 0) << "invalid input for merge";
     const Entry *a = sa.data, *a_end = sa.data + sa.size;
     const Entry *b = sb.data, *b_end = sb.data + sb.size;
     this->size = sa.size + sb.size;
@@ -569,7 +569,7 @@ struct GKSummary {
         ++dst; ++b;
       } while (b != b_end);
     }
-    utils::Assert(dst == data + size, "bug in combine");
+    CHECK(dst == data + size) << "bug in combine";
   }
 };
 
@@ -592,15 +592,15 @@ class QuantileSketchTemplate {
     std::vector<Entry> space;
     SummaryContainer(const SummaryContainer &src) : Summary(NULL, src.size) {
       this->space = src.space;
-      this->data = BeginPtr(this->space);
+      this->data = dmlc::BeginPtr(this->space);
     }
-    SummaryContainer(void) : Summary(NULL, 0) {
+    SummaryContainer() : Summary(NULL, 0) {
     }
     /*! \brief reserve space for summary */
     inline void Reserve(size_t size) {
       if (size > space.size()) {
         space.resize(size);
-        this->data = BeginPtr(space);
+        this->data = dmlc::BeginPtr(space);
       }
     }
     /*!
@@ -610,7 +610,7 @@ class QuantileSketchTemplate {
      */
     inline void SetMerge(const Summary *begin,
                          const Summary *end) {
-      utils::Assert(begin < end, "can not set combine to empty instance");
+      CHECK(begin < end) << "can not set combine to empty instance";
       size_t len = end - begin;
       if (len == 1) {
         this->Reserve(begin[0].size);
@@ -655,11 +655,10 @@ class QuantileSketchTemplate {
     /*! \brief load data structure from input stream */
     template<typename TStream>
     inline void Load(TStream &fi) {  // NOLINT(*)
-      utils::Check(fi.Read(&this->size, sizeof(this->size)) != 0, "invalid SummaryArray 1");
+      CHECK_EQ(fi.Read(&this->size, sizeof(this->size)), sizeof(this->size));
       this->Reserve(this->size);
       if (this->size != 0) {
-        utils::Check(fi.Read(this->data, this->size * sizeof(Entry)) != 0,
-                     "invalid SummaryArray 2");
+        CHECK_EQ(fi.Read(this->data, this->size * sizeof(Entry)), sizeof(this->size));
       }
     }
   };
@@ -678,8 +677,8 @@ class QuantileSketchTemplate {
     }
     // check invariant
     size_t n = (1UL << nlevel);
-    utils::Assert(n * limit_size >= maxn, "invalid init parameter");
-    utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
+    CHECK(n * limit_size >= maxn) << "invalid init parameter";
+    CHECK(nlevel <= limit_size * eps) << "invalid init parameter";
     // lazy reserve the space, if there is only one value, no need to allocate space
     inqueue.queue.resize(1);
     inqueue.qtail = 0;
@@ -707,7 +706,7 @@ class QuantileSketchTemplate {
     inqueue.Push(x, w);
   }
   /*! \brief push up temp */
-  inline void PushTemp(void) {
+  inline void PushTemp() {
     temp.Reserve(limit_size * 2);
     for (size_t l = 1; true; ++l) {
       this->InitLevel(l + 1);
@@ -769,7 +768,7 @@ class QuantileSketchTemplate {
     data.resize(limit_size * nlevel);
     level.resize(nlevel, Summary(NULL, 0));
     for (size_t l = 0; l < level.size(); ++l) {
-      level[l].data = BeginPtr(data) + l * limit_size;
+      level[l].data = dmlc::BeginPtr(data) + l * limit_size;
     }
   }
   // input data queue
@@ -793,7 +792,7 @@ class QuantileSketchTemplate {
  */
 template<typename DType, typename RType = unsigned>
 class WQuantileSketch :
-      public QuantileSketchTemplate<DType, RType, WQSummary<DType, RType> >{
+      public QuantileSketchTemplate<DType, RType, WQSummary<DType, RType> > {
 };
 
 /*!
@@ -803,7 +802,7 @@ class WQuantileSketch :
  */
 template<typename DType, typename RType = unsigned>
 class WXQuantileSketch :
-      public QuantileSketchTemplate<DType, RType, WXQSummary<DType, RType> >{
+      public QuantileSketchTemplate<DType, RType, WXQSummary<DType, RType> > {
 };
 /*!
  * \brief Quantile sketch use WQSummary
@@ -812,9 +811,8 @@ class WXQuantileSketch :
  */
 template<typename DType, typename RType = unsigned>
 class GKQuantileSketch :
-      public QuantileSketchTemplate<DType, RType, GKSummary<DType, RType> >{
+      public QuantileSketchTemplate<DType, RType, GKSummary<DType, RType> > {
 };
-
-}  // namespace utils
+}  // namespace common
 }  // namespace xgboost
-#endif  // XGBOOST_UTILS_QUANTILE_H_
+#endif  // XGBOOST_COMMON_QUANTILE_H_