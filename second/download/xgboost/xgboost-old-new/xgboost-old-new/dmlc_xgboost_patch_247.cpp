@@ -2,22 +2,36 @@
 #include <utils/quantile.h>
 using namespace xgboost;
 
-int main(int argc, char *argv[]) {  
-  utils::WQuantileSketch<float, float> sketch;
+
+template<typename Sketch, typename RType>
+inline void test(void) {
+  Sketch sketch;
   size_t n;
   double wsum = 0.0;
   float eps, x, w;
   utils::Check(scanf("%lu%f", &n, &eps) == 2, "needs to start with n eps");
   sketch.Init(n, eps);
   printf("nlevel = %lu, limit_size=%lu\n", sketch.nlevel, sketch.limit_size);
   while (scanf("%f%f", &x, &w) == 2) {
-    sketch.Push(x, w);
+    sketch.Push(x, static_cast<RType>(w));
     wsum += w;
   }
-  sketch.CheckValid(0.1);
-  utils::WQuantileSketch<float, float>::SummaryContainer out;
+  sketch.CheckValid(static_cast<RType>(0.1));
+  typename Sketch::SummaryContainer out;
   sketch.GetSummary(&out);
-  printf("MaxError=%f/%f = %g\n", out.MaxError(), wsum, out.MaxError() / wsum);
+  double maxerr = static_cast<double>(out.MaxError());
+  printf("MaxError=%g/%g = %g\n", maxerr, wsum, maxerr / wsum);
   out.Print();
+}
+
+int main(int argc, char *argv[]) {
+  const char *method = "wq";
+  if (argc > 1) method = argv[1];
+  if (!strcmp(method, "wq")) {
+    test<utils::WQuantileSketch<float, float>, float>();
+  }
+  if (!strcmp(method, "gk")) {
+    test<utils::GKQuantileSketch<float, unsigned>, unsigned>();
+  }
   return 0;
 }