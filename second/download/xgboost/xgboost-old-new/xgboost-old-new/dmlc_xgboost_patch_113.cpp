@@ -1,10 +1,12 @@
-#ifndef XGBOOST_UTILS_QUANTILE_H_
-#define XGBOOST_UTILS_QUANTILE_H_
 /*!
+ * Copyright 2014 by Contributors
  * \file quantile.h
- * \brief util to compute quantiles 
+ * \brief util to compute quantiles
  * \author Tianqi Chen
  */
+#ifndef XGBOOST_UTILS_QUANTILE_H_
+#define XGBOOST_UTILS_QUANTILE_H_
+
 #include <cmath>
 #include <vector>
 #include <cstring>
@@ -37,8 +39,8 @@ struct WQSummary {
     // constructor
     Entry(RType rmin, RType rmax, RType wmin, DType value)
         : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {}
-    /*! 
-     * \brief debug function,  check Valid 
+    /*!
+     * \brief debug function,  check Valid
      * \param eps the tolerate level for violating the relation
      */
     inline void CheckValid(RType eps = 0) const {
@@ -65,7 +67,7 @@ struct WQSummary {
       // default constructor
       QEntry(void) {}
       // constructor
-      QEntry(DType value, RType weight) 
+      QEntry(DType value, RType weight)
           : value(value), weight(weight) {}
       // comparator on value
       inline bool operator<(const QEntry &b) const {
@@ -83,11 +85,11 @@ struct WQSummary {
       } else {
         queue[qtail - 1].weight += w;
       }
-    }   
+    }
     inline void MakeSummary(WQSummary *out) {
       std::sort(queue.begin(), queue.begin() + qtail);
       out->size = 0;
-      // start update sketch      
+      // start update sketch
       RType wsum = 0;
       // construct data with unique weights
       for (size_t i = 0; i < qtail;) {
@@ -106,7 +108,7 @@ struct WQSummary {
   /*! \brief number of elements in the summary */
   size_t size;
   // constructor
-  WQSummary(Entry *data, size_t size) 
+  WQSummary(Entry *data, size_t size)
       : data(data), size(size) {}
   /*!
    * \return the maximum error of the Summary
@@ -119,12 +121,12 @@ struct WQSummary {
     }
     return res;
   }
-  /*! 
+  /*!
    * \brief query qvalue, start from istart
    * \param qvalue the value we query for
    * \param istart starting position
    */
-  inline Entry Query(DType qvalue, size_t &istart) const {
+  inline Entry Query(DType qvalue, size_t &istart) const { // NOLINT(*)
     while (istart < size && qvalue > data[istart].value) {
       ++istart;
     }
@@ -136,7 +138,7 @@ struct WQSummary {
       return data[istart];
     } else {
       if (istart == 0) {
-        return Entry(0.0f, 0.0f, 0.0f, qvalue);    
+        return Entry(0.0f, 0.0f, 0.0f, qvalue);
       } else {
         return Entry(data[istart - 1].rmin_next(),
                      data[istart].rmax_prev(),
@@ -154,12 +156,12 @@ struct WQSummary {
    */
   inline void CopyFrom(const WQSummary &src) {
     size = src.size;
-    std::memcpy(data, src.data, sizeof(Entry) * size);    
-  }  
-  /*! 
-   * \brief debug function, validate whether the summary 
+    std::memcpy(data, src.data, sizeof(Entry) * size);
+  }
+  /*!
+   * \brief debug function, validate whether the summary
    *  run consistency check to check if it is a valid summary
-   * \param eps the tolerate error level, used when RType is floating point and 
+   * \param eps the tolerate error level, used when RType is floating point and
    *        some inconsistency could occur due to rounding error
    */
   inline void CheckValid(RType eps) const {
@@ -199,8 +201,8 @@ struct WQSummary {
     size_t i = 1, lastidx = 0;
     for (size_t k = 1; k < n; ++k) {
       RType dx2 =  2 * ((k * range) / n + begin);
-      // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2 
-      while (i < src.size - 1 
+      // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2
+      while (i < src.size - 1
              && dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
       utils::Assert(i != src.size - 1, "this cannot happen");
       if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
@@ -217,7 +219,7 @@ struct WQSummary {
       data[size++] = src.data[src.size - 1];
     }
   }
-  /*! 
+  /*!
    * \brief set current summary to be merged summary of sa and sb
    * \param sa first input summary to be merged
    * \param sb second input summar to be merged
@@ -230,7 +232,7 @@ struct WQSummary {
     if (sb.size == 0) {
       this->CopyFrom(sa); return;
     }
-    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
+    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge");
     const Entry *a = sa.data, *a_end = sa.data + sa.size;
     const Entry *b = sb.data, *b_end = sb.data + sb.size;
     // extended rmin value
@@ -297,7 +299,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
     RType begin = src.data[0].rmax;
     size_t n = maxsize - 1, nbig = 0;
     RType range = src.data[src.size - 1].rmin - begin;
-    // prune off zero weights 
+    // prune off zero weights
     if (range == 0.0f) {
       // special case, contain only two effective data pts
       this->data[0] = src.data[0];
@@ -331,7 +333,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
       utils::Printf("LOG: check quantile stats, nbig=%lu, n=%lu\n", nbig, n);
       utils::Printf("LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
                     src.size, maxsize, static_cast<double>(range),
-                    static_cast<double>(chunk));      
+                    static_cast<double>(chunk));
       for (size_t i = 0; i < src.size; ++i) {
         utils::Printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g, isbig=%d\n", i,
                       src.data[i].rmin, src.data[i].rmax,  src.data[i].wmin,
@@ -352,7 +354,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
           RType maxdx2 = src.data[end].rmax_prev() * 2;
           for (; k < n; ++k) {
             RType dx2 =  2 * ((k * mrange) / n + begin);
-            if (dx2 >= maxdx2) break; 
+            if (dx2 >= maxdx2) break;
             while (i < end &&
                    dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
             if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
@@ -371,13 +373,13 @@ struct WXQSummary : public WQSummary<DType, RType> {
           lastidx = end;
         }
         bid = end;
-        // shift base by the gap 
+        // shift base by the gap
         begin += src.data[bid].rmin_next() - src.data[bid].rmax_prev();
       }
     }
   }
 };
-/*! 
+/*!
  * \brief traditional GK summary
  */
 template<typename DType, typename RType>
@@ -405,7 +407,7 @@ struct GKSummary {
     // push data to the queue
     inline void Push(DType x, RType w) {
       queue[qtail++] = x;
-    }   
+    }
     inline void MakeSummary(GKSummary *out) {
       std::sort(queue.begin(), queue.begin() + qtail);
       out->size = qtail;
@@ -419,7 +421,7 @@ struct GKSummary {
   /*! \brief number of elements in the summary */
   size_t size;
   GKSummary(Entry *data, size_t size)
-      : data(data), size(size) {} 
+      : data(data), size(size) {}
   /*! \brief the maximum error of the summary */
   inline RType MaxError(void) const {
     RType res = 0;
@@ -432,7 +434,7 @@ struct GKSummary {
   inline RType MaxRank(void) const {
     return data[size - 1].rmax;
   }
-  /*! 
+  /*!
    * \brief copy content from src
    * \param src source sketch
    */
@@ -450,8 +452,8 @@ struct GKSummary {
                 << "[" << data[i].rmin << "," << data[i].rmax << "]"
                 << std::endl;
     }
-  }  
-  /*! 
+  }
+  /*!
    * \brief set current summary to be pruned summary of src
    *        assume data field is already allocated to be at least maxsize
    * \param src source summary
@@ -486,8 +488,8 @@ struct GKSummary {
     }
     if (sb.size == 0) {
       this->CopyFrom(sa); return;
-    }    
-    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
+    }
+    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge");
     const Entry *a = sa.data, *a_end = sa.data + sa.size;
     const Entry *b = sb.data, *b_end = sb.data + sb.size;
     this->size = sa.size + sb.size;
@@ -500,7 +502,7 @@ struct GKSummary {
         aprev_rmin = a->rmin;
         ++dst; ++a;
       } else {
-        *dst = Entry(aprev_rmin + b->rmin, 
+        *dst = Entry(aprev_rmin + b->rmin,
                      b->rmax + a->rmax - 1, b->value);
         bprev_rmin = b->rmin;
         ++dst; ++b;
@@ -537,15 +539,15 @@ class QuantileSketchTemplate {
   /*! \brief type of summary type */
   typedef TSummary Summary;
   /*! \brief the entry type */
-  typedef typename Summary::Entry Entry;   
+  typedef typename Summary::Entry Entry;
   /*! \brief same as summary, but use STL to backup the space */
   struct SummaryContainer : public Summary {
     std::vector<Entry> space;
-    SummaryContainer(const SummaryContainer &src) : Summary(NULL, src.size) { 
+    SummaryContainer(const SummaryContainer &src) : Summary(NULL, src.size) {
       this->space = src.space;
       this->data = BeginPtr(this->space);
     }
-    SummaryContainer(void) : Summary(NULL, 0) { 
+    SummaryContainer(void) : Summary(NULL, 0) {
     }
     /*! \brief reserve space for summary */
     inline void Reserve(size_t size) {
@@ -554,7 +556,7 @@ class QuantileSketchTemplate {
         this->data = BeginPtr(space);
       }
     }
-    /*! 
+    /*!
      * \brief set the space to be merge of all Summary arrays
      * \param begin begining position in th summary array
      * \param end ending position in the Summary array
@@ -597,23 +599,24 @@ class QuantileSketchTemplate {
     }
     /*! \brief save the data structure into stream */
     template<typename TStream>
-    inline void Save(TStream &fo) const {
+    inline void Save(TStream &fo) const {  // NOLINT(*)
       fo.Write(&(this->size), sizeof(this->size));
       if (this->size != 0) {
         fo.Write(this->data, this->size * sizeof(Entry));
       }
     }
     /*! \brief load data structure from input stream */
     template<typename TStream>
-    inline void Load(TStream &fi) {
+    inline void Load(TStream &fi) {  // NOLINT(*)
       utils::Check(fi.Read(&this->size, sizeof(this->size)) != 0, "invalid SummaryArray 1");
       this->Reserve(this->size);
       if (this->size != 0) {
-        utils::Check(fi.Read(this->data, this->size * sizeof(Entry)) != 0, "invalid SummaryArray 2");
+        utils::Check(fi.Read(this->data, this->size * sizeof(Entry)) != 0,
+                     "invalid SummaryArray 2");
       }
     }
   };
-  /*! 
+  /*!
    * \brief intialize the quantile sketch, given the performance specification
    * \param maxn maximum number of data points can be feed into sketch
    * \param eps accuracy level of summary
@@ -741,8 +744,8 @@ class QuantileSketchTemplate {
  * \tparam DType type of data content
  * \tparam RType type of rank
  */
-template<typename DType, typename RType=unsigned>
-class WQuantileSketch : 
+template<typename DType, typename RType = unsigned>
+class WQuantileSketch :
       public QuantileSketchTemplate<DType, RType, WQSummary<DType, RType> >{
 };
 
@@ -751,20 +754,20 @@ class WQuantileSketch :
  * \tparam DType type of data content
  * \tparam RType type of rank
  */
-template<typename DType, typename RType=unsigned>
-class WXQuantileSketch : 
+template<typename DType, typename RType = unsigned>
+class WXQuantileSketch :
       public QuantileSketchTemplate<DType, RType, WXQSummary<DType, RType> >{
 };
 /*!
  * \brief Quantile sketch use WQSummary
  * \tparam DType type of data content
  * \tparam RType type of rank
  */
-template<typename DType, typename RType=unsigned>
-class GKQuantileSketch : 
+template<typename DType, typename RType = unsigned>
+class GKQuantileSketch :
       public QuantileSketchTemplate<DType, RType, GKSummary<DType, RType> >{
 };
 
-}  // utils
-}  // xgboost
-#endif
+}  // namespace utils
+}  // namespace xgboost
+#endif  // XGBOOST_UTILS_QUANTILE_H_