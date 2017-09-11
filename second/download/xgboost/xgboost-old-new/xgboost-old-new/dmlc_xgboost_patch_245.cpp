@@ -2,7 +2,6 @@
 #include <utils/quantile.h>
 using namespace xgboost;
 
-
 template<typename Sketch, typename RType>
 inline void test(void) {
   Sketch sketch;
@@ -11,7 +10,6 @@ inline void test(void) {
   float eps, x, w;
   utils::Check(scanf("%lu%f", &n, &eps) == 2, "needs to start with n eps");
   sketch.Init(n, eps);
-  printf("nlevel = %lu, limit_size=%lu\n", sketch.nlevel, sketch.limit_size);
   while (scanf("%f%f", &x, &w) == 2) {
     sketch.Push(x, static_cast<RType>(w));
     wsum += w;
@@ -20,8 +18,10 @@ inline void test(void) {
   typename Sketch::SummaryContainer out;
   sketch.GetSummary(&out);
   double maxerr = static_cast<double>(out.MaxError());
-  printf("MaxError=%g/%g = %g\n", maxerr, wsum, maxerr / wsum);
   out.Print();
+  
+  printf("MaxError=%g/%g = %g\n", maxerr, wsum, maxerr / wsum);
+  printf("maxlevel = %lu, usedlevel=%lu, limit_size=%lu\n", sketch.nlevel, sketch.level.size(), sketch.limit_size);
 }
 
 int main(int argc, char *argv[]) {
@@ -30,6 +30,9 @@ int main(int argc, char *argv[]) {
   if (!strcmp(method, "wq")) {
     test<utils::WQuantileSketch<float, float>, float>();
   }
+  if (!strcmp(method, "wx")) {
+    test<utils::WXQuantileSketch<float, float>, float>();
+  }
   if (!strcmp(method, "gk")) {
     test<utils::GKQuantileSketch<float, unsigned>, unsigned>();
   }