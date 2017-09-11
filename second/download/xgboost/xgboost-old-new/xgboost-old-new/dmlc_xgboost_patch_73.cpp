@@ -173,14 +173,6 @@ struct WQSummary {
       }
     }
   }
-  /*! \brief used for debug purpose, print the summary */
-  inline void Print(void) const {
-    for (size_t i = 0; i < size; ++i) {
-      std::cout << "x=" << data[i].value << "\t"
-                << "[" << data[i].rmin << "," << data[i].rmax << "]"
-                << " wmin=" << data[i].wmin << std::endl;
-    }
-  }
   /*!
    * \brief set current summary to be pruned summary of src
    *        assume data field is already allocated to be at least maxsize
@@ -226,6 +218,8 @@ struct WQSummary {
    */
   inline void SetCombine(const WQSummary &sa,
                          const WQSummary &sb) {
+	utils::Check(sa.Check("BeforeCombine A"), "Check Left error");
+    utils::Check(sb.Check("BeforeCombine B"), "Check right error");
     if (sa.size == 0) {
       this->CopyFrom(sb); return;
     }
@@ -276,9 +270,74 @@ struct WQSummary {
       } while (b != b_end);
     }
     this->size = dst - data;
+	const RType tol = 10;
+    RType err_mingap, err_maxgap, err_wgap;
+    this->FixError(&err_mingap, &err_maxgap, &err_wgap);
+    if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
+      utils::Printf("INFO: mingap=%g, maxgap=%g, wgap=%g\n",
+                    err_mingap, err_maxgap, err_wgap);
+    }
+
+    if (!this->Check("AfterCombine")) {
+      utils::Printf("-----Left-----\n");
+      sa.Print();
+      utils::Printf("-----Right-----\n");
+      sb.Print();
+      utils::Error("Error after combine\n");
+    }
     utils::Assert(size <= sa.size + sb.size, "bug in combine");
   }
+  // helper function to print the current content of sketch
+  inline void Print() const {
+    for (size_t i = 0; i < this->size; ++i) {
+      utils::Printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g\n",
+                    i, data[i].rmin, data[i].rmax,
+                    data[i].wmin, data[i].value);
+    }
+  }
+  // try to fix rounding error
+  // and re-establish invariance
+  inline void FixError(RType *err_mingap,
+                       RType *err_maxgap,
+                       RType *err_wgap) const {
+    *err_mingap = 0;
+    *err_maxgap = 0;
+    *err_wgap = 0;
+    RType prev_rmin = 0, prev_rmax = 0;
+    for (size_t i = 0; i < this->size; ++i) {
+      if (data[i].rmin < prev_rmin) {
+        data[i].rmin = prev_rmin;
+        *err_mingap = std::max(*err_mingap, prev_rmin - data[i].rmin);
+      } else {
+        prev_rmin = data[i].rmin;
+      }
+      if (data[i].rmax < prev_rmax) {
+        data[i].rmax = prev_rmax;
+        *err_maxgap = std::max(*err_maxgap, prev_rmax - data[i].rmax);
+      }
+      RType rmin_next = data[i].rmin_next();
+      if (data[i].rmax < rmin_next) {
+        data[i].rmax = rmin_next;
+        *err_wgap = std::max(*err_wgap, data[i].rmax - rmin_next);
+      }
+      prev_rmax = data[i].rmax;
+    }
+  }
+  // check consistency of the summary
+  inline bool Check(const char *msg) const {
+    const float tol = 10.0f;
+    for (size_t i = 0; i < this->size; ++i) {
+      if (data[i].rmin + data[i].wmin > data[i].rmax + tol ||
+          data[i].rmin < -1e-6f || data[i].rmax < -1e-6f) {
+        utils::Printf("----%s: Check not Pass------\n", msg);
+        this->Print();
+        return false;
+      }
+    }
+    return true;
+  }  
 };
+
 /*! \brief try to do efficient prunning */
 template<typename DType, typename RType>
 struct WXQSummary : public WQSummary<DType, RType> {
@@ -293,6 +352,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
   }
   // set prune
   inline void SetPrune(const WQSummary<DType, RType> &src, size_t maxsize) {
+    utils::Check(src.Check("BeforePrune"), "Check src error");
     if (src.size <= maxsize) {
       this->CopyFrom(src); return;
     }
@@ -334,11 +394,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
       utils::Printf("LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
                     src.size, maxsize, static_cast<double>(range),
                     static_cast<double>(chunk));
-      for (size_t i = 0; i < src.size; ++i) {
-        utils::Printf("[%lu] rmin=%g, rmax=%g, wmin=%g, v=%g, isbig=%d\n", i,
-                      src.data[i].rmin, src.data[i].rmax,  src.data[i].wmin,
-                      src.data[i].value, CheckLarge(src.data[i], chunk));
-      }
+      src.Print();
       utils::Assert(nbig < n - 1, "quantile: too many large chunk");
     }
     this->data[0] = src.data[0];
@@ -357,6 +413,12 @@ struct WXQSummary : public WQSummary<DType, RType> {
             if (dx2 >= maxdx2) break;
             while (i < end &&
                    dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
+            if (i == end) {
+              utils::Printf("INFO: i==end reached, dx2=%g, i=%lu, end=%lu, mrange=%g, k=%lu, n=%lu, maxsize=%lu\n",
+                           dx2, i, end, mrange, k, n, maxsize);
+              src.Print();
+              break;
+            }
             if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
               if (i != lastidx) {
                 this->data[this->size++] = src.data[i]; lastidx = i;
@@ -377,6 +439,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
         begin += src.data[bid].rmin_next() - src.data[bid].rmax_prev();
       }
     }
+    utils::Check(this->Check("AfterPrune"), "Check result error");
   }
 };
 /*!