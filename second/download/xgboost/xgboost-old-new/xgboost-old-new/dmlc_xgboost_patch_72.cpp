@@ -218,8 +218,6 @@ struct WQSummary {
    */
   inline void SetCombine(const WQSummary &sa,
                          const WQSummary &sb) {
-	utils::Check(sa.Check("BeforeCombine A"), "Check Left error");
-    utils::Check(sb.Check("BeforeCombine B"), "Check right error");
     if (sa.size == 0) {
       this->CopyFrom(sb); return;
     }
@@ -270,21 +268,14 @@ struct WQSummary {
       } while (b != b_end);
     }
     this->size = dst - data;
-	const RType tol = 10;
+    const RType tol = 10;
     RType err_mingap, err_maxgap, err_wgap;
     this->FixError(&err_mingap, &err_maxgap, &err_wgap);
     if (err_mingap > tol || err_maxgap > tol || err_wgap > tol) {
       utils::Printf("INFO: mingap=%g, maxgap=%g, wgap=%g\n",
                     err_mingap, err_maxgap, err_wgap);
     }
 
-    if (!this->Check("AfterCombine")) {
-      utils::Printf("-----Left-----\n");
-      sa.Print();
-      utils::Printf("-----Right-----\n");
-      sb.Print();
-      utils::Error("Error after combine\n");
-    }
     utils::Assert(size <= sa.size + sb.size, "bug in combine");
   }
   // helper function to print the current content of sketch
@@ -335,7 +326,7 @@ struct WQSummary {
       }
     }
     return true;
-  }  
+  }
 };
 
 /*! \brief try to do efficient prunning */
@@ -352,7 +343,6 @@ struct WXQSummary : public WQSummary<DType, RType> {
   }
   // set prune
   inline void SetPrune(const WQSummary<DType, RType> &src, size_t maxsize) {
-    utils::Check(src.Check("BeforePrune"), "Check src error");
     if (src.size <= maxsize) {
       this->CopyFrom(src); return;
     }
@@ -413,12 +403,7 @@ struct WXQSummary : public WQSummary<DType, RType> {
             if (dx2 >= maxdx2) break;
             while (i < end &&
                    dx2 >= src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
-            if (i == end) {
-              utils::Printf("INFO: i==end reached, dx2=%g, i=%lu, end=%lu, mrange=%g, k=%lu, n=%lu, maxsize=%lu\n",
-                           dx2, i, end, mrange, k, n, maxsize);
-              src.Print();
-              break;
-            }
+            if (i == end) break;
             if (dx2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
               if (i != lastidx) {
                 this->data[this->size++] = src.data[i]; lastidx = i;
@@ -439,7 +424,6 @@ struct WXQSummary : public WQSummary<DType, RType> {
         begin += src.data[bid].rmin_next() - src.data[bid].rmax_prev();
       }
     }
-    utils::Check(this->Check("AfterPrune"), "Check result error");
   }
 };
 /*!