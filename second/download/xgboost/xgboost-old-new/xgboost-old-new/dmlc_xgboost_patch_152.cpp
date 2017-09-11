@@ -316,7 +316,19 @@ struct WXQSummary : public WQSummary<DType, RType> {
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
+        printf("[%lu] rmin=%g, rmax=%g, wmin=%g, isbig=%d\n", i,
+               src.data[i].rmin, src.data[i].rmax, src.data[i].wmin,
+               CheckLarge(src.data[i], chunk));
+      }
+      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
+    }
     this->data[0] = src.data[0];
     this->size = 1;
     // use smaller size