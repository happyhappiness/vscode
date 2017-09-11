@@ -32,14 +32,27 @@ class WQuantileSketch {
     /*! \brief the value of data */
     DType value;
     // constructor
-    Entry(void) {}
+    Entry(void) {
+      rmin = rmax = wmin = 0.0;
+    }
     // constructor
     Entry(RType rmin, RType rmax, RType wmin, DType value)
-        : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {}
-    /*! \brief debug function,  */
-    inline void CheckValid(void) const {
+        : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {
+      if (!(this->rmax - this->rmin - this->wmin > -0.1)) {
+        rmax = rmin + wmin;
+        printf("correct\n");
+        printf("rmax=%f, rmin=%f, wmin=%f, plus=%f, v=%f\n", 
+               rmax, rmin, wmin, rmin+wmin, value);
+      }
+    }
+    /*! \brief debug function,  check Valid */
+    inline void CheckValid(RType eps = 0) const {
       utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
-      utils::Assert(rmax >= rmin + wmin, "relation constraint");
+      if (!(rmax - rmin - wmin > -eps)) {
+        printf("rmax=%f, rmin=%f, wmin=%f, plus=%f, v=%f\n", 
+               rmax, rmin, wmin, rmin+wmin, value);
+      }
+      utils::Assert(rmax- rmin - wmin > -eps  , "relation constraint: min/max");
     }
     /*! \return rmin estimation for v strictly bigger than value */
     inline RType rmin_next(void) const {
@@ -65,19 +78,21 @@ class WQuantileSketch {
      */
     inline RType MaxError(void) const {
       RType res = data[0].rmax - data[0].rmin - data[0].wmin;
-      for (RType i = 1; i < size; ++i) {
-        res = std::max(data[i].rmax_prev() - data[i - 1].rmax_next(), res);
+      for (size_t i = 1; i < size; ++i) {
+        res = std::max(data[i].rmax_prev() - data[i - 1].rmin_next(), res);
         res = std::max(data[i].rmax - data[i].rmin - data[i].wmin, res);
       }
       return res;
     }
     /*! 
      * \brief debug function, validate whether the summary 
      *  run consistency check to check if it is a valid summary
+     * \param eps the tolerate error level, used when RType is floating point and 
+     *        some inconsistency could occur due to rounding error
      */
-    inline void CheckValid(void) const {
-      for (RType i = 0; i < size; ++i) {
-        data[i].CheckValid();
+    inline void CheckValid(RType eps) const {
+      for (size_t i = 0; i < size; ++i) {
+        data[i].CheckValid(eps);
         if (i != 0) {
           utils::Assert(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin, "rmin range constraint");
           utils::Assert(data[i].rmax >= data[i - 1].rmax + data[i].wmin, "rmax range constraint");
@@ -92,6 +107,16 @@ class WQuantileSketch {
     inline void Clear(void) {
       size = 0;
     }
+    /*! \brief used for debug purpose, print the summary */
+    inline void Print(void) const {
+      for (size_t i = 0; i < size; ++i) {
+        printf("x=%f\t[%f, %f] wmin=%f\n", 
+               data[i].value, 
+               data[i].rmin,
+               data[i].rmax,
+               data[i].wmin);
+      }
+    }
     /*!
      * \brief copy content from src
      * \param src source sketch
@@ -117,10 +142,10 @@ class WQuantileSketch {
       // lastidx is used to avoid duplicated records
       size_t i = 0, lastidx = 0;
       for (RType k = 1; k < n; ++k) {
-        RType dx2 = (k * max_rank) / n * 2;
+        RType dx2 =  (2 * k * max_rank) / n;
         // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2 
         while (i < src.size - 1 &&
-               dx2 < src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
+               dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
         if (i == src.size - 1) break;
         if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
           if (i != lastidx) {
@@ -136,6 +161,11 @@ class WQuantileSketch {
         data[size++] = src.data[src.size - 1];
       }
     }
+    /*! 
+     * \brief set current summary to be merged summary of sa and sb
+     * \param sa first input summary to be merged
+     * \param sb second input summar to be merged
+     */
     inline void SetCombine(const Summary &sa,
                            const Summary &sb) {
       utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
@@ -226,10 +256,15 @@ class WQuantileSketch {
    * \param eps accuracy level of summary
    */
   inline void Init(size_t maxn, double eps) {
-    nlevel = std::max(ceil(maxn * eps), 1.0);
-    limit_size = ceil(nlevel / eps);
+    //nlevel = std::max(log2(ceil(maxn * eps)) - 2.0, 1.0);
+    nlevel = 1;
+    while (true) {
+      limit_size = ceil(nlevel / eps) + 1;
+      if ((1 << nlevel)  * limit_size >= maxn) break;
+      ++nlevel;
+    }
     // check invariant
-    utils::Assert((1 << nlevel)  * limit_size > maxn, "invalid init parameter");
+    utils::Assert((1 << nlevel) * limit_size >= maxn, "invalid init parameter");
     utils::Assert(nlevel <= limit_size * eps, "invalid init parameter");
     // lazy reserve the space, if there is only one value, no need to allocate space
     inqueue.resize(1);
@@ -241,7 +276,7 @@ class WQuantileSketch {
    * \brief add an element to a sketch 
    * \param x the elemented added to the sketch
    */
-  inline void Add(DType x, RType w = 1) {
+  inline void Push(DType x, RType w = 1) {
     if (qtail == inqueue.size()) {
       // jump from lazy one value to limit_size * 2
       if (inqueue.size() == 1) {
@@ -252,10 +287,11 @@ class WQuantileSketch {
         // cleanup queue
         qtail = 0;
         for (size_t l = 1; true; ++l) {
-          this->InitLevel(std::max(l + 1, nlevel));
+          this->InitLevel(l + 1);
           // check if level l is empty
           if (level[l].size == 0) {
-            level[l].SetPrune(temp, limit_size); break;            
+            level[l].SetPrune(temp, limit_size); 
+            break;            
           } else {
             // level 0 is actually temp space
             level[0].SetPrune(temp, limit_size);
@@ -295,10 +331,21 @@ class WQuantileSketch {
         }
       }
       out->CopyFrom(level[0]);
+    } else {
+      if (out->size > limit_size) {
+        temp.Reserve(limit_size);
+        temp.SetPrune(*out, limit_size);
+        out->CopyFrom(temp);
+      }
     }
   }
+  // used for debug, check if the sketch is valid
+  inline void CheckValid(RType eps) const {
+    for (size_t l = 1; l < level.size(); ++l) {
+      level[l].CheckValid(eps);
+    }    
+  }
   
- private:
   // initialize level space to at least nlevel
   inline void InitLevel(size_t nlevel) {
     if (level.size() >= nlevel) return;
@@ -355,7 +402,7 @@ class WQuantileSketch {
   // content of the summary
   std::vector<Entry> data;
   // temporal summary, used for temp-merge
-  SummaryContainer temp;  
+  SummaryContainer temp;
 };
 
 /*!
@@ -391,7 +438,7 @@ class GKQuantileSketch {
     /*! \brief the maximum error of the summary */
     inline RType MaxError(void) const {
       RType res = 0;
-      for (RType i = 1; i < size; ++i) {
+      for (size_t i = 1; i < size; ++i) {
         res = std::max(data[i].rmax - data[i-1].rmin, res);
       }
       return res;
@@ -424,7 +471,7 @@ class GKQuantileSketch {
       data[0] = src.data[0];
       RType n = maxsize - 1;
       RType top = 1;
-      for (RType i = 1; i < n; ++i) {
+      for (size_t i = 1; i < n; ++i) {
         RType k = (i * max_rank) / n;
         while (k > src.data[top + 1].rmax) ++top;
         // assert src.data[top].rmin <= k
@@ -539,7 +586,7 @@ class GKQuantileSketch {
    * \brief add an element to a sketch 
    * \param x the elemented added to the sketch
    */
-  inline void Add(DType x) {
+  inline void Push(DType x) {
     inqueue[qtail++] = x;
     if (qtail == inqueue.size()) {
       // start update sketch