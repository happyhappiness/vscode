@@ -102,6 +102,36 @@ inline static bool CmpSecond(const std::pair<float, unsigned> &a,
                              const std::pair<float, unsigned> &b) {
   return a.second > b.second;
 }
+
+#ifdef XGBOOST_STRICT_R_MODE_
+// check nan
+bool CheckNAN(double v);
+double LogGamma(double v);
+#else
+template<typename T>
+inline bool CheckNAN(T v) {
+#ifdef _MSC_VER
+  return (_isnan(v) != 0);
+#else
+  return isnan(v);
+#endif
+}
+template<typename T>
+inline T LogGamma(T v) {
+#ifdef _MSC_VER
+#if _MSC_VER >= 1800
+  return lgamma(v);
+#else
+#pragma message("Warning: lgamma function was not available until VS2013"\
+                ", poisson regression will be disabled")
+  utils::Error("lgamma function was not available until VS2013");
+  return static_cast<T>(1.0);
+#endif
+#else
+  return lgamma(v);
+#endif
+}
+#endif  // XGBOOST_STRICT_R_MODE_
 }  // namespace common
 }  // namespace xgboost
 #endif  // XGBOOST_COMMON_MATH_H_